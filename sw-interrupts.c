/*
 * INCLUDES
 */

#include "sw-interrupts.h"
#include "syscalls.h"
#include "kernel.h"
#include "supervisor.h"

/*
 * FUNCTION PROTOTYPES
 */

static int on_nice(SysStruct *ss, int pid);
static int on_fork(SysStruct *ss, int pid);
static int on_get_pid(SysStruct *ss, int pid);

/*
 * FUNCTION DEFINITIONS
 */

void nice()
{
    call_sw_interrupt(NICE_INT, NULL);
}

int fork()
{
    return call_sw_interrupt(FORK_INT, NULL);
}

int get_pid()
{
    return call_sw_interrupt(GET_PID_INT, NULL);
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

    case NICE_INT:
        return on_nice(ss, pid);

    case FORK_INT:
        return on_fork(ss, pid);

    case GET_PID_INT:
        return on_get_pid(ss, pid);

    default:
        return -1;

    }

}

int on_nice(SysStruct *ss, int pid)
{
    int p = pid;
    do
    {
        p++;
        if(p >= NUM_PROCS)
            p = 0;
        if(get_reg(ss, p, SP_REG))
            break;
    }
    while(p != pid);
    return set_last_pid(ss, p);
}

int on_fork(SysStruct *ss, int pid)
{
    int p = get_next_avail_pid(ss), offset;
    int *spa, *spb;
    if(p < 0)
        return set_reg(ss, pid, 0, -1);
    my_memcpy(&(ss->proc[p]),
              &(ss->proc[pid]),
              sizeof(ss->proc[pid]));
    spa = (int *)get_reg(ss, pid, SP_REG);
    offset = spa - ss->proc[pid].stack;
    spb = ss->proc[pid].stack + offset;
    if(set_reg(ss, p, SP_REG, (int)spb))
        return 1;
    if(set_reg(ss, pid, 0, p))
        return 2;
    if(set_reg(ss, p, 0, 0))
        return 3;
    return 0;
}

int on_get_pid(SysStruct *ss, int pid)
{
    set_reg(ss, pid, 0, pid);
    return 0;
}

/* jl */
