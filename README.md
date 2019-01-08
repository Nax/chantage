# Chantage

A Final Fantasy Tactics: The War of the Lions mod loader and API.

## Dependencies

In order to build chantage, you need a copy of the chantage toolchain.
It can be obtained here: https://dl.nax.io/

On windows, simply copy the toolchain into `C:\`

CMake is also required. On Windows, you probably want to use PowerShell and get GNU Make.

## Building

To build:

    git clone https://github.com/FFT-Hackers/chantage.git
    cd chantage
    mkdir build
    cd build
    mkdir MinRelSize
    cd MinRelSize
    cmake ../.. -DCMAKE_BUILD_TYPE=MinRelSize -G "Unix Makefiles" -DCMAKE_INSTALL_PREFIX=""
    make -j16

To install for development (Windows, PPSSPP with installed.txt):

    make install DESTDIR="${env:UserProfile}/Documents/PPSSPP"

To install for development (Windows, PPSSPP without installed.txt):

    make install DESTDIR="C:/Program Files/ppsspp/memstick"

To package before release:

    make install DESTDIR=dist

