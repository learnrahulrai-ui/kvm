#!/usr/bin/env bash
set -euo pipefail
run_dir="${1:-}"
if [[ -z "$run_dir" || ! -d "$run_dir" ]]; then
  echo 'usage: stop_pair.sh RUN_DIR' >&2
  exit 2
fi
qmp_py="$(dirname "$0")/qmp.py"
for guest in a b; do
  sock="$run_dir/$guest.qmp"
  if [[ -S "$sock" ]]; then
    python3 "$qmp_py" "$sock" quit || {
      echo "QMP quit failed for $guest; inspect process before manual cleanup" >&2
    }
  fi
done
echo 'Requested QMP quit for lab VMs. Overlay disks are retained for inspection.'
