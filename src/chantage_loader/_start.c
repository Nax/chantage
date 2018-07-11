#include <prx/prx.h>

#define CHANTAGE_PATH   "ms0:/PSP/GAME/ULUS10297/chantage.prx"

void* _start() __attribute__ ((section(".text.start")));


void* _start()
{
    SceUID fd;
    void* addr;

    fd = sceIoOpen(CHANTAGE_PATH, SCE_O_RDONLY, 0777);
    addr = prxLoad(fd);
    sceIoClose(fd);
    return addr;
}
