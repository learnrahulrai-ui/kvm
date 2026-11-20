MIT 6.1810 2025 COW fork
Original assignment: https://pdos.csail.mit.edu/6.1810/2025/labs/cow.html
Evidence: official full lab body inspected
Goal: COW fork, readonly shared PTE, per-page refcounts, writes fault
Important limitation: Use the course cow branch. Run cowtest and usertests inside QEMU; host harness only verifies fixture handling.

First run (works without VM):
  make smoke
  # parses 3 independent numeric observations; each column sum = 4099
  make puzzle
  # exits 77, because your 10 logical functions/decisions are not implemented.
Then:
  bash bootstrap.sh
  # downloads allowed original source/handout into the ignored upstream/ directory
Target source paths to inspect:
  kernel/proc.c, kernel/vm.c, kernel/trap.c; user/* tests

Core logical work belongs to student, not this package.
  CHALLENGES.md lists all 10 decisions.
  src/fixture_reader.c contains genuine strict CSV read/overflow checking,
  not an implementation of the university assignment.
  Existing test harnesses and external starter branches remain upstream.
No hosted code, CI/CD, VM provisioning, or cloud operations are necessary to test the local fixture.
Do NOT treat successful smoke test as a real target kernel pass.
