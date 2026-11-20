Ten deliberately unsolved core decision points for JHU CS318 2019 Pintos Project 3 virtual memory.
These are implementation contracts, not program solutions. Resolve each in the real target codebase.
TODO 01: track_supplemental_pages — input state → exact condition → output state → regression test
TODO 02: resolve_lazy_fault — input state → exact condition → output state → regression test
TODO 03: allocate_user_frame — input state → exact condition → output state → regression test
TODO 04: select_eviction_victim — input state → exact condition → output state → regression test
TODO 05: read_accessed_bit — input state → exact condition → output state → regression test
TODO 06: handle_alias_access — input state → exact condition → output state → regression test
TODO 07: write_dirty_victim — input state → exact condition → output state → regression test
TODO 08: reserve_swap_slot — input state → exact condition → output state → regression test
TODO 09: restore_swapped_page — input state → exact condition → output state → regression test
TODO 10: release_page_lifetime — input state → exact condition → output state → regression test

Independent numeric fixture is three permutations of 4096,8192,16384.
Each column sums to 28672. All three rows together sum to 86016.
Observe the state transitions in the real kernel/VM before claiming a result.
Question: When does the local observation cease to prove the global invariant?
