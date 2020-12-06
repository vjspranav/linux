#include <linux/kernel.h>
#include <linux/syscalls.h>

SYSCALL_DEFINE2(rtnice, long, pid, long, tim)
{
	struct task_struct *p;
	if(tim<0){
		printk("Invalid Softruntime %ld\n", tim);
		return -1;
	}
	read_lock(&tasklist_lock);
	for_each_process(p) {
		if (pid==p->pid) {
			p->se.sruntime=tim;
			read_unlock(&tasklist_lock);
			printk(KERN_INFO "Updating softruntime gurantee of %ld to %ld Found\n", pid, tim);
			return pid;
		}
	}
	read_unlock(&tasklist_lock);
	printk("Invalid pid %ld\n", pid);
	return 0;
}
