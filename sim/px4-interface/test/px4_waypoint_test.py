import time
import unittest
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
        2)
    
    # --- mission plan from home -> waypoint 1 -> waypoint 2 ---
    # home -> wp1
    req = master.recv_match(type=["MISSION_REQUEST", "TYPE_MISSION_ITEM_INT"], blocking=True, timeout=5)
    assert req is not None, "No MISSION_REQUEST received for home to waypoint 1"

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
    assert req is not None, "No MISSION_REQUEST received for waypoint 1 to waypoint 2"
    
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
    ack = master.recv_match(type=["MISSION_ACK", "TYPE_MISSION_ACK"], blocking=True, timeout=5)
    assert ack is not None, "No MISSION_ACK received after sending waypoints"

class TestPX4WaypointsMission(unittest.TestCase):
    def setUp(self):
        self.px4_plugin = PX4PluginModel()      # PX4PluginModel instance
        self.px4_plugin.initialize_connection() # connect to PX4 SITL
        self.px4_plugin.setup_fdm()             # load shared lib (FDM)

    def waypoint_mission_upload(self):
        """Test uploading a waypoint mission to PX4 SITL."""
        wp1 = [48.602000, -123.412000, 20]  # lat, lon, alt (m)
        wp2 = [48.603000, -123.413000, 20]  # lat, lon, alt (m)
        mission_waypoints_config(self.px4_plugin.master, wp1, wp2)
    
    def QGC_mission_action(self, px4_plugin): 
        """ HIL loop testing the QGC"""
        # cType struct inputting 
        FDM_Input().motor_commands[:]= (0.2, 0.2, 0.2, 0.2) # set all motors to 20% throttle 

        t_end = time.time() + 10  # Run for 10 seconds to make sure QGC going to show "ready to fly" state
        while time.time() < t_end:
            msg = px4_plugin.recv_actuator_controls()
            if msg: FDM_Input(px4_plugin.actuator_to_fdm_input(msg)) 
            px4_plugin.fdm_lib.fdm_step(byref(FDM_Input()), byref(FDM_Output()))
            px4_plugin.send_hil_state_quaternion()
            time.sleep(px4_plugin.dt)
        
        self.assertTrue(True)

if __name__ == '__main__':
    unittest.main()