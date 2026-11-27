#include "common.h"
#include "framebuf.h"

void SetupFS_AA_buffer(int bx, int by, int sx, int sy, int ofx, int ofy)
{
    qword *regs;

    pAAbuff = &aaBuff;
    aaBuff.drawW = bx;
    aaBuff.drawH = by;
    aaBuff.dispW = sx;
    aaBuff.dispH = sy;
    aaBuff.dispOfsX = ofx;
    aaBuff.dispOfsY = ofy;
    aaBuff.update_context = 0;
    aaBuff.dispPSM = 0;
    aaBuff.drawPSM = 0;
    aaBuff.auxPSM = 0;
    aaBuff.zPSM = 0x31;
    aaBuff.dispFBP = GSmemDisplay >> 13;
    aaBuff.drawFBP = GSmemDraw >> 13;
    aaBuff.zFBP = GSmemZbuf >> 13;

    sceGsSetDefDispEnv(&aaBuff.disp, 0, sx, sy, ofx, ofy);
    pAAbuff->disp.dispfb.FBP = aaBuff.dispFBP;

    sceGsSetDefDrawEnv(&pAAbuff->drawLarge, aaBuff.drawPSM, aaBuff.drawW, aaBuff.drawH, 3, aaBuff.zPSM);
    pAAbuff->drawLarge.frame1.FBP = aaBuff.drawFBP;
    *(unsigned long *)&pAAbuff->drawLarge.zbuf1 = SCE_GS_SET_ZBUF(aaBuff.zFBP, aaBuff.zPSM & 0xF, 0);
    *(u_long128 *)&pAAbuff->giftagDrawLarge = 0;
    pAAbuff->giftagDrawLarge.NLOOP = 8;
    pAAbuff->giftagDrawLarge.EOP = 1;
    pAAbuff->giftagDrawLarge.NREG = 1;
    pAAbuff->giftagDrawLarge.REGS0 = GIF_REG_AD;

    sceGsSetDefDrawEnv(&pAAbuff->drawSmall, aaBuff.dispPSM, aaBuff.dispW, aaBuff.dispH, 0, 0);
    pAAbuff->drawSmall.frame1.FBP = aaBuff.dispFBP;
    *(unsigned long *)&pAAbuff->drawSmall.zbuf1 = 1UL << 32;
    *(u_long128 *)&pAAbuff->giftagDrawSmall = 0;
    pAAbuff->giftagDrawSmall.NLOOP = 8;
    pAAbuff->giftagDrawSmall.EOP = 1;
    pAAbuff->giftagDrawSmall.NREG = 1;
    pAAbuff->giftagDrawSmall.REGS0 = GIF_REG_AD;

    regs = aaDisplayRegs;
    QWORD_LO(regs[0]) = 0x408B400000000001UL;
    QWORD_HI(regs[0]) = 0xEEEE;
    QWORD_LO(regs[1]) = 0x30000;
    QWORD_HI(regs[1]) = 0x47;
    QWORD_LO(regs[2]) = 5;
    QWORD_HI(regs[2]) = 8;
    QWORD_LO(regs[3]) = 0x100000261UL;
    QWORD_HI(regs[3]) = 0x14;
    QWORD_LO(regs[4]) = ((long)pAAbuff->drawFBP << 5) | ((unsigned long)((pAAbuff->drawW >> 6) & 0x3F) << 14)
                     | ((long)pAAbuff->drawPSM << 20) | 0xEA8000000UL;
    QWORD_HI(regs[4]) = 6;
    QWORD_LO(regs[5]) = 0x4400000000008010UL;
    QWORD_HI(regs[5]) = 0x5353;

    unsigned long *displayStrip;
    int column;

    for (column = 0, displayStrip = (unsigned long *)&regs[6]; column < 16; column++) {
        *displayStrip++ = column * pAAbuff->drawW;
        *displayStrip++ = (column * pAAbuff->dispW + (0x8000 - pAAbuff->dispW * 8)) | ((long)(0x7FF8 - pAAbuff->dispH * 8) << 16);
        *displayStrip++ = (column + 1) * pAAbuff->drawW | ((long)pAAbuff->drawH << 20);
        *displayStrip++ = ((column + 1) * pAAbuff->dispW + (0x8000 - pAAbuff->dispW * 8)) | ((long)(pAAbuff->dispH * 8 + 0x7FF8) << 16);
    }

    QWORD_LO(regs[38]) = 0x4400000000008001UL;
    QWORD_HI(regs[38]) = 0x4410;
    QWORD_LO(regs[39]) = 0x181;
    QWORD_HI(regs[39]) = 0x80000000UL;
    QWORD_LO(regs[40]) = 0x6FF8 | ((long)(0x7FF8 - pAAbuff->dispH * 8) << 16);
    QWORD_HI(regs[40]) = 0x6FF8 | ((long)(pAAbuff->dispH * 8 + 0x7FF8) << 16);

    regs = aaMovieDisplayRegs;
    QWORD_LO(regs[0]) = 0x308B400000000001UL;
    QWORD_HI(regs[0]) = 0xEEE;
    QWORD_LO(regs[1]) = 0x30000;
    QWORD_HI(regs[1]) = 0x47;
    QWORD_LO(regs[2]) = 0x100000261UL;
    QWORD_HI(regs[2]) = 0x14;
    QWORD_LO(regs[3]) = ((long)pAAbuff->drawFBP << 5) | ((unsigned long)((pAAbuff->drawW >> 6) & 0x3F) << 14)
                          | ((long)pAAbuff->drawPSM << 20) | 0xEA8000000UL;
    QWORD_HI(regs[3]) = 6;
    QWORD_LO(regs[4]) = 0x4400000000008010UL;
    QWORD_HI(regs[4]) = 0x5353;

    unsigned long *movieStrip = (unsigned long *)&regs[5];

    for (int column = 0; column < 16; column++) {
        *movieStrip++ = column * pAAbuff->drawW;
        *movieStrip++ = (column * 0x200 + 0x6FF8) | ((long)(0x7FF8 - pAAbuff->dispH * 8) << 16);
        *movieStrip++ = (column + 1) * pAAbuff->drawW | 0x1A000000;
        *movieStrip++ = ((column + 1) * 0x200 + 0x6FF8) | ((long)(pAAbuff->dispH * 8 + 0x7FF8) << 16);
    }

    regs = aaBlurRegs;
    QWORD_LO(regs[0]) = 0x408B400000000001UL;
    QWORD_HI(regs[0]) = 0xEEEE;
    QWORD_LO(regs[1]) = 0x30000;
    QWORD_HI(regs[1]) = 0x47;
    QWORD_LO(regs[2]) = 5;
    QWORD_HI(regs[2]) = 8;
    QWORD_LO(regs[3]) = 0x100000261UL;
    QWORD_HI(regs[3]) = 0x14;
    QWORD_LO(regs[4]) = ((long)pAAbuff->drawFBP << 5) | ((unsigned long)((pAAbuff->drawW >> 6) & 0x3F) << 14)
                  | ((long)pAAbuff->drawPSM << 20) | 0xEA8000000UL;
    QWORD_HI(regs[4]) = 6;
    QWORD_LO(regs[5]) = 0x4400000000008010UL;
    QWORD_HI(regs[5]) = 0x5353;

    unsigned long *blurStrip = (unsigned long *)&regs[6];

    for (int column = 0; column < 16; column++) {
        *blurStrip++ = column * 0x200;
        *blurStrip++ = (column * 0x200 + 0x7000) | ((long)(0x8000 - pAAbuff->drawH * 8) << 16);
        *blurStrip++ = ((column + 1) * 0x200) | ((long)pAAbuff->drawH << 20);
        *blurStrip++ = ((column + 1) * 0x200 + 0x7000) | ((long)(pAAbuff->drawH * 8 + 0x7FF0) << 16);
    }

    regs = aaClearRegs;
    QWORD_LO(regs[0]) = 0x1000000000000001UL;
    QWORD_HI(regs[0]) = 0xE;
    QWORD_LO(regs[1]) = 0x30000;
    QWORD_HI(regs[1]) = 0x47;
    QWORD_LO(regs[2]) = 0x2400000000008001UL;
    QWORD_HI(regs[2]) = 0x10;
    QWORD_LO(regs[3]) = 0x106;
    QWORD_HI(regs[3]) = 0x80008000UL;
    QWORD_LO(regs[4]) = 0x2400000000008010UL;
    QWORD_HI(regs[4]) = 0x44;

    unsigned long *clearStrip = (unsigned long *)&regs[5];

    for (int column = 0; column < 16; column++) {
        *clearStrip++ = (column * 0x200 + 0x6FF8) | ((long)(0x7FF8 - pAAbuff->drawH * 8) << 16);
        *clearStrip++ = ((column + 1) * 0x200 + 0x6FF8) | ((long)(pAAbuff->drawH * 8 + 0x7FF8) << 16);
    }

    regs = gif_clear_screen;
    unsigned long *screenStrip = (unsigned long *)&regs[4];

    for (int column = 0; column < 16; column++) {
        *screenStrip++ = (column * 0x200 + 0x6FF8) | ((long)(0x7FF8 - pAAbuff->drawH * 8) << 16);
        *screenStrip++ = ((column + 1) * 0x200 + 0x6FF8) | ((long)(pAAbuff->drawH * 8 + 0x7FF8) << 16);
    }

    regs = gif_clear_frame_buf;
    unsigned long *frameStrip = (unsigned long *)&regs[4];

    for (int column = 0; column < 16; column++) {
        *frameStrip++ = (column * 0x200 + 0x6FF8) | ((long)(0x7FF8 - pAAbuff->dispH * 8) << 16);
        *frameStrip++ = ((column + 1) * 0x200 + 0x6FF8) | ((long)(pAAbuff->dispH * 8 + 0x7FF8) << 16);
    }
}

void SetBackgroundColor(int r, int g, int b)
{
    QWORD_HI(aaClearRegs[AA_CLEAR_REGS_RGBAQ]) = (long)r | ((long)g << 8) | ((long)b << 16) | 0x80000000L;
}

void PutDispBuffer(void)
{
    sceGsPutDispEnv(&pAAbuff->disp);
}

void PutDrawBufferLarge(void)
{
    if (vu1_bufPtr.bytes != 0) {
        VU1_CHAIN_WORD(0) = DMA_TAG_REF | AA_DRAW_ENV_QWC;
        VU1_CHAIN_WORD(4) = (unsigned int)&pAAbuff->giftagDrawLarge & EE_PHYSICAL_ADDRESS_MASK;
        VU1_CHAIN_WORD(8) = 0;
        VU1_CHAIN_WORD(12) = VIF_DIRECT | AA_DRAW_ENV_QWC;

        vu1_bufPtr.bytes += 16;
    } else {
        sceGsPutDrawEnv(&pAAbuff->giftagDrawLarge);
    }
}

void ClearDrawBufferLarge(int black)
{
    if (vu1_bufPtr.bytes != 0) {
        VU1_CHAIN_WORD(0) = DMA_TAG_REF | AA_CLEAR_REGS_QWC;
        VU1_CHAIN_WORD(4) = (unsigned int)aaClearRegs;
        VU1_CHAIN_WORD(8) = 0;
        VU1_CHAIN_WORD(12) = VIF_DIRECT | AA_CLEAR_REGS_QWC;

        vu1_bufPtr.bytes += 16;
    }
}

void PutDrawBufferSmall(void)
{
    VU1_CHAIN_WORD(0) = DMA_TAG_REF | AA_DRAW_ENV_QWC;
    VU1_CHAIN_WORD(4) = (unsigned int)&pAAbuff->giftagDrawSmall & EE_PHYSICAL_ADDRESS_MASK;
    VU1_CHAIN_WORD(8) = 0;
    VU1_CHAIN_WORD(12) = VIF_DIRECT | AA_DRAW_ENV_QWC;

    vu1_bufPtr.bytes += 16;
}

void SetMovieDrawSmallVIFChain(int widthLog2, int heightLog2, int gsAddress)
{
    int bufferWidthLog2 = widthLog2 - 6;
    long *gifTag;
    sceGsDrawEnv1 *drawEnv;
    long *clearSprite;

    if (bufferWidthLog2 <= 0) {
        bufferWidthLog2 = 1;
    }

    aaBuff.auxFBP = gsAddress >> 13;
    aaBuff.auxW = 1 << widthLog2;
    aaBuff.auxH = 1 << heightLog2;
    AuxBufferTex0 = (unsigned long)(gsAddress >> 8) | ((unsigned long)(1 << bufferWidthLog2) << 14)
                  | ((unsigned long)widthLog2 << 26) | ((unsigned long)heightLog2 << 30) | (1UL << 34);

    FastMemSetZero(vu1_bufPtr.words, 0xF0);

    vu1_bufPtr.words[0] = DMA_TAG_CNT | 0xE;
    vu1_bufPtr.words[1] = 0;
    vu1_bufPtr.words[2] = 0;
    vu1_bufPtr.words[3] = VIF_DIRECT | 0xE;
    vu1_bufPtr.words += 4;

    gifTag = (long *)vu1_bufPtr.words;
    gifTag[0] = 0x1000000000000008L;
    gifTag[1] = GIF_REG_AD;
    vu1_bufPtr.words += 4;

    drawEnv = (sceGsDrawEnv1 *)vu1_bufPtr.words;
    sceGsSetDefDrawEnv(drawEnv, aaBuff.auxPSM, aaBuff.auxW, aaBuff.auxH, 3, 0);
    drawEnv->frame1.FBP = aaBuff.auxFBP;
    *(unsigned long *)&drawEnv->zbuf1 = SCE_GS_SET_ZBUF(aaBuff.zFBP, aaBuff.zPSM & 0xF, 0);
    vu1_bufPtr.words += sizeof(sceGsDrawEnv1) / 4;

    clearSprite = (long *)vu1_bufPtr.words;
    clearSprite[0] = 0x1000000000000001L;
    clearSprite[1] = GIF_REG_AD;
    clearSprite[2] = 0x30003;
    clearSprite[3] = 0x47;
    clearSprite[4] = 0x4400000000008001L;
    clearSprite[5] = 0x4410;
    clearSprite[6] = 0x106;
    clearSprite[7] = 0;
    clearSprite[8] = (long)(0x8000 - aaBuff.auxW * 8) | ((long)(0x8000 - aaBuff.auxH * 8) << 16);
    clearSprite[9] = (long)(aaBuff.auxW * 8 + 0x8000) | ((long)(aaBuff.auxH * 8 + 0x7FF0) << 16);
    vu1_bufPtr.words += 0x14;
}

void AA_BlurPass(void)
{
    VU1_CHAIN_WORD(0) = DMA_TAG_REF | AA_BLUR_REGS_QWC;
    VU1_CHAIN_WORD(4) = (unsigned int)aaBlurRegs;
    VU1_CHAIN_WORD(8) = 0;
    VU1_CHAIN_WORD(12) = VIF_DIRECT | AA_BLUR_REGS_QWC;

    vu1_bufPtr.bytes += 16;
}

void AA_DisplayPass(int opaque)
{
    VU1_CHAIN_WORD(0) = DMA_TAG_REF | AA_DISPLAY_REGS_QWC;
    VU1_CHAIN_WORD(4) = (unsigned int)aaDisplayRegs;
    VU1_CHAIN_WORD(8) = 0;
    VU1_CHAIN_WORD(12) = VIF_DIRECT | AA_DISPLAY_REGS_QWC;

    vu1_bufPtr.bytes += 16;
}

void DrawLineList(int width, int height)
{
    DmaTag *tag;
    unsigned long *packet;
    unsigned long *corner;
    int columns;
    int column;
    int zero;
    int left;
    int right;
    unsigned long top;
    unsigned long bottom;

    columns = width / 32;

    VU1_addGSregister(GS_REG_ALPHA_1, 0x800000004AUL);

    vu1_bufPtr.tag->tag = DMA_TAG_CNT | (columns + 5);
    vu1_bufPtr.tag->addr = 0;
    vu1_bufPtr.tag->vif0 = 0;
    vu1_bufPtr.tag->vif1 = VIF_DIRECT | (columns + 5);

    tag = vu1_bufPtr.tag;
    packet = (unsigned long *)(tag + 1);
    vu1_bufPtr.tag = tag + 1;

    zero = 0;
    packet[zero] = 0x1000000000000001UL;
    packet[1] = GIF_REG_AD;
    packet[2] = 0x32003;
    packet[3] = 0x47;
    packet[4] = 0x2400000000000001UL;
    packet[5] = 0x10;
    packet[6] = 0x146;
    packet[7] = 0x80008080UL;
    packet[8] = (unsigned long)(columns | 0x8000) | 0x2400000000000000UL;
    packet[9] = 0x44;

    column = zero;

    if (columns > zero) {
        top = (long)(0x8000 - height * 8) << 16;
        left = -(width * 8) + 0x8000;
        corner = &packet[10];
        right = -(width * 8) + 0x8200;
        bottom = (long)(height * 8 + 0x7FF0) << 16;

        do {
            *corner++ = left | top;
            *corner++ = right | bottom;
            right += 0x200;
            left += 0x200;
            column++;
        } while (column < columns);
    }

    vu1_bufPtr.bytes += columns * 16 + 0x50;
}

void DrawFilledRectGS(int x0, int y0, int x1, int y1, int width, int height, unsigned int color)
{
    DmaTag *tag;
    unsigned long *packet;
    int left;
    int top;
    int right;
    int bottom;

    VU1_addVIFcode(VIF_FLUSHA);
    VU1_addGSregister(GS_REG_ALPHA_1, 0x64);

    vu1_bufPtr.tag->tag = DMA_TAG_CNT | 6;
    vu1_bufPtr.tag->addr = 0;
    vu1_bufPtr.tag->vif0 = 0;
    vu1_bufPtr.tag->vif1 = VIF_DIRECT | 6;

    top = y0 << 4;
    bottom = y1 << 4;
    left = x0 << 4;
    right = x1 << 4;

    bottom += 0x8000;
    top += 0x8000;
    right += 0x8000;
    left += 0x8000;

    bottom -= height << 3;
    top -= height << 3;
    right -= width << 3;
    left -= width << 3;

    tag = vu1_bufPtr.tag;
    packet = (unsigned long *)(tag + 1);
    vu1_bufPtr.tag = tag + 1;

    packet[0] = 0x1000000000000001UL;
    packet[1] = GIF_REG_AD;
    packet[2] = 0x33003;
    packet[3] = 0x47;
    packet[4] = 0x2400000000000001UL;
    packet[5] = 0x10;
    packet[6] = 0x106;
    packet[7] = color;
    packet[8] = 0x2400000000008001UL;
    packet[9] = 0x44;
    packet[10] = left | ((unsigned long)top << 16);
    packet[11] = right | ((unsigned long)bottom << 16);
    vu1_bufPtr.bytes += 0x60;

    VU1_addGSregister(GS_REG_ALPHA_1, 0x8000000044UL);
    VU1_addVIFcode(VIF_FLUSHA);
}
