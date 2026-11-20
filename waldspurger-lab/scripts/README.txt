SAFE INSTRUMENTATION ENTRY POINTS

bash scripts/preflight.sh
  Prints observed machine/kernel/QEMU/KSM capabilities. Reads only host state.

bash scripts/snapshot.sh /tmp/ws-baseline
  Saves current /proc/meminfo, /proc/vmstat and relevant KSM fields. Reads only host state.

bash scripts/run_ksm_pair.sh 32 45 0
  Launches two nonmergeable anonymous 32MiB process regions as baseline.
bash scripts/run_ksm_pair.sh 32 45 1
  Launches two mergeable anonymous 32MiB process regions; KSM must be enabled separately to merge them. Both programs exit after 45 seconds.
bash scripts/observe_ksm.sh 45 2 /tmp/ksm-01.csv
  Watches global host KSM counters but does NOT change /sys/kernel/mm/ksm/run.

bash scripts/launch_pair.sh /absolute/path/to/installed-linux-base.qcow2 /tmp/ws1
  Starts TWO isolated QEMU guests, separate overlays and Unix QMP sockets. Requires 4GiB MemAvailable before starting, a qcow2 base and accessible KVM. Source base is not modified. Use a short /tmp path for Unix socket length.
python3 scripts/qmp.py /tmp/ws1/a.qmp query-status
python3 scripts/qmp.py /tmp/ws1/a.qmp query-balloon
python3 scripts/qmp.py /tmp/ws1/a.qmp balloon 671088640
  Only bounded logical guest memory requests are allowed. VMs may not immediately reach the desired logical memory target; verify guest virtio-balloon driver.
bash scripts/observe_vms.sh /tmp/ws1 30 2 /tmp/vms-01.csv
  Samples QEMU process RSS, reported balloon logical memory, host-wide KSM additional sharing mappings. Not an exact saved-RAM accounting.
bash scripts/stop_pair.sh /tmp/ws1
  Sends quit to both local QMP sockets. Does not remove disk overlays.

OPTIONAL HOST-WIDE KSM ENABLEMENT — NOT AUTOMATED:
before="$(cat /sys/kernel/mm/ksm/run)"
printf 'prior run=%s\n' "$before"
sudo sh -c 'printf 1 > /sys/kernel/mm/ksm/run'
# Run test, then restore the specific prior setting. If old was 2, read the kernel KSM semantics before writing 2; that value unmerges all host pages.
printf '%s\n' "$before" | sudo tee /sys/kernel/mm/ksm/run
KSM is a host-wide setting and these commands can change other processes. Prefer a disposable L0 test VM or a machine with no valuable tenants before editing it.

NO script in this folder inserts a kernel module, binds a VFIO device, changes clocksource, or runs a historical vulnerable KVM host.
