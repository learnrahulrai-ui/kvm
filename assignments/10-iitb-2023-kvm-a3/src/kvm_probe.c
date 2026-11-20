/* Host-side KVM preparation. Builds a real VM and vCPU without running
 * guest instructions. The hard guest-state and VM exit logic belongs to you.
 * Smoke-built with -Werror on Linux; runtime requires /dev/kvm.
 */
#define _GNU_SOURCE
#include <errno.h>
#include <fcntl.h>
#include <inttypes.h>
#include <linux/kvm.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <unistd.h>
int main(void) {
    int kvm = -1, vm = -1, vcpu = -1, status = 2;
    void *ram = MAP_FAILED, *run = MAP_FAILED;
    size_t run_size = 0;
    const size_t ram_size = 2U * 1024U * 1024U;
    kvm = open("/dev/kvm", O_RDWR | O_CLOEXEC);
    if (kvm == -1) { perror("open /dev/kvm"); goto done; }
    int api = ioctl(kvm, KVM_GET_API_VERSION, 0);
    if (api != KVM_API_VERSION) {
        fprintf(stderr, "KVM API version: expected %d, found %d\n", KVM_API_VERSION, api);
        goto done;
    }
    int user_mem = ioctl(kvm, KVM_CHECK_EXTENSION, KVM_CAP_USER_MEMORY);
    if (user_mem <= 0) { fputs("KVM_CAP_USER_MEMORY unavailable\n", stderr); goto done; }
    vm = ioctl(kvm, KVM_CREATE_VM, 0);
    if (vm < 0) { perror("KVM_CREATE_VM"); goto done; }
    ram = mmap(NULL, ram_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (ram == MAP_FAILED) { perror("mmap RAM"); goto done; }
    struct kvm_userspace_memory_region region = {
        .slot = 0, .flags = 0, .guest_phys_addr = 0,
        .memory_size = ram_size, .userspace_addr = (uint64_t)(uintptr_t)ram
    };
    if (ioctl(vm, KVM_SET_USER_MEMORY_REGION, &region) == -1) {
        perror("KVM_SET_USER_MEMORY_REGION"); goto done;
    }
    vcpu = ioctl(vm, KVM_CREATE_VCPU, 0);
    if (vcpu < 0) { perror("KVM_CREATE_VCPU"); goto done; }
    int n = ioctl(kvm, KVM_GET_VCPU_MMAP_SIZE, 0);
    if (n <= 0) { perror("KVM_GET_VCPU_MMAP_SIZE"); goto done; }
    run_size = (size_t)n;
    run = mmap(NULL, run_size, PROT_READ | PROT_WRITE, MAP_SHARED, vcpu, 0);
    if (run == MAP_FAILED) { perror("mmap kvm_run"); goto done; }
    printf("api=%d user_memory=%d guest_bytes=%zu vcpu_run_bytes=%zu\n",
           api, user_mem, ram_size, run_size);
    puts("VM and vCPU created. Guest registers and execution left for the student.");
    status = 0;
done:
    if (run != MAP_FAILED) munmap(run, run_size);
    if (vcpu >= 0) close(vcpu);
    if (ram != MAP_FAILED) munmap(ram, ram_size);
    if (vm >= 0) close(vm);
    if (kvm >= 0) close(kvm);
    return status;
}
