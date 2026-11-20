/* Read-only. Reports local kernel, page size, /dev/kvm API, and available nodes.
 * It does NOT try to trigger any historical kernel/QEMU failure.
 */
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/utsname.h>
#include <dirent.h>
#include <linux/kvm.h>
static int count_nodes(void) {
  DIR *d=opendir("/sys/devices/system/node");
  if(!d) return -1;
  struct dirent *e; int n=0;
  while((e=readdir(d))) {
    if(strncmp(e->d_name,"node",4)==0 && e->d_name[4]>='0' && e->d_name[4]<='9') ++n;
  }
  closedir(d); return n;
}
static void show_cpu(void) {
  FILE *f=fopen("/proc/cpuinfo","r"); if(!f) return;
  char buf[512];
  while(fgets(buf,sizeof(buf),f)) {
    if(strncmp(buf,"vendor_id",9)==0 || strncmp(buf,"model name",10)==0) {
      fputs(buf,stdout);
      if(strncmp(buf,"model name",10)==0) break;
    }
  }
  fclose(f);
}
int main(void) {
  struct utsname u;
  if(uname(&u)==0) printf("host_kernel=%s machine=%s\n",u.release,u.machine);
  long p=sysconf(_SC_PAGESIZE);
  printf("page_bytes=%ld numa_nodes=%d\n",p,count_nodes());
  show_cpu();
  int kvm=open("/dev/kvm",O_RDWR|O_CLOEXEC);
  if(kvm<0) { perror("/dev/kvm"); puts("kvm_access=no"); return 0; }
  int ver=ioctl(kvm,KVM_GET_API_VERSION,0);
  printf("kvm_api=%d expected=%d\n",ver,KVM_API_VERSION);
#ifdef KVM_CAP_DIRTY_LOG_RING
  int dirty=ioctl(kvm,KVM_CHECK_EXTENSION,KVM_CAP_DIRTY_LOG_RING);
  printf("dirty_ring_extension=%d\n",dirty);
#endif
#ifdef KVM_CAP_GUEST_MEMFD
  int gmem=ioctl(kvm,KVM_CHECK_EXTENSION,KVM_CAP_GUEST_MEMFD);
  printf("guest_memfd_extension=%d\n",gmem);
#endif
  close(kvm);
  return 0;
}
