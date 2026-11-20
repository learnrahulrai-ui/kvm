Ten deliberately unsolved core decision points for MIT 6.1810 2025 page tables and superpages.
These are implementation contracts, not program solutions. Resolve each in the real target codebase.
TODO 01: map_readonly_usyscall — input state → exact condition → output state → regression test
TODO 02: initialize_shared_pid_data — input state → exact condition → output state → regression test
TODO 03: print_page_tables — input state → exact condition → output state → regression test
TODO 04: reserve_2m_pool — input state → exact condition → output state → regression test
TODO 05: allocate_aligned_superpage — input state → exact condition → output state → regression test
TODO 06: install_superpage_pte — input state → exact condition → output state → regression test
TODO 07: copy_superpages_on_fork — input state → exact condition → output state → regression test
TODO 08: free_superpages — input state → exact condition → output state → regression test
TODO 09: demote_partial_superpage — input state → exact condition → output state → regression test
TODO 10: ensure_tlb_consistency — input state → exact condition → output state → regression test

Independent numeric fixture is three permutations of 4096,2097152,512.
Each column sums to 2101760. All three rows together sum to 6305280.
Observe the state transitions in the real kernel/VM before claiming a result.
Question: When does the local observation cease to prove the global invariant?
