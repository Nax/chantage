#ifndef INCLUDED_PSP_MODULE_INFO_H
#define INCLUDED_PSP_MODULE_INFO_H

typedef struct _scemoduleinfo {
    unsigned short      modattribute;
    unsigned char       modversion[2];
    char                modname[27];
    char                terminal;
    void*               gp_value;
    void*               ent_top;
    void*               ent_end;
    void*               stub_top;
    void*               stub_end;
} _sceModuleInfo;

typedef const _sceModuleInfo SceModuleInfo;

#define PSP_MODULE_INFO(name, attributes, major_version, minor_version) \
SceModuleInfo module_info                                               \
        __attribute__((section(".rodata.sceModuleInfo"),                \
            aligned(16), unused)) = {                                   \
            attributes, { minor_version, major_version }, name, 0, 0,   \
            0, 0,                                                       \
            0, 0                                                        \
}

#endif
