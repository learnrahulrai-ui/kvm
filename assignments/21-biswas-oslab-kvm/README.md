Soumadip Biswas OS Lab capstone project 18 KVM
Original assignment: https://soumadip.github.io/courses/os-lab/content/assignments/capstone/
Evidence: official professor capstone page inspected, lines 333-346
Goal: 16-bit real mode KVM hypervisor and VM exit I/O emulation
Important limitation: Instructor's reference binary payload is not public. dpw is an independently licensed substitute, not the course's own provided payload.

First run (works without VM):
  make smoke
  # parses 3 independent numeric observations; each column sum = 4113
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
