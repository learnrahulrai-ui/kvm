import importlib.util
import json
import socket
import tempfile
import threading
import unittest
from pathlib import Path

PATH = Path(__file__).resolve().parent.parent / "scripts/qmp.py"
spec = importlib.util.spec_from_file_location("lab_qmp", PATH)
mod = importlib.util.module_from_spec(spec)
spec.loader.exec_module(mod)

class QMPProtocol(unittest.TestCase):
    def test_handshake_event_skipping_and_result(self):
        with tempfile.TemporaryDirectory(prefix="ws-qmp-") as td:
            path = str(Path(td) / "a.qmp")
            listener = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)
            listener.bind(path)
            listener.listen(1)
            seen = []
            def serve():
                conn, _ = listener.accept()
                with conn:
                    stream = conn.makefile("rwb", buffering=0)
                    stream.write((json.dumps({"QMP": {"version": {}, "capabilities": []}}) + "\n").encode())
                    for index in range(2):
                        query = json.loads(stream.readline())
                        seen.append(query["execute"])
                        if index == 0:
                            stream.write(b'{"return":{}}\n')
                        else:
                            stream.write(b'{"event":"BALLOON_CHANGE","data":{}}\n')
                            stream.write(b'{"return":{"actual":671088640}}\n')
            thread = threading.Thread(target=serve, daemon=True)
            thread.start()
            try:
                result = mod.do_qmp(path, "query-balloon")
                self.assertEqual(result, {"actual": 671088640})
                self.assertEqual(seen, ["qmp_capabilities", "query-balloon"])
            finally:
                thread.join(timeout=5)
                listener.close()
            self.assertFalse(thread.is_alive())
if __name__ == "__main__":
    unittest.main()
