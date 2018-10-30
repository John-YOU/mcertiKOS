#ifndef _KERN_MM_MALOP_H_
#define _KERN_MM_MALOP_H_

#ifdef _KERN_

/**
 * The getter and setter functions implemented in the MATIntro layer.
 */

// The total number of physical pages.
unsigned int get_nps(void);

// Whether the page with the given index has normal permissions.
unsigned int at_is_norm(unsigned int page_index);

// Whether the page with the given index is already allocated.
unsigned int at_is_allocated(unsigned int page_index);

// Mark the allocation flag of the page with the given index using the given value.
void at_set_allocated(unsigned int page_index, unsigned int allocated);

void add_to_free(unsigned int pg_idx);
void add_to_alloc(unsigned int pg_idx);
unsigned int rm_from_free();
unsigned int rm_from_alloc(unsigned int pg_idx);

#endif  /* _KERN_ */

#endif  /* !_KERN_MM_MALOP_H_ */
