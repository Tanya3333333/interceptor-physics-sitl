import os, time, csv, math
from datetime import datetime
from sim.px4_interface.interface.px4_interface_sitl import PX4InterfaceSILModel
from sim.px4_interface.interface.ground_station import GroundStation
from sim.visualizer.interface.client import VisualSimState

# Logging files 
desktop = os.path.expanduser("~/Desktop")

LOG_PATH_FDM            = os.path.join(desktop, "timestamp_fdm_log.csv")
LOG_PATH_SENSOR         = os.path.join(desktop, "timestamp_hil_sensor_log.csv")
LOG_PATH_GPS            = os.path.join(desktop, "timestamp_hil_gps_log.csv")
LOG_PATH_STATE_Q        = os.path.join(desktop, "timestamp_hil_state_q_log.csv")
LOG_PATH_HEARTBEAT      = os.path.join(desktop, "timestamp_heartbeat_sent_log.csv")
LOG_PATH_RAW_STATES     = os.path.join(desktop, "fdm_raw_states_log.csv")
LOG_PATH_EXEC           = os.path.join(desktop, "execution_time_log.csv")

# Frequencies (Hz) and intervals (sec)
# FDM rate sets max frequency, all step times must be integer multiples of DT_FDM.
FDM_RATE_HZ         = 100.0
SENSOR_RATE_HZ      = 100.0
STATE_QUAT_RATE_HZ  = 100.0
GPS_RATE_HZ         = 5.0
HEARTBEAT_RATE_HZ   = 1.0

DT_FDM              = 1.0 / FDM_RATE_HZ         
DT_SENSOR           = 1.0 / SENSOR_RATE_HZ   
DT_STATE_QUAT       = 1.0 / STATE_QUAT_RATE_HZ 
DT_GPS              = 1.0 / GPS_RATE_HZ         
DT_HEARTBEAT        = 1.0 / HEARTBEAT_RATE_HZ

class SimSITL:  
    """
    This class is a scheduler for PX4 Interface SITL with the logic of "busy wait" - meaning that the OS is consistantly using 100% of a CPU core to check time. 
    """
    def __init__(self):
        # Lists to buffer monitoring data from test run
        self.exec_t_log   = []
        self.fdm_t_log    = []
        self.sensor_t_log = []
        self.gps_t_log    = []
        self.home_position = [48.6508200, -123.4174899, 30.0]
        
        
        # Initialize PX4 and FDM 
        self.px4 = PX4InterfaceSILModel()
        self.px4.initialize_connection()                # connect to px4 and initialize plant
        self.px4.set_home_position(self.home_position)
        
        # initialize visualizer
        
        self.visualizer = VisualSimState()
        self.visualizer.send_home_position(self.home_position)

        
        # Cycle count
        self.sim_start = datetime.now()
        self.cycle   = 0

        # Set flag if sync'd to each FDM step
        if(math.isclose(SENSOR_RATE_HZ/FDM_RATE_HZ, 1)):self.syncImuToFDM = 1, print("HIL_SENSOR synchronized to FDM") 
        else:self.syncImuToFDM = 0 

        if(math.isclose(STATE_QUAT_RATE_HZ/FDM_RATE_HZ, 1)):self.syncStateToFDM = 1, print("HIL_STATE_QUATERNION synchronized to FDM") 
        else:self.syncStateToFDM = 0

    def precise_sleep(self, seconds):
        start_time = time.perf_counter()
        while time.perf_counter() - start_time < seconds:
            pass

    def step_plant(self):
        # Recv commands
        msg = self.px4.recv_actuator_controls()
        self.px4.actuator_to_fdm_input(msg)

        # FDM STEP
        self.fdm_t_log.append(time.perf_counter())  # Record time
        self.px4.fdm_step()

        t = int(time.perf_counter() * 1e6)

        # HIL_STATE_QUATERNION
        if(self.syncStateToFDM):
            self.px4.send_hil_state_quaternion(t) # If synced, call every loop 
        elif(self.cycle % (FDM_RATE_HZ // STATE_QUAT_RATE_HZ) == 0):
            self.px4.send_hil_state_quaternion(t) # Else send with decimation

        # HIL_SENSOR
        if(self.syncImuToFDM):
            self.sensor_t_log.append(time.perf_counter())
            self.px4.send_hil_sensor(t) # If synced, call every loop 
        
        elif(self.cycle % (FDM_RATE_HZ // SENSOR_RATE_HZ) == 0):
            self.sensor_t_log.append(time.perf_counter())
            self.px4.send_hil_sensor(t) # Else send with decimation

        # HIL_GPS
        if(self.cycle % (FDM_RATE_HZ // GPS_RATE_HZ) == 0):
            self.gps_t_log.append(time.perf_counter())
            self.px4.send_hil_gps(t)
        
        # HEARTBEAT
        if(self.cycle % (FDM_RATE_HZ // HEARTBEAT_RATE_HZ) == 0):
            self.px4.send_heartbeat()
        pass

    def run_sim(self):    
        # Init timing vars
        next_t = time.perf_counter()        
        
        try:
            print("Start Loop...")
            while True:     
                now = time.perf_counter()

                # Wait if needed
                if now < next_t:
                    self.precise_sleep(next_t - now)

                start = time.perf_counter()
                
                ## Start FDM Loop ##
                self.step_plant()
    
                #send plant states to visualizer
                self.visualizer.state_collection(self.px4.plant_output) 
                ## End Loop ##
                
                end = time.perf_counter()

                # Check timing of last loop
                exec_time   = end - start
                lateness    = end - next_t
                self.exec_t_log.append(exec_time) # record time

                if lateness > DT_FDM:
                    print(
                        f"OVERRUN: exec={exec_time*1e3:.2f}ms "
                        f"late={lateness*1e3:.2f}ms"
                    )

                self.cycle += 1
                next_t += DT_FDM # Sync to next period

        except KeyboardInterrupt:
            sim_end = datetime.now()
            print("\nShutdown...")
            print(f"sim start time since connection to PX4: {self.sim_start}")
            print(f"sim end time: {sim_end}")
            ## Write buffered data to files
            self.writeListToCsv(self.fdm_t_log, "FDM Timestamp", LOG_PATH_FDM)
            self.writeListToCsv(self.exec_t_log, "Execution Time", LOG_PATH_EXEC)
            self.writeListToCsv(self.sensor_t_log, "Sensor Timestamp", LOG_PATH_SENSOR)
            self.writeListToCsv(self.gps_t_log, "GPS Timestamp", LOG_PATH_GPS)
    
    def writeListToCsv(self, dataList, header, fileDir):
        with open(fileDir, 'w', newline='') as file:
            writer = csv.writer(file)
            #Write a header row
            writer.writerow([header])
            for val in dataList:
                writer.writerow([val])
            file.close
        print(f"Successfully wrote data to {fileDir}")

if __name__ == '__main__':
    sitl = SimSITL()
    sitl.run_sim()