import unittest, time
from datetime import datetime
from interface.px4_interface_sitl import PX4InterfaceSILModel
from analysis.logger.logger_module import SimLogger, ServerLogger

# Frequencies (Hz) and intervals (sec)
FDM_RATE_HZ = 100.0
SENSOR_RATE_HZ = 90.0
STATE_QUAT_RATE_HZ = 50.0
GPS_RATE_HZ = 2.0
HEARTBEAT_RATE_HZ = 1.0

DT_FDM = int(1e9 / FDM_RATE_HZ)
DT_SENSOR = int(1e9 / SENSOR_RATE_HZ)   
DT_STATE_QUAT = int(1e9 / STATE_QUAT_RATE_HZ) 
DT_GPS = int(1e9 / GPS_RATE_HZ)        
DT_HEARTBEAT = int(1e9 / HEARTBEAT_RATE_HZ)

class SimSITL(unittest.TestCase):  

    def test_fdm_init_and_step(self):
        
        # Initialize logger
        logger_client = SimLogger()
        logger_client.initialize_logger_client()

        # Initialize PX4 and FDM
        px4 = PX4InterfaceSILModel()
        px4.initialize_connection() # connect to px4 and initialize plant
        sim_start = datetime.now()
        
        # frequency and timing control
        last_fdm_step = time.perf_counter_ns()
        last_sensor_send = time.perf_counter_ns()
        last_state_quat_send = time.perf_counter_ns()
        last_gps_send = time.perf_counter_ns()
        last_heartbeat_send = time.perf_counter_ns()
        
        t_end_sim = (time.perf_counter_ns()/1e9) + 200  # seconds
        while (time.perf_counter_ns()/1e9) < t_end_sim:
                
                """
                1. control and prioritize the function calls
                2. assess the time elapse for each data being sent to px4
                """
                
                now = time.perf_counter_ns()

                if (now - last_heartbeat_send >= DT_HEARTBEAT):
                    dt = (now - last_heartbeat_send)/1e9 # in seconds
                    data = [(f"heartbeat dt: {dt:.4f}")]
                    logger_client.log_data(data)
                    last_heartbeat_send = now

                if (now - last_fdm_step >= DT_FDM):
                    msg = px4.recv_actuator_controls()
                    px4.actuator_to_fdm_input(msg)
                    px4.fdm_step()
                    dt = (now - last_fdm_step)/1e9
                    data = [(f"fdm step dt: {dt:.4f}")]
                    logger_client.log_data(data)
                    last_fdm_step = now
            
                if (now - last_sensor_send >= DT_SENSOR):
                    t_hil_sens = int(time.time() * 1e6)  
                    px4.send_hil_sensor(t_hil_sens)  
                    dt = (now - last_sensor_send)/1e9
                    data = [(f"hil_sensor dt: {dt:.4f}")]
                    logger_client.log_data(data)
                    last_sensor_send = now

                if (now - last_state_quat_send >= DT_STATE_QUAT):
                    t_hil_state_q= int(time.time() * 1e6)  
                    px4.send_hil_state_quaternion(t_hil_state_q)
                    dt = (now - last_state_quat_send)/1e9
                    data = [(f"hil_state_q dt: {dt:.4f}")]
                    logger_client.log_data(data)
                    last_state_quat_send = now

                if (now - last_gps_send >= DT_GPS):
                    t_hil_gps = int(time.time() * 1e6)  
                    px4.send_hil_gps(t_hil_gps)
                    dt = (now - last_gps_send)/1e9
                    data = [(f"hil_gps dt: {dt:.4f}")]
                    logger_client.log_data(data)
                    last_gps_send = now
                
        self.assertTrue(True)
        sim_end = datetime.now()
        print(f"sim start time since connection to PX4: {sim_start}")
        print(f"sim end time: {sim_end}")
        
                
if __name__ == '__main__':
    unittest.main()