#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/mm.h>
#include <linux/gfp.h>
#include <linux/slab.h>
#include <linux/errno.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>

/* Registration, task lifetime, fault samples, worker teardown, buffer mmap:
 * student-owned logic. This module does not inspect or alter other tasks.
 */
static struct proc_dir_entry *mp3_directory;

static int mp3_status_show(struct seq_file *stream, void *unused)
{
    (void)unused;
    seq_puts(stream, "NOT_IMPLEMENTED\n");
    return 0;
}

static int mp3_status_open(struct inode *inode, struct file *file)
{
    (void)inode;
    return single_open(file, mp3_status_show, NULL);
}

static const struct proc_ops mp3_status_ops = {
    .proc_open = mp3_status_open,
    .proc_read = seq_read,
    .proc_lseek = seq_lseek,
    .proc_release = single_release,
};

static int __init mp3_profiler_init(void)
{
    mp3_directory = proc_mkdir("mp3", NULL);
    if (!mp3_directory)
        return -ENOMEM;
    if (!proc_create("status", 0444, mp3_directory, &mp3_status_ops)) {
        remove_proc_subtree("mp3", NULL);
        mp3_directory = NULL;
        return -ENOMEM;
    }
    pr_info("mp3_profiler: /proc/mp3/status ready; sampling unimplemented\n");
    return 0;
}

static void __exit mp3_profiler_exit(void)
{
    remove_proc_subtree("mp3", NULL);
    mp3_directory = NULL;
    pr_info("mp3_profiler: exit\n");
}

module_init(mp3_profiler_init);
module_exit(mp3_profiler_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("user");
MODULE_DESCRIPTION("CS423 MP3 procfs scaffold; registration and sampling left unimplemented");
