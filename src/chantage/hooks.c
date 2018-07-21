#include <chantage/impl.h>

void HookFunctions()
{
    RegisterFunction("LoadFunction", &LoadFunction);
    RegisterFunction("RegisterFunction", &RegisterFunction);
    RegisterFunction("ReplaceFunction", &ReplaceFunction);
}
