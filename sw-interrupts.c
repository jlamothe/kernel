/*
 * INCLUDES
 */

#include "sw-interrupts.h"
#include "kernel.h"

/*
 * FUNCTION DEFINITIONS
 */

int fork()
{
    return call_sw_interrupt(FORK_INT, NULL);
}

int process_sw_interrupt(SysStruct *ss)
{
    int pid, id;
    void *buf;
    if(ss == NULL)
        return 1;
    pid = get_last_pid(ss);
    if(pid < 0 || pid >= NUM_PROCS)
        return 2;
    id = get_reg(ss, pid, 0);
    buf = (void *)get_reg(ss, pid, 1);

    switch(id)
    {

    case FORK_INT:
        return on_fork(ss, pid);

    default:
        return -1;

    }

}

int on_fork(SysStruct *ss, int pid)
{
    /* TODO: implement fork */
    return set_reg(ss, pid, 0, -1);
}

/* jl */
