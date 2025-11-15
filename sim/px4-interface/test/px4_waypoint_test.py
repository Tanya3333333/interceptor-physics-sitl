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

        # 1. Create plugin model (NO PX4 NEEDED)
        px4 = PX4PluginModel()

        # 2. Load shared library
        px4.setup_fdm()   # <-- should print from libfdm.c

        # 3. Set dummy motor commands
        px4.fdm_input.motor_commands[:] = (0.2, 0.2, 0.2, 0.2)
        px4.fdm_input.delta_time = px4.dt

        # 4. Run ONE FDM step
        px4.fdm_lib.fdm_step(
            byref(px4.fdm_input),
            byref(px4.fdm_output)
        )

        # Print the velocity to confirm C → Python works
        print("[py] velocity:",
              px4.fdm_output.velocity_ned[0],
              px4.fdm_output.velocity_ned[1],
              px4.fdm_output.velocity_ned[2])

        # test passes if no crash
        self.assertTrue(True)

'''
    def setUp(self):
        self.px4_plugin = PX4PluginModel()      # PX4PluginModel instance
        #self.px4_plugin.initialize_connection() # connect to PX4 SITL
        self.px4_plugin.setup_fdm()             # load shared lib (FDM)
    
    def tearDown(self):
        self.px4_plugin.close()                 # close connection to reset data for next step

    def test_QGC_mission_action(self): 
        """ HIL loop testing the QGC"""
        # cType struct inputting 

        FDM_Input().motor_commands[:]= (0.2, 0.2, 0.2, 0.2) # set all motors to 20% throttle 

        t_end = time.time() + 1000  # Run for 1000 seconds to make sure QGC going to show "ready to fly" state
        while time.time() < t_end:

            # creates connection to QGC
            self.px4_plugin.send_heartbeat()
            msg = self.px4_plugin.recv_actuator_controls()

            #effect FDM step
            if msg: 
                fdm_in = self.px4_plugin.actuator_to_fdm_input(msg)
                self.px4_plugin.fdm_lib.fdm_step(byref(FDM_Input()), byref(FDM_Output()))
            
            self.px4_plugin.send_hil_state_quaternion()
            self.px4_plugin.send_hil_sensor()
            self.px4_plugin.send_hil_gps()
            time.sleep(self.px4_plugin.dt)
        
        self.assertTrue(True)

    def test_waypoint_mission_upload(self):
        """Test uploading a waypoint mission to PX4 SITL."""
        wp1 = [48.602000, -123.412000, 20]  # lat, lon, alt (m)
        wp2 = [48.603000, -123.413000, 20]  # lat, lon, alt (m)
        
        self.assertIsNotNone(self.px4_plugin.master, "MAVLink connection not established")
        mission_waypoints_config(self.px4_plugin.master, wp1, wp2)



    ----
    
    def test_fdm_init_and_step(self):

        # load model and shared lib
        px4 = PX4PluginModel()
        px4.setup_fdm()  

        # set all motors to 20% throttle just for test
        px4.fdm_input.motor_commands[:] = (0.2, 0.2, 0.2, 0.2)
        px4.fdm_input.delta_time = px4.dt


        t_end = time.time() + 1000  # Run for 1000 seconds to make sure QGC going to show "ready to fly" state
        while time.time() < t_end:

            # creates connection to QGC
            px4.send_heartbeat()
            msg = px4.recv_actuator_controls()

            #effect FDM step
            px4.fdm_lib.fdm_step(byref(px4.fdm_input),byref(px4.fdm_output))
            
            px4.send_hil_state_quaternion()
            px4.send_hil_sensor()
            px4.send_hil_gps()
            time.sleep(px4.dt)


        # Print the all the fdm output in the terminal
        print("summery:",
              px4.fdm_output)

        # test passes if no crash
        self.assertTrue(True)


'''


if __name__ == '__main__':
    unittest.main()