Ten deliberately unsolved core decision points for Georgia Tech CS6210 vCPU scheduler and memory coordinator.
These are implementation contracts, not program solutions. Resolve each in the real target codebase.
TODO 01: enumerate_domains — input state → exact condition → output state → regression test
TODO 02: sample_vcpu_cpu_time — input state → exact condition → output state → regression test
TODO 03: sample_pcpu_utilization — input state → exact condition → output state → regression test
TODO 04: choose_vcpu_migration — input state → exact condition → output state → regression test
TODO 05: respect_vcpu_pinning — input state → exact condition → output state → regression test
TODO 06: read_guest_memory_stats — input state → exact condition → output state → regression test
TODO 07: detect_host_pressure — input state → exact condition → output state → regression test
TODO 08: choose_memory_donor — input state → exact condition → output state → regression test
TODO 09: limit_balloon_target — input state → exact condition → output state → regression test
TODO 10: prove_migration_improves_load — input state → exact condition → output state → regression test

Independent numeric fixture is three permutations of 25,75,50.
Each column sums to 150. All three rows together sum to 450.
Observe the state transitions in the real kernel/VM before claiming a result.
Question: When does the local observation cease to prove the global invariant?
