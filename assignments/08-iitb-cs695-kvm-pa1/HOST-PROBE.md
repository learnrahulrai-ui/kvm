Actual Linux KVM bootstrap program in src/kvm_probe.c, separate from course starter.
The mainline logic calls:
open /dev/kvm -> KVM_GET_API_VERSION -> KVM_CHECK_EXTENSION -> KVM_CREATE_VM
-> mmap(2097152 bytes) -> KVM_SET_USER_MEMORY_REGION -> KVM_CREATE_VCPU
-> KVM_GET_VCPU_MMAP_SIZE -> mmap(vcpu fd)
This uses real Linux KVM ioctls, unlike the numeric fixture.
Run make kvm-probe on a host with /dev/kvm accessible.
Guest registers, boot, exit decode, hypercalls, isolation tests remain student work.
Smoke compilation verified on Linux; execution not verified: test container has no /dev/kvm.
