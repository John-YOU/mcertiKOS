#ifndef _KERN_MM_MPTFORK_H_
#define _KERN_MM_MPTFORK_H_

void copy_pdir_ptbl(unsigned int proc_1, unsigned int proc_2);
unsigned int proc_fork(unsigned int quota);
void copy_COW(unsigned int pid, unsigned int vaddr);

#endif  /* !_KERN_MM_MPTFORK_H_ */