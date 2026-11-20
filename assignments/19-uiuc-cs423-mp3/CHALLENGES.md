Ten deliberately unsolved core decision points for UIUC CS423 Spring 2021 MP3 page fault profiler.
These are implementation contracts, not program solutions. Resolve each in the real target codebase.
TODO 01: parse_registration_protocol — input state → exact condition → output state → regression test
TODO 02: validate_pid_lifetime — input state → exact condition → output state → regression test
TODO 03: track_task_struct — input state → exact condition → output state → regression test
TODO 04: schedule_sampling_work — input state → exact condition → output state → regression test
TODO 05: read_minor_faults — input state → exact condition → output state → regression test
TODO 06: read_major_faults — input state → exact condition → output state → regression test
TODO 07: read_cpu_runtime — input state → exact condition → output state → regression test
TODO 08: append_to_vmalloc_ring — input state → exact condition → output state → regression test
TODO 09: expose_character_device_mmap — input state → exact condition → output state → regression test
TODO 10: teardown_concurrently — input state → exact condition → output state → regression test

Independent numeric fixture is three permutations of 20,100,128.
Each column sums to 248. All three rows together sum to 744.
Observe the state transitions in the real kernel/VM before claiming a result.
Question: When does the local observation cease to prove the global invariant?
