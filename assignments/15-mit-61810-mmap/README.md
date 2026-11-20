MIT 6.1810 2025 mmap and munmap
Original assignment: https://pdos.csail.mit.edu/6.1810/2025/labs/mmap.html
Evidence: official full lab body and test description inspected
Goal: lazy mmap, MAP_SHARED file write-back, unmap and fork lifetimes
Important limitation: The baseline allows distinct physical pages for two MAP_SHARED file mappings. Physical sharing is an optional extension.

First run (works without VM):
  make smoke
  # parses 3 independent numeric observations; each column sum = 28672
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
