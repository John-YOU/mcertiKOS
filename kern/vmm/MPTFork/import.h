#ifndef _KERN_MM_MPTFORK_H_
#define _KERN_MM_MPTFORK_H_

#ifdef _KERN_


unsigned int map_page(unsigned int proc_index, unsigned int vaddr,
                      unsigned int page_index, unsigned int perm);
unsigned int get_pdir_entry(unsigned int proc_index, unsigned int pde_index);
void set_pdir_entry(unsigned int proc_index, unsigned int pde_index,
                    unsigned int page_index);
unsigned int get_ptbl_entry(unsigned int proc_index, unsigned int pde_index,
                            unsigned int pte_index);
void set_ptbl_entry(unsigned int proc_index, unsigned int pde_index,
                    unsigned int pte_index, unsigned int page_index,
                    unsigned int perm);

unsigned int get_curid(void);
void proc_start_user(void);
unsigned int get_ptbl_entry_by_va(unsigned int proc_index, unsigned int vaddr);
unsigned int thread_spawn(void *entry, unsigned int id, unsigned int quota);
void set_ptbl_entry_by_va(unsigned int proc_index, unsigned int vaddr,
                          unsigned int page_index, unsigned int perm);

unsigned int alloc_page(unsigned int proc_index, unsigned int vaddr,
                        unsigned int perm);
void rmv_ptbl_entry_by_va(unsigned int proc_index, unsigned int vaddr);
                        
#endif  /* _KERN_ */

#endif  /* !_KERN_MM_MPTFORK_H_ */
