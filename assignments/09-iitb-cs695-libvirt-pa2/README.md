IIT Bombay CS695 PA2 libvirt autoscaler
Original assignment: https://www.cse.iitb.ac.in/~cs695/pa/pa2.html
Evidence: official assignment body including part A and optional extensions inspected
Goal: 1 server VM to 2 when load rises, libvirt monitoring only, low/high client workloads
Important limitation: The handout requires libvirt APIs rather than invoking virsh through system(). VM images and applications are not included.

First run (works without VM):
  make smoke
  # parses 3 independent numeric observations; each column sum = 93
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
