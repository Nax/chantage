#include <chantage/psp_module_info.h>

PSP_MODULE_INFO("Chantage", 0, 0, 0);

int foo[4];

void _start()
{
    foo[2] = 0x1111abcd;
    return;
}
