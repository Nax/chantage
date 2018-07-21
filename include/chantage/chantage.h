#ifndef CHANTAGE_H
#define CHANTAGE_H

#include <chantage/psp.h>
#include <chantage/psp_module_info.h>

typedef void* (PFNLOADFUNCTIONPROC)(const char*);
typedef void* (PFNREGISTERFUNCTIONPROC)(const char*, void*);
typedef void  (PFNREPLACEFUNCTIONPROC)(void*, const void*);

#endif
