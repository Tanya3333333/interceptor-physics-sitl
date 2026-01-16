import unittest, os,sys
from pathlib import Path


PX4_ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(PX4_ROOT))


from analysis.loggerModu import ServerLogger

class test_loggger (unittest.TestCase):  
    print ("waiting for simulator to connect to logger module...")
    
    def test_server_logger(self):
        server = ServerLogger()
        server.initialize_server()
        while True: 
            
            server.process_logs()



if __name__ == '__main__':
    unittest.main()