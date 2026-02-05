# TODO: use the appropriate plant model name to import your model info here.
# from plant_model import <plant_model_name>.py 

#TODO: change number of motors if necessary
motor_num = 4 

class PlantWrapper:
    """
    This is a wrapper to take the plant model (their io names) and equate it to the global variables 
    that can be recognized by the px4_interface_sitl model.
    Notes:
        1) This model can initialize the Plant before connecting to PX4 and run the FDM Step. 
        2) Make sure the plant model has "UAV_Dynamics_step()" function that can step your FDM Model. 
        3) Complete all the TODO lines before running the simulator. 

    """
    def __init__(self):

        # TODO: instead of 0 arrays put address of the Plant model (FDM and sensor models) i/o structure
        self.fdm_input = {
            "motor_commands": [0.0] * motor_num
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
        # TODO: uncomment the line bellow and remove "pass" to step your FDM and sensor models
        #return UAV_Dynamics_step()
        pass