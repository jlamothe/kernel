#ifndef SW_INTERRUPT_H

/*
 * INCLUDES
 */

#include "supervisor.h"

/*
 * DEFINES
 */

#define NICE_INT 0
#define FORK_INT 1
#define GET_PID_INT 2

/*
 * FUNCTION PROTOTYPES
 */

int call_sw_interrupt(int id, void *data);
int process_sw_interrupt(SysStruct *ss);

#endif  /* SW_INTERRUPT_H */

/* jl */
