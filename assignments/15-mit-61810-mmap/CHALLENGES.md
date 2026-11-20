Ten deliberately unsolved core decision points for MIT 6.1810 2025 mmap and munmap.
These are implementation contracts, not program solutions. Resolve each in the real target codebase.
TODO 01: validate_mmap_args — input state → exact condition → output state → regression test
TODO 02: reserve_virtual_region — input state → exact condition → output state → regression test
TODO 03: track_file_lifetime — input state → exact condition → output state → regression test
TODO 04: fault_in_page_lazily — input state → exact condition → output state → regression test
TODO 05: apply_pte_permissions — input state → exact condition → output state → regression test
TODO 06: differentiate_shared_private — input state → exact condition → output state → regression test
TODO 07: writeback_dirty_shared — input state → exact condition → output state → regression test
TODO 08: split_edge_unmap — input state → exact condition → output state → regression test
TODO 09: inherit_vma_on_fork — input state → exact condition → output state → regression test
TODO 10: cleanup_on_exit — input state → exact condition → output state → regression test

Independent numeric fixture is three permutations of 4096,8192,16384.
Each column sums to 28672. All three rows together sum to 86016.
Observe the state transitions in the real kernel/VM before claiming a result.
Question: When does the local observation cease to prove the global invariant?
