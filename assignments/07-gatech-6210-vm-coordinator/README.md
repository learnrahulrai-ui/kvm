Georgia Tech CS6210 vCPU scheduler and memory coordinator
Original assignment: https://github.com/Felo2/solved-cs6210-project-1-vm-cpu-scheduler-and-memory-coordinator-fall2026
Evidence: secondary student repository reference only; no official public specification verified
Goal: host-side libvirt CPU pin balancing and VM memory adjustments; no copied solution
Important limitation: Do not read or copy the student solution. The scaffold has a genuine libvirt inventory build, but grading details remain unverified.

First run (works without VM):
  make smoke
  # parses 3 independent numeric observations; each column sum = 150
  make puzzle
  # exits 77, because your 10 logical functions/decisions are not implemented.
Then:
  bash bootstrap.sh
  # downloads allowed original source/handout into the ignored upstream/ directory
Target source paths to inspect:
  libvirt-domain APIs, virDomainGetCPUStats, virDomainSetVcpuPinning, virDomainSetMemoryStatsPeriod

Core logical work belongs to student, not this package.
  CHALLENGES.md lists all 10 decisions.
  src/fixture_reader.c contains genuine strict CSV read/overflow checking,
  not an implementation of the university assignment.
  Existing test harnesses and external starter branches remain upstream.
No hosted code, CI/CD, VM provisioning, or cloud operations are necessary to test the local fixture.
Do NOT treat successful smoke test as a real target kernel pass.
