Ten deliberately unsolved core decision points for IIT Bombay CS695 PA1 KVM Hello World.
These are implementation contracts, not program solutions. Resolve each in the real target codebase.
TODO 01: map_guest_hpa — input state → exact condition → output state → regression test
TODO 02: install_memory_slot — input state → exact condition → output state → regression test
TODO 03: construct_guest_page_tables — input state → exact condition → output state → regression test
TODO 04: set_guest_cpu_state — input state → exact condition → output state → regression test
TODO 05: route_io_exit — input state → exact condition → output state → regression test
TODO 06: validate_hypercall_arguments — input state → exact condition → output state → regression test
TODO 07: dispatch_display_hypercall — input state → exact condition → output state → regression test
TODO 08: dispatch_file_hypercall — input state → exact condition → output state → regression test
TODO 09: resume_after_exit — input state → exact condition → output state → regression test
TODO 10: preserve_guest_host_isolation — input state → exact condition → output state → regression test

Independent numeric fixture is three permutations of 4096,2097152,5.
Each column sums to 2101253. All three rows together sum to 6303759.
Observe the state transitions in the real kernel/VM before claiming a result.
Question: When does the local observation cease to prove the global invariant?
