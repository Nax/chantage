#ifndef CHANTAGE_H
#define CHANTAGE_H

#include <psp.h>
#include <chantage/psp_module_info.h>

void LoadMods();
void ReplaceFunction(void* existingFunction, void* newFunction);

#endif
