import sys
import os
import time
import math
from ctypes import *
from pymavlink import mavutil

# --- Config ---
PX4_SIM_IP = '127.0.0.1'
PX4_SIM_PORT = 4560  # Standard tcp port for PX4 SIL
SIM_LOOP_RATE_HZ = 50.0 # Simulation loop frequency
DT = 1.0 / SIM_LOOP_RATE_HZ
SHARED_LIB_PATH = 'sim/px4-interface/interface/libfdm.so' # Compiled C library name 
SIM_SYS_ID = 2 # Simulator MAVLink System ID
SIM_COMP_ID = 222

# --- FDM Structure from C to Python ---
class FDM_Input(Structure):
    """Input struct for the C FDM."""
    _fields_ = [
        ("motor_commands", c_float * 4),
        ("delta_time", c_float),
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
        ("course_deg", c_double),
    ]

# --- Model ---
class PX4PluginModel():
    """MAVLink HIL bridge to run FDM in the loop."""
    def __init__(self, host=PX4_SIM_IP, port=PX4_SIM_PORT, sim_rate_hz=SIM_LOOP_RATE_HZ):

        # PX4 Connection Related
        self.host = host
        self.port = port
        self.dt = 1.0 / sim_rate_hz
        self.master = None

        # FDM Related
        self.fdm_lib = None
        self.fdm_input = FDM_Input()
        self.fdm_output = FDM_Output()

    def initialize_connection(self, sys_id=SIM_SYS_ID, comp_id=SIM_COMP_ID):
        """Initiate the MAVLink TCP connection."""
        self.master = mavutil.mavlink_connection("tcpin:127.0.0.1:4560", 
                                                 source_system=sys_id, source_component=comp_id, 
                                                 input=True, autoreconnect=True, robust_parsing=True)
        self.master.wait_heartbeat()
        return self.master

    def close(self):
        """Closes the MAVLink connection if TCP does not have data to read"""
        if self.master: 
            try: self.master.close()
            except: pass
            self.master = None

    def setup_fdm(self):
        """Loads the C FDM library and initialize it.
        fdm_initialize and fdm_step are both exported c functions in the shared lib 
        Here we first describe the signiture of the functions and then proceed with calling the initialization in the wrapper
        """
        self.fdm_lib = CDLL(SHARED_LIB_PATH) #load lib to get acess to exported c functions
        self.fdm_lib.fdm_initialize.argtypes = [] # no expectations for the attribute of the loaded functions' arguments
        self.fdm_lib.fdm_initialize.restype = None # attribute of loaded function's return value (return nothing)
        self.fdm_lib.fdm_step.argtypes = [POINTER(FDM_Input), POINTER(FDM_Output)]
        self.fdm_lib.fdm_step.restype = None

        self.fdm_lib.fdm_initialize()

    def send_heartbeat(self):
        """Sends a MAVLink heartbeat message to PX4.""" 
        if not self.master:
            return
        self.master.mav.heartbeat_send(
            mavutil.mavlink.MAV_TYPE_GCS,
            mavutil.mavlink.MAV_AUTOPILOT_INVALID,
            0, 0, 0
        )

    def recv_actuator_controls(self):
        """Receives the HIL_ACTUATOR_CONTROLS message from PX4."""
        if not self.master: return None
        return self.master.recv_match(type="HIL_ACTUATOR_CONTROLS", blocking=False) # Non-blocking receive for for RTOS so sim doesn't keep stoping 

    def actuator_to_fdm_input(self, actuator_msg):
        """Converts MAVLink ACTUATOR_CONTROLS to FDM_Input struct."""
        # 4 motor channels (the delta time is set later as its not a control channel)
        fdm_input = FDM_Input()
        for i in range(4):
            fdm_input.motor_commands[i] = max(0.0, min(1.0, actuator_msg.controls[i])) # Clamping controls to [motor off, full throttle] for normalized motor commands
        fdm_input.delta_time = self.dt
        return fdm_input
    
    
    def send_hil_sensor(self):
        self.master.mav.hil_sensor_send(
            int(time.time() * 1e6), # timestamp (microseconds)
            0, 0, 0,               # accelerometer (m/s^2)
            0, 0, 0,               # gyroscope (rad/s)
            0, 0, 0,               # magnetometer (gauss)
            1013.25,               # absolute pressure (hPa)
            0,                     # differential pressure (hPa)
            20.0,                  # temperature (deg C)
            0, 0, 0                # fields not used
        )
    
    '''
    def send_hil_sensor(self):
        if not self.master:
            return
        
        self.master.mav.hil_sensor_send(
            int(time.time() * 1e6),
            float(self.fdm_output.acc[0]),
            float(self.fdm_output.acc[1]),
            float(self.fdm_output.acc[2]),

            float(self.fdm_output.gyro[0]),
            float(self.fdm_output.gyro[1]),
            float(self.fdm_output.gyro[2]),

            float(self.fdm_output.mag[0]),
            float(self.fdm_output.mag[1]),
            float(self.fdm_output.mag[2]),

            float(self.fdm_output.pressure),  # absolute pressure
            0.0,                              # differential pressure
            20.0,                             # temp
            0xFFFF                            # fields updated mask
        )
    '''

    def send_hil_gps(self):
        if not self.master:
            return

        now = int(time.time() * 1e6)

        self.master.mav.hil_gps_send(
            now,                          # time_usec
            3,                            # fix_type (3 = 3D GPS fix)
            int(48.601569 * 1e7),         # lat (degE7)
            int(-123.411646 * 1e7),       # lon (degE7)
            int(100.0 * 1000),            # alt (mm)
            50,                           # eph (cm)
            50,                           # epv (cm)
            0,                            # vel (cm/s)
            0, 0, 0,                      # vn, ve, vd
            0,                            # cog (cdeg)
            10                            # satellites_visible
        )

    def send_hil_state_quaternion(self):
        """Converts FDM_Output to MAVLink HIL_STATE_QUATERNION and sends it.
            Fill in the Fields for HIL_STATE_QUATERNION (115): 
            https://mavlink.io/en/messages/common.html#HIL_STATE_QUATERNION
        """
        if not self.master:
            return

        # Timestamp (int64)
        time_us = int(time.time() * 1e6)

        # Quaternion (ctypes → float → tuple)
        attitude_quat_xyzw = (
            float(self.fdm_output.attitude_quaternion[0]),  # w
            float(self.fdm_output.attitude_quaternion[1]),  # x
            float(self.fdm_output.attitude_quaternion[2]),  # y
            float(self.fdm_output.attitude_quaternion[3])   # z
        )

        # Angular velocity (rad/s)
        rollspeed  = float(self.fdm_output.angular_velocity[0])
        pitchspeed = float(self.fdm_output.angular_velocity[1])
        yawspeed   = float(self.fdm_output.angular_velocity[2])

        # GPS reference (lat/lon/alt must be ints)
        LAT_REF = int(48.601569 * 1e7)     # degE7
        LON_REF = int(-123.411646 * 1e7)   # degE7
        ALT_REF = int(100.0 * 1000)        # mm (100 m AGL)

        # Velocity: NED (m/s → cm/s → int)
        vx_cm = int(self.fdm_output.velocity_ned[0] * 100)
        vy_cm = int(self.fdm_output.velocity_ned[1] * 100)
        vz_cm = int(self.fdm_output.velocity_ned[2] * 100)

        # Airspeed (leave as zero)
        ind_airspeed = 0
        true_airspeed = 0

        # Accelerations (must be integers)
        xacc = 0
        yacc = 0
        zacc = 0

        # Send MAVLink message
        self.master.mav.hil_state_quaternion_send(
            time_us,
            attitude_quat_xyzw,
            rollspeed,
            pitchspeed,
            yawspeed,
            LAT_REF,
            LON_REF,
            ALT_REF,
            vx_cm,
            vy_cm,
            vz_cm,
            ind_airspeed,
            true_airspeed,
            xacc,
            yacc,
            zacc
        )
    
'''
    def send_hil_gps(self):
        if not self.master:
            return

        t = int(time.time() * 1e6)

        lat = int(self.fdm_output.lla[0] * 1e7)
        lon = int(self.fdm_output.lla[1] * 1e7)
        alt = int(self.fdm_output.lla[2] * 1000)

        vn = int(self.fdm_output.velocity_ned[0] * 100)
        ve = int(self.fdm_output.velocity_ned[1] * 100)
        vd = int(self.fdm_output.velocity_ned[2] * 100)

        self.master.mav.hil_gps_send(
            t,
            3,
            lat, lon, alt,
            50, 50,
            int(abs(self.fdm_output.gnd_speed) * 100),
            vn, ve, vd,
            int(self.fdm_output.course_deg * 100),
            10
        )

    # -----------------------------------------------------
    def send_hil_state_quaternion(self):
        if not self.master:
            return
        
        quat = (
            self.fdm_output.attitude_quaternion[0],
            self.fdm_output.attitude_quaternion[1],
            self.fdm_output.attitude_quaternion[2],
            self.fdm_output.attitude_quaternion[3],
        )

        vx = int(self.fdm_output.velocity_ned[0] * 100)
        vy = int(self.fdm_output.velocity_ned[1] * 100)
        vz = int(self.fdm_output.velocity_ned[2] * 100)

        self.master.mav.hil_state_quaternion_send(
            int(time.time() * 1e6),
            quat,
            float(self.fdm_output.angular_velocity[0]),
            float(self.fdm_output.angular_velocity[1]),
            float(self.fdm_output.angular_velocity[2]),

            int(self.fdm_output.lla[0] * 1e7),
            int(self.fdm_output.lla[1] * 1e7),
            int(self.fdm_output.lla[2] * 1000),

            vx, vy, vz,
            0, 0,
            int(self.fdm_output.acc[0]),
            int(self.fdm_output.acc[1]),
            int(self.fdm_output.acc[2])
        )



'''
