Ten deliberately unsolved core decision points for MIT 6.1810 2025 COW fork.
These are implementation contracts, not program solutions. Resolve each in the real target codebase.
TODO 01: mark_pte_cow — input state → exact condition → output state → regression test
TODO 02: share_on_fork — input state → exact condition → output state → regression test
TODO 03: increment_page_ref — input state → exact condition → output state → regression test
TODO 04: detect_store_fault — input state → exact condition → output state → regression test
TODO 05: distinguish_cow_from_readonly — input state → exact condition → output state → regression test
TODO 06: allocate_private_copy — input state → exact condition → output state → regression test
TODO 07: remap_faulting_pte — input state → exact condition → output state → regression test
TODO 08: decrement_page_ref — input state → exact condition → output state → regression test
TODO 09: handle_copyout_to_cow — input state → exact condition → output state → regression test
TODO 10: free_on_last_reference — input state → exact condition → output state → regression test

Independent numeric fixture is three permutations of 1,2,4096.
Each column sums to 4099. All three rows together sum to 12297.
Observe the state transitions in the real kernel/VM before claiming a result.
Question: When does the local observation cease to prove the global invariant?
