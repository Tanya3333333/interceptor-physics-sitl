import os, sys
# ensure parent package directory is on sys.path so "import interface" works
sys.path.insert(0, os.path.abspath(os.path.join(os.path.dirname(__file__), '..')))

import time, unittest
from ctypes import byref
from interface.px4_plugin import PX4PluginModel, FDM_Input, FDM_Output


def mission_waypoints_config(master, wp1, wp2):
    # link for this MAVLink command: https://mavlink.io/en/services/mission.html 
    MAV_CMD_NAV_WAYPOINT = 16
    MAV_FRAME_GLOBAL_RELATIVE_ALT = 3

    # Tell PX4 we are sending 2 waypoints
    master.mav.mission_count_send(
        master.target_system, 
        master.target_component, 
        2,0)

    # --- mission plan from home -> waypoint 1 -> waypoint 2 ---
    # home -> wp1
    req = master.recv_match(type=["MISSION_REQUEST", "MISSION_REQUEST_INT"], blocking=True, timeout=5)

    master.mav.mission_item_int_send(
        master.target_system, 
        master.target_component,
        0, # sequence number
        MAV_FRAME_GLOBAL_RELATIVE_ALT,
        MAV_CMD_NAV_WAYPOINT,
        1, # current
        1, # autocontinue
        0, 0, 0, 0, # param1-4 (not used for waypoint)
        int(wp1[0] * 1e7), # lat (degE7)
        int(wp1[1] * 1e7), # lon (degE7)
        float(wp1[2])) # alt (m)    
    
    # wp1 -> wp2
    req = master.recv_match(type=["MISSION_REQUEST", "TYPE_MISSION_ITEM_INT"], blocking=True, timeout=5)
    
    master.mav.mission_item_int_send(
        master.target_system,
        master.target_component,
        1, # sequence number
        MAV_FRAME_GLOBAL_RELATIVE_ALT,
        MAV_CMD_NAV_WAYPOINT,
        0, # current
        1, # autocontinue
        0, 0, 0, 0, # param1-4 (not used for waypoint)
        int(wp2[0] * 1e7), # lat (degE7)
        int(wp2[1] * 1e7), # lon (degE7)
        float(wp2[2])) # alt (m)    

    # Wait for MISSION_ACK
    ack = master.recv_match(type=["MISSION_ACK", "MISSION_ACK"], blocking=True, timeout=5)

class TestPX4WaypointsMission(unittest.TestCase):   

    def test_fdm_init_and_step(self):

        #setup
        px4 = PX4PluginModel()
        px4.initialize_connection()
        px4.setup_fdm()   # <-- load shared lib (libfdm.c)

        # 3. Set dummy motor commands
        px4.fdm_input.motor_commands[:] = (0.9, 0.8, 0.76, 0.88)
        px4.fdm_input.delta_time = px4.dt
        
        # loop timing
        t_end = time.time() + 1000  # Run for 1000 seconds to make sure QGC going to show "ready to fly" state
        sim_time_usec = 0
        last_loop_time = time.time()

        while time.time() < t_end:
            
            #update loop timing
            current_time = time.time()
            time_since_last_loop = current_time - last_loop_time
            last_loop_time = current_time
            sim_time_usec += int(time_since_last_loop * 1e6)
            t = sim_time_usec 
           
            # creates connection to QGC
            px4.send_heartbeat()
            
            #effect FDM step
            msg = px4.recv_actuator_controls()
            if msg: 
                print ("HIL ACTUATOR: ", msg.controls[:4])
                fdm_in = px4.actuator_to_fdm_input(msg)
                px4.fdm_lib.fdm_step(byref(fdm_in),byref(px4.fdm_output))

            print("ACC:", px4.fdm_output.acc[0], px4.fdm_output.acc[1], px4.fdm_output.acc[2])
            print("GYRO:", px4.fdm_output.angular_velocity[:])
            print("MAG:", px4.fdm_output.mag[:])
            print("LLA:", px4.fdm_output.lla[:])
            print("VEL:", px4.fdm_output.velocity_ned[:])
            print("Q:", px4.fdm_output.attitude_quaternion[:])
            print("PRESSURE:", px4.fdm_output.pressure)

            # note: order of sending data matters 
            px4.send_hil_sensor(t)              # at 250 Hz
            px4.send_hil_state_quaternion(t)    # at 50 Hz
            px4.send_hil_gps(t)                 # at 5 Hz   
            
            time.sleep(max(0, px4.dt - ((time.time()) - current_time)))
        
        self.assertTrue(True)

'''


class TestPX4WaypointsMission(unittest.TestCase):   

    def test_fdm_init_and_step(self):

        #setup
        px4 = PX4PluginModel()
        px4.initialize_connection()
        px4.setup_fdm()   # <-- load shared lib (libfdm.c)

        # 3. Set dummy motor commands
        px4.fdm_input.motor_commands[:] = (0.9, 0.8, 0.76, 0.88)
        px4.fdm_input.delta_time = px4.dt
        
        t_end = time.time() + 1000  # Run for 1000 seconds to make sure QGC going to show "ready to fly" state
        while time.time() < t_end:
            
            t = int(time.time() * 1e6) # create a synchronized timestep for sending hil data to px4
           
            # creates connection to QGC
            px4.send_heartbeat()
            
            #effect FDM step
            msg = px4.recv_actuator_controls()
            if msg: 
                print ("HIL ACTUATOR: ", msg.controls[:4])
                fdm_in = px4.actuator_to_fdm_input(msg)
                px4.fdm_lib.fdm_step(byref(fdm_in),byref(px4.fdm_output))

            print("ACC:", px4.fdm_output.acc[0], px4.fdm_output.acc[1], px4.fdm_output.acc[2])
            print("GYRO:", px4.fdm_output.angular_velocity[:])
            print("MAG:", px4.fdm_output.mag[:])
            print("LLA:", px4.fdm_output.lla[:])
            print("VEL:", px4.fdm_output.velocity_ned[:])
            print("Q:", px4.fdm_output.attitude_quaternion[:])
            print("PRESSURE:", px4.fdm_output.pressure)

            # order of sending data matters
            px4.send_hil_sensor(t)
            px4.send_hil_state_quaternion(t)
            px4.send_hil_gps(t)
            
            time.sleep(px4.dt)
        
        self.assertTrue(True)


'''


if __name__ == '__main__':
    unittest.main()