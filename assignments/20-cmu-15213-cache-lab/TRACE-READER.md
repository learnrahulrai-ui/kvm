Actual trace format parser in src/trace_reader.c (not an LRU simulator).
For the eight example records, I=1 is ignored, data records=7, effective data references=9.
The two M records represent four references (read followed by write).
Hard part reserved: set lookup and eviction must produce hits=4, misses=5, evictions=3 for this trace when -s 4 -E 1 -b 4, matching the original CMU PDF example (the instruction fetch was added only for the parser smoke).
Run make trace to check input parsing, not LRU correctness.
Verified strict C compilation and output on a Linux sandbox.
