#include <chantage/chantage.h>

void ReplaceFunction(void* existingFunction, const void* newFunction)
{
    uint32_t* dst;
    uint32_t src;

    dst = (uint32_t*)existingFunction;
    src = (uint32_t)newFunction;

    /*
     * We replace the destination first two instructions
     * by a J followed by a NOP.
     */
    dst[0] = 0x08000000 | ((src >> 2) & 0x3ffffff);
    dst[1] = 0x00000000;
    sceKernelDcacheWritebackRange(dst, 8);
}

void ReplaceHi16(void* dst, const void* newPtr)
{
    uint32_t value;
    uint16_t hi;

    value = (uint32_t)newPtr;
    hi = value >> 16;
    if (value & 0x8000)
        hi++;
    *(uint16_t*)dst = hi;
    sceKernelDcacheWritebackRange(dst, 4);
}

void ReplaceLo16(void* dst, const void* newPtr)
{
    uint32_t value;
    uint16_t lo;

    value = (uint32_t)newPtr;
    lo = value & 0xffff;
    *(uint16_t*)dst = lo;
    sceKernelDcacheWritebackRange(dst, 4);
}

void ReplaceLoadAddress(void* dst, const void* newPtr)
{
    uint32_t value;
    uint16_t hi;
    uint16_t lo;

    value = (uint32_t)newPtr;
    hi = value >> 16;
    lo = value & 0xffff;
    if (value & 0x8000)
        hi++;
    ((uint16_t*)dst)[0] = hi;
    ((uint16_t*)dst)[2] = lo;
    sceKernelDcacheWritebackRange(dst, 8);
}
