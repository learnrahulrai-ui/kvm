IIT Bombay CS695 2023 A3 Hello KVM
Original assignment: https://www.cse.iitb.ac.in/~puru/courses/spring22/assignments.html
Evidence: official listing inspected; linked Google Doc handout inaccessible; original tar.gz link found
Goal: assignment #3 Hello KVM, university-hosted skeleton archive
Important limitation: Exact task details unknown without the Google Doc. bootstrap.sh downloads the original archive URL into upstream without claiming its contents.

First run (works without VM):
  make smoke
  # parses 3 independent numeric observations; each column sum = 2101249
  make puzzle
  # exits 77, because your 10 logical functions/decisions are not implemented.
Then:
  bash bootstrap.sh
  # downloads allowed original source/handout into the ignored upstream/ directory
Target source paths to inspect:
  kvm-hello-world.c, guest.c, linux/kvm.h, kvm_run, KVM_RUN

Core logical work belongs to student, not this package.
  CHALLENGES.md lists all 10 decisions.
  src/fixture_reader.c contains genuine strict CSV read/overflow checking,
  not an implementation of the university assignment.
  Existing test harnesses and external starter branches remain upstream.
No hosted code, CI/CD, VM provisioning, or cloud operations are necessary to test the local fixture.
Do NOT treat successful smoke test as a real target kernel pass.
