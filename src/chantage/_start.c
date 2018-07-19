#include "chantage_impl.h"
#include <chantage/chantage.h>

PSP_MODULE_INFO("Chantage", 0, 0, 0);

void HookTitleScreen();

void _start()
{
    InitFunctionRegistry();
    HookTitleScreen();
    LoadMods();
}
