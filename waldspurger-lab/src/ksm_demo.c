/* Anonymous same-content page experiment. No kernel memory writes.
 * Two independent copies can be merged only if the host KSM daemon runs.
 */
#define _GNU_SOURCE
#include <errno.h>
#include <inttypes.h>
#include <limits.h>
#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
static volatile sig_atomic_t change_first = 0;
static void on_signal(int sig) { (void)sig; change_first = 1; }
static int parse(const char *s, long *out)
{
    char *end=NULL; errno=0;
    long n=strtol(s,&end,10);
    if(errno || end==s || *end) return -1;
    *out=n; return 0;
}
int main(int argc, char **argv)
{
    long mib, merge, seconds;
    if(argc != 4 || parse(argv[1],&mib) || parse(argv[2],&merge) ||
       parse(argv[3],&seconds) || mib<1 || mib>128 ||
       (merge!=0 && merge!=1) || seconds<0 || seconds>600) {
        fprintf(stderr, "usage: ksm_demo MiB(1..128) merge(0|1) seconds(0..600)\n");
        return 2;
    }
    long page=sysconf(_SC_PAGESIZE);
    if(page<=0 || page > INT_MAX) return 2;
    size_t size=(size_t)mib * 1024U * 1024U;
    if(size%(size_t)page) { fprintf(stderr,"size not page aligned\n"); return 2; }
    unsigned char *p=mmap(NULL,size,PROT_READ|PROT_WRITE,MAP_PRIVATE|MAP_ANONYMOUS,-1,0);
    if(p==MAP_FAILED){perror("mmap");return 2;}
    size_t pages=size/(size_t)page;
    for(size_t i=0;i<pages;i++){
        unsigned char *a=p+i*(size_t)page;
        memset(a,0x5a,(size_t)page);
        /* Two processes get identical content for equal indices, but
         * distinct page indices are NOT all mapped to the same bytes. */
        uint32_t index=(uint32_t)i;
        memcpy(a,&index,sizeof(index));
    }
    if(merge && madvise(p,size,MADV_MERGEABLE)) {
        perror("madvise(MADV_MERGEABLE)");munmap(p,size);return 2;
    }
    struct sigaction sa={0};
    sa.sa_handler=on_signal;
    sigemptyset(&sa.sa_mask);
    if(sigaction(SIGUSR1,&sa,NULL)){perror("sigaction");munmap(p,size);return 2;}
    printf("pid=%ld address=%p bytes=%zu page_bytes=%ld pages=%zu merge=%ld\n",
           (long)getpid(),(void*)p,size,page,pages,merge);
    fflush(stdout);
    for(long sec=0;sec<seconds;sec++){
        sleep(1);
        if(change_first) {
            change_first=0;
            unsigned char old=p[8];
            p[8]=(unsigned char)(old ^ 0xffU);
            printf("after_SIGUSR1 page_zero_byte_8_before=%u after=%u\n",
                   (unsigned)old,(unsigned)p[8]);
            fflush(stdout);
        }
    }
    if(munmap(p,size)) { perror("munmap"); return 2; }
    return 0;
}
