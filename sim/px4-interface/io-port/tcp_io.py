import socket, errno

DEFAULT_TIMEOUT_MS = 1000 # TODO make a way to calculate appropriate timeout

class Client: #simulator side
    def __init__(self, host, port, timeout_ms=DEFAULT_TIMEOUT_MS):
        self.host = host
        self.port = port
        self.timeout_ms = timeout_ms

    def open_socket(self):
        s = socket.socket(socket.AF_INET, socket.SOCK_STREAM) # (address family, socket type)
        try:
            s.settimeout(self.timeout_ms / 1000.0) # if connection did not happen witin a sec produce error
            s.connect((self.host, self.port))
            self.s = s
        except Exception:
            try: s.close()
            except Exception: pass
            raise

    def write_socket(self,data):
        self.s.sendall(data)

    def read_socket(self, nbyte=8192):  # 8k size of info
        return self.s.recv(nbyte)

    def close_socket(self):
        try: self.s.shutdown(socket.SHUT_RDWR)
        except OSError: pass
        try: self.s.close()
        except OSError: pass

class Server:
    """
    Backlog used to provide a list of client waiting for being accepted during the listening procedure. 
    """
    def __init__(self, host, port, backlog=5):
        self.host = host
        self.port = port
        self.backlog = backlog

    def listener_socket(self):
        ls = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        try:
            ls.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
            ls.bind((self.host, self.port))
            ls.listen(self.backlog)
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