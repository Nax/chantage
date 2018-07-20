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
