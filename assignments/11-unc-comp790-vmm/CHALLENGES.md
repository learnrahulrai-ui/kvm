Ten deliberately unsolved core decision points for UNC COMP790 Lab 6b JOS paravirtual VMM.
These are implementation contracts, not program solutions. Resolve each in the real target codebase.
TODO 01: check_vmx_capability — input state → exact condition → output state → regression test
TODO 02: create_guest_environment — input state → exact condition → output state → regression test
TODO 03: create_ept_pages — input state → exact condition → output state → regression test
TODO 04: map_guest_gpa — input state → exact condition → output state → regression test
TODO 05: set_vmx_guest_state — input state → exact condition → output state → regression test
TODO 06: launch_guest — input state → exact condition → output state → regression test
TODO 07: resume_guest — input state → exact condition → output state → regression test
TODO 08: decode_vm_exit — input state → exact condition → output state → regression test
TODO 09: dispatch_guest_hypercall — input state → exact condition → output state → regression test
TODO 10: preserve_memory_isolation — input state → exact condition → output state → regression test

Independent numeric fixture is three permutations of 4096,8192,12288.
Each column sums to 24576. All three rows together sum to 73728.
Observe the state transitions in the real kernel/VM before claiming a result.
Question: When does the local observation cease to prove the global invariant?
