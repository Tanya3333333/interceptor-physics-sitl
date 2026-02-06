import socket, time, struct
from px4_interface.interface.plant.plant_wrapper.c_wrapper import PlantWrapper 

class SimStateModel: 
    """
    Sending minimum physics paramter to visualize an aircraft
    """
    def __init__ (self):
        self.win_ip = "192.168.1.123" # need to be changed with respect to Window PC IP address
        self.port = 5555
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM) # UDP Connection 

    def send_states(self):
        while True: 
            lat, lon, alt, roll, pitch, yaw, t_us = 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, time.perf_counter_ns()
            payload = struct.pack("<7f", lat, lon, alt, roll, pitch, yaw, t_us)  # little-endian, 7 floats
            self.sock.sendto(payload, (self.win_ip, self.port))
            time.sleep(0.033)