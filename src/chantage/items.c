#include <chantage/impl.h>

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
    ChantageItemRegistry* registry;

    registry = &gContext.items;
    const char* strBase;
    uint32_t    strLength;

    /* Init the registry */
    registry->itemSize = 0x13c;
    registry->itemCapacity = 0x13c;
    registry->data = SystemAlloc(sizeof(ItemData) * registry->itemCapacity);
    memset(registry->data, 0, sizeof(ItemData) * registry->itemCapacity);

    /* Copy basic item data */
    for (size_t i = 0; i < 0x100; ++i)
        memcpy(&registry->data[i].basic, ((ItemBasicData*)0x08b29288) + i, sizeof(ItemBasicData));
    for (size_t i = 0; i < 0x3c; ++i)
        memcpy(&registry->data[0x100 + i].basic, ((ItemBasicData*)0x08a5adac) + i, sizeof(ItemBasicData));

    /* Copy names */
    strBase = (const char*)(0x08a935fd);
    for (size_t i = 0; i < 0x13c; ++i)
    {
        strLength = GetTextLength(strBase) + 1;
        registry->data[i].name = malloc(strLength);
        memcpy(registry->data[i].name, strBase, strLength);
        strBase += strLength;
        registry->data[i].name[0]++; // DEBUG
    }

    /* Copy descriptions */
    for (size_t i = 0; i < 0x13c; ++i)
    {
        strBase = GetText((const char*)0x08ab027b, i);
        strLength = 0;
        if (*strBase == (char)0xe3)
        {
            while (*strBase != (char)0xf8)
                strBase++;
            strBase++;
        }
        for (;;)
        {
            if (strBase[strLength] == (char)0xfe || strBase[strLength] == (char)0xff)
                break;
            if (strBase[strLength] == (char)0xe3 || strBase[strLength + 1] == (char)0x08)
                break;
            strLength++;
        }
        while (strLength)
        {
            if (strBase[strLength - 1] == (char)0xf8)
                strLength--;
            else
                break;
        }
        registry->data[i].desc = malloc(strLength + 1);
        memcpy(registry->data[i].desc, strBase, strLength);
        registry->data[i].desc[strLength] = 0xfe;
    }

    /* Copy weapon data */
    for (size_t i = 0; i < 0x80; ++i)
        memcpy(&registry->data[i].weapon, ((ItemWeaponData*)0x08b29e88) + i, sizeof(ItemWeaponData));
    for (size_t i = 0; i < 0x16; ++i)
        memcpy(&registry->data[0x100 + i].weapon, ((ItemWeaponData*)0x08a5b07c) + i, sizeof(ItemWeaponData));

    /* Copy shield data */
    for (size_t i = 0; i < 0x10; ++i)
        memcpy(&registry->data[0x80 + i].block, ((ItemBlockData*)0x08b2a288) + i, sizeof(ItemBlockData));
    for (size_t i = 0; i < 0x2; ++i)
        memcpy(&registry->data[0x120 + i].block, ((ItemBlockData*)0x08a5b17c) + i, sizeof(ItemBlockData));

    /* Copy armor data */
    for (size_t i = 0; i < 0x40; ++i)
        memcpy(&registry->data[0x90 + i].armor, ((ItemArmorData*)0x08b2a2a8) + i, sizeof(ItemArmorData));
    for (size_t i = 0; i < 0xe; ++i)
        memcpy(&registry->data[0x124 + i].armor, ((ItemArmorData*)0x08a5b184) + i, sizeof(ItemArmorData));

    /* Copy accessory data */
    for (size_t i = 0; i < 0x20; ++i)
        memcpy(&registry->data[0xd0 + i].accessory, ((ItemBlockData*)0x08b2a328) + i, sizeof(ItemBlockData));

    /* Copy chemist data */
    for (size_t i = 0; i < 0xe; ++i)
        memcpy(&registry->data[0xf0 + i].chemist, ((ItemChemistData*)0x08b2a368) + i, sizeof(ItemChemistData));

    /* Copy item attributes */
    for (size_t i = 0; i < 0x13c; ++i)
    {
        ItemAttributes* attr;
        ItemData* item = registry->data + i;
        u16 attrID = item->basic.attrID;

        if (attrID >= 0x50)
            attr = ((ItemAttributes*)0x08a5b1b8) + (i - 0x50);
        else
            attr = ((ItemAttributes*)0x08b2a694) + i;
        memcpy(&item->attributes, attr, sizeof(ItemAttributes));
    }

    ReplaceFunction((void*)0x08a18600, &GetItemData);
    ReplaceFunction((void*)0x08a18680, &GetItemWeaponData);
    ReplaceFunction((void*)0x08a186c0, &GetItemShieldData);
    ReplaceFunction((void*)0x08a18700, &GetItemArmorData);
    ReplaceFunction((void*)0x08a18740, &GetItemAccessoryData);
    ReplaceFunction((void*)0x08a18780, &GetItemChemistData);
    ReplaceFunction((void*)0x08a18dc0, &IsItemValid);
    ReplaceFunction((void*)0x08A18E40, &IsItemInCategory);
    ReplaceFunction((void*)0x08A18F40, &IsItemInCategory);
}

const char* GetItemName(u16 itemID)
{
    return gContext.items.data[itemID].name;
}

const char* GetItemDescription(u16 itemID)
{
    return gContext.items.data[itemID].desc;
}

ItemData* GetItemData(u16 itemID)
{
    return gContext.items.data + itemID;
}

ItemWeaponData* GetItemWeaponData(u16 itemID)
{
    if (itemID >= gContext.items.itemSize)
        return NULL;
    ItemData* item = &gContext.items.data[itemID];
    if (item->basic.flags & 0x80)
        return &item->weapon;
    return NULL;
}

ItemBlockData* GetItemShieldData(u16 itemID)
{
    if (itemID >= gContext.items.itemSize)
        return NULL;
    ItemData* item = &gContext.items.data[itemID];
    if (item->basic.flags & 0x40)
        return &item->block;
    return NULL;
}

ItemArmorData* GetItemArmorData(u16 itemID)
{
    if (itemID >= gContext.items.itemSize)
        return NULL;
    ItemData* item = &gContext.items.data[itemID];
    if (item->basic.flags & 0x30)
        return &item->armor;
    return NULL;
}

ItemBlockData* GetItemAccessoryData(u16 itemID)
{
    if (itemID >= gContext.items.itemSize)
        return NULL;
    ItemData* item = &gContext.items.data[itemID];
    if (item->basic.flags & 0x08)
        return &item->accessory;
    return NULL;
}

ItemChemistData* GetItemChemistData(u16 itemID)
{
    if (itemID >= gContext.items.itemSize)
        return NULL;
    ItemData* item = &gContext.items.data[itemID];
    if (!(item->basic.flags & 0xf8))
        return &item->chemist;
    return NULL;
}

int IsItemInCategory(u16 itemID, int category)
{
    ItemData* item = &gContext.items.data[itemID];
    switch (category)
    {
    case 0:
        return !!(item->basic.flags & 0x80) && (item->basic.type != 33 && item->basic.type != 32);
    case 2:
        return !!(item->basic.flags & 0x40);
    case 3:
        return !!(item->basic.flags & 0x20);
    case 4:
        return !!(item->basic.flags & 0x10);
    case 5:
        return !!(item->basic.flags & 0x08);
    }
    return 0;
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
    return gContext.items.itemSize;
}

u16 CreateItem(void)
{
    size_t newCapacity;
    ItemData* newData;
    u16 itemID;

    if (gContext.items.itemSize == gContext.items.itemCapacity)
    {
        newCapacity = gContext.items.itemCapacity;
        newCapacity += newCapacity / 2;
        newData = SystemAlloc(newCapacity * sizeof(ItemData));
        memcpy(newData, gContext.items.data, gContext.items.itemSize * sizeof(ItemData));
        memset(newData + gContext.items.itemSize, 0, newCapacity - gContext.items.itemCapacity);
        SystemFree(gContext.items.data);
        gContext.items.data = newData;
        gContext.items.itemCapacity = newCapacity;
    }
    itemID = gContext.items.itemSize;
    gContext.items.itemSize++;
    for (size_t i = 0; i < (sizeof(gPatchList) / sizeof(*gPatchList)); ++i)
    {
        *((u16*)gPatchList[i]) = (u16)ItemCount();
        sceKernelDcacheWritebackRange((void*)gPatchList[i], 2);
    }
    return itemID;
}
