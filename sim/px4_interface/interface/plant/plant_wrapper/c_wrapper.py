from ctypes import *
from importlib.resources import files
import sys

lib_dir = files("sim.px4_interface.interface.plant.plant_shared_lib")

lib_name = "libPlant.dll" if sys.platform == "win32" else "libPlant.so"
libPlant_path = (str(lib_dir / lib_name))

# Plant Structure from C to Python.
motor_num = 4
class FDMInput(Structure):
    """Input struct for the C FDM
    The variables names need to match the libPlant.c
    """
    _fields_ = [
        ("motor_commands", c_float * motor_num)
    ]

class PLANTOutput(Structure):
    """Output struct for the C Plant
    The variables names need to match the libPlant.c
    """
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
    """
    This class is designed to translate the C based plant model code script to Python based using ctype library.
    Core functionality is to assign expectation of inputs for C based function and initalize the model, also step the fdm using byref 
    initialize the plant and load the .so file. 
    """
    def __init__(self):
        self.fdm_lib = None
        self.fdm_in = FDMInput()
        self.plant_out = PLANTOutput()
    
    def setup_plant(self):
        """
        This function first describes the signiture of the functions, then proceedd with calling the initialization in the wrapper.
        """
        self.fdm_lib = CDLL(libPlant_path) #load lib to get acess to exported c functions
        self.fdm_lib.plant_initialize.argtypes = [] # no expectations for the arguments to call function
        self.fdm_lib.plant_initialize.restype = None # expect no return from the function
        self.fdm_lib.fdm_step.argtypes = [POINTER(FDMInput), POINTER(PLANTOutput)]
        self.fdm_lib.fdm_step.restype = None

        self.fdm_lib.plant_initialize()
        
    def fdm_step(self):
        """Calls the C FDM step function."""
        self.fdm_lib.fdm_step(byref(self.fdm_in), byref(self.plant_out))