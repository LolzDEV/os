.section .text
.global _entry
_entry: # Placed at 0x80000000 by the linker
    la sp, etext # Let the stack start where the text section ends
    li a0, 1024*4
    csrr a1, mhartid
    addi a1, a1, 1
    mul a0, a0, a1
    add sp, sp, a0
    csrr a1, mhartid # Check if the hardid is 0, if so start the kernel (C)
    bne a1, zero, spin
kernel:
    call start

spin:
    j spin