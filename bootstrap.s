        .global _start
_start:
        ldr sp, =0x07fffffc
        msr CPSR_c, #0xdf
        ldr sp, =0x07fffffc
        msr CPSR_c, #0xd3
        ldr r0, =0x400
        sub sp, sp, r0
        mov r0, #0x10
        msr SPSR, r0
        ldr lr, =main
        movs pc, lr        
