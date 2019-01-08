#ifndef INCLUDED_PSP_MODULE_INFO_H
#define INCLUDED_PSP_MODULE_INFO_H

#include <chantage/types.h>
#include <chantage/util.h>

typedef struct {
    u16     modattribute;
    u8      modversion[2];
    char    modname[27];
    char    terminal;
    void*   gp_value;
    void*   ent_top;
    void*   ent_end;
    void*   stub_top;
    void*   stub_end;
} PACKED SceModuleInfo;

#if defined(__GNUC__)
# define PSP_MODULE_INFO(name, attributes, major_version, minor_version)    \
const SceModuleInfo module_info                                             \
        __attribute__((section(".rodata.sceModuleInfo"),                    \
            aligned(16), unused)) = {                                       \
            attributes, { minor_version, major_version }, name, 0, 0,       \
            0, 0,                                                           \
            0, 0                                                            \
}
#else
# define PSP_MODULE_INFO(name, attributes, major_version, minor_version)
#endif

#endif
