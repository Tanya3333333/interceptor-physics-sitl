import sys
import time
import math
from ctypes import *
from pymavlink import mavutil

# --- Config ---
PX4_SIM_IP = '127.0.0.1'
PX4_SIM_PORT = 4560  # Standard TCP port for PX4 SIL
SIM_LOOP_RATE_HZ = 50.0 # Simulation loop frequency
DT = 1.0 / SIM_LOOP_RATE_HZ
SHARED_LIB_PATH = 'libfdm.so' # Compiled C library name 
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
    """Output struct from the C FDM."""
    _fields_ = [
        ("position_ned", c_double * 3),
        ("velocity_ned", c_double * 3),
        ("attitude_quaternion", c_float * 4), # w, x, y, z
        ("angular_velocity", c_float * 3), # P, Q, R
    ]


# --- Model ---
class PX4PluginModel():
    """MAVLink HIL bridge to run FDM in the loop."""
    def __init__(self, host=PX4_SIM_IP, port=PX4_SIM_PORT, sim_rate_hz=SIM_LOOP_RATE_HZ):
        self.host = host
        self.port = port
        self.dt = 1.0 / sim_rate_hz
        self.master = None
        self.fdm_lib = None
        self.fdm_input = FDM_Input()
        self.fdm_output = FDM_Output()

    def initialize_connection(self, sys_id=SIM_SYS_ID, comp_id=SIM_COMP_ID):
        """Initiate the MAVLink TCP connection."""
        self.master = mavutil.mavlink_connection(
                f'tcpout:{self.host}:{self.port}',
                source_system=sys_id,
                source_component=comp_id
            )
        self.master.wait_heartbeat()

    def setup_fdm(self):
        """Loads the C FDM library and initialize it.
        fdm_initialize and fdm_step are both exported c functions in the shared lib 
        Here we first describe the signiture of the functions and then proceed with calling the initialization in the wrapper
        """
        self.fdm_lib = CDLL(SHARED_LIB_PATH, winmode=0) #load lib to get acess to exported c functions
        self.fdm_lib.fdm_initialize.argtypes = [] # no expectations for the attribute of the loaded functions' arguments
        self.fdm_lib.fdm_initialize.restype = None # attribute of loaded function's return value (return nothing)
        self.fdm_lib.fdm_step.argtypes = [POINTER(FDM_Input), POINTER(FDM_Output)]
        self.fdm_lib.fdm_step.restype = None

        self.fdm_lib.fdm_initialize()

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

    def send_hil_state_quaternion(self):
        """Converts FDM_Output to MAVLink HIL_STATE_QUATERNION and sends it.
            Fill in the Fields for HIL_STATE_QUATERNION [16]: 
            https://mavlink.io/en/messages/common.html#HIL_STATE_QUATERNION
        """
        if not self.master: return

        time_us = int(time.time() * 1e6)

        # field name: attitude_quaternion
        attitude_quat_xyzw = [
            self.fdm_output.attitude_quaternion[0], # W
            self.fdm_output.attitude_quaternion[1], # X
            self.fdm_output.attitude_quaternion[2], # Y
            self.fdm_output.attitude_quaternion[3]  # Z
        ]

        # field name: body frame roll,pitch,and yaw -- Angular rates (rad/s)
        rollspeed = self.fdm_output.angular_velocity[0] # P
        pitchspeed = self.fdm_output.angular_velocity[1] # Q
        yawspeed = self.fdm_output.angular_velocity[2] # R

        # field name: lat, lon, and alt - TODO: Using placeholder GPS reference for simplicity
        LAT_REF = 48.601569 * 1e7 # degE7
        LON_REF = -123.411646 * 1e7 # degE7
        ALT_REF = 100000 # mm (100m AGL)

        # field name: ground velocity in m/s (NED) - converted to cm/s for MAVLink
        vx_cm = int(self.fdm_output.velocity_ned[0] * 100)
        vy_cm = int(self.fdm_output.velocity_ned[1] * 100)
        vz_cm = int(self.fdm_output.velocity_ned[2] * 100)

        ind_airspeed = 0
        true_airspeed = 0

        # field name: accekeration
        xacc = 0
        yacc = 0
        zacc = 0

        self.master.mav.hil_state_quaternion_send(
            time_us, attitude_quat_xyzw, 
            rollspeed, pitchspeed, yawspeed, 
            LAT_REF, LON_REF, ALT_REF,
            vx_cm, vy_cm, vz_cm,
            ind_airspeed, true_airspeed, xacc, yacc, zacc
        )

# error handling:
#      print("Connection Initialization Successful (Heartbeat Received).")
#        except Exception as e:
#            print(f"E: Connection Initialization Unsuccessful: {e}")
#            sys.exit(1)