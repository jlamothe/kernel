/*
 * INCLUDES
 */

#include "kernel.h"

/*
 * DEFINES
 */

#define STACK_SIZE 256
#define NUM_PROCS 16

/*
 * STRUCTS
 */

typedef struct
{
    int stack[NUM_PROCS * STACK_SIZE];
    int reg_data[NUM_PROCS * 0x10];
    int *stack_ptr[NUM_PROCS];
    int last_pid;
} SysStruct;

/*
 * FUNCTION PROTOTYPES
 */

int get_next_avail_pid(SysStruct *sys);
int set_proc_data(SysStruct *ss, int *buf, int pid);
int *get_proc_data(SysStruct *ss, int *buf, int pid);

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
        ss->stack_ptr[i] = NULL;
    return 0;
}

int init_new_thread(SysStruct *ss, int (*f)())
{
    int pid, offset;
    if(ss == NULL)
        return -1;
    pid = get_next_avail_pid(ss);
    if(pid < 0 || pid >= NUM_PROCS)
        return -1;
    offset = pid * STACK_SIZE;
    ss->stack_ptr[pid] = ss->stack + (STACK_SIZE * (pid + 1));
    ss->reg_data[offset] = (int)halt_and_catch_fire; /* lr */
    ss->reg_data[offset + 1] = (int)f; /* pc */
    ss->reg_data[offset + 2] = 0x10; /* SPSR */
    return pid;
}

int get_next_avail_pid(SysStruct *ss)
{
    int i;
    if(ss == NULL)
        return -1;
    for(i = 0; i < NUM_PROCS; i++)
        if(!ss->stack_ptr[i])
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
        return 1;
    ss->last_pid = pid;
    return 0;
}

int get_last_pid(SysStruct *ss)
{
    if(ss == NULL)
        return -1;
    return ss->last_pid;
}

int set_last_proc_data(SysStruct *ss, int *buf)
{
    if(ss == NULL)
        return 1;
    return set_proc_data(ss, buf, ss->last_pid);
}

int set_proc_data(SysStruct *ss, int *buf, int pid)
{
    if(ss == NULL || buf == NULL)
        return 1;
    if(pid < 0 || pid >= NUM_PROCS)
        return 1;
    my_memcpy(ss->reg_data + (pid * 0x10), buf, 0x40);
    return 0;
}

int *get_last_proc_data(SysStruct *ss, int *buf)
{
    if(ss == NULL)
        return NULL;
    return get_proc_data(ss, buf, ss->last_pid);
}

int *get_proc_data(SysStruct *ss, int *buf, int pid)
{
    int *sp;
    if(ss == NULL || buf == NULL)
        return NULL;
    if(pid < 0 || pid >= NUM_PROCS)
        return NULL;
    sp = ss->stack_ptr[pid];
    my_memcpy(buf, ss->reg_data + (pid * 0x10), 0x40);
    return sp;
}

/* jl */
