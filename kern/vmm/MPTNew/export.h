#ifndef _NEW_MM_MPTNEW_H_
#define _NEW_MM_MPTNEW_H_

unsigned int alloc_page(unsigned int proc_index, unsigned int vaddr,
                        unsigned int perm);
unsigned int alloc_mem_quota(unsigned int id, unsigned int quota);

#endif  /* !_NEW_MM_MPTNEW_H_ */
