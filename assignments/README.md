Independent assignment workspaces assembled 2026-11-20.
The existing Waldspurger research files in the parent repository remain unchanged.

Each numbered folder is standalone for its own assignment: primary handout URL and evidence status, the exact kernel files to inspect, 10 core decisions left to the student, numeric observations, a strict C fixture-reader build, smoke/puzzle targets, and bootstrap.sh to obtain available unsolved upstream sources. No solutions were copied from student repositories.

Run:
  cd assignments/01-wisc-2018-lottery
  make smoke               # builds and validates numeric fixture I/O, NOT assignment correctness
  make puzzle              # intentionally exits 77: logical work remains
  bash bootstrap.sh        # obtains public starter if one was verified

Notes:
- Linux modules, QEMU labs and libvirt labs need the respective real target environment before functional testing.
- External university handouts, test fixtures and source archives are referenced and downloaded locally by bootstrap.sh where available, not republished.
- Some university distribution material is private. Those folders flag it rather than fabricating an official starter.
- The generic fixture reader proves only file parsing and arithmetic. It is NOT an implementation of KVM, xv6, Pintos, a balloon driver, or a scheduler.
- Cumulative research from the original nine Waldspurger files is intentionally left untouched.
- For the memory-manager exercises, verify kernel version, guest agent support, host pressure, balloon bounds, and observed host/guest metrics in a real QEMU/KVM run.

22 distinct university exercises / historical course variants:
01-wisc-2018-lottery — UW Madison CS537 Spring 2018 P2b lottery
02-wisc-2015-stride — UW Madison CS537 2015 P2b stride
03-ucr-2024-lottery-stride — UCR CS202 Fall 2024 Lab 2 lottery and stride
04-ucr-2019-stride-syscalls — UCR CS202 2019 Lab 1 syscalls and stride
05-iit-cs450-lottery — Illinois Tech CS450 MP2 lottery
06-wisc-2019-mlfq — UW Madison CS537 2019 MLFQ
07-gatech-6210-vm-coordinator — Georgia Tech CS6210 vCPU scheduler and memory coordinator
08-iitb-cs695-kvm-pa1 — IIT Bombay CS695 PA1 KVM Hello World
09-iitb-cs695-libvirt-pa2 — IIT Bombay CS695 PA2 libvirt autoscaler
10-iitb-2023-kvm-a3 — IIT Bombay CS695 2023 A3 Hello KVM
11-unc-comp790-vmm — UNC COMP790 Lab 6b JOS paravirtual VMM
12-unc-2017-amd-svm — UNC COMP790 2017 AMD SVM final project
13-ut-cs360v-jos-hypervisor — UT Austin CS360V 2021 Project 1 JOS VMM
14-mit-61810-cow — MIT 6.1810 2025 COW fork
15-mit-61810-mmap — MIT 6.1810 2025 mmap and munmap
16-mit-61810-superpages — MIT 6.1810 2025 page tables and superpages
17-pintos-cs318-vm — JHU CS318 2019 Pintos Project 3 virtual memory
18-umich-eecs482-pager — UMich EECS482 external pager archived
19-uiuc-cs423-mp3 — UIUC CS423 Spring 2021 MP3 page fault profiler
20-cmu-15213-cache-lab — CMU 15-213 Fall 2012 Cache Lab Part A
21-biswas-oslab-kvm — Soumadip Biswas OS Lab capstone project 18 KVM
22-hws-331-lottery — Hobart William Smith CPSC331 Spring 2026 lottery

Primary historical anchor: Carl Waldspurger, Memory Resource Management in VMware ESX Server (OSDI 2002), https://www.usenix.org/legacy/publications/library/proceedings/osdi02/tech/waldspurger/waldspurger_html/
CPU anchor: Waldspurger and Weihl, Lottery Scheduling (OSDI 1994), https://www.waldspurger.org/carl/research.html
The 2015 HOSS primary paper: https://www.cs.unc.edu/~porter/pubs/jos-vm.pdf
