NONTRIVIAL KVM / LINUX / QEMU CORRECTNESS AND LIVENESS BUG REPRODUCTION INDEX
Recorded on: 2026-11-21. Expanded with pre-2015 cases on 2026-11-21. Last 20-year research sample, NOT every bug anyone encountered.
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

Start with B09 or B14 for software-only QEMU migration hangs. B16 is AMD SVM-specific and has an unusually strong reviewer correction trail; B15 requires Intel PML and is not a Ryzen laptop reproduction. Start with B09 for software-only QEMU migration channel hang. Use B06 for KVM dirty-ring livelock after checking nested KVM capability. Use B10 and B11 for a guest-kernel CPU deadlock and fd-release hang. B04 is a migration recovery state-machine hang with a full original reproduction recipe. B03 needs nested SVM and a 2020-vulnerable kernel. B05 is not a 14GiB laptop experiment: the published setup used 256GiB/2 NUMA nodes.
B01 is reported historical corruption with not fully established root cause; do not claim its specific kernel page-table primitive. B02 requires /dev/dax. B07 needs spare VFIO passthrough hardware. B08 needs real vhost-user page faults, not merely KVM running. B12 is recent and unconfirmed root, B13 is archive-only.
B14 14-2019-qemu-multifd-cancel-semaphore-hang | CONFIRMED_MERGED_FIX_NO_MINIMAL_SCRIPT_IN_SOURCE | GOOD_SOFTWARE_ONLY_VERSION_PINNED_QEMU | source https://patchew.org/QEMU/20190725105724.2562-1-quintela@redhat.com/
B15 15-2019-nested-pml-incorrect-address-space | CONFIRMED_KVM_PATCH_WITH_REGRESSION_TEST | REQUIRES_INTEL_VMX_PML_NOT_AMD_RYZEN | source https://lists.openwall.net/linux-kernel/2019/09/26/690
B16 16-2021-kvm-nsvm-nested-pending-state-lost | CONFIRMED_AUTHOR_REPRO_REVIEW_CORRECTED_HYPOTHESIS | MODERATE_NESTED_AMD_SVM_WITH_VERSION_PINNED_L0 | source https://lists.openwall.net/linux-kernel/2021/01/07/367
EXCLUDED: 2010 VMware balloon PPN_NOTNEEDED patch was called a small optimization by its author, not a liveness failure. Source: https://lkml.iu.edu/1012.0/03016.html
EXCLUDED: 2026 hugetlb migration/punch_hole ABBA deadlock is now CVE-2026-23097, although it was a genuine reliability deadlock; user requested non-security bugs. Source: https://lists.openwall.net/linux-cve-announce/2026/02/04/79
EXCLUDED: KVM gfn-pfncache host use-after-free vulnerability, because primary reports center on host memory corruption and security research, not user-requested nonsecurity correctness bugs.
EXCLUDED: 2011 KVM notifier init ordering was a real race but a minimal reproducer wasn't verified: https://lkml.rescloud.iu.edu/1106.0/01591.html

Mechanism invariant: actor has a reference to resource -> that reference must remain valid until last consumer stops; event transitions must not silently lose ownership or wait for progress from an actor they have blocked.

Workspace files: CASE.txt in each bug folder, ASSIGNMENT-MAP.txt, src/host_preflight.c and Makefile. A successful preflight build says the inventory program compiled, NOT that the bug occurs.

IMPORTANT HISTORICAL SOURCE CONTRADICTION
2021 B16: The initial author attributed the missing L2 interrupt to unsaved event injection. The reviewer observed that the event was already in the migrated VMCB. The author agreed and corrected the missing restored KVM_STATE_NESTED_RUN_PENDING state flag in v2. Never cite the first patch as the final cause.
2017 notifier release race discussions contain a direct objection that SRCU synchronization may already prevent the claimed use-after-free; not accepted as independently reproduced without resolving the objection. See https://lkml.iu.edu/1704.3/01856.html
2024 KVM CMPXCHG dirty-log regression causes real migration data corruption but is classified as CVE-2024-35804, hence not included under user's non-security filter. Kernel primary https://lists.openwall.net/linux-kernel/2024/04/04/1512 ; security classification https://nvd.nist.gov/vuln/detail/CVE-2024-35804
2023 KVM mmu_seq sign-extension bug needs approximately 2^31 invalidations to appear; exact bug confirmed but poor laptop reproduction candidate and disfavored by user's focus on deeper causal bugs. Source https://lkml.iu.edu/2308.2/08685.html

PRE-2015 CASES (B17-B28), ALL HISTORICAL, NOT EXECUTED ON USER'S LAPTOP:
B17 | 2008 | KVM SMP shadow table caches a guest PTE that a sibling has replaced | HISTORICAL_REPRO_HARD | https://lkml.rescloud.iu.edu/hypermail/linux/kernel/0801.0/0114.html
B18 | 2008 | Prefetch before write-protection leaves a guest page permanently not-present in shadow | GOOD_ORIGINAL_REPRO_OLD_KERNEL | https://sourceforge.net/p/kvm/mailman/message/19067975/
B19 | 2009 | virtio_net completed transmit queue can remain stopped with no pending work | GOOD_GUEST_KERNEL_EXERCISE | https://bugzilla.redhat.com/show_bug.cgi?id=524651
B20 | 2010 | KVM dirty/write-protect state permits old guest memory after live migration | ORIGINAL_REPRO_NEEDS_OLD_INTEL_NON_EPT | https://bugzilla.redhat.com/show_bug.cgi?id=647367
B21 | 2010 | Live migration loses guest changes made by vhost-net after final dirty-page scan | GOOD_WITH_OLD_QEMU_AND_GUEST | https://bugzilla.redhat.com/show_bug.cgi?id=623552
B22 | 2011 | Wrong address conversion in vhost migration dirty tracking segfaults QEMU | ORIGINAL_GDB_RECIPE_OLD_DISTRO | https://bugzilla.redhat.com/show_bug.cgi?id=684076
B23 | 2011 | Pausing a KVM guest creates a false soft-lockup diagnosis and breaks naive clock corrections | GOOD_SAFE_GUEST_EXPERIMENT | https://lkml.iu.edu/1111.3/02146.html
B24 | 2012 | QEMU zero-page optimization discards neighboring guest bytes if host page is larger | NO_RYZEN_REPRO_HARDWARE | https://github.com/qemu/qemu/commit/f1a2195ec327fd2b837a3539623ee431d133f03c
B25 | 2013 | QEMU skips a source zero page whose destination still contains firmware bytes | GOOD_SOFTWARE_ONLY_OLD_QEMU | https://github.com/qemu/qemu/commit/f1c72795af573b24a7da5eb52375c9aba8a37972
B26 | 2013 | QEMU aio_poll treats no immediate progress as no pending I/O | GOOD_SOFTWARE_ONLY_CONDITIONAL | https://github.com/qemu/qemu/commit/2ea9b58f0bc62445b7ace2381b4c4db7d5597e19
B27 | 2013 | KVM VMX invalid-state emulation fails to clear pending halt and later hangs guest | INTEL_ONLY_OLD_KERNEL | https://lkml.iu.edu/1306.0/01022.html
B28 | 2014 | Linux NUMA scan performs expensive KVM MMU invalidations over holes in huge guest memory | HUGE_VM_ONLY | https://lkml.iu.edu/hypermail/linux/kernel/1402.2/01745.html

PRIORITY FOR NON-SECURITY INTERVIEW REPRODUCTION:
B19 (TX wakeup; guest kernel), B23 (false watchdog warning on host pause), B25 (source/destination state divergence on zero-page skip), B26 (AIO drain waits for real work), B18 (authentic dmsetup-status SMP guest spin, but requires ancient shadow MMU), B20/B21 (dirty logging during migration). B24 and B28 require hardware/memory unavailable to an ordinary Ryzen laptop. B27 requires Intel VMX rather than AMD SVM.
Do NOT use modern QEMU/kernel without source pinning and claim a historical bug. Some historical versions require an older build toolchain and nested virtualization that a laptop may not expose. Historical source check and negative control must precede reproduction claims.
The two 2008 KVM shadow MMU bugs are distinct: B17 caches an entry across a sibling update and must validate it; B18 runs prefetch before protection and must establish protection before prefetch. The 2010 vhost bugs are distinct: B20 violates dirty-vs-write-protection in KVM, B21 loses late vhost dirties across QEMU final transfer, B22 uses the wrong address conversion in a QEMU dirty sync.
