.section .text

.globl memcpy
memcpy:
    j 0x0880c700
    nop

.globl memset
memset:
    j 0x0880cb80
    nop

.globl memcmp
memcmp:
    j 0x0880c640
    nop

.globl memmove
memmove:
    j 0x0880c840
    nop

.globl memchr
memchr:
    j 0x0880c540
    nop

.globl strcat
strcat:
    j 0x0880f740
    nop

.globl strcmp
strcmp:
    j 0x0880f800
    nop

.globl strcpy
strcpy:
    j 0x0880f880
    nop

.globl strlen
strlen:
    j 0x0880f940
    nop

.globl malloc
malloc:
    move    $5, $4
    lui     $4, 0x08a7
    j       0x0880bd40
    ori     $4, 0x1f38

.globl free
free:
    move    $5, $4
    lui     $4, 0x08a7
    j       0x0880ad24
    ori     $4, 0x1f38

.globl sceIoRead
sceIoRead:
    j 0x08a4af3c
    nop

.globl sceIoClose
sceIoClose:
    j 0x08a4af4c
    nop

.globl sceIoOpen
sceIoOpen:
    j 0x08a4af6c
    nop

.globl sceIoLseek
sceIoLseek:
    j 0x08a4af74
    nop

.globl sceKernelDcacheWritebackRange
sceKernelDcacheWritebackRange:
    j 0x08a4b134
    nop
