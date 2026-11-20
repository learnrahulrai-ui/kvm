UMich EECS482 external pager archived
Original assignment: http://williamwjs.github.io/assets/482_Project_3.html
Evidence: archived student-hosted handout from earlier collection; not revalidated here
Goal: external pager, software reference bits, clock eviction and shared frame ownership
Important limitation: Version and instructor distribution unverified. No course-provided test binaries copied.

First run (works without VM):
  make smoke
  # parses 3 independent numeric observations; each column sum = 28672
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
