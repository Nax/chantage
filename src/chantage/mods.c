#include <chantage/impl.h>
#include <chantage/prx.h>

#define BASE_PATH       "ms0:/PSP/COMMON/ULUS10297/"

static const char* sModsTxtPath = BASE_PATH "mods.txt";
static const char* sModsDirPath = BASE_PATH "mods/";

void LoadMods()
{
    char* buffer;
    char* strStart;
    char* strEnd;
    char strBuffer[256];
    char c;
    int len;
    size_t i;
    size_t j;

    SceUID fdMods;
    SceUID fd;
    Mod* mod;

    fdMods = sceIoOpen(sModsTxtPath, SCE_O_RDONLY, 0777);
    buffer = malloc(0x8000);
    len = sceIoRead(fdMods, buffer, 0x7fff);
    buffer[len] = 0;
    sceIoClose(fdMods);

    strStart = buffer;
    strEnd = buffer;

    for (;;)
    {
        for (;;)
        {
            c = *strEnd;
            if (c == '\n' || c == '\r' || c == 0)
                break;
            strEnd++;
        }
        if (strEnd > strStart)
        {
            i = 0;
            j = 0;
            while (i < 31)
            {
                strBuffer[i] = sModsDirPath[i];
                i++;
            }
            for (j = 0; j < strEnd - strStart; ++j)
            {
                strBuffer[i + j] = strStart[j];
            }
            strBuffer[i + j] = 0;
            fd = sceIoOpen(strBuffer, SCE_O_RDONLY, 0777);
            mod = prxLoad(fd);
            sceIoClose(fd);
            mod(&LoadFunction);
        }
        for (;;)
        {
            c = *strEnd;
            if (c != '\n' && c != '\r')
                break;
            strEnd++;
        }
        if (c == 0)
            break;
        strStart = strEnd;
    }

    free(buffer);
}
