#include <lib/gcc.h>
#include <lib/x86.h>
#include <lib/debug.h>
#include <lib/seg.h>
#include <lib/trap.h>

#include "import.h"


void copy_pdir_ptbl(unsigned int proc_1, unsigned int proc_2)
{
    unsigned int pde_index, pte_index, pdir_entry, ptbl_entry, page_index, perm, vaddr;
    for (pde_index = 0; pde_index < 1024; pde_index++)
    {
        pdir_entry = get_pdir_entry(proc_1, pde_index);
        page_index = pdir_entry >> 12;
        // set_pdir_entry(proc_2, pde_index, page_index);
        for (pte_index = 0; pte_index < 1024; pte_index++)
        {
            vaddr = ((pde_index << 10) + pte_index) << 12;
            if (vaddr >= VM_USERLO && vaddr < VM_USERHI)
            {
                ptbl_entry = get_ptbl_entry(proc_1, pde_index, pte_index);

                page_index = ptbl_entry >> 12;
                perm = PTE_COW | PTE_U | PTE_P;
                // set_ptbl_entry(proc_2, pde_index, pte_index, page_index, perm);
                map_page(proc_2, vaddr, page_index, perm);
            }
        }
    }
     dprintf("done with copy_pdir_ptbl\n");
}

// How to make the child process return 0???? In sys_fork
extern tf_t uctx_pool[NUM_IDS];
unsigned int proc_fork(unsigned int quota)
{
    unsigned int pid, id;

    id = get_curid();
    pid = thread_spawn((void *)proc_start_user, id, quota / 2);
    //dprintf("pid:%d\n", pid);

    uctx_pool[pid].es = uctx_pool[id].es;
    uctx_pool[pid].ds = uctx_pool[id].ds;
    uctx_pool[pid].cs = uctx_pool[id].cs;
    uctx_pool[pid].ss = uctx_pool[id].ss;
    uctx_pool[pid].esp = uctx_pool[id].esp;
    uctx_pool[pid].eflags = uctx_pool[id].eflags;
    uctx_pool[pid].eip = uctx_pool[id].eip;
    dprintf("done with proc_fork\n");
    return pid;
}

void copy_COW(unsigned int pid, unsigned int vaddr)
{
    //old page
    unsigned int ptbl_entry = get_ptbl_entry_by_va(pid, vaddr);
    unsigned int page_index = ptbl_entry >> 12;
    unsigned int phys_addr_old = page_index << 12, phys_addr_end_old = (page_index + 1) << 12;
    
    rmv_ptbl_entry_by_va(pid, vaddr);

    //new page
    unsigned int phys_index = alloc_page(pid, vaddr, PTE_P | PTE_W | PTE_U);
    unsigned int phys_addr = phys_index << 12, phys_addr_end = (phys_index + 1) << 12;
    unsigned int i, j;
    //change the mapping
    // Do we have to remove the old one first?
    // What about pdir_entry?
    set_ptbl_entry_by_va(pid, vaddr, phys_index, PTE_P | PTE_W | PTE_U);

    //copy
    for (i = phys_addr, j = phys_addr_old; i < phys_addr_end; i++, j++)
    {
        unsigned int *x = (unsigned int*)i, *y = (unsigned int*)j;
        *x = *y;
    }
    dprintf("done with copy_COW\n");
}
