SECTIONS
{
    .text : SUBALIGN(0x4) {
        * ( .text )
    }

    .bss : SUBALIGN(0x4) {
        * ( .bss )
    }

    .data : SUBALIGN(0x4) {
        * ( .data )
    }

    .rodata : SUBALIGN(0x4) {
        * ( .rodata )
    }

    /DISCARD/ : {
        * ( .comment )
        * ( .pdr )
        * ( .MIPS.abiflags )
        * ( .reginfo )
        * ( .gnu.attributes )
        * ( .gcc_compiled_long32 )
        * ( .mdebug.eabi32 )
    }
}
