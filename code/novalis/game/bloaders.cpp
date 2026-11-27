#include "common.h"
#include "fastfunc.h"
#include "framebuf.h"
#include "loaders.h"
#include "music.h"
#include "sce.h"
#include "wad.h"

extern unsigned char debugFontBuffer[] __attribute__((section(".data")));
extern unsigned long long debugFontPifHeader;

int FastLog2(int value);

void LoadPifAsPSMT8H(PifHeader *pPif, unsigned long long *gsRegs, int tex_loc, int pal_loc)
{
    PifParser pp;
    sceGsLoadImage image;

    FastMemSet(&pp, 0, sizeof(pp));
    pp.pClut = (unsigned char *)(pPif + 1);

    if (pPif->clutFormat == 0)
        pp.cSize = 0x400;

    else
        pp.cSize = 0x200;

    pp.uLog = FastLog2(pPif->uSize);
    pp.vLog = FastLog2(pPif->vSize);

    pp.pTex[0] = (unsigned char *)(pPif + 1) + pp.cSize;
    pp.tSize[0] = pPif->uSize * pPif->vSize;

    sceGsSetDefLoadImage(&image, pal_loc >> 8, 1, (short)pPif->clutFormat, 0, 0, 16, 16);
    FlushCache(0);
    sceGsExecLoadImage(&image, (u_long128 *)pp.pClut);
    sceGsSyncPath(0, 0);

    pp.tbw[0] = pPif->uSize >> 6;

    if (pp.tbw[0] <= 0)
        pp.tbw[0] = 1;

    pp.tPos[0] = tex_loc >> 8;

    sceGsSetDefLoadImage(&image, pp.tPos[0], pp.tbw[0], 0x1B, 0, 0, (short)pPif->uSize, (short)pPif->vSize);
    FlushCache(0);
    sceGsExecLoadImage(&image, (u_long128 *)pp.pTex[0]);
    sceGsSyncPath(0, 0);

    gsRegs[0] = (unsigned long long)pp.tPos[0] | ((unsigned long long)pp.tbw[0] << 14) | ((unsigned long long)27 << 20) | ((unsigned long long)pp.uLog << 26) | ((unsigned long long)pp.vLog << 30) | ((unsigned long long)1 << 34) | ((unsigned long long)(pal_loc >> 8) << 37) | ((unsigned long long)pPif->clutFormat << 51) | ((unsigned long long)1 << 63);

    gsRegs[1] = 1;
    gsRegs[2] = 0;
}

void LoadDebugFont(void)
{
    unsigned char regs[0x18];

    music_LoadFileSync(debugFontBuffer, bootAssets.debugFont.offset, bootAssets.debugFont.length);
    LoadPifAsPSMT8H((PifHeader *)debugFontBuffer, (unsigned long long *)regs, GSmemZbuf + 0xC0000, 0x3FFC00);
    debugFontPifHeader = *(unsigned long long *)regs;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/bloaders", func_0020CC70);
