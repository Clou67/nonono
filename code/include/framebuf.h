#ifndef FRAMEBUF_H
#define FRAMEBUF_H

#include "gsregs.h"

#include "sce.h"
#include "vuchain.h"

// Full-screen anti-aliasing buffer: display and draw environments plus the sizes they were built from (DL fsAABuff).
struct fsAABuff {
    sceGsDispEnv disp;
    sceGifTag giftagDrawLarge;
    sceGsDrawEnv1 drawLarge;
    sceGifTag giftagDrawSmall;
    sceGsDrawEnv1 drawSmall;
    short drawW;
    short drawH;
    short drawPSM;
    short drawFBP;
    short dispW;
    short dispH;
    short dispPSM;
    short dispFBP;
    short auxW;
    short auxH;
    short auxPSM;
    short auxFBP;
    short dispOfsX;
    short dispOfsY;
    short zPSM;
    short zFBP;
    int update_context;
};

// GS memory addresses. DL keeps these in a GSMEM struct, but RC1 addresses
// each one as a separate global.
extern int GSmemDisplay;
extern int GSmemDraw;
extern int GSmemZbuf;
// Start of free GS memory after the frame and depth buffers.
extern int GSmemBase;
extern fsAABuff aaBuff;
extern fsAABuff *pAAbuff;

// One 128-bit DMA/GIF quadword, as DL types it.
typedef int qword[4];

// The low and high 64-bit halves of a quadword.
#define QWORD_LO(q) (*(unsigned long *)&(q)[0])
#define QWORD_HI(q) (*(unsigned long *)&(q)[2])

// GIF packets for the AA passes (qword counts are in the DMA tags that send them).
extern qword aaBlurRegs[];
extern qword aaDisplayRegs[];
extern qword aaMovieDisplayRegs[];
extern qword aaClearRegs[];
extern qword gif_clear_screen[];
extern qword gif_clear_frame_buf[];

#define AA_BLUR_REGS_QWC 0x26
#define AA_DISPLAY_REGS_QWC 0x29
#define AA_CLEAR_REGS_QWC 0x15
#define GIF_CLEAR_FRAME_BUF_QWC 0x14
#define AA_DRAW_ENV_QWC 9

// Quadword of the clear packet holding the RGBAQ register (data in the high half).
#define AA_CLEAR_REGS_RGBAQ 3

#define EE_PHYSICAL_ADDRESS_MASK 0x0FFFFFFF

#define VIF_FLUSHA 0x13000000

// TEX0 for the aux render target set up by SetMovieDrawSmallVIFChain.
extern unsigned long AuxBufferTex0;

void FastMemSetZero(void *destination, int size);

void SetupFS_AA_buffer(int drawWidth, int drawHeight, int dispWidth, int dispHeight, int offsetX, int offsetY);
void DrawLineList(int width, int height);
void SetBackgroundColor(int red, int green, int blue);
void PutDispBuffer(void);
void PutDrawBufferLarge(void);
void ClearDrawBufferLarge(int black);
void PutDrawBufferSmall(void);
void AA_BlurPass(void);
void AA_DisplayPass(int opaque);
void SetMovieDrawSmallVIFChain(int widthLog2, int heightLog2, int gsAddress);
void DrawFilledRectGS(int x0, int y0, int x1, int y1, int width, int height, unsigned int color);

#endif
