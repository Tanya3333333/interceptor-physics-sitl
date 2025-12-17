from ctypes import *
import os
# --- File Path --- 
BASE_DIR = os.path.dirname(os.path.abspath(__file__))
SHARED_LIB_PATH = os.path.join(BASE_DIR, 'plant-shared_lib','libPlant.so') # Compiled C library name


# --- Plant Structure from C to Python ---
class FDM_Input(Structure):
    """Input struct for the C FDM."""
    _fields_ = [
        ("motor_commands", c_float * 4)
    ]

class PLANT_Output(Structure):
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

        ("states_raw", c_double * 21)
    ]

class PlantWrapper:
    # --- Plant Structure from C to Python ---
    def __init__(self):
        self.fdm_lib = None
        self.fdm_in = FDM_Input()
        self.plant_out = PLANT_Output()
      
    
    def setup_plant(self):
        """
        Loads the C FDM library and initialize it.
        fdm_initialize and fdm_step are both exported c functions in the shared lib 
        Here, we first describe the signiture of the functions and then proceed with calling the initialization in the wrapper
        """
        self.fdm_lib = CDLL(SHARED_LIB_PATH) #load lib to get acess to exported c functions
        self.fdm_lib.plant_initialize.argtypes = [] # no expectations for the arguments to call function
        self.fdm_lib.plant_initialize.restype = None # expect no return from the function
        self.fdm_lib.fdm_step.argtypes = [POINTER(FDM_Input), POINTER(PLANT_Output)]
        self.fdm_lib.fdm_step.restype = None

        self.fdm_lib.plant_initialize()
        

    def fdm_step(self):
        """Calls the C FDM step function."""
        self.fdm_lib.fdm_step(byref(self.fdm_in), byref(self.plant_out))