#ifndef DRAW_H
#define DRAW_H

#include "moby.h"

struct GeometryQuad {
    Vec4 positions[4];
    unsigned int colors[4];
    float textureCoordinates[4][2];
    unsigned long long state[4];
};
void FastDrawQuadReal(GeometryQuad *quad, int flags, int mode);

extern int mobyVu1State;
void ComposeCameraMatrix(void);
void CleanAnimationCache(void);
void DrawMobys(void);
void SkySpace(void);
void PatchMobyGifs(void);
void SetScreenClearColorPacket(int red, int green, int blue, int alpha);

struct MobyInstance;
typedef void (*DrawMobyCallback)(MobyInstance *moby);

enum { DRAW_CALLBACK_LIMIT = 64 };

void DrawRoundedRect(int top, int bottom, int left, int right, int rgba);
void DrawTextShadow(int top, int bot, int left, int right, int alpha);
void DrawSprite(int sc_x, int sc_y, int sc_w, int sc_h, int tx_u, int tx_v, int tx_w, int tx_h, unsigned long rgba, unsigned long tex0);

// Starts and ends a VU1 frame packet chain.
void FlipAndExploreTimersVU1(int arg);
void FinalizeVU1FramePacketChain(void);

// Frame counter of the GS display.
extern int gsFrame;
// Nonzero when the console is running in PAL mode.
extern int videoModePal;

extern float screenFade;

// What the frame draws (RenderFlags).
enum RenderFlag {
    RENDER_SKY = 0x1,
    RENDER_TFRAGS = 0x2,
    RENDER_TIES = 0x4,
    RENDER_SHRUBS = 0x8,
    RENDER_MOBYS = 0x10,
    // World effects, moby effects and particles. The PS3 build calls this bit Ocean.
    RENDER_EFFECTS = 0x20,
    RENDER_SCREEN_OVERLAYS = 0x40,
    RENDER_HUD = 0x80,
    RENDER_DEBUG = 0x10000,
};

extern int RenderFlags;
void FadeToBlack(int frames);

// Which scene layers are drawn, and whether their textures are paged into GS memory this frame.
enum { DRAW_CONFIG_ENABLE_COUNT = 20 };

struct DrawConfig {
    union {
        int enables[DRAW_CONFIG_ENABLE_COUNT];
        struct {
            int unk_00;
            int sky_texture_paging;
            int sky;
            int tfrag_texture_paging;
            int tfrag;
            int tie_texture_paging;
            int tie;
            int shrub_texture_paging;
            int shrub;
            int moby_texture_paging;
            int mobys;
            int unk_2C;
            int moby_vu1_data;
            int post_draws;
            int particles;
            int pre_draws;
            int hud;
            int screen_overlays;
            int aa_blur;
        };
    };
};

extern DrawConfig drawConfig;

void InitViewContext(void);
void UpdateViewContext(void);

int FontLen(char *s, int len);

int FontLenSmall(char *text, int length);

int FontLenLarge(char *text, int length);

void EnableFontColors(void);

void DisableFontColors(void);

void CallDrawOverlayIfNoCutscene(void);

int FontLenWithTable(char *text, int length, unsigned char *metrics);

void EndAuxDrawMode(void);

void RegisterMobyDraw(DrawMobyCallback draw, MobyInstance *moby);

void RegisterPreDraw(DrawMobyCallback draw, MobyInstance *moby);

void STUB_00218990(void);

void ResetDebugEnables(void);

void SetupDefaultDrawMovie(int black);

void ResetLevelCounters(void);


// A full-screen colour wash; DrawScreenInsertEffect sets the alpha register from alpha and fills the screen.
struct ScreenInsertEffect {
    int enabled;
    unsigned int color;
    unsigned long alpha;
};

// The colour washes the level starts with (space levels get their own).
extern ScreenInsertEffect ScreenColorEffectDefault __attribute__((section(".data")));
extern ScreenInsertEffect ScreenColorEffectSpace __attribute__((section(".data")));
extern ScreenInsertEffect *ScreenColorEffectNow;
extern ScreenInsertEffect *volatile ScreenColorEffectLevel;

void ResetDrawGlobals(void);
void UpdateFog(void);
// 1 switches the frame timing to PAL, 0 to NTSC.
void SetNtscPalTiming(int pal);

// The level's fog colour, distances and intensities, from the gameplay file.
extern unsigned char DrawSdata15F444;
extern unsigned char DrawSdata15F445;
extern unsigned char DrawSdata15F446;
extern float DrawSdata15F448;
extern float DrawSdata15F44C;
extern float DrawSdata15F450;
extern float DrawSdata15F454;
// The occlusion grid of the level, if it has one.
extern char *OcclGrid;

void SetupFogColorGsReg(void);
void ResetGsRegistersPr(void);

#endif
