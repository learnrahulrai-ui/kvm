#!/usr/bin/env bash
set -euo pipefail
duration="${1:-30}"
interval="${2:-2}"
out="${3:-/dev/stdout}"
if [[ ! "$duration" =~ ^[0-9]+$ || ! "$interval" =~ ^[0-9]+$ ]] ||
   (( duration < 1 || duration > 600 || interval < 1 || interval > 60 )); then
    echo 'usage: observe_ksm.sh duration_sec(1..600) interval_sec(1..60) [csv_output]' >&2
    exit 2
fi
if [[ ! -r /sys/kernel/mm/ksm/pages_sharing ]]; then
    echo 'KSM sysfs absent; do not infer page sharing from configuration' >&2
    exit 2
fi
if [[ "$out" != /dev/stdout ]]; then
    mkdir -p "$(dirname "$out")"
fi
printf 'unix_time,run,pages_shared,pages_sharing,pages_unshared,pages_volatile,full_scans\n' >"$out"
for ((sec=0;sec<=duration;sec+=interval)); do
    now="$(date +%s)"
    values=()
    for key in run pages_shared pages_sharing pages_unshared pages_volatile full_scans; do
        f="/sys/kernel/mm/ksm/$key"
        if [[ -r "$f" ]]; then values+=("$(cat "$f")"); else values+=(NA); fi
    done
    (IFS=,; printf '%s,%s\n' "$now" "${values[*]}") >>"$out"
    (( sec + interval > duration )) && break
    sleep "$interval"
done
