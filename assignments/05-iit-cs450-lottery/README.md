Illinois Tech CS450 MP2 lottery
Original assignment: https://moss.cs.iit.edu/cs450/mp2-xv6.html
Evidence: official detailed spec inspected
Goal: settickets, getpinfo, child inheritance, 7 instructor tests in private classroom repository
Important limitation: The class's seven tests were in a private course repository; they are NOT included. Local fixtures are original, not replicas of the hidden tests.

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
