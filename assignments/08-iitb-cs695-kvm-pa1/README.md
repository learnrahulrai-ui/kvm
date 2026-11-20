IIT Bombay CS695 PA1 KVM Hello World
Original assignment: https://www.cse.iitb.ac.in/~cs695/pa/pa1.html
Evidence: official handout body and dpw starter repository inspected
Goal: extend kvm-hello-world.c and guest.c, guest/host exit path, hypercalls
Important limitation: The official starter has an MIT license and an AMD-V-tested description. Existing PA1 work should NOT be overwritten by this folder.

First run (works without VM):
  make smoke
  # parses 3 independent numeric observations; each column sum = 2101253
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
