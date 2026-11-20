Ten deliberately unsolved core decision points for UT Austin CS360V 2021 Project 1 JOS VMM.
These are implementation contracts, not program solutions. Resolve each in the real target codebase.
TODO 01: identify_lab_baseline — input state → exact condition → output state → regression test
TODO 02: map_guest_code — input state → exact condition → output state → regression test
TODO 03: create_guest_pagetable — input state → exact condition → output state → regression test
TODO 04: create_ept — input state → exact condition → output state → regression test
TODO 05: configure_vmx_control — input state → exact condition → output state → regression test
TODO 06: enter_guest — input state → exact condition → output state → regression test
TODO 07: handle_cpuid — input state → exact condition → output state → regression test
TODO 08: dispatch_hypercall — input state → exact condition → output state → regression test
TODO 09: implement_disk_access — input state → exact condition → output state → regression test
TODO 10: restart_after_exit — input state → exact condition → output state → regression test

Independent numeric fixture is three permutations of 4096,8192,12288.
Each column sums to 24576. All three rows together sum to 73728.
Observe the state transitions in the real kernel/VM before claiming a result.
Question: When does the local observation cease to prove the global invariant?
