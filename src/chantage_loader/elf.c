#include <chantage_loader/loader.h>

void elfParseHeader(Elf32_Ehdr* ehdr, SceUID fd)
{
    sceIoLseek(fd, 0, SEEK_SET);
    sceIoRead(fd, ehdr, sizeof(*ehdr));
}
