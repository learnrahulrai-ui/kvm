# Waldspurger research laboratory — executable KVM/ESX/SHARDS work

The target is one Linux development laptop with KVM and QEMU already installed. A disposable pair of guests is used for KSM, ballooning, dirty-page tracking and migration work. The host is never assumed to run an old vulnerable kernel.

START:
```bash
git clone https://github.com/learnrahulrai-ui/kvm.git
cd kvm/waldspurger-lab
make CC=gcc check
make preflight
```

The test results establish only four working standalone C baselines and their debug symbols. A successful program build does NOT show that an ESX 2002 implementation, Nutanix deployment, KVM guest, or historical bug was reproduced.

For the full experiment order open [RUNBOOK.txt](RUNBOOK.txt). Read the matching [experiments](experiments) directory before running each step. The project keeps source references in [SOURCES.txt](SOURCES.txt), KVM bug links in [BUG-BRIDGE.txt](BUG-BRIDGE.txt), and a reproducible result template in [REPORT-TEMPLATE.txt](REPORT-TEMPLATE.txt).

The single core progression is:

guest instruction → KVM_RUN → guest physical / host virtual translation → host memory backing → KSM sharing → COW write → balloon reclaim → cache misses → CPU charge → memory migration.

The papers and implemented components are deliberately separated:

| Paper / mechanism | Implemented now | Still student work |
|---|---|---|
| 1994 lottery scheduling and 1995 stride scheduling | Deterministic C simulation with real ticket inputs | Sleep compensation, kernel runnable sets, xv6 scheduler, original tests |
| ESX 2002 share-based memory allocation | Exact idle-tax arithmetic calculator | Actual host allocation policy and guest activity estimator |
| ESX 2002 content sharing | Linux anonymous mergeable pages and controlled two-VM RAM backing | Reverse mappings, write-protection and KSM lifetime trace |
| ESX 2002 ballooning | Two virtual machines with virtio balloon and bounded QMP requests | Memory-pressure feedback controller and guest reclaim traces |
| SHARDS FAST 2015 | Exact LRU reuse-distance curve, fixed-rate hash-selected approximation | Correct adaptive bounded-sample state, efficient distance tree, original multi-trace evaluation |
| 2024 Memstrata | Source and experiment design | Requires hardware-managed CXL tier or separately justified simulation |
| ProfileMe 1997 | Source and perf comparison plan | Original hardware cannot be reconstructed by a modern laptop alone |
| KVM/QEMU 2008–2026 bugs | Version-pinned source studies mapped to the 22 course folders | Actual isolated repro and pre-/post-patch measurements |

The C demonstration and the two QEMU guests can run on a Ryzen laptop with roughly 14 GiB RAM. Actual requirements are determined by `scripts/preflight.sh`. The default QEMU configuration asks for 768 MiB each, or 1,536 MiB total configured guest memory, and requires at least 4 GiB of host MemAvailable before starting.

Do not execute a historic vulnerable kernel on the laptop's regular boot installation. KSM settings are host-wide. This repository does not automatically enable them. Historical QEMU and KVM reproduction instructions are optional, require snapshots, and must be tested in disposable nested virtual machines.

Commands worth learning:
```bash
make check
./build/idle_tax 100 100 0.25 50 50 0.75 0.75
./build/scheduler stride 6 100 50
./build/scheduler lottery 6000 100 50
./build/mrc traces/six-blocks.txt 1000
./build/mrc traces/six-blocks.txt 500
./build/ksm_demo 32 1 45
bash scripts/observe_ksm.sh 30 2
```

The full original material remains linked, not copied into the repository. Research cases are indexed in [../bugs](../bugs); the original university laboratories remain in [../assignments](../assignments).

Every actual experiment has a `measured_` record and a `source_` record. Never write a guessed address, benchmark, guest exit count, or kernel version as though it was measured on the user's machine.
