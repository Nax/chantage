#include <chantage/chantage.h>

typedef struct {
    usize       size;
    usize       capacity;
    usize       strSize;
    usize       strCapacity;
    char*       strTable;
    u32*        offTable;
    void**      fnTable;
} ChantageFunctionRegistry;

typedef struct {
    usize       itemSize;
    usize       itemCapacity;
    ItemData*   data;
    char*       names;
    usize       namesSize;
} ChantageItemRegistry;

typedef struct {
    ChantageFunctionRegistry    functions;
    ChantageItemRegistry        items;
    u8*                         inventory;
} ChantageContext;

extern ChantageContext gContext;

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
int                 IsItemInCategory(u16 itemID, int category);
int                 IsItemValid(u16 itemID);
usize               ItemCount(void);
u16                 CreateItem(void);

/*
 * text.c
 */

void        InitText(void);
const char* GetText(const char* base, u32 id);
const char* GetTextCompat(const char* base, u32 id);
u32         GetTextLength(const char* str);

/*
 * Inventory
 */
void        InitInventory(void);
