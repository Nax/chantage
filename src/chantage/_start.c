#include <chantage/impl.h>

PSP_MODULE_INFO("Chantage", 0, 0, 0);

void HookTitleScreen();

void _start()
{
    InitFunctionRegistry();
    HookFunctions();
    HookTitleScreen();
    LoadMods();
}
