#include <chantage/chantage.h>

static uint8_t gTitleText[] = {
#include "title_text.inc"
};

typedef struct
{
    uint32_t    enabled;
    uint32_t    textureID;
    uint32_t    unk0;
    uint32_t    unk1;
    uint32_t    counter;
    uint32_t    unk2;
    uint32_t    x;
    uint32_t    y;
    uint32_t    unk3;
} __attribute__ ((packed)) TextureDescriptor;

typedef void (*pfnCreateDrawContext)(uint32_t);
typedef uint32_t (*pfnLoadTextureDescriptor)(TextureDescriptor*, void*);
typedef void (*pfn_Unk08833d40)(uint16_t*, uint32_t);
typedef void (*pfn_Unk08833a80)(uint32_t);

static const pfnCreateDrawContext CreateDrawContext = (pfnCreateDrawContext)0x088d81c0;
static const pfnCreateDrawContext CreateDrawContext2 = (pfnCreateDrawContext)0x088d6c40;
static const pfnLoadTextureDescriptor LoadTextureDescriptor = (pfnLoadTextureDescriptor)0x088d9b40;
static const pfn_Unk08833d40 _Unk08833d40 = (pfn_Unk08833d40)0x08833d40;
static const pfn_Unk08833a80 _Unk08833a80 = (pfn_Unk08833a80)0x08833a80;

static void DrawTitleText()
{
    uint8_t* base;
    uint8_t value;

    base = (uint8_t*)0x09b27190;
    for (uint32_t j = 0; j < 16; ++j)
    {
        for (uint32_t i = 0; i < 128; ++i)
        {
            value = gTitleText[i + j * 128];
            if (value)
            {
                base[i + 20 + 512 * (j + 20)] = value;
            }
        }
    }
}

uint32_t SetupTitleScreen(uint32_t unkArg)
{
    TextureDescriptor* desc;
    uint32_t* tmpPtr;
    uint32_t tmp;
    uint32_t tmp2;
    uint32_t tmp3;
    uint16_t unk1;
    uint16_t unk2;
    uint16_t unk3;
    uint16_t unk4;

    uint32_t x;
    uint32_t y;

    DrawTitleText();

    tmpPtr = (uint32_t*)0x092efb74;
    *tmpPtr = ((*tmpPtr) & 0xffffdfff) | 0x00001000;
    CreateDrawContext(0u);

    unk1 = 0;
    unk2 = 0;
    unk3 = 0x140;
    unk4 = 0xF0;

    if ((*(uint32_t*)0x09384408) != 0)
    {
        unk2 = 0xF0;
    }

    _Unk08833d40(&unk1, *(uint32_t*)0x092f7b84);
    _Unk08833a80(0u);

    /* render copyright */
    tmp = LoadTextureDescriptor((void*)0x092eeb14, (void*)0x092eeb94);
    tmpPtr = (uint32_t*)0x92ee960;
    tmp2 = *(uint32_t*)0x092eeaf0;
    tmpPtr[tmp2 * 25] = tmp;

    desc = ((TextureDescriptor*)0x92eef20) + tmp;
    desc->textureID = 0x11;
    desc->unk0 = 0x04;
    desc->unk1 = 0x00;
    desc->counter = 0x00;
    desc->x = 0x00;
    desc->y = 0xFA;

    x = 0xB9;
    y = 0xBA;

    for (uint32_t i = 0; i < 4; ++i)
    {
        tmp = LoadTextureDescriptor((void*)0x092eeb14, (void*)0x092eeb94);
        tmpPtr = (uint32_t*)0x92ee960;
        tmp2 = *(uint32_t*)0x092eeaf0;
        tmpPtr[tmp2 * 25 + i + 1] = tmp;
        desc = ((TextureDescriptor*)0x92eef20) + tmp;
        desc->unk0 = 4;
        desc->unk1 = 0x00;
        desc->counter = 0x00;

        switch (i)
        {
            case 0:
                desc->textureID = 3;
                desc->x = 0xcc;
                desc->y = 0xb9;
                break;
            case 1:
                desc->textureID = 4;
                desc->x = 0xcc;
                desc->y = 0xcc;
                break;
            case 2:
                desc->textureID = 5;
                desc->x = 0xcc;
                desc->y = 0xde;
                break;
            case 3:
                desc->textureID = 6;
                desc->x = 0x00;
                desc->y = 0x00;
                break;
        }
    }

    tmp = LoadTextureDescriptor((void*)0x092eeb14, (void*)0x092eeb94);
    tmpPtr = (uint32_t*)0x92ee984;
    tmp2 = *(uint32_t*)0x092eeaf0;
    tmpPtr[tmp2 * 25] = tmp;
    desc = ((TextureDescriptor*)0x92eef20) + tmp;
    desc->textureID = 0x13;
    desc->unk0 = 0x04;
    tmpPtr = (uint32_t*)0x092eef20;
    tmpPtr[tmp * 9] |= 0x10;
    desc->counter = 0;
    desc->unk1 = 0x00;
    desc->x = 0x60;
    desc->y = 0x58;

    if ((*((uint32_t*)0x092efb74) & 0x40) != 0)
    {
        CreateDrawContext2(0x20);
    }


    /* Render everything else ... */

    tmpPtr = (uint32_t*)0x092ee974;
    tmp2 = *(uint32_t*)0x092eeaf0;
    tmpPtr[tmp2 * 25] = 0x00;
    tmpPtr = (uint32_t*)0x092ee978;
    tmpPtr[tmp2 * 25] = unkArg;
    tmpPtr = (uint32_t*)0x092ee97c;
    tmp = tmpPtr[tmp2 * 25] = *(uint32_t*)0x0934d5e4;
    tmpPtr = (uint32_t*)0x092ee980;
    tmpPtr[tmp2 * 25] = 0x00;
    tmpPtr = (uint32_t*)0x092ee994;
    tmpPtr[tmp2 * 25] = 0x00;
    tmpPtr = (uint32_t*)0x092ee964;
    tmp = tmpPtr[tmp2 * 25 + tmp];
    desc = ((TextureDescriptor*)0x092eef20) + tmp;
    desc->unk2 = 0x09;
    tmpPtr = (uint32_t*)0x092eeaf4;
    tmpPtr[tmp2] = 0x02;
    *((uint32_t*)0x092eeaf0) = tmp2 + 1;

    return 0x05;
}

void HookTitleScreen()
{
    ReplaceFunction((void*)0x088dda80, &SetupTitleScreen);
}
