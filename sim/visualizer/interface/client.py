import socket, time, struct
import pymap3d

class VisualSimState:
    """
    Continuously sends physics parameters to visualize an aircraft.
    Inherits SimSITL so it already has self.px4 initialized.
    """
    def __init__(self, lin_ip ="10.0.0.129"):
        self.port_home = 55554 
        self.addr_home = (lin_ip, self.port_home)
        self.socket_home = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        
        self.port_state = 55556
        self.addr_state = (lin_ip, self.port_state)
        self.socket_state = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    
    def send_home_position (self, px4_home_posi):
        """ Home position is in degree for lat and lon data
        
        It's sending as a double for extra precesion so we do not have error propogation 
        as the states are stepping since the states in ecef are also depend on home position.
        """
        lat0 = px4_home_posi[0]
        lon0 = px4_home_posi[1]
        home_position_payload = struct.pack('<dd', lat0, lon0)          # 2 doubles
        self.socket_home.sendto(home_position_payload, self.addr_home)
        print ("home location sent to Unreal")
    
    def state_collection(self, plant_output):
        """sending fdm states to visualizer - Project AirSim Server"""
        # raw position [NED] in m
        N = plant_output.position_ned[0] #x
        E = plant_output.position_ned[1] #y
        D = plant_output.position_ned[2] #z
            
        # raw quaternion
        qw = plant_output.attitude_quaternion[0]
        qx = plant_output.attitude_quaternion[1]
        qy = plant_output.attitude_quaternion[2]
        qz = plant_output.attitude_quaternion[3] 
        
        # timestamp (for real-time analysis)
        t1_states = time.perf_counter_ns() 
        
        state_payload = struct.pack('<3f4fQ', N, E, D, qw, qx, qy, qz, t1_states) #3 floats, 4 floats, uint64
        self.socket_state.sendto(state_payload, self.addr_state)