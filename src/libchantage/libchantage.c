#include <chantage/psp.h>

void* SystemAlloc(size_t size)
{
    SceUID id = sceKernelAllocPartitionMemory(2, "X", 0, size + 4, NULL);
    void* base = (char*)sceKernelGetBlockHeadAddr(id) + 4;
    ((SceUID*)base)[-1] = id;
    return base;
}

void SystemFree(void* ptr)
{
    SceUID id;

    id = ((SceUID*)ptr)[-1];
    sceKernelFreePartitionMemory(id);
}
