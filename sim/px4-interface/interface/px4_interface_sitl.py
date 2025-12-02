import sys, os, time
import numpy as np
from ctypes import *
from pymavlink import mavutil

# --- Config ---
SIM_LOOP_RATE_HZ = 100.0 # Simulation loop frequency
DT_SIM = 1.0 / SIM_LOOP_RATE_HZ
DT_GPS = 1.0/2.0

BASE_DIR = os.path.dirname(os.path.abspath(__file__))
SHARED_LIB_PATH = os.path.join(BASE_DIR, 'libfdm.so') # Compiled C library name


SIM_SYS_ID = 3 # Simulator MAVLink System ID
SIM_COMP_ID = 222

# --- FDM Structure from C to Python ---
class FDM_Input(Structure):
    """Input struct for the C FDM."""
    _fields_ = [
        ("motor_commands", c_float * 4)
    ]

class FDM_Output(Structure):
    _fields_ = [
        ("position_ned", c_double * 3),
        ("velocity_ned", c_double * 3),
        ("attitude_quaternion", c_float * 4),
        ("angular_velocity", c_float * 3),

        ("acc", c_double * 3),
        ("gyro", c_double * 3),
        ("mag", c_double * 3),

        ("pressure", c_double),
        ("lla", c_double * 3),

        ("gnd_speed", c_double),
        ("course_deg", c_double)
    ]

# --- Model ---
class PX4InterfaceSILModel():
    """MAVLink HIL bridge to run FDM in the loop."""
    def __init__(self):

        # PX4 Connection Related
        self.master = None

        # FDM Related
        self.fdm_lib = None
        self.fdm_input = FDM_Input()
        self.fdm_output = FDM_Output()
        self.last_actuator_msg = [0.0, 0,0, 0.0, 0.0]    

    def initialize_connection(self, sys_id=SIM_SYS_ID, comp_id=SIM_COMP_ID):
        """Initiate the MAVLink TCP connection."""
        self.master = mavutil.mavlink_connection("tcpin:127.0.0.1:4560", 
                                                 source_system=sys_id, source_component=comp_id, 
                                                 input=True, autoreconnect=True, robust_parsing=True)
        self.master.wait_heartbeat()
        return self.master

    def close(self):
        """Closes the MAVLink connection - for safety purposes."""
        if self.master: 
            try: self.master.close()
            except: pass
            self.master = None

    def send_heartbeat(self):
        """Sends a MAVLink heartbeat message to PX4.""" 
        if not self.master:
            return
        self.master.mav.heartbeat_send(
            mavutil.mavlink.MAV_TYPE_QUADROTOR,
            mavutil.mavlink.MAV_AUTOPILOT_GENERIC,
            mavutil.mavlink.MAV_MODE_FLAG_SAFETY_ARMED | mavutil.mavlink.MAV_MODE_FLAG_CUSTOM_MODE_ENABLED, 
            0,
            mavutil.mavlink.MAV_STATE_ACTIVE
        )

    def setup_fdm(self):
        """Loads the C FDM library and initialize it.
        fdm_initialize and fdm_step are both exported c functions in the shared lib 
        Here, we first describe the signiture of the functions and then proceed with calling the initialization in the wrapper
        """
        self.fdm_lib = CDLL(SHARED_LIB_PATH) #load lib to get acess to exported c functions
        self.fdm_lib.fdm_initialize.argtypes = [] # no expectations for the arguments to call function
        self.fdm_lib.fdm_initialize.restype = None # expect no return from the function
        self.fdm_lib.fdm_step.argtypes = [POINTER(FDM_Input), POINTER(FDM_Output)]
        self.fdm_lib.fdm_step.restype = None

        self.fdm_lib.fdm_initialize()
    
    def recv_actuator_controls(self):
        """Receives the HIL_ACTUATOR_CONTROLS message from PX4."""
        if not self.master: return None
        return self.master.recv_match(type="HIL_ACTUATOR_CONTROLS", blocking=False) 
    

    def actuator_to_fdm_input(self, actuator_msg):
        """Converts MAVLink ACTUATOR_CONTROLS to FDM_Input struct and normalized motor commands"""
        if actuator_msg is None:
            actuator_msg = self.last_actuator_msg
        else:
            cmnd_stored = []
            for i in range(4): 
                act = float(actuator_msg.controls[i])
                act = max (0.0, min (1.0, act))
                cmnd_stored.append(act)
            self.last_actuator_msg = cmnd_stored

        for i in range(4): self.fdm_input.motor_commands [i] = (self.last_actuator_msg[i])
        return self.fdm_input
    
    def send_hil_sensor(self, t):
        if not self.master:
            return
        
        self.master.mav.hil_sensor_send(
            t,

            float(self.fdm_output.acc[0]),
            float(self.fdm_output.acc[1]),
            float(self.fdm_output.acc[2]),

            float(self.fdm_output.gyro[0]),
            float(self.fdm_output.gyro[1]),
            float(self.fdm_output.gyro[2]),

            float(self.fdm_output.mag[0])/100,
            float(self.fdm_output.mag[1])/100,
            float(self.fdm_output.mag[2])/100,

            float(self.fdm_output.pressure)/ 100,   # dynamic baro (abs pressure)
            0.0,                                    # diff pressure
            float(self.fdm_output.lla[2]),          # pressure alt
            25.0,                                   # temp
            8191,                                 # field update
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
            int(self.fdm_output.lla[0] * 1e7),                  # lat 
            int(self.fdm_output.lla[1] * 1e7),                  # lon
            int(self.fdm_output.lla[2] * 1000),                 # alt
            
            int(0.3*100),                                       # eph (cm)
            int(0.4*100),                                       # epv (cm)
            
            int(abs(self.fdm_output.gnd_speed) * 100),          # vel (cm/s)
            int(self.fdm_output.velocity_ned[0] * 100),         # vn
            int(self.fdm_output.velocity_ned[1] * 100),         # ve
            int(self.fdm_output.velocity_ned[2] * 100),         # vd
            
            int(self.fdm_output.course_deg * 100),              # cog (cdeg)

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
            float(self.fdm_output.attitude_quaternion[0]),          # w
            float(self.fdm_output.attitude_quaternion[1]),          # x
            float(self.fdm_output.attitude_quaternion[2]),          # y
            float(self.fdm_output.attitude_quaternion[3])           # z
        )

        # Send MAVLink message
        self.master.mav.hil_state_quaternion_send(
            t,

            attitude_quat_xyzw,

            # Angular velocity (rad/s)
            float(self.fdm_output.angular_velocity[0]),             # roll
            float(self.fdm_output.angular_velocity[1]),             # pitch
            float(self.fdm_output.angular_velocity[2]),             # yaw

            # GPS reference (lat/lon/alt must be ints)
            int(self.fdm_output.lla[0] * 1e7),                      # lat 
            int(self.fdm_output.lla[1] * 1e7),                      # lon
            int(self.fdm_output.lla[2] * 1000),                     # alt

            # Velocity: NED (m/s → cm/s → int)
            int(self.fdm_output.velocity_ned[0] * 100),
            int(self.fdm_output.velocity_ned[1] * 100),
            int(self.fdm_output.velocity_ned[2] * 100),

            0,                                                      # ind_airspeed
            0,                                                      # true_airspeed

            # accelerations (mG -> MAVLINK specific)
            int((self.fdm_output.acc[0]/ 9.80665) * 1000),
            int((self.fdm_output.acc[1]/ 9.80665) * 1000),
            int((self.fdm_output.acc[2]/ 9.80665) * 1000)
        )