SECTIONS
{
    . = 0x0;
    .text : {
        start.o (.text)
        * (.text)
    }

    .shstrtab : {
        * (.shstrtab)
    }

    . = 0x1000;
    .bss : {
        * (.bss)
    }

    .data : {
        * (.data)
    }

    .rodata : {
        * (.rodata)
    }

    /DISCARD/ : {
        * (.MIPS.abiflags)
        * (.reginfo)
        * (.comment)
    }
}
