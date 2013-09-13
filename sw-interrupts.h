#ifndef SW_INTERRUPT_H

/*
 * INCLUDES
 */

#include "supervisor.h"

/*
 * DEFINES
 */

#define FORK_INT 0

/*
 * FUNCTION PROTOTYPES
 */

int call_sw_interrupt(int id, void *data);
int process_sw_interrupt(SysStruct *ss);

#endif  /* SW_INTERRUPT_H */

/* jl */
