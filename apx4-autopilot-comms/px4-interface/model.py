from pymavlink import mavutil
from dataclasses import dataclass
import mavlink bridge source, bridge sink
from connection import host, port

link = mavutil.mavlink_connection('tcpin:localhost:4560') # start a connection listening
link.wait_heartbeat() # indication of started session

@dataclass
class PluginConfig:
    """
    Input to and output from autopilot:
    """

class SimplePluginModel():
    """
    PX4 is the client and the simulator is the server 
    """
    
    def __init__(self, host, port):
        host = "127.0.0.1"
        port = 4560

    def initializaConnection(self, sys_id, comp_id, host, port):
        """
        Initiate the HIL mode connection, so that PX4 recive or send HIL messages to the simulator

        source system:
            by default for id #: 1-> px4, and 255 -> GCS
            We choose 2 -> simulator
        
        Source Component: check the list of id to ensure simulator's id doesnt interupt the connectins of other components.
        """
        master = mavutil.mavlink_connection(host, port, source_system=sys_id, source_component=comp_id)
        if master is None: raise ConnectionError ("E: Connection Initialization Unsuccessful")
        else: ("Connection Initialization Successful..")
        master.wait_heartbeat()    
        return master

    def recvActCmd (self, master):
        hil_actuator_controls = master.recv_match(type="HIL_ACTUATOR_CONTROLS", blocking=False)  # false blocking is for RTOS so sim doesnt keep stoping 
        if hil_actuator_controls is None: raise OSError("No hil_actuator_controls received")
        return hil_actuator_controls

    def decode(self, msg):
        #TODO: Put this in simple autopilot adaptor model
        msg.to_dict() # convert mavlink message to dict
        decode_map: dict[int, str] = {
            0: 'normalized_thrust', 
            1: 'normalized_roll',
            2: 'normalized_pitch',
            3: 'normalized_yaw'
        }
    

    def translator():
        def hil_actu_controls():
            if hil_actu_controls.is_new_mavlink: 
                message = hil_byte_data.mavlink_deserialization() #byte to mavlink 
                return actuator

        def uav_dynamics (actuator):
            pwm_input = actuator
            
            # minimum requirments - hil_sensor: imu
            acc = [xacc, yacc, zacc]
            gyro = [xgyro, ygyro, zgyro]
            mag = [xmag, ymag, zmag]
            pressure = [abs_pressure, diff_pressure, pressure_alt]

            # others for hil_sensor
            tempreture = 0
            hil_sensor_update_flag = [fields_updated]
            sensor_id = [id ++]	#Sensor ID (zero indexed). Used for multiple sensor inputs

        def uav_dynamics (actuator):
            pwm_input = actuator
            
            # minimum requirments - hil_sensor
            acc = [xacc, yacc, zacc]
            gyro = [xgyro, ygyro, zgyro]
            mag = [xmag, ymag, zmag]
            pressure = [abs_pressure, diff_pressure, pressure_alt]
            timestamp_sens = time_usec # for hil_sesnor


            # minimum requirments - hil_gps
            lla = (lat, lon, alt)
            gps_velcocity = (vn, ve, vd)
            gps_groundSpeed_velocity = gps_velcocity
            course = cog 

            # others for hil_gps
            num_satellites_visible	= satellites_visible  #Number of satellites visible. If unknown, set to UINT8_MAX
            gps_id = id++ # GPS ID (zero indexed). Used for multiple GPS input
            yaw_id = yaw++ #Yaw of vehicle relative to Earth's North, zero means not available, use 36000 for north
            timestamp_gps = time_usec # for hil_gps
            type_gps = fix_type # 0-1: no fix, 2: 2D fix, 3: 3D fix. Some applications will not use the value of this field unless it is at least two, so always correctly fill in the fix.

            
        
        def sensor_packing():
            hil_sensor_packing = hil_byte_msg.mavlink_serialization(acc, gyro,mag,pressure) #mavlink to byte for data and length
            hil_gps_packing = hil_byte_msg.mavlink_serialization(lla, gps_velcocity,gps_groundSpeed_velocity,course) #mavlink to byte for data and length


    def encode(sensor_packing):
        out_signal =  mavlinkbridgeSink(sensor_packing, heatbeat_bytes)
        return out_signal
    
    def input_to_autopilot(self, hil_imu, hil_gps, hil_obtical_flow, hil_rc_input_raw, hil_state_quaternion):
        pass
