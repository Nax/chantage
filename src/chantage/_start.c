#include <chantage/impl.h>

PSP_MODULE_INFO("Chantage", 0, 0, 0);

ChantageContext gContext;

void HookTitleScreen();

void _start()
{
    InitFunctionRegistry();
    HookFunctions();
    HookTitleScreen();

    InitItems();
    LoadMods();
    InitInventory();
    InitText();
}
