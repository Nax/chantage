#include <loader/common.h>

.section .text

.macro wrap sym, addr
.globl \sym
\sym\():
    li  $v0, \addr
    jr  $v0
.endm

wrap sceIoChdir,    0x08a4af34
wrap sceIoRead,     0x08a4af3c
wrap sceIoClose,    0x08a4af4c
wrap sceIoDopen,    0x08a4af5c
wrap sceIoDclose,   0x08a4af64
wrap sceIoOpen,     0x08a4af6c
wrap sceIoLseek,    0x08a4af74

wrap _malloc_r,     0x0880bd40

.globl malloc
malloc:
    move    $a1, $a0
    li      $a0, 0x08a71f38
    j       _malloc_r
