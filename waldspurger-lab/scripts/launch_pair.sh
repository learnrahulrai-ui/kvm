#!/usr/bin/env bash
set -euo pipefail
base="${1:-}"
out="${2:-}"
if [[ -z "$base" || -z "$out" ]]; then
    echo 'usage: launch_pair.sh EXISTING_BASE.qcow2 NEW_RUN_DIRECTORY' >&2
    exit 2
fi
for tool in qemu-system-x86_64 qemu-img python3; do
    command -v "$tool" >/dev/null || { echo "missing $tool" >&2; exit 2; }
done
[[ -f "$base" ]] || { echo 'base image file missing' >&2; exit 2; }
[[ -c /dev/kvm && -w /dev/kvm ]] || { echo 'no writable /dev/kvm' >&2; exit 2; }
base="$(readlink -f "$base")"
# Two 768 MiB guests plus host/QEMU overhead require headroom beyond 1.5 GiB.
free_kib="$(awk '/^MemAvailable:/ {print $2}' /proc/meminfo)"
if (( free_kib < 4 * 1024 * 1024 )); then
    echo 'less than 4 GiB MemAvailable; refusing to start both guests' >&2
    exit 2
fi
image_format="$(qemu-img info --output=json "$base" | python3 -c 'import json,sys; print(json.load(sys.stdin)["format"])')"
[[ "$image_format" == qcow2 ]] || { echo 'base must be qcow2; refuse format guessing' >&2; exit 2; }
if [[ -e "$out" ]]; then
    echo 'run directory exists; choose a NEW path to avoid overwriting guest state' >&2
    exit 2
fi
mkdir -p "$out"
out="$(readlink -f "$out")"
# Linux AF_UNIX paths have a short maximum; fail rather than truncating QMP paths.
if (( ${#out} > 76 )); then
    echo 'run dir path too long for safe QMP UNIX sockets; use /tmp/ws1, for example' >&2
    exit 2
fi
printf '%s\n' "$base" >"$out/base_path.txt"
for guest in a b; do
    overlay="$out/$guest.qcow2"
    qemu-img create -f qcow2 -F qcow2 -b "$base" "$overlay"
    qemu-system-x86_64 -daemonize -nodefaults \
      -name "waldspurger-$guest" -machine q35,accel=kvm,memory-backend=ram0 \
      -m 768M -smp 2 \
      -object memory-backend-ram,id=ram0,size=768M,merge=on \
      -drive "file=$overlay,if=virtio,format=qcow2,cache=none" \
      -netdev user,id=net0 -device virtio-net-pci,netdev=net0 \
      -device virtio-balloon-pci,id=balloon0 \
      -qmp "unix:$out/$guest.qmp,server=on,wait=off" \
      -serial "file:$out/$guest.serial.log" -display none \
      -pidfile "$out/$guest.pid"
    printf 'guest=%s pid=%s qmp=%s\n' "$guest" "$(cat "$out/$guest.pid")" "$out/$guest.qmp"
done
printf 'Two private overlays created. The source base disk remains unmodified.\n'
printf 'To stop: python3 scripts/qmp.py %s/a.qmp quit; python3 scripts/qmp.py %s/b.qmp quit\n' "$out" "$out"
