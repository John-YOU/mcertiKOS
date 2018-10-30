#include <lib/x86.h>

#include "import.h"

#define PAGESIZE     4096
#define VM_USERLO    0x40000000
#define VM_USERHI    0xF0000000
#define VM_USERLO_PI (VM_USERLO / PAGESIZE)
#define VM_USERHI_PI (VM_USERHI / PAGESIZE)

/**
 * For each process from id 0 to NUM_IDS - 1,
 * set up the page directory entries so that the kernel portion of the map is
 * the identity map, and the rest of the page directories are unmapped.
 */
void pdir_init(unsigned int mbi_addr)
{
    // TODO: Define your local variables here.

    idptbl_init(mbi_addr);
    for (unsigned int i=0;i<NUM_IDS;i++){

	for (unsigned int j=0;j<VM_USERLO_PI>>10;j++)
		set_pdir_entry_identity(i,j);
	for (unsigned int j=VM_USERHI_PI>>10;j<1024;j++)
		set_pdir_entry_identity(i,j);

	//the rest unmapped
	for (unsigned int j=VM_USERLO_PI>>10;j<VM_USERHI_PI>>10;j++)
		rmv_pdir_entry(i,j);
    }
    // TODO
}

/**
 * Allocates a page (with container_alloc) for the page table,
 * and registers it in the page directory for the given virtual address,
 * and clears (set to 0) all page table entries for this newly mapped page table.
 * It returns the page index of the newly allocated physical page.
 * In the case when there's no physical page available, it returns 0.
 */
unsigned int alloc_ptbl(unsigned int proc_index, unsigned int vaddr)
{
    // TODO

    unsigned int page_index=container_alloc(proc_index);
    if (!page_index) return 0;

    set_pdir_entry_by_va(proc_index,vaddr,page_index);

    for (unsigned int i=page_index<<12;i<(page_index+1)<<12;i++){
        unsigned int *tmp;
        tmp= (unsigned int*) i;
	*tmp=0x00000000;
    }
    return page_index;
}

// Reverse operation of alloc_ptbl.
// Removes corresponding the page directory entry,
// and frees the page for the page table entries (with container_free).
void free_ptbl(unsigned int proc_index, unsigned int vaddr)
{
    // TODO
    unsigned int page_index=get_pdir_entry_by_va(proc_index, vaddr)>>12;
	rmv_pdir_entry_by_va(proc_index, vaddr);

	//free the physical page
	container_free(proc_index, page_index);
}
