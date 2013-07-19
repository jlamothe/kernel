        .global _start
_start:
        ldr sp, =0x07fffffc
        msr CPSR_c, #0xdf
        ldr sp, =0x07fffffc
        msr CPSR_c, #0xd3
        ldr r0, =0x400
        sub sp, sp, r0
        ldr r0, =jump_interrupt
        mov r1, #0x8
        ldr r2, [r0, #0]
        str r2, [r1, #0]
        ldr r2, [r0, #4]
        str r2, [r1, #4]
        mov r0, #0x10
        msr SPSR, r0
        ldr lr, =main
        movs pc, lr        

catch_interrupt:
        push {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12}
        msr CPSR_c, #0xdf
        mov r0, sp
        mov r1, lr
        msr CPSR_c, #0xd3
        push {r0, r1}
        push {lr}
        mrs r0, SPSR
        push {r0}
        mov r12, sp

return_control:
        mov sp, r12
        pop {r0}
        msr SPSR, r0
        pop {lr}
        pop {r0, r1}
        msr CPSR_c, #0xdf
        mov sp, r0
        mov lr, r1
        msr CPSR_c, #0xd3
        pop {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12}
        movs pc, lr

jump_interrupt:
        ldr pc, interrupt_addr
interrupt_addr: 
        .word catch_interrupt
        
        .global call_interrupt
        .type call_interrupt, %function
call_interrupt:
        svc #0
        mov pc, lr
        