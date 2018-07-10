#ifndef CHANTAGE_LOADER_H
#define CHANTAGE_LOADER_H

#include <stddef.h>
#include <stdint.h>
#include <elf.h>

#define CHANTAGE_PATH   "ms0:/PSP/GAME/ULUS10297/chantage.prx"

#define SCE_O_RDONLY    0x01

#define SEEK_SET    0
#define SEEK_CUR    1
#define SEEK_END    2

typedef uint32_t    SceUID;
typedef uint32_t    SceMode;
typedef int64_t     SceOff;

typedef int     (*pfnSceIoRead)(SceUID fd, void* buffer, size_t size);
typedef void    (*pfnSceIoClose)(SceUID fd);
typedef SceUID  (*pfnSceIoOpen)(const char* path, int flags, SceMode mode);
typedef SceOff  (*pfnSceIoLseek)(SceUID fd, SceOff off, int whence);

static const pfnSceIoRead   sceIoRead   = (void*)0x08a4af3c;
static const pfnSceIoClose  sceIoClose  = (void*)0x08a4af4c;
static const pfnSceIoOpen   sceIoOpen   = (void*)0x08a4af6c;
static const pfnSceIoLseek  sceIoLseek  = (void*)0x08a4af74;

void*   malloc(size_t size);
void    free(void* ptr);

void elfParseHeader(Elf32_Ehdr* ehdr, SceUID file);

#endif
