#include <chantage/chantage.h>

typedef void (Mod)(PFNLOADFUNCTIONPROC*);

void    InitFunctionRegistry();
void*   LoadFunction(const char* str);
void*   RegisterFunction(const char* str, void* fn);
