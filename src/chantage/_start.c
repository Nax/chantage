#include <chantage/chantage.h>

PSP_MODULE_INFO("Chantage", 0, 0, 0);

static void loop()
{
    for (;;) {}
}

void _start()
{
    ReplaceFunction((void*)0x088DDA80, &loop);
    LoadMods();
}
