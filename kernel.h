#ifndef KERNEL_H
#define KERNEL_H

/*
 * DEFINES
 */

#define NULL ((void *)0)


/*
 * FUNCTION PROTOTYPES
 */

void halt_and_catch_fire(void);
void bwputs(char *s);
void my_memcpy(void *dest, void *src, int size);
void call_sw_interrupt(void);

#endif  /* KERNEL_H */

/* jl */
