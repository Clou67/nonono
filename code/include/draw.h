#ifndef DRAW_H
#define DRAW_H

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

int FontLen(char *text, int length);

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

#endif
