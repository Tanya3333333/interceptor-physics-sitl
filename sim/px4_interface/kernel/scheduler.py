import asyncio,time,os, sys
sys.path.insert(0, os.path.abspath(os.path.join(os.path.dirname(__file__), '..')))
from interface.px4_interface_sitl import PX4InterfaceSILModel

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

""" multi rate task scheduler for simulation """
class simTask():
    def __init__(self):
        self.interface = PX4InterfaceSILModel()
        start = time.perf_counter()

    async def heartbeat(self):
        self.interface.send_heartbeat()
        await asyncio.sleep(DT_HEARTBEAT)

    async def fdm_step(self):
        self.interface.fdm_step()
        await asyncio.sleep(DT_FDM)

    async def send_hil_sensor(self):
        self.interface.send_hil_sensor()
        await asyncio.sleep(DT_SENSOR)

    async def send_state_quat(self):
        self.interface.send_hil_state_quaternion()
        await asyncio.sleep(DT_STATE_QUAT)

    async def send_hil_gps(self):
        self.interface.send_hil_gps()
        await asyncio.sleep(DT_GPS)

    async def main(self):
        start = time.perf_counter()
        await asyncio.gather(
            self.heartbeat(),
            self.fdm_step(),
            self.send_hil_sensor(),
            self.send_state_quat(),
            self.send_hil_gps()
        )
        end = time.perf_counter()
        print(f"Simulation ran for {end - start:.6f} seconds")
    asyncio.run(main())