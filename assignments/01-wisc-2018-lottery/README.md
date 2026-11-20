UW Madison CS537 Spring 2018 P2b lottery
Original assignment: https://pages.cs.wisc.edu/~remzi/Classes/537/Spring2018/Projects/p2b.html
Evidence: official handin page and referenced instructor project README inspected
Goal: xv6 scheduler, settickets, getpinfo, fork inheritance, graph for 30:20:10
Important limitation: The lecturer's 2018 handin links a fuller instructor README. The generic xv6-public checkout is a substitute, not the exact CS537 2018 class tarball.

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
