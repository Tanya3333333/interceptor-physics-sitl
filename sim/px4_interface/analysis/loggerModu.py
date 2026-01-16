import socket, os, pickle
ip = socket.gethostbyname(socket.gethostname())

class SimLogger:
    """
    client side of the logger module
    """
    def __init__(self):
        self.host = ip
        self.port = 44446
        self.client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    def initialize_logger_client(self):
        files = [
            "fdm_log.txt",
            "sensor_log.txt",
            "state_q_log.txt",
            "gps_log.txt",
            "heartbeat_log.txt"
        ]
        
        for file_name in files:
            if os.path.exists(file_name):
                os.remove(file_name)
        
        self.client.connect((self.host, self.port))
        print ("[Logger Module] connected to logging server at port: ", self.port)

    def log_data(self, data):

        # make data type readable by socket communication by converting "list" to "bytes"
        data_app = pickle.dumps(data)
        self.client.sendall(data_app)
        print ("send data to server from client side:", data)
        

class ServerLogger:
    """
    server side of the logger module
    """
    def __init__(self):
        self.host = ip
        self.port = 44446
        self.flag_serv = 0
        self.server = socket.socket(socket.AF_INET, socket.SOCK_STREAM) # create TCP socket and receive data from the port
        self.conn = None

    def initialize_server(self):
        self.server.bind((self.host, self.port))
        self.server.listen()  # client in queue 
        self.conn, self.addr = self.server.accept()
        
        self.flag_serv = 1
        
        print ("connection established with simulator: at", self.addr)
        print ("connectoion establlish at: ", self.conn)

    def process_logs(self):
        buffer = self.conn.recv(4096) 
        print("data received at server side:", buffer)
        data = pickle.loads(buffer)
        print("data after unpickling:", data)

        # detect filename from data
        keywords = [
            "fdm step dt: ",
            "hil_sensor dt: ",
            "hil_state_q dt: ",
            "hil_gps dt: ",
            "heartbeat dt: "
        ]

        for i in data:
            if keywords[0] in i:
                _data = float(i.split(keywords[0])[1].strip())
                file_name = "fdm_log.txt"
            elif keywords[1] in i:
                _data = float(i.split(keywords[1])[1].strip())
                file_name = "sensor_log.txt"
            elif keywords[2] in i:
                _data = float(i.split(keywords[2])[1].strip())
                file_name = "state_q_log.txt"
            elif keywords[3] in i:
                _data = float(i.split(keywords[3])[1].strip())
                file_name = "gps_log.txt"
            elif keywords[4] in i:
                _data = float(i.split(keywords[4])[1].strip())
                file_name = "heartbeat_log.txt"
        
        print (f" data being processed {file_name}: {_data}")
        file = open(file_name, mode='a')
        file.write(f"{_data}\n")
        print (f"logged data to {file_name}: {_data}")
        
    
           