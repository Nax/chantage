#include <chantage/chantage.h>

typedef void (Mod)(PFNLOADFUNCTIONPROC*);

void    LoadMods();
void    InitFunctionRegistry();
void*   LoadFunction(const char* str);
void*   RegisterFunction(const char* str, void* fn);
void    HookFunctions();
void    ReplaceFunction(void* existingFunction, const void* newFunction);
