import asyncio, time, math, csv, os
from datetime import datetime
from interface.px4_interface_sitl import PX4InterfaceSILModel

# Logging files 
desktop = os.path.expanduser("~/Desktop")

LOG_PATH_FDM            = os.path.join(desktop, "timestamp_fdm_log.csv")
LOG_PATH_SENSOR         = os.path.join(desktop, "timestamp_hil_sensor_log.csv")
LOG_PATH_GPS            = os.path.join(desktop, "timestamp_hil_gps_log.csv")
LOG_PATH_STATE_Q        = os.path.join(desktop, "timestamp_hil_state_q_log.csv")
LOG_PATH_HEARTBEAT      = os.path.join(desktop, "timestamp_heartbeat_sent_log.csv")
LOG_PATH_RAW_STATES     = os.path.join(desktop, "fdm_raw_states_log.csv")
LOG_PATH_EXEC           = os.path.join(desktop, "execution_time_log.csv")

# config
FDM_RATE_HZ = 100.0
SENSOR_RATE_HZ = 90.0
STATE_QUAT_RATE_HZ = 50.0
GPS_RATE_HZ = 2.0
HEARTBEAT_RATE_HZ = 1.0

DT_FDM = (1/ FDM_RATE_HZ)
DT_SENSOR = (1/ SENSOR_RATE_HZ)   
DT_STATE_QUAT = (1/ STATE_QUAT_RATE_HZ) 
DT_GPS = (1/ GPS_RATE_HZ)        
DT_HEARTBEAT = (1/ HEARTBEAT_RATE_HZ)

rates = [
    FDM_RATE_HZ,
    SENSOR_RATE_HZ,     #1
    STATE_QUAT_RATE_HZ, #2
    GPS_RATE_HZ,        #3
    HEARTBEAT_RATE_HZ   #4
]

keywords = [
    "fdm step: ",
    "hil_sensor: ",  #1
    "hil_state_q: ", #2
    "hil_gps: ",     #3
    "heartbeat: ",   #4
    "steptime: "     #5
]

class SimSITL:  
    def __init__(self):
        # Lists to buffer monitoring data from test run
        self.exec_t_log      = []
        self.fdm_t_log       = []
        self.sensor_t_log    = []
        self.gps_t_log       = []
        self.heartbeat_t_log = []
        self.state_q_t_log   = []

        # Assign the list to keywords2
        self.keywords2 = [
            self.exec_t_log,
            self.fdm_t_log,
            self.sensor_t_log,
            self.gps_t_log,
            self.heartbeat_t_log,
            self.state_q_t_log
        ]
        
        # Initialize PX4 and FDM
        self.px4 = PX4InterfaceSILModel()
        self.px4.initialize_connection() # connect to px4 and initialize plant
        self.sim_start = datetime.now() 
        
        # Cycle count
        self.cycle   = 0

        # Set flag if sync'd to each FDM step
        if(math.isclose(SENSOR_RATE_HZ/FDM_RATE_HZ, 1)):self.syncImuToFDM = 1, print("HIL_SENSOR synchronized to FDM") 
        else:self.syncImuToFDM = 0 
        if(math.isclose(STATE_QUAT_RATE_HZ/FDM_RATE_HZ, 1)):self.syncStateToFDM = 1, print("HIL_STATE_QUATERNION synchronized to FDM") 
        else:self.syncStateToFDM = 0


    async def step_fdm (self):
        # Recv commands from autopilot
        msg = self.px4.recv_actuator_controls()
        self.px4.actuator_to_fdm_input(msg)

        # FDM stepping
        self.px4.fdm_step()
        self.keywords2[1].append(time.perf_counter())

    
    async def activate(self, rate_num, send, key_num, key2_num):

        if(self.cycle % (FDM_RATE_HZ // rates[rate_num]) == 0):
            send
            self.keywords2[key2_num].append(time.perf_counter())
        else: 
            pass
    
    async def writeListToCsv(self, dataList, header, fileDir):
        with open(fileDir, 'w', newline='') as file:
            writer = csv.writer(file)
            #Write a header row
            writer.writerow([header])
            for val in dataList:
                writer.writerow([val])
            file.close
        print(f"Successfully wrote data to {fileDir}")

    async def sitl_sim(self):
        sitl = asyncio.get_running_loop()
        next_t = sitl.time()
        starting = time.perf_counter()

        try:            
            while True:     
                now = sitl.time()
                # catchup to expected next_t
                if now < next_t:
                    await asyncio.sleep(next_t - now)

                ## Start Loop ##
                start = sitl.time()
                t = int(sitl.time() * 1e6)

                # run a step
                await asyncio.gather(
                    self.step_fdm(),
                    self.activate(1,self.px4.send_hil_sensor(t),1, 2),
                    self.activate(2,self.px4.send_hil_state_quaternion(t),2,5),
                    self.activate(3,self.px4.send_hil_gps(t),3,3),
                    self.activate(4,self.px4.send_heartbeat(),4,4),
                )
                self.keywords2[0].append(time.perf_counter())

                self.cycle += 1
                next_t += DT_FDM # Sync to next expected step

        except asyncio.CancelledError:
            sim_end = datetime.now()
            print("\nShutdown...")
            print(f"sim start time since connection to PX4: {self.sim_start}")
            print(f"sim end time: {sim_end}")
            ## Write buffered data to files
            await asyncio.gather(
                self.writeListToCsv(self.fdm_t_log, "FDM Timestamp", LOG_PATH_FDM),
                self.writeListToCsv(self.exec_t_log, "Execution Time", LOG_PATH_EXEC),
                self.writeListToCsv(self.sensor_t_log, "Sensor Timestamp", LOG_PATH_SENSOR),
                self.writeListToCsv(self.gps_t_log, "GPS Timestamp", LOG_PATH_GPS)
            )
    
if __name__ == '__main__':
    asyncio.run(SimSITL().sitl_sim())