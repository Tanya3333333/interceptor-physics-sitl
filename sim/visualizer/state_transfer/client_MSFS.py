import socket, time, struct
from plant.plant_wrapper.c_wrapper import PlantWrapper 

class SimStateModel: 
    def __init__ (self):
        self.win_ip = "192.168.1.123" # need to be changed with respect to Window PC IP address
        self.port = 5555
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM) # UDP Connection 

    def send_states(self):
        while True: 
"""
                        int(self.plant_output.lla[0] * 1e7),                  # lat 
            int(self.plant_output.lla[1] * 1e7),                  # lon
            int(self.plant_output.lla[2] * 1000),                 # alt
"""
            lat, lon, alt, roll, pitch, yaw, t_us = 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, time.perf_counter_ns()
            payload = struct.pack("<7f", lat, lon, alt, roll, pitch, yaw, t_us)  # little-endian, 7 floats
            self.sock.sendto(payload, (self.win_ip, self.port))
            time.sleep(0.033)