#!/usr/bin/env python3
"""Minimal, bounded QEMU Machine Protocol client for local lab sockets."""
import json
import socket
import sys

ALLOWED = {
    "query-status", "query-balloon", "query-migrate", "query-commands",
    "query-kvm", "qom-list", "balloon", "stop", "cont", "quit"
}
def do_qmp(sockpath, command, arguments=None):
    with socket.socket(socket.AF_UNIX, socket.SOCK_STREAM) as sock:
        sock.settimeout(5)
        sock.connect(sockpath)
        stream = sock.makefile("rwb", buffering=0)
        greet = json.loads(stream.readline())
        if "QMP" not in greet:
            raise RuntimeError("not a QMP greeting")
        def execute(cmd, args=None):
            packet = {"execute": cmd}
            if args is not None:
                packet["arguments"] = args
            stream.write((json.dumps(packet) + "\n").encode())
            for _ in range(100):
                line = stream.readline()
                if not line:
                    raise RuntimeError("QMP closed before reply")
                reply = json.loads(line)
                if "event" in reply:
                    continue
                if "error" in reply:
                    raise RuntimeError(str(reply["error"]))
                if "return" in reply:
                    return reply["return"]
            raise RuntimeError("too many events without reply")
        execute("qmp_capabilities")
        return execute(command, arguments)

def main():
    if len(sys.argv) < 3:
        print("usage: qmp.py SOCK query-status|query-balloon|query-kvm|balloon BYTES|stop|cont|quit|query-migrate", file=sys.stderr)
        return 2
    sockpath, cmd = sys.argv[1:3]
    if cmd not in ALLOWED:
        print("command not in lab allowlist", file=sys.stderr)
        return 2
    args = None
    if cmd == "balloon":
        if len(sys.argv) != 4 or not sys.argv[3].isdigit():
            print("balloon needs logical VM memory size in bytes", file=sys.stderr)
            return 2
        desired = int(sys.argv[3])
        if not (256 * 1024 * 1024 <= desired <= 768 * 1024 * 1024):
            print("balloon target outside lab's 256-768 MiB bounds", file=sys.stderr)
            return 2
        args = {"value": desired}
    elif cmd == "qom-list":
        if len(sys.argv) != 4:
            print("qom-list needs an object path", file=sys.stderr)
            return 2
        args = {"path": sys.argv[3]}
    elif len(sys.argv) != 3:
        return 2
    print(json.dumps({"command": cmd, "result": do_qmp(sockpath, cmd, args)}, indent=2))
    return 0

if __name__ == "__main__":
    try:
        sys.exit(main())
    except (OSError, ValueError, json.JSONDecodeError, RuntimeError) as exc:
        print(f"qmp error: {exc}", file=sys.stderr)
        sys.exit(1)
