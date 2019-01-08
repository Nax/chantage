#include <chantage/prx.h>

static const unsigned char sElfSignature[] = { 0x7f, 0x45, 0x4c, 0x46 };

void* prxLoad(SceUID fd)
{
    char* segments[32];
    size_t segSize[32];
    char* tmp;
    size_t segCount;
    size_t relCount;
    Elf32_Ehdr ehdr;
    Elf32_Phdr phdr;
    Elf32_Shdr shdr;
    Elf32_Rel rel;
    char* relOff;
    uint32_t relVal;
    char* hiPtr;
    uint16_t hiVal;
    int hiSolved;

    hiVal = 0;
    segCount = 0;
    sceIoRead(fd, &ehdr, sizeof(ehdr));

    if (memcmp(ehdr.e_ident, sElfSignature, 4) != 0)
    {
        BREAKPOINT;
    }

    /* Load the actual segments */
    for (int i = 0; i < ehdr.e_phnum; ++i)
    {
        sceIoLseek(fd, ehdr.e_phoff + i * ehdr.e_phentsize, SEEK_SET);
        sceIoRead(fd, &phdr, sizeof(phdr));

        if (phdr.p_type != PT_LOAD)
            continue;

        tmp = SystemAlloc(phdr.p_memsz);
        sceIoLseek(fd, phdr.p_offset, SEEK_SET);
        sceIoRead(fd, tmp, phdr.p_filesz);
        for (Elf32_Word i = phdr.p_filesz; i < phdr.p_memsz; ++i)
            tmp[i] = 0;
        segments[segCount] = tmp;
        segSize[segCount] = phdr.p_memsz;
        segCount++;
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
        hiPtr = 0;
        hiSolved = 0;
        for (size_t j = 0; j < relCount; ++j)
        {
            sceIoRead(fd, &rel, sizeof(Elf32_Rel));
            relOff = segments[ELF32_R_OFS_BASE(rel.r_info)] + rel.r_offset;
            relVal = (uint32_t)segments[ELF32_R_ADDR_BASE(rel.r_info)];
            switch (ELF32_R_TYPE(rel.r_info))
            {
            case R_MIPS_NONE:
                break;
            case R_MIPS_16:
                relVal += *(uint16_t*)relOff;
                *(uint16_t*)relOff = (uint16_t)relVal;
                break;
            case R_MIPS_32:
                relVal += *(uint32_t*)relOff;
                *(uint32_t*)relOff = (uint32_t)relVal;
                break;
            case R_MIPS_REL32:
                relVal += *(uint32_t*)relOff;
                *(uint32_t*)relOff = (uint32_t)relVal - (uint32_t)relOff;
                break;
            case R_MIPS_26:
                relVal += (*((uint32_t*)relOff) & 0x3ffffff) << 2;
                *((uint32_t*)relOff) = (*((uint32_t*)relOff) & 0xfc000000) | ((relVal >> 2) & 0x3ffffff);
                break;
            case R_MIPS_HI16:
                hiPtr = relOff;
                hiVal = *(uint16_t*)hiPtr;
                hiSolved = 0;
                break;
            case R_MIPS_LO16:
                relVal += (hiVal << 16) | (*(uint16_t*)relOff);
                if (!hiSolved)
                {
                    /* LO16 is signed, so we may need to adjust the HI16 accordingly */
                    if (relVal & 0x8000)
                    {
                        relVal += 0x10000;
                    }
                    *((uint16_t*)hiPtr) = (relVal >> 16);
                    hiSolved = 1;
                }
                *((uint16_t*)relOff) = (relVal & 0xffff);
                break;
            }
        }
    }

    for (size_t i = 0; i < segCount; ++i)
        sceKernelDcacheWritebackRange(segments[i], segSize[i]);
    return segments[0] + ehdr.e_entry;
}
