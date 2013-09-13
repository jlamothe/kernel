/*
 * INCLUDES
 */

#include "supervisor.h"
#include "kernel.h"

/*
 * FUNCTION PROTOTYPES
 */

static int get_next_avail_pid(const SysStruct *ss);
static int set_proc_data(SysStruct *ss, const int *buf, int pid);
static int get_proc_data(const SysStruct *ss, int *buf, int pid);

/*
 * FUNCTION DEFINITIONS
 */

int sys_struct_size()
{
    return sizeof(SysStruct);
}

int init_sys_struct(SysStruct *ss)
{
    int i;
    if(ss == NULL)
        return 1;
    for(i = 0; i < NUM_PROCS; i++)
        ss->proc[i].reg_data[0] = 0;
    return 0;
}

int init_new_thread(SysStruct *ss, int (*f)())
{
    int pid;
    if(ss == NULL)
        return -1;
    pid = get_next_avail_pid(ss);
    if(pid < 0 || pid >= NUM_PROCS)
        return -1;
    ss->proc[pid].reg_data[0] =
        (int)(ss->proc[pid].stack + STACK_SIZE); /* sp */
    ss->proc[pid].reg_data[1] =
        (int)halt_and_catch_fire; /* lr */
    ss->proc[pid].reg_data[2] = (int)f; /* pc */
    ss->proc[pid].reg_data[3] = 0x10; /* SPSR */
    return pid;
}

int get_next_avail_pid(const SysStruct *ss)
{
    int i;
    if(ss == NULL)
        return -1;
    for(i = 0; i < NUM_PROCS; i++)
        if(!ss->proc[i].reg_data[0])
            return i;
    return -1;
}

void halt_and_catch_fire()
{
    bwputs("OH NOES!!!!!!111oneone\n");
    while(1);
}

int set_last_pid(SysStruct *ss, int pid)
{
    if(ss == NULL)
        return -1;
    ss->last_pid = pid;
    return pid;
}

int get_last_pid(const SysStruct *ss)
{
    if(ss == NULL)
        return -1;
    return ss->last_pid;
}

int set_last_proc_data(SysStruct *ss, const int *buf)
{
    if(ss == NULL)
        return -1;
    return set_proc_data(ss, buf, ss->last_pid);
}

int set_proc_data(SysStruct *ss, const int *buf, int pid)
{
    if(ss == NULL || buf == NULL)
        return -1;
    if(pid < 0 || pid >= NUM_PROCS)
        return -2;
    my_memcpy(ss->proc[pid].reg_data, buf, 0x44);
    return pid;
}

int get_last_proc_data(const SysStruct *ss, int *buf)
{
    if(ss == NULL)
        return -1;
    return get_proc_data(ss, buf, ss->last_pid);
}

int get_proc_data(const SysStruct *ss, int *buf, int pid)
{
    if(ss == NULL || buf == NULL)
        return -1;
    if(pid < 0 || pid >= NUM_PROCS)
        return -2;
    my_memcpy(buf, ss->proc[pid].reg_data, 0x44);
    return pid;
}

/* jl */
