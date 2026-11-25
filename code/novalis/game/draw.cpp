#include "common.h"
#include "font.h"
#include "framebuf.h"
#include "draw.h"
#include "fastfunc.h"
#include "viewcontext.h"
#include "mathfunc_inline.h"
#include "tfrag.h"
#include "sce.h"
#include "gameglobals.h"
#include "lights.h"
#include "update.h"
#include "help.h"
#include "camera.h"
#include "vuchain.h"
#include "shrub.h"
#include "tie.h"
#include "sky.h"
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

// Rebuilds everything in VC that follows from the screen size, the view angle, the clip planes and the fog,
// and the copies of it that the renderers and VU1 programs read.
void UpdateViewContext(void)
{
    float zscale;
    float zoffset;
    float xclipRadpad;
    float yclipRadpad;
    float fogRange;
    float fogSpan;
    float fogMult;
    float nearClip;
    float projNearClip;
    float farClip;
    float fog0;
    float projFog0;
    float xratio;
    float yratio;
    float xpix;
    float ypix;
    int nearBits;
    int farBits;
    int fogBits;

    zscale = -8388080.0f;
    zoffset = 8388112.0f;
    if (videoModePal) {
        VC.yratio = VC.xratio * 0.756f;
    } else {
        VC.yratio = VC.xratio * 0.775f;
    }
    VC.xclipratio = VC.xclip / VC.xpix;
    VC.yclipratio = VC.yclip / VC.ypix;
    VC.xradpad = 1.0f / FastAngleSinF(FastArcTan(1.0f, VC.xratio));
    VC.yradpad = 1.0f / FastAngleSinF(FastArcTan(1.0f, VC.yratio));
    xclipRadpad = 1.0f / FastAngleSinF(FastArcTan(1.0f, VC.xratio * VC.xclipratio));
    yclipRadpad = 1.0f / FastAngleSinF(FastArcTan(1.0f, VC.yratio * VC.yclipratio));
    xclipRadpad /= VC.xradpad;
    yclipRadpad /= VC.yradpad;
    VC.sphereCheckA.z = 1.0f / VC.xclipratio;
    VC.sphereCheckA.w = 1.0f / VC.yclipratio;
    VC.sphereCheckB.x = VC.xradpad;
    VC.sphereCheckB.y = VC.yradpad;
    VC.sphereCheckC.x = VC.farClip;
    VC.sphereCheckA.x = VC.xclipratio;
    VC.sphereCheckA.y = VC.yclipratio;
    nearClip = VC.nearClip;
    VC.sphereCheckC.y = nearClip;
    VC.sphereCheckB.z = (xclipRadpad + yclipRadpad) * 0.5f;
    CopyVec4Inline(&FastFrustum[4], (Vec4 *)&VC.xratio);
    CopyVec4Inline(&FastFrustum[5], &VC.sphereCheckA);
    CopyVec4Inline(&FastFrustum[6], &VC.sphereCheckB);
    CopyVec4Inline(&FastFrustum[7], &VC.sphereCheckC);

    farBits = *(int *)&VC.fogFarIntensity;
    nearBits = *(int *)&VC.fogNearIntensity;
    fogRange = VC.fogFarDist - VC.fogNearDist;
    fogSpan = VC.fogFarIntensity - VC.fogNearIntensity;
    fog0 = fogSpan * nearClip / fogRange;
    fogMult = fogSpan / (fogRange * 0.0009765625f);
    VC.fog1 = (VC.fogNearIntensity * VC.fogFarDist - VC.fogFarIntensity * VC.fogNearDist) / fogRange;
    VC.fogMult = fogMult;
    VC.fogAdd = VC.fogNearIntensity - VC.fogNearDist * 0.0009765625f * fogMult;
    VC.fog0 = fog0;
    RenderConsts1 = fog0;
    stripvif_head[12] = fog0;
    watertile_blockvif_head[12] = fog0;
    fogBits = *(int *)&VC.fog0;
    tfrag_setup_consts.fog0 = fogBits;
    tfrag_setup_consts.fogFarIntensity = farBits;
    tfrag_setup_consts.fogNearIntensity = nearBits;
    shrub_setup_consts.fog0 = fogBits;
    shrub_near_setup_consts.fog0 = fogBits;
    shrub_setup_consts.fogFarIntensity = farBits;
    shrub_setup_consts.fogNearIntensity = nearBits;
    shrub_near_setup_consts.fogFarIntensity = farBits;
    shrub_near_setup_consts.fogNearIntensity = nearBits;
    shrub_setup_consts.max = 0x437EFFFF;
    shrub_near_setup_consts.max = 0x437EFFFF;
    SetTfragDists();

    projNearClip = VC.nearClip;
    farClip = VC.farClip;
    xratio = VC.xratio;
    yratio = VC.yratio;
    xpix = VC.xpix;
    ypix = VC.ypix;
    projFog0 = VC.fog0;
    part_constants[0] = 0.5f / 210000.0f;
    part_constants[1] = -0.5f / 210000.0f;
    part_constants[2] = 0.5f;
    part_constants[3] = xpix / (xratio * 210000.0f);
    VC.fMtx.v0.x = xpix / (xratio * projNearClip);
    VC.fMtx.v0.y = 0.0f;
    VC.fMtx.v0.z = 0.0f;
    VC.fMtx.v0.w = 0.0f;
    VC.fMtx.v1.x = 0.0f;
    VC.fMtx.v1.y = ypix / (yratio * projNearClip);
    VC.fMtx.v1.z = 0.0f;
    VC.fMtx.v1.w = 0.0f;
    VC.fMtx.v2.x = 0.0f;
    VC.fMtx.v2.y = 0.0f;
    VC.fMtx.v2.z = (farClip + projNearClip) / (projNearClip * (farClip - projNearClip)) * zscale;
    VC.fMtx.v2.w = 1.0f / projNearClip * projFog0;
    VC.fMtx.v3.x = 0.0f;
    VC.fMtx.v3.y = 0.0f;
    VC.fMtx.v3.z = -2.0f * projNearClip * farClip / (projNearClip * (farClip - projNearClip)) * zscale;
    VC.fMtx.v3.w = 0.0f;
    FastMemCopy32(&VC.nfMtx, &VC.fMtx, sizeof(Mtx4));
    VC.nfMtx.v2.w = 1.0f / VC.nearClip;
    FastMemCopy32(&VC.hMtx, &VC.nfMtx, sizeof(Mtx4));
    VC.hMtx.v0.x /= VC.xclip;
    VC.hMtx.v1.y /= VC.yclip;
    VC.hMtx.v2.z /= zscale;
    VC.hMtx.v3.z /= zscale;
    VC.hmgScale.x = 1.0f / VC.xclip;
    VC.hmgScale.y = 1.0f / VC.yclip;
    VC.hmgScale.z = 1.0f / zscale;
    VC.hmgScale.w = 1.0f / VC.fog0;
    VC.ihmgScale.x = VC.xclip;
    VC.ihmgScale.y = VC.yclip;
    VC.ihmgScale.z = zscale;
    VC.ihmgScale.w = VC.fog0;
    VC.unSquish.x = VC.xclip / VC.fMtx.v0.x;
    VC.unSquish.y = VC.yclip / VC.fMtx.v1.y;
    VC.unSquish.z = zscale / VC.fMtx.v2.z;
    VC.unSquish.w = VC.fog0;
    VC.hvdf.x = 2048.0f;
    VC.hvdf.y = 2048.0f;
    VC.hvdf.z = zoffset;
    VC.hvdf.w = VC.fog1;
    VC.guard.x = VC.xclip / VC.xpix;
    VC.guard.y = VC.yclip / VC.ypix;
    VC.guard.z = 1.0f;
    VC.guard.w = 1.0f;

    VC.headerBase[0][0] = *(int *)&VC.fogFarIntensity;
    VC.headerBase[0][1] = 0x103E4000;
    VC.headerBase[0][2] = 0xE;
    VC.headerBase[0][3] = 0;
    ZeroVec4Inline((Vec4 *)VC.headerBase[1]);

    VC.headerTex[0] = *(int *)&VC.fog0;
    VC.headerTex[1] = 0x303E4000;
    VC.headerTex[2] = 0x412;
    VC.headerTex[3] = 0x303EC000;
    VC.headerTexNoFog[0] = *(int *)&VC.fog0;
    VC.headerTexNoFog[1] = 0x302E4000;
    VC.headerTexNoFog[2] = 0x412;
    VC.headerTexNoFog[3] = 0x302EC000;
    VC.headerGr[0] = *(int *)&VC.fog0;
    VC.headerGr[1] = 0x20364000;
    VC.headerGr[2] = 0x41;
    VC.headerGr[3] = 0;
    VC.headerGrNoFog[0] = *(int *)&VC.fog0;
    VC.headerGrNoFog[1] = 0x20264000;
    VC.headerGrNoFog[2] = 0x41;
    VC.headerGrNoFog[3] = 0;
    CopyVec4Inline((Vec4 *)VC.headerBase[1], (Vec4 *)VC.headerTex);
    CopyVec4Inline((Vec4 *)VC.headerBase[2], &VC.guard);
    CopyVec4Inline((Vec4 *)VC.headerBase[3], &VC.hmgScale);
    CopyVec4Inline((Vec4 *)VC.headerBase[4], &VC.ihmgScale);
    CopyVec4Inline((Vec4 *)VC.headerBase[5], &VC.hvdf);
    CopyVec4Inline(&ViewConstsA[0], &VC.hvdf);
    CopyVec4Inline(&ViewConstsA[1], &VC.ihmgScale);
    CopyVec4Inline(&ViewConstsA[2], &VC.guard);
    CopyVec4Inline(&tfrag_setup_consts.hvdf, &VC.hvdf);
    CopyVec4Inline(&tfrag_setup_consts.hmgScale, &VC.hmgScale);
    CopyVec4Inline(&tfrag_setup_consts.ihmgScale, &VC.ihmgScale);
    tfrag_setup_consts.guardX = *(int *)&VC.guard.x;
    tfrag_setup_consts.guardY = *(int *)&VC.guard.y;
    CopyVec4Inline(&shrub_near_setup_consts.ihmgScale, &VC.ihmgScale);
    CopyVec4Inline(&shrub_near_setup_consts.hvdf, &VC.hvdf);
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/draw", SetUserViewContext);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/draw", SetPalMode);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/draw", ResetDrawGlobals);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/draw", SetupFogColorGsReg);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/draw", ResetGsRegistersPr);

// A full-screen colour wash; DrawScreenInsertEffect sets the alpha register from alphaReg and fills the screen.
struct ScreenInsertEffect {
    int enabled;
    unsigned int color;
    unsigned long alphaReg;
};

extern float g_SceneFlash;
// Debug switches for the draw loop.
struct DrawDebugState {
    int occlMode;
    char unk_04[0x14];
    int forceClear;
};

extern DrawDebugState DrawDebug;
extern ScreenInsertEffect ScreenColorEffectDefault;
extern int OcclMode;
extern int PostDrawCnt;
extern int PostPreDrawCnt;
extern int MobyFnListCnt;
extern int PreDrawCnt;
extern int mobyVu1State;
extern unsigned char g_UnderwaterTintR;
extern unsigned char g_UnderwaterTintG;
extern unsigned char g_UnderwaterTintB;
extern unsigned char g_UnderwaterTintA;
extern unsigned char g_SubtitlesOn;
extern long LightVU0Program[];


void ComposeCameraMatrix(void);
void CleanAnimationCache(void);
void UpdateOcclusion(void);
void SetupFogColorGsReg(void);
void ExecutePostDraws(void);
void ExecutePostPreDraws(void);
void ExecuteRegisteredMobyFuncs(void);
void ExecutePreDraws(void);
void DrawLameShadows(void);
void DrawWorldEffectsPass(void);
void DrawMobys(void);
void Camera_DrawReticule(void);
void PartProc(void);
void ImpactSprite_Draw(void);
void TargetCrosshairDraw(void);
void DrawGameplayHud(void);
void UpdateLetterBox(void);
void DrawSubtitles(void);
void SetScreenClearColorPacket(int r, int g, int b, int a);
void DrawScreenEffect(void);
void DrawScreenInsertEffect(ScreenInsertEffect *effect);
void LightTfrags(void *sprStash);
void LightShrubs(void *sprStash);
void PatchMobyGifs(void);
void UpdateFog(void);

// draw.cpp's small data, in retail order. The variables DefaultDraw reads through $gp are defined
// before it; the rest come after it, since retail reaches those with lui.
int DrawSdata15F2F0 = 0;
int DrawSdata15F2F4 = 0;
int DrawSdata15F2F8 = 0;
int DrawSdata15F2FC = 0;
int DrawSdata15F300 = 0;
int DrawSdata15F304 = 0;
float DrawSdata15F308 = 0.0f;
int ScreenColorEffectEnabled = 0;
ScreenInsertEffect *ScreenColorEffectNow = &ScreenColorEffectDefault;
int DrawSdata15F314 = 0;
int ScreenColorEffectLevel = 0;
int DrawSdata15F31C = 0;
int DrawSdata15F320 = 0;
int DrawSdata15F324 = 0;
int DrawSdata15F328 = 0;
int DrawSdata15F32C = 0;
ScreenInsertEffect g_ScreenInsertEffect = { 0, 0, 0 };

// Draws the frame: the sky, the tfrags, ties, shrubs and mobys, the effects, the HUD and the screen
// overlays, then lights and patches the next frame's packets while VU1 works through this one.
void DefaultDraw(void)
{
    int clearColor; // never set: retail passes whatever is in $a0

    if (Sky == 0 || Sky->clear_screen != 0 || !(RenderFlags & RENDER_SKY) || drawConfig.sky == 0 || DrawDebug.forceClear != 0) {
        ClearDrawBufferLarge(clearColor);
    }
    ComposeCameraMatrix();
    CleanAnimationCache();
    UpdateOcclusion();
    SetupFogColorGsReg();
    mobyVu1State = -1;
    printf_stub2("render setup", 15);
    printf_stub3("render setup", 15);

    if (Sky != 0 && (RenderFlags & RENDER_SKY)) {
        if (drawConfig.sky) {
            InitSky();
        }
        printf_stub3("sky draw", 14);
        printf_stub2("sky draw", 14);
    }

    if (RenderFlags & RENDER_TFRAGS) {
        DrawTfrag();
    }
    Vif1ChainCmd(VIF_CHAIN_STAGE_1);

    if (RenderFlags & RENDER_TIES) {
        if (videoModePal) {
            DrawTiesEx();
        } else {
            DrawTie();
        }
    }
    Vif1ChainCmd(VIF_CHAIN_STAGE_2);

    if (drawConfig.post_draws && PostDrawCnt) {
        VU1_gsRegsEffects();
        FlipAndExploreTimersVU1(1);
        ExecutePostDraws();
        FinalizeVU1FramePacketChain();
        VU1_gsRegsNormal();
    }
    printf_stub2("pre effects", 6);
    printf_stub3("pre effects", 6);

    if (RenderFlags & RENDER_SHRUBS) {
        DrawShrub();
    }
    Vif1ChainCmd(VIF_CHAIN_STAGE_3);

    if (drawConfig.screen_overlays && g_ScreenInsertEffect.enabled) {
        DrawScreenInsertEffect(&g_ScreenInsertEffect);
    }
    if (RenderFlags & RENDER_EFFECTS) {
        FlipAndExploreTimersVU1(1);
        DrawWorldEffectsPass();
        FinalizeVU1FramePacketChain();
    }
    if (drawConfig.post_draws && PostPreDrawCnt) {
        VU1_gsRegsEffects();
        FlipAndExploreTimersVU1(1);
        ExecutePostPreDraws();
        FinalizeVU1FramePacketChain();
        VU1_gsRegsNormal();
    }

    if (RenderFlags & RENDER_MOBYS) {
        DrawMobys();
    }
    Vif1ChainCmd(VIF_CHAIN_STAGE_4);
    FlipAndExploreTimersVU1(0);

    if ((RenderFlags & RENDER_EFFECTS) && drawConfig.moby_vu1_data && mobyVu1State != 6) {
        VU1_addDataRef(MobyVU1Data, MobyVu1HeaderData.qwc);
        mobyVu1State = 6;
    }
    printf_stub3("vu effects", 4);
    printf_stub2("vu effects", 4);

    if (RenderFlags & RENDER_EFFECTS) {
        VU1_gsRegsEffects();
        if (drawConfig.post_draws) {
            if (MobyFnListCnt) {
                ExecuteRegisteredMobyFuncs();
            }
            VU1_addGSregister(0x42, 0x8000000048);
            Camera_DrawReticule();
            VU1_gsRegsEffects();
            DrawLameShadows();
        }
        printf_stub2("moby effects", 6);
        printf_stub3("moby effects", 6);

        if (drawConfig.particles) {
            VU1_addGSregister(8, 5);
            VU1_gsRegsEffects();
            FlushCache(0);
            PartProc();
            mobyVu1State = 8;
        }
        printf_stub2("part draw", 8);
        printf_stub3("part draw", 8);

        if (drawConfig.pre_draws) {
            if (PreDrawCnt) {
                VU1_gsRegsEffects();
                ExecutePreDraws();
            }
            if (gameMode == 0) {
                ImpactSprite_Draw();
            }
            VU1_addGSregister(0x42, 0x8000000044);
            TargetCrosshairDraw();
        }
        printf_stub2("post effects", 6);
        printf_stub3("post effects", 6);
    }

    if (drawConfig.aa_blur) {
        AA_BlurPass();
    }
    printf_stub3("aa blur", 15);
    VU1_gsRegsEffects();

    if (RenderFlags & RENDER_DEBUG) {
        update_stub();
    }
    if ((RenderFlags & RENDER_HUD) && drawConfig.hud) {
        DrawGameplayHud();
        Help_Draw();
        UpdateLetterBox();
    }
    if (gameMode == 2 && g_SubtitlesOn) {
        DrawSubtitles();
    }
    printf_stub3("hud", 14);
    printf_stub2("hud", 14);
    FinalizeVU1FramePacketChain();

    if (RenderFlags & RENDER_SCREEN_OVERLAYS) {
        if (drawConfig.screen_overlays) {
            VU1_addGSregister(0x42, 0x8000000044);
            if (GameCamera.camUnderWater) {
                SetScreenClearColorPacket(g_UnderwaterTintR, g_UnderwaterTintG, g_UnderwaterTintB, g_UnderwaterTintA);
            }
            if (screenFade > 0.0f) {
                if (screenFade > 1.0f) {
                    screenFade = 1.0f;
                }
                SetScreenClearColorPacket(0, 0, 0, FastFloatToInt(screenFade * 128.0f));
            }
            if (g_SceneFlash > 0.0f) {
                if (g_SceneFlash > 1.0f) {
                    g_SceneFlash = 1.0f;
                }
                SetScreenClearColorPacket(255, 255, 255, FastFloatToInt(g_SceneFlash * 128.0f));
            }
            if (ScreenColorEffectEnabled && ScreenColorEffectNow) {
                DrawScreenEffect();
            }
        }
        printf_stub3("screen overlays", 10);
    }

    // Light and patch next frame's packets while VU1 draws this one.
    VU0_loadMicroProgram(LightVU0Program);
    FlushCache(0);
    PerfLoad = FastIntToFloat(*T0_COUNT) / (videoModePal ? 11520.0f : 9600.0f);

    VU1_syncChain(2);
    printf_stub2("", 17);
    if (RenderFlags & RENDER_TFRAGS) {
        if (drawConfig.tfrag) {
            LightTfrags(TfragSprStash);
            PatchTfragGifs();
        }
        printf_stub2("tfrag patch-light", 2);
    }

    VU1_syncChain(4);
    printf_stub2("", 17);
    if (RenderFlags & RENDER_TIES) {
        if (drawConfig.tie) {
            if (videoModePal) {
                RefreshTieLights();
                UpdateTieTextures();
            } else {
                LightTies(TieSprStash);
                PatchTieGifs();
            }
        }
        printf_stub2("tie patch-light", 5);
    }

    VU1_syncChain(8);
    printf_stub2("", 17);
    if (RenderFlags & RENDER_SHRUBS) {
        if (drawConfig.shrub) {
            LightShrubs(ShrubSprStash);
            PatchShrubGifs();
        }
        printf_stub2("shrub patch-light", 7);
    }

    VU1_syncChain(0x10);
    printf_stub2("", 17);
    if (RenderFlags & RENDER_MOBYS) {
        if (drawConfig.mobys) {
            PatchMobyGifs();
        }
        printf_stub2("moby patch", 3);
    }

    UpdateFog();
    OcclMode = 0;
}




INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/draw", SetupDefaultDraw);

extern int CutscenePlaying;
void DefaultDraw(void);

void SetupDefaultDrawMovie(int black)
{
    if (!CutscenePlaying) {
        ClearDrawBufferLarge(black);
        RenderFlags = RENDER_SKY | RENDER_TFRAGS | RENDER_TIES | RENDER_SHRUBS | RENDER_MOBYS | RENDER_EFFECTS |
                      RENDER_SCREEN_OVERLAYS;
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

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/draw", DrawScreenInsertEffect);

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

// The rest of draw.cpp's small data. Defined last so every function above reaches it the way retail
// does (lui, or $gp only where the compiler fills a delay slot).
int RenderFlags = 0;
int gsFrame = 0;
float screenFade = 0.0f;
float g_SceneFlash = 0.0f;
int DrawSdata15F404 = 0;
int DrawSdata15F408 = 0;
int DrawSdata15F40C = 0;
int DrawSdata15F410 = 0;
int DrawSdata15F414 = 0;
int GifLoadCnt = 0;
int DrawSdata15F41C = 0;
int DrawSdata15F420 = 0;
int MobyFnListCnt = 0;
int PreDrawCnt = 0;
int PostDrawCnt = 0;
int PostPreDrawCnt = 0;
int DrawSdata15F434 = 0;
int DrawSdata15F438 = 0;
int DrawSdata15F43C = 0;
int DrawSdata15F440 = 0;
unsigned char DrawSdata15F444 = 0;
unsigned char DrawSdata15F445 = 0;
unsigned char DrawSdata15F446 = 0;
float DrawSdata15F448 = 0.0f;
float DrawSdata15F44C = 0.0f;
float DrawSdata15F450 = 0.0f;
float DrawSdata15F454 = 0.0f;
int DrawSdata15F458 = 0;
int FontColorsEnabled = 0;
int DrawSdata15F460 = 0;
