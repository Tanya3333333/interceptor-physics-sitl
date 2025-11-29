import os, sys
import time, unittest
from ctypes import byref

sys.path.insert(0, os.path.abspath(os.path.join(os.path.dirname(__file__), '..')))
from interface.px4_interface_sitl import PX4InterfaceSILModel, DT_SIM, DT_GPS

class TestPX4WaypointsMission(unittest.TestCase):   

    def test_fdm_init_and_step(self):

        # Initialize PX4 and FDM
        px4 = PX4InterfaceSILModel()
        px4.initialize_connection()
        px4.setup_fdm()   # <-- load shared lib (libfdm.c)
        
        # frequency and timing control
        t_end = time.time() + 10000 # Run for 1000 seconds to make sure QGC going to show "ready to fly" state
        
        while time.time() < t_end:

            last_fdm_step_time = time.time()
            last_gps_send = time.time()
                   
            # creates connection to QGC
            px4.send_heartbeat()

            px4.step_fdm(fdm_in)
            
            # Mavlink to FDM
            msg = px4.recv_actuator_controls()
            fdm_in = px4.actuator_to_fdm_input(msg)
            
            # FDM step at 100Hz
            current_time = time.time()
            if current_time - last_fdm_step_time >= DT_SIM:
                px4.fdm_lib.fdm_step(byref(fdm_in),byref(px4.fdm_output))
                last_fdm_step_time = current_time
                print ("Motor Commands:", fdm_in.motor_commands[0], fdm_in.motor_commands[1], fdm_in.motor_commands[2], fdm_in.motor_commands[3])
            
            

            t = int(time.time() * 1e6)  # current time in microseconds
            # note: order of sending data matters 
            px4.send_hil_sensor(t)              
            px4.send_hil_state_quaternion(t) 

            if t - last_gps_send >= DT_GPS:   
                px4.send_hil_gps(t)
                last_gps_send = t
        
        self.assertTrue(True)

if __name__ == '__main__':
    unittest.main()



"""

            print ("HIL ACTUATOR: ", msg.controls[:4])
            print("ACC:", px4.fdm_output.acc[0], px4.fdm_output.acc[1], px4.fdm_output.acc[2])
            print("GYRO:", px4.fdm_output.angular_velocity[:])
            print("MAG:", px4.fdm_output.mag[:])
            print("LLA:", px4.fdm_output.lla[:])
            print("VEL:", px4.fdm_output.velocity_ned[:])
            print("Q:", px4.fdm_output.attitude_quaternion[:])
            print("PRESSURE:", px4.fdm_output.pressure)
"""