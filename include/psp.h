#ifndef PSP_H
#define PSP_H

#include <stddef.h>
#include <stdint.h>

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

typedef void* (*pfn_malloc_r)(const void* reent, size_t size);
typedef void  (*pfn_free_r)(const void* reent, void* ptr);

static const pfn_malloc_r   _malloc_r = (void*)(0x0880bd40);
static const pfn_free_r     _free_r =   (void*)(0x0880ad24);

static const void* sReent = (void*)0x08a71f38;

#define malloc(sz)  (_malloc_r(sReent, sz))
#define free(ptr)   (_free_r(sReent, ptr))

#endif
