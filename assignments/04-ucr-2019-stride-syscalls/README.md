UCR CS202 2019 Lab 1 syscalls and stride
Original assignment: https://www.cs.ucr.edu/~nael/cs202/labs/lab1.html
Evidence: official complete 2019 assignment body read
Goal: info syscall with three modes plus lottery and stride policies
Important limitation: This 2019 assignment is distinct from the later UCR 2024 Lab 2.

First run (works without VM):
  make smoke
  # parses 3 independent numeric observations; each column sum = 60
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
