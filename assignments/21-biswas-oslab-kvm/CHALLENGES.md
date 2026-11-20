Ten deliberately unsolved core decision points for Soumadip Biswas OS Lab capstone project 18 KVM.
These are implementation contracts, not program solutions. Resolve each in the real target codebase.
TODO 01: load_16bit_guest_image — input state → exact condition → output state → regression test
TODO 02: check_kvm_api — input state → exact condition → output state → regression test
TODO 03: create_vm — input state → exact condition → output state → regression test
TODO 04: map_guest_memory — input state → exact condition → output state → regression test
TODO 05: create_vcpu — input state → exact condition → output state → regression test
TODO 06: initialize_real_mode — input state → exact condition → output state → regression test
TODO 07: run_vcpu — input state → exact condition → output state → regression test
TODO 08: decode_io_exit — input state → exact condition → output state → regression test
TODO 09: emulate_guest_output — input state → exact condition → output state → regression test
TODO 10: validate_hlt_or_shutdown — input state → exact condition → output state → regression test

Independent numeric fixture is three permutations of 16,4096,1.
Each column sums to 4113. All three rows together sum to 12339.
Observe the state transitions in the real kernel/VM before claiming a result.
Question: When does the local observation cease to prove the global invariant?
