NONTRIVIAL KVM / LINUX / QEMU CORRECTNESS AND LIVENESS BUG REPRODUCTION INDEX
Recorded on: 2026-11-21. Last 20-year research sample, NOT every bug anyone encountered.
There is no published record establishing every bug Carl Waldspurger personally saw. The bugs below were reported by named upstream developers. His published ESX, scheduler and cache work supplies conceptual relationships, not personal attribution.
Scope: guest hung, failed I/O progress, incorrect page lifetime, migration hangs, data-integrity failures. This list excludes CVE-oriented security exercises, crashes that occur only in unit tests, and trivial error-handling defects. Some diagnostic reproductions use test harnesses but demonstrate real guest failures.
The current user's laptop kernel 6.14.0-37-generic is a stated target, not independently measured. Current actual machine capability must be probed on the other laptop. Debug host-only code does not establish historical kernel vulnerability.
Never load a version-pinned vulnerable kernel directly onto the user's primary laptop. Use isolated QEMU guests/nested virtualization, snapshots, serial console, resource limits and throwaway disks. Some host kernel KVM bugs require a dedicated disposable host or L0 nested setup.

B01 01-2016-thp-amd-guest-corruption | CONFIRMED_REPORT_FIXED_RELEASE_CAUSAL_COMMIT_NOT_ESTABLISHED | HISTORICAL_VM_ONLY | source https://bugs.debian.org/cgi-bin/bugreport.cgi?bug=821225
B02 02-2019-kvm-zone-device-reference-leak | CONFIRMED_UPSTREAM_CAUSAL_PATCH | REQUIRES_DEVDAX | source https://lkml.iu.edu/1911.1/04249.html
B03 03-2020-nested-tsc-migration-guest-hang | CONFIRMED_PATCH_TESTED_AUTHOR | MODERATE_NESTED_AMD | source https://lkml.iu.edu/2009.2/06466.html
B04 04-2023-postcopy-recovery-stuck | CONFIRMED_UPSTREAM_PATCH_WITH_RECIPE | MODERATE_SOFTWARE_ONLY | source https://patchew.org/QEMU/20231017202633.296756-1-peterx@redhat.com/20231017202633.296756-3-peterx@redhat.com/
B05 05-2024-kvm-ksm-numa-vcpu-stalls | CONFIRMED_REPORT_BISECTED_PATCH_VALIDATED | NEEDS_LARGE_DUAL_NUMA_HOST | source https://lists.openwall.net/linux-kernel/2024/01/04/582
B06 06-2025-kvm-dirty-ring-reset-livelock | CONFIRMED_PATCH_CONTAINS_MINIMAL_CONCURRENT_REPRO | GOOD_NESTED_KVM_GUEST | source https://lists.openwall.net/linux-kernel/2025/05/16/1409
B07 07-2026-kvm-vfio-disabled-bar-vm-kill | CONFIRMED_PRODUCTION_REPORT_REDUCED_REPRO | REQUIRES_SPARE_VFIO_PCI_DEVICE | source https://lkml.iu.edu/2606.2/07858.html
B08 08-2026-qemu-postcopy-page-request-leak | CONFIRMED_UPSTREAM_PATCH_WITH_THREAD_TRACES | SOFTWARE_HEAVY_VHOST_USER | source https://www.mail-archive.com/qemu-devel@nongnu.org/msg1221024.html
B09 09-2026-qemu-multifd-postcopy-channel-hang | CONFIRMED_UPSTREAM_PATCH_EXACT_REPRO_COMMAND | GOOD_ON_SINGLE_LINUX_LAPTOP | source https://go.mail-archive.com/qemu-devel@nongnu.org/msg1239999.html
B10 10-2026-clocksource-jiffies-boot-deadlock | CONFIRMED_AUTHOR_REPRO_AND_PATCH | GOOD_ISOLATED_QEMU_GUEST | source https://lkml.iu.edu/2611.0/04403.html
B11 11-2026-vtpm-proxy-release-hang | CONFIRMED_AUTHOR_MINIMAL_C_AND_NEGATIVE_CONTROL_CAUSE_UNRESOLVED | GOOD_DISPOSABLE_GUEST_7_3 | source https://lkml.iu.edu/2611.1/06205.html
B12 12-2026-f2fs-writeback-hang | CURRENT_BUG_REPORT_ORIGINAL_REPRO_LINK_CAUSE_NOT_CONFIRMED | POSSIBLE_GUEST_7_4_RC3 | source https://lkml.iu.edu/2611.2/12996.html
B13 13-2009-kvm-ksm-teardown-latency | HISTORICAL_DISTRIBUTION_CHANGELOG_NO_MINIMAL_REPRO | ARCHIVE_ONLY | source https://repowatch.ulni.us-ashburn-1.oci.oraclecloud.com/repowatch/oraclelinux5.x86_64/el5_u5_base/2f5936d4e02b332e8f1672bdb11a23351d7e20fb

Start with B09 for software-only QEMU migration channel hang. Use B06 for KVM dirty-ring livelock after checking nested KVM capability. Use B10 and B11 for a guest-kernel CPU deadlock and fd-release hang. B04 is a migration recovery state-machine hang with a full original reproduction recipe. B03 needs nested SVM and a 2020-vulnerable kernel. B05 is not a 14GiB laptop experiment: the published setup used 256GiB/2 NUMA nodes.
B01 is reported historical corruption with not fully established root cause; do not claim its specific kernel page-table primitive. B02 requires /dev/dax. B07 needs spare VFIO passthrough hardware. B08 needs real vhost-user page faults, not merely KVM running. B12 is recent and unconfirmed root, B13 is archive-only.
EXCLUDED: 2010 VMware balloon PPN_NOTNEEDED patch was called a small optimization by its author, not a liveness failure. Source: https://lkml.iu.edu/1012.0/03016.html
EXCLUDED: 2026 hugetlb migration/punch_hole ABBA deadlock is now CVE-2026-23097, although it was a genuine reliability deadlock; user requested non-security bugs. Source: https://lists.openwall.net/linux-cve-announce/2026/02/04/79
EXCLUDED: KVM gfn-pfncache host use-after-free vulnerability, because primary reports center on host memory corruption and security research, not user-requested nonsecurity correctness bugs.
EXCLUDED: 2011 KVM notifier init ordering was a real race but a minimal reproducer wasn't verified: https://lkml.rescloud.iu.edu/1106.0/01591.html

Mechanism invariant: actor has a reference to resource -> that reference must remain valid until last consumer stops; event transitions must not silently lose ownership or wait for progress from an actor they have blocked.

Workspace files: CASE.txt in each bug folder, ASSIGNMENT-MAP.txt, src/host_preflight.c and Makefile. A successful preflight build says the inventory program compiled, NOT that the bug occurs.
