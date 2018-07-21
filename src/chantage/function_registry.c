#include <chantage/impl.h>

typedef struct {
    size_t      size;
    size_t      capacity;
    size_t      strSize;
    size_t      strCapacity;
    char*       strTable;
    uint32_t*   offTable;
    void**      fnTable;
} FunctionRegistry;

static FunctionRegistry gFunctionRegistry;

static int _GetRegistryIndex(size_t* dst, const char* str)
{
    size_t max;

    max = gFunctionRegistry.size;
    for (size_t i = 0; i < max; ++i)
    {
        if (strcmp(str, gFunctionRegistry.strTable + gFunctionRegistry.offTable[i]) == 0)
        {
            *dst = i;
            return 1;
        }
    }
    return 0;
}

void InitFunctionRegistry()
{
    gFunctionRegistry.size = 0;
    gFunctionRegistry.capacity = 8;
    gFunctionRegistry.strSize = 0;
    gFunctionRegistry.strCapacity = 64;
    gFunctionRegistry.strTable = malloc(gFunctionRegistry.strCapacity);
    gFunctionRegistry.offTable = malloc(gFunctionRegistry.capacity * sizeof(uint32_t));
    gFunctionRegistry.fnTable = malloc(gFunctionRegistry.capacity * sizeof(void*));
}

void* LoadFunction(const char* str)
{
    size_t index;

    if (_GetRegistryIndex(&index, str))
        return gFunctionRegistry.fnTable[index];
    return NULL;
}

void* RegisterFunction(const char* str, void* fn)
{
    void* old;
    size_t index;
    size_t len;
    size_t newCapacity;
    void* newPtr;
    uint32_t off;

    if (_GetRegistryIndex(&index, str))
    {
        old = gFunctionRegistry.fnTable[index];
        gFunctionRegistry.fnTable[index] = fn;

        return old;
    }

    /* The function is not registered yet, let's register it */
    len = strlen(str) + 1;
    while (gFunctionRegistry.strSize + len > gFunctionRegistry.strCapacity)
    {
        newCapacity = gFunctionRegistry.strCapacity;
        newCapacity += newCapacity / 2;
        newPtr = malloc(newCapacity);
        memcpy(newPtr, gFunctionRegistry.strTable, gFunctionRegistry.strSize);
        free(gFunctionRegistry.strTable);
        gFunctionRegistry.strTable = newPtr;
        gFunctionRegistry.strCapacity = newCapacity;
    }
    off = gFunctionRegistry.strSize;
    memcpy(gFunctionRegistry.strTable + off, str, len);
    gFunctionRegistry.strSize += len;

    while (gFunctionRegistry.size >= gFunctionRegistry.capacity)
    {
        newCapacity = gFunctionRegistry.capacity;
        newCapacity += newCapacity / 2;
        newPtr = malloc(newCapacity * sizeof(uint32_t));
        memcpy(newPtr, gFunctionRegistry.offTable, gFunctionRegistry.size * sizeof(uint32_t));
        free(gFunctionRegistry.offTable);
        gFunctionRegistry.offTable = newPtr;
        newPtr = malloc(newCapacity * sizeof(void*));
        memcpy(newPtr, gFunctionRegistry.fnTable, gFunctionRegistry.size * sizeof(void*));
        free(gFunctionRegistry.fnTable);
        gFunctionRegistry.fnTable = newPtr;
        gFunctionRegistry.capacity = newCapacity;
    }
    index = gFunctionRegistry.size;
    gFunctionRegistry.offTable[index] = off;
    gFunctionRegistry.fnTable[index] = fn;
    gFunctionRegistry.size++;
    return NULL;
}
