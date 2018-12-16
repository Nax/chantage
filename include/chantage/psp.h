#ifndef PSP_H
#define PSP_H

#include <stddef.h>
#include <stdint.h>

/*
 * LibChantage
 */

#define SCE_O_RDONLY    0x01

#define SEEK_SET    0
#define SEEK_CUR    1
#define SEEK_END    2

typedef uint32_t    SceUID;
typedef uint32_t    SceMode;
typedef int64_t     SceOff;

void*   memset(void*, int, size_t);
void*   memmove(void*, const void*, size_t);
int     memcmp(const void*, const void*, size_t);
void*   memcpy(void* dst, const void* src, size_t len);
void*   memchr(const void*, int, size_t);

char*   strcat(char*, const char*);
int     strcmp(const char*, const char*);
char*   strcpy(char*, const char*);
size_t  strlen(const char*);

void*   malloc(size_t);
void    free(void*);

int     sceIoRead(SceUID fd, void* buffer, size_t size);
void    sceIoClose(SceUID fd);
SceUID  sceIoOpen(const char* path, int flags, SceMode mode);
SceOff  sceIoLseek(SceUID fd, SceOff off, int whence);
void    sceKernelDcacheWritebackRange(void* base, size_t size);
SceUID  sceKernelAllocPartitionMemory(SceUID partitionId, const char* name, int type, size_t size, void* addr);
int     sceKernelFreePartitionMemory(SceUID blockId);
void*   sceKernelGetBlockHeadAddr(SceUID blockid);

void*   SystemAlloc(size_t size);
void    SystemFree(void* ptr);

#endif
