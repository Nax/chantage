#include <chantage_loader/loader.h>

void* _start() __attribute__ ((section(".text.start")));

void* _start()
{
    SceUID fd;
    char* segments[32];
    char* tmp;
    size_t segCount;
    size_t relCount;
    Elf32_Ehdr ehdr;
    Elf32_Phdr phdr;
    Elf32_Shdr shdr;
    Elf32_Rel rel;
    Elf32_Off off;
    char* relOff;
    uint32_t relVal;
    char* hiPtr;
    int hiSolved;
    uint32_t addend;

    segCount = 0;
    fd = sceIoOpen(CHANTAGE_PATH, SCE_O_RDONLY, 0777);
    sceIoRead(fd, &ehdr, sizeof(ehdr));

    /* Load the actual segments */
    for (int i = 0; i < ehdr.e_phnum; ++i)
    {
        sceIoLseek(fd, ehdr.e_phoff + i * ehdr.e_phentsize, SEEK_SET);
        sceIoRead(fd, &phdr, sizeof(phdr));

        if (phdr.p_type != PT_LOAD)
            continue;

        tmp = malloc(phdr.p_memsz);
        sceIoLseek(fd, phdr.p_offset, SEEK_SET);
        sceIoRead(fd, tmp, phdr.p_filesz);
        for (Elf32_Word i = phdr.p_filesz; i < phdr.p_memsz; ++i)
            tmp[i] = 0;
        segments[segCount++] = tmp;
    }

    /* Load the relocs */
    for (int i = 0; i < ehdr.e_shnum; ++i)
    {
        sceIoLseek(fd, ehdr.e_shoff + i * ehdr.e_shentsize, SEEK_SET);
        sceIoRead(fd, &shdr, sizeof(shdr));

        if (shdr.sh_type != SHT_LOPROC + 0xa0)
            continue;

        relCount = shdr.sh_size / sizeof(Elf32_Rel);
        sceIoLseek(fd, shdr.sh_offset, SEEK_SET);
        for (size_t j = 0; j < relCount; ++j)
        {
            hiPtr = 0;
            hiSolved = 0;
            sceIoRead(fd, &rel, sizeof(Elf32_Rel));
            relOff = segments[ELF32_R_OFS_BASE(rel.r_info)] + rel.r_offset;
            relVal = (uint32_t)segments[ELF32_R_ADDR_BASE(rel.r_info)];
            switch (ELF32_R_TYPE(rel.r_info))
            {
                case R_MIPS_NONE:
                    break;
                case R_MIPS_HI16:
                    hiPtr = relOff;
                    hiSolved = 0;
                    break;
                case R_MIPS_LO16:
                    addend = ((*(uint16_t*)hiPtr) << 16) | (*(uint16_t*)relOff);
                    relVal += addend;
                    if (!hiSolved)
                    {
                        *((uint16_t*)hiPtr) = (relVal >> 16);
                        hiSolved = 1;
                    }
                    *((uint16_t*)relOff) = (relVal & 0xffff);
                    break;
            }
        }
    }
    sceIoClose(fd);
    return segments[0] + ehdr.e_entry;
}
