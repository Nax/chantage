#include <chantage/impl.h>

#define OLD_ITEM_COUNT  0x100
#define NEW_ITEM_COUNT  0x13c

static struct {
    size_t      extraItemSize;
    size_t      extraItemCapacity;
    ItemData*   extraItem;
} gItemRegistry;

void InitItems(void)
{
    gItemRegistry.extraItemSize = 0;
    gItemRegistry.extraItemCapacity = 8;
    gItemRegistry.extraItem = malloc(sizeof(ItemData) * gItemRegistry.extraItemCapacity);

    ReplaceFunction((void*)0x08a18600, &GetItemData);
    ReplaceFunction((void*)0x08a18dc0, &IsItemInvalid);
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

int IsItemInvalid(u16 itemID)
{
    if (itemID == 0x00 || itemID == 0xfe || itemID == 0xff)
        return 1;
    if (itemID >= ItemCount())
        return 1;
    return 0;
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
    itemID = NEW_ITEM_COUNT + gItemRegistry.extraItemSize;
    gItemRegistry.extraItemSize++;
    return itemID;
}
