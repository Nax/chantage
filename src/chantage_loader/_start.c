#include <chantage_loader/loader.h>

void _start() __attribute__ ((section(".text.start")));

void _start()
{
    SceUID file;

    file = sceIoOpen(CHANTAGE_PATH, SCE_O_RDONLY, 0777);
    sceIoClose(file);
}
