/*
 * INCLUDES
 */

#include "supervisor.h"
#include "kernel.h"
#include "syscalls.h"

/*
 * FUNCTION PROTOTYPES
 */

static int set_proc_data(SysStruct *ss, const int *buf, int pid);
static int get_proc_data(const SysStruct *ss, int *buf, int pid);
static void end_process();

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
        set_reg(ss, i, SP_REG, 0);
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
    set_reg(ss, pid, SP_REG, (int)(ss->proc[pid].stack + STACK_SIZE));
    set_reg(ss, pid, LR_REG, (int)end_process);
    set_reg(ss, pid, PC_REG, (int)f);
    set_spsr(ss, pid, 0x10);
    return pid;
}

int get_next_avail_pid(const SysStruct *ss)
{
    int i;
    if(ss == NULL)
        return -1;
    for(i = 0; i < NUM_PROCS; i++)
        if(!get_reg(ss, i, SP_REG))
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

int get_reg(const SysStruct *ss, int pid, int num)
{
    if(ss == NULL)
        return 0xdeadbeef;
    if(pid < 0 || pid >= NUM_PROCS)
        return 0xdeadbeef;
    if(num < 0 || num > 15)
        return 0xdeadbeef;
    if(num < 13)
        return ss->proc[pid].reg_data[num + 4];
    return ss->proc[pid].reg_data[num - 13];
}

int set_reg(SysStruct *ss, int pid, int num, int val)
{
    if(ss == NULL)
        return 1;
    if(pid < 0 || pid >= NUM_PROCS)
        return 2;
    if(num < 0 || num > 15)
        return 3;
    if(num < 13)
        ss->proc[pid].reg_data[num + 4] = val;
    else
        ss->proc[pid].reg_data[num - 13] = val;
    return 0;
}

int get_spsr(const SysStruct *ss, int pid)
{
    if(ss == NULL)
        return 0xdeadbeef;
    if(pid < 0 || pid >= NUM_PROCS)
        return 0xdeadbeef;
    return ss->proc[pid].reg_data[3];
}

int set_spsr(SysStruct *ss, int pid, int val)
{
    if(ss == NULL)
        return 1;
    if(pid < 0 || pid >= NUM_PROCS)
        return 2;
    ss->proc[pid].reg_data[3] = val;
    return 0;
}

void end_process()
{
    while(1)
        nice();
}

/* jl */
