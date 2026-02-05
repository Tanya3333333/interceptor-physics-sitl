import time
import numpy as np
from pymavlink import mavutil
from interface.plant.plant_wrapper.c_wrapper import PlantWrapper

# note: only one language wrapper can be active at a time.
# TODO: if using python wrapper uncomment the line bellow and comment the c wrapper path. 
#from plant-wrapper.python_wrapper import PlantWrapper

# Config 
SIM_LOOP_RATE_HZ = 100.0 # Simulation loop frequency
DT_SIM = 1.0 / SIM_LOOP_RATE_HZ
DT_GPS = 1.0/2.0

SIM_SYS_ID = 2 # Simulator MAVLink System ID
SIM_COMP_ID = 222


# Model 
class PX4InterfaceSILModel():
    """Run the simulation in lockstep with PX4 SITL using MAVLink HIL messages."""
    def __init__(self):

        # PX4 Connection Related
        self.master = None

        # Plant Related
        self.plant_lib = None
        self.plant_wrapper = PlantWrapper()
        self.fdm_input = self.plant_wrapper.fdm_in
        self.plant_output = self.plant_wrapper.plant_out
        self.last_actuator_msg = [0.0, 0,0, 0.0, 0.0]  

    def set_param(self, name, value, param_type):
        """
        Generic MAVLink PARAM_SET to configure PX4 parameters from Python
        """
        if not self.master:return
        self.master.mav.param_set_send(
            self.master.target_system,
            self.master.target_component,
            name.encode('utf-8'),
            float(value),
            param_type)    
        time.sleep(0.1) # small delay so PX4 applies it

    def configure_px4_logging(self):
        """
        Configure PX4 logging for SIL mode and access after mission completetion in QGC.
        """
        self.set_param("SDLOG_MODE",      2, mavutil.mavlink.MAV_PARAM_TYPE_INT32)
        self.set_param("SDLOG_BACKEND",   1, mavutil.mavlink.MAV_PARAM_TYPE_INT32)
        self.set_param("SDLOG_PROFILE", 131, mavutil.mavlink.MAV_PARAM_TYPE_INT32)
        self.set_param("SDLOG_MISSION",   1, mavutil.mavlink.MAV_PARAM_TYPE_INT32)
        self.set_param("SDLOG_DIRS_MAX", 10, mavutil.mavlink.MAV_PARAM_TYPE_INT32)
        print("[PX4] Logging configured..")

    def initialize_connection(self, sys_id=SIM_SYS_ID, comp_id=SIM_COMP_ID):
        """Initiate the MAVLink TCP connection."""
        self.master = mavutil.mavlink_connection("tcpin:127.0.0.1:4560", 
                                                 source_system=sys_id, source_component=comp_id, 
                                                 input=True, autoreconnect=True, robust_parsing=True)
        self.master.wait_heartbeat()
        self.plant_wrapper.setup_plant() # Initialize (load) the FDM and clear previous runtimes
        self.configure_px4_logging()
        return self.master
    
    def close_comms(self):
        """Closes the MAVLink connection - for safety purposes."""
        if self.master: 
            try: self.master.close()
            except: pass
            self.master = None

    def send_heartbeat(self):
        """
        Sends a MAVLink heartbeat message to PX4 to configure a specific airframe and system type. 
        https://mavlink.io/en/services/heartbeat.html
        """ 
        if not self.master:
            return
        self.master.mav.heartbeat_send(
            mavutil.mavlink.MAV_TYPE_QUADROTOR,
            mavutil.mavlink.MAV_AUTOPILOT_GENERIC,
            mavutil.mavlink.MAV_MODE_FLAG_SAFETY_ARMED | mavutil.mavlink.MAV_MODE_FLAG_CUSTOM_MODE_ENABLED, 
            0,
            mavutil.mavlink.MAV_STATE_ACTIVE
        )
    
    def recv_actuator_controls(self):
        """Receives the HIL_ACTUATOR_CONTROLS message from PX4."""
        if not self.master: return None
        return self.master.recv_match(type="HIL_ACTUATOR_CONTROLS", blocking=False) 

    def actuator_to_fdm_input(self, actuator_msg):
        """Converts MAVLink ACTUATOR_CONTROLS to FDM_Input struct and normalized motor commands"""
        if actuator_msg is None:
            cmnd_stored = self.last_actuator_msg
        else:
            cmnd_stored = [float(actuator_msg.controls[i]) for i in range(len(self.fdm_input.motor_commands))]
            self.last_actuator_msg = cmnd_stored

        for i in range(len(self.fdm_input.motor_commands)): self.fdm_input.motor_commands [i] = cmnd_stored[i]
        return self.fdm_input
    
    def fdm_step(self):
        """Calls the C/Python FDM step function."""
        return self.plant_wrapper.fdm_step()
            
    def send_hil_sensor(self, t):
        if not self.master:
            return
        
        self.master.mav.hil_sensor_send(
            t,

            float(self.plant_output.acc[0]),
            float(self.plant_output.acc[1]),
            float(self.plant_output.acc[2]),

            float(self.plant_output.gyro[0]),
            float(self.plant_output.gyro[1]),
            float(self.plant_output.gyro[2]),

            float(self.plant_output.mag[0])/100,
            float(self.plant_output.mag[1])/100,
            float(self.plant_output.mag[2])/100,

            float(self.plant_output.pressure)/ 100,   # dynamic baro (abs pressure)
            0.0,                                    # diff pressure
            float(self.plant_output.lla[2]),          # pressure alt
            25.0,                                   # temp
            8191,                                   # field update
            0                                       # sensor id
        )

    def send_hil_gps(self, t):
        """
        Used the pymav array structure to fill in the param: https://mavlink.io/en/messages/common.html#HIL_GPS
        id msg = 113
        """
        if not self.master:
            return

        self.master.mav.hil_gps_send(
            t,                                                  # time_usec                                  
            3,                                                  # fix type (3d gps)
            int(self.plant_output.lla[0] * 1e7),                  # lat 
            int(self.plant_output.lla[1] * 1e7),                  # lon
            int(self.plant_output.lla[2] * 1000),                 # alt
            
            int(0.3*100),                                       # eph (cm)
            int(0.4*100),                                       # epv (cm)
            
            int(abs(self.plant_output.gnd_speed) * 100),          # vel (cm/s)
            int(self.plant_output.velocity_ned[0] * 100),         # vn
            int(self.plant_output.velocity_ned[1] * 100),         # ve
            int(self.plant_output.velocity_ned[2] * 100),         # vd
            
            int(self.plant_output.course_deg * 100),              # cog (cdeg)

            10,                                                 # satellites_visible
            0,                                                  # gps id
            0,                                                  # yaw
        )

    def send_hil_state_quaternion(self,t):
        """Converts FDM_Output to MAVLink HIL_STATE_QUATERNION and sends it.
            Fill in the Fields for HIL_STATE_QUATERNION (115): 
            https://mavlink.io/en/messages/common.html#HIL_STATE_QUATERNION
        """
        if not self.master:
            return

        # Quaternion (ctypes → float → tuple)
        attitude_quat_xyzw = (
            float(self.plant_output.attitude_quaternion[0]),          # w
            float(self.plant_output.attitude_quaternion[1]),          # x
            float(self.plant_output.attitude_quaternion[2]),          # y
            float(self.plant_output.attitude_quaternion[3])           # z
        )

        # Send MAVLink message
        self.master.mav.hil_state_quaternion_send(
            t,

            attitude_quat_xyzw,

            # Angular velocity (rad/s)
            float(self.plant_output.angular_velocity[0]),             # roll
            float(self.plant_output.angular_velocity[1]),             # pitch
            float(self.plant_output.angular_velocity[2]),             # yaw

            # GPS reference (lat/lon/alt must be ints)
            int(self.plant_output.lla[0] * 1e7),                      # lat 
            int(self.plant_output.lla[1] * 1e7),                      # lon
            int(self.plant_output.lla[2] * 1000),                     # alt

            # Velocity: NED (m/s → cm/s → int)
            int(self.plant_output.velocity_ned[0] * 100),
            int(self.plant_output.velocity_ned[1] * 100),
            int(self.plant_output.velocity_ned[2] * 100),

            0,                                                      # ind_airspeed
            0,                                                      # true_airspeed

            # accelerations (mG -> MAVLINK specific)
            int((self.plant_output.acc[0]/ 9.80665) * 1000),
            int((self.plant_output.acc[1]/ 9.80665) * 1000),
            int((self.plant_output.acc[2]/ 9.80665) * 1000)
        )