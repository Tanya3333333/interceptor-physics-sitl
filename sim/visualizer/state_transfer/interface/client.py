import socket, time, pickle
#from sim.px4_interface.interface.plant.plant_wrapper.c_wrapper import PlantWrapper 
from sim.px4_interface.interface.px4_interface_sitl import PX4InterfaceSILModel

class SimStateModel: 
    """
    Sending minimum physics paramter to visualize an aircraft
    """
    def __init__ (self):
        self.win_ip = "10.0.0.129" # need to be changed with respect to Window PC IP address
        self.port = 55555
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM) # UDP Connection 
        self.plant_output = PX4InterfaceSILModel().plant_output

    def send_states(self):
        """
        Match the units and frames to Airsim expected interface.
        If bypassing the AirSim and wanting to purely/directly connect to Unreal Engine, the units are in cm and z is up positive. 
            . position_ned[i] *100 
            . negate z and qz.
        """
        while True: 
            # raw position (match unit and frame to AirSIm expected interface - not Unreal)
            print(self.plant_output.attitude_quaternion[0])
            x = self.plant_output.position_ned[0] 
            y = self.plant_output.position_ned[1] 
            z = self.plant_output.position_ned[2] 
            
            # raw quaternion
            qw = self.plant_output.attitude_quaternion[0]
            qx = self.plant_output.attitude_quaternion[1]
            qy = self.plant_output.attitude_quaternion[2]
            qz = self.plant_output.attitude_quaternion[3] 
            
            t_us = time.perf_counter_ns()                           # timestamp (for rt analysis)
            
            states = [x,y,z,qw,qx,qy,qz,t_us]
            payload = pickle.dumps(states)
            self.sock.sendto(payload, (self.win_ip, self.port))
            time.sleep(0.05)                                       # set frequency 
            print(self.plant_output.attitude_quaternion[0])
            
if __name__ == "__main__":
    visual = SimStateModel()
    visual.send_states()