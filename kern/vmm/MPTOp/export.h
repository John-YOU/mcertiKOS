#ifndef _KERN_MM_MPTOP_H_
#define _KERN_MM_MPTOP_H_

unsigned int get_pdir_entry_by_va(unsigned int proc_index, unsigned int vaddr);
void set_pdir_entry_by_va(unsigned int proc_index, unsigned int vaddr,
                          unsigned int page_index);
void rmv_pdir_entry_by_va(unsigned int proc_index, unsigned int vaddr);
unsigned int get_ptbl_entry_by_va(unsigned int proc_index, unsigned int vaddr);
void set_ptbl_entry_by_va(unsigned int proc_index, unsigned int vaddr,
                          unsigned int page_index, unsigned int perm);
void rmv_ptbl_entry_by_va(unsigned int proc_index, unsigned int vaddr);
void idptbl_init(unsigned int mbi_addr);

#endif  /* !_KERN_MM_MPTOP_H_ */
