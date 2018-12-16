#include <chantage/impl.h>

static const u32 sInventoryPatchHi16[] = {
    0x08878CE8, 0x08878CFC, 0x08878D10, 0x08878F30,
    0x08883600, 0x0888363C, 0x088B96D0, 0x088C7A40,
    0x088D1FA4, 0x088D546C, 0x08918C88, 0x08927CAC,
    0x0892C524, 0x0894C4A0, 0x0894CF3C, 0x0894DFCC,
    0x08954CDC, 0x08970B20, 0x08970B88, 0x0898B758,
    0x0898B850, 0x0898C92C, 0x0898CAF0, 0x0898EC18,
    0x0898ECE0, 0x0898F128, 0x0898FAC0, 0x0898FB48,
    0x0899004C, 0x0899013C, 0x08990190, 0x08990320,
    0x089903E4, 0x08990614, 0x0899065C, 0x08990FF4,
    0x08991048, 0x089A05E0, 0x089A0710, 0x089A2058,
    0x089A2180, 0x089A2200, 0x089AB24C, 0x089B0F38,
    0x089B0FBC, 0x089D92EC, 0x08A0BB80, 0x08A0C100,
    0x08A29C24, 0x08A29D60
};

static const u32 sInventoryPatchLo16[] = {
    0x08878CF0, 0x08878D04, 0x08878D18, 0x08878F38,
    0x08883608, 0x08883640, 0x088B96F0, 0x088C7A48,
    0x088D1FB4, 0x088D5478, 0x08918C90, 0x08927CC4,
    0x0892C6F0, 0x0894C4E4, 0x0894CF44, 0x0894DFD0,
    0x08954CE0, 0x08970B2C, 0x08970B8C, 0x0898B760,
    0x0898B85C, 0x0898C938, 0x0898CAFC, 0x0898EC24,
    0x0898ECEC, 0x0898F134, 0x0898FAC4, 0x0898FB4C,
    0x08990058, 0x08990144, 0x089901A4, 0x08990324,
    0x089903E8, 0x08990620, 0x08990668, 0x08990FFC,
    0x0899105C, 0x089A0630, 0x089A071C, 0x089A2064,
    0x089A2184, 0x089A2204, 0x089AB250, 0x089B0F3C,
    0x089B0FC4, 0x089D9304, 0x08A0BB84, 0x08A0C104,
    0x08A29C2C, 0x08A29D68
};

static const u32 sInventoryPatchChemistHi16[] = {
    0x08883674, 0x08883680, 0x0888368C, 0x08883694,
    0x0888369C, 0x088836A4, 0x088836AC, 0x088836B4,
    0x088836BC, 0x088836C4, 0x088836CC, 0x088836D4,
    0x088836DC, 0x088836E4
};

static const u32 sInventoryPatchChemistLo16[] = {
    0x08883678, 0x08883684, 0x08883690, 0x08883698,
    0x088836A0, 0x088836A8, 0x088836B0, 0x088836B8,
    0x088836C0, 0x088836C8, 0x088836D0, 0x088836D8,
    0x088836E0, 0x088836E8
};

void InitInventory(void)
{
    gContext.inventory = malloc(gContext.items.itemSize);
    memset(gContext.inventory, 0, gContext.items.itemSize);
    for (size_t i = 0; i < sizeof(sInventoryPatchHi16) / sizeof(*sInventoryPatchHi16); ++i)
        ReplaceHi16((void*)sInventoryPatchHi16[i], gContext.inventory);
    for (size_t i = 0; i < sizeof(sInventoryPatchLo16) / sizeof(*sInventoryPatchLo16); ++i)
        ReplaceLo16((void*)sInventoryPatchLo16[i], gContext.inventory);

    /* Fixup inventory+1 pointers */
    ReplaceHi16((void*)0x0898EA00, gContext.inventory + 1);
    ReplaceLo16((void*)0x0898EA10, gContext.inventory + 1);

    /* Fixup chemist item pointers */
    for (size_t i = 0; i < 0x0e; ++i)
    {
        ReplaceHi16((void*)sInventoryPatchChemistHi16[i], gContext.inventory + 0xf0 + i);
        ReplaceLo16((void*)sInventoryPatchChemistLo16[i], gContext.inventory + 0xf0 + i);
    }
}
