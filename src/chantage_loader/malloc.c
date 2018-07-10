#include <chantage_loader/loader.h>

typedef void* (*pfn_malloc_r)(const void* reent, size_t size);
typedef void  (*pfn_free_r)(const void* reent, void* ptr);

static const pfn_malloc_r   _malloc_r = (void*)(0x0880bd40);
static const pfn_free_r     _free_r =   (void*)(0x0880ad24);

static const void* sReent = (void*)0x08a71f38;

void* malloc(size_t size)
{
    return _malloc_r(sReent, size);
}

void free(void* ptr)
{
    return _free_r(sReent, ptr);
}
