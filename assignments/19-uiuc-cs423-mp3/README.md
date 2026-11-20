UIUC CS423 Spring 2021 MP3 page fault profiler
Original assignment: https://courses.grainger.illinois.edu/cs423/sp2021/mp/mp3/index.html
Evidence: official full implementation description and private starter conditions inspected
Goal: proc registration, task collection, work queue sampler, vmalloc plus mmap buffer
Important limitation: School-provided mp3_given.h was private. This repo will not invent it or claim the module is ready for a running host kernel.

First run (works without VM):
  make smoke
  # parses 3 independent numeric observations; each column sum = 248
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
