Hobart William Smith CPSC331 Spring 2026 lottery
Original assignment: https://math.hws.edu/~bridgeman/courses/331/s26/projects/xv6-scheduling.html~
Evidence: course's archived plaintext handout and linked upstream OSTEP README inspected
Goal: lottery with system calls and ps, schedtest numeric ticket inputs
Important limitation: Course AI policy restricts generated implementation. This folder contains only independent study harness and original TODO prompts, not a generated solution to their submission.

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
