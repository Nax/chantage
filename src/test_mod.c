#include <chantage/chantage.h>

PSP_MODULE_INFO("Test Mod", 0, 0, 0);

PFNGETITEMDATAPROC* GetItemData = NULL;
PFNCREATEITEMPROC* CreateItem = NULL;

void _start(PFNLOADFUNCTIONPROC* LoadFunction)
{
    u16 itemID;
    ItemData* item;

    GetItemData = LoadFunction("GetItemData");
    CreateItem = LoadFunction("CreateItem");

    itemID = CreateItem();
    item = GetItemData(itemID);
    item->palette = 0x14;
    item->gfx = 0x18;
    item->level = 99;
    item->flags = 0x82;
    item->attrID = 0x23;
    item->type = 4;
    item->unk1 = 0;
    item->attrID = 3;
    item->price = 10000;
    item->shop = 0x14;
    item->unk2 = 0;
}
