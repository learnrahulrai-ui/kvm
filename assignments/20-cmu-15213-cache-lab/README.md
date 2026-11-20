CMU 15-213 Fall 2012 Cache Lab Part A
Original assignment: https://csapp.cs.cmu.edu/2e/cachelab.pdf
Evidence: official 10-page PDF inspected including p3 reference example
Goal: trace driven set-associative LRU cache simulator, exact hits/misses/evictions
Important limitation: Official csim-ref program and course handout are not redistributed. Later SHARDS exploration is self-assigned, not CMU's syllabus.

First run (works without VM):
  make smoke
  # parses 3 independent numeric observations; each column sum = 12
  make puzzle
  # exits 77, because your 10 logical functions/decisions are not implemented.
Then:
  bash bootstrap.sh
  # downloads allowed original source/handout into the ignored upstream/ directory
Target source paths to inspect:
  kernel module or host C program, course tests, syscall boundary

Core logical work belongs to student, not this package.
  CHALLENGES.md lists all 10 decisions.
  src/fixture_reader.c contains genuine strict CSV read/overflow checking,
  not an implementation of the university assignment.
  Existing test harnesses and external starter branches remain upstream.
No hosted code, CI/CD, VM provisioning, or cloud operations are necessary to test the local fixture.
Do NOT treat successful smoke test as a real target kernel pass.
