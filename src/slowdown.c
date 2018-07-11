#include <stdint.h>
#include <chantage/psp_module_info.h>

PSP_MODULE_INFO("Slowdown Fix", 0, 0, 0);

int dummy = 0;

void _start(void* unused)
{
    (void)unused;

    dummy = 1;
    *((uint8_t*)0x08a0ef80) = 0x02;
    *((uint8_t*)0x08a0ef90) = 0x03;
    *((uint8_t*)0x08a0ef9c) = 0x02;
}
