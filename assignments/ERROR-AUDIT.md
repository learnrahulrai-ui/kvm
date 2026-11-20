# Errors found and corrected while preparing these assignments

This documents assistant-generated errors, not errors attributed to the user. Entries describe a wrong causal assumption, a falsifying check, and the correction. Source code and measurements are separate from opinion.

01. Earlier assignment/README described 22 projects after one common src/fixture_reader.c compiled → FALSE PROOF; successful compilation of one arithmetic parser does not validate any university kernel mechanism → src/logic_drill.c now leaves ten tasks per folder incomplete and make check reports failure.
02. Earlier MIT lab scripts cloned mit-pdos/xv6-riscv and requested origin/cow, origin/mmap, origin/pgtbl → WRONG SOURCE; the lab branches belong to the official xv6-labs-2025 course source → bootstrap.sh in folders 14/15/16 now uses the course's declared repository instead.
03. First COW drill asked 'increment_shared_page_refcount' using 100 plus 7 → WRONG CAUSAL EVENT; one additional reference increases count by one → corrected tests use 1→2 and 4→5 in folder 14.
04. First COW drill labeled a minimum operation as refcount release → WRONG; refcount release is not a minimum-of-two comparison → renamed decrement_refcount_on_release and corrected test values.
05. First Pintos drill equated clock eviction with choosing the lowest number → WRONG; the scan follows a pointer and the referenced states of frames → narrowed to first_unreferenced_from_clock_hand, with explicit accessed bits and initial hand.
06. First cache drill added three integers to represent total cache lines → WRONG DOMAIN; set count and associativity determine line capacity → corrected tests 64 × 4 = 256 and 16 × 8 = 128 (the function remains a blank).
07. A global interpretation of all six position arguments in each exercise was introduced → WRONG SCOPE; different logical steps use the same positions for different meanings → all 22 FILL_BLANKS files now name the input operands per operation.
08. Runtime KVM path assumed when seeing a successful compiler → WRONG; the GitHub runner has no demonstrated guest KVM execution → build tests cover syntax and userspace fixtures, not KVM_RUN.
09. Claim that module can always be built at -O0 -> FALSE; Kbuild against 6.12.107 Debian headers failed when KCFLAGS=-O0 -g3 was forced by an inline-assembly restriction. Using the normal kernel optimization and KCFLAGS=-g3 produced the module with debug info. No student algorithm was implicated.
10. Kernel version 6.14.0-37-generic was supplied as a desired environment → NOT OBSERVED on the machine used for test; actual module test headers were /usr/src/linux-headers-6.12.107+deb13-amd64, and the environment's running kernel was different. Do not call these the user's laptop values.
11. Statements about all source branches, private starter files, and user academic grades → NOT MEASURED. These require the actual original source distribution and tests.
12. No Cargo.toml is tracked → no Cargo crates exist in the present 22 C workspaces; asking to pass cargo test would manufacture a Rust package or a test result.
13. Several isolated C logic tests use constructed values → they are not production latencies, physical page addresses, guest state, or measurements of Nutanix AHV.
14. ASCII 3D drawings in MCQ_PROOF.txt are not photographic images → do not describe them as genuine 3D rendered photographs. The requested image asset set has not been committed.
15. The university assignment source is external and is not replaced by the local numerical drills. A full claim of 'workable' requires confirming that the original starter can be fetched, built, and graded in its target environment.

New inference audit: numeric examples are marked constructed; kernel file names are source-specific; completed tests are not inferred from compilation. Every factual machine measurement names the machine used.
