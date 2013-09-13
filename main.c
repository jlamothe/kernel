/*
 * INCLUDES
 */

#include "kernel.h"

/*
 * FUNCTION DEFINITIONS
 */

int main(void)
{
    int fork_result;
    bwputs("Hello world!\n");
    fork_result = fork();
    if(fork_result < 0)
        bwputs("Fork failed!\n");
    else if(fork_result)
        bwputs("Main thread!\n");
    else
        bwputs("Child thread!\n");
    return 0;
}

/* jl */
