UT Austin CS360V 2021 Project 1 JOS VMM
Original assignment: https://github.com/vijay03/cs360v-f21/blob/main/project1-labs.md
Evidence: course repo linked, full file contents not independently inspected in this pass
Goal: JOS guest bootstrap, EPT, instruction trap, disk hypercalls
Important limitation: Code checkout obtains the course repository, not a solved hypervisor. Verify lab-specific branch before changing it.

First run (works without VM):
  make smoke
  # parses 3 independent numeric observations; each column sum = 24576
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
