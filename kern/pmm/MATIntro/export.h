#ifndef _KERN_MM_MALINIT_H_
#define _KERN_MM_MALINIT_H_

unsigned int get_nps(void);
void set_nps(unsigned int page_index);

unsigned int at_is_norm(unsigned int page_index);
void at_set_perm(unsigned int page_index, unsigned int perm);

unsigned int at_is_allocated(unsigned int page_index);
void at_set_allocated(unsigned int page_index, unsigned int allocated);

void init_list();
void add_to_free(unsigned int pg_idx);
void add_to_alloc(unsigned int pg_idx);
unsigned int rm_from_free(unsigned int pg_idx);
unsigned int rm_from_alloc(unsigned int pg_idx);
unsigned int at_is_allocated(unsigned int page_index);

#endif
