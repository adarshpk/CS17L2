// CS 17L2 NETWORKS AND OPERATING SYSTEMS LABORATORY
// Cycle 4 : Exp 23 : LINUX INTERNALS
// ADARSH P.K. CSU13203
/* Creates a proc file entry that displays the current time (EPOCH).
~~DO NOT COMPILE DIRECTLY~~
Compile using make command. See Makefile.
Insert the module using insmod after compilation.
Display proc file using cat /proc/deeds_clock
*/

#include <linux/module.h>
#include <linux/init.h>
#include <linux/errno.h>
#include <linux/fs.h>
#include <linux/proc_fs.h>
#include <linux/time.h>
#include <asm/uaccess.h>

#define PROC_FILE_NAME "deeds_clock"
#define TMP_SIZE 100

MODULE_AUTHOR("Adarsh P.K.");
MODULE_DESCRIPTION("Lab Solution");
MODULE_LICENSE("GPL");

struct proc_dir_entry *proc_entry;
static char tmp[TMP_SIZE];

// this method is executed when reading from the module
static ssize_t gen_module_read(struct file *file, char *buf, size_t count, loff_t *ppos)
{
	static int once = 0;
	if(once) {
		once = 0;
		return 0; //Returns 0 to inidicate EOF. Prevents infinite read loop.
	}
	once=1;
	struct timeval curtime;
	do_gettimeofday(&curtime);
	sprintf(tmp, "Current time: %lu seconds\n", curtime.tv_sec);
	printk(KERN_DEFAULT "gen_module_read : Read Attempted.");
	return copy_to_user(buf, tmp, TMP_SIZE) ? -EFAULT : TMP_SIZE;
}

// this method is called whenever the module is being used
// e.g. for both read and write operations
static int gen_module_open(struct inode * inode, struct file * file)
{
	return 0;
}

// module's file operations
static struct file_operations gen_module_fops = {
	.owner =	THIS_MODULE,
	.read =		gen_module_read,
	.open =		gen_module_open,
};

// initialize module (executed when using insmod)
static int __init gen_module_init(void)
{
	printk(KERN_INFO "deeds_clock module is being loaded.\n");
	proc_entry = proc_create(PROC_FILE_NAME, 0, NULL, &gen_module_fops);
  	if(proc_entry == NULL)
  	{
   		remove_proc_entry(PROC_FILE_NAME, 0);
		printk(KERN_ALERT "Error: Could not initialize /proc/%s\n",PROC_FILE_NAME);
		return -ENOMEM;
	}
	printk(KERN_INFO "/proc/%s created\n", PROC_FILE_NAME);
	return 0;
}

// cleanup module (executed when using rmmod)
static void __exit gen_module_cleanup(void)
{
	remove_proc_entry(PROC_FILE_NAME, NULL);
    printk(KERN_INFO "/proc/%s removed\n", PROC_FILE_NAME);
	printk(KERN_INFO "deeds_clock module is being unloaded.\n");
}

module_init(gen_module_init);
module_exit(gen_module_cleanup);
