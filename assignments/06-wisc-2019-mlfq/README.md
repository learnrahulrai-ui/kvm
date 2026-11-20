UW Madison CS537 2019 MLFQ
Original assignment: https://pages.cs.wisc.edu/~shivaram/cs537-sp19/p2b.html
Evidence: official full handout inspected
Goal: 4 queue levels, queue 0 FIFO, top levels round robin, 1 CPU
Important limitation: This is an alternative scheduler, not Waldspurger's proportional-share algorithm. Use it as a counterexample to resource-allocation guarantees.

First run (works without VM):
  make smoke
  # parses 3 independent numeric observations; each column sum = 6
  make puzzle
  # exits 77, because your 10 logical functions/decisions are not implemented.
Then:
  bash bootstrap.sh
  # downloads allowed original source/handout into the ignored upstream/ directory
Target source paths to inspect:
  proc.c, proc.h, trap.c, syscall.c, sysproc.c; pstat.h

Core logical work belongs to student, not this package.
  CHALLENGES.md lists all 10 decisions.
  src/fixture_reader.c contains genuine strict CSV read/overflow checking,
  not an implementation of the university assignment.
  Existing test harnesses and external starter branches remain upstream.
No hosted code, CI/CD, VM provisioning, or cloud operations are necessary to test the local fixture.
Do NOT treat successful smoke test as a real target kernel pass.
