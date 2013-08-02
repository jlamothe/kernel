        .global _start
_start:

        /* Initialize the SysStruct: */
        ldr sp, =0x08000000
        bl sys_struct_size
        sub sp, r0
        mov r0, sp
        bl init_sys_struct

        /* Set the interrupt vector: */
        ldr r0, =jump_sw_interrupt
        ldmfd r0, {r1, r2}
        mov r0, #0x8
        stmfd r0, {r1, r2}

        /* Initialize the first process: */
        mov r0, sp              /* SysStruct */
        ldr r1, =main           /* entry point */
        bl init_new_thread

resume_thread:

        /* Save the PID: */
        mov r1, r0
        mov r0, sp
        bl set_last_pid

        /* Get last process data: */
        mov r0, sp              /* SysStruct */
        sub sp, #0x40           /* make room on the stack */
        mov r1, sp              /* buffer */
        bl get_last_proc_data

        pop {r1, r2}            /* lr & pc */
        mov lr, r2              /* save pc for later */

        /* Set sytem sp and lr: */
        msr CPSR_c, #0xdf       /* system mode */
        mov sp, r0
        mov lr, r1
        msr CPSR_c, #0xd3       /* supervisor mode */
        
        /* SPSR: */
        pop {r0}
        msr SPSR, r0

        /* Remaining registers: */
        pop {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12}

        movs pc, lr             /* to user mode */

catch_sw_interrupt:

        /* Save registers: */
        push {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12}

        /* Save SPSR: */
        mrs r0, SPSR
        push {r0}

        /* Get user sp, lr & pc: */
        msr CPSR_c, #0xdf       /* system mode */
        mov r0, lr
        mov r1, sp
        msr CPSR_c, #0xd3       /* supervisor mode */
        push {r0, lr}           /* save lr & pc */

        /* Save data in the SysStruct: */
        mov r0, r1
        add r0, #0x40           /* SysStruct */
        bl set_last_proc_data
        add sp, #0x40

        b halt_and_catch_fire

jump_sw_interrupt:
        ldr pc, interrupt_addr
interrupt_addr: 
        .word catch_sw_interrupt
        
        .global call_sw_interrupt
        .type call_interrupt, %function
call_sw_interrupt:
        svc #0
        mov pc, lr
