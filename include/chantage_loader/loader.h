#ifndef CHANTAGE_LOADER_H
#define CHANTAGE_LOADER_H

#include <stddef.h>
#include <stdint.h>

#define CHANTAGE_PATH   "ms0:/PSP/GAME/ULUS10297/chantage.elf"

#define SCE_O_RDONLY    0x01

typedef uint32_t    SceUID;
typedef uint32_t    SceMode;

typedef void    (*pfnSceIoClose)(SceUID uid);
typedef SceUID  (*pfnSceIoOpen)(const char* path, int flags, SceMode mode);

static const pfnSceIoClose  sceIoClose  = (void*)0x08a4af4c;
static const pfnSceIoOpen   sceIoOpen   = (void*)0x08a4af6c;

void*   malloc(size_t size);
void    free(void* ptr);

#endif
