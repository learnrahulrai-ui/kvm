UNC COMP790 2017 AMD SVM final project
Original assignment: https://www.cs.unc.edu/~porter/courses/comp790/s17/lab5.html
Evidence: official final-project options inspected
Goal: port JOS VMM from Intel VMX to AMD SVM; open-ended, instructor approval required
Important limitation: This is an open-ended suggested project, not an instructor-provided ten-step graded lab. Requires supporting environment before bare-metal test.

First run (works without VM):
  make smoke
  # parses 3 independent numeric observations; each column sum = 12289
  make puzzle
  # exits 77, because your 10 logical functions/decisions are not implemented.
Then:
  bash bootstrap.sh
  # downloads allowed original source/handout into the ignored upstream/ directory
Target source paths to inspect:
  JOS env.c, pmap.c, trap.c; VMX/SVM entry, EPT/NPT

Core logical work belongs to student, not this package.
  CHALLENGES.md lists all 10 decisions.
  src/fixture_reader.c contains genuine strict CSV read/overflow checking,
  not an implementation of the university assignment.
  Existing test harnesses and external starter branches remain upstream.
No hosted code, CI/CD, VM provisioning, or cloud operations are necessary to test the local fixture.
Do NOT treat successful smoke test as a real target kernel pass.
