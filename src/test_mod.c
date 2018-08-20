#include <chantage/chantage.h>

PSP_MODULE_INFO("Test Mod", 0, 0, 0);

PFNGETITEMDATAPROC* GetItemData = NULL;
PFNCREATEITEMPROC* CreateItem = NULL;

void _start(PFNLOADFUNCTIONPROC* LoadFunction)
{
    u16 itemID;
    ItemData* excalibur;
    ItemData* item;

    GetItemData = LoadFunction("GetItemData");
    CreateItem = LoadFunction("CreateItem");

    itemID = CreateItem();
    excalibur = GetItemData(0x21);
    item = GetItemData(itemID);
    memcpy(item, excalibur, sizeof(ItemData));
    item->basic.palette = 0x14;
}
