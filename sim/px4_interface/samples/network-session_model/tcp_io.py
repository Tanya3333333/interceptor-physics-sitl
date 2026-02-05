import socket, errno

DEFAULT_TIMEOUT_MS = 3000 

class Simclient: 

    def connect_tcp_socket(self,host,port, timeout_ms=DEFAULT_TIMEOUT_MS):
        s = socket.socket(socket.AF_INET, socket.SOCK_STREAM) # (address family, socket type)
        try:
            s.settimeout(timeout_ms / 1000.0) 
            s.connect((host, port))
            self.s = s
        except Exception: # if connection did not happen witin 3 seconds produce error
            try: s.close()
            except Exception: pass
            raise

    def write_to_socket(self,data):
        self.s.sendall(data)

    def read_from_socket(self, nbyte=8192):  # 8k size of info
        return self.s.recv(nbyte)

    def close_socket(self):
        try: self.s.shutdown(socket.SHUT_RDWR)
        except OSError: pass
        try: self.s.close()
        except OSError: pass

class SimServer:
    """
    Backlog used to provide a list of client waiting for being accepted during the listening procedure. 
    """

    def listener_socket(self, host, port, backlog):
        ls = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        try:
            ls.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
            ls.bind((host, port))
            ls.listen(backlog)
            self.listener = ls
        except Exception:
            try: ls.close()
            except Exception: pass
            raise
    
    def wait_for_listener(self):
        self.connection, self.peer = self.listener.accept()

    def socket_write(self, data):
        self.connection.sendall(data)

    def socket_read(self, nbytes=8192):
        return self.connection.recv(nbytes)

    def close_socket(self):
        try: self.connection.close()
        except AttributeError: pass
        except OSError: pass
        try: self.listener.close()
        except AttributeError: pass
        except OSError: pass