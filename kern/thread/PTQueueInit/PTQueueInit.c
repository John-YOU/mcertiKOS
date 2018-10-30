#include "lib/x86.h"

#include "import.h"

/**
 * Initializes all the thread queues with tqueue_init_at_id.
 */
void tqueue_init(unsigned int mbi_addr)
{
    // TODO: define your local variables here.
    unsigned int i;
    tcb_init(mbi_addr);

    // TODO
    for(i = 0 ; i < NUM_IDS+1; i++){
        tqueue_init_at_id(i);
    }
}

/**
 * Insert the TCB #pid into the tail of the thread queue #chid.
 * Recall that the doubly linked list is index based.
 * So you only need to insert the index.
 * Hint: there are multiple cases in this function.
 */
void tqueue_enqueue(unsigned int chid, unsigned int pid)
{
    // TODO
    unsigned int hindex = tqueue_get_head(chid);
    unsigned int tindex = tqueue_get_tail(chid);
    if(hindex == NUM_IDS){
        tqueue_set_head(chid, pid);
        tqueue_set_tail(chid, pid);
    }
    else {
        tcb_set_next(tindex, pid);
        tcb_set_prev(pid, tindex);
        tqueue_set_tail(chid, pid);
    }
}

/**
 * Reverse action of tqueue_enqueue, i.e. pops a TCB from the head of the specified queue.
 * It returns the popped thread's id, or NUM_IDS if the queue is empty.
 * Hint: there are multiple cases in this function.
 */
unsigned int tqueue_dequeue(unsigned int chid)
{
    // TODO
    unsigned int hindex = tqueue_get_head(chid);
    unsigned int tindex = tqueue_get_tail(chid);
    if(hindex == NUM_IDS){
        return NUM_IDS;
    }
    else {
        unsigned int hnext = tcb_get_next(hindex);
        if(hnext==NUM_IDS){
            tcb_set_next(hindex, NUM_IDS);
            tqueue_set_head(chid, NUM_IDS);
            tqueue_set_tail(chid, NUM_IDS);
        }
        else{
            tcb_set_next(hindex, NUM_IDS);
            tcb_set_prev(hnext, NUM_IDS);
            tqueue_set_head(chid, hnext);
        }
        return hindex;
    }
    //return 0;
}

/**
 * Removes the TCB #pid from the queue #chid.
 * Hint: there are many cases in this function.
 */
void tqueue_remove(unsigned int chid, unsigned int pid)
{
    // TODO
    unsigned int hindex = tqueue_get_head(chid);
    unsigned int tindex = tqueue_get_tail(chid);
    unsigned int cur = hindex;
    unsigned int flag = 0;
    // check if pid is in the queue
    while(cur!=NUM_IDS){
        if(cur == pid) {
            flag = 1;
            break;
        }
        cur = tcb_get_next(cur);
    }
    if(flag==0)return;
    
    unsigned int prev = tcb_get_prev(pid);
    unsigned int next = tcb_get_next(pid);
    if(pid==hindex){
        tcb_set_next(pid, NUM_IDS);
        tcb_set_prev(next, NUM_IDS);
        tqueue_set_head(chid, next);
    }
    else if(pid==tindex){
        tcb_set_next(prev, NUM_IDS);
        tcb_set_prev(pid, NUM_IDS);
        tqueue_set_tail(chid, prev);
    }
    else{ 
        tcb_set_prev(next, prev);
        tcb_set_next(prev, next);
        tcb_set_prev(pid, NUM_IDS);
        tcb_set_next(pid, NUM_IDS);
    }
    
}

