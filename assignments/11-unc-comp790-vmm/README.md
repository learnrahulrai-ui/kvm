UNC COMP790 Lab 6b JOS paravirtual VMM
Original assignment: https://www.cs.unc.edu/~porter/courses/comp790/s20/lab6b.html
Evidence: official 2020 URL provided earlier; live fetch currently blocked; underlying HOSS 2015 full PDF read
Goal: JOS-on-JOS VMX/EPT VM exits, hypercalls and virtual disk
Important limitation: Intel VMX lab uses an emulated Bochs environment. This is not a native AMD-V implementation.

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
