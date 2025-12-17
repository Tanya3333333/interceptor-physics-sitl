import os, sys, logging
import time, unittest
from ctypes import byref

sys.path.insert(0, os.path.abspath(os.path.join(os.path.dirname(__file__), '..')))
from interface.px4_interface_sitl import PX4InterfaceSILModel

# --- Logging files ---
desktop = os.path.expanduser("~/Desktop")

LOG_PATH_FDM         = os.path.join(desktop, "timestamp_fdm_log.txt")
LOG_PATH_SENSOR      = os.path.join(desktop, "timestamp_hil_sensor_log.txt")
LOG_PATH_GPS         = os.path.join(desktop, "timestamp_hil_gps_log.txt")
LOG_PATH_STATE_Q     = os.path.join(desktop, "timestamp_hil_state_q_log.txt")
LOG_PATH_HEARTBEAT   = os.path.join(desktop, "timestamp_heartbeat_sent_log.txt")

def create_logger(name, file_path):
    logger = logging.getLogger(name)
    logger.setLevel(logging.INFO)
    
    handler = logging.FileHandler(file_path)
    handler.setFormatter(logging.Formatter("%(asctime)s - %(message)s"))
    
    logger.addHandler(handler)
    return logger

log_fdm       = create_logger("fdm_logger",          LOG_PATH_FDM)
log_sensor    = create_logger("sensor_logger",       LOG_PATH_SENSOR)
log_gps       = create_logger("gps_logger",          LOG_PATH_GPS)
log_state_q   = create_logger("stateq_logger",       LOG_PATH_STATE_Q)
log_heartbeat = create_logger("heartbeat_logger",    LOG_PATH_HEARTBEAT)


# --- Frequencies (Hz) and intervals (sec) ---
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
        px4.setup_plant()   # <-- load shared lib (libplant.c)
        
        # frequency and timing control
        last_fdm_step = time.time()
        last_sensor_send = time.time()
        last_state_quat_send = time.time()
        last_gps_send = time.time()
        last_heartbeat_send = time.time()
        
        while True:
            now = time.time()    
            
            if now - last_heartbeat_send >= DT_HEARTBEAT: 
                px4.send_heartbeat()
                log_heartbeat.info("heartbeat sent to px4 - timestamp: %f", (now - last_heartbeat_send))
                last_heartbeat_send = now

            # FDM step at 100Hz
            if now - last_fdm_step >= DT_FDM: 
                msg = px4.recv_actuator_controls()
                fdm_in = px4.actuator_to_fdm_input(msg)
                px4.fdm_lib.fdm_step(byref(fdm_in),byref(px4.plant_output))
                log_fdm.info("fdm step dt: %f", (now - last_fdm_step))
                last_fdm_step = now
                
                
                
            t = int(now * 1e6)  # current time in microseconds
    
            if now - last_sensor_send >= DT_SENSOR:
                px4.send_hil_sensor(t)  
                log_sensor.info("hil_sensor sent to px4 - timestamp: %f", (now - last_sensor_send))
                last_sensor_send = now
            if now - last_state_quat_send >= DT_STATE_QUAT:                 
                px4.send_hil_state_quaternion(t) 
                log_state_q.info("hil_state_quaternion sent to px4 - timestamp: %f", (now - last_state_quat_send))
                last_state_quat_send = now
            if now - last_gps_send >= DT_GPS:
                px4.send_hil_gps(t)
                log_gps.info("hil_gps sent to px4 - timestamp: %f", (now - last_gps_send))
                last_gps_send = now
    
        px4.close_comms()
        self.assertTrue(True)


if __name__ == '__main__':
    unittest.main()

"""
            print ("Motor Commands:", fdm_in.motor_commands[0], fdm_in.motor_commands[1], fdm_in.motor_commands[2], fdm_in.motor_commands[3])
            print ("HIL ACTUATOR: ", msg.controls[:4])
            print("ACC:", px4.fdm_output.acc[0], px4.fdm_output.acc[1], px4.fdm_output.acc[2])
            print("GYRO:", px4.fdm_output.angular_velocity[:])
            print("MAG:", px4.fdm_output.mag[:])
            print("LLA:", px4.fdm_output.lla[:])
            print("VEL:", px4.fdm_output.velocity_ned[:])
            print("Q:", px4.fdm_output.attitude_quaternion[:])
            print("PRESSURE:", px4.fdm_output.pressure)
"""