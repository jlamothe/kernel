#ifndef SUPERVISOR_H

/*
 * DEFINES
 */

#define STACK_SIZE 256
#define NUM_PROCS 16
#define SP_REG 13
#define LR_REG 14
#define PC_REG 15

/*
 * STRUCTS
 */

typedef struct
{
    int stack[STACK_SIZE];
    int reg_data[17];
} ProcData;

typedef struct
{
    ProcData proc[NUM_PROCS];
    int last_pid;
} SysStruct;

/*
 * FUNCTION PROTOTYPES
 */

int sys_struct_size(void);
int init_sys_struct(SysStruct *ss);
int init_new_thread(SysStruct *ss, int (*f)());
int set_last_pid(SysStruct *ss, int pid);
int get_last_pid(const SysStruct *ss);
int set_last_proc_data(SysStruct *ss, const int *buf);
int get_last_proc_data(const SysStruct *ss, int *buf);

#endif  /* SUPERVISOR_H */

/* jl */
