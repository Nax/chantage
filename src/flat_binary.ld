OUTPUT_FORMAT(binary)
SECTIONS
{
    . = 0x09000000;

    .text : SUBALIGN(0x04) {
        * ( .text.start )
        * ( .text )
    }

    .data : SUBALIGN(0x04) {
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
