#include <chantage/impl.h>

#define OLD_ITEM_COUNT  0x100
#define NEW_ITEM_COUNT  0x13c

static struct {
    size_t      extraItemSize;
    size_t      extraItemCapacity;
    ItemData*   extraItem;
} gItemRegistry;

static const u32 gPatchList[] = {
    0x08878d5c,
    0x08883700,
    0x08970cb4,
    0x08974404,
    0x0898b7e8,
    0x0898c67c,
    0x0898d508,
    0x0898ea34,
    0x08990808,
    0x08990dbc,
    0x089a0618,
    0x089a1808,
    0x089a2878,
    0x08a18c10,
    0x08a18e54,
    0x08a18f54,
    0x08a190d0,
    0x08a191b4,
    0x08a192d0,
    0x08a193b4,
    0x08a194d0,
    0x08a195b4,
    0x08a196d0,
    0x08a197b4,
    0x08a198d0,
    0x08a199b4,
    0x08a34710,
    0x08a34728,
    0x08a34758,
    0x08a34770
};

void InitItems(void)
{
    gItemRegistry.extraItemSize = 0;
    gItemRegistry.extraItemCapacity = 8;
    gItemRegistry.extraItem = malloc(sizeof(ItemData) * gItemRegistry.extraItemCapacity);

    ReplaceFunction((void*)0x08a18600, &GetItemData);
    ReplaceFunction((void*)0x08a18dc0, &IsItemValid);
}

ItemData* GetItemData(u16 itemID)
{
    ItemData* base;

    if (itemID < OLD_ITEM_COUNT)
    {
        base = (ItemData*)0x08b29288;
    }
    else if (itemID < NEW_ITEM_COUNT)
    {
        base = (ItemData*)0x08a5adac;
        itemID -= OLD_ITEM_COUNT;
    }
    else
    {
        base = gItemRegistry.extraItem;
        itemID -= NEW_ITEM_COUNT;
    }
    return base + itemID;
}

int IsItemValid(u16 itemID)
{
    if (itemID == 0x00 || itemID == 0xfe || itemID == 0xff)
        return 0;
    if (itemID >= ItemCount())
        return 0;
    return 1;
}

size_t ItemCount(void)
{
    return 0x13C + gItemRegistry.extraItemSize;
}

u16 CreateItem(void)
{
    size_t newCapacity;
    ItemData* newData;
    u16 itemID;

    if (gItemRegistry.extraItemSize == gItemRegistry.extraItemCapacity)
    {
        newCapacity = gItemRegistry.extraItemCapacity;
        newCapacity += newCapacity / 2;
        newData = malloc(newCapacity * sizeof(ItemData));
        memcpy(newData, gItemRegistry.extraItem, gItemRegistry.extraItemSize * sizeof(ItemData));
        free(gItemRegistry.extraItem);
        gItemRegistry.extraItem = newData;
        gItemRegistry.extraItemCapacity = newCapacity;
    }
    memset(gItemRegistry.extraItem + gItemRegistry.extraItemSize, 0, sizeof(ItemData));
    itemID = NEW_ITEM_COUNT + gItemRegistry.extraItemSize;
    gItemRegistry.extraItemSize++;
    for (size_t i = 0; i < (sizeof(gPatchList) / sizeof(*gPatchList)); ++i)
    {
        *((u16*)gPatchList[i]) = (u16)ItemCount();
        sceKernelDcacheWritebackRange((void*)gPatchList[i], 2);
    }
    return itemID;
}
