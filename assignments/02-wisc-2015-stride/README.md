UW Madison CS537 2015 P2b stride
Original assignment: https://pages.cs.wisc.edu/~kzhao32/projects/cs537p2b_xv6Scheduler.pdf
Evidence: archived assignment PDF inspected (student-hosted copy)
Goal: minimum pass selection, quantum accounting, getpinfo, overflow, 2 CPU issue
Important limitation: PDF permits the simplification of a full 10 ms charge even when a process yields after 2 ms. Advanced extension must separately record partial-runtime error.

First run (works without VM):
  make smoke
  # parses 3 independent numeric observations; each column sum = 600
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
