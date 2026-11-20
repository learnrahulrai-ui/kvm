Harder interview example, using published ESX workload figures. This is a worked accounting question, not a proposed scheduler or reclaim algorithm.

Five VMs: 256 + 256 + 320 + 320 + 320 = 1472 MB of configured guest memory.
Overhead: 160 MB. Configured total = 1632 MB.
Available to the VMs in the paper's described run: 1 GB.
If GB is taken as 1024 MB, configured-minus-available = 608 MB.
During boot: reported zero-page sharing recovered 325 MB; observed nonzero paging was 35 MB.
325 / 35 = 9.285714...; neither number is a final memory snapshot.

Tempting but WRONG: 608 - 325 - 35 = 248 MB implies a missing accounting record.
Why wrong: 608 is a configuration difference at a workload level. Sharing recovered 325 MB and paging wrote 35 MB over an episode, potentially at different times. They are not partitions of one fixed snapshot.
What a valid measurement requires: one timestamp, actual machine pages in use, mapping-sharing multiplicities, resident frames, host swap occupancy, each VM allocation and hypervisor overhead.
Your difficult unsolved extension: choose a reclaim order for concurrent balloon refusal, short-lived page sharing, busy guest swap, an idle memory tax, and two contending tenants. Show first why the chosen action improves the global host constraint. Do not assume the host has guest free-page knowledge.

Source: https://www.usenix.org/legacy/publications/library/proceedings/osdi02/tech/waldspurger/waldspurger_html/node20.html
Grounding: read with OSDI 2002 sections 3-6, plus existing WALDSPURGER_05_CUMULATIVE_ESX_REAL_5_VM_RUN.txt.
