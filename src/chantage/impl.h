#include <chantage/chantage.h>

#define BREAKPOINT      __asm__ __volatile__ ("break\r\n");

typedef void (Mod)(PFNLOADFUNCTIONPROC*);

void    LoadMods();
void    InitFunctionRegistry();
void*   LoadFunction(const char* str);
void*   RegisterFunction(const char* str, void* fn);
void    HookFunctions();
void    ReplaceFunction(void* existingFunction, const void* newFunction);
void    ReplaceHi16(void* dst, const void* newPtr);
void    ReplaceLo16(void* dst, const void* newPtr);
void    ReplaceLoadAddress(void* dst, const void* newPtr);

/*
 * items.c
 */

void                InitItems(void);
const char*         GetItemName(u16 itemID);
const char*         GetItemDescription(u16 itemID);
ItemData*           GetItemData(u16 itemID);
ItemWeaponData*     GetItemWeaponData(u16 itemID);
ItemBlockData*      GetItemShieldData(u16 itemID);
ItemArmorData*      GetItemArmorData(u16 itemID);
ItemBlockData*      GetItemAccessoryData(u16 itemID);
ItemChemistData*    GetItemChemistData(u16 itemID);
int                 IsItemValid(u16 itemID);
size_t              ItemCount(void);
u16                 CreateItem(void);

/*
 * text.c
 */

void        InitText(void);
const char* GetText(const char* base, uint32_t id);
const char* GetTextCompat(const char* base, uint32_t id);
uint32_t    GetTextLength(const char* str);
