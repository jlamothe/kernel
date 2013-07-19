#include "versatilepb.h"
#include "kernel.h"

void main(void)
{
    call_interrupt();
    char *str = "Hello world!\n";
    bwputs(str);
}

void bwputs(char *s)
{
    while(*s)
    {
        while(*(UART0 + UARTFR) & UARTFR_TXFF);
        *UART0 = *s;
        s++;
    }
}
