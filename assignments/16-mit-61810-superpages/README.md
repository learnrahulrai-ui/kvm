MIT 6.1810 2025 page tables and superpages
Original assignment: https://pdos.csail.mit.edu/6.1810/2025/labs/pgtbl.html
Evidence: official complete lab body inspected
Goal: read-only getpid mapping, recursive PTE print, 2 MiB superpage allocations
Important limitation: This directly exercises the large-page versus 4KiB page sharing tension. Extra extensions must remain separate from official grading.

First run (works without VM):
  make smoke
  # parses 3 independent numeric observations; each column sum = 2101760
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
