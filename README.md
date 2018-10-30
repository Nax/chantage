# Chantage

A Final Fantasy Tactics : The War of the Lions mod loader and API.

## Building

In order to build chantage, you need:

 * A working binutils + gcc cross compiler targeting the `mips-unknown-elf` triple.
 * The `psp-prxgen` tool.

The easiest way to build a working cross compiler is to use the [build-cc](https://github.com/Nax/build-cc) tool:

    git clone https://github.com/Nax/build-cc.git
    cd build-cc
    sudo bin/build-cc mips-unknown-elf

This will install a working cross compiler at `/opt/cross` by default.

You can get psp-prxgen here: https://github.com/pspdev/pspsdk  
If you don't want to build the whole PSP SDK, it is possible to make a dummy, empty config.h and then to compile
psp-prxgen directly from the `psp-prxgen.c` file.
