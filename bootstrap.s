        .global _start
_start:
        ldr sp, =0x07ffffff
        bl main
