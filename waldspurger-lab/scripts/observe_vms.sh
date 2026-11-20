#!/usr/bin/env bash
set -euo pipefail
run_dir="${1:-}"
duration="${2:-30}"
interval="${3:-2}"
out="${4:-/dev/stdout}"
if [[ -z "$run_dir" || ! -d "$run_dir" ||
      ! "$duration" =~ ^[0-9]+$ || ! "$interval" =~ ^[0-9]+$ ]] ||
   (( duration < 1 || duration > 600 || interval < 1 || interval > 60 )); then
    echo 'usage: observe_vms.sh RUN_DIR duration_sec interval_sec [csv_output]' >&2
    exit 2
fi
qmp_py="$(dirname "$0")/qmp.py"
if [[ "$out" != /dev/stdout ]]; then mkdir -p "$(dirname "$out")"; fi
get_rss() {
    local pid_file="$1" pid=""
    if [[ -r "$pid_file" ]]; then pid="$(cat "$pid_file")"; fi
    if [[ "$pid" =~ ^[0-9]+$ && -r "/proc/$pid/status" ]]; then
        awk '/^VmRSS:/ {print $2; found=1; exit} END {if(!found)print "NA"}' "/proc/$pid/status"
    else
        printf 'NA\n'
    fi
}
get_balloon() {
    local sock="$1" payload=""
    if [[ -S "$sock" ]]; then
        payload="$(python3 "$qmp_py" "$sock" query-balloon 2>/dev/null)" || { echo NA; return; }
        printf '%s\n' "$payload" | python3 -c 'import json,sys; v=json.load(sys.stdin).get("result",{}); print(v.get("actual","NA"))'
    else
        echo NA
    fi
}
get_ksm() {
    local f=/sys/kernel/mm/ksm/pages_sharing
    if [[ -r "$f" ]]; then cat "$f"; else echo NA; fi
}
printf 'unix_time,a_rss_kib,b_rss_kib,a_balloon_logical_bytes,b_balloon_logical_bytes,host_ksm_pages_sharing\n' >"$out"
for ((sec=0;sec<=duration;sec+=interval)); do
    (IFS=,; printf '%s,%s,%s,%s,%s,%s\n' "$(date +%s)" \
        "$(get_rss "$run_dir/a.pid")" "$(get_rss "$run_dir/b.pid")" \
        "$(get_balloon "$run_dir/a.qmp")" "$(get_balloon "$run_dir/b.qmp")" \
        "$(get_ksm)") >>"$out"
    (( sec + interval > duration )) && break
    sleep "$interval"
done
