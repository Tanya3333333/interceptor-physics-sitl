import os, sys
import time, unittest
from ctypes import byref

sys.path.insert(0, os.path.abspath(os.path.join(os.path.dirname(__file__), '..')))
from interface.px4_interface_sitl import PX4InterfaceSILModel

# Frequencies (Hz) and intervals (sec)
FDM_RATE_HZ = 100.0
SENSOR_RATE_HZ = 90.0
STATE_QUAT_RATE_HZ = 50.0
GPS_RATE_HZ = 2.0
HEARTBEAT_RATE_HZ = 1.0

DT_FDM = 1.0 / FDM_RATE_HZ         
DT_SENSOR = 1.0 / SENSOR_RATE_HZ   
DT_STATE_QUAT = 1.0 / STATE_QUAT_RATE_HZ 
DT_GPS = 1.0 / GPS_RATE_HZ         
DT_HEARTBEAT = 1.0 / HEARTBEAT_RATE_HZ

class TestPX4WaypointsMission(unittest.TestCase):   
    """
    This class has single function for purly testing the alpha version of the simulator
    """
    def test_fdm_init_and_step(self):

        # Initialize PX4 and FDM
        px4 = PX4InterfaceSILModel()
        px4.initialize_connection()
        px4.setup_fdm()   # <-- load shared lib (libfdm.c)
        
        # frequency and timing control
        last_fdm_step = time.time()
        last_sensor_send = time.time()
        last_state_quat_send = time.time()
        last_gps_send = time.time()
        last_heartbeat_send = time.time()
        t_end = time.time() + 10000 
        
        while time.time() < t_end:
            now = time.time()    
            
            if now - last_heartbeat_send >= DT_HEARTBEAT: 
                px4.send_heartbeat()
                last_heartbeat_send = now

            # FDM step at 100Hz
            if now - last_fdm_step >= DT_FDM: 
                msg = px4.recv_actuator_controls()
                fdm_in = px4.actuator_to_fdm_input(msg)
                px4.fdm_lib.fdm_step(byref(fdm_in),byref(px4.fdm_output))
                last_fdm_step = now
                print ("Motor Commands:", fdm_in.motor_commands[0], fdm_in.motor_commands[1], fdm_in.motor_commands[2], fdm_in.motor_commands[3])

            t = int(now * 1e6)  # current time in microseconds
            # note: order of sending data matters 
            if now - last_sensor_send >= DT_SENSOR:
                px4.send_hil_sensor(t)  
                last_sensor_send = now
            if now - last_state_quat_send >= DT_STATE_QUAT:                 
                px4.send_hil_state_quaternion(t) 
                last_state_quat_send = now
            if now - last_gps_send >= DT_GPS:
                px4.send_hil_gps(t)
                last_gps_send = now
        
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