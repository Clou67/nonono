#include "libc.h"
#include "font.h"
#include "hud.h"
#include "camera.h"
#include "common.h"
#include "draw.h"
#include "fastfunc.h"
#include "freeze.h"
#include "gameglobals.h"
#include "hero.h"
#include "lights.h"
#include "loaders.h"
#include "mathfunc_inline.h"
#include "mobyclasses.h"
#include "mobyutil.h"
#include "music.h"
#include "pad.h"
#include "path.h"
#include "pause.h"
#include "sound.h"
#include "space.h"
#include "initlevel.h"
#include "wad.h"
#include "mcstate.h"
#include "galaxymap.h"
#include "framebuf.h"
#include "viewcontext.h"
#include "vuchain.h"

extern unsigned char FinishedLoading[]; // incomplete type: retail stores to it
                                        // with lui/sb, not $gp
extern Vec4 ShipTrailOffsets[3][2];
extern Vec4 ShipRatchetOffsets[3];
extern Vec4 ShipClankOffsets[3];
extern float g_SceneFlash;
extern float frameTime;
extern float frameTimeSq __attribute__((section(".sdata")));

int SpaceshipPreplaced __attribute__((section(".sdata"))) = 0;
int SpaceshipOClasses[3] = {531, 532, 533};
int SpaceshipOClassesB[3] = {535, 536, 537};
int SpaceEnvRefresh __attribute__((section(".sdata"))) = 1;
int SpaceEnvWasActive __attribute__((section(".sdata"))) = 1;
int SpaceEnvTimer __attribute__((section(".sdata"))) = 0;
int SpaceTransitionSequenceFrames[3] = {240, 240, 240};
int SpaceVariantEffectQuadCounts[3] = {8, 2, 2};
float SpaceWarpTrailWidths[3] = {0.8f, 0.8f, 0.8f};

// Loading-screen quad placement and its motion per frame.
Vec4 SpaceQuadBase __attribute__((section(".sdata"))) = {-370.0f, -280.0f, 280.0f, 0.0f};
Vec4 SpaceQuadOffset __attribute__((section(".sdata"))) = {0.0f, 0.0f, 0.0f, 0.0f};
Vec4 SpaceQuadStep __attribute__((section(".sdata"))) = {0.3f, 0.5f, 0.0f, 0.0f};

// Frame each take-off cutscene skips to, per ship variant.
int ShipTakeoffSkipFrames[3] = {558, 558, 558};

int SpaceEnvColors[4] = {0x50807060, 0x30807060, 0x30807060, 0x302080FF};
int SpaceEnvVertexCounts[4] = {102, 39, 49, 42};
int SpaceEnvQuadCounts[4] = {74, 24, 48, 30};
Vec4 *SpaceEnvNormals[4] = {SpaceEnvNormals0, SpaceEnvNormals1, SpaceEnvNormals2, SpaceEnvNormals3};
Vec4 *SpaceEnvPositions[4] = {SpaceEnvPositions0, SpaceEnvPositions1, SpaceEnvPositions2, SpaceEnvPositions3};
IndexedQuad *SpaceEnvQuads[4] = {SpaceEnvQuads0, SpaceEnvQuads1, SpaceEnvQuads2, SpaceEnvQuads3};


enum {
    SPACE_LOADING_EARLY_PROGRESSION = 4,
    SPACE_CUTSCENE_TAKEOFF = 0,
    SPACE_CUTSCENE_FLIGHT = 3,
    SPACE_CUTSCENE_LOADING = 4,
    SPACE_CUTSCENE_ARRIVAL = 8
};

void ResetGameCounters(void);
void UpdateMobyChain(void);
void sound_UpdateAmbient(void);
void HeroUpdate(void);
void UpdateParts(void);
void UpdateGameCounters(void);
void Space_UpdateCutsceneScene(void);
void Space_DrawTransitionOverlay(MobyInstance *moby);
void Space_DrawLoadingBanner(MobyInstance *moby);
void Space_DrawShipEngineGlow(MobyInstance *moby);
void Space_DrawShipEffects(MobyInstance *moby);
void Space_SpawnShipParticles(MobyInstance *ship, float zVel);
void BeginMenu(int menu);
void Hero_MakeVisible(void);
void SetPositionAfterMovie(void);
void Hero_AddPulsingMobyGlow(MobyInstance *moby);
void Hero_UpdateInScene(MobyInstance *moby);
void Hero_SnapMobyToBonePose(MobyInstance *hero, MobyInstance *attachment);
void MB_SetZBoundsFromFloorCeil(MobyInstance *moby);
void UpdateMobyFrameData(MobyInstance *moby);
float FastScaleBySpeed(float value);
float FastSubRots(float first, float second);
void FastVecZero(Vec4 *vector);
void FastVecLerp(Vec4 *out, Vec4 *from, Vec4 *to, float amount);
void FastVec3Cross(Vec4 *out, Vec4 *first, Vec4 *second);
void camPolarInit(Mtx4 *matrix);
void camPolarRot0(Mtx4 *out, Mtx4 *in, float angle);
void camPolarRot1(Mtx4 *out, Mtx4 *in, float angle);
void camPolarRot2(Mtx4 *out, Mtx4 *in, float angle);
float OrganicDelt(float *value, float *velocity, float target, float accel, float decel,
                  float limit);
void FUN_00316ef8(Vec4 *position, PolarSm *rotation, int flags, int unk0, int unk1);
void FUN_00316dd0(Vec4 *position);
void FUN_00316e28(Vec4 *rotation);
void MB_PathEvalSpline(MobyPath *path, int unk, Vec4 *position, Vec4 *rotation, int flags,
                       float progress);
int sceGsSyncV(int mode);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/space", UpdateMoby_Spaceship);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/space", Space_SetCutsceneCamera);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/space", Space_DrawLoadingBanner);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/space", SetupSpaceShipVars);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/space", Space_DisableShip);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/space", Space_EnableShip);

void space_PlayCutscene(int cutscene)
{
    MobyInstance *moby;
    int speechTrack, shipVariant, sceneIndex, arrivalScene, sceneWorkspaceOffset;

    bootSpaceTransitionState.timer = -1;
    CutscenePlaying = 1;
    bootSpaceTransitionState.cutscene = cutscene;
    bootSpaceTransitionState.o2Mask = 0;

    FastMemSet(&SceneLoad, 0, 0x1C0);
    FastMemSet(SceneScratchA, 0, 0x40);
    FastMemSet(SceneScratchB, 0, 0x40);

    VU1_setBufSizeByLevel();
    sceneWorkspaceOffset = vu1_bufSize - 0x60000;
    SceneLoad.decodedChunk = MemSlots.vu1_chain[0] + sceneWorkspaceOffset;
    SceneLoad.buffer = MemSlots.vu1_chain[1] + sceneWorkspaceOffset;
    screenFade = 1.0f;
    gameMode = GAME_MODE_SPACE;
    vu1_bufSize = sceneWorkspaceOffset;
    g_SceneFlash = 0.0f;

    Hero_InitBodyState(HERO_STATE_CUSTOM_UI, 2);
    Hero.invisible = 1;
    Hero_MakeInvisible();

    bootSpaceTransitionState.spaceship->modeBits |= DISABLED;
    for (moby = MobyInstancePermEnd; moby->state != 0xFF; moby++)
        if (!(moby->state & 0x80) &&
            ((short)moby->oClass == OCLASS_MINE_74 || (short)moby->oClass == OCLASS_DECOY))
            moby->modeBits |= NO_DRAW;

    if (cutscene == SPACE_CUTSCENE_TAKEOFF) {
        shipVariant = bootSpaceTransitionState.shipVariant;
        sceneIndex = shipVariant + 1;
        speechTrack = shipVariant + 6;
        if (Level == LEVEL_ORXON && shipVariant == 1 && UnlockableItems[ITEM_O2_MASK] == 0) {
            sceneIndex = 0;
            speechTrack = 11;
        }

        else if (Level == LEVEL_OLTANIS && bootSpaceTransitionState.shipVariant == 2) {
            sceneIndex = 8;
            speechTrack = 14;
        }
        LoadSpaceScene(sceneIndex, FastScaleRoundInt(6));
    }

    else {
        int arrivalPending, fadeFrames;
        shipVariant = bootSpaceTransitionState.shipVariant;
        arrivalPending = bootSpaceTransitionState.arrivalPending;
        speechTrack = shipVariant + 3;
        if (arrivalPending)
            speechTrack = shipVariant;
        arrivalScene = shipVariant + 5;
        if (Level == LEVEL_ORXON && shipVariant == 1 && UnlockableItems[ITEM_O2_MASK] == 0) {
            speechTrack = 10;
            if (arrivalPending)
                speechTrack = 9;
            arrivalScene = 4;
        }

        else if (Level == LEVEL_OLTANIS && bootSpaceTransitionState.shipVariant == 2) {
            speechTrack = 13;
            if (bootSpaceTransitionState.arrivalPending)
                speechTrack = 12;
            arrivalScene = 9;
        }
        fadeFrames = 0;
        if (!bootSpaceTransitionState.arrivalPending)
            fadeFrames = FastScaleRoundInt(6);
        LoadSpaceScene(arrivalScene, fadeFrames);
    }

    musicTransition.queuedSpeech = speechTrack + MUSIC_SCENE_SPEECH_BASE;
    ParseSpaceSceneChunk(0);
    while (musicTransition.state != MUSIC_STATE_READY) {
        sound_Update();
        sceGsSyncV(0);
    }

    music_PlayPreseekedSpeech();
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/space", Space_StartTakeoffCutscene);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/space", StartLeaveLevelCutscene);

extern int CutscenePlaying;

void ChangeLevel(int level)
{
    g_newlevelnum = level;
    g_newlevel = 1;
    CutscenePlaying = 1;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/space", space_StartLevelArrival);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/space", Space_DrawShipEngineGlow);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/space", Space_DrawShipEffects);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/space", Space_DrawQuadStrip);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/space", Space_DrawHelper);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/space", Space_UpdateCutsceneScene);

void TransitionDraw_Space(void)
{
    float rotationAngle;
    float screenY;
    float quadExtent;
    int overlayAlpha;
    float savedXRatio;
    Screen *screen;
    unsigned long texture;

    // Retail omits the ignored black argument.
    ((void (*)(void))ClearDrawBufferLarge)();
    ComposeCameraMatrix();
    CleanAnimationCache();
    SetupFogColorGsReg();

    savedXRatio = VC.xratio;
    mobyVu1State = -1;
    if (savedXRatio < 0.63f)
        VC.xratio = 0.63f;

    UpdateViewContext();
    ComposeCameraMatrix();
    SkySpace();
    VC.xratio = savedXRatio;

    UpdateViewContext();
    ComposeCameraMatrix();

    if (bootSpaceTransitionState.loadingScreen == SPACE_LOADING_EARLY_PROGRESSION) {
        FlipAndExploreTimersVU1(1);
        Space_DrawQuadStrip();
        FinalizeVU1FramePacketChain();
    }

    DrawMobys();
    Vif1ChainCmd(0x02080000);
    FlipAndExploreTimersVU1(1);

    if ((Level != LEVEL_VELDIN) && ((Level != LEVEL_NOVALIS) || (g_SeenPlanets[3] != 0)))
        Space_DrawShipEffects(SceneLoad.mobys[0]);

    if ((bootSpaceTransitionState.loadingScreen == SPACE_LOADING_EARLY_PROGRESSION) &&
        (SceneLoad.sceneFrame >= 0x3D)) {
        overlayAlpha = (SceneLoad.sceneFrame - 0x3C) * 2;
        if (overlayAlpha >= 0x81)
            overlayAlpha = 0x80;
        Space_DrawHelper(overlayAlpha);
    }

    if ((Level != LEVEL_VELDIN) && ((Level != LEVEL_NOVALIS) || (g_SeenPlanets[3] != 0)))
        Space_DrawTransitionOverlay(SceneLoad.mobys[0]);

    if ((g_memcard.stage >= MC_STAGE_FORMAT) || (g_memcard.nextstage >= MC_STAGE_GET_INFO)) {
        VU1_addGSregister(0x47, 0x3004B);
        quadExtent = 272.0f;
        texture = FontSet(2);
        screen = &Scrn;
        DrawSprite(0x2C, screen->paramY - 0x60, 0x40, 0x40, 0, 0, 0x40, 0x40, 0x80808080, texture);
        screenY = (float)((screen->paramY - 0x40) * 16);
        rotationAngle = ((gsFrame % 55) * (-6.2831855f)) / 55.0f;
        Hud_DrawRotatedSprite16(1216.0f, screenY, quadExtent, 272.0f, rotationAngle, 0x40, 0x40,
                                FontSet(3));
    }

    FinalizeVU1FramePacketChain();

    if (screenFade > 0.0f) {
        if (screenFade > 1.0f)
            screenFade = 1.0f;
        SetScreenClearColorPacket(0, 0, 0, FastFloatToInt(screenFade * 128.0f));
    }

    VU1_syncChain(0x10);
    PatchMobyGifs();
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/space", Space_SpawnShipParticles);



void UpdateSpace(void)
{
    Mtx4 scratch;
    int keyframeFlags;
    int ticksPerBank;
    int skip;
    int objectIndex;
    int pointIndex;
    MobyInstance *playbackObject;
    MobyInstance *objectCursor;
    MobyInstance *expiredObject;
    int releaseIndex;
    int bankTickLimit;
    MobyInstance *player;
    int pathPointIndex;
    float cameraBlendStep;

    SceneCameraFrame *keyframe;
    Vec4 *cameraPosition;
    float *keyframeAngles;
    Vec4 *animationPositions;
    int currentFrame;

    MobyPath *path;
    float segmentAngle;
    float maximumTurn;
    float turnScale;
    float blend;

    bootSpaceTransitionState.timer++;

    switch (bootSpaceTransitionState.cutscene) {
    case SPACE_CUTSCENE_TAKEOFF:
    case SPACE_CUTSCENE_ARRIVAL:
        ResetGameCounters();
        UpdateMobyChain();
        sound_UpdateAmbient();
        HeroUpdate();
        UpdateParts();
        screenFade -= 0.125f;
        SceneLoad.cameraFrame++;
        SceneLoad.sceneFrame++;

        if (screenFade < 0.0f)
            screenFade = 0.0f;

        ticksPerBank = videoModePal ? 0x50 : 0x60;
        skip = bootSpaceTransitionState.skip;

        if ((padState.bitsOn & (PAD_TRIANGLE | PAD_CROSS)) &&
            FastScaleRoundInt(30) < SceneLoad.sceneFrame && screenFade == 0.0f) {
            if (bootSpaceTransitionState.cutscene == SPACE_CUTSCENE_TAKEOFF &&
                SceneLoad.sceneFrame <
                    FastScaleRoundInt(ShipTakeoffSkipFrames[bootSpaceTransitionState.shipVariant] -
                                      30))
                skip = 1;

            if (bootSpaceTransitionState.cutscene == SPACE_CUTSCENE_ARRIVAL &&
                SceneLoad.sceneFrame < SceneLoad.numFrames - FastScaleRoundInt(30))
                skip = 1;
        }

        if (skip) {
            if (musicTransition.state != 6 && musicTransition.state != 7)
                musicTransition.state = 5;

            if (bootSpaceTransitionState.cutscene == SPACE_CUTSCENE_TAKEOFF) {
                SceneLoad.sceneFrame =
                    FastScaleRoundInt(ShipTakeoffSkipFrames[bootSpaceTransitionState.shipVariant]);
                SceneLoad.chunk = SceneLoad.sceneFrame / ticksPerBank;
                ParseSpaceSceneChunk(SceneLoad.chunk);
                SceneLoad.cameraFrame = SceneLoad.sceneFrame % ticksPerBank;

                if (bootSpaceTransitionState.skip)
                    bootSpaceTransitionState.skip = 0;

                else
                    FadeToBlack(4);

                screenFade = 1.0f;
            }

            else
                SceneLoad.sceneFrame = SceneLoad.numFrames;
        }

        if (SceneLoad.sceneFrame >= SceneLoad.numFrames) {
            if (musicTransition.state != 6 && musicTransition.state != 7)
                musicTransition.state = 5;

            VU1_setBufSizeByLevel();
            VC.xratio = 0.63f;
            UpdateViewContext();
            /* Retail releases the attachment once per screenFade object, even when
       * that object is null. */
            for (releaseIndex = 0; releaseIndex < SceneLoad.mobyCount; releaseIndex++) {
                expiredObject = SceneLoad.mobys[releaseIndex];

                if (expiredObject != 0) {
                    expiredObject->pClass->sequenceCount--;
                    expiredObject->pClass->animations[expiredObject->pClass->sequenceCount] = 0;
                    DeleteMoby(expiredObject);
                }

                if (bootSpaceTransitionState.o2Mask != 0)
                    DeleteMoby(bootSpaceTransitionState.o2Mask);
            }

            bootSpaceTransitionState.spaceship->modeBits &= ~1;

            for (objectCursor = MobyInstancePermEnd; objectCursor->state != 0xFF;
                 objectCursor++) {
                if (!(objectCursor->state & 0x80) &&
                    ((short)objectCursor->oClass == OCLASS_MINE_74 || (short)objectCursor->oClass == OCLASS_DECOY))
                    objectCursor->modeBits &= ~0x80;
            }

            if (bootSpaceTransitionState.cutscene == SPACE_CUTSCENE_TAKEOFF) {
                BeginMenu(0);
                PauseMenu.state = 0xE;
                CutscenePlaying = 1;
                return;
            }

            gameMode = 0;
            music_Unpause();
            CutscenePlaying = 1;
            FinishedLoading[0] = 0;
            Hero_MakeVisible();

            if (bootSpaceTransitionState.arrivalPending != 0) {
                SetPositionAfterMovie();
                return;
            }

            Hero_Warp(&bootSpaceTransitionState.arrivalPos.x,
                      &bootSpaceTransitionState.arrivalRot.x, 0, 1);
            return;
        }

        bankTickLimit = videoModePal ? 0x50 : 0x60;

        if (SceneLoad.cameraFrame >= bankTickLimit)
            ParseSpaceSceneChunk(++SceneLoad.chunk);

        keyframe = &SceneLoad.cameraFrames[SceneLoad.cameraFrame];
        keyframeAngles = &keyframe->rotX;
        keyframeFlags = keyframe->flags[0];
        VC.xratio = keyframeAngles[3];
        UpdateViewContext();
        cameraPosition = &GameCamera.position;
        CopyVec4Inline(cameraPosition, &keyframe->position);
        FastVecMtx3Mult(cameraPosition, cameraPosition,
                        &bootSpaceTransitionState.spaceship->transform);
        FastVec3Add(cameraPosition, cameraPosition, &bootSpaceTransitionState.spaceship->pos);
        segmentAngle =
            FastAddRots(keyframeAngles[2], bootSpaceTransitionState.spaceship->rotation.z);
        camPolarInit(&scratch);
        camPolarRot0(&scratch, &scratch, keyframe->rotX);
        camPolarRot1(&scratch, &scratch, keyframeAngles[1]);
        camPolarRot2(&scratch, &scratch, segmentAngle);
        GameCamera.orientMtx.forward.x = -scratch.v2.x;
        GameCamera.orientMtx.right.x = -scratch.v0.x;
        GameCamera.orientMtx.up.x = scratch.v1.x;
        GameCamera.orientMtx.forward.y = -scratch.v2.y;
        GameCamera.orientMtx.right.y = -scratch.v0.y;
        GameCamera.orientMtx.up.y = scratch.v1.y;
        GameCamera.orientMtx.forward.z = -scratch.v2.z;
        GameCamera.orientMtx.right.z = -scratch.v0.z;
        GameCamera.orientMtx.up.z = scratch.v1.z;

        if (CheatsActivated[4] != 0)
            FastVec3Cross(&GameCamera.orientMtx.right, &GameCamera.orientMtx.up,
                          &GameCamera.orientMtx.forward);

        for (objectIndex = 0; objectIndex < SceneLoad.mobyCount; objectIndex++) {
            playbackObject = SceneLoad.mobys[objectIndex];
            currentFrame = SceneLoad.cameraFrame >> 1;
            playbackObject->previousAnimationFrame = currentFrame;
            playbackObject->animationFrame = currentFrame + 1;
            UpdateMobyFrameData(playbackObject);
            playbackObject->animationBlend = FastIntToFloat(SceneLoad.cameraFrame & 1) * 0.5f;

            if (keyframeFlags != 0 && (SceneLoad.cameraFrame & 1))
                playbackObject->animationBlend = 1.0f;

            animationPositions = (Vec4 *)playbackObject->pVar;
            FastVec3Scale(&scratch.v0,
                          &animationPositions[playbackObject->previousAnimationFrame],
                          1.0f - playbackObject->animationBlend);
            FastVec3Scale(&scratch.v1, &animationPositions[playbackObject->animationFrame],
                          playbackObject->animationBlend);
            FastVec3Add(&playbackObject->pos, &scratch.v0, &scratch.v1);
            FastVecMtx3Mult(&playbackObject->pos, &playbackObject->pos,
                            &bootSpaceTransitionState.spaceship->transform);
            FastVec3Add(&playbackObject->pos, &playbackObject->pos,
                        &bootSpaceTransitionState.spaceship->pos);
            playbackObject->rotation.z = bootSpaceTransitionState.spaceship->rotation.z;
            playbackObject->unk71 = 0xFF;
            PostUpdateMoby(playbackObject);

            if ((short)playbackObject->oClass == OCLASS_RATCHET) {
                if (bootSpaceTransitionState.cutscene == SPACE_CUTSCENE_TAKEOFF) {
                    if (Level == LEVEL_ORXON && UnlockableItems[ITEM_O2_MASK] == 0)
                        playbackObject->shadow = 0;

                    else if (SceneLoad.sceneFrame <= FastScaleRoundInt(0x3E))
                        playbackObject->shadow = 0x18;

                    else
                        playbackObject->shadow = 0;
                }

                else if (FastScaleRoundInt(360) < SceneLoad.sceneFrame) {
                    if (Level == LEVEL_ORXON && UnlockableItems[ITEM_O2_MASK] == 0)
                        playbackObject->shadow = 0;

                    else
                        playbackObject->shadow = 0x18;
                }

                else
                    playbackObject->shadow = 0;
            }

            else if ((short)playbackObject->oClass == OCLASS_CLANK_10) {
                if (bootSpaceTransitionState.cutscene == SPACE_CUTSCENE_TAKEOFF) {
                    if (SceneLoad.sceneFrame <= FastScaleRoundInt(350))
                        playbackObject->shadow = 0x18;

                    else
                        playbackObject->shadow = 0;
                }

                else if (SceneLoad.sceneFrame <= FastScaleRoundInt(524))
                    playbackObject->shadow = 0;

                else
                    playbackObject->shadow = 0x18;
            }

            if (playbackObject->shadow != 0)
                MB_SetZBoundsFromFloorCeil(playbackObject);

            if ((short)playbackObject->oClass == OCLASS_CLANK_10)
                Hero_AddPulsingMobyGlow(playbackObject);

            if ((short)playbackObject->oClass == OCLASS_RATCHET) {
                Hero_UpdateInScene(playbackObject);

                if ((Level == LEVEL_ORXON && UnlockableItems[ITEM_O2_MASK] != 0) ||
                    Level == LEVEL_GEMLIK) {
                    if (bootSpaceTransitionState.o2Mask == 0) {
                        bootSpaceTransitionState.o2Mask = CreateMoby(OCLASS_O2_MASK);
                        bootSpaceTransitionState.o2Mask->drawDistance = 0x40;
                        bootSpaceTransitionState.o2Mask->modeBits |= 0x806;
                        bootSpaceTransitionState.o2Mask->lights = playbackObject->lights;

                        if (bootSpaceTransitionState.o2Mask->pClass->metalCount != 0)
                            bootSpaceTransitionState.o2Mask->metal = 0x18;
                    }

                    Hero_SnapMobyToBonePose(playbackObject, bootSpaceTransitionState.o2Mask);
                }
            }

            if ((unsigned short)(short)playbackObject->oClass - OCLASS_GREEN_SHIP_531 < 3U) {
                RegisterPreDraw(Space_DrawTransitionOverlay, playbackObject);
                RegisterMobyDraw(Space_DrawLoadingBanner, playbackObject);

                if (bootSpaceTransitionState.cutscene == SPACE_CUTSCENE_TAKEOFF) {
                    if (SceneLoad.sceneFrame < FastScaleRoundInt(360)) {
                        int colorIntensity =
                            (int)(FastAngleSinF(FastIntToFloat((SceneLoad.sceneFrame & 0x3F) - 32) *
                                                0.09817477f) *
                                  80.0f) +
                            120;

                        if ((short)playbackObject->oClass == OCLASS_PURPLE_SHIP_533)
                            playbackObject->glowRgba = (colorIntensity >> 1) |
                                                        (colorIntensity << 8) |
                                                        (colorIntensity << 16);

                        else
                            playbackObject->glowRgba =
                                colorIntensity | (colorIntensity << 8) | (colorIntensity << 16);
                    }

                    else if (SceneLoad.sceneFrame < FastScaleRoundInt(0x1F8)) {
                        int colorIntensity =
                            (int)(((float)SceneLoad.sceneFrame - FastScaleBySpeed(360.0f)) *
                                  (transStepScale * 1.25f));

                        if (colorIntensity >= 256)
                            colorIntensity = 255;

                        if ((short)playbackObject->oClass == OCLASS_PURPLE_SHIP_533)
                            playbackObject->glowRgba =
                                (colorIntensity << 8) | (colorIntensity << 16);

                        else
                            playbackObject->glowRgba =
                                colorIntensity | (colorIntensity << 8) | (colorIntensity << 16);

                        if (FastScaleRoundInt(0x1A4) < SceneLoad.sceneFrame) {
                            bootSpaceTransitionState.spaceship->setByGroup =
                                (int)(((float)SceneLoad.sceneFrame - FastScaleBySpeed(420.0f)) *
                                      (transStepScale * 1.2f));
                            bootSpaceTransitionState.spaceship->uid = 0;
                            RegisterMobyDraw(Space_DrawShipEngineGlow,
                                             bootSpaceTransitionState.spaceship);
                        }

                        if (FastScaleRoundInt(0x1D0) < SceneLoad.sceneFrame) {
                            g_SceneFlash += 0.025f;

                            if (g_SceneFlash > 1.0f)
                                g_SceneFlash = 1.0f;
                        }
                    }

                    else {
                        playbackObject->glowRgba = 0xA0A0A0;
                        g_SceneFlash -= 0.025f;

                        if (g_SceneFlash < 0.0f)
                            g_SceneFlash = 0.0f;
                    }
                }

                else if (SceneLoad.sceneFrame < FastScaleRoundInt(0xF0)) {
                    int colorIntensity;

                    if (SceneLoad.sceneFrame < FastScaleRoundInt(0xC8)) {
                        Space_SpawnShipParticles(playbackObject, frameTime * -4.0f);
                        Space_SpawnShipParticles(playbackObject, frameTime * -3.0f);
                    }

                    colorIntensity =
                        (int)(FastAngleSinF(FastIntToFloat((SceneLoad.sceneFrame & 0x3F) - 32) *
                                            0.09817477f) *
                              80.0f) +
                        120;

                    if ((short)playbackObject->oClass == OCLASS_PURPLE_SHIP_533)
                        playbackObject->glowRgba = (colorIntensity >> 1) |
                                                    (colorIntensity << 8) |
                                                    (colorIntensity << 16);

                    else
                        playbackObject->glowRgba =
                            colorIntensity | (colorIntensity << 8) | (colorIntensity << 16);

                    playbackObject->setByGroup = 0x32;
                    playbackObject->uid = 10;
                    RegisterMobyDraw(Space_DrawShipEngineGlow, playbackObject);
                }

                else if (SceneLoad.sceneFrame <= FastScaleRoundInt(360)) {
                    int colorIntensity;

                    if (SceneLoad.sceneFrame < FastScaleRoundInt(300)) {
                        bootSpaceTransitionState.spaceship->setByGroup =
                            (int)((FastScaleBySpeed(300.0f) - (float)SceneLoad.sceneFrame) *
                                  (transStepScale * 1.5f));
                        bootSpaceTransitionState.spaceship->uid = 0;
                        RegisterMobyDraw(Space_DrawShipEngineGlow,
                                         bootSpaceTransitionState.spaceship);
                    }

                    colorIntensity =
                        (int)((FastScaleBySpeed(360.0f) - (float)SceneLoad.sceneFrame) *
                              (transStepScale * 1.25f));

                    if ((short)playbackObject->oClass == OCLASS_PURPLE_SHIP_533)
                        playbackObject->glowRgba =
                            (colorIntensity << 8) | (colorIntensity << 16);

                    else
                        playbackObject->glowRgba =
                            colorIntensity | (colorIntensity << 8) | (colorIntensity << 16);
                }

                else {
                    int colorIntensity =
                        (int)(FastAngleSinF(FastIntToFloat((SceneLoad.sceneFrame & 0x3F) - 32) *
                                            0.09817477f) *
                              80.0f) +
                        120;

                    if ((short)playbackObject->oClass == OCLASS_PURPLE_SHIP_533)
                        playbackObject->glowRgba = (colorIntensity >> 1) |
                                                    (colorIntensity << 8) |
                                                    (colorIntensity << 16);

                    else
                        playbackObject->glowRgba =
                            colorIntensity | (colorIntensity << 8) | (colorIntensity << 16);
                }
            }
        }

        sound_Update();
        UpdatePointLights();
        MB_UpdateLightAngle();
        UpdateGameCounters();
        break;

    case SPACE_CUTSCENE_FLIGHT:
        ResetGameCounters();
        UpdateMobyChain();
        sound_UpdateAmbient();
        HeroUpdate();
        UpdateParts();

        if (bootSpaceTransitionState.timer == 0) {
            music_Pause(0);
            music_Sync(0);
            musicTransition.queuedSpeech = bootSpaceTransitionState.shipVariant + 0x9C4F;
            FadeToBlack(FastScaleRoundInt(12));

            while ((short)musicTransition.state != 3) {
                sound_Update();
                sceGsSyncV(0);
            }

            music_PlayPreseekedSpeech();
            bootSpaceTransitionState.spaceship->updateId = 1;
            bootSpaceTransitionState.spaceship->animationId = 2;
            bootSpaceTransitionState.spaceship->animationBlend = 0.0f;
            UpdateMobyFrameData(bootSpaceTransitionState.spaceship);
            bootSpaceTransitionState.spaceship->lodTransition = 0xFF;
            bootSpaceTransitionState.spaceship->collision = 0;

            if (bootSpaceTransitionState.shipSplinePath >= 0) {
                bootSpaceTransitionState.riderRatchet = CreateMoby(OCLASS_RATCHET);
                bootSpaceTransitionState.riderRatchet->drawDistance = 0x1FF;
                bootSpaceTransitionState.riderRatchet->lodTransition = 0xFF;
                bootSpaceTransitionState.riderRatchet->collision = 0;
                bootSpaceTransitionState.riderRatchet->modeBits |= 6;
                bootSpaceTransitionState.riderRatchet->lights = Hero.moby->lights;
                bootSpaceTransitionState.riderClank = CreateMoby(OCLASS_CLANK_10);
                bootSpaceTransitionState.riderClank->drawDistance = 0x1FF;
                bootSpaceTransitionState.riderClank->lodTransition = 0xFF;
                bootSpaceTransitionState.riderClank->collision = 0;
                bootSpaceTransitionState.riderClank->modeBits |= 6;
                bootSpaceTransitionState.riderClank->lights = Hero.moby->lights;
            }

            FUN_00316ef8(&GameCamera.position, &GameCamera.rot, 1, 0, 0);
            bootSpaceTransitionState.cameraBlend = 0.0f;
            bootSpaceTransitionState.cameraBlendSpeed = 0.0f;

            if (bootSpaceTransitionState.shipSplinePath >= 0) {
                path = Splines[bootSpaceTransitionState.shipSplinePath];
                maximumTurn = bootSpaceTransitionState.cameraBlend;
                path->points[0].w = maximumTurn;

                for (pathPointIndex = 1; pathPointIndex < path->pointCount - 1;
                     pathPointIndex++) {
                    segmentAngle = FastArcTan(
                        path->points[pathPointIndex].x - path->points[pathPointIndex - 1].x,
                        path->points[pathPointIndex].y - path->points[pathPointIndex - 1].y);
                    path->points[pathPointIndex].w =
                        FastSubRots(FastArcTan(path->points[pathPointIndex + 1].x -
                                                   path->points[pathPointIndex].x,
                                               path->points[pathPointIndex + 1].y -
                                                   path->points[pathPointIndex].y),
                                    segmentAngle);

                    if (maximumTurn < FastAbsF(path->points[pathPointIndex].w))
                        maximumTurn = FastAbsF(path->points[pathPointIndex].w);
                }

                segmentAngle = FastArcTan(
                    path->points[path->pointCount - 1].x - path->points[path->pointCount - 2].x,
                    path->points[path->pointCount - 1].y - path->points[path->pointCount - 2].y);
                path->points[path->pointCount - 1].w = FastSubRots(
                    FastArcTan(path->points[0].x - path->points[path->pointCount - 1].x,
                               path->points[0].y - path->points[path->pointCount - 1].y),
                    segmentAngle);
                turnScale = 0.34906584f / maximumTurn;

                for (pointIndex = 0; pointIndex < path->pointCount; pointIndex++)
                    path->points[pointIndex].w *= turnScale;

                bootSpaceTransitionState.flightSegLen =
                    FastVec3Dist(&path->points[0], &path->points[1]);
                bootSpaceTransitionState.flightParam = 0.0f;
                bootSpaceTransitionState.flightSpeed = 0.0f;
                bootSpaceTransitionState.trailHead = 0;
                bootSpaceTransitionState.trailLen = 0;
                player = bootSpaceTransitionState.spaceship;
                CopyVec4Inline(&bootSpaceTransitionState.liftFrom, &player->pos);
                CopyVec4Inline(&bootSpaceTransitionState.liftTo, &path->points[0]);
                CopyVec4Inline(&bootSpaceTransitionState.liftFromRot, &player->rotation);
                bootSpaceTransitionState.liftPitch =
                    FastArcTan(FastVec3DistLen(&path->points[1], &path->points[0]),
                               path->points[0].z - path->points[1].z);
                bootSpaceTransitionState.liftYaw = FastArcTan(
                    path->points[1].x - path->points[0].x, path->points[1].y - path->points[0].y);
            }
        }

        if (bootSpaceTransitionState.shipCameraStartCuboid >= 0 &&
            bootSpaceTransitionState.shipCameraEndCuboid >= 0) {
            cameraBlendStep = 0.666f * frameTimeSq;
            OrganicDelt(&bootSpaceTransitionState.cameraBlend,
                        &bootSpaceTransitionState.cameraBlendSpeed, 1.0f, cameraBlendStep,
                        cameraBlendStep, frameTime * 0.5f);
            FastVecLerp(&scratch.v0,
                        &CuboidVolumes[bootSpaceTransitionState.shipCameraStartCuboid].origin,
                        &CuboidVolumes[bootSpaceTransitionState.shipCameraEndCuboid].origin,
                        bootSpaceTransitionState.cameraBlend);
            FastVecZero(&scratch.v1);
            scratch.v1.y = FastSubRots(CuboidVolumes[bootSpaceTransitionState.shipCameraEndCuboid]
                                           .inverseTransform.v3.y,
                                       CuboidVolumes[bootSpaceTransitionState.shipCameraStartCuboid]
                                           .inverseTransform.v3.y) *
                           bootSpaceTransitionState.cameraBlend;
            scratch.v1.y = FastAddRots(
                CuboidVolumes[bootSpaceTransitionState.shipCameraStartCuboid].inverseTransform.v3.y,
                scratch.v1.y);
            scratch.v1.z = FastSubRots(CuboidVolumes[bootSpaceTransitionState.shipCameraEndCuboid]
                                           .inverseTransform.v3.z,
                                       CuboidVolumes[bootSpaceTransitionState.shipCameraStartCuboid]
                                           .inverseTransform.v3.z) *
                           bootSpaceTransitionState.cameraBlend;
            scratch.v1.z = FastAddRots(
                CuboidVolumes[bootSpaceTransitionState.shipCameraStartCuboid].inverseTransform.v3.z,
                scratch.v1.z);
            FUN_00316dd0(&scratch.v0);
            FUN_00316e28(&scratch.v1);
        }

        if (bootSpaceTransitionState.shipSplinePath >= 0) {
            if (bootSpaceTransitionState.timer < FastScaleRoundInt(150)) {
                blend =
                    (1.0f - FastAngleSinF(FastIntToFloat(bootSpaceTransitionState.timer) *
                                          (3.1415927f / FastIntToFloat(FastScaleRoundInt(120))))) *
                    0.5f;

                if (bootSpaceTransitionState.timer >= FastScaleRoundInt(120))
                    blend = 1.0f;

                bootSpaceTransitionState.spaceship->animationBlend = blend;
                FastVecLerp(&bootSpaceTransitionState.spaceship->pos,
                            &bootSpaceTransitionState.liftFrom, &bootSpaceTransitionState.liftTo,
                            blend);
                bootSpaceTransitionState.spaceship->rotation.x = 0.0f;
                bootSpaceTransitionState.spaceship->rotation.y =
                    FastAddRots(bootSpaceTransitionState.liftFromRot.y,
                                FastSubRots(bootSpaceTransitionState.liftPitch,
                                            bootSpaceTransitionState.liftFromRot.y) *
                                    blend);
                bootSpaceTransitionState.spaceship->rotation.z =
                    FastAddRots(bootSpaceTransitionState.liftFromRot.z,
                                FastSubRots(bootSpaceTransitionState.liftYaw,
                                            bootSpaceTransitionState.liftFromRot.z) *
                                    blend);

                if (screenFade > 0.0f) {
                    screenFade -= 0.125f;

                    if (screenFade < 0.0f)
                        screenFade = 0.0f;
                }

                if (blend < 1.0f)
                    Space_SpawnShipParticles(bootSpaceTransitionState.spaceship,
                                             frameTime * -3.75f);
            }

            else {
                MobyPath *activePath;
                bootSpaceTransitionState.flightSpeed += 0.8f;
                activePath = Splines[bootSpaceTransitionState.shipSplinePath];

                if (bootSpaceTransitionState.flightSpeed > 100.0f)
                    bootSpaceTransitionState.flightSpeed = 100.0f;

                if ((padState.bitsOn & (PAD_TRIANGLE | PAD_CROSS)) && screenFade < 0.0625f)
                    screenFade = 0.0625f;

                if ((float)(activePath->pointCount - 6) < bootSpaceTransitionState.flightParam &&
                    screenFade < 0.0625f)
                    screenFade = 0.0625f;

                if (bootSpaceTransitionState.shipVariant < 2) {
                    bootSpaceTransitionState.spaceship->setByGroup = 0x32;
                    bootSpaceTransitionState.spaceship->uid = 10;
                    RegisterMobyDraw(Space_DrawShipEngineGlow, bootSpaceTransitionState.spaceship);
                }

                bootSpaceTransitionState.flightParam += bootSpaceTransitionState.flightSpeed *
                                                        frameTime /
                                                        bootSpaceTransitionState.flightSegLen;

                if ((float)(activePath->pointCount - 1) < bootSpaceTransitionState.flightParam ||
                    screenFade >= 1.0f) {
                    g_newlevel = 1;
                    CutscenePlaying = 1;
                }

                else {
                    MB_PathEvalSpline(activePath, 1, &bootSpaceTransitionState.spaceship->pos,
                                      &bootSpaceTransitionState.spaceship->rotation, 0,
                                      bootSpaceTransitionState.flightParam);
                    bootSpaceTransitionState.spaceship->rotation.x =
                        bootSpaceTransitionState.spaceship->rotation.w;
                    bootSpaceTransitionState.trailHead =
                        (bootSpaceTransitionState.trailHead + 1) & 0x1F;

                    if (bootSpaceTransitionState.trailLen < 0x20)
                        bootSpaceTransitionState.trailLen++;

                    FastVecMtx3Mult(
                        &bootSpaceTransitionState.trails[0][bootSpaceTransitionState.trailHead],
                        &ShipTrailOffsets[bootSpaceTransitionState.shipVariant][0],
                        &bootSpaceTransitionState.spaceship->transform);
                    FastVec3Add(
                        &bootSpaceTransitionState.trails[0][bootSpaceTransitionState.trailHead],
                        &bootSpaceTransitionState.trails[0][bootSpaceTransitionState.trailHead],
                        &bootSpaceTransitionState.spaceship->pos);
                    bootSpaceTransitionState.trails[0][bootSpaceTransitionState.trailHead].w = 1.0f;
                    FastVecMtx3Mult(
                        &bootSpaceTransitionState.trails[1][bootSpaceTransitionState.trailHead],
                        &ShipTrailOffsets[bootSpaceTransitionState.shipVariant][1],
                        &bootSpaceTransitionState.spaceship->transform);
                    FastVec3Add(
                        &bootSpaceTransitionState.trails[1][bootSpaceTransitionState.trailHead],
                        &bootSpaceTransitionState.trails[1][bootSpaceTransitionState.trailHead],
                        &bootSpaceTransitionState.spaceship->pos);
                    bootSpaceTransitionState.trails[1][bootSpaceTransitionState.trailHead].w = 1.0f;
                    RegisterMobyDraw(Space_DrawShipEffects, bootSpaceTransitionState.spaceship);

                    if (screenFade > 0.0f) {
                        screenFade += 0.0625f;

                        if (screenFade > 1.0f)
                            screenFade = 1.0f;
                    }
                }
            }

            {
                MobyInstance *p = bootSpaceTransitionState.spaceship;
                MobyInstance *companion = bootSpaceTransitionState.riderRatchet;

                CopyVec4Inline(&companion->rotation, &p->rotation);
                FastVecMtx3Mult(&companion->pos,
                                &ShipRatchetOffsets[bootSpaceTransitionState.shipVariant],
                                &p->transform);
            }

            FastVec3Add(&bootSpaceTransitionState.riderRatchet->pos,
                        &bootSpaceTransitionState.riderRatchet->pos,
                        &bootSpaceTransitionState.spaceship->pos);
            PostUpdateMoby(bootSpaceTransitionState.riderRatchet);
            {
                MobyInstance *companion = bootSpaceTransitionState.riderClank;
                MobyInstance *p = bootSpaceTransitionState.spaceship;

                CopyVec4Inline(&companion->rotation, &p->rotation);
                FastVecMtx3Mult(&companion->pos,
                                &ShipClankOffsets[bootSpaceTransitionState.shipVariant],
                                &p->transform);
            }

            FastVec3Add(&bootSpaceTransitionState.riderClank->pos,
                        &bootSpaceTransitionState.riderClank->pos,
                        &bootSpaceTransitionState.spaceship->pos);
            PostUpdateMoby(bootSpaceTransitionState.riderClank);
        }

        UpdateCameras();
        sound_Update();
        UpdatePointLights();
        MB_UpdateLightAngle();
        UpdateGameCounters();
        break;

    case SPACE_CUTSCENE_LOADING:
        Space_UpdateCutsceneScene();
        break;
    case 1:
    case 2:
    case 5:
    case 6:
    case 7:
        break;
    }
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/space", space_DefaultDraw);

void SpaceTransition_LoadWad(void)
{
    enum { LEVEL_SCENE_MODE_EARLY_PROGRESSION = 4 };
    unsigned long long texturePacket[4];
    SpaceWadHeader *header;
    int dataBase;
    int mobyTexData;
    TextureDef *mobyTextures;
    SpaceMobyEntry *mobyEntry;
    int *textureOffsets;
    int languageIndex;
    int archiveSize;
    unsigned char *allocationCursor;
    int *sceneOffsets;
    int *sceneOffset;
    SceneChunkEntry *sceneChunk;
    int textureIndex;
    int modelIndex;
    int chunkIndex;
    int textureCursor;
    int sceneVariant;
    int workspaceOffset;

    bootSpaceTransitionState.cutscene = SPACE_CUTSCENE_LOADING;
    bootSpaceTransitionState.timer = -1;
    screenFade = 1.0f;
    Hero.moby = 0;
    vu1_bufSize = 0x100000;
    CutscenePlaying = 0;
    g_SceneFlash = 0.0f;

    InitMemSlots();
    GSloc = GSmemBase;
    GSbase = GSmemBase;
    FastMemSet(CollJointCacheKeys, 0x87654321, 0x10);
    FastMemSet(MobyClassLookup, -1, 0x800);
    FastMemSet(MobyTexLookup, -1, 0xE00);
    FastMemSet(MobyMipDists, 0, 0xE0);

    InitViewContext();
    UpdateViewContext();
    VU1_initChain();

    music_LoadBankFromEE(MemSlots.levelBase + 0x400000, bootAssets.transition.offset,
                         bootAssets.transition.length);
    FadeToBlack(FastScaleRoundInt(0xC));
    sceCdSync(0);
    FlushCache(0);
    archiveSize = WadDecompress(MemSlots.levelBase + 0x400000, MemSlots.levelBase);
    FlushCache(0);

    header = (SpaceWadHeader *)MemSlots.levelBase;
    ParsePermGsRam((char *)header + header->permTexData, header->permTexCount,
                   (PermGsTexture *)((char *)header + header->permTexDefs));

    dataBase = (int)header + header->dataOffset;
    mobyTexData = dataBase + header->mobyTexData;
    VisGifSpecialTemplate[0] =
        (int)((GSmemBase + header->specialTextureBase) >> 8) | 0x1D308000 |
        ((unsigned long long)0xB800 << 19) |
        ((unsigned long long)((GSmemBase + header->specialClutBase) >> 8) << 37) |
        0x8000000000000000LL;
    VisGifSpecialTemplate[1] = 0x0000FFA0000000E0LL;
    VisGifSpecialTemplate[2] = 0x0040000400004000LL;

    mobyTextures = (TextureDef *)((int)header + header->mobyTexDefs);
    MobyTextureCount = header->mobyTexCount;
    for (textureIndex = 0; textureIndex < MobyTextureCount; textureIndex++) {
        MobyTexLocs[textureIndex] = mobyTexData + mobyTextures[textureIndex].offset +
                                    (FastLog2(mobyTextures[textureIndex].width) << 28);
    }

    FastMemCopy16(MobyTexDefs, mobyTextures, MobyTextureCount * sizeof(TextureDef));
    ParseSky((char *)(dataBase + header->sky));

    mobyEntry = (SpaceMobyEntry *)((int)header + header->mobys);
    MobyClassIndex = 0;
    for (modelIndex = 0; modelIndex < header->mobyCount; modelIndex++) {
        ParseMoby(mobyEntry->offset == 0 ? 0 : (char *)(dataBase + mobyEntry->offset),
                  (short *)((int)header + header->mobyTexDefs), (char *)mobyEntry->textureRefs,
                  mobyEntry->oClass);
        mobyEntry++;
    }

    EffectTextureData = dataBase + header->textureData;
    ParseEffectTexs((int *)((int)header + header->effectTexDefs), header->effectTexCount);
    {
        int particleDataBase = dataBase + header->partTexData;
        int particleEntries = (int)header + header->partTexDefs;

        ParseParticleTexs((int *)((int)header + header->partTexHeaders), particleDataBase,
                          (int *)particleEntries, header->partTexCount);
    }

    textureOffsets = (int *)(dataBase + header->planetTextures);
    languageIndex = gameLanguage - 1;
    if (languageIndex < 0)
        languageIndex = 0;
    ParseGsRamTextures((PifHeader *)((int)textureOffsets + textureOffsets[Level + 1]),
                       texturePacket);
    SpacePlanetTex0 = texturePacket[0];
    ParseGsRamTextures(
        (PifHeader *)((int)textureOffsets + textureOffsets[languageIndex * 19 + Level + 0x14]),
        texturePacket);

    textureCursor = GSloc + 0x2000;
    allocationCursor = MemSlots.levelBase + archiveSize;
    GSloc = textureCursor;
    MemSlots.levelData = allocationCursor;
    GSbase = textureCursor;
    SpacePlanetTextTex0 = texturePacket[0];

    FastMemSetZero(PointLights, 0x100);
    FastMemSetZero(PointLightData, 0x180);
    FastMemSetZero(DirectionalLights, 0x400);
    FastMemCopy16(DirectionalLights, &SpaceDefaultDirectionalLight, 0x40);

    MobyInstances = (MobyInstance *)allocationCursor;
    FastMemSet(allocationCursor, 0, 0x4000);
    allocationCursor += 0x4000;
    MobyInstancePermEnd = MobyInstances;
    MobyInstances->state = 0xFF;
    mobyVars = (char *)allocationCursor;
    allocationCursor += 0x2000;
    PartInstances = (PartInstance *)allocationCursor;
    PartIndexTop = -1;
    MobyInstanceEnd = MobyInstances + 63;
    PartIndexNext = 0;
    PartActiveCnt = 0;
    FastMemSetZero(PartAlloc, 0x200);

    ResetDrawGlobals();
    MobyDrawDist = 0x1F4;
    PartClipDist = 0x1F4000;

    sceneVariant = (rand() >> 16) & 3;
    bootSpaceTransitionState.loadingCount = 0;
    bootSpaceTransitionState.loadingScreen = sceneVariant;
    bootSpaceTransitionState.trailHead = 0;
    bootSpaceTransitionState.trailLen = 0;
    CopyVec4Inline(&SpaceQuadOffset, &SpaceQuadBase);

    if (Level == LEVEL_VELDIN || (Level == LEVEL_NOVALIS && g_SeenPlanets[3] == 0)) {
        bootSpaceTransitionState.loadingScreen = LEVEL_SCENE_MODE_EARLY_PROGRESSION;
        bootSpaceTransitionState.loadingCount = 2;
    }

    FastMemSet(&SceneLoad, 0, 0x1C0);
    FastMemSet(SceneScratchA, 0, 0x40);
    FastMemSet(SceneScratchB, 0, 0x40);

    sceneOffsets = header->scenes;
    workspaceOffset = vu1_bufSize - 0x60000;
    sceneOffset = &sceneOffsets[bootSpaceTransitionState.loadingScreen];
    SceneLoad.decodedChunk = MemSlots.vu1_chain[0] + workspaceOffset;
    SceneLoad.buffer = MemSlots.vu1_chain[1] + workspaceOffset;
    vu1_bufSize = workspaceOffset;
    sceneChunk =
        (SceneChunkEntry *)(dataBase + sceneOffsets[bootSpaceTransitionState.loadingScreen]);
    /* The archive list is terminated by a zero size and the resident table holds 70 entries. */
    for (chunkIndex = 0; chunkIndex < 70 && sceneChunk->length != 0; chunkIndex++) {
        {
            int chunkOffset = sceneChunk->offset + 0x800;
            SceneLoad.chunks[chunkIndex] = (unsigned char *)(dataBase + *sceneOffset + chunkOffset);
        }
        sceneChunk++;
    }

    ParseSpaceSceneChunk(0);
    levelSoundBank = 0xFFFFFFFF;
    snd_BankLoadFromEE_CB((void *)(dataBase + header->sound), sound_LoadBankCB,
                          (unsigned int)&levelSoundBank);
    do {
        FlushCache(0);
        sceGsSyncV(0);
        snd_FlushSoundCommands();
    } while (levelSoundBank == 0xFFFFFFFF);

    snd_ResolveBankXREFS();
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/space", DisplayLoadingScreen);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/space", SpacePlate_DrawQuad);

static inline SpacePlatePif *getSpacePlatePif(SpacePlateArchive *archive, int imageIndex)
{
    int offset = *(archive->recordOffsets + imageIndex + SPACE_PLATE_IMAGE_BASE);
    return (SpacePlatePif *)((unsigned char *)archive + offset);
}

void LoadSpacePlate(int language, int firstImage, int lastImage, unsigned long long *sharedTexture,
                    unsigned long long *firstTexture,

                    unsigned long long *lastTexture)
{
    int textureBases[SPACE_PLATE_UPLOAD_COUNT];
    sceGsLoadImage loadImage;
    unsigned long long *firstOutput;
    unsigned long long *lastOutput;
    int uploadIndex;
    int *textureBaseOutput;
    int uploadBytes;
    u_long128 *imageAddress;
    SpacePlateArchive *archiveBase;
    struct MEMSLOTS *archiveMemory;


    firstOutput = firstTexture;
    lastOutput = lastTexture;
    archiveMemory = &MemSlots;
    uploadIndex = 0;

    music_LoadBankFromEE(archiveMemory->levelBase + 0x100000,
                         bootAssets.spacePlates[language].offset,
                         bootAssets.spacePlates[language].length);
    sceCdSync(0);
    FlushCache(0);
    WadDecompress(archiveMemory->levelBase + 0x100000, archiveMemory->levelBase);
    FlushCache(0);

    archiveBase = (SpacePlateArchive *)archiveMemory->levelBase;
    GSloc = GSmemBase;
    GSbase = GSmemBase;
    textureBaseOutput = textureBases;

    for (uploadIndex = 0; uploadIndex < SPACE_PLATE_UPLOAD_COUNT; uploadIndex++) {
        if (uploadIndex == SPACE_PLATE_SHARED_CLUT) {
            sceGsSetDefLoadImage(&loadImage, (GSloc << 8) >> 16, 1, PIF_PSMCT32, 0, 0, 0x10, 0x10);
            uploadBytes = 0x400;
            imageAddress =
                (u_long128 *)getSpacePlatePif(archiveBase, SPACE_PLATE_SHARED_IMAGE_INDEX)->palette;
        }

        else if (uploadIndex == SPACE_PLATE_SHARED_TEXTURE) {
            sceGsSetDefLoadImage(&loadImage, (GSloc << 8) >> 16, 1, PIF_PSMT8, 0, 0, 0x40, 0x40);
            uploadBytes = 0x1000;
            imageAddress =
                (u_long128 *)getSpacePlatePif(archiveBase, SPACE_PLATE_SHARED_IMAGE_INDEX)->texels;
        }

        else if (uploadIndex == SPACE_PLATE_FIRST_CLUT) {
            sceGsSetDefLoadImage(&loadImage, (GSloc << 8) >> 16, 1, PIF_PSMCT32, 0, 0, 0x10, 0x10);
            uploadBytes = 0x400;
            imageAddress = (u_long128 *)getSpacePlatePif(archiveBase, firstImage)->palette;
        }

        else if (uploadIndex == SPACE_PLATE_FIRST_TEXTURE) {
            sceGsSetDefLoadImage(&loadImage, (GSloc << 8) >> 16, 8, PIF_PSMT8, 0, 0, 0x200, 0x40);
            uploadBytes = 0x8000;
            imageAddress = (u_long128 *)getSpacePlatePif(archiveBase, firstImage)->texels;
        }

        else if (uploadIndex == SPACE_PLATE_LAST_CLUT) {
            sceGsSetDefLoadImage(&loadImage, (GSloc << 8) >> 16, 1, PIF_PSMCT32, 0, 0, 0x10, 0x10);
            uploadBytes = 0x400;
            imageAddress = (u_long128 *)getSpacePlatePif(archiveBase, lastImage)->palette;
        }

        else {
            sceGsSetDefLoadImage(&loadImage, (GSloc << 8) >> 16, 8, PIF_PSMT8, 0, 0, 0x200, 0x40);
            uploadBytes = 0x8000;
            imageAddress = (u_long128 *)getSpacePlatePif(archiveBase, lastImage)->texels;
        }

        FlushCache(0);
        sceGsExecLoadImage(&loadImage, imageAddress);
        sceGsSyncPath(0, 0);
        *textureBaseOutput = GSloc >> 8;
        GSloc += uploadBytes;
        textureBaseOutput++;
    }

    /* Each TEX0 combines an image base with its paired palette base. */
    {
        unsigned long long paletteBits =
            ((unsigned long long)textureBases[SPACE_PLATE_SHARED_CLUT] << 37) |
            SPACE_PLATE_TEX0_HIGH;
        unsigned long long imageBits =
            (unsigned long long)(textureBases[SPACE_PLATE_SHARED_TEXTURE] |
                                 SPACE_PLATE_SHARED_TEX0_LOW);
        *sharedTexture = (imageBits | paletteBits) | SPACE_PLATE_TEX0_CLD;
    }
    {
        unsigned long long imageBits =
            (unsigned long long)(textureBases[SPACE_PLATE_FIRST_TEXTURE] |
                                 SPACE_PLATE_IMAGE_TEX0_LOW);
        unsigned long long paletteBits =
            ((unsigned long long)textureBases[SPACE_PLATE_FIRST_CLUT] << 37) |
            SPACE_PLATE_TEX0_HIGH;
        *firstOutput = (imageBits | paletteBits) | SPACE_PLATE_TEX0_CLD;
    }
    {
        unsigned long long imageBits = (unsigned long long)(textureBases[SPACE_PLATE_LAST_TEXTURE] |
                                                            SPACE_PLATE_IMAGE_TEX0_LOW);
        unsigned long long paletteBits =
            ((unsigned long long)textureBases[SPACE_PLATE_LAST_CLUT] << 37) | SPACE_PLATE_TEX0_HIGH;
        *lastOutput = (imageBits | paletteBits) | SPACE_PLATE_TEX0_CLD;
    }
}

void PlaySpacePlate(

    int language, int firstImage, int lastImage, int duration, int preload)
{
    unsigned long long sharedTexture;
    unsigned long long firstTexture;
    unsigned long long secondTexture;
    int frame;
    int alpha;
    int fadeInAlpha;
    float scrollPhase;
    float scrollStart;
    float scrollEnd;

    LoadSpacePlate(language, firstImage, lastImage, &sharedTexture, &firstTexture, &secondTexture);

    if (preload != 0) {
        ReadFileEntryWithRetry(Level);
        LevelLoad.stage = 0;
        LevelLoad.hold = 0;
    }

    sceGsSyncV(0);
    VU1_initChain();

    for (frame = 0; frame < duration && g_memcard.stage < MC_STAGE_FORMAT &&
                    g_memcard.nextstage < MC_STAGE_GET_INFO;
         frame++) {
        alpha = 0x80;
        SetupFogColorGsReg();
        PutDrawBufferSmall();
        VU1_addGSregister(GS_REG_RGBAQ, (unsigned long long)0x8000 << 16);
        VU1_addGSregister(GS_REG_CLAMP_1, 0);

        vu1_bufPtr.tag->tag = DMA_TAG_REF | GIF_CLEAR_FRAME_BUF_QWC;
        fadeInAlpha = frame * 4;
        if (frame <= 0x1F)
            alpha = fadeInAlpha;
        vu1_bufPtr.tag->addr = (unsigned int)gif_clear_frame_buf;
        vu1_bufPtr.tag->vif0 = 0;
        vu1_bufPtr.tag->vif1 = VIF_DIRECT | GIF_CLEAR_FRAME_BUF_QWC;
        vu1_bufPtr.tag++;

        if (duration - 0x10 < frame)
            alpha = (duration - frame) * 8;

        scrollPhase = FastIntToFloat(frame % 600) * 0.0016666667f;
        if (firstImage == lastImage) {
            SpacePlate_DrawQuad(0, Scrn.halfY - 0x20, 0x200, 0x40, (alpha << 24) | 0x808080,
                                sharedTexture, 0.0f, 4.0f, scrollPhase + 0.0f, scrollPhase + 0.4f);
            DrawSprite(0, Scrn.halfY - 0x20, 0x200, 0x40, 0, 0, 0x200, 0x40, 0x80808080,
                       firstTexture);
        }

        else {
            scrollStart = scrollPhase + 0.0f;
            scrollEnd = scrollPhase + 0.4f;
            SpacePlate_DrawQuad(0, Scrn.halfY - 0x2E, 0x200, 0x40, (alpha << 24) | 0x808080,
                                sharedTexture, 0.0f, 4.0f, scrollStart, scrollEnd);
            DrawSprite(0, Scrn.halfY - 0x2E, 0x200, 0x40, 0, 0, 0x200, 0x40, 0x80808080,
                       firstTexture);
            if (frame > 0x40) {
                if (frame < 0x60)
                    alpha = (frame - 0x40) * 4;
                SpacePlate_DrawQuad(0, Scrn.halfY, 0x200, 0x40, (alpha << 24) | 0x808080,
                                    sharedTexture, 0.0f, 4.0f, scrollStart, scrollEnd);
                DrawSprite(0, Scrn.halfY, 0x200, 0x40, 0, 0, 0x200, 0x40, 0x80808080,
                           secondTexture);
            }
        }

        memcard_Update();
        UpdateMCState();
        VU1_syncChain(1);
        sceGsSyncV(0);
        ResetGsRegistersPr();
        VU1_sendChain();
        VU1_swapChain();

        if (preload != 0) {
            if (LoadLevelFiles() == 0) {
                if (duration < frame + 0x14)
                    duration = frame + 0x14;
            }

            else {
                preload = 0;
            }
        }
    }

    FadeToBlack(2);
}

void DoSpaceTransition(void)
{
    int languageIndex;
    int markLevelVisited;
    int loadComplete;

    languageIndex = gameLanguage - 1;
    if (languageIndex < 0)
        languageIndex = 0;

    CollOutput.collCount |= COLLISION_COUNTER_INVALIDATE;
    gameMode = GAME_MODE_SPACE;
    bootSpaceTransitionState.shipVariant = SPACE_SHIP_INITIAL;
    if (g_SeenPlanets[LEVEL_BATALIA] != 0 || g_newlevelnum >= LEVEL_BATALIA)
        bootSpaceTransitionState.shipVariant = SPACE_SHIP_BATALIA;
    if (g_SeenPlanets[LEVEL_OLTANIS] != 0 || g_newlevelnum >= LEVEL_OLTANIS)
        bootSpaceTransitionState.shipVariant = SPACE_SHIP_OLTANIS;

    FlushCache(0);
    snd_SetReverbEx(2, 0, 0, 0, 0);
    snd_ResetStateAndFlushCommands();
    snd_FlushSoundCommands();
    sound_StopAllSounds();
    music_Stop();

    musicTransition.updatesSuspended = 1;
    if (LevelSounds != 0) {
        snd_UnloadBank(LevelSounds->bank_index);
        snd_ResolveBankXREFS();
        printf_stub(SpaceUnloadBankFormat, LevelSounds->bank_index);
    }

    levelSoundBank = 0;
    snd_StreamSafeCdCallback(0);
    snd_StreamSafeCdSync(0);

    VC.fogB = 16;
    VC.fogFarDist = 524288.0f;
    VC.fogNearIntensity = 255.0f;
    VC.fogR = 0;
    VC.fogG = 0;
    VC.fogNearDist = 0;
    VC.fogFarIntensity = 128.0f;
    SetBackgroundColor(0, 0, 0);

    if (g_newlevelnum < 0) {
        while (g_memcard.stage >= MC_STAGE_FORMAT || g_memcard.nextstage >= MC_STAGE_GET_INFO) {
            memcard_Update();
            UpdateMCState();
        }
        FadeToBlack(FastScaleRoundInt(6));
        Level = g_newlevelnum;
        SetupLevelWadBuffer();
        sceCdSync(0);
        musicTransition.updatesSuspended = 0;
        DMAC_VIF1_Disable();
        return;
    }

    if (g_newlevelnum == LEVEL_VELDIN && LevelVisited[LEVEL_VELDIN] == 0) {
        FadeToBlack(FastScaleRoundInt(6));
        PlaySpacePlate(languageIndex, 0, 1, FastScaleRoundInt(240), 0);
        DisplayLoadingScreen(0);
        PlaySpacePlate(languageIndex, 2, 2, FastScaleRoundInt(180), 0);
        DisplayLoadingScreen(1);
        Level = g_newlevelnum;
        PlaySpacePlate(languageIndex, 3, 4, FastScaleRoundInt(240), 1);
        DisplayLoadingScreen(2);
    }

    else if (Level == LEVEL_VELDIN && g_newlevelnum == LEVEL_NOVALIS &&
             LevelVisited[LEVEL_NOVALIS] == 0) {
        FadeToBlack(FastScaleRoundInt(6));
        PlaySpacePlate(languageIndex, 5, 6, FastScaleRoundInt(240), 0);
        DisplayLoadingScreen(3);
        DisplayLoadingScreen(4);
        PlaySpacePlate(languageIndex, 7, 7, FastScaleRoundInt(180), 0);
        DisplayLoadingScreen(5);
        LevelVisited[Level] = 2;
        Level = g_newlevelnum;
        PlaySpacePlate(languageIndex, 8, 8, FastScaleRoundInt(240), 1);
    }

    else {

        if (g_newlevelnum == LEVEL_EUDORA && LevelVisited[LEVEL_EUDORA] == 0) {
            FadeToBlack(FastScaleRoundInt(12));
            PlaySpacePlate(languageIndex, 9, 10, FastScaleRoundInt(240), 0);
            DisplayLoadingScreen(6);
        }

        if (Level == LEVEL_UMBRIS && LevelVisited[LEVEL_UMBRIS] != 2 &&
            g_SeenPlanets[LEVEL_BATALIA] != 0) {
            FadeToBlack(FastScaleRoundInt(12));
            PlaySpacePlate(languageIndex, 11, 11, FastScaleRoundInt(240), 0);
            DisplayLoadingScreen(7);
        }

        if (g_newlevelnum == LEVEL_GEMLIK && LevelVisited[LEVEL_GEMLIK] == 0) {
            FadeToBlack(FastScaleRoundInt(12));
            PlaySpacePlate(languageIndex, 12, 13, FastScaleRoundInt(240), 0);
            DisplayLoadingScreen(8);
        }

        if (Level == LEVEL_OLTANIS && LevelVisited[LEVEL_OLTANIS] != 2 &&
            g_SeenPlanets[LEVEL_QUARTU] != 0) {
            FadeToBlack(FastScaleRoundInt(12));
            PlaySpacePlate(languageIndex, 14, 14, FastScaleRoundInt(240), 0);
            DisplayLoadingScreen(9);
        }

        if (g_newlevelnum == LEVEL_KALEBO_3 && LevelVisited[LEVEL_KALEBO_3] == 0) {
            FadeToBlack(FastScaleRoundInt(12));
            PlaySpacePlate(languageIndex, 15, 16, FastScaleRoundInt(240), 0);
            DisplayLoadingScreen(10);
        }

        if ((unsigned int)Level < LEVEL_COUNT) {
            markLevelVisited = 1;
            if (Level == LEVEL_UMBRIS && g_SeenPlanets[LEVEL_BATALIA] == 0)
                markLevelVisited = 0;
            if (Level == LEVEL_OLTANIS && g_SeenPlanets[LEVEL_QUARTU] == 0)
                markLevelVisited = 0;
            if (markLevelVisited)
                LevelVisited[Level] = 2;
        }

        LevelLoad.hold = 1;
        loadComplete = 0;
        Level = g_newlevelnum;
        LevelLoad.stage = 0;
        SpaceTransition_LoadWad();
        ReadFileEntryWithRetry(Level);

        while (CutscenePlaying == 0) {
            VU1_sendChain();
            VU1_swapChain();
            PutDrawBufferSmall();
            ((void (*)(
                void))AA_DisplayPass)(); // Retail passes no argument to this unused parameter.
            PutDrawBufferLarge();
            UpdatePad();
            UpdateSpace();
            space_DefaultDraw();
            memcard_Update();
            UpdateMCState();
            VU1_syncChain(1);
            sceGsSyncV(0);
            gsFrame++;
            Respawn_IncCounter();
            if (!loadComplete)
                loadComplete = LoadLevelFiles();
        }

        if (!loadComplete) {
            do {
                FlushCache(0);
                sceGsSyncV(0);
                memcard_Update();
                UpdateMCState();
                Respawn_IncCounter();
            } while (LoadLevelFiles() == 0);
        }

        while (g_memcard.stage != MC_STAGE_IDLE || g_memcard.nextstage >= MC_STAGE_GET_INFO) {
            FlushCache(0);
            sceGsSyncV(0);
            memcard_Update();
            UpdateMCState();
            Respawn_IncCounter();
        }
    }

    sceCdSync(0);
    musicTransition.updatesSuspended = 0;
    DMAC_VIF1_Disable();
}

void Space_DrawTransitionOverlay(MobyInstance *moby)
{
    enum { SPACE_ENV_REFRESH_PENDING = 1, SPACE_ENV_REFRESH_CONSUMED = 2 };
    GeometryQuad quad;
    Mtx4 objectTransform;
    Vec4 normal;
    Vec4 reflection;
    Vec4 viewDirection;
    IndexedQuad *indexedQuads;
    Vec4 *positions;
    Vec4 *normals;
    int quadCount;
    int vertexCount;
    int classIndex;
    int color;
    int mappingEnabled;
    float transitionFraction;
    float sphereDenominator;
    float coordinate;
    int elementIndex;
    int cornerIndex;

    classIndex = (short)moby->oClass - 0x212;
    positions = SpaceEnvPositions[classIndex];
    normals = SpaceEnvNormals[classIndex];
    indexedQuads = SpaceEnvQuads[classIndex];
    quadCount = SpaceEnvQuadCounts[classIndex];
    vertexCount = SpaceEnvVertexCounts[classIndex];

    if (gameMode == GAME_MODE_SPACE && bootSpaceTransitionState.cutscene == SPACE_CUTSCENE_LOADING)
        quad.state[1] = FontSet(1);

    else
        quad.state[1] = FontSet(0x15);

    mappingEnabled = 0;
    color = SpaceEnvColors[classIndex];
    quad.state[2] = 0xFF9000000260;
    quad.state[3] = 0x8000000044;
    quad.state[0] = 0;
    quad.colors[3] = color;
    quad.colors[2] = color;
    quad.colors[1] = color;
    quad.colors[0] = color;

    MB_GetBoneTransformation(moby, 0, &objectTransform);

    if (gameMode != GAME_MODE_NORMAL || (FastAbsF(GameCamera.position.x - moby->pos.x) < 16.0f &&
                                         FastAbsF(GameCamera.position.y - moby->pos.y) < 16.0f)) {
        mappingEnabled = 1;
    }

    if (gameMode == GAME_MODE_SPACE && bootSpaceTransitionState.cutscene == SPACE_CUTSCENE_LOADING)
        mappingEnabled = 0;

    if (mappingEnabled != 0 || SpaceEnvRefresh == SPACE_ENV_REFRESH_PENDING) {
        SpaceEnvWasActive = 1;
        FastDecTimer(SpaceEnvTimer);
        transitionFraction =
            FastIntToFloat(SpaceEnvTimer) / FastIntToFloat(FastScaleRoundInt(0x3C));
        for (elementIndex = 0; elementIndex < vertexCount; elementIndex++) {
            FastTransformVec4(&SpaceEnvTransformedPositions[elementIndex], &positions[elementIndex],
                              &objectTransform);
            FastSubVec3(&viewDirection, &SpaceEnvTransformedPositions[elementIndex],
                        &GameCamera.position);
            FastVec3Normalize(&viewDirection, &viewDirection, 1.0f);
            FastTransformVec4(&normal, &normals[elementIndex], &objectTransform);
            FastVec3Normalize(&normal, &normal, 0.1f);
            FastVec3Scale(&reflection, &normal, FastVec3Dot(&normal, &viewDirection) * 2.0f);
            FastSubVec3(&reflection, &viewDirection, &reflection);
            FastVec3Normalize(&reflection, &reflection, 1.0f);
            reflection.z += 1.0f;
            sphereDenominator = FastFSqrt(reflection.z * 2.0f) * 2.0f;
            if (SpaceEnvRefresh == SPACE_ENV_REFRESH_PENDING || SpaceEnvTimer == 0) {
                SpaceEnvUVs[elementIndex][0] = reflection.x / sphereDenominator + 0.5f;
                SpaceEnvUVs[elementIndex][1] = reflection.y / sphereDenominator + 0.5f;
            }
            else {
                coordinate = reflection.x / sphereDenominator + 0.5f;
                SpaceEnvUVs[elementIndex][0] =
                    coordinate +
                    (SpaceEnvSavedUVs[elementIndex][0] - coordinate) * transitionFraction;
                coordinate = reflection.y / sphereDenominator + 0.5f;
                SpaceEnvUVs[elementIndex][1] =
                    coordinate +
                    (SpaceEnvSavedUVs[elementIndex][1] - coordinate) * transitionFraction;
            }
        }
        if (SpaceEnvRefresh == SPACE_ENV_REFRESH_PENDING)
            SpaceEnvRefresh = SPACE_ENV_REFRESH_CONSUMED;
    }

    else {
        if (SpaceEnvWasActive == 1) {
            SpaceEnvWasActive = 0;
            for (elementIndex = 0; elementIndex < vertexCount; elementIndex++) {
                SpaceEnvSavedUVs[elementIndex][0] = SpaceEnvUVs[elementIndex][0];
                SpaceEnvSavedUVs[elementIndex][1] = SpaceEnvUVs[elementIndex][1];
                FastTransformVec4(&SpaceEnvTransformedPositions[elementIndex],
                                  &positions[elementIndex], &objectTransform);
            }
        }
        else {
            for (elementIndex = 0; elementIndex < vertexCount; elementIndex++) {
                FastTransformVec4(&SpaceEnvTransformedPositions[elementIndex],
                                  &positions[elementIndex], &objectTransform);
            }
        }
        SpaceEnvTimer = FastScaleRoundInt(0x3C);
    }

    for (elementIndex = 0; elementIndex < quadCount; elementIndex++) {
        for (cornerIndex = 0; cornerIndex < 4; cornerIndex++) {
            int vertexIndex = indexedQuads[elementIndex].corners[cornerIndex].vertexIndex;

            CopyVec4Inline(&quad.positions[cornerIndex],
                           &SpaceEnvTransformedPositions[vertexIndex]);
            quad.textureCoordinates[cornerIndex][0] = SpaceEnvUVs[vertexIndex][0];
            quad.textureCoordinates[cornerIndex][1] = SpaceEnvUVs[vertexIndex][1];
        }
        FastDrawQuadReal(&quad, 0, 0);
    }
}
