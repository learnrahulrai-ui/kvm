Ten deliberately unsolved core decision points for UNC COMP790 2017 AMD SVM final project.
These are implementation contracts, not program solutions. Resolve each in the real target codebase.
TODO 01: detect_svm_support — input state → exact condition → output state → regression test
TODO 02: enable_svm_in_guest — input state → exact condition → output state → regression test
TODO 03: allocate_vmcb — input state → exact condition → output state → regression test
TODO 04: configure_guest_registers — input state → exact condition → output state → regression test
TODO 05: configure_nested_page_tables — input state → exact condition → output state → regression test
TODO 06: set_intercept_bitmap — input state → exact condition → output state → regression test
TODO 07: execute_vmrun — input state → exact condition → output state → regression test
TODO 08: decode_exit_code — input state → exact condition → output state → regression test
TODO 09: inject_virtual_interrupt — input state → exact condition → output state → regression test
TODO 10: test_guest_reentry — input state → exact condition → output state → regression test

Independent numeric fixture is three permutations of 4096,8192,1.
Each column sums to 12289. All three rows together sum to 36867.
Observe the state transitions in the real kernel/VM before claiming a result.
Question: When does the local observation cease to prove the global invariant?
