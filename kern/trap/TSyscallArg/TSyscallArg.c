#include <lib/trap.h>
#include <lib/x86.h>

#include "import.h"

extern tf_t uctx_pool[NUM_IDS];

/**
 * Retrieves the system call arguments from uctx_pool that get
 * passed in from the current running process' system call.
 */
unsigned int syscall_get_arg1(void)
{
    // TODO
    unsigned int cid = get_curid();
    return uctx_pool[cid].regs.eax;
    //return 0;
}

unsigned int syscall_get_arg2(void)
{
    // TODO
    unsigned int cid = get_curid();
    return uctx_pool[cid].regs.ebx;
    //return 0;
}

unsigned int syscall_get_arg3(void)
{
    // TODO
    unsigned int cid = get_curid();
    return uctx_pool[cid].regs.ecx;
    //return 0;
}

unsigned int syscall_get_arg4(void)
{
    // TODO
    unsigned int cid = get_curid();
    return uctx_pool[cid].regs.edx;
    //return 0;
}

unsigned int syscall_get_arg5(void)
{
    // TODO
    unsigned int cid = get_curid();
    return uctx_pool[cid].regs.esi;
    //return 0;
}

unsigned int syscall_get_arg6(void)
{
    // TODO
    unsigned int cid = get_curid();
    return uctx_pool[cid].regs.edi;
    //return 0;
}

/**
 * Sets the error number in uctx_pool that gets passed
 * to the current running process when we return to it.
 */
void syscall_set_errno(unsigned int errno)
{
    // TODO
    unsigned int cid = get_curid();
    uctx_pool[cid].regs.eax = errno;
}

/**
 * Sets the return values in uctx_pool that get passed
 * to the current running process when we return to it.
 */
void syscall_set_retval1(unsigned int retval)
{
    // TODO
    unsigned int cid = get_curid();
    //dprintf("Set_retval1 %d\n", cid);
    //dprintf("Current errno %d\n", uctx_pool[cid].err);
    //dprintf("trapno before %d\n", uctx_pool[cid].trapno);
    uctx_pool[cid].regs.ebx = retval;
    //dprintf("trapno after %d\n", uctx_pool[cid].trapno);
}

void syscall_set_retval2(unsigned int retval)
{
    // TODO
    unsigned int cid = get_curid();
    uctx_pool[cid].regs.ecx = retval;
}

void syscall_set_retval3(unsigned int retval)
{
    // TODO
    unsigned int cid = get_curid();
    uctx_pool[cid].regs.edx = retval;
}

void syscall_set_retval4(unsigned int retval)
{
    // TODO
    unsigned int cid = get_curid();
    uctx_pool[cid].regs.esi = retval;
}

void syscall_set_retval5(unsigned int retval)
{
    // TODO
    unsigned int cid = get_curid();
    uctx_pool[cid].regs.edi = retval;
}
