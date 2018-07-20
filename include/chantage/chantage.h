#ifndef CHANTAGE_H
#define CHANTAGE_H

#include <chantage/psp.h>
#include <chantage/psp_module_info.h>

void LoadMods();
void ReplaceFunction(void* existingFunction, void* newFunction);

typedef void* (PFNLOADFUNCTIONPROC)(const char*);
typedef void* (PFNREGISTERFUNCTIONPROC)(const char*, void*);


#endif
