#include "common.h"
#include "fastfunc.h"
#include "sce.h"
#include "framebuf.h"
#include "music.h"
#include "wad.h"
#include "loaders.h"

extern unsigned char debugFontBuffer[] __attribute__((section(".data")));
extern unsigned long long debugFontPifHeader;


int FastLog2(int value);

void LoadPifAsPSMT8H(PifHeader *pif, unsigned long long *gsRegisters, int textureAddress, int paletteAddress)
{
    PifParser parsed;
    sceGsLoadImage packet;

    FastMemSet(&parsed, 0, sizeof(parsed));
    parsed.pClut = (unsigned char *)(pif + 1);

    if (pif->clutFormat == 0)
        parsed.cSize = 0x400;

    else
        parsed.cSize = 0x200;

    parsed.uLog = FastLog2(pif->uSize);
    parsed.vLog = FastLog2(pif->vSize);

    parsed.pTex[0] = (unsigned char *)(pif + 1) + parsed.cSize;
    parsed.tSize[0] = pif->uSize * pif->vSize;

    sceGsSetDefLoadImage(&packet, paletteAddress >> 8, 1, (short)pif->clutFormat, 0, 0, 16, 16);
    FlushCache(0);
    sceGsExecLoadImage(&packet, (u_long128 *)parsed.pClut);
    sceGsSyncPath(0, 0);

    parsed.tbw[0] = pif->uSize >> 6;

    if (parsed.tbw[0] <= 0)
        parsed.tbw[0] = 1;

    parsed.tPos[0] = textureAddress >> 8;

    sceGsSetDefLoadImage(&packet, parsed.tPos[0], parsed.tbw[0], 0x1B, 0, 0, (short)pif->uSize, (short)pif->vSize);
    FlushCache(0);
    sceGsExecLoadImage(&packet, (u_long128 *)parsed.pTex[0]);
    sceGsSyncPath(0, 0);

    gsRegisters[0] = (unsigned long long)parsed.tPos[0]
              | ((unsigned long long)parsed.tbw[0]        << 14)
              | ((unsigned long long)27               << 20)
              | ((unsigned long long)parsed.uLog          << 26)
              | ((unsigned long long)parsed.vLog          << 30)
              | ((unsigned long long)1                << 34)
              | ((unsigned long long)(paletteAddress >> 8)   << 37)
              | ((unsigned long long)pif->clutFormat << 51)
              | ((unsigned long long)1                << 63);

    gsRegisters[1] = 1;
    gsRegisters[2] = 0;
}

void LoadDebugFont(void)
{
    unsigned char pifBuffer[0x18];

    music_LoadFileSync(debugFontBuffer, bootAssets.debugFont.offset, bootAssets.debugFont.length);
    LoadPifAsPSMT8H((PifHeader *)debugFontBuffer, (unsigned long long *)pifBuffer, GSmemZbuf + 0xC0000, 0x3FFC00);
    debugFontPifHeader = *(unsigned long long *)pifBuffer;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/bloaders", func_0020CC70);
