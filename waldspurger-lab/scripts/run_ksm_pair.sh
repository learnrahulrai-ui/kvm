#!/usr/bin/env bash
set -euo pipefail
mib="${1:-32}"
seconds="${2:-45}"
merge="${3:-1}"
if [[ ! "$mib" =~ ^[0-9]+$ || ! "$seconds" =~ ^[0-9]+$ ||
      ! "$merge" =~ ^[01]$ ]] ||
   (( mib < 1 || mib > 128 || seconds < 5 || seconds > 600 )); then
  echo 'usage: run_ksm_pair.sh MiB(1..128) seconds(5..600) merge(0|1)' >&2
  exit 2
fi
project="$(cd "$(dirname "$0")/.." && pwd)"
[[ -x "$project/build/ksm_demo" ]] || { echo 'run make first' >&2; exit 2; }
a=""
b=""
cleanup() {
  [[ -n "$a" ]] && kill "$a" 2>/dev/null || true
  [[ -n "$b" ]] && kill "$b" 2>/dev/null || true
  wait 2>/dev/null || true
}
trap cleanup EXIT
"$project/build/ksm_demo" "$mib" "$merge" "$seconds" &
a=$!
"$project/build/ksm_demo" "$mib" "$merge" "$seconds" &
b=$!
printf 'test_pids=%s,%s; merge=%s; host KSM daemon unchanged\n' "$a" "$b" "$merge"
bash "$project/scripts/observe_ksm.sh" "$seconds" 2 || true
wait "$a"
wait "$b"
a=""
b=""
