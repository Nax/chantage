#ifndef CHANTAGE_H
#define CHANTAGE_H

#include <chantage/types.h>
#include <chantage/psp.h>
#include <chantage/psp_module_info.h>

/*
 * GCC is the only supported compiler,
 * this is mostly to fix static analysis.
 */
#if defined(__GNUC__)
# define PACKED  __attribute__ ((packed))
#else
# define PACKED
#endif

typedef struct {
    u8      palette;
    u8      gfx;
    u8      level;
    u8      flags;
    u8      unk0;
    u8      type;
    u8      unk1;
    u8      attrID;
    u16     price;
    u8      shop;
    u8      unk2;
} PACKED ItemBasicData;

typedef struct {
    u8    unk[8];
} PACKED ItemWeaponData;

typedef struct {
    u8  physicalBlock;
    u8  magicalBlock;
} PACKED ItemBlockData;

typedef struct {
    u8  hp;
    u8  mp;
} PACKED ItemArmorData;

typedef struct {
    u8  formula;
    u8  z;
    u8  status;
} PACKED ItemChemistData;

typedef struct {
    u8  pa;
    u8  ma;
    u8  speed;
    u8  move;
    u8  jump;
    u8  statusPermanent[5];
    u8  statusImmunity[5];
    u8  statusStart[5];
    u8  eAbsorb;
    u8  eCancel;
    u8  eHalf;
    u8  eWeak;
    u8  eStrengthen;
} PACKED ItemAttributes;

typedef struct {
    ItemBasicData   basic;
    union {
        ItemWeaponData      weapon;
        ItemBlockData       block;
        ItemArmorData       armor;
        ItemBlockData       accessory;
        ItemChemistData     chemist;
    };
    ItemAttributes  attributes;
    u8              zero;
    char*           name;
    char*           desc;
} PACKED ItemData;

/*
 * items.c
 */
typedef const char*         (PFNGETITEMNAMEPROC)(u16);
typedef ItemData*           (PFNGETITEMDATAPROC)(u16);
typedef ItemWeaponData*     (PFNGETITEMWEAPONDATAPROC)(u16);
typedef ItemBlockData*      (PFNGETITEMSHIELDDATAPROC)(u16);
typedef ItemArmorData*      (PFNGETITEMARMORDATAPROC)(u16);
typedef ItemBlockData*      (PFNGETITEMACCESSORYDATAPROC)(u16);
typedef ItemChemistData*    (PFNGETITEMCHEMISTDATAPROC)(u16);

typedef int             (PFNISITEMVALIDPROC)(u16);
typedef size_t          (PFNITEMCOUNTPROC)();
typedef u16             (PFNCREATEITEMPROC)();

typedef void* (PFNLOADFUNCTIONPROC)(const char*);
typedef void* (PFNREGISTERFUNCTIONPROC)(const char*, void*);
typedef void  (PFNREPLACEFUNCTIONPROC)(void*, const void*);

#endif
