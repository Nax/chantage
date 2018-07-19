#include <chantage/chantage.h>

void ReplaceFunction(void* existingFunction, void* newFunction)
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
