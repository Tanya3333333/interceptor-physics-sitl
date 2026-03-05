from pymavlink import mavutil

SIM_SYS_ID = 2 # Simulator MAVLink System ID
SIM_COMP_ID = 222

class GroundStation:
    
    def __init__(self):
        self.master_gs = None
        self.last_home = [0.0, 0.0]
        
    
    def initialize_connection(self, sys_id=SIM_SYS_ID, comp_id=SIM_COMP_ID):
        """Initiate the MAVLink TCP connection."""
        self.master_gs = mavutil.mavlink_connection("udpin:127.0.0.1:14550", 
                                                 source_system=sys_id, source_component=comp_id, 
                                                 input=True, autoreconnect=True, robust_parsing=True)
        self.master_gs.wait_heartbeat()
        return self.master_gs
    
    def recv_home_position(self):
        """
        get the origin from the mission plan 
        interface: https://docs.px4.io/main/en/msg_docs/HomePosition  
        """
        if not self.master_gs: return None
        home = self.master_gs.recv_match(type="HOME_POSITION", blocking=False)
            
        if home is None: return self.last_home
           
        print(f"HOME POSITION type: {home}")
        home_data = [float(home.latitude * 1e-7), float(home.longitude * 1e-7)]
        self.last_home = home_data
        print ("home data recived")
        
        return self.last_home
            
            
        