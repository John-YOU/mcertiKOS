#ifndef _KERN_MM_MPTCOMM_H_
#define _KERN_MM_MPTCOMM_H_

void pdir_init(unsigned int mbi_addr);
unsigned int alloc_ptbl(unsigned int proc_index, unsigned int vaddr);
void free_ptbl(unsigned int proc_index, unsigned int vaddr);

#endif  /* !_KERN_MM_MPTCOMM_H_ */
