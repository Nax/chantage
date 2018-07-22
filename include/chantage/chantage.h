#ifndef CHANTAGE_H
#define CHANTAGE_H

#include <chantage/psp.h>
#include <chantage/psp_module_info.h>

#define PACKED  __attribute__ ((packed))

typedef int8_t      i8;
typedef int16_t     i16;
typedef int32_t     i32;

typedef uint8_t     u8;
typedef uint16_t    u16;
typedef uint32_t    u32;

typedef struct {
    u8      palette;
    u8      gfx;
    u8      level;
    u8      flags;
    u8      attrID;
    u8      type;
    u8      unk1;
    u8      sia;
    u16     price;
    u8      shop;
    u8      unk2;
} PACKED ItemData;

/*
 * items.c
 */
typedef ItemData*   (PFNGETITEMDATAPROC)(u16);
typedef int         (PFNISITEMINVALIDPROC)(u16);
typedef size_t      (PFNITEMCOUNTPROC)();
typedef u16         (PFNCREATEITEMPROC)();

typedef void* (PFNLOADFUNCTIONPROC)(const char*);
typedef void* (PFNREGISTERFUNCTIONPROC)(const char*, void*);
typedef void  (PFNREPLACEFUNCTIONPROC)(void*, const void*);

#endif
