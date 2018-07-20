#include <chantage/prx.h>

#define CHANTAGE_PATH   "ms0:/PSP/COMMON/ULUS10297/chantage.prx"

void* _start() __attribute__ ((section(".text.start")));

void* _start()
{
    SceUID fd;
    void* addr;

    fd = sceIoOpen(CHANTAGE_PATH, SCE_O_RDONLY, 0777);
    if (fd < 0)
    {
        return NULL;
    }
    addr = prxLoad(fd);
    sceIoClose(fd);
    return addr;
}
