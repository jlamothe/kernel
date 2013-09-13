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
void bwputs(const char *s);
void my_memcpy(void *dest, const void *src, int size);
void debug(int val);
int fork(void);

#endif  /* KERNEL_H */

/* jl */
