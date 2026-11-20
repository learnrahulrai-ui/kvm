Ten deliberately unsolved core decision points for CMU 15-213 Fall 2012 Cache Lab Part A.
These are implementation contracts, not program solutions. Resolve each in the real target codebase.
TODO 01: parse_trace_line — input state → exact condition → output state → regression test
TODO 02: ignore_instruction_fetch — input state → exact condition → output state → regression test
TODO 03: count_modify_as_two — input state → exact condition → output state → regression test
TODO 04: decode_cache_set — input state → exact condition → output state → regression test
TODO 05: decode_cache_tag — input state → exact condition → output state → regression test
TODO 06: detect_hit — input state → exact condition → output state → regression test
TODO 07: detect_miss — input state → exact condition → output state → regression test
TODO 08: choose_lru_victim — input state → exact condition → output state → regression test
TODO 09: count_eviction — input state → exact condition → output state → regression test
TODO 10: format_reference_counters — input state → exact condition → output state → regression test

Independent numeric fixture is three permutations of 4,5,3.
Each column sums to 12. All three rows together sum to 36.
Observe the state transitions in the real kernel/VM before claiming a result.
Question: When does the local observation cease to prove the global invariant?
