#include <chantage/chantage.h>

typedef void (Mod)(PFNLOADFUNCTIONPROC*);

void    LoadMods();
void    InitFunctionRegistry();
void*   LoadFunction(const char* str);
void*   RegisterFunction(const char* str, void* fn);
void    HookFunctions();
void    ReplaceFunction(void* existingFunction, const void* newFunction);

/*
 * items.c
 */

void                InitItems(void);
ItemData*           GetItemData(u16 itemID);
ItemWeaponData*     GetItemWeaponData(u16 itemID);
ItemBlockData*      GetItemShieldData(u16 itemID);
ItemArmorData*      GetItemArmorData(u16 itemID);
ItemBlockData*      GetItemAccessoryData(u16 itemID);
ItemChemistData*    GetItemChemistData(u16 itemID);
int                 IsItemValid(u16 itemID);
size_t              ItemCount(void);
u16                 CreateItem(void);
