import os, sys
import time
from datetime import datetime
import csv, math

sys.path.insert(0, os.path.abspath(os.path.join(os.path.dirname(__file__), '..')))
from interface.px4_interface_sitl import PX4InterfaceSILModel

# --- Logging files ---
desktop = os.path.expanduser("~/Desktop")

LOG_PATH_FDM            = os.path.join(desktop, "timestamp_fdm_log.csv")
LOG_PATH_SENSOR         = os.path.join(desktop, "timestamp_hil_sensor_log.csv")
LOG_PATH_GPS            = os.path.join(desktop, "timestamp_hil_gps_log.csv")
LOG_PATH_STATE_Q        = os.path.join(desktop, "timestamp_hil_state_q_log.csv")
LOG_PATH_HEARTBEAT      = os.path.join(desktop, "timestamp_heartbeat_sent_log.csv")
LOG_PATH_RAW_STATES     = os.path.join(desktop, "fdm_raw_states_log.csv")
LOG_PATH_EXEC           = os.path.join(desktop, "execution_time_log.csv")

STATE_LABELS = [
    "p (roll rate)", 
    "q (pitch rate)", 
    "r (yaw rate)",

    "u (body X vel)", 
    "v (body Y vel)", 
    "w (body Z vel)",

    "north (pos)", 
    "east (pos)", 
    "down (pos)",

    "rotor_tf_1",
    "rotor_tf_2",
    "rotor_tf_3",
    "rotor_tf_4",
    "rotor_tf_5",
    "rotor_tf_6"
]

def format_raw_states(raw_states):
    lines = []
    lines.append("------------------------")
    lines.append(f"FDM raw states at real time = {datetime.now().strftime('%H:%M:%S.%f')[:-3]}\n")

    for i in range(15):
        label = STATE_LABELS[i]
        value = raw_states[i]
        lines.append(f"{label:<18}: {value:.6f}")

    lines.append("------------------------")
    return "\n".join(lines)

# --- Frequencies (Hz) and intervals (sec) ---
# FDM rate sets max frequency, all step times must be integer multiples of DT_FDM!
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

class SimManager:  
    def __init__(self):
        # Lists to buffer monitoring data from test run
        self.exec_t_log   = []
        self.fdm_t_log    = []
        self.sensor_t_log = []
        self.gps_t_log    = []
        
        # Initialize PX4 and FDM
        self.px4 = PX4InterfaceSILModel()
        self.px4.initialize_connection() # connect to px4 and initialize plant
        
        # Cycle count
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

    def fdmLoop(self):
        # Recv commands
        msg = self.px4.recv_actuator_controls()
        self.px4.actuator_to_fdm_input(msg)

        # FDM STEP
        self.fdm_t_log.append(time.perf_counter()) # Record time
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

    def runSim(self):    
        # Init timing vars
        next_t  = time.perf_counter()

        try:
            print("Start Loop...")
            while True:     
                now = time.perf_counter()

                # Wait if needed
                if now < next_t:
                    self.precise_sleep(next_t - now)

                start = time.perf_counter()
                ## Start FDM Loop ##
                self.fdmLoop()
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
            print("\nShutdown...")
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
    sitl = SimManager()
    sitl.runSim()

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
