#!/usr/bin/env bash
set -euo pipefail
printf 'kernel='
uname -r
printf 'machine='
uname -m
printf 'time_utc='
date -u +%FT%TZ
printf 'page_bytes='
getconf PAGESIZE
printf 'available_memory_kib='
awk '/^MemAvailable:/ {print $2}' /proc/meminfo
printf 'cpu_threads='
getconf _NPROCESSORS_ONLN
printf 'cpu_model='
awk -F: '/^model name/ {gsub(/^ +/,"",$2); print $2; exit}' /proc/cpuinfo
printf 'cpu_virt='
grep -m1 -oE '(svm|vmx)' /proc/cpuinfo || true
if [[ -c /dev/kvm && -r /dev/kvm && -w /dev/kvm ]]; then echo 'kvm_access=yes'
else echo 'kvm_access=no'; fi
for f in /sys/module/kvm_amd/parameters/nested /sys/module/kvm_intel/parameters/nested; do
    if [[ -r "$f" ]]; then printf '%s=' "$f"; cat "$f"; fi
done
for tool in cc gcc clang make qemu-system-x86_64 qemu-img python3 readelf perf virsh; do
    if command -v "$tool" >/dev/null 2>&1; then
        printf '%s=' "$tool"
        command -v "$tool"
    else
        printf '%s=MISSING\n' "$tool"
    fi
done
if command -v qemu-system-x86_64 >/dev/null 2>&1; then
    qemu-system-x86_64 --version | head -n1
fi
for key in run pages_shared pages_sharing pages_unshared pages_volatile full_scans; do
    f="/sys/kernel/mm/ksm/$key"
    if [[ -r "$f" ]]; then printf 'ksm_%s=' "$key"; cat "$f"; fi
done
if [[ -r /proc/swaps ]]; then head -n4 /proc/swaps; fi
if [[ -r /sys/kernel/mm/transparent_hugepage/enabled ]]; then
    printf 'host_thp='
    cat /sys/kernel/mm/transparent_hugepage/enabled
fi
echo 'preflight=read_only'
