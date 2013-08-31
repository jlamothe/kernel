/*
 * INCLUDES
 */

#include "kernel.h"

/*
 * FUNCTION DEFINITIONS
 */

int main(void)
{
    bwputs("Hello world!\n");
    call_sw_interrupt();
    bwputs("Control returned!\n");
    return 0;
}

/* jl */
