#include <chantage/chantage.h>

PSP_MODULE_INFO("Slowdown Fix", 0, 0, 0);

int dummy = 0;

void _start(PFNLOADFUNCTIONPROC* LoadFunction)
{
    dummy = 1;

    /*
    *((uint8_t*)0x08a0ef80) = 0x02;
    *((uint8_t*)0x08a0ef90) = 0x03;
    *((uint8_t*)0x08a0ef9c) = 0x02;
    */
}
