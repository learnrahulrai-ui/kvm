/* Read-only libvirt inventory: host setup, not a VM balancing solution.
 * Build: cc -std=c11 -O2 -Wall -Wextra -Werror -Wpedantic
 *             $(pkg-config --cflags libvirt) libvirt_inventory.c
 *             $(pkg-config --libs libvirt) -o inventory
 */
#define _POSIX_C_SOURCE 200809L
#include <libvirt/libvirt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char **argv) {
    if (argc > 2) { fputs("usage: inventory [qemu:///system]\n", stderr); return 2; }
    virConnectPtr connection = virConnectOpenReadOnly(argc == 2 ? argv[1] : NULL);
    if (connection == NULL) { fputs("Unable to open read-only libvirt connection\n", stderr); return 2; }
    virNodeInfo host = {0};
    if (virNodeGetInfo(connection, &host) == 0) {
        printf("host_cpus=%u host_memory_KiB=%lu\n", host.cpus, host.memory);
    }
    virDomainPtr *domains = NULL;
    int total = virConnectListAllDomains(connection, &domains, VIR_CONNECT_LIST_DOMAINS_ACTIVE);
    if (total < 0) { fputs("Unable to list running domains\n", stderr); virConnectClose(connection); return 2; }
    printf("running_vms=%d\n", total);
    for (int i = 0; i < total; ++i) {
        virDomainInfo info = {0};
        if (virDomainGetInfo(domains[i], &info) == 0) {
            const char *name = virDomainGetName(domains[i]);
            printf("vm=%s state=%u max_mem_KiB=%lu current_mem_KiB=%lu vcpus=%hu cumulative_cpu_ns=%llu\n",
                name ? name : "(unnamed)", (unsigned)info.state, info.maxMem,
                info.memory, info.nrVirtCpu, (unsigned long long)info.cpuTime);
        }
        virDomainFree(domains[i]);
    }
    free(domains);
    virConnectClose(connection);
    puts("These are point-in-time totals, NOT CPU utilization or a relocation decision.");
    return 0;
}
