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
typedef void    (*pfnSceKernelDcacheWritebackRange)(void* base, size_t size);

static const pfnSceIoRead   sceIoRead   = (void*)0x08a4af3c;
static const pfnSceIoClose  sceIoClose  = (void*)0x08a4af4c;
static const pfnSceIoOpen   sceIoOpen   = (void*)0x08a4af6c;
static const pfnSceIoLseek  sceIoLseek  = (void*)0x08a4af74;
static const pfnSceKernelDcacheWritebackRange sceKernelDcacheWritebackRange = (void*)0x08a4b134;

typedef void* (*pfn_malloc_r)(const void* reent, size_t size);
typedef void  (*pfn_free_r)(const void* reent, void* ptr);

static const pfn_malloc_r   _malloc_r = (void*)(0x0880bd40);
static const pfn_free_r     _free_r =   (void*)(0x0880ad24);

static const void* sReent = (void*)0x08a71f38;

#define malloc(sz)  (_malloc_r(sReent, sz))
#define free(ptr)   (_free_r(sReent, ptr))

typedef char* (PFNSTRCATPROC)(char*, const char*);
typedef int (PFNSTRCMPPROC)(const char*, const char*);
typedef char* (PFNSTRCPYPROC)(char*, const char*);
typedef size_t (PFNSTRLENPROC)(const char*);

static const PFNSTRCATPROC* strcat = (const PFNSTRCATPROC*)0x0880f740;
static const PFNSTRCMPPROC* strcmp = (const PFNSTRCMPPROC*)0x0880f800;
static const PFNSTRCPYPROC* strcpy = (const PFNSTRCPYPROC*)0x0880f880;
static const PFNSTRLENPROC* strlen = (const PFNSTRLENPROC*)0x0880f940;

typedef void* (PFNMEMCHRPROC)(const void*, int, size_t);
typedef int (PFNMEMCMPPROC)(const void*, const void*, size_t);
typedef void* (PFNMEMCPYPROC)(void*, const void*, size_t);
typedef void* (PFNMEMMOVEPROC)(void*, const void*, size_t);
typedef void* (PFNMEMSETPROC)(void*, int, size_t);

static const PFNMEMCHRPROC* memchr = (const PFNMEMCHRPROC*)0x0880c540;
static const PFNMEMCMPPROC* memcmp = (const PFNMEMCMPPROC*)0x0880c640;
static const PFNMEMCPYPROC* memcpy = (const PFNMEMCPYPROC*)0x0880c700;
static const PFNMEMMOVEPROC* memmove = (const PFNMEMMOVEPROC*)0x0880c840;
static const PFNMEMSETPROC* memset = (const PFNMEMSETPROC*)0x0880cb80;

#endif
