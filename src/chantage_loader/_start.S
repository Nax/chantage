#include <loader/common.h>

.section .text.start
.globl _start
_start:
    li  $a0, 0x12345678
    jal sceIoChdir
    nop
    jr  $ra
    nop

.section .text
