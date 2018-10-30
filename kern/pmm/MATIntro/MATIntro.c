#include <lib/gcc.h>

// Number of physical pages that are actually available in the machine.
static unsigned int NUM_PAGES;

/**
 * Structure representing information for one physical page.
 */
struct ATStruct {
    /**
     * The permission of the page.
     * 0: Reserved by the BIOS.
     * 1: Kernel only.
     * >1: Normal (available).
     */
    unsigned int perm;
    /**
     * Whether the page is allocated.
     * 0: unallocated
     * >0: allocated
     */
    unsigned int allocated;
};

/**
 * Self implemented linked list and list node for storing both free and allocated pages.
 * Used for allocating single page.
 */
struct ListNode{
    unsigned int pg_idx;
    unsigned int pre;
    unsigned int next;
};
struct LinkedList{
    struct ListNode list[1<<20];
    unsigned int size;
    unsigned int head;
    unsigned int tail;
};

// Declare two linked lists.
static struct LinkedList freepg;
static struct LinkedList allocpg;

// Initialize the lists.
void init_list(){
    freepg.size = 0;
    allocpg.size = 0;
    freepg.head = 0;
    freepg.tail = 0;
    allocpg.head = 0;
    allocpg.tail = 0;
}


// Add a free page to the free page list.
void add_to_free(unsigned int pg_idx){
    freepg.list[freepg.tail].next = pg_idx;
    freepg.list[pg_idx].pre = freepg.tail;
    freepg.list[pg_idx].next = -1;
    freepg.tail = pg_idx;
    freepg.size += 1;
}

// Add an allocated page to the alloc page list.
void add_to_alloc(unsigned int pg_idx){
    allocpg.list[allocpg.tail].next = pg_idx;
    allocpg.list[pg_idx].pre = allocpg.tail;
    allocpg.list[pg_idx].next = -1;
    allocpg.tail = pg_idx;
    allocpg.size += 1;
}

// Remove a free page from the free page list. Return 0 if failed.
void rm_from_free(){
    unsigned int ret = freepg.list[freepg.tail].pg_idx;
    freepg.list[freepg.list[freepg.tail].pre].next = -1;
    freepg.tail = freepg.list[freepg.tail].pre;
    freepg.size -= 1;
}

// Remove an allocated page from the alloc page list. Return 0 if failed.
void rm_from_alloc(unsigned int pg_idx){
    unsigned int pre = allocpg.list[pg_idx].pre;
    if(pre==-1){
        allocpg.head = allocpg.list[pg_idx].next;
        allocpg.list[allocpg.head].pre = -1;
    }
    else{
        allocpg.list[pre].next = allocpg.list[pg_idx].next;
        if(allocpg.list[pg_idx].next!=-1)allocpg.list[allocpg.list[pg_idx].next].pre = pre;
    }
    allocpg.size -= 1;
}


/*
 * Self-implemented MemChunk and MemMap for storing info of continuous pages.
 * Used for allocating continuous pages.
 */
struct MemChunk{
    unsigned int start;
    unsigned int size;
};
struct MemMap{
    struct MemChunk mmap[1<<20];
    int size;
};



/**
 * A 32 bit machine may have up to 4GB of memory.
 * So it may have up to 2^20 physical pages,
 * with the page size being 4KB.
 */
static struct ATStruct AT[1 << 20];

// The getter function for NUM_PAGES.
unsigned int get_nps(void)
{
    return NUM_PAGES;
}

// The setter function for NUM_PAGES.
void set_nps(unsigned int nps)
{
    NUM_PAGES = nps;
}

/**
 * The getter function for the page permission.
 * If the page with the given index has the normal permission,
 * then returns 1, otherwise returns 0.
 */
unsigned int at_is_norm(unsigned int page_index)
{
    unsigned int perm;

    perm = AT[page_index].perm;
    if (perm > 1) {
        perm = 1;
    } else {
        perm = 0;
    }

    return perm;
}

/**
 * The setter function for the physical page permission.
 * Sets the permission of the page with given index.
 * It also marks the page as unallocated.
 */
void at_set_perm(unsigned int page_index, unsigned int perm)
{
    AT[page_index].perm = perm;
    AT[page_index].allocated = 0;
}

/**
 * The getter function for the physical page allocation flag.
 * Returns 0 if the page is not allocated, otherwise returns 1.
 */
unsigned int at_is_allocated(unsigned int page_index)
{
    unsigned int allocated;

    allocated = AT[page_index].allocated;
    if (allocated > 0) {
        allocated = 1;
    }

    return allocated;
}

/**
 * The setter function for the physical page allocation flag.
 * Set the flag of the page with given index to the given value.
 */
void at_set_allocated(unsigned int page_index, unsigned int allocated)
{
    AT[page_index].allocated = allocated;
}
