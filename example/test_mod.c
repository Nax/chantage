#include <chantage/chantage.h>

PSP_MODULE_INFO("Test Mod", 0, 0, 0);

PFNGETITEMDATAPROC* GetItemData = NULL;
PFNCREATEITEMPROC* CreateItem = NULL;

int dummy;

void _start(PFNLOADFUNCTIONPROC* LoadFunction)
{
    dummy = 1;
    /*
    u16 itemID;
    ItemData* excalibur;
    ItemData* item;

    GetItemData = LoadFunction("GetItemData");
    CreateItem = LoadFunction("CreateItem");

    itemID = CreateItem();
    excalibur = GetItemData(0x23);
    item = GetItemData(itemID);
    memcpy(item, excalibur, sizeof(ItemData));
    item->basic.palette = 0x14;
    item->weapon.unk[0x04] = 99;
    */
}
