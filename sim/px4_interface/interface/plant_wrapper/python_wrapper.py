"""
Add fdm and sensor model i/o file:
import os
# --- File Path --- 
BASE_DIR = os.path.dirname(os.path.abspath(__file__))
python_plant = os.path.join(BASE_DIR, 'plant.py')
"""
# TODO: instead of 0 arrays put address of the Plant model (FDM and sensor models) i/o structure
class PlantWrapper:
    def __init__(self):
        self.fdm_input = {
            "motor_commands": [0.0,0.0,0.0,0.0]
        }

        self.plant_output = {
            "position_ned":        [0.0, 0.0, 0.0],
            "velocity_ned":        [0.0, 0.0, 0.0],
            "attitude_quaternion": [0.0, 0.0, 0.0, 0.0],
            "angular_velocity":    [0.0, 0.0, 0.0],

            "acc":                 [0.0, 0.0, 0.0],
            "gyro":                [0.0, 0.0, 0.0],
            "mag":                 [0.0, 0.0, 0.0],
            
            "lla":                 [0.0, 0.0, 0.0],
            "pressure":   0.0,
            "gnd_speed":  0.0,
            "course_deg": 0.0
        }

    def setup_plant(self):
        """
        setting all i/o to zero at the start.
        """
        for key, value in self.fdm_input.items():
            if isinstance(value, list):
                for i in range(len(value)):
                    value[i] = 0.0

        for key, value in self.plant_output.items():
            if isinstance(value, list):
                for i in range(len(value)):
                    value[i] = 0.0
            else:
                self.plant_output[key] = 0.0

    def step_fdm(self):  
        """
        advance one tick - placeholder for actual fdm and sensor models step function
        """ 
        #return UAV_Dynamics_step()
        pass