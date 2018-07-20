#include <chantage/chantage.h>

void    InitFunctionRegistry();
void*   LoadFunction(const char* str);
void*   RegisterFunction(const char* str, void* fn);
