OUTPUT_FORMAT(binary)
SECTIONS
{
    .text : {
        * ( .text.start )
        * ( .text )
        * ( .data )
        * ( .rodata )
        * ( .bss )
    }

    /DISCARD/ : {
        * ( .comment )
        * ( .reginfo )
        * ( .MIPS.abiflags )
        * ( .gnu.attributes )
        * ( .symtab )
        * ( .pdr )
        * ( .strtab )
        * ( .shstrtab )
    }
}
