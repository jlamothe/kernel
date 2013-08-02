/*
 * INCLUDES
 */

#include "kernel.h"
#include "versatilepb.h"

/*
 * FUNCTION DEFINITIONS
 */

void bwputs(char *s)
{
    while(*s)
    {
        while(*(UART0 + UARTFR) & UARTFR_TXFF);
        *UART0 = *s;
        s++;
    }
}

void my_memcpy(void *dest, void *src, int size)
{
    int i;
    if(size < 0)
        return;
    for(i = 0; i < size; i++)
        ((char *)dest)[i] = ((char *)src)[i];
}

/* jl */
