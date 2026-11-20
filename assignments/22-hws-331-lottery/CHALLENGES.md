Ten deliberately unsolved core decision points for Hobart William Smith CPSC331 Spring 2026 lottery.
These are implementation contracts, not program solutions. Resolve each in the real target codebase.
TODO 01: validate_ticket_syscall — input state → exact condition → output state → regression test
TODO 02: initialize_ticket_count — input state → exact condition → output state → regression test
TODO 03: inherit_ticket_count — input state → exact condition → output state → regression test
TODO 04: count_runnable_total — input state → exact condition → output state → regression test
TODO 05: draw_lottery — input state → exact condition → output state → regression test
TODO 06: select_winner — input state → exact condition → output state → regression test
TODO 07: increment_sched_ticks — input state → exact condition → output state → regression test
TODO 08: return_pstat — input state → exact condition → output state → regression test
TODO 09: build_ps_utility — input state → exact condition → output state → regression test
TODO 10: verify_schedtest_output — input state → exact condition → output state → regression test

Independent numeric fixture is three permutations of 30,20,10.
Each column sums to 60. All three rows together sum to 180.
Observe the state transitions in the real kernel/VM before claiming a result.
Question: When does the local observation cease to prove the global invariant?
