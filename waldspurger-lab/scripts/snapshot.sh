#!/usr/bin/env bash
set -euo pipefail
out="${1:-}"
if [[ -z "$out" ]]; then
    echo 'usage: snapshot.sh OUTPUT_DIRECTORY' >&2
    exit 2
fi
mkdir -p "$out"
bash "$(dirname "$0")/preflight.sh" >"$out/preflight.txt"
date -u +%FT%TZ >"$out/time_utc.txt"
if command -v git >/dev/null 2>&1; then
    git rev-parse HEAD >"$out/repo_git_sha.txt" 2>/dev/null || true
fi
cat /proc/meminfo >"$out/meminfo.txt"
cat /proc/vmstat >"$out/vmstat.txt"
if [[ -d /sys/kernel/mm/ksm ]]; then
    for key in run pages_shared pages_sharing pages_unshared pages_volatile full_scans; do
       if [[ -r "/sys/kernel/mm/ksm/$key" ]]; then
           cat "/sys/kernel/mm/ksm/$key" >"$out/ksm_$key.txt"
       fi
    done
fi
echo "snapshot=$out; host config unchanged"
