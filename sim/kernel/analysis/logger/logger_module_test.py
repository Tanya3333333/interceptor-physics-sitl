from sim.kernel.analysis.logger.logger_module import ServerLogger
import unittest

class test_loggger (unittest.TestCase):  
    print ("waiting for simulator to connect to logger module...")
    
    def test_server_logger(self):
        server = ServerLogger()
        server.initialize_server()
        while True: 
            server.process_logs()

if __name__ == '__main__':
    unittest.main()