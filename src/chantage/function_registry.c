#include <chantage/impl.h>

static int _GetRegistryIndex(size_t* dst, const char* str)
{
    size_t max;

    max = gContext.functions.size;
    for (size_t i = 0; i < max; ++i)
    {
        if (strcmp(str, gContext.functions.strTable + gContext.functions.offTable[i]) == 0)
        {
            *dst = i;
            return 1;
        }
    }
    return 0;
}

void InitFunctionRegistry()
{
    ChantageFunctionRegistry* registry;

    registry = &gContext.functions;
    registry->size = 0;
    registry->capacity = 8;
    registry->strSize = 0;
    registry->strCapacity = 64;
    registry->strTable = malloc(registry->strCapacity);
    registry->offTable = malloc(registry->capacity * sizeof(uint32_t));
    registry->fnTable = malloc(registry->capacity * sizeof(void*));
}

void* LoadFunction(const char* str)
{
    size_t index;

    if (_GetRegistryIndex(&index, str))
        return gContext.functions.fnTable[index];
    return NULL;
}

void* RegisterFunction(const char* str, void* fn)
{
    ChantageFunctionRegistry* registry;
    void* old;
    size_t index;
    size_t len;
    size_t newCapacity;
    void* newPtr;
    uint32_t off;

    registry = &gContext.functions;
    if (_GetRegistryIndex(&index, str))
    {
        old = registry->fnTable[index];
        registry->fnTable[index] = fn;

        return old;
    }

    /* The function is not registered yet, let's register it */
    len = strlen(str) + 1;
    while (registry->strSize + len > registry->strCapacity)
    {
        newCapacity = registry->strCapacity;
        newCapacity += newCapacity / 2;
        newPtr = malloc(newCapacity);
        memcpy(newPtr, registry->strTable, registry->strSize);
        free(registry->strTable);
        registry->strTable = newPtr;
        registry->strCapacity = newCapacity;
    }
    off = registry->strSize;
    memcpy(registry->strTable + off, str, len);
    registry->strSize += len;

    while (registry->size >= registry->capacity)
    {
        newCapacity = registry->capacity;
        newCapacity += newCapacity / 2;
        newPtr = malloc(newCapacity * sizeof(uint32_t));
        memcpy(newPtr, registry->offTable, registry->size * sizeof(uint32_t));
        free(registry->offTable);
        registry->offTable = newPtr;
        newPtr = malloc(newCapacity * sizeof(void*));
        memcpy(newPtr, registry->fnTable, registry->size * sizeof(void*));
        free(registry->fnTable);
        registry->fnTable = newPtr;
        registry->capacity = newCapacity;
    }
    index = registry->size;
    registry->offTable[index] = off;
    registry->fnTable[index] = fn;
    registry->size++;
    return NULL;
}
