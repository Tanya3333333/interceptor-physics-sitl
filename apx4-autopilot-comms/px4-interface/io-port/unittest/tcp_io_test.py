import unittest, threading, queue
from ..tcp_io import Client, Server

HOST = "127.0.0.1"

def _server(port_q):
    srv = Server(HOST, 0, backlog=1)
    srv.listener_socket()
    port_q.put(srv.listener.getsockname()[1])   # tell test which port
    srv.wait_for_listener()

    msg_in = srv.socket_read(1024)
    print(f"[SERVER] received: {msg_in.decode()}")

    reply = b"im happy w my side too"
    srv.socket_write(reply)
    print(f"[SERVER] sent: {reply.decode()}")

    srv.close_socket()

class TestTCPSession(unittest.TestCase):
    def test_happy_exchange(self):
        port_q = queue.Queue()
        t = threading.Thread(target=_server, args=(port_q,), daemon=True)
        t.start()
        port = port_q.get(timeout=2)

        cli = Client(HOST, port, timeout_ms=1000)
        cli.open_socket()

        msg = b"im happy with my side"
        cli.write_socket(msg)
        print(f"[CLIENT] sent: {msg.decode()}")

        resp = cli.read_socket(1024)
        print(f"[CLIENT] received: {resp.decode()}")

        cli.close_socket()
        self.assertEqual(resp, b"im happy w my side too")

        t.join(timeout=1)

if __name__ == "__main__":
    unittest.main(verbosity=2)
