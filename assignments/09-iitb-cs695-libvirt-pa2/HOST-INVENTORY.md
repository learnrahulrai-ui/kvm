Actual read-only libvirt inventory is src/libvirt_inventory.c.
Uses virConnectOpenReadOnly -> virNodeGetInfo -> virConnectListAllDomains
-> virDomainGetInfo -> virDomainFree -> virConnectClose.
Records domain state, memory KiB, vCPUs, cumulative CPU time ns.
It makes no policy decisions, no CPU pin changes, no balloon changes, no VM creation.
Run make inventory with libvirt-dev and a readable libvirt connection.
The build was not executed in this environment: libvirt headers are absent.
For scheduling policy, obtain CPU-time deltas from two snapshots before reasoning about utilization.
