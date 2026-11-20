Ten deliberately unsolved core decision points for IIT Bombay CS695 2023 A3 Hello KVM.
These are implementation contracts, not program solutions. Resolve each in the real target codebase.
TODO 01: inspect_supplied_archive — input state → exact condition → output state → regression test
TODO 02: discover_entry_point — input state → exact condition → output state → regression test
TODO 03: map_kvm_capabilities — input state → exact condition → output state → regression test
TODO 04: allocate_guest_ram — input state → exact condition → output state → regression test
TODO 05: create_vm_fd — input state → exact condition → output state → regression test
TODO 06: create_vcpu_fd — input state → exact condition → output state → regression test
TODO 07: initialize_guest_registers — input state → exact condition → output state → regression test
TODO 08: handle_guest_exit — input state → exact condition → output state → regression test
TODO 09: observe_guest_memory_effects — input state → exact condition → output state → regression test
TODO 10: write_evidence_for_viva — input state → exact condition → output state → regression test

Independent numeric fixture is three permutations of 4096,2097152,1.
Each column sums to 2101249. All three rows together sum to 6303747.
Observe the state transitions in the real kernel/VM before claiming a result.
Question: When does the local observation cease to prove the global invariant?
