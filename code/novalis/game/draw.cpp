#include "common.h"
#include "font.h"
#include "framebuf.h"
#include "draw.h"
#include "fastfunc.h"
#include "viewcontext.h"
#include "mathfunc_inline.h"
#include "tfrag.h"

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/draw", ScreenPosFromWorldSpace);

struct LevelDrawCounterState {
    char unk_00[0x1B0];
    int unk_1B0;
    char unk_1B4[0x1B0];
    int frameCount;
    int previousFrameCount;
};

extern LevelDrawCounterState LevelDrawCounters;

void ResetLevelCounters(void)
{
    int frameCount = LevelDrawCounters.frameCount;
    LevelDrawCounters.unk_1B0 = 0;
    LevelDrawCounters.previousFrameCount = frameCount;
    LevelDrawCounters.frameCount = 0;
}

void STUB_00218990(void)
{
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/draw", printf_stub2);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/draw", printf_stub3);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/draw", ResetFrameBufferForCutscene__Fv);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/draw", ComposeCameraMatrix);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/draw", UpdateFog);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/draw", ParseOcclGrid);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/draw", GetOcclGridFromPair);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/draw", BuildOcclVisibility);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/draw", UpdateOcclusion);

void InitViewContext(void)
{
    short width = aaBuff.drawW;
    int halfWidth = width >> 1;
    short height = aaBuff.drawH;
    int halfHeight = height >> 1;

    Scrn.paramX = width;
    Scrn.paramY = height;
    Scrn.halfX = halfWidth;
    Scrn.halfY = halfHeight;
    Scrn.minX = (0x800 - halfWidth) << 4;
    Scrn.minY = (0x800 - halfHeight) << 4;
    Scrn.maxX = (halfWidth + 0x800) << 4;
    Scrn.maxY = (halfHeight + 0x800) << 4;

    VC.nearClip = 32.0f;
    VC.farClip = 745472.0f;
    VC.xratio = 0.63f;

    VC.xpix = FastIntToFloat(width) * 0.5f;
    VC.ypix = FastIntToFloat(aaBuff.drawH) * 0.5f;

    VC.xclip = VC.xpix * 4.0f;
    VC.yclip = VC.ypix * 4.0f;

    VC.fogNearDist = 0.0f;
    VC.fogFarDist = 524288.0f;
    VC.fogNearIntensity = 255.0f;
    VC.fogFarIntensity = 0.0f;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/draw", UpdateViewContext);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/draw", SetUserViewContext);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/draw", SetPalMode);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/draw", ResetDrawGlobals);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/draw", SetupFogColorGsReg);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/draw", ResetGsRegistersPr);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/draw", DefaultDraw);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/draw", SetupDefaultDraw);

extern int CutscenePlaying;
extern int RenderFlags __attribute__((section(".sdata")));
void DefaultDraw(void);

void SetupDefaultDrawMovie(int black)
{
    if (!CutscenePlaying) {
        ClearDrawBufferLarge(black);
        RenderFlags = 0x7F;
        DefaultDraw();
    }
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/draw", SetupDefaultDrawFreeze);

extern int CutscenePlaying;
void FrontEnd_DrawMenu(int mode);

void CallDrawOverlayIfNoCutscene(void)
{
    if (!CutscenePlaying)
        FrontEnd_DrawMenu(0);
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/draw", DrawFrameEnd);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/draw", FlipAndExploreTimersVU1);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/draw", FinalizeVU1FramePacketChain);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/draw", FontSet);

extern int MobyFnListCnt;
extern DrawMobyCallback MobyFnList[];
extern MobyInstance *MobyFnListArgs[];

void RegisterMobyDraw(DrawMobyCallback draw, MobyInstance *moby)
{
    int slot = MobyFnListCnt;

    if (slot < DRAW_CALLBACK_LIMIT) {
        MobyFnList[slot] = draw;
        MobyFnListArgs[slot] = moby;
        MobyFnListCnt = slot + 1;
    }
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/draw", ExecuteRegisteredMobyFuncs);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/draw", ExecutePostDraws);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/draw", ExecutePostPreDraws);

extern int PreDrawCnt;
extern DrawMobyCallback PreDrawCallbacks[];
extern MobyInstance *PreDrawArgs[];

void RegisterPreDraw(DrawMobyCallback draw, MobyInstance *moby)
{
    int slot = PreDrawCnt;

    if (slot < DRAW_CALLBACK_LIMIT) {
        PreDrawCallbacks[slot] = draw;
        PreDrawArgs[slot] = moby;
        PreDrawCnt = slot + 1;
    }
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/draw", ExecutePreDraws);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/draw", DrawLameShadows);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/draw", FadeToBlack);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/draw", Draw_FlushAndPresent);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/draw", DrawSubtitles);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/draw", UpdateLetterBox);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/draw", DrawScreenEffect);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/draw", DrawScreenOverlay);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/draw", SetScreenClearColorPacket);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/draw", DrawRectOverlay);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/draw", func_0021BE88);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/draw", DrawSprite);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/draw", DrawSpriteF);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/draw", DrawSpriteFont);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/draw", Sprite_DrawRotated);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/draw", func_0021C950);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/draw", DrawTextShadow);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/draw", DrawRoundedRect);

extern int FontColorsEnabled;

void EnableFontColors(void)
{
    FontColorsEnabled = 1;
}

void DisableFontColors(void)
{
    FontColorsEnabled = 0;
}

struct FontGlyph {
    unsigned char u;
    unsigned char v;
    signed char yOff;
    signed char width;
};

int FontLenWithTable(char *text, int length, unsigned char *metrics)
{
    const FontGlyph *glyphs = (const FontGlyph *)metrics;
    int total = 0;
    int index = 0;
    if (length != 0 && *(unsigned char *)text != 0) {
        unsigned char *cursor = (unsigned char *)text;
        do {
            int code = *cursor++;
            int width = glyphs[code].width;
            if (width)
                total += width;
            index++;
        } while (index != length && *cursor != 0);
    }
    return total;
}

int FontLenWithTable(char *text, int length, unsigned char *metrics);
extern unsigned char FontNormalMetrics[];

int FontLen(char *text, int length)
{
    return FontLenWithTable(text, length, FontNormalMetrics);
}

extern unsigned char FontSmallMetrics[];

int FontLenSmall(char *text, int length)
{
    return FontLenWithTable(text, length, FontSmallMetrics);
}

extern unsigned char FontLargeMetrics[];

int FontLenLarge(char *text, int length)
{
    return FontLenWithTable(text, length, FontLargeMetrics);
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/draw", FontPrint);

void FontPrint(int x, int y, unsigned long rgba, char *text, int length, unsigned long tex0, unsigned char *metrics);

void FontPrintMediumLeft(int x, int y, unsigned long rgba, char *text, int length)
{
    unsigned long tex0 = FontSet(FONT_MEDIUM);
    FontPrint(x, y, rgba, text, length, tex0, FontNormalMetrics);
}

void FontPrintSmallLeft(int x, int y, unsigned long rgba, char *text, int length)
{
    unsigned long tex0 = FontSet(FONT_SMALL);
    FontPrint(x, y, rgba, text, length, tex0, FontSmallMetrics);
}

void FontPrintLarge(int x, int y, unsigned long rgba, char *text, int length)
{
    unsigned long tex0 = FontSet(FONT_LARGE);
    FontPrint(x, y, rgba, text, length, tex0, FontLargeMetrics);
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/draw", FontPrintWindowLine);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/draw", func_0021D3E0);

void FontPrintMediumRight(int x, int y, unsigned long rgba, char *text, int length)
{
    x -= (FontLen(text, length));
    unsigned long tex0 = FontSet(FONT_MEDIUM);

    FontPrint(x, y, rgba, text, length, tex0, FontNormalMetrics);
}

void FontPrintSmallRight(int x, int y, unsigned long rgba, char *text, int length)
{
    x -= (FontLenSmall(text, length));
    unsigned long tex0 = FontSet(FONT_SMALL);

    FontPrint(x, y, rgba, text, length, tex0, FontSmallMetrics);
}

void FontPrintLargeRight(int x, int y, unsigned long rgba, char *text, int length)
{
    x -= (FontLenLarge(text, length));
    unsigned long tex0 = FontSet(FONT_LARGE);

    FontPrint(x, y, rgba, text, length, tex0, FontLargeMetrics);
}

int FontPrintCenter(int x, int y, unsigned long rgba, char *text, int length)
{
    x -= (FontLen(text, length) >> 1);
    unsigned long tex0 = FontSet(FONT_MEDIUM);

    FontPrint(x, y, rgba, text, length, tex0, FontNormalMetrics);
    return x;
}

int FontPrintCenterSmall(int x, int y, unsigned long rgba, char *text, int length)
{
    x -= (FontLenSmall(text, length) >> 1);
    unsigned long tex0 = FontSet(FONT_SMALL);

    FontPrint(x, y, rgba, text, length, tex0, FontSmallMetrics);
    return x;
}

int FontPrintCenterLarge(int x, int y, unsigned long rgba, char *text, int length)
{
    x -= (FontLenLarge(text, length) >> 1);
    unsigned long tex0 = FontSet(FONT_LARGE);

    FontPrint(x, y, rgba, text, length, tex0, FontLargeMetrics);
    return x;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/draw", FontPrintWrapped);

int FontPrintWrapped(int x, int y, unsigned long rgba, char *text, int length, int width, int spacing, unsigned long tex0, unsigned char *metrics);

int FontPrintWrappedSmall(int x, int y, unsigned long rgba, char *text, int length, int width, int spacing)
{
    unsigned long tex0 = FontSet(FONT_SMALL);
    return FontPrintWrapped(x, y, rgba, text, length, width, spacing, tex0, FontSmallMetrics);
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/draw", func_0021DB28);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/draw", FontPrintWindow);

void FontPrintWindowMedium(FontWindow *window, unsigned long rgba, char *text, int length)
{
    unsigned long tex0 = FontSet(FONT_MEDIUM);
    FontPrintWindow(window, rgba, text, length, tex0, FontNormalMetrics);
}

void FontPrintWindowSmall(FontWindow *window, unsigned long rgba, char *text, int length)
{
    unsigned long tex0 = FontSet(FONT_SMALL);
    FontPrintWindow(window, rgba, text, length, tex0, FontSmallMetrics);
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/draw", func_0021E118);

void SetFontWindow(FontWindow *window, int win_top, int win_bot, int win_left, int win_right, int text_x, int text_y, int line_spacing, int flags)
{
    window->win_top = win_top;
    window->win_bot = win_bot;
    window->win_left = win_left;
    window->win_right = win_right;
    window->text_x = text_x;
    window->text_y = text_y;
    window->line_spacing = line_spacing;
    window->flags = flags;

    window->max_width = 0;
    window->max_height = 0;
    window->sub_pixel_x = 0;
    window->sub_pixel_y = 0;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/draw", DrawScreenCopyToVU1);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/draw", SetupVU1WorldDraw);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/draw", BeginAuxDrawMode);

void EndAuxDrawMode(void)
{
    PutDrawBufferLarge();
    InitViewContext();
    UpdateViewContext();
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/draw", DrawWorldEffectsPass);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/draw", InitAlphaPal);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/draw", FontPrintCenterScaled);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/draw", DrawTimedHelpMsg);
