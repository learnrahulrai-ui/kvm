JHU CS318 2019 Pintos Project 3 virtual memory
Original assignment: https://web.eecs.umich.edu/~ryanph/jhu/cs318/fall19/project/project3.html
Evidence: official archived full technical spec inspected, including frame/accessed/dirty alias warning
Goal: supplemental table, frame and swap allocation, eviction, mmap
Important limitation: Lab 3 builds on Lab 2; an isolated starter is insufficient for grading without the prerequisite Pintos code.

First run (works without VM):
  make smoke
  # parses 3 independent numeric observations; each column sum = 28672
  make puzzle
  # exits 77, because your 10 logical functions/decisions are not implemented.
Then:
  bash bootstrap.sh
  # downloads allowed original source/handout into the ignored upstream/ directory
Target source paths to inspect:
  vm/, userprog/, devices/block.c, userprog/pagedir.c

Core logical work belongs to student, not this package.
  CHALLENGES.md lists all 10 decisions.
  src/fixture_reader.c contains genuine strict CSV read/overflow checking,
  not an implementation of the university assignment.
  Existing test harnesses and external starter branches remain upstream.
No hosted code, CI/CD, VM provisioning, or cloud operations are necessary to test the local fixture.
Do NOT treat successful smoke test as a real target kernel pass.
