Ten deliberately unsolved core decision points for UMich EECS482 external pager archived.
These are implementation contracts, not program solutions. Resolve each in the real target codebase.
TODO 01: register_address_space — input state → exact condition → output state → regression test
TODO 02: track_virtual_page — input state → exact condition → output state → regression test
TODO 03: simulate_reference_fault — input state → exact condition → output state → regression test
TODO 04: simulate_write_fault — input state → exact condition → output state → regression test
TODO 05: choose_clock_hand — input state → exact condition → output state → regression test
TODO 06: clear_reference_protection — input state → exact condition → output state → regression test
TODO 07: evict_shared_frame — input state → exact condition → output state → regression test
TODO 08: write_dirty_to_disk — input state → exact condition → output state → regression test
TODO 09: restore_on_fault — input state → exact condition → output state → regression test
TODO 10: teardown_shared_mapping — input state → exact condition → output state → regression test

Independent numeric fixture is three permutations of 4096,8192,16384.
Each column sums to 28672. All three rows together sum to 86016.
Observe the state transitions in the real kernel/VM before claiming a result.
Question: When does the local observation cease to prove the global invariant?
