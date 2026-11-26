#include "common.h"
#include "mathfunc_inline.h"
#include "draw.h"
#include "npc.h"
#include "mobyutil.h"
#include "fastfunc.h"
#include "hero.h"
#include "gameglobals.h"
#include "water.h"
#include "pad.h"
#include "sound.h"
#include "hud.h"
#include "memcard.h"
#include "loaders.h"
#include "vuchain.h"

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_ResetHero);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_InitStuff);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_GetIdleAnim);

int Hero_GetAnim(int animation)
{
    return animation;
}

int Hero_RegisterHealthHud(void);

void TakeDamage(int damage)
{
    if (damage) {
        if (damage > 1)
            damage = 1;

        Hero.health -= damage;
        if (Hero.health < 0)
            Hero.health = 0;

        Hero_RegisterHealthHud();
    }
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_GetTweakerMoby);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", hero_SetManipulator);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_UpdateTweakers);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_ResetTweakers);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_UpdateBlinkTimer);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", hero_SetEyeManipulator);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_UpdateGlowAndBlink);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", MetalDetectorUpdate_Unused);

enum { OCLASS_MAGNEBOOTS = 0xAD };

int sound_FootstepPlay(int groundType, int whichFoot, int magneboots, int flags, MobyInstance *moby);

void Hero_PlayFootStep(int groundType, int whichFoot, int playSound)
{
    if (playSound) {
        int magneboots = 0;
        if (Hero.items[1].moby)
            magneboots = (short)Hero.items[1].moby->oClass == OCLASS_MAGNEBOOTS;

        sound_FootstepPlay(groundType, whichFoot, magneboots, 0, Hero.moby);
    }
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_FeetSounds);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", HeroUpdateNonRatchet);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_KillLoopingSounds);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_DisplayHelpMsgs);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_CheckCheatSequences);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", HeroUpdate);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_SyncGadgetColors);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_SetLightsFromMoby);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_AddPulsingMobyGlow);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_UpdateColorEffects);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_GetHeroRelativeVector);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_RotEffects);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_UpdateScaleEffect);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_UpdateScreenFadeInOut);

void Hero_DrawGlows(MobyInstance *moby);

void Hero_RegisterGlowDraw(void)
{
    if (!Hero.glowDrawRegistered) {
        Hero.glowDrawRegistered = 1;
        RegisterMobyDraw(Hero_DrawGlows, Hero.moby);
    }
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_DrawGlows);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_SetGadgetColor);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_UpdateGadgetGlows);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_MapToMoby);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_MapToMobyNonRatchet);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_UpdateShadow);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_GetAnimFrameBlend);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_GetLoopedAnimFrame);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_ApplyRootMotionDelta);

void FastVecZero(Vec4 *vector);
void Hero_ApplyRootMotionDelta(Vec4 *out, float x, float y, float z);

void Hero_ApplyRootMotion(float x, float y, float z)
{
    Vec4 displacement;

    FastVecZero(&displacement);
    displacement.z = 0.6f;
    Hero_ApplyRootMotionDelta(&displacement, x, y, z);
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_GetJoint9Mtx);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_BuildPoseFromJoints);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_SpawnWaterRings);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_SpawnWaterWake);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_SpawnWaterDrops);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_SpawnWaterBubbles);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_SpawnWaterSplash);

void Hero_SetTweakPair_97b44(float first, float second)
{
    HeroTweaks.unk_A4 = first;
    HeroTweaks.unk_A8 = second;
}

void Hero_SetTweakPair_929e8(float first, float second)
{
    HeroTweaks.unk_154 = first;
    HeroTweaks.unk_158 = second;
}

void Hero_SetTweak_721dd4(float first, float second)
{
    HeroTweaks.unk_204 = first;
    HeroTweaks.unk_208 = second;
}

void Hero_SetTweak_721e84(float first, float second)
{
    HeroTweaks.unk_2B4 = first;
    HeroTweaks.unk_2B8 = second;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_ProbeLineHit);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_UpdateCrateTargeting);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_ClearBlock);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_UpdateCheatTweaks);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_UpdateIdleLook);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_UpdateLookAtTarget);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_UpdateTiltWobbleFx);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_UpdateLedge);

void Hero_ResetIfTypeThree(void)
{
    if (Hero.type == HERO_TYPE_HOLOGUISE)
        Hero_RevertToRatchet();
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_HandleGroundType);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_CheckLedgeGrab);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_CheckLedgeAhead);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_HandGadgetID);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_GetGadgetMoby);

int Hero_GetGadgetMoby(int slot);

int Hero_IsWeaponGroupB(int slot)
{
    int gadget = Hero_GetGadgetMoby(slot);
    if (gadget == ITEM_MINE_GLOVE || gadget == ITEM_BOMB_GLOVE || gadget == ITEM_GLOVE_OF_DOOM || gadget == ITEM_DECOY_GLOVE)
        return 1;

    return 0;
}

int Hero_GetGadgetMoby(int slot);

int Hero_IsWeaponGroupA(int slot)
{
    return (unsigned int)(Hero_GetGadgetMoby(slot) - ITEM_SONIC_SUMMONER) < 3;
}

int Hero_IsWearingBoots(int slot)
{
    return (unsigned int)(Hero_GetGadgetMoby(slot) - ITEM_MAGNEBOOTS) < 2;
}

int Hero_IsInSpecialMovementState(void)
{
    if ((unsigned int)(Hero.stateType - HERO_STATE_TYPE_SWIM) < 2 ||
        Hero.state == HERO_STATE_DROWN ||
        Hero.state == HERO_STATE_ELECTRIC_DEATH_UNDER ||
        Hero.state == HERO_STATE_GET_HIT_UNDER ||
        Hero.state == HERO_STATE_GET_HIT_SURF)
        return 1;

    return 0;
}

int Hero_DefaultByteIfFF(MobyInstance *moby, int animation)
{
    if (animation == 0xFF)
        animation = moby->previousAnimationId;

    return animation;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_GetGadgetAnimBlend);

enum { HERO_HISTORY_COUNT = 32 };

float Hero_GetRotationHistory(int framesAgo)
{
    if (framesAgo >= HERO_HISTORY_COUNT)
        framesAgo = HERO_HISTORY_COUNT - 1;
    if (framesAgo > Hero.rotZHistoryCount)
        framesAgo = Hero.rotZHistoryCount;

    return Hero.rotZHistory[(Hero.rotZHistoryIdx - framesAgo + HERO_HISTORY_COUNT - 1) % HERO_HISTORY_COUNT];
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_ComputeTargetScore);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_GetAutoTargetMoby);

int Hero_GetOverlayAnimId(int overlay)
{
    switch (overlay) {
    case 1:
        return 121;
    case 2:
        return 119;
    case 3:
        return 117;
    default:
        return 0;
    }
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_UpdateOverlayAnimLayer);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_UpdateGadgetAnimLayers);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_UpdateWeaponReadyAnim);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_PlayFiringAnim);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_PlayBackpackIdle);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_UpdateFiringAnimLayer);

void Hero_UpdateGadgetAnimLayers(void);
void Hero_UpdateFiringAnimLayer(void);
void Hero_UpdateOverlayAnimLayer(void);

void Hero_UpdateAnimLayers(void)
{
    Hero_UpdateGadgetAnimLayers();
    Hero_UpdateFiringAnimLayer();
    Hero_UpdateOverlayAnimLayer();
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", EquipItem);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Mtx3_AbsDiffSum);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_PushGadgetMtxHistory);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_UpdateGadgetMobys);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_KillGadget);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_SetGadgetSwitchTimerA);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_SetGadgetSwitchTimerB);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_CanSwitchGadget);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_HandleGadgetSwitching);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_UpdateGadgetSlots);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_UpdateGadgets);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", SetHeroType);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_RevertToRatchet);

void FastVec3RSqrtScale(Vec4 *out, Vec4 *direction, float scale);

void Hero_NormalizeThrust(Vec4 *direction, float horizontal, float vertical, int scaleComponents)
{
    if (scaleComponents) {
        direction->x *= horizontal;
        direction->y *= horizontal;
        direction->z *= vertical;
    }

    else {
        FastVec3RSqrtScale(direction, direction, horizontal);
        direction->z = vertical;
    }
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_HandleDamage);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", HandleHeroDeath);

enum { WRENCH_CLASS = 0x47 };

int Hero_isMobyWrench(MobyInstance *moby)
{
    if (!moby)
        return 0;

    return (short)moby->oClass == WRENCH_CLASS;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_UpdateCollisionSize);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_UpdateMovement);

float Hero_GetPadMagnitude(void)
{
    float magnitude = FastVec3Length(Hero.padStick);

    if (magnitude > 1.0f)
        magnitude = 1.0f;

    return magnitude;
}

int Hero_AnimFrameInWindow(float frame)
{
    if (frame < Hero.animFrame)
        return Hero.animFrame - frame <= Hero.animFrameWindow;

    return 0;
}

void Hero_ZeroThrustVars(void)
{
    Hero.idealSpeed = 0.0f;
    Hero.storedNeutralSpeed = 0.0f;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_GetIdealThrustFromPad);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_GetIdealThrustForWalk);

void FastEulerToMtx1(Mtx4 *out, Vec4 *angles);
void MB_GetOrientationMtx(Mtx4 *matrix, Vec4 *out);

void Hero_RotateByEuler(float xAngle, float yAngle, float zAngle)
{
    Vec4 angles;
    Mtx4 rotationDelta;
    Mtx4 orientation;

    angles.x = xAngle;
    angles.y = yAngle;
    angles.z = zAngle;
    FastEulerToMtx1(&rotationDelta, &angles);
    FastEulerToMtx1(&orientation, &Hero.rotation);
    FastMtxTransform(&orientation, &orientation, &rotationDelta);
    MB_GetOrientationMtx(&orientation, &Hero.rotation);
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_Turn3D);

void Hero_Turn3D(float gain, float damping, float limit, int direction);
float AccelDeltAng(float &angle, float target, float &speed, float gain, float damping, float limit, int direction);

void Hero_Turn(float gain, float damping, float limit, int direction)
{
    if (Hero.gravityMode)
        Hero_Turn3D(gain, damping, limit, direction);
    else
        Hero.turnDelta = AccelDeltAng(Hero.rotation.z, Hero.idealRotZ, Hero.turnSpeed, gain, damping, limit, direction);
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_GunTurnWalk);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_TurnWalk);

void Hero_ThrustModeAccel(float acceleration, float deceleration)
{
    if (Hero.storedNeutralSpeed < Hero.idealSpeed)
        Delt(Hero.storedNeutralSpeed, Hero.idealSpeed, acceleration);

    else
        Delt(Hero.storedNeutralSpeed, Hero.idealSpeed, deceleration);
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_ThrustToMotionFwd);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_WallSloopMotion);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_KneeBumpMotion);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_UpdateExternalThrust);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_GetGroundInfo);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_SnapToGround);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_ThrustToMotion);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_SinCosDot);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_ResolveCollision);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", func_00233D04);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_ResolveCollisionWithHistory);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_ApplyMotion);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_ScaleMotion);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_JumpTranslation);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_JumpThrustGrav);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_JumpTurnTrans);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_UpdateAutoTargetAim);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_SetMagnebootsTweaks);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_SetBankTwistSway);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_SetBackpackSway);

void FastMtx3Transpose(Mtx4 *out, Mtx4 *matrix);
void FastTransformVec4(Vec4 *out, Vec4 *vector, Mtx4 *matrix);
float FastFSqrt(float value);

void Hero_AlignToVec(Vec4 *direction, Vec4 *out)
{
    Mtx4 orientation;
    Mtx4 inverse;
    Vec4 local;

    CopyVec4Inline(&local, direction);
    FastEulerToMtx1(&orientation, &Hero.moby->rotation);
    FastMtx3Transpose(&inverse, &orientation);
    FastTransformVec4(&local, &local, &inverse);

    out->x = FastArcTan(FastFSqrt(local.x * local.x + local.z * local.z), local.y);
    out->y = -FastArcTan(local.z, local.x);
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", func_00236090);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_Turn3D_XYZ);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_AlignToGravityInAir);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_AlignToGravity);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_ApplyFriction);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_PlaySound);

enum { HERO_LOOP_SOUND_FLAGS = 4 };
int sound_PlayMobySound(int soundId, int flags, MobyInstance *moby);

void Hero_PlayLoopSound(int slot, MobyInstance *moby, int soundId)
{
    if (Hero.loopSounds[slot] == -1)
        Hero.loopSounds[slot] = sound_PlayMobySound(soundId, HERO_LOOP_SOUND_FLAGS, moby);

    Hero.loopSoundMobys[slot] = moby;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_QueueSound);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_UpdateQueuedSounds);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_Warp);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_EdgeStop);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_JumpOrSnapJumpCheck);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_ThrowWrench);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_DoBehavior);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_UpdateGroundCollision);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_UpdateMovementState);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_UpdateIdleDetect);

int Hero_GetSnapJumpDir(void);
enum { SNAP_JUMP_NO_HOLD = 2, SNAP_JUMP_STANDARD_HOLD = 3 };

int Hero_GetJumpHoldTime(void)
{
    int frames = FastScaleRoundInt(12);
    int direction = Hero_GetSnapJumpDir();

    if (direction == SNAP_JUMP_NO_HOLD)
        frames = 0;
    else if (direction == SNAP_JUMP_STANDARD_HOLD)
        frames = FastScaleRoundInt(12);

    return frames;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_GetSnapJumpDir);

extern WaterTile *WaterTiles;
extern int WaterTileCnt;
void WaterTile_PutDrop(WaterTile *tile, int tiles, int mode, float x, float y, float radius, float height);

int Hero_GetAnim(int animation);
void Hero_TransAnim(int animation, int frame, float blend);
int Hero_GetIdleAnim(int index);
void Hero_PlayBackpackIdle(void);
int Hero_PlaySound(int soundId, int flags);
void Hero_QueueSound(int soundId, int flags, int delay);
void Hero_SpawnWaterSplash(int puffs, int debris, int flash);
void Hero_KillLoopingSounds(void);
int Hero_CheckGadgetReady(void);
void Hero_ClearBlock(void);
void Hero_ResetIfTypeThree(void);
void Hero_UpdateWeaponReadyAnim(int previous, int current);
void Hero_ScaleMotion(float scale);
void Hero_UpdateAutoTargetAim(float range, float coneAngle, float turnRate);
void Hero_SetNextAnimFrame(int animation, int frame);
void AddMotionBlurElem(MotionBlur *blur, int alpha, int delay);
void Hero_ToHeroRelative(Vec4 *out, Vec4 *in, float z);
float Hero_RelativeXYLength(float *vector);
MobyInstance *Hero_HandGadgetID(int slot);
float Hero_GetRotationHistory(int back);
int Hero_IsInSpecialMovementState(void);
float Hero_GetIdealThrustFromPad(float scale, int mode);
void MB_SetAnimation(MobyInstance *moby, int animation, int frame, int blend);
COLL_DAM_OUT *MB_FindSlotByMask(MobyInstance *moby, int mask, int flag);
float MB_randRangeSigned(float low, float high);
extern float frameTime;
extern float frameTimeSq;
extern unsigned char optMirrorAnim;
extern int Level;
extern int videoModePal;
extern float transStepScale;

// Small data of the hero code. Only the timers are named so far, the rest belongs to hero functions
// that are not decompiled yet.
int R1RepeatTimer __attribute__((section(".sdata"))) = 0;
float HeroSdata15F67C __attribute__((section(".sdata"))) = 0.1f;
int HeroSdata15F680[2] __attribute__((section(".sdata"))) = {0, 0};
int HelpHintTimer __attribute__((section(".sdata"))) = 0;
int HeroSdata15F68C __attribute__((section(".sdata"))) = 0;
int HeroSdata15F690[8] __attribute__((section(".sdata"))) = {1, 11, 0, 0, 12, 13, 7, 8};
int HeroSdata15F6B0 __attribute__((section(".sdata"))) = 10;
int HeroSdata15F6B4 __attribute__((section(".sdata"))) = -1;
int HeroSdata15F6B8[6] __attribute__((section(".sdata"))) = {0x10030065, 0x11040065, 0xFFFF, 0, 0, 1};
int HeroSdata15F6D0[2] __attribute__((section(".sdata"))) = {5, 0};

int HeroSlideAnimFrames[4] __attribute__((section(".sdata"))) = {8, 0, 11, 16};

HeroVelocityKey HeroPackJumpVelocityKeys[1] __attribute__((section(".sdata"))) = {
    {48.0f, 0.0f, 1000}
};

int Hero_InitBodyState(int state, int animMode)
{
    int savedSubState;
    MobyInstance *moby;
    int hadItemSelectBlocked;

    {
        HeroState *hero = &Hero;

        if (hero->stateType == HERO_STATE_TYPE_DYING &&
            (state != HERO_STATE_CUSTOM_UI ||
             animMode != 2))
            return 0;
    }

    if ((gameMode == GAME_MODE_SCENE || gameMode == GAME_MODE_SPACE) &&
        animMode != 2)
        return 0;

    {
        HeroState *hero = &Hero;

        if (hero->health == 0 &&
            (hero->stateType == HERO_STATE_TYPE_FALL || hero->stateType == HERO_STATE_TYPE_HURT) &&
            state != HERO_STATE_FALL && state != HERO_STATE_DEATH &&
            state != HERO_STATE_CLANK_DYING &&
            state != HERO_STATE_HOLOGUISE_DYING &&
            state != HERO_STATE_GIANT_CLANK_DYING &&
            state != HERO_STATE_DEATH_FALL &&
            state != HERO_STATE_DEATHSAND_SINK &&
            state != HERO_STATE_LAVA_DEATH && state != HERO_STATE_ICEWATER_FREEZE &&
            state != HERO_STATE_DROWN &&
            state != HERO_STATE_ELECTRIC_DEATH &&
            state != HERO_STATE_ELECTRIC_DEATH_UNDER)
            return 0;
    }

    {
        HeroState *hero = &Hero;

        savedSubState = hero->subState;
        moby = hero->moby;
        hadItemSelectBlocked = hero->itemSelectBlocked;
        hero->prev2State = hero->prevState;
        hero->prev2StateType = hero->prevStateType;
        hero->prevStateTimer = hero->stateTimer;
        hero->prevState = hero->state;
        hero->prevStateType = hero->stateType;
        hero->state = state;
        hero->subState = 0;
        hero->invisible = 0;
        hero->itemUseLocked = 0;

        if (hero->type == HERO_TYPE_RATCHET) {
            moby->collisionMesh = 0;
            hero->tiltDisabled = 0;
            hero->itemSelectBlocked = 0;
            hero->onHoverboard = 0;
            hero->handItemHidden = 0;
            hero->glowPulseLevel = 0;
            DeleteMotionBlur(&hero->trail);
        }

        if (hero->type == HERO_TYPE_HOLOGUISE) {
            int currentState = hero->state;

            if (!(currentState >= HERO_STATE_HOLOGUISE_STANDING && currentState <= HERO_STATE_HOLOGUISE_WAVE) &&
                !(currentState >= HERO_STATE_WALK_TO_POS && currentState <= HERO_STATE_IDLE_TO_POS) &&
                currentState != HERO_STATE_IDLE && currentState != HERO_STATE_LOOK)
                Hero_ResetIfTypeThree();
        }
    }

    {
        HeroState *hero = &Hero;

        Hero_UpdateWeaponReadyAnim(hero->prevState, hero->state);
        hero->randTimer.range = 0;
    }

    switch (state) {
    case HERO_STATE_IDLE: {
        HeroState *hero = &Hero;

        hero->stateType = HERO_STATE_TYPE_IDLE;
        hero->requestedCamType = 0;
        hero->headLookTimer = MB_randRange(FastScaleRoundInt(0x32), FastScaleRoundInt(0x64));
        Hero_ClearBlock();

        if (hero->type != HERO_TYPE_RATCHET) {
            Hero_TransitionToDefault();
            return 1;
        }

        CopyVec4Inline(&hero->externalMomentum, &hero->resolvedVelocity);

        if (hero->onSlipGround != 0 && hero->framesOffGround == 0) {
            Hero_InitBodyState(HERO_STATE_SLOPESLIDE, 1);
            return 0;
        }

        {
            HeroState *hero = &Hero;

            hero->randTimer.range = 0x68;
        }

        if (animMode) {
            if (Hero_GetIdleAnim(0) == 0x54)
                Hero_TransAnim(
                    Hero_GetIdleAnim(0), 0, (float)FastScaleRoundInt(0x12));

            else
                Hero_TransAnim(Hero_GetIdleAnim(0), 0, -1.0f);
        }
        break;
    }

    case HERO_STATE_IDLE_TO_POS: {
        HeroState *hero = &Hero;

        hero->stateType = HERO_STATE_TYPE_IDLE;
        hero->requestedCamType = 0;
        FastVecZero(&hero->externalMomentum);
        hero->randTimer.range = 0x68;

        if (animMode) {
            if (Hero_GetIdleAnim(0) == 0x54)
                Hero_TransAnim(
                    Hero_GetIdleAnim(0), 0, (float)FastScaleRoundInt(0x12));

            else
                Hero_TransAnim(Hero_GetIdleAnim(0), 0, -1.0f);
        }
        break;
    }

    case HERO_STATE_FIDGET_ALT: {
        int blendFrames = FastScaleRoundInt(9);

        Hero_TransAnim(Hero_GetIdleAnim(0), 0, (float)blendFrames);

        {
            HeroState *hero = &Hero;

            if (hero->fidgetPropMoby != 0)
                MB_SetAnimation(hero->fidgetPropMoby, 0, 0, blendFrames);
        }
        break;
    }

    case HERO_STATE_DEATH: {
        HeroState *hero = &Hero;

        hero->stateType = HERO_STATE_TYPE_DYING;
        hero->requestedCamType = 0;
        CopyVec4Inline(&hero->externalMomentum, &hero->resolvedVelocity);

        if (animMode)
            Hero_TransAnim(0x45, 0, (float)FastScaleRoundInt(0xC));
        break;
    }

    case HERO_STATE_ELECTRIC_DEATH: {
        HeroState *hero = &Hero;

        hero->stateType = HERO_STATE_TYPE_DYING;
        hero->requestedCamType = 0;
        hero->health = 0;
        CopyVec4Inline(&hero->externalMomentum, &hero->resolvedVelocity);
        ClampVec3Magnitude(&hero->externalMomentum, frameTime * 3.5f);

        if (animMode)
            Hero_TransAnim(0x7C, 0, (float)FastScaleRoundInt(0xC));
        break;
    }

    case HERO_STATE_ICEWATER_FREEZE: {
        HeroState *hero = &Hero;

        hero->stateType = HERO_STATE_TYPE_DYING;
        hero->requestedCamType = 0;
        hero->health = 0;
        hero->swimBobVelocity = hero->displacement.z * 0.2f;
        hero->swimWaterLevel = hero->waterHeight - 0.37f;

        if (hero->swimBobVelocity < frameTime * -7.0f)
            hero->swimBobVelocity = frameTime * -7.0f;
        hero->itemSelectBlocked = 1;
        hero->swimWaterLevelVelocity = 0;
        hero->swimBobOffset = hero->position.z - hero->swimWaterLevel;

        if (animMode)
            Hero_TransAnim(0x74, 0, (float)FastScaleRoundInt(0xB));
        break;
    }

    case HERO_STATE_SWIMUNDER: {
        HeroState *hero = &Hero;

        hero->stateType = HERO_STATE_TYPE_SWIM;
        hero->requestedCamType = 0xB;
        hero->itemSelectBlocked = 1;
        hero->drownSinkSpeed = 0.0f;

        if (hero->prevStateType == HERO_STATE_TYPE_WATER_SURFACE) {
            Hero_PlaySound(3, 0);
            hero->subState = 1;
        }


        else
            hero->swimThrustTimer = FastScaleRoundInt(0x2D);

        {
            HeroState *hero = &Hero;
            int blendFrames;

            hero->randTimer.range = 0x68;
            hero->swimEntryFrames = 0;
            blendFrames = FastScaleRoundInt(0xC);

            if (animMode)
                Hero_TransAnim(0x3B, 0, (float)blendFrames);
        }
        break;
    }

    case HERO_STATE_CHARGEUNDER: {
        HeroState *hero = &Hero;
        int blendFrames;

        hero->stateType = HERO_STATE_TYPE_SWIM;
        hero->requestedCamType = 0xB;
        hero->itemSelectBlocked = 1;
        hero->swimThrustTimer = FastScaleRoundInt(0x3C);

        if (hero->prevStateType == HERO_STATE_TYPE_WATER_SURFACE) {
            Hero_PlaySound(3, 0);
            hero->subState = 1;
        }

        hero->swimEntryFrames = 0;
        hero->randTimer.range = 0x68;
        blendFrames = FastScaleRoundInt(0xB);

        if (hero->prevState == HERO_STATE_SWIMUNDER)
            blendFrames = FastScaleRoundInt(0xF);

        if (animMode)
            Hero_TransAnim(0x3D, 0, (float)blendFrames);
        break;
    }

    case HERO_STATE_IDLEUNDER: {
        HeroState *hero = &Hero;
        int blendFrames;

        hero->stateType = HERO_STATE_TYPE_SWIM;
        hero->requestedCamType = 0xB;
        hero->itemSelectBlocked = 1;
        CopyVec4Inline(&hero->externalMomentum, &hero->resolvedVelocity);
        hero->randTimer.range = 0x68;
        blendFrames = FastScaleRoundInt(0x23);

        if (hero->prevState == HERO_STATE_CHARGEUNDER)
            blendFrames = -2;

        if (animMode)
            Hero_TransAnim(0x3C, 0, (float)blendFrames);
        break;
    }

    case HERO_STATE_IDLESURF: {
        HeroState *hero = &Hero;

        hero->stateType = HERO_STATE_TYPE_WATER_SURFACE;
        hero->itemSelectBlocked = 1;
        hero->requestedCamType = 0;
        hero->splashEffectTimer = 0;

        if (hero->prevStateType == HERO_STATE_TYPE_SWIM) {
            Hero_SpawnWaterSplash(3, 0xA, 0);

            if (WaterTiles != 0)
                WaterTile_PutDrop(WaterTiles,
                            WaterTileCnt,
                            0,
                            hero->position.x,
                            hero->position.y,
                            0.4f,
                            0.3f);
        }


        else if (hero->displacement.z < frameTime * -0.5f) {
            int splashCount = FastFloatToInt(FastAbsF(hero->displacement.z) * 300.0f);

            Hero_SpawnWaterSplash(3, splashCount < 0x28 ? splashCount : 0x28, 1);

            if (WaterTiles != 0)
                WaterTile_PutDrop(WaterTiles,
                            WaterTileCnt,
                            0,
                            hero->position.x,
                            hero->position.y,
                            0.5f,
                            -0.4f);
            hero->splashEffectTimer = FastScaleRoundInt(0x4B);
        }

        {
            HeroState *hero = &Hero;

            hero->swimStrokeTimer = 0;

            if (hero->prevStateType == HERO_STATE_TYPE_SWIM) {
                if ((float)hero->oxygen < 2500.0f)
                    Hero_QueueSound(8, FastScaleRoundInt(0x1E), 0);

                else if ((float)hero->oxygen < 7500.0f)
                    Hero_QueueSound(7, FastScaleRoundInt(0x1B), 0);

                {
                    HeroState *hero = &Hero;

                    if (hero->prevStateType == HERO_STATE_TYPE_SWIM) {
                        if ((float)hero->oxygen < 2500.0f)
                            Hero_QueueSound(8, FastScaleRoundInt(0x1E), 0);

                        else if ((float)hero->oxygen < 7500.0f)
                            Hero_QueueSound(7, FastScaleRoundInt(0x28), 0);
                    }
                }
            }
        }

        {
            HeroState *hero = &Hero;

            hero->swimBobVelocity = hero->displacement.z * 0.37f;

            if (hero->swimBobVelocity < frameTime * -7.0f)
                hero->swimBobVelocity = frameTime * -7.0f;
            hero->swimWaterLevel = hero->waterHeight;
            hero->swimWaterLevelVelocity = 0;
            hero->swimBobOffset = hero->position.z - hero->swimWaterLevel - -0.12f;
            CopyVec4Inline(&hero->externalMomentum, &hero->resolvedVelocity);
            hero->externalMomentum.z = 0.0f;
            ClampVec3Magnitude(&hero->externalMomentum, frameTime * 5.5f);
            hero->randTimer.range = 0x68;

            if (animMode)
                Hero_TransAnim(0x3A, 0, (float)FastScaleRoundInt(0x16));
        }
        break;
    }

    case HERO_STATE_GET_HIT_SURF:

    case HERO_STATE_GET_HIT_UNDER: {
        HeroState *hero = &Hero;
        COLL_DAM_OUT *damage;

        hero->stateType = HERO_STATE_TYPE_HURT;
        hero->requestedCamType = 0;
        Hero_ScaleMotion(0.5f);
        hero->itemSelectBlocked = 1;
        CopyVec4Inline(&hero->velocity, &hero->displacement);
        damage = MB_FindSlotByMask(hero->moby, 1, 0);

        if (damage != 0)
            TakeDamage(FastFloatToInt(damage->damageHp));

        else
            TakeDamage(1);

        {
            int postHitInvinc = FastScaleRoundInt(0x4D);
            HeroState *hero = &Hero;

            hero->postHitInvinc = postHitInvinc;

            if (animMode) {
                if (hero->state == HERO_STATE_GET_HIT_SURF)
                    Hero_TransAnim(0x70, 3, -3.0f);

                else
                    Hero_TransAnim(0x6F, 3, -3.0f);

                {
                    HeroState *hero = &Hero;

                    hero->moby->animationBlend =
                        HeroAnimBlendCurves[hero->animBlendCurve][(hero->animBlendStep)++];
                }
            }
        }
        break;
    }

    case HERO_STATE_SWIMSURF: {
        HeroState *hero = &Hero;

        hero->stateType = HERO_STATE_TYPE_WATER_SURFACE;
        hero->itemSelectBlocked = 1;
        hero->requestedCamType = 0;
        hero->drownSinkSpeed = 0.0f;
        hero->swimStrokeTimer = FastScaleRoundInt(0x2D);
        hero->randTimer.range = 0x68;

        if (animMode)
            Hero_TransAnim(0x65, 0, (float)FastScaleRoundInt(0x11));
        break;
    }

    case HERO_STATE_DROWN: {
        HeroState *hero = &Hero;

        hero->stateType = HERO_STATE_TYPE_DYING;
        hero->itemSelectBlocked = 1;
        hero->requestedCamType = 0;
        hero->health = 0;

        if (hero->jumpButtonFrames > FastScaleRoundInt(0x32)) {
            UsageStat *stats = ActionUsageStats;

            if (stats[USAGE_DROWN].count <= 0xFFFE)
                stats[USAGE_DROWN].count = stats[USAGE_DROWN].count + 1;
        }

        {
            UsageStat *stats = ActionUsageStats;

            if (FastScaleRoundInt(TotalPlayTime) / 600 > stats[USAGE_DROWN].latestTimeBucket)
                stats[USAGE_DROWN].latestTimeBucket = FastScaleRoundInt(TotalPlayTime) / 600;

            {
                HeroState *hero = &Hero;

                stats[USAGE_DROWN].levelMask =
                    stats[USAGE_DROWN].levelMask | (1 << Level) | USAGE_STAT_USED;

                if (hero->swimCrossTapCount >= 3) {
                    if (stats[USAGE_DROWN_FLAIL].count <= 0xFFFE)
                        stats[USAGE_DROWN_FLAIL].count = stats[USAGE_DROWN_FLAIL].count + 1;
                }
            }
        }

        {
            UsageStat *stats = ActionUsageStats;

            if (FastScaleRoundInt(TotalPlayTime) / 600 > stats[USAGE_DROWN_FLAIL].latestTimeBucket)
                stats[USAGE_DROWN_FLAIL].latestTimeBucket = FastScaleRoundInt(TotalPlayTime) / 600;
            stats[USAGE_DROWN_FLAIL].levelMask =
                stats[USAGE_DROWN_FLAIL].levelMask | (1 << Level) | USAGE_STAT_USED;
        }

        CopyVec4Inline(&Hero.externalMomentum, &Hero.resolvedVelocity);

        if (animMode)
            Hero_TransAnim(0x5F, 0, (float)FastScaleRoundInt(0xA));
        break;
    }

    case HERO_STATE_ELECTRIC_DEATH_UNDER: {
        HeroState *hero = &Hero;

        hero->stateType = HERO_STATE_TYPE_DYING;
        hero->itemSelectBlocked = 1;
        hero->requestedCamType = 0;
        hero->health = 0;
        CopyVec4Inline(&hero->externalMomentum, &hero->resolvedVelocity);

        if (animMode)
            Hero_TransAnim(0x80, 0, (float)FastScaleRoundInt(0xA));
        break;
    }

    case HERO_STATE_LOOK: {
        HeroState *hero = &Hero;
        int idleAnimation;

        hero->stateType = HERO_STATE_TYPE_IDLE;
        hero->requestedCamType = 4;
        HelpHintTimer = FastScaleRoundInt(0x3C);

        if (hero->weaponUp == 0) {
            idleAnimation = Hero_GetIdleAnim(1);

            if (hero->moby->animationId != idleAnimation && animMode)
                Hero_TransAnim(idleAnimation, 0, (float)FastScaleRoundInt(0x12));
        }
        break;
    }

    case HERO_STATE_ITEM_BUTTON_RELEASE_WAIT: {
        HeroState *hero = &Hero;

        hero->stateType = HERO_STATE_TYPE_ITEM_RELEASE_WAIT;
        hero->requestedCamType = 0;
        CopyVec4Inline(&hero->externalMomentum, &hero->displacement);
        Hero_TransAnim(Hero_GetIdleAnim(0), 0, (float)FastScaleRoundInt(0xA));
        hero->idleReturnDelay = FastScaleRoundInt(7);
        break;
    }

    case HERO_STATE_WAIT_FOR_ITEM_RELEASE_THEN_IDLE: {
        HeroState *hero = &Hero;

        hero->stateType = HERO_STATE_TYPE_ITEM_RELEASE_WAIT;
        hero->requestedCamType = 0;
        CopyVec4Inline(&hero->externalMomentum, &hero->displacement);
        Hero_TransAnim(Hero_GetIdleAnim(0), 0, (float)FastScaleRoundInt(5));
        hero->idleReturnDelay = FastScaleRoundInt(7);
        break;
    }

    case HERO_STATE_ITEM_BUTTON_HOLD_ANIMATION_WAIT: {
        HeroState *hero = &Hero;

        hero->stateType = HERO_STATE_TYPE_RUN;
        hero->requestedCamType = 0;
        hero->storedNeutralSpeed = FastVec3Length(&hero->displacement.x);
        hero->subState = 0;
        hero->moveAlongStick = 0;
        hero->runStartBlending = 0;
        Hero_TransAnim(0x2E, 0, (float)FastScaleRoundInt(5));
        break;
    }

    case HERO_STATE_WALK:
    case HERO_STATE_MAGNE_WALK:

    case HERO_STATE_WADE: {
        HeroState *hero = &Hero;

        hero->stateType = HERO_STATE_TYPE_RUN;
        hero->requestedCamType = 0;

        if (hero->prevStateType != HERO_STATE_TYPE_JUMP &&
            hero->prev2StateType != HERO_STATE_TYPE_JUMP) {
            hero->storedNeutralSpeed = FastVec3Length(&hero->resolvedVelocity.x);
        }

        {
            HeroState *hero = &Hero;

            if (frameTime * 7.0f < hero->storedNeutralSpeed)
                hero->storedNeutralSpeed = frameTime * 7.0f;
            hero->sharpTurn = 0;
            Hero_GetIdealThrustFromPad(1.0f, 0);

            if (1.5707964f <
                FastDiffRots(hero->rotation.z, hero->idealRotZ)) {
                if (hero->prevStateType == HERO_STATE_TYPE_HURT || hero->prevState == HERO_STATE_SKID ||
                    hero->prev2State == HERO_STATE_SKID) {
                    HeroState *hero = &Hero;

                    hero->storedNeutralSpeed = 0.0f;
                }
            }
        }

        {
            HeroState *hero = &Hero;

            hero->randTimer.range = 0x68;

            if (hero->onSlipGround != 0 && hero->framesOffGround == 0) {
                Hero_InitBodyState(HERO_STATE_SLOPESLIDE, 1);
                return 0;
            }
        }

        {
            HeroState *hero = &Hero;

            if (hero->wading != 0 || hero->state == HERO_STATE_WADE) {
                hero->state = HERO_STATE_WADE;
                Hero_TransAnim(0x60, 0, (float)FastScaleRoundInt(8));
            }


            else {
                int blendFrames;

                hero->subState = 0;
                hero->moveAlongStick = 0;
                hero->runStartBlending = 0;
                blendFrames = FastScaleRoundInt(8);

                if (hero->health == 1)
                    blendFrames = FastScaleRoundInt(0xC);

                if (hero->prev2State == HERO_STATE_THROWING_ITEM)
                    blendFrames = FastScaleRoundInt(0xF);

                if (hero->prev2State == HERO_STATE_FALL || hero->prev2State == HERO_STATE_SWING_FALL)
                    blendFrames = FastScaleRoundInt(0x12);

                {
                    HeroState *hero = &Hero;

                    if (hero->prev2StateType == HERO_STATE_TYPE_JUMP &&
                        FastScaleRoundInt(5) < hero->dustHoverState)
                        blendFrames = FastScaleRoundInt(0xD);
                }

                if (animMode) {
                    HeroState *hero = &Hero;

                    Hero_TransAnim(hero->subState + 3, HeroSlideAnimFrames[hero->subState],
                                   (float)blendFrames);
                }
            }
        }
        break;
    }

    case HERO_STATE_WALK_TO_POS: {
        HeroState *hero = &Hero;

        hero->stateType = HERO_STATE_TYPE_RUN;
        hero->requestedCamType = 0;
        hero->storedNeutralSpeed = FastVec3Length(&hero->resolvedVelocity.x);
        hero->itemUseLocked = 1;

        if (hero->type == HERO_TYPE_RATCHET)
            Hero_PlayBackpackIdle();

        if (animMode) {
            if (hero->type == HERO_TYPE_HOLOGUISE)
                Hero_TransAnim(1, 0, (float)FastScaleRoundInt(8));

            else if (hero->type == HERO_TYPE_CLANK)
                Hero_TransAnim(2, 0, (float)FastScaleRoundInt(8));

            else if (hero->type == HERO_TYPE_RATCHET)
                Hero_TransAnim(
                    hero->subState + 3, HeroSlideAnimFrames[hero->subState], (float)FastScaleRoundInt(8));
        }
        break;
    }

    case HERO_STATE_SLIDE: {
        HeroState *hero = &Hero;

        hero->stateType = HERO_STATE_TYPE_SLIDE;
        hero->requestedCamType = 3;
        hero->itemSelectBlocked = 1;
        FastMemSet((char *)hero + 0x9D0, 0, 0x20);
        CopyVec4Inline(&hero->externalMomentum, &hero->displacement);

        if (animMode)
            Hero_TransAnim(0x64, 0, (float)FastScaleRoundInt(0xF));
        break;
    }

    case HERO_STATE_SKID: {
        HeroState *hero = &Hero;

        hero->stateType = HERO_STATE_TYPE_RUN;
        hero->requestedCamType = 0;
        CopyVec4Inline(&hero->externalMomentum, &hero->resolvedVelocity);

        if (hero->onSlipGround != 0 && hero->framesOffGround == 0) {
            Hero_InitBodyState(HERO_STATE_SLOPESLIDE, 1);
            return 0;
        }

        if (Hero_CheckGadgetReady())
            return 0;

        if (Hero_GetIdleAnim(0) == 0x54) {
            if (Hero_InitBodyState(HERO_STATE_IDLE, 0))
                Hero_TransAnim(
                    Hero_GetIdleAnim(0), 0, (float)FastScaleRoundInt(0x12));
            return 0;
        }

        if (animMode) {
            HeroState *hero = &Hero;
            float frame = hero->animFrame;
            int animation = 6;

            if (Hero_GetAnim(moby->updateId) == 4 && 3.0f < frame && frame < 16.0f)
                animation = 5;
            Hero_TransAnim(animation, 4, (float)FastScaleRoundInt(9));
        }
        break;
    }

    case HERO_STATE_SKID_TO_POS: {
        HeroState *hero = &Hero;

        hero->stateType = HERO_STATE_TYPE_RUN;
        hero->requestedCamType = 0;
        hero->storedNeutralSpeed = Hero_RelativeXYLength(&hero->resolvedVelocity.x);
        CopyVec4Inline(&hero->externalMomentum, &hero->resolvedVelocity);

        if (animMode) {
            int animation = 6;
            float frame = hero->animFrame;

            if (Hero_GetAnim(moby->updateId) == 4 && 3.0f < frame && frame < 16.0f)
                animation = 5;
            Hero_TransAnim(animation, 4, (float)FastScaleRoundInt(9));
        }
        break;
    }

    case HERO_STATE_CROUCH: {
        HeroState *hero = &Hero;

        hero->stateType = HERO_STATE_TYPE_CROUCH;
        hero->requestedCamType = 0;
        hero->storedNeutralSpeed = FastVec3Length(&hero->resolvedVelocity.x);

        if (frameTime * 7.0f < hero->storedNeutralSpeed)
            hero->storedNeutralSpeed = frameTime * 7.0f;

        if (hero->onSlipGround != 0 && hero->framesOffGround == 0) {
            Hero_InitBodyState(HERO_STATE_SLOPESLIDE, 1);
            return 0;
        }

        {
            HeroState *hero = &Hero;

            hero->randTimer.range = 0x68;
            CopyVec4Inline(&hero->externalMomentum, &hero->resolvedVelocity);
            ClampVec3Magnitude(&hero->externalMomentum, frameTime * 7.0f);

            if (frameTime * 3.5f < hero->forwardSpeed)
                Hero_PlaySound(0xC, 0);

            if (animMode) {
                if (hero->moby->updateId == Hero_GetIdleAnim(0))
                    Hero_TransAnim(0xD, 2, (float)FastScaleRoundInt(9));

                else
                    Hero_TransAnim(0xD, 2, (float)FastScaleRoundInt(0xE));
                Hero_SetNextAnimFrame(3, 0x12);
            }
        }
        break;
    }

    case HERO_STATE_ROCKET_STOMP: {
        HeroState *hero = &Hero;

        hero->stateType = HERO_STATE_TYPE_STOMP;
        hero->riseFallTargetFrame = 39.0f;
        hero->requestedCamType = 0x50;
        hero->pastApex = 0.0f;
        hero->riseFallLandFrames = 0;
        hero->riseFallGravity = frameTimeSq * 100.0f;

        if (animMode)
            Hero_TransAnim(0x2A, 0, (float)FastScaleRoundInt(6));
        break;
    }

    case HERO_STATE_LEDGE_GRAB: {
        HeroState *hero = &Hero;

        hero->stateType = HERO_STATE_TYPE_LEDGE;
        hero->requestedCamType = 0xD;
        hero->ledgeGravity = frameTimeSq * 24.0f;
        hero->smoothedAirZ = hero->position.z;

        if (hero->prevStateType == HERO_STATE_TYPE_JUMP) {
            hero->ledgeGravity = hero->jumpGravity;
            hero->smoothedAirZ = hero->smoothedGroundZ;
        }

        hero->itemSelectBlocked = 1;

        if (animMode) {
            if (frameTime * 3.5f < hero->flatSpeed)
                Hero_TransAnim(0x20, 0, (float)FastScaleRoundInt(9));

            else
                Hero_TransAnim(0x20, 1, (float)(FastScaleRoundInt(9) + 2));
        }
        break;
    }

    case HERO_STATE_LEDGE_IDLE: {
        HeroState *hero = &Hero;

        hero->stateType = HERO_STATE_TYPE_LEDGE;
        hero->requestedCamType = 0xD;
        hero->itemSelectBlocked = 1;
        hero->randTimer.range = 0x68;

        if (animMode)
            Hero_TransAnim(0x21, 0, (float)FastScaleRoundInt(6));
        break;
    }

    case HERO_STATE_LEDGE_TRAVERSE_LEFT: {
        HeroState *hero = &Hero;

        hero->stateType = HERO_STATE_TYPE_LEDGE;
        hero->requestedCamType = 0xD;
        hero->itemSelectBlocked = 1;

        if (animMode)
            Hero_TransAnim(0x24, 0, (float)FastScaleRoundInt(6));
        break;
    }

    case HERO_STATE_LEDGE_TRAVERSE_RIGHT: {
        HeroState *hero = &Hero;

        hero->stateType = HERO_STATE_TYPE_LEDGE;
        hero->requestedCamType = 0xD;
        hero->itemSelectBlocked = 1;

        if (animMode)
            Hero_TransAnim(0x25, 0, (float)FastScaleRoundInt(6));
        break;
    }

    case HERO_STATE_SLOPESLIDE: {
        HeroState *hero = &Hero;

        hero->stateType = HERO_STATE_TYPE_FALL;
        hero->requestedCamType = 0;
        CopyVec4Inline(&hero->velocity, &hero->resolvedVelocity);

        if (animMode)
            Hero_TransAnim(0xB, 0, (float)FastScaleRoundInt(0xC));
        break;
    }

    case HERO_STATE_FALL:

    case HERO_STATE_DEATH_FALL: {
        HeroState *hero = &Hero;

        hero->stateType = HERO_STATE_TYPE_FALL;
        hero->requestedCamType = 0;
        hero->fallStateGravity = frameTimeSq * 24.0f;
        hero->sticklessDecel = frameTimeSq * 7.0f;

        if (hero->state == HERO_STATE_DEATH_FALL) {
            if (hero->type == HERO_TYPE_RATCHET)
                hero->fallVoiceSlot = Hero_PlaySound(0x17, 0x20);
            hero->pivotRotXTarget =
                MB_randRangeSigned(frameTime * 3.1415927f, frameTime * 4.3633232f);
            hero->fatalFallTumbleTargetY =
                MB_randRangeSigned(frameTime * 3.1415927f, frameTime * 4.3633232f);
        }

        {
            HeroState *hero = &Hero;

            hero->randTimer.range = 0x68;
            hero->subState = 0;
            CopyVec4Inline(&hero->velocity, &hero->resolvedVelocity);

            if (animMode) {
                if (hero->type == HERO_TYPE_HOLOGUISE) {
                    Hero_TransAnim(6, 0, (float)FastScaleRoundInt(8));
                    return 1;
                }

                if (1.75f < hero->groundDist) {
                    Hero_TransAnim(0xB, 0, (float)FastScaleRoundInt(0xC));
                    hero->subState = 1;
                }


                else
                    Hero_TransAnim(0xA, 0, (float)FastScaleRoundInt(0xA));
            }
        }
        break;
    }

    case HERO_STATE_ROCKET_HOVER: {
        HeroState *hero = &Hero;
        int animation_timing_override = -2;

        hero->stateType = HERO_STATE_TYPE_RUN;
        hero->hoverLatch = 1;
        hero->randTimer.range = 0x68;
        hero->requestedCamType = 0;

        if (frameTime * 4.5f < hero->speedXY)
            Hero_ScaleMotion(frameTime * 4.5f / hero->speedXY);
        CopyVec4Inline(&hero->velocity, &hero->resolvedVelocity);

        if (animMode)
            Hero_TransAnim(0x13, 0, (float)animation_timing_override);
        break;
    }

    case HERO_STATE_LAND: {
        HeroState *hero = &Hero;
        int animation_timing_override = -2;

        hero->stateType = HERO_STATE_TYPE_LAND;
        hero->randTimer.range = 0x68;
        hero->requestedCamType = 0;

        if (frameTime * 4.5f < hero->speedXY)
            Hero_ScaleMotion(frameTime * 4.5f / hero->speedXY);
        CopyVec4Inline(&hero->velocity, &hero->displacement);

        if (animMode)
            Hero_TransAnim(0x13, 0, (float)animation_timing_override);
        break;
    }

    case HERO_STATE_JUMP:
    case HERO_STATE_RUN_JUMP:
    case HERO_STATE_HELI_PACK_FWD_JUMP:
    case HERO_STATE_FLIP_JUMP:
    case HERO_STATE_STORED_HEADING_JUMP:
    case HERO_STATE_ROCKET_JUMP:
    case HERO_STATE_DOUBLE_JUMP:
    case HERO_STATE_HELI_JUMP:
    case HERO_STATE_THRUSTER_PACK_FORWARD_JUMP:
    case HERO_STATE_WALL_JUMP:
    case HERO_STATE_WATER_JUMP:
    case HERO_STATE_LEDGE_JUMP:
    case HERO_STATE_GRIND_JUMP:
    case HERO_STATE_GRIND_SWITCH_JUMP:
    case HERO_STATE_TAKING_DAMAGE_LAVA:
    case HERO_STATE_CLANK_JUMP:
    case HERO_STATE_CLANK_EDGE_JUMP:
    case HERO_STATE_GIANT_CLANK_JUMP:

    case HERO_STATE_QUICKSAND_JUMP: {
        HeroState *hero = &Hero;

        if (hero->noJumps != 0) {
            hero->state = hero->prevState;
            hero->subState = savedSubState;
            hero->stateTimer = hero->prevStateTimer;
            return 0;
        }

        hero->stateType = HERO_STATE_TYPE_JUMP;

        if (state >= HERO_STATE_GRIND_JUMP &&
            state <= HERO_STATE_GRIND_SWITCH_JUMP) {
            hero->requestedCamType = 3;
        }


        else
            hero->requestedCamType = 0x50;
        CopyVec4Inline(&Hero.velocity, &Hero.resolvedVelocity);

        if (Hero.state != HERO_STATE_WATER_JUMP) {
            if (Hero.hotSpotWater != 0 && Hero.position.z < Hero.waterHeight + 0.5f)
                Hero_SpawnWaterSplash(3, 0x10, 0);
        }

        {
            HeroState *hero = &Hero;

            hero->smoothedGroundZ = hero->position.z;
            hero->jumpGravity = frameTimeSq * 29.7f;
            hero->velocityKeyIndex = -1;
            hero->airSpeedStepUp = frameTimeSq * 20.0f;
            hero->jumpDecel = frameTimeSq * 11.0f;
            hero->tookOffFromIce = hero->onIceGround;
            hero->pastJumpApex = 0;
            hero->dustHoverState = 0;
            hero->pendingJumpImpulse = 0.0f;
            hero->jumpImpulseTotal = 0.0f;
            hero->velocityKeysActive = 0;
            hero->fallStartDistance = 2.5f;
            hero->jumpBlockedAhead = 0;
            hero->canUseItemInJump = 0;
            hero->canChainHighJump = 0;
            hero->canDoubleJump = 0;
            hero->jumpMaxFrames = FastScaleRoundInt(0x50);
            hero->fallDelayFrames = FastScaleRoundInt(0x46);
            hero->packGlideDelay = 0;
            hero->jumpAnimRetimeScale = 0.5f;
            hero->airStickSpeed = frameTime * 5.7f;
            hero->airTurnRate = frameTime * 15.0098314f;
            hero->fallGravity = 0.0f;
            hero->wallJumped = 0;

            if (hero->state == HERO_STATE_JUMP) {
                hero->jumpHeight = 1.47f;
                hero->takeoffFrame = FastScaleRoundInt(5);
                hero->airCapsuleBottom = 0.6f;
                hero->apexAnimFrame = 18.0f;
                hero->targetAnimFrame = 30.0f;
                hero->jumpLandAnimFrame = 12.0f;
                hero->jumpHeightTarget = 2.62f;
                hero->jumpHeightStart = 1.47f;
                hero->jumpRampFrames = FastScaleRoundInt(0xF);
                hero->canUseItemInJump = 1;
                hero->canChainHighJump = 1;
                hero->canDoubleJump = 1;
                hero->fallGravity = hero->jumpGravity * 1.17f;
            }


            else if (hero->state == HERO_STATE_WATER_JUMP) {
                hero->jumpHeight = 0.1f;
                hero->takeoffFrame = FastScaleRoundInt(2);
                hero->airCapsuleBottom = 0.6f;
                hero->apexAnimFrame = 18.0f;
                hero->targetAnimFrame = 28.0f;
                hero->jumpLandAnimFrame = 14.0f;
                hero->jumpHeightTarget = 0.2f;
                hero->jumpHeightStart = 0.1f;
                hero->jumpRampFrames = FastScaleRoundInt(0xA);

                if (hero->waterDepth < 1.25f) {
                    hero->takeoffFrame = FastScaleRoundInt(0xF);
                    hero->jumpHeightStart = 1.95f;
                    hero->jumpHeightTarget = 1.98f;
                    hero->jumpHeight = 1.95f;
                }


                else {
                    Hero_ToHeroRelative(&hero->velocity, &hero->velocity, 0.0f);
                    hero->velocityKeysActive = 1;
                    hero->velocityKeysStartFrame = FastScaleRoundInt(2);
                    hero->velocityKeysEndFrame =
                        FastScaleRoundInt(0x23) + hero->velocityKeysStartFrame;
                    hero->keyedMoveTargetFrame = 0.0f;
                    hero->unk3DC = 18.0f;
                    hero->keyedAnimTargetFrame = FastScaleRoundInt(0x28);
                    hero->velocityKeys = HeroWaterJumpKeys;
                }

                {
                    HeroState *hero = &Hero;

                    hero->itemSelectBlocked = 1;
                }
            }


            else if (hero->state == HERO_STATE_RUN_JUMP) {
                hero->jumpHeight = 1.0f;
                hero->takeoffFrame = FastScaleRoundInt(5);
                hero->airCapsuleBottom = 0.6f;
                hero->apexAnimFrame = 18.0f;
                hero->targetAnimFrame = 29.0f;
                hero->jumpLandAnimFrame = 11.0f;
                hero->jumpHeightTarget = 2.7f;
                hero->jumpHeightStart = 1.0f;
                hero->jumpRampFrames = FastScaleRoundInt(0xF);
                hero->airStickSpeed = frameTime * 5.7f;
                hero->canUseItemInJump = 1;
                hero->canChainHighJump = 1;
                hero->canDoubleJump = 1;
            }


            else if (hero->state == HERO_STATE_HELI_PACK_FWD_JUMP) {
                hero->jumpHeight = 1.9f;
                hero->takeoffFrame = FastScaleRoundInt(5);
                hero->airCapsuleBottom = 0.6f;
                hero->apexAnimFrame = 18.0f;
                hero->targetAnimFrame = 29.0f;
                hero->jumpLandAnimFrame = 10.0f;
                hero->jumpHeightTarget = 1.95f;
                hero->jumpHeightStart = 1.9f;
                hero->jumpRampFrames = FastScaleRoundInt(0xE);
                hero->canChainHighJump = 1;
                hero->jumpGravity = frameTimeSq * 11.0f;
                hero->jumpMaxFrames = FastScaleRoundInt(0x78);
                hero->fallDelayFrames = FastScaleRoundInt(0x5A);
                hero->packGlideDelay = FastScaleRoundInt(0x46);
            }


            else if (hero->state == HERO_STATE_THRUSTER_PACK_FORWARD_JUMP) {
                MotionBlur *trail = &hero->trail;

                hero->jumpHeight = 1.5f;
                hero->takeoffFrame = FastScaleRoundInt(5);
                hero->airCapsuleBottom = 0.8f;
                hero->apexAnimFrame = 18.0f;
                hero->targetAnimFrame = 30.0f;
                hero->jumpLandAnimFrame = 11.0f;
                hero->jumpHeightTarget = 1.55f;
                hero->jumpHeightStart = 1.5f;
                hero->jumpRampFrames = FastScaleRoundInt(1);
                hero->jumpHeight = 0.4f;
                hero->jumpHeightStart = 0.4f;
                hero->jumpHeightTarget = 0.9f;
                CreateMotionBlur(hero->moby, trail);
                AddMotionBlurElem(trail, 0x28, 2);
                AddMotionBlurElem(trail, 0x14, 4);
                AddMotionBlurElem(trail, 0xA, 6);
                hero->canChainHighJump = 1;
                hero->longJumpSpeed = frameTime * 11.5f;

                if (1.4f < hero->groundDist)
                    hero->longJumpSpeed = frameTime * 5.7f;
                hero->jumpGravity = frameTimeSq * 8.5f;
                hero->airSpeedStepUp = frameTimeSq * 44.0f;
                hero->jumpDecel = frameTimeSq * 50.0f;
            }


            else if (hero->state == HERO_STATE_LEDGE_JUMP) {
                hero->jumpHeight = 2.0f;
                hero->takeoffFrame = FastScaleRoundInt(0xA);
                hero->airCapsuleBottom = 0.85f;
                hero->apexAnimFrame = 20.0f;
                hero->targetAnimFrame = 29.0f;
                hero->jumpLandAnimFrame = 19.0f;
                hero->jumpHeightTarget = 2.05f;
                hero->jumpHeightStart = 2.0f;
                hero->jumpRampFrames = FastScaleRoundInt(1);
                hero->jumpAnimRetimeScale = 1.0f;
                hero->jumpGravity = frameTimeSq * 25.0f;
                hero->ledgeJumpSpeed = 0.0f;
                hero->itemSelectBlocked = 1;
                hero->canChainHighJump = 1;
            }


            else if (hero->state == HERO_STATE_WALL_JUMP) {
                hero->jumpHeight = 3.3f;
                hero->takeoffFrame = FastScaleRoundInt(9);
                hero->airCapsuleBottom = 0.6f;
                hero->apexAnimFrame = 12.0f;
                hero->targetAnimFrame = 20.0f;
                hero->jumpLandAnimFrame = 10.0f;
                hero->jumpHeightTarget = 3.35f;
                hero->jumpHeightStart = 3.3f;
                hero->jumpRampFrames = FastScaleRoundInt(0xC);
                hero->fallDelayFrames = FastScaleRoundInt(0x50);
                hero->jumpGravity = frameTimeSq * 29.0f;
                CopyVec4Inline(&hero->wallJumpNormal, &hero->wallHitNormal);
                hero->wallJumped = 1;
                hero->itemSelectBlocked = 1;
                hero->canUseItemInJump = 1;
            }


            else if (hero->state == HERO_STATE_ROCKET_JUMP) {
                MotionBlur *trail = &hero->trail;

                hero->jumpHeight = 0.1f;
                hero->takeoffFrame = FastScaleRoundInt(9);
                hero->airCapsuleBottom = 0.6f;
                hero->apexAnimFrame = 26.0f;
                hero->targetAnimFrame = 38.0f;
                hero->jumpLandAnimFrame = 18.0f;
                hero->jumpHeightTarget = 0.2f;
                hero->jumpHeightStart = 0.1f;
                hero->jumpRampFrames = FastScaleRoundInt(0xE);
                hero->fallStartDistance = 4.5f;
                hero->jumpMaxFrames = FastScaleRoundInt(0x78);
                hero->airStickSpeed = frameTime * 1.9f;
                CreateMotionBlur(hero->moby, trail);
                AddMotionBlurElem(trail, 0x28, 3);
                AddMotionBlurElem(trail, 0x14, 5);
                hero->velocityKeysActive = 1;
                hero->velocityKeysStartFrame = FastScaleRoundInt(9);
                hero->velocityKeysEndFrame = FastScaleRoundInt(0x23) + hero->velocityKeysStartFrame;
                hero->unk3DC = 26.0f;
                hero->keyedMoveTargetFrame = 0.0f;
                hero->keyedAnimTargetFrame = FastScaleRoundInt(0x2D);
                hero->velocityKeys = HeroTrailJumpKeys;
                hero->canChainHighJump = 1;
            }


            else if (hero->state == HERO_STATE_HELI_JUMP) {
                hero->jumpHeight = 1.9f;
                hero->takeoffFrame = FastScaleRoundInt(9);
                hero->airCapsuleBottom = 0.6f;
                hero->apexAnimFrame = 50.0f;
                hero->targetAnimFrame = 64.0f;
                hero->jumpLandAnimFrame = 28.0f;
                hero->jumpHeightTarget = 1.95f;
                hero->jumpHeightStart = 1.9f;
                hero->jumpRampFrames = FastScaleRoundInt(5);
                hero->fallStartDistance = 4.5f;
                hero->jumpMaxFrames = FastScaleRoundInt(0x82);
                hero->airStickSpeed = frameTime * 3.3f;
                hero->packGlideDelay = FastScaleRoundInt(0x55);
                hero->noLedge = FastScaleRoundInt(0x46);
                hero->velocityKeysActive = 1;

                if (videoModePal != 0)
                    hero->velocityKeysStartFrame = FastScaleRoundInt(0x22);

                else
                    hero->velocityKeysStartFrame = FastScaleRoundInt(0x23);

                {
                    HeroState *hero = &Hero;

                    hero->velocityKeysEndFrame =
                        FastScaleRoundInt(0x24) + hero->velocityKeysStartFrame;
                    hero->keyedMoveTargetFrame = 29.0f;
                    hero->unk3DC = 50.0f;
                    hero->keyedAnimTargetFrame = FastScaleRoundInt(0x56);
                    hero->velocityKeys = HeroPackJumpVelocityKeys;
                    hero->canChainHighJump = 1;
                }
            }


            else if (hero->state == HERO_STATE_DOUBLE_JUMP) {
                float jumpHeightBase = 0.7f;

                if (hero->groundDist < 2.0f)
                    jumpHeightBase = (2.5f - hero->groundDist) * 0.5f + 0.7f;
                hero->airCapsuleBottom = 0.6f;
                hero->apexAnimFrame = 32.0f;
                hero->targetAnimFrame = 43.0f;
                hero->jumpLandAnimFrame = 19.0f;
                hero->jumpHeightTarget = jumpHeightBase + 0.05f;
                hero->jumpHeight = jumpHeightBase;
                hero->jumpHeightStart = jumpHeightBase;
                hero->takeoffFrame = -1;
                hero->jumpRampFrames = FastScaleRoundInt(0xE);
                hero->jumpAnimRetimeScale = 1.0f;
                hero->airStickSpeed = frameTime * 3.5f;
                hero->packGlideDelay = FastScaleRoundInt(0x1E);
            }


            else if (hero->state == HERO_STATE_FLIP_JUMP) {
                hero->jumpHeight = 3.2f;
                hero->takeoffFrame = FastScaleRoundInt(5);
                hero->airCapsuleBottom = 0.6f;
                hero->apexAnimFrame = 18.0f;
                hero->targetAnimFrame = 31.0f;
                hero->jumpLandAnimFrame = 24.0f;
                hero->jumpHeightTarget = 3.25f;
                hero->jumpHeightStart = 3.2f;
                hero->jumpRampFrames = FastScaleRoundInt(0xE);
                hero->fallStartDistance = 4.5f;
                hero->fallDelayFrames = FastScaleRoundInt(0x32);
                hero->jumpAnimRetimeScale = 1.0f;
                hero->takeoffYaw = Hero_GetRotationHistory(FastScaleRoundInt(0xA));
                hero->jumpStickDirection = Hero_GetSnapJumpDir();
                hero->highJumpDriftYaw = hero->idealRotZ;

                if (frameTime * 1.5f < hero->flatSpeed)
                    hero->airTargetSpeed = hero->flatSpeed;

                else
                    hero->airTargetSpeed = 0.0f;

                {
                    HeroState *hero = &Hero;

                    hero->highJumpDriftSpeed = 0;
                    hero->canUseItemInJump = 1;
                    hero->canChainHighJump = 1;
                }
            }
        }

        {
            HeroState *hero = &Hero;

            if (hero->fallStartDistance == 0.0f)
                hero->fallStartDistance = hero->jumpHeight * 1.5f;

            if (animMode) {
                int currentState = hero->state;

                if (currentState == HERO_STATE_JUMP)
                    Hero_TransAnim(7, 0, (float)FastScaleRoundInt(5));

                else if (currentState == HERO_STATE_WATER_JUMP)
                    Hero_TransAnim(0x72, 1, -1.0f);

                else if (currentState == HERO_STATE_RUN_JUMP) {
                    int animation = 8;
                    int frameIndex = FastFloatToInt(hero->animFrame);

                    if (Hero_GetAnim(moby->updateId) == 4)
                        animation = HeroRunJumpAnims[frameIndex];
                    Hero_TransAnim(animation, 0, (float)FastScaleRoundInt(5));
                }


                else if (currentState == HERO_STATE_HELI_PACK_FWD_JUMP)
                    Hero_TransAnim(0x12, 0, (float)FastScaleRoundInt(5));

                else if (currentState == HERO_STATE_THRUSTER_PACK_FORWARD_JUMP) {
                    if (hero->prevStateType == HERO_STATE_TYPE_JUMP ||
                        (hero->prevState == HERO_STATE_CROUCH && FastScaleRoundInt(7) > hero->stateTimer)) {
                        Hero_TransAnim(0x26, 0, (float)FastScaleRoundInt(8));
                        hero->takeoffFrame += FastScaleRoundInt(3);
                    }


                    else
                        Hero_TransAnim(0x26, 0, (float)FastScaleRoundInt(5));
                }


                else if (currentState == HERO_STATE_LEDGE_JUMP)
                    Hero_TransAnim(0x22, 0, (float)FastScaleRoundInt(4));

                else if (currentState == HERO_STATE_WALL_JUMP)
                    Hero_TransAnim(0x23, 2, (float)FastScaleRoundInt(7));

                else if (currentState == HERO_STATE_ROCKET_JUMP)
                    Hero_TransAnim(0x11, 0, (float)FastScaleRoundInt(5));

                else if (currentState == HERO_STATE_DOUBLE_JUMP) {
                    Hero_TransAnim(0x16, 3, (float)FastScaleRoundInt(7));
                    hero->animSpeed = transStepScale * 0.8f;
                }


                else if (currentState == HERO_STATE_HELI_JUMP)
                    Hero_TransAnim(0x15, 0, (float)FastScaleRoundInt(5));

                else if (currentState == HERO_STATE_FLIP_JUMP) {
                    int animation;

                    if (hero->jumpStickDirection == 2)
                        hero->jumpStickDirection = 0;
                    animation = hero->jumpStickDirection + 0x1C;

                    if (optMirrorAnim != 0) {
                        if (animation == 0x1C)
                            animation = 0x1D;

                        else if (animation == 0x1D)
                            animation = 0x1C;
                    }

                    {
                        HeroState *hero = &Hero;

                        if (hero->prevStateType == HERO_STATE_TYPE_JUMP) {
                            Hero_TransAnim(animation, 1, (float)FastScaleRoundInt(4));
                            hero->takeoffFrame = FastScaleRoundInt(1);
                        }


                        else
                            Hero_TransAnim(animation, 0, (float)FastScaleRoundInt(5));
                    }
                }
            }
        }
        break;
    }

    case HERO_STATE_COMBO_ATTACK:
    case HERO_STATE_JUMP_ATTACK:
    case HERO_STATE_THROW_ATTACK:
    case HERO_STATE_WALLOPER_ATTACK:
    case HERO_STATE_THROWING_ITEM:

    case HERO_STATE_CLANK_ATTACK: {
        HeroState *hero = &Hero;

        hero->stateType = HERO_STATE_TYPE_ATTACK;
        hero->speedScale = 1.0f;
        hero->requestedCamType = 0;
        hero->headingLocked = 0;
        hero->meleeTarget = 0;
        hero->meleeHit = 0;

        switch (hero->state) {
        case HERO_STATE_JUMP_ATTACK: {
            UsageStat *stats = ActionUsageStats;
            HeroState *hero;

            if (stats[USAGE_HYPER_STRIKE].count <= 0xFFFE)
                stats[USAGE_HYPER_STRIKE].count = stats[USAGE_HYPER_STRIKE].count + 1;

            if (FastScaleRoundInt(TotalPlayTime) / 600 > stats[USAGE_HYPER_STRIKE].latestTimeBucket)
                stats[USAGE_HYPER_STRIKE].latestTimeBucket = FastScaleRoundInt(TotalPlayTime) / 600;
            stats[USAGE_HYPER_STRIKE].levelMask =
                stats[USAGE_HYPER_STRIKE].levelMask | (1 << Level) | USAGE_STAT_USED;
            hero = &Hero;
            hero->requestedCamType = 0x50;
            hero->attackRecord = 4;
            hero->savedItem[0] = 0;
            Hero_UpdateAutoTargetAim(8.0f, 1.0471976f, -1.0f);
            hero->slamDescending = 0.0f;
            hero->items[0].timer = 0xA;

            if (animMode) {
                MobyInstance *gadget;
                int blendFrames = FastScaleRoundInt(0xB);

                if (hero->prevState == HERO_STATE_FLIP_JUMP && FastScaleRoundInt(0x2A) > hero->prevStateTimer)
                    blendFrames = FastScaleRoundInt(0x11);
                Hero_TransAnim(0x2B, 4, (float)blendFrames);
                gadget = Hero_HandGadgetID(0);

                if (Hero_isMobyWrench(gadget))
                    MB_SetAnimation(gadget, 0xA, 4, blendFrames + 2);
            }
            break;
        }

        case HERO_STATE_THROW_ATTACK: {
            UsageStat *stats = ActionUsageStats;
            UsageStat *itemUsage;
            HeroState *hero;

            if (stats[USAGE_WRENCH_THROW].count <= 0xFFFE)
                stats[USAGE_WRENCH_THROW].count = stats[USAGE_WRENCH_THROW].count + 1;

            if (FastScaleRoundInt(TotalPlayTime) / 600 > stats[USAGE_WRENCH_THROW].latestTimeBucket)
                stats[USAGE_WRENCH_THROW].latestTimeBucket = FastScaleRoundInt(TotalPlayTime) / 600;
            stats[USAGE_WRENCH_THROW].levelMask =
                stats[USAGE_WRENCH_THROW].levelMask | (1 << Level) | USAGE_STAT_USED;
            itemUsage = UsageStats;

            if (itemUsage[ITEM_COUNT].count <= 0xFFFE)
                itemUsage[ITEM_COUNT].count = itemUsage[ITEM_COUNT].count + 1;

            if (FastScaleRoundInt(TotalPlayTime) / 600 >
                itemUsage[ITEM_COUNT].latestTimeBucket) {
                itemUsage[ITEM_COUNT].latestTimeBucket = FastScaleRoundInt(TotalPlayTime) / 600;
            }

            itemUsage[ITEM_COUNT].levelMask =
                itemUsage[ITEM_COUNT].levelMask | (1 << Level) | USAGE_STAT_USED;
            hero = &Hero;
            hero->attackRecord = 3;
            hero->savedItem[0] = 0;
            Hero_UpdateAutoTargetAim(14.0f, 0.5235988f, -1.0f);
            hero->crouchSwingToggle = hero->crouchSwingToggle == 0;

            if (animMode) {
                int blendFrames = FastScaleRoundInt(0xA);

                if (hero->moby->animationId == 0x1A)
                    blendFrames = FastScaleRoundInt(3);

                if (hero->prevState == HERO_STATE_LOOK)
                    blendFrames = FastScaleRoundInt(0x11);
                Hero_TransAnim(0x1A, 0, (float)blendFrames);
                Hero_SetNextAnimFrame(6, 0x15);
            }
            break;
        }

        case HERO_STATE_WALLOPER_ATTACK: {
            HeroState *hero = &Hero;

            if (hero->items[0].moby == 0)
                break;
            if (animMode) {
                Hero_TransAnim(0x67, 4, -1.0f);
                MB_SetAnimation(hero->items[0].moby, 3, 4, -1);
            }

            Hero_UpdateAutoTargetAim(11.0f, 0.87266463f, -1.0f);
            break;
        }

        case HERO_STATE_COMBO_ATTACK: {
            UsageStat *stats = UsageStats;
            HeroState *hero;
            HeroAttackRow *attack;
            int comboKind;

            if (stats[ITEM_WRENCH].count <= 0xFFFE)
                stats[ITEM_WRENCH].count = stats[ITEM_WRENCH].count + 1;

            if (FastScaleRoundInt(TotalPlayTime) / 600 > stats[ITEM_WRENCH].latestTimeBucket)
                stats[ITEM_WRENCH].latestTimeBucket = FastScaleRoundInt(TotalPlayTime) / 600;
            hero = &Hero;
            stats[ITEM_WRENCH].levelMask =
                stats[ITEM_WRENCH].levelMask | (1 << Level) | USAGE_STAT_USED;
            attack = &HeroAttackTable[hero->attackRecord];
            hero->savedItem[0] = 0;
            comboKind = 0;

            if (hero->prevStateType == HERO_STATE_TYPE_ATTACK && attack->comboEnds == 0 &&
                hero->animFrame < (float)attack->chainBeforeFrame) {
                comboKind = (attack->kind + 1) % 3;
            }

            {
                HeroState *hero = &Hero;

                hero->attackRecord = comboKind;
            }

            Hero_UpdateAutoTargetAim(5.0f, 0.7853982f, 0.7853982f);

            if (animMode) {
                MobyInstance *gadget;
                int animOffset = 0;
                int blendFrames;

                if (comboKind == 0)
                    blendFrames = FastScaleRoundInt(5);

                else if (comboKind == 1) {
                    animOffset = 2;
                    blendFrames = FastScaleRoundInt(7);
                }


                else {
                    animOffset = 4;
                    blendFrames = FastScaleRoundInt(7);
                }

                {
                    HeroState *hero = &Hero;

                    if (hero->headingLocked != 0 && comboKind < 2)
                        blendFrames += FastFloatToInt(FastDiffRots(
                                                       hero->attackTargetYaw, hero->rotation.z) *
                                                   1.5f);
                }

                animOffset = animOffset / 2;
                Hero_TransAnim(comboKind + 0x17, animOffset, (float)blendFrames);
                gadget = Hero_HandGadgetID(0);

                if (Hero_isMobyWrench(gadget))
                    MB_SetAnimation(gadget, comboKind + 3, animOffset, blendFrames);
            }
            break;
        }

        case HERO_STATE_THROWING_ITEM: {
            HeroState *hero;

            if (animMode)
                Hero_TransAnim(0x2C, 7, (float)FastScaleRoundInt(9));
            hero = &Hero;

            if (hero->items[0].itemId == 0xA && hero->throwTarget != 0) {
                hero->headingLocked = 1;
                hero->attackTargetYaw =
                    FastArcTan(hero->throwTarget->pos.x - hero->position.x,
                               hero->throwTarget->pos.y - hero->position.y);
            }
            break;
        }
        }
        break;
    }

    case HERO_STATE_UNK_BONK: {
        HeroState *hero = &Hero;

        hero->stateType = HERO_STATE_TYPE_BOUNCE;
        hero->requestedCamType = 0;
        hero->storedNeutralSpeed = frameTime * 9.0f;

        if (animMode) {
            MobyInstance *gadget;
            HeroAttackRow *attack = &HeroAttackTable[hero->attackRecord];
            int comboKind = attack->kind;
            int blendFrames;

            if (attack->comboEnds == 1)
                comboKind = 2;
            blendFrames = FastScaleRoundInt(5);
            Hero_TransAnim(comboKind + 0x27, 5, (float)blendFrames);
            gadget = Hero_HandGadgetID(0);

            if (Hero_isMobyWrench(gadget))
                MB_SetAnimation(gadget, comboKind + 7, 5, blendFrames);
        }
        break;
    }

    case HERO_STATE_JUMP_BOUNCE: {
        HeroState *hero = &Hero;

        hero->stateType = HERO_STATE_TYPE_BOUNCE;
        hero->requestedCamType = 0;
        hero->pushbackYaw = FastAddRots(hero->rotation.z, 3.1415927f);
        hero->storedNeutralSpeed = frameTime * 9.0f;

        if (animMode)
            Hero_TransAnim(0x29, 5, (float)FastScaleRoundInt(8));
        break;
    }

    case HERO_STATE_GET_HIT: {
        HeroState *hero = &Hero;
        COLL_DAM_OUT *damage;

        hero->stateType = HERO_STATE_TYPE_HURT;
        hero->requestedCamType = 0;
        Hero_ScaleMotion(0.5f);
        hero->screenFlashRed = FastScaleRoundInt(0x2D);
        CopyVec4Inline(&hero->velocity, &hero->resolvedVelocity);
        ClampVec3Magnitude(&hero->velocity, frameTime * 7.0f);
        damage = MB_FindSlotByMask(hero->moby, 1, 0);

        if (damage != 0)
            TakeDamage(FastFloatToInt(damage->damageHp));

        else
            TakeDamage(1);

        {
            HeroState *hero = &Hero;

            hero->postHitInvinc = FastScaleRoundInt(0x4D);

            if (animMode) {
                Hero_TransAnim(0x10, 3, -3.0f);
                hero->moby->animationBlend =
                    HeroAnimBlendCurves[hero->animBlendCurve][(hero->animBlendStep)++];
            }
        }
        break;
    }

    case HERO_STATE_HOLOGUISE_STANDING: {
        HeroState *hero = &Hero;

        hero->stateType = HERO_STATE_TYPE_IDLE;
        hero->requestedCamType = 0;

        if (animMode)
            Hero_TransAnim(0, 0, (float)FastScaleRoundInt(0xE));
        break;
    }

    case HERO_STATE_HOLOGUISE_WAVE: {
        HeroState *hero = &Hero;

        hero->stateType = HERO_STATE_TYPE_IDLE;
        hero->requestedCamType = 0;

        if (animMode) {
            Hero_TransAnim(4, 0, (float)FastScaleRoundInt(7));
            Hero_SetNextAnimFrame(0xE, 0x22);
        }
        break;
    }

    case HERO_STATE_HOLOGUISE_SLIP: {
        HeroState *hero = &Hero;

        hero->stateType = HERO_STATE_TYPE_FALL;
        hero->requestedCamType = 0;
        CopyVec4Inline(&hero->velocity, &hero->resolvedVelocity);

        if (animMode)
            Hero_TransAnim(6, 0, (float)FastScaleRoundInt(0xC));
        break;
    }

    case HERO_STATE_HOLOGUISE_FALLING: {
        HeroState *hero = &Hero;

        hero->stateType = HERO_STATE_TYPE_FALL;
        hero->requestedCamType = 0;
        hero->fallStateGravity = frameTimeSq * 24.0f;
        hero->sticklessDecel = frameTimeSq * 7.0f;
        CopyVec4Inline(&hero->velocity, &hero->resolvedVelocity);

        if (animMode)
            Hero_TransAnim(6, 0, (float)FastScaleRoundInt(7));
        break;
    }

    case HERO_STATE_HOLOGUISE_WALKING: {
        HeroState *hero = &Hero;

        hero->stateType = HERO_STATE_TYPE_RUN;
        hero->requestedCamType = 0;

        {
            float planarSpeed = FastVec3Length(&hero->resolvedVelocity.x);

            hero->storedNeutralSpeed = planarSpeed;

            if (frameTime * 1.5f < planarSpeed)
                hero->storedNeutralSpeed = frameTime * 1.5f;
            hero->moveAlongStick = 0;

            if (animMode)
                Hero_TransAnim(1, 0, (float)FastScaleRoundInt(8));
        }
        break;
    }

    case HERO_STATE_HOLOGUISE_DYING: {
        HeroState *hero = &Hero;

        hero->stateType = HERO_STATE_TYPE_DYING;
        hero->requestedCamType = 0;
        CopyVec4Inline(&hero->externalMomentum, &hero->resolvedVelocity);

        if (animMode)
            Hero_TransAnim(3, 0, (float)FastScaleRoundInt(0xC));
        break;
    }

    case HERO_STATE_HOLOGUISE_DAMAGE: {
        HeroState *hero = &Hero;

        hero->stateType = HERO_STATE_TYPE_HURT;
        hero->requestedCamType = 0;
        Hero_ScaleMotion(0.5f);
        CopyVec4Inline(&hero->velocity, &hero->resolvedVelocity);
        ClampVec3Magnitude(&hero->velocity, frameTime * 5.0f);
        TakeDamage(1);
        hero->postHitInvinc = FastScaleRoundInt(0x4D);

        if (animMode) {
            Hero_TransAnim(2, 3, -3.0f);
            hero->moby->animationBlend =
                HeroAnimBlendCurves[hero->animBlendCurve][(hero->animBlendStep)++];
        }
        break;
    }

    case HERO_STATE_GRINDRAIL_DAMAGE: {
        HeroState *hero = &Hero;

        hero->stateType = HERO_STATE_TYPE_GRIND;
        hero->requestedCamType = 0;

        if (hero->railOffFrames == 0)
            TakeDamage(1);
        hero->postHitInvinc = FastScaleRoundInt(0x4D);
        hero->grindRecoverySpeed = frameTime * 2.5f;

        if (frameTime * 2.5f < hero->grindBaseSpeed)
            hero->grindBaseSpeed = frameTime * 2.5f;
        hero->grindSpeedBoost = 0;
        FastVecZero(&hero->velocity);
        FastVecZero(&hero->displacement);
        hero->velocity.z = frameTime * 10.0f;

        if (animMode)
            Hero_TransAnim(0x10, 2, -3.0f);
        break;
    }

    case HERO_STATE_VISIBOMB: {
        HeroState *hero = &Hero;

        hero->stateType = HERO_STATE_TYPE_BUSY;
        hero->itemUseLocked = 1;
        hero->requestedCamType = 0;
        Hero_TransAnim(Hero_GetIdleAnim(0), 0, (float)FastScaleRoundInt(0xA));
        break;
    }

    case HERO_STATE_WEAPON_FIRST_PERSON_VIEW: {
        HeroState *hero = &Hero;

        hero->requestedCamType = 0x51;
        hero->stateType = HERO_STATE_TYPE_IDLE;

        if (Hero_GetAnim(hero->moby->animationId) !=
            Hero_GetIdleAnim(1)) {
            Hero_TransAnim(Hero_GetIdleAnim(1), 0, (float)FastScaleRoundInt(5));
        }
        break;
    }

    case HERO_STATE_ACTIVATE_SONIC_SUMMONER_MOUSE: {
        HeroState *hero = &Hero;

        hero->stateType = HERO_STATE_TYPE_BUSY;
        hero->requestedCamType = 0;
        Hero_TransAnim(Hero_GetIdleAnim(0), 0, (float)FastScaleRoundInt(0xA));
        break;
    }

    case HERO_STATE_CUT_SCENE: {
        HeroState *hero = &Hero;

        hero->stateType = HERO_STATE_TYPE_BUSY;
        hero->itemUseLocked = 1;
        hero->requestedCamType = 0;
        Hero_PlayBackpackIdle();
        Hero_TransAnim(Hero_GetIdleAnim(0), 0, (float)FastScaleRoundInt(0xA));
        break;
    }

    case HERO_STATE_IDLE_ANIMATION_LONG_BLEND_ENTRY: {
        HeroState *hero = &Hero;

        hero->stateType = HERO_STATE_TYPE_ITEM_RELEASE_WAIT;
        hero->requestedCamType = 0;
        Hero_TransAnim(Hero_GetIdleAnim(0), 0, (float)FastScaleRoundInt(0xA));
        break;
    }

    case HERO_STATE_TURRET_PLANE_UI: {
        HeroState *hero = &Hero;

        hero->stateType = HERO_STATE_TYPE_BUSY;
        hero->requestedCamType = 0;
        hero->itemSelectBlocked = 1;
        hero->tiltDisabled = 1;
        hero->itemUseLocked = 1;

        if (animMode)
            Hero_TransAnim(Hero_GetIdleAnim(0), 0, -1.0f);
        break;
    }

    case HERO_STATE_CLEAR_VELOCITY: {
        HeroState *hero = &Hero;

        hero->stateType = HERO_STATE_TYPE_BUSY;
        hero->requestedCamType = 0;
        hero->itemSelectBlocked = 1;
        hero->itemUseLocked = 1;
        FastVecZero(&hero->velocity);

        if (animMode)
            Hero_TransAnim(0xB, 0, -1.0f);
        break;
    }

    case HERO_STATE_BOLT_CRANK: {
        HeroState *hero = &Hero;
        MobyInstance *gadget;
        int blendFrames;

        hero->stateType = HERO_STATE_TYPE_BUSY;
        hero->itemSelectBlocked = 1;
        hero->tiltDisabled = 1;
        blendFrames = FastScaleRoundInt(8);
        Hero_TransAnim(0x44, 2, (float)blendFrames);
        gadget = hero->items[0].moby;

        if (Hero_isMobyWrench(gadget))
            MB_SetAnimation(gadget, 0xB, 2, blendFrames + FastScaleRoundInt(5));
        break;
    }

    case HERO_STATE_NPC:

    case HERO_STATE_CUSTOM_UI: {
        HeroState *hero = &Hero;

        hero->stateType = HERO_STATE_TYPE_NPC;
        hero->itemUseLocked = 1;
        Hero_PlayBackpackIdle();

        if (animMode)
            Hero_TransAnim(Hero_GetIdleAnim(0), 0, -1.0f);
        break;
    }
    }

    if (hadItemSelectBlocked != 0) {
        HeroState *hero = &Hero;

        if (hero->itemSelectBlocked == 0)
            hero->restoreItem[0] = 1;
    }

    {
        HeroState *hero = &Hero;

        if (hero->onMagnerail == 0 && hero->items[1].itemId == 0x1C && hero->savedItem[1] != 0)
            hero->restoreItem[1] = 1;
    }

    {
        HeroState *hero = &Hero;

        if (hero->stateType != HERO_STATE_TYPE_GRIND && hero->items[1].itemId == 0x1D &&
            hero->savedItem[1] != 0) {
            hero->restoreItem[1] = 1;
        }
    }

    if (Hero_IsInSpecialMovementState() == 0) {
        HeroState *hero = &Hero;

        if (hero->items[1].itemId == 0 && hero->savedItem[1] != 0)
            hero->restoreItem[1] = 1;
    }

    {
        HeroState *hero = &Hero;

        if (hero->stateType == HERO_STATE_TYPE_DYING) {
            Hero_PlayBackpackIdle();
            hero->itemUseLocked = 1;
        }

        if (hero->stateType != hero->prevStateType)
            Hero_KillLoopingSounds();
        hero->stateTimer = 0;
        hero->stepFrames = 0;

        if (hero->stateType != hero->prevStateType)
            hero->controlModeTimer = 0;
        hero->animSeqFrames = 0;
    }

    return 1;
}

void Hero_TransitionToDefault(void)
{
    switch (Hero.type) {
    case HERO_TYPE_RATCHET:
        Hero_InitBodyState(HERO_STATE_IDLE, 1);
        break;
    case HERO_TYPE_HOLOGUISE:
        Hero_InitBodyState(HERO_STATE_HOLOGUISE_STANDING, 1);
        break;
    }
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_IdleCycleFiringTransition);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_UnderwaterTransitions);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_SwimSurfTransition);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_SurfBob);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_GadgetTransitions);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_JumpCheckHeld);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_UpdateWalkAnim);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_CleanupAttachedMobys);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_GetSpecialIdle);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", func_00242194);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_JumpLandTransitions);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_CrouchJumpTransitions);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_ProbeCollAlongVelocity);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_CheckGadgetReady);

// Jump table of Hero_GadgetTransitions, kept as data until that function is decompiled.
extern const unsigned int HeroUpdateWeaponInputJumpTable[28] __attribute__((section(".rodata"), aligned(16))) = {
    0x00240FA0, 0x002417F8, 0x002415C8, 0x002417F8, 0x002417F8, 0x002417F8, 0x002417F8,
    0x002414B0, 0x002417F8, 0x002415C8, 0x0024173C, 0x002417F8, 0x002415C8, 0x002417D0,
    0x002417F8, 0x002417F8, 0x002415C8, 0x002415C8, 0x002417F8, 0x002417F8, 0x002417F8,
    0x002417F8, 0x002417F8, 0x002413CC, 0x0024145C, 0x00000000, 0x00000000, 0x00000000
};

extern float transStepScaleSq;
extern int QuickSwapDefaultItem;
extern int ItemSelectorDisabled;
extern float HeroYawReference[];
extern HeroIdleFidget HeroIdleFidgets[5];
extern GadgetModelEntry Gadgets[37];
extern HeroJumpSpeedTweaks HeroJumpSpeeds;

int Hero_HandleDamage(int damageMode);
int Hero_GadgetTransitions(void);
int Hero_SwimSurfTransition(void);
int Hero_UnderwaterTransitions(void);
int Hero_IdleCycleFiringTransition(void);
int FastDecTimer_220e78(int *timer);
int FastDecTimer_220ea8(short *timer);
int Hero_GetGadgetMoby(int slot);
int Hero_GetSpecialIdle(int *index);
float FastScaleBySpeed(float value);
void Hero_PlayBackpackIdleAnim(void);
int Hero_JumpCheckHeld(int a, int b);
void Hero_CleanupAttachedMobys(void);
int Hero_CheckLedgeAhead(Vec4 *position, float *yaw);
void Hero_PlayFootStep(int groundType, int whichFoot, int playSound);
void Hero_GetIdealThrustForWalk(void);
void Hero_JumpLandTransitions(void);
void Hero_TransitionToDefault(void);
float Hero_PredictLand(float a, float b, float c);
float Hero_GetAnimFrameBlend(float a, float b, float c, float d);
int Hero_CrouchJumpTransitions(void);
void Hero_SetNextAnimBlend(int frames);
int Hero_ProbeCollAlongVelocity(void);
void Hero_UpdateWalkAnim(void);
void sound_KillChannel(int channel);
void HandleHeroDeath(void);
float Hero_RelativeZComponent(Vec4 *vector);
void Hero_SetTiltWobbleParams(float a, float b, short c, unsigned char d, unsigned char e, unsigned char f);
float Hero_GetJumpPeak(Vec4 *position, Vec4 *velocity, int *steps, float step);
void Hero_HandleGadgetSwitching(int item);
float FastVec3DistLen(Vec4 *first, Vec4 *second);
float FastVec3Length(Vec4 *vector);
float FastAngleSinF(float angle);
float FastAngleCosF(float angle);
int PadRingBitsOn(int bits, int frames, int *frame);
int PadRingCoincidentBitsOn(int firstBits, int secondBits, int frames, int window);
float PadRingAng(int frames);
float MB_randRangeFloat(float low, float high);
int MB_randRange(int low, int high);


void Hero_Transitions(void)
{
    MobyInstance *moby;
    int previousStateType;
    int previousSubState;
    int previousAnimation;

    Vec4 ledgeProbePosition __attribute__((aligned(16)));
    Vec4 shimmyEntryProbePosition __attribute__((aligned(16)));
    int fidgetIndex;
    float ledgeHoldProbeYaw;
    float positiveShimmyProbeYaw;
    float negativeShimmyProbeYaw;
    float shimmyContinuationProbeYaw;
    int predictedSteps;
    int jumpPressAge;

    moby = Hero.moby;
    previousStateType = Hero.stateType;
    previousSubState = Hero.subState;
    previousAnimation = moby->animationId;

    if (Hero_HandleDamage(1) == 0) {
        if (Hero.health <= 0 && Hero.stateType != HERO_STATE_TYPE_DYING &&
            (Hero.state == HERO_STATE_IDLE || Hero.state == HERO_STATE_WALK)) {
            Hero_InitBodyState(HERO_STATE_DEATH, 1);
        }

        else if (Hero_GadgetTransitions() == 0 && Hero_SwimSurfTransition() == 0 &&
                 Hero_UnderwaterTransitions() == 0 && Hero_IdleCycleFiringTransition() == 0) {
            if ((padState.bitsOn & PAD_TRIANGLE) || (padState.hudBitsOn & PAD_TRIANGLE)) {
                if (Hero.items[0].switchLock != 2 && ItemSelectorDisabled == 0 &&
                    (Hero.itemUseLocked == 0 || Hero.type == HERO_TYPE_CLANK ||
                     Hero.allowQuickSelect != 0) &&
                    (Hero.itemSelectBlocked == 0 ||
                     Hero.type == HERO_TYPE_CLANK ||
                     Hero.allowQuickSelect != 0) &&
                    (Hero.type == HERO_TYPE_RATCHET || Hero.type == HERO_TYPE_HOLOGUISE)) {
                    int hudHandle;

                    if (Hero.quickSwapTapWindow != 0)
                        Hero.itemSelectorTimer = FastScaleRoundInt(0x1B);

                    else
                        Hero.itemSelectorTimer = FastScaleRoundInt(0xF);
                    RegisterHUDCallback(3, 0, QuickSelectHud_Init, UpdateQuickSelect, Draw_QuickSelectHud, 0,
                                        0);
                    hudHandle = Hero_RegisterHealthHud();
                    Hud_SetEntryMinValueById(hudHandle, FastScaleRoundInt(0xB4));
                    hudHandle = RegisterHUDCallback(2, 0x754E, Hud_DrawTexQuadUV_Fixed, BoltHud_Update,
                                                    Draw_BoltCountUI, &HeroBolts, 0x98967F);
                    Hud_SetEntryMinValueById(hudHandle, FastScaleRoundInt(0xB4));
                }
            }

            FastDecTimer_220ea8(&Hero.quickSwapTapTimer);
            FastDecTimer_220ea8(&Hero.quickSwapTapWindow);

            if (padState.bitsOn & PAD_TRIANGLE)
                Hero.quickSwapTapTimer = FastScaleRoundInt(0x14);

            if ((Hero.quickSwapTapTimer != 0 || Hero.quickSwapTapWindow != 0) &&
                (padState.digitalBitsOff & PAD_TRIANGLE)) {
                if (Hero.quickSwapTapWindow == 0)
                    Hero.quickSwapTapWindow = FastScaleRoundInt(0x14);

                else {
                    int quickSwapItem = QuickSwapDefaultItem;
                    int quickSwapTarget = quickSwapItem;
                    int currentItemId = Hero.items[0].itemId;

                    if (currentItemId == ITEM_WRENCH)
                        quickSwapTarget = EquippedItems[0];

                    if (quickSwapTarget != 0 &&
                        currentItemId != quickSwapItem) {
                        if (ActionUsageStats[31].count < 0xFFFF)
                            ActionUsageStats[31].count++;

                        if (FastScaleRoundInt(TotalPlayTime) / 600 >
                            ActionUsageStats[31].latestTimeBucket) {
                            ActionUsageStats[31].latestTimeBucket =
                                FastScaleRoundInt(TotalPlayTime) / 600;
                        }

                        ActionUsageStats[31].levelMask = ActionUsageStats[31].levelMask |
                                                          (1 << Level) | 0x80000000;
                        Hero.pendingItem[0] = quickSwapTarget;
                        Hero.quickSwapTapTimer = 0;
                        Hero.quickSwapTapWindow = 0;
                    }
                }
            }

            if (HeroDeathHeight > Hero.position.z && Hero.groundDist > 2.0f &&
                Hero.type != HERO_TYPE_GIANT_CLANK && Hero.state != HERO_STATE_DEATH_FALL) {
                Hero_InitBodyState(HERO_STATE_DEATH_FALL, 1);
            }

            else {
                switch (Hero.state) {
                case HERO_STATE_IDLE:
                    if (padState.bits & (PAD_L2 | PAD_L1)) {
                        Hero_InitBodyState(HERO_STATE_LOOK, 1);
                        break;
                    }

                    Hero_ClearNextAnim();

                    if (Hero.hoverLatch != 0) {
                        if (Hero.onMagnerail == 0 || UnlockableItems[ITEM_MAGNEBOOTS] == 0) {
                            Hero_InitBodyState(HERO_STATE_ROCKET_HOVER, 1);
                            break;
                        }
                    }

                    {
                        int canFidget;
                        MobyInstance *backpackMoby;
                        int currentIdleAnimation;

                        canFidget = 1;

                        if (Hero_GetGadgetMoby(0) == ITEM_METAL_DETECTOR) {
                            if (Hero.moby->animationId !=
                                Hero_GetIdleAnim(0)) {
                                Hero_TransAnim(Hero_GetIdleAnim(0), 0, -2.0f);
                            }

                            canFidget = 0;
                        }

                        if (Hero.items[3].state == 2) {
                            backpackMoby = Hero.items[3].moby;

                            if (backpackMoby != 0 && (backpackMoby->unk70 & 2) && backpackMoby->animationId != 1)
                                MB_SetAnimation(backpackMoby, 1, 0, FastScaleRoundInt(7));
                            backpackMoby = Hero.items[3].moby2;

                            if (backpackMoby != 0 && (backpackMoby->unk70 & 2) && backpackMoby->animationId != 1)
                                MB_SetAnimation(backpackMoby, 1, 0, FastScaleRoundInt(7));
                        }

                        if (0.61086524f < HeroTweaks.unk_258 ||
                            HeroTweaks.unk_254 > 0.43633232f) {
                            backpackMoby = Hero.items[3].moby;

                            if (backpackMoby != 0 && backpackMoby->animationId != 1)
                                MB_SetAnimation(backpackMoby, 1, 0, FastScaleRoundInt(0xC));
                            backpackMoby = Hero.items[3].moby2;

                            if (backpackMoby != 0 && backpackMoby->animationId != 1)
                                MB_SetAnimation(backpackMoby, 1, 0, FastScaleRoundInt(0xC));
                        }

                        currentIdleAnimation =
                            Hero_GetAnim(moby->animationId);

                        if (currentIdleAnimation == Hero_GetIdleAnim(0) && canFidget) {
                            if (Hero_GetSpecialIdle(&fidgetIndex)) {
                                HeroIdleFidget *fidget;

                                Hero.fidgetIndex = fidgetIndex;
                                fidget = &HeroIdleFidgets[fidgetIndex];
                                Hero.fidgetCooldown = FastScaleRoundInt(0x78);
                                fidget->durationFrames = FastScaleBySpeed(fidget->duration) * 60.0f;

                                if (fidget->useSpecialState != 0)
                                    Hero_InitBodyState(HERO_STATE_FIDGET, 1);

                                else
                                    Hero_TransAnim(fidget->animation, 0, FastScaleRoundInt(0xC));
                            }
                        }

                        else if (Hero.animFlags & 2) {
                            int keepHoldAnimation = 0;

                            if (Hero.itemAnimActive != 0 && Hero.weaponUp != 0) {
                                if (Hero.moby->animationId == Hero.itemHoldAnim ||
                                    Hero.heldItemAnimMoby[0] != 0) {
                                    keepHoldAnimation = 1;
                                }
                            }

                            if (!keepHoldAnimation) {
                                Hero.itemAnimActive = 0;

                                if (Hero_GetIdleAnim(0) == 0x54)
                                    Hero_TransAnim(Hero_GetIdleAnim(0),
                                                       0,
                                                       FastScaleRoundInt(0x12));

                                else
                                    Hero_TransAnim(Hero_GetIdleAnim(0), 0, -2.0f);
                            }
                        }
                    }

                    if (FastScaleRoundInt(0xA) < Hero.stateTimer) {
                        if (Hero.items[3].moby2 != 0 &&
                            Hero.items[3].moby2->animationId == 1) {
                            if (FastDecTimer_220e78(&Hero.slot3AnimTimer)) {
                                if (0.55850536f > HeroTweaks.unk_258 &&
                                    HeroTweaks.unk_254 < 0.34906584f && Hero.items[3].state == 2) {
                                    Hero.slot3AnimTimer = MB_randRange(
                                        FastScaleRoundInt(0x6E), FastScaleRoundInt(0x10E));
                                    Hero_PlayBackpackIdleAnim();
                                }
                            }
                        }
                    }

                    if (Hero.itemAnimActive != 0 && Hero.animChanging == 0 &&
                        Hero.weaponUp != 0 && Hero.weaponLowered == 0) {
                        int gadgetItem = Hero_GetGadgetMoby(0);

                        if (gadgetItem != Hero.itemAnimItemId)
                            Hero_PlayBackpackIdle();

                        else {
                            int gadgetAnimation = Gadgets[gadgetItem].animation;

                            if (Hero.moby->animationId != gadgetAnimation) {
                                if (Hero.heldItemAnimMoby[0] != 0)
                                    Hero.armLayerFade = 1;
                                Hero.itemHoldAnim = gadgetAnimation;
                                Hero_TransAnim(Hero.itemHoldAnim, 0, FastScaleRoundInt(0xB));
                            }
                        }
                    }

                    Hero_GetIdealThrustFromPad(1.0f, 0);

                    if (Hero.onSlipGround != 0 && Hero.framesOffGround == 0) {
                        Hero_InitBodyState(HERO_STATE_SLOPESLIDE, 1);
                        break;
                    }

                    if (Hero.framesNotGrounded > FastScaleRoundInt(4)) {
                        if (Hero.groundDist > 0.4f) {
                            if (Hero.prevState != HERO_STATE_LAND) {
                                Hero_InitBodyState(HERO_STATE_FALL, 1);
                                break;
                            }

                            if (FastScaleRoundInt(0xF) > Hero.stateTimer)
                                break;
                            Hero_InitBodyState(HERO_STATE_FALL, 1);
                            break;
                        }
                    }

                    if (Hero.moveLockTimer != 0)
                        break;
                    {
                        int holdAllowed = 1;

                        if (Hero.prevState == HERO_STATE_LOOK || Hero.prevState == HERO_STATE_WEAPON_FIRST_PERSON_VIEW) {
                            if (FastScaleRoundInt(5) > Hero.stateTimer)
                                holdAllowed = 0;
                        }

                        if (holdAllowed) {
                            if (Hero.onMagnerail != 1) {
                                int jumpBufferFrames = FastScaleRoundInt(7);

                                if (Hero.jumpBufferLockout != 0)
                                    jumpBufferFrames = 1;

                                if (Hero_JumpCheckHeld(jumpBufferFrames, 0))
                                    break;
                            }
                        }
                    }

                    if (Hero.onMagnerail == 1) {
                        if (PadRingBitsOn(PAD_CROSS, FastScaleRoundInt(7), 0)) {
                            Hero_InitBodyState(HERO_STATE_MAGNE_JUMP, 1);
                            break;
                        }
                    }

                    if ((padState.bits & (PAD_R2 | PAD_R1)) && Hero.framesGroundedCnt != 0) {
                        if (Hero.moby->animationId != 0x1A ||
                            !(Hero.animFrame < 108.0f)) {
                            Hero_InitBodyState(HERO_STATE_CROUCH, 1);
                            break;
                        }
                    }

                    {
                        int walkAllowed = 1;

                        if (Hero.prevState == HERO_STATE_LOOK || Hero.prevState == HERO_STATE_WEAPON_FIRST_PERSON_VIEW) {
                            if (FastScaleRoundInt(0x18) > Hero.stateTimer &&
                                Hero.onMagnerail == 0) {
                                Hero_GetIdealThrustFromPad(1.0f, 0);

                                if (FastDiffRots(
                                        Hero.idealRotZ, HeroYawReference[0]) > 1.2217305f) {
                                    walkAllowed = 0;
                                }
                            }
                        }

                        if (walkAllowed && 0.22f < Hero.padMagnitude) {
                            if (Level == LEVEL_HOVEN) {
                                int groundSound = Hero.groundSoundClass;

                                Hero_PlayFootStep(groundSound, 0, 0);
                                Hero_PlayFootStep(groundSound, 1, 0);
                            }

                            Hero_InitBodyState(HERO_STATE_WALK, 1);
                        }
                    }
                    break;

                case HERO_STATE_FIDGET:
                    if (padState.bits & (PAD_L2 | PAD_L1)) {
                        Hero_InitBodyState(HERO_STATE_LOOK, 1);
                        break;
                    }

                    if (Hero.framesNotGrounded != 0) {
                        Hero_InitBodyState(HERO_STATE_FIDGET_ALT, 1);
                        break;
                    }

                    if (padState.bits & PAD_CROSS) {
                        Hero_InitBodyState(HERO_STATE_FIDGET_ALT, 1);
                        break;
                    }

                    if (padState.bits & (PAD_R2 | PAD_R1)) {
                        Hero_InitBodyState(HERO_STATE_FIDGET_ALT, 1);
                        break;
                    }

                    Hero_GetIdealThrustForWalk();

                    if (Hero.idealSpeed > 0.0f) {
                        Hero_InitBodyState(HERO_STATE_FIDGET_ALT, 1);
                        break;
                    }

                    if (Hero.animFlags & 2) {
                        Hero_CleanupAttachedMobys();
                        Hero_InitBodyState(HERO_STATE_IDLE, 1);
                    }
                    break;

                case HERO_STATE_FIDGET_ALT:
                    if (FastScaleRoundInt(8) < Hero.stateTimer) {
                        Hero_CleanupAttachedMobys();

                        if (Hero.framesNotGrounded != 0) {
                            Hero_InitBodyState(HERO_STATE_FALL, 1);
                            break;
                        }

                        if (Hero_JumpCheckHeld(FastScaleRoundInt(7), 0))
                            break;
                        if (padState.bits & (PAD_R2 | PAD_R1)) {
                            Hero_InitBodyState(HERO_STATE_CROUCH, 1);
                            break;
                        }

                        Hero_GetIdealThrustForWalk();

                        if (Hero.idealSpeed > 0.0f) {
                            Hero_InitBodyState(HERO_STATE_WALK, 1);
                            break;
                        }

                        Hero_InitBodyState(HERO_STATE_IDLE, 1);
                    }
                    break;

                case HERO_STATE_DEATH:
                case HERO_STATE_CLANK_DYING:
                case HERO_STATE_HOLOGUISE_DYING:
                case HERO_STATE_GIANT_CLANK_DYING:
                case HERO_STATE_DROWN:
                case HERO_STATE_ELECTRIC_DEATH:
                case HERO_STATE_ELECTRIC_DEATH_UNDER:
                    if (Hero.animFlags & 2) {
                        HandleHeroDeath();
                        return;
                    }
                    break;

                case HERO_STATE_ICEWATER_FREEZE:
                    if (Hero.stateTimer > FastScaleRoundInt(0xDC)) {
                        HandleHeroDeath();
                        return;
                    }
                    break;

                case HERO_STATE_SWIMUNDER:
                case HERO_STATE_CHARGEUNDER:
                    if (Hero.state == HERO_STATE_SWIMUNDER) {
                        Hero.animSpeed = Hero.storedNeutralSpeed * 15.0f;

                        if (Hero.animSpeed < 0.25f)
                            Hero.animSpeed = 0.25f;

                        if (Hero.animSpeed > 0.75f)
                            Hero.animSpeed = 0.75f;
                    }

                    if (Hero.state == HERO_STATE_SWIMUNDER) {
                        float stillSpeedLimit = frameTime * 2.0f;

                        if (!(padState.bits & (PAD_CROSS | PAD_SQUARE)) && Hero.animFrame > 9.0f &&
                            Hero.animFrame < 19.0f && Hero.subState != 1 &&
                            Hero.padMagnitude < 0.1f && Hero.storedNeutralSpeed < stillSpeedLimit) {
                            Hero_InitBodyState(HERO_STATE_IDLEUNDER, 1);
                            break;
                        }
                    }

                    if (UnlockableItems[ITEM_HYDRO_PACK] != 0 && (padState.bits & (PAD_R2 | PAD_R1))) {
                        if (Hero.state == HERO_STATE_SWIMUNDER &&
                            FastScaleRoundInt(0x14) < Hero.stateTimer) {
                            Hero_InitBodyState(HERO_STATE_CHARGEUNDER, 1);
                            break;
                        }
                    }

                    else if (Hero.state == HERO_STATE_CHARGEUNDER && Hero.padMagnitude > 0.5f) {
                        Hero_InitBodyState(HERO_STATE_SWIMUNDER, 1);
                        break;
                    }

                    if (Hero.state == HERO_STATE_CHARGEUNDER && !(padState.bits & (PAD_CROSS | PAD_SQUARE)) &&
                        Hero.subState != 1 && Hero.padMagnitude < 0.7f &&
                        !(padState.bits & (PAD_R2 | PAD_R1))) {
                        Hero_InitBodyState(HERO_STATE_IDLEUNDER, 1);
                    }
                    break;

                case HERO_STATE_IDLEUNDER:
                    if (Hero.animFlags & 2) {
                        if (Hero.moby->animationId != 0x3C)
                            Hero_TransAnim(0x3C, 0, FastScaleRoundInt(0xB));
                    }

                    if (0.2f < Hero.padMagnitude || (padState.bits & (PAD_CROSS | PAD_SQUARE)) ||
                        (UnlockableItems[ITEM_HYDRO_PACK] != 0 && (padState.bits & (PAD_R2 | PAD_R1)))) {
                        if (UnlockableItems[ITEM_HYDRO_PACK] != 0 && (padState.bits & (PAD_R2 | PAD_R1))) {
                            Hero_InitBodyState(HERO_STATE_CHARGEUNDER, 1);
                            break;
                        }

                        Hero_InitBodyState(HERO_STATE_SWIMUNDER, 1);
                    }
                    break;

                case HERO_STATE_IDLESURF:
                    if (Hero.noWaterJump == 0) {
                        if (PadRingBitsOn(PAD_CROSS, FastScaleRoundInt(8), 0)) {
                            if (FastScaleRoundInt(0xA) < Hero.stateTimer) {
                                Hero_InitBodyState(HERO_STATE_WATER_JUMP, 1);
                                break;
                            }
                        }
                    }

                    Hero.itemSelectBlocked = 1;

                    if (Hero.noWaterDive == 0) {
                        if (PadRingBitsOn(PAD_SQUARE, FastScaleRoundInt(7), 0) ||
                            (UnlockableItems[ITEM_HYDRO_PACK] != 0 &&
                             PadRingBitsOn(PAD_R2 | PAD_R1, FastScaleRoundInt(7), 0))) {
                            if (UnlockableItems[ITEM_HYDRO_PACK] != 0 && (padState.bits & (PAD_R2 | PAD_R1))) {
                                Hero_InitBodyState(HERO_STATE_CHARGEUNDER, 1);
                                break;
                            }

                            Hero_InitBodyState(HERO_STATE_SWIMUNDER, 1);
                            break;
                        }
                    }

                    if (Hero.wading != 0 && Hero.waterDepth < 0.4f) {
                        if (Hero_InitBodyState(HERO_STATE_IDLE, 0))
                            Hero_TransAnim(
                                Hero_GetIdleAnim(0), 0, FastScaleRoundInt(0x12));
                    }

                    if (0.2f < Hero.padMagnitude) {
                        if (FastScaleRoundInt(0xA) < Hero.stateTimer)
                            Hero_InitBodyState(HERO_STATE_SWIMSURF, 1);
                    }
                    break;

                case HERO_STATE_SWIMSURF:
                    if (Hero.noWaterJump == 0) {
                        if (PadRingBitsOn(PAD_CROSS, FastScaleRoundInt(8), 0)) {
                            Hero_InitBodyState(HERO_STATE_WATER_JUMP, 1);
                            break;
                        }
                    }

                    if (Hero.noWaterDive == 0) {
                        if (PadRingBitsOn(PAD_SQUARE, FastScaleRoundInt(7), 0)) {
                            if (UnlockableItems[ITEM_HYDRO_PACK] != 0 && (padState.bits & (PAD_R2 | PAD_R1))) {
                                Hero_InitBodyState(HERO_STATE_CHARGEUNDER, 1);
                                break;
                            }

                            Hero_InitBodyState(HERO_STATE_SWIMUNDER, 1);
                            break;
                        }
                    }

                    if (Hero.wading != 0 && Hero.waterDepth < 0.7f) {
                        Hero_InitBodyState(HERO_STATE_WADE, 0);
                        Hero_TransAnim(0x60, 0, FastScaleRoundInt(0x11));
                        Hero.velocity.z = 0.0f;
                        Hero.displacement.z = 0.0f;
                    }

                    if (0.1f > Hero.padMagnitude && Hero.storedNeutralSpeed == 0.0f &&
                        Hero.swimStrokeTimer == 0) {
                        Hero_InitBodyState(HERO_STATE_IDLESURF, 1);
                    }
                    break;

                case HERO_STATE_GET_HIT_UNDER:
                    if (Hero.health <= 0) {
                        if (Level == LEVEL_QUARTU ||
                            Level == LEVEL_VELDIN_ORBIT) {
                            Hero_InitBodyState(HERO_STATE_ELECTRIC_DEATH_UNDER, 1);
                            break;
                        }

                        Hero_InitBodyState(HERO_STATE_DROWN, 1);
                        Hero_TransAnim(0x5F, 0x28, FastScaleRoundInt(0x12));
                        break;
                    }

                    if (Hero.animFlags & 2) {
                        Hero_InitBodyState(HERO_STATE_IDLEUNDER, 1);
                        break;
                    }

                    if (FastScaleRoundInt(0x32) < Hero.stateTimer)
                        Hero_InitBodyState(HERO_STATE_IDLEUNDER, 0);
                    break;

                case HERO_STATE_GET_HIT_SURF:
                    if (Hero.health <= 0) {
                        Hero_InitBodyState(HERO_STATE_DROWN, 1);
                        Hero_TransAnim(0x5F, 0x25, FastScaleRoundInt(0x12));
                        break;
                    }

                    if (FastScaleRoundInt(0x32) < Hero.stateTimer)
                        Hero_InitBodyState(HERO_STATE_IDLESURF, 0);
                    break;

                case HERO_STATE_LOOK:
                    if (Hero.type == HERO_TYPE_RATCHET) {
                        if (Hero.weaponUp == 0 || Hero.invisible != 0) {
                            if (padState.bits & (PAD_R2 | PAD_R1)) {
                                if (Hero.moby->animationId != 0xD)
                                    Hero_TransAnim(0xD, 0, FastScaleRoundInt(8));
                            }

                            else {
                                int idleAnimation = Hero_GetIdleAnim(1);

                                if (Hero.moby->animationId != idleAnimation)
                                    Hero_TransAnim(idleAnimation, 0, FastScaleRoundInt(8));
                            }
                        }
                    }

                    {
                        MobyInstance *weaponMoby = Hero.items[0].moby;
                        int idleAllowed = 1;

                        if (weaponMoby != 0 && Hero_isMobyWrench(weaponMoby) && weaponMoby->state != 0)
                            idleAllowed = 0;

                        if (padState.bits & (PAD_L2 | PAD_L1))
                            break;
                        if (!idleAllowed)
                            break;
                    }

                    if (Hero.type != HERO_TYPE_RATCHET) {
                        Hero_TransitionToDefault();
                        break;
                    }

                    if (padState.bits & (PAD_R2 | PAD_R1)) {
                        Hero_InitBodyState(HERO_STATE_CROUCH, 1);
                        break;
                    }

                    Hero_InitBodyState(HERO_STATE_IDLE, 0);

                    {
                        int idleAnimation = Hero_GetIdleAnim(1);

                        if (Hero.moby->animationId != idleAnimation)
                            Hero_TransAnim(idleAnimation, 0, FastScaleRoundInt(8));
                    }
                    break;

                case HERO_STATE_ITEM_BUTTON_RELEASE_WAIT:
                    if (padState.bits & Hero.items[0].buttonMask)
                        break;
                    if (Hero.idleReturnDelay != 0)
                        break;
                    Hero_InitBodyState(HERO_STATE_IDLE, 1);
                    break;

                case HERO_STATE_WAIT_FOR_ITEM_RELEASE_THEN_IDLE:
                    if (padState.bits & Hero.items[0].buttonMask)
                        break;
                    if (Hero.idleReturnDelay != 0)
                        break;
                    if (Hero.moby->animationId == 0x36) {
                        Hero_InitBodyState(HERO_STATE_IDLE, 0);
                        break;
                    }

                    Hero_InitBodyState(HERO_STATE_IDLE, 1);
                    break;

                case HERO_STATE_ITEM_BUTTON_HOLD_ANIMATION_WAIT: {
                    int itemButtonMask = Hero.items[0].buttonMask;

                    if (Hero.moby->updateId == 0x2E && Hero.animFrame > 28.0f) {
                        if (padState.bits & itemButtonMask) {
                            Hero_InitBodyState(HERO_STATE_ITEM_BUTTON_RELEASE_WAIT, 1);
                            break;
                        }

                        Hero_InitBodyState(HERO_STATE_IDLE, 1);
                    }
                } break;

                case HERO_STATE_COMBO_ATTACK:
                case HERO_STATE_JUMP_ATTACK:
                case HERO_STATE_THROW_ATTACK:
                    if (Hero.state == HERO_STATE_JUMP_ATTACK) {
                        int slamInterceptFrames =
                            FastFloatToInt(Hero_PredictLand(
                                60.0f, frameTimeSq * 130.0f, -1.0f));
                        int slamEndFrame = 0x1A;

                        if (Hero.slamDescending == 0.0f)
                            Hero.animSpeed = 0.33f;

                        else if (Hero.slamDescending != 0.0f && Hero.framesNotGrounded != 0 &&
                                   slamInterceptFrames != 0 &&
                                   (float)slamEndFrame - Hero.animFrame > 1.0f) {
                            Hero_GetAnimFrameBlend(
                                slamEndFrame, slamInterceptFrames, 0.5f, -1.0f);

                            if (Hero.groundDist < 0.7f && Hero.animSpeed < 0.75f)
                                Hero.animSpeed = 0.75f;
                        }

                        else if (Hero.framesNotGrounded == 0 && Hero.animFrame < (float)slamEndFrame)
                            Hero.animSpeed = 2.0f;

                        else
                            Hero.animSpeed = 1.0f;
                    }

                    {
                        HeroAttackRow *attackRow = &HeroAttackTable[Hero.attackRecord];
                        int comboWindowFrames = (FastFloatToInt(Hero.animFrame) - attackRow->baseFrame) * 2;

                        if ((float)attackRow->interruptFrame < Hero.animFrame && Hero.animChanging == 0 &&
                            !(Hero.state == HERO_STATE_THROW_ATTACK &&
                              Hero.onMagnerail != 0)) {
                            if (PadRingBitsOn(PAD_CROSS, comboWindowFrames, 0)) {
                                if (padState.bits & (PAD_R2 | PAD_R1)) {
                                    if (Hero_CrouchJumpTransitions())
                                        break;
                                }

                                else if (Hero.noJumps == 0) {
                                    Hero_InitBodyState(HERO_STATE_JUMP, 1);
                                    break;
                                }
                            }
                        }

                        if (Hero.animChanging == 0 && (float)attackRow->endFrame < Hero.animFrame) {
                            Hero_InitBodyState(HERO_STATE_IDLE, 0);
                            break;
                        }
                    }

                    if (Hero.state == HERO_STATE_THROW_ATTACK) {
                        if (Hero.items[0].itemId != 8) {
                            Hero_InitBodyState(HERO_STATE_IDLE, 1);
                            break;
                        }

                        if (FastScaleRoundInt(0x64) < Hero.stateTimer &&
                            Hero.nextAnimationFrame < 0x1A) {
                            Hero_SetNextAnimBlend(2);
                            Hero.nextAnimationFrame = 0x1A;
                        }
                    }
                    break;

                case HERO_STATE_UNK_BONK:
                case HERO_STATE_JUMP_BOUNCE:
                    if (Hero.animFlags & 2)
                        Hero_InitBodyState(HERO_STATE_IDLE, 1);
                    break;

                case HERO_STATE_WALK:
                case HERO_STATE_ICE_SLIDING:
                case HERO_STATE_WADE:
                case 126:
                    if (Hero.runStartBlending != 0 &&
                        (moby->animationBlend > 0.9f || moby->updateId != 0xFF)) {
                        Hero.runStartBlending = 0;
                    }

                    if (Hero.onSlipGround != 0 && Hero.framesOffGround == 0) {
                        Hero_InitBodyState(HERO_STATE_SLOPESLIDE, 1);
                        break;
                    }

                    if (!(Hero.framesNotGrounded < FastScaleRoundInt(5)) &&
                        !(Hero.prevStateType == HERO_STATE_TYPE_WATER_SURFACE &&
                          Hero.wading != 0) &&
                        Hero.groundDist > 1.35f) {
                        if (Hero_ProbeCollAlongVelocity() == 0) {
                            Hero_InitBodyState(HERO_STATE_FALL, 1);
                            break;
                        }
                    }

                    {
                        int jumpBufferFrames = FastScaleRoundInt(9);

                        if (Hero.jumpBufferLockout != 0)
                            jumpBufferFrames = 1;

                        if (PadRingBitsOn(PAD_CROSS, jumpBufferFrames, 0)) {
                            if (!(Hero.framesNotGrounded > FastScaleRoundInt(4)) ||
                                Hero.stillFrames != 0) {
                                Hero_GetIdealThrustFromPad(1.0f, 0);

                                if (Hero_JumpCheckHeld(jumpBufferFrames, 1))
                                    break;
                                if (Hero.subState <= 0) {
                                    Hero_InitBodyState(HERO_STATE_JUMP, 1);
                                    break;
                                }

                                if (Hero.idealSpeed > HeroJumpSpeeds.minRunSpeed &&
                                    FastDiffRots(
                                        Hero.idealRotZ, Hero.rotation.z) < 1.0471976f &&
                                    HeroJumpSpeeds.stepSpeed * frameTime * 0.85f <
                                        Hero.flatSpeed) {
                                    Hero_InitBodyState(HERO_STATE_RUN_JUMP, 1);
                                    break;
                                }

                                Hero_InitBodyState(HERO_STATE_JUMP, 1);
                                break;
                            }
                        }
                    }

                    if (Hero.framesNotGrounded != 0)
                        break;
                    if (Hero.onIceGround == 0 || (frameTime * 2.0f > Hero.flatSpeed &&
                                                    Hero.groundSlope < 0.08726646f)) {
                        if (padState.bits & (PAD_L2 | PAD_L1)) {
                            Hero_InitBodyState(HERO_STATE_LOOK, 1);
                            break;
                        }
                    }

                    if (padState.bits & (PAD_R2 | PAD_R1)) {
                        Hero_InitBodyState(HERO_STATE_CROUCH, 1);
                        break;
                    }

                    if (Hero.state == HERO_STATE_WALK) {
                        if (Hero.wading != 0)
                            Hero_InitBodyState(HERO_STATE_WADE, 1);
                    }

                    else if (Hero.state == HERO_STATE_WADE) {
                        if (Hero.wading == 0)
                            Hero_InitBodyState(HERO_STATE_WALK, 1);
                    }

                    if (Hero.stateTimer > FastScaleRoundInt(0xF) ||
                        (Hero.prevStateType != HERO_STATE_TYPE_IDLE &&
                         Hero.prevStateType != HERO_STATE_TYPE_RUN)) {
                        if ((padState.bitsOn & 0x10000) && Hero.weaponUp == 0)
                            Hero.sharpTurn = 1;
                    }

                    if (Hero.state == HERO_STATE_WALK) {
                        if (Hero.padMagnitude < 0.17f) {
                            if (frameTime * 2.7f < Hero.speedXY && Hero.weaponUp == 0) {
                                if (Hero.speedXY < frameTime * 4.4f ||
                                    PadRingAng(4) < 0.8f) {
                                    if (Hero_InitBodyState(HERO_STATE_SKID, 0) == 0)
                                        break;
                                    if (Hero_GetIdleAnim(0) == 0x54)
                                        Hero_TransAnim(Hero_GetIdleAnim(0),
                                                           0,
                                                           FastScaleRoundInt(0x12));

                                    else
                                        Hero_TransAnim(0x14, 7, FastScaleRoundInt(9));
                                    break;
                                }

                                Hero_InitBodyState(HERO_STATE_SKID, 1);
                                break;
                            }

                            if (!(Hero.stateTimer > FastScaleRoundInt(0x19)))
                                break;
                            if (Hero_CheckGadgetReady())
                                break;
                            if (Hero_InitBodyState(HERO_STATE_IDLE, 0) == 0)
                                break;
                            if (Hero_GetIdleAnim(0) == 0x54)
                                Hero_TransAnim(
                                    Hero_GetIdleAnim(0), 0, FastScaleRoundInt(0x12));

                            else
                                Hero_TransAnim(Hero_GetIdleAnim(0), 0, -1.0f);
                            break;
                        }

                        Hero_UpdateWalkAnim();
                        break;
                    }

                    else if (Hero.state == HERO_STATE_WADE) {
                        if (padState.handsOffStick != 0) {
                            if (FastVec3Length(&Hero.velocity) < frameTime * 3.2f) {
                                if (Hero_InitBodyState(HERO_STATE_IDLE, 0))
                                    Hero_TransAnim(Hero_GetIdleAnim(0),
                                                       0,
                                                       FastScaleRoundInt(0x11));
                            }
                        }

                        Hero.animSpeed = Hero.speedXY * 35.0f;

                        if (Hero.animSpeed < 0.6f)
                            Hero.animSpeed = 0.6f;

                        if (Hero.animSpeed > 1.05f)
                            Hero.animSpeed = 1.05f;
                    }
                    break;

                case HERO_STATE_WALK_TO_POS:
                    if (FastVec3DistLen(&Hero.position, &Hero.targetPose) < 0.2f) {
                        if (frameTime * 2.7f > Hero.speedXY) {
                            if (FastDiffRots(
                                    Hero.rotation.z, Hero.targetPose.w) < 0.034906585f) {
                                Hero_InitBodyState(HERO_STATE_IDLE_TO_POS, 1);
                                break;
                            }
                        }

                        if (Hero.type != HERO_TYPE_RATCHET &&
                            frameTime * 2.7f <= Hero.speedXY) {
                            Hero_InitBodyState(HERO_STATE_SKID_TO_POS, 1);
                        }
                        break;
                    }

                    Hero_UpdateWalkAnim();
                    break;

                case HERO_STATE_SKID_TO_POS:
                    if (Hero.animFlags & 2)
                        Hero_InitBodyState(HERO_STATE_WALK_TO_POS, 1);
                    break;

                case HERO_STATE_IDLE_TO_POS:
                    if ((Hero.animFlags & 2) || Hero.stateEntryOption != 0)
                        Hero_InitBodyState(HERO_STATE_IDLE, 1);

                    if (0.2f < FastVec3DistLen(&Hero.position, &Hero.targetPose))
                        Hero_InitBodyState(HERO_STATE_WALK_TO_POS, 1);
                    break;

                case HERO_STATE_SLIDE:
                    if (Hero.selector4 != 0)
                        break;
                    if (Hero.sinkingFloorHold != 0)
                        break;
                    if (Hero.loopSounds[2] != -1) {
                        SoundVoice *voiceRow = &audioState.rows[Hero.loopSounds[2]];

                        if (voiceRow[1].pMoby == Hero.moby &&
                            voiceRow[1].inUse != 0) {
                            sound_KillChannel(Hero.loopSounds[2]);
                        }
                    }

                    Hero.loopSounds[2] = -1;

                    if (Hero_InitBodyState(HERO_STATE_IDLE, 0) == 0)
                        break;
                    Hero_TransAnim(
                        Hero_GetIdleAnim(0), 0, FastScaleRoundInt(0x11));
                    CopyVec4Inline(&Hero.externalMomentum, &Hero.frameMove);
                    break;

                case HERO_STATE_SKID:
                    if (padState.bits & (PAD_L2 | PAD_L1)) {
                        Hero_InitBodyState(HERO_STATE_LOOK, 1);
                        break;
                    }

                    if (Hero.moveLockTimer == 0) {
                        if (padState.bitsOn & PAD_CROSS) {
                            Hero_InitBodyState(HERO_STATE_JUMP, 1);
                            break;
                        }

                        if (padState.bits & (PAD_R2 | PAD_R1)) {
                            Hero_InitBodyState(HERO_STATE_CROUCH, 1);
                            break;
                        }
                    }

                    if (Hero.framesNotGrounded > FastScaleRoundInt(8) && Hero.groundDist > 0.3f) {
                        Hero_InitBodyState(HERO_STATE_FALL, 1);
                        break;
                    }

                    if (Hero.animFlags & 2) {
                        Hero_InitBodyState(HERO_STATE_IDLE, 1);
                        break;
                    }

                    if (!(Hero.padMagnitude > 0.2f))
                        break;
                    if (Hero_GetIdleAnim(0) != 0x54) {
                        if (Hero.storedNeutralSpeed == 0.0f) {
                            Hero_InitBodyState(HERO_STATE_IDLE, 0);
                            break;
                        }
                    }

                    else if (Hero.animFrame > 10.0f) {
                        if (Hero_InitBodyState(HERO_STATE_IDLE, 0))
                            Hero_TransAnim(
                                Hero_GetIdleAnim(0), 0, FastScaleRoundInt(0x11));
                    }

                    if (0.5f < Hero.padMagnitude)
                        Hero_InitBodyState(HERO_STATE_WALK, 1);
                    break;

                case HERO_STATE_CROUCH:
                    if (padState.bits & (PAD_L2 | PAD_L1)) {
                        Hero_InitBodyState(HERO_STATE_LOOK, 1);
                        break;
                    }

                    if (Hero.stateTimer > FastScaleRoundInt(0xB) &&
                        !(padState.bits & (PAD_R2 | PAD_R1))) {
                        Hero_InitBodyState(HERO_STATE_IDLE, 0);
                        Hero_TransAnim(Hero_GetIdleAnim(0), 0, -2.0f);
                        break;
                    }

                    if (Hero.onSlipGround != 0 && Hero.framesOffGround == 0) {
                        Hero_InitBodyState(HERO_STATE_SLOPESLIDE, 1);
                        break;
                    }

                    if (Hero.onMagnerail == 1) {
                        if (PadRingBitsOn(PAD_CROSS, FastScaleRoundInt(7), 0)) {
                            Hero_InitBodyState(HERO_STATE_MAGNE_JUMP, 1);
                            break;
                        }
                    }

                    else if (Hero_CrouchJumpTransitions())
                        break;
                    if (PadRingBitsOn(PAD_SQUARE, FastScaleRoundInt(0xF), 0)) {
                        if (Hero.items[0].itemId == 8)
                            Hero_InitBodyState(HERO_STATE_THROW_ATTACK, 1);
                    }

                    if (Hero.framesNotGrounded > FastScaleRoundInt(8)) {
                        if (Hero.prevState != HERO_STATE_LAND) {
                            Hero_InitBodyState(HERO_STATE_FALL, 1);
                            break;
                        }

                        if (FastScaleRoundInt(0xF) > Hero.stateTimer)
                            break;
                        Hero_InitBodyState(HERO_STATE_FALL, 1);
                    }
                    break;

                case HERO_STATE_ROCKET_STOMP:
                    if (Hero.stateTimer < FastScaleRoundInt(0xC) &&
                        (Hero.prev2State != HERO_STATE_THRUSTER_PACK_FORWARD_JUMP ||
                         (Hero.prevState != HERO_STATE_LAND && Hero.prevState != HERO_STATE_FALL)) &&
                        Hero.prevState != HERO_STATE_HELI_JUMP && Hero.prevState != HERO_STATE_HELI_PACK_FWD_JUMP &&
                        Hero.prevState != HERO_STATE_THRUSTER_PACK_FORWARD_JUMP && Hero.prevState != HERO_STATE_WATER_JUMP &&
                        Hero.prevState != HERO_STATE_TAKING_DAMAGE_LAVA && (padState.bitsOn & PAD_CROSS)) {
                        Hero_InitBodyState(HERO_STATE_THRUSTER_PACK_FORWARD_JUMP, 1);
                    }

                    {
                        int riseFallInterceptFrames =
                            FastFloatToInt(Hero_PredictLand(
                                60.0f, Hero.riseFallGravity, -1.0f));
                        Hero.predictedLandFrames = riseFallInterceptFrames;

                        if (Hero.pastApex != 0.0f && Hero.framesOffGround != 0 &&
                            riseFallInterceptFrames != 0) {
                            if (riseFallInterceptFrames == 2)
                                FastScaleRoundInt(0xA);
                            Hero_GetAnimFrameBlend(
                                Hero.riseFallTargetFrame,
                                Hero.predictedLandFrames,
                                0.5f,
                                -1.0f);
                        }

                        else
                            Hero.animSpeed = 1.0f;
                    }

                    if (Hero.animFlags & 2)
                        Hero_InitBodyState(HERO_STATE_IDLE, 1);
                    break;

                case HERO_STATE_LEDGE_GRAB:
                    if (13.5f < Hero.animFrame)
                        Hero_InitBodyState(HERO_STATE_LEDGE_IDLE, 0);
                    break;

                case HERO_STATE_LEDGE_IDLE:
                    if ((Hero.animFlags & 2) && Hero.moby->animationId == 0x20)
                        Hero_TransAnim(0x21, 0, FastScaleRoundInt(6));
                    Hero_GetIdealThrustFromPad(1.0f, 0);
                    CopyVec4Inline(&ledgeProbePosition, &Hero.position);
                    ledgeHoldProbeYaw = Hero.rotation.z;

                    if (Hero_CheckLedgeAhead(&ledgeProbePosition, &ledgeHoldProbeYaw) == 0) {
                        Hero_InitBodyState(HERO_STATE_FALL, 1);
                        Hero.noLedge = FastScaleRoundInt(0xA);
                        break;
                    }

                    if ((Hero.padMagnitude > 0.5f &&
                         PadRingBitsOn(PAD_CROSS, FastScaleRoundInt(9), 0) &&
                         2.3561945f < FastDiffRots(Hero.idealRotZ,
                                                                        Hero.rotation.z)) ||
                        (padState.bitsOn & (PAD_R2 | PAD_R1))) {
                        Hero_InitBodyState(HERO_STATE_FALL, 1);
                        Hero.noLedge = FastScaleRoundInt(0xA);
                        break;
                    }

                    if (PadRingBitsOn(PAD_CROSS, FastScaleRoundInt(0x11), 0)) {
                        Hero_InitBodyState(HERO_STATE_LEDGE_JUMP, 1);
                        break;
                    }

                    if (0.5f < Hero.padMagnitude &&
                        FastDiffRots(
                            Hero.idealRotZ,
                            FastAddRots(Hero.rotation.z, 1.5707964f)) < 0.7853982f) {
                        CopyVec4Inline(&shimmyEntryProbePosition, &Hero.position);
                        shimmyEntryProbePosition.x +=
                            FastAngleSinF(FastAddRots(Hero.rotation.z, 1.5707964f)) * 0.3f;
                        shimmyEntryProbePosition.y +=
                            FastAngleCosF(FastAddRots(Hero.rotation.z, 1.5707964f)) * 0.3f;
                        positiveShimmyProbeYaw = Hero.rotation.z;

                        if (Hero_CheckLedgeAhead(&shimmyEntryProbePosition,
                                                  &positiveShimmyProbeYaw)) {
                            Hero_InitBodyState(HERO_STATE_LEDGE_TRAVERSE_LEFT, 1);
                        }
                        break;
                    }

                    if (0.5f < Hero.padMagnitude &&
                        FastDiffRots(
                            Hero.idealRotZ,
                            FastAddRots(Hero.rotation.z, -1.5707964f)) < 0.7853982f) {
                        CopyVec4Inline(&shimmyEntryProbePosition, &Hero.position);
                        shimmyEntryProbePosition.x +=
                            FastAngleSinF(FastAddRots(Hero.rotation.z, -1.5707964f)) * 0.3f;
                        shimmyEntryProbePosition.y +=
                            FastAngleCosF(FastAddRots(Hero.rotation.z, -1.5707964f)) * 0.3f;
                        negativeShimmyProbeYaw = Hero.rotation.z;

                        if (Hero_CheckLedgeAhead(&shimmyEntryProbePosition,
                                                  &negativeShimmyProbeYaw)) {
                            Hero_InitBodyState(HERO_STATE_LEDGE_TRAVERSE_RIGHT, 1);
                        }
                    }
                    break;

                case HERO_STATE_LEDGE_TRAVERSE_LEFT:

                case HERO_STATE_LEDGE_TRAVERSE_RIGHT: {
                    float shimmyYawOffset;

                    CopyVec4Inline(&ledgeProbePosition, &Hero.position);
                    shimmyYawOffset = 1.5707964f;

                    if (Hero.state == HERO_STATE_LEDGE_TRAVERSE_RIGHT)
                        shimmyYawOffset = -1.5707964f;
                    ledgeProbePosition.x +=
                        FastAngleSinF(FastAddRots(Hero.rotation.z, shimmyYawOffset)) *
                        0.3f;
                    ledgeProbePosition.y +=
                        FastAngleCosF(FastAddRots(Hero.rotation.z, shimmyYawOffset)) *
                        0.3f;
                    shimmyContinuationProbeYaw = Hero.rotation.z;
                    Hero_GetIdealThrustFromPad(1.0f, 0);

                    if (Hero.padMagnitude < 0.5f ||
                        0.7853982f <
                            FastDiffRots(
                                Hero.idealRotZ,
                                FastAddRots(Hero.rotation.z, shimmyYawOffset)) ||
                        Hero_CheckLedgeAhead(&ledgeProbePosition,
                                              &shimmyContinuationProbeYaw) == 0) {
                        if (Hero.animFlags & 2) {
                            Hero_InitBodyState(HERO_STATE_LEDGE_IDLE, 1);
                            break;
                        }
                    }
                }

                    if (0.5f < Hero.padMagnitude &&
                        PadRingBitsOn(PAD_CROSS, FastScaleRoundInt(9), 0) &&
                        2.3561945f < FastDiffRots(Hero.idealRotZ,
                                                                       Hero.rotation.z)) {
                        Hero_InitBodyState(HERO_STATE_FALL, 1);
                        Hero.noLedge = FastScaleRoundInt(0x28);
                        break;
                    }

                    if (PadRingBitsOn(PAD_CROSS, FastScaleRoundInt(9), 0))
                        Hero_InitBodyState(HERO_STATE_LEDGE_JUMP, 1);
                    break;

                case HERO_STATE_SLOPESLIDE:
                    if (FastScaleRoundInt(0x12C) < Hero.stateTimer)
                        HandleHeroDeath();

                    if (Hero.onSlipGround != 0)
                        break;
                    if (Hero.framesNotGrounded != 0) {
                        Hero_InitBodyState(HERO_STATE_FALL, 1);
                        break;
                    }

                    Hero_InitBodyState(HERO_STATE_IDLE, 1);
                    break;

                case HERO_STATE_FALL:
                case HERO_STATE_SWING_FALL:
                    if (Hero.subState == 0) {
                        if (!(FastScaleRoundInt(0x12) > Hero.stateTimer) ||
                            Hero.groundDist > 1.75f) {
                            Hero_TransAnim(0xB, 0, FastScaleRoundInt(0x10));
                            Hero.subState = 1;

                            if (Hero.state == HERO_STATE_SWING_FALL)
                                Hero.requestedCamType = 7;

                            else
                                Hero.requestedCamType = 0;
                        }
                    }

                    if (Hero.framesNotGrounded == 0) {
                        int landedOffMoby;
                        int heavyLandSubState;

                        Hero_PlayFootStep(Hero.groundSoundClass, 0, 1);
                        Hero_PlayFootStep(Hero.groundSoundClass, 1, 1);

                        if (frameTime * -9.0f > Hero.displacement.z)
                            Hero.displacement.z = frameTime * -9.0f;

                        if (frameTime * -9.0f > Hero.velocity.z)
                            Hero.velocity.z = frameTime * -9.0f;

                        if (Hero.health <= 0) {
                            Hero_InitBodyState(HERO_STATE_DEATH, 1);
                            break;
                        }

                        landedOffMoby = Hero.standingOnMoby == 0;
                        heavyLandSubState = 1;

                        if (!(FastScaleRoundInt(0x5A) > Hero.stateTimer)) {
                            if (Hero_InitBodyState(HERO_STATE_IDLE, 0))
                                Hero_TransAnim(0xC, 4, FastScaleRoundInt(6));

                            if (landedOffMoby)
                                Hero.moveLockTimer = FastScaleRoundInt(0x16);
                            Hero_SetTiltWobbleParams(0.022f, 0.004f, 0xA, 4, 0, 1);
                            break;
                        }

                        if (Hero.subState == heavyLandSubState) {
                            if (Hero_InitBodyState(HERO_STATE_IDLE, 0))
                                Hero_TransAnim(0xC, 9, -1.0f);
                            Hero_ToHeroRelative(&Hero.externalMomentum, &Hero.externalMomentum, 0.0f);
                            ClampVec3Magnitude(&Hero.externalMomentum, frameTime * 7.0f);
                            Hero.moveLockTimer = FastScaleRoundInt(7);

                            if (Hero.prevState == HERO_STATE_SWING_FALL)
                                Hero.moveLockTimer = FastScaleRoundInt(0xA);

                            if (landedOffMoby) {
                                if (FastScaleRoundInt(0x32) < Hero.stateTimer)
                                    Hero.moveLockTimer = FastScaleRoundInt(0x12);
                            }

                            Hero_SetTiltWobbleParams(0.019f, 0.002f, 0xA, 2, 0, 1);
                            break;
                        }

                        if (Hero.padMagnitude > 0.5f && Hero.moveLockTimer == 0) {
                            Hero_InitBodyState(HERO_STATE_WALK, 1);
                            Hero_SetTiltWobbleParams(0.016f, 0.002f, 7, 2, 0, 1);
                            break;
                        }

                        if (frameTime * 3.0f < Hero.flatSpeed) {
                            if (Hero_InitBodyState(HERO_STATE_SKID, 0) == 0)
                                break;
                            Hero_TransAnim(6, 0, FastScaleRoundInt(0xC));
                            ClampVec3Magnitude(&Hero.externalMomentum, frameTime * 7.7f);
                            break;
                        }

                        Hero_InitBodyState(HERO_STATE_IDLE, 1);
                        Hero_SetTiltWobbleParams(0.016f, 0.002f, 5, 2, 0, 1);
                        break;
                    }

                    if (Hero.health <= 0)
                        break;
                    if ((padState.bits & PAD_CROSS) && UnlockableItems[ITEM_HELI_PACK] != 0 &&
                        Hero_GetGadgetMoby(3) != ITEM_HYDRO_PACK && Hero.hasClank == 0 &&
                        Hero.moveLockTimer == 0 && Hero.groundDist > 0.6f) {
                        Hero_InitBodyState(HERO_STATE_LAND, 1);
                        break;
                    }

                    if (Hero.stillFrames > FastScaleRoundInt(0x14)) {
                        int jumpBufferFrames = FastScaleRoundInt(6);

                        if (Hero.jumpBufferLockout != 0)
                            jumpBufferFrames = 1;

                        if (Hero_JumpCheckHeld(jumpBufferFrames, 0))
                            break;
                    }

                    if (Hero_GetGadgetMoby(3) == ITEM_THRUSTER_PACK && Hero.hasClank == 0) {
                        if (PadRingCoincidentBitsOn(
                                0x40, 0xA, FastScaleRoundInt(9), FastScaleRoundInt(8))) {
                            if ((padState.bits & (PAD_R2 | PAD_R1)) &&
                                (padState.bitsOn & PAD_CROSS)) {
                                if (Hero.pastJumpApex == 0 || Hero.groundDist > 1.5f) {
                                    Hero_InitBodyState(HERO_STATE_THRUSTER_PACK_FORWARD_JUMP, 1);
                                    break;
                                }
                            }
                        }
                    }

                    if (Hero.ledgeFound != 0)
                        Hero_InitBodyState(HERO_STATE_LEDGE_GRAB, 1);
                    break;

                case HERO_STATE_DEATH_FALL:
                    if ((Level == LEVEL_KERWAN && 5.0f > Hero.position.z) ||
                        (Level == LEVEL_NEBULA_G34 && 50.0f > Hero.position.z) ||
                        (Level == LEVEL_KALEBO_3 &&
                         (77.0f > Hero.position.z ||
                          (Hero.stateTimer > 0x14 && Hero.wallHit != 0 &&
                           Hero.displacement.z >= 0.0f))) ||
                        Hero.stateTimer > FastScaleRoundInt(0x78)) {
                        HandleHeroDeath();
                        return;
                    }
                    break;

                case HERO_STATE_ROCKET_HOVER:
                    if (Hero.onSlipGround != 0 && Hero.groundDist < 0.5f) {
                        Hero_InitBodyState(HERO_STATE_SLOPESLIDE, 1);
                        break;
                    }

                    {
                        int r1Repeated = 0;

                        FastDecTimer_220e78(&R1RepeatTimer);

                        if (R1RepeatTimer != 0) {
                            r1Repeated = 1;

                            if (!((padState.bits & PAD_R1) && (padState.bitsOn & PAD_R1)))
                                r1Repeated = 0;
                        }

                        if (padState.bitsOn & PAD_R1)
                            R1RepeatTimer = FastScaleRoundInt(0x1E);

                        if (!(Hero.stateTimer > FastScaleRoundInt(0x14)))
                            break;
                        if (!(padState.bitsOn & PAD_CROSS) && !r1Repeated)
                            break;
                    }

                    Hero.hoverLatch = 0;
                    Hero.moveLockTimer = FastScaleRoundInt(0x19);

                    if (Hero.framesNotGrounded != 0) {
                        if (Hero_InitBodyState(HERO_STATE_IDLE, 0) == 0)
                            break;
                        Hero_TransAnim(7, 0x17, FastScaleRoundInt(9));
                        Hero_SetTiltWobbleParams(0.016f, 0.002f, 5, 2, 0, 1);
                        break;
                    }

                    if (Hero_InitBodyState(HERO_STATE_IDLE, 0) == 0)
                        break;
                    Hero_TransAnim(Hero_GetIdleAnim(0), 0, -2.0f);
                    Hero_SetTiltWobbleParams(0.016f, 0.002f, 5, 2, 0, 1);
                    break;

                case HERO_STATE_LAND:
                    if (Hero.wallJumpOk != 0) {
                        if (FastScaleRoundInt(9) > Hero.stateTimer) {
                            int wasAirborne = 0;

                            if (Hero.prevState == HERO_STATE_JUMP || Hero.prevState == HERO_STATE_RUN_JUMP ||
                                Hero.prevState == HERO_STATE_DOUBLE_JUMP || Hero.prevState == HERO_STATE_WALL_JUMP) {
                                wasAirborne = 1;
                            }

                            if (wasAirborne)
                                Hero_InitBodyState(HERO_STATE_WALL_JUMP, 1);
                            break;
                        }
                    }

                    if (Hero.stateTimer > FastScaleRoundInt(0x1E) &&
                        !(padState.bits & PAD_CROSS) &&
                        !(padState.hudBits & PAD_CROSS)) {
                        Hero_InitBodyState(HERO_STATE_FALL, 1);
                        break;
                    }

                    if (Hero.ledgeFound != 0) {
                        Hero_InitBodyState(HERO_STATE_LEDGE_GRAB, 1);
                        break;
                    }

                    if (Hero.framesNotGrounded != 0 &&
                        !(Hero.position.z - Hero.groundHeight < 0.4f)) {
                        break;
                    }

                    if (FastScaleRoundInt(0xA) > Hero.stateTimer)
                        Hero.jumpBufferLockout = FastScaleRoundInt(0xC) - Hero.stateTimer;
                    Hero_GetIdealThrustFromPad(1.0f, 0);

                    if (Hero.prevState == HERO_STATE_THRUSTER_PACK_FORWARD_JUMP && FastScaleRoundInt(4) > Hero.stateTimer) {
                        if (Hero_InitBodyState(HERO_STATE_SKID, 0) == 0)
                            break;
                        Hero_TransAnim(5, 0, -1.0f);
                        Hero.moveLockTimer = FastScaleRoundInt(0x22);
                        break;
                    }

                    if (padState.bits & (PAD_R2 | PAD_R1)) {
                        Hero_InitBodyState(HERO_STATE_CROUCH, 1);
                        Hero_SetTiltWobbleParams(0.016f, 0.002f, 5, 2, 0, 1);
                        break;
                    }

                    if (Hero.idealSpeed > HeroJumpSpeeds.minRunSpeed &&
                        FastDiffRots(Hero.idealRotZ,
                                                          Hero.rotation.z) < 1.5707964f) {
                        if (Hero.onIceGround != 0 || Hero.wading != 0) {
                            Hero_InitBodyState(HERO_STATE_WALK, 1);
                            break;
                        }

                        Hero_InitBodyState(HERO_STATE_WALK, 0);

                        if (Hero.state == HERO_STATE_WALK) {
                            Hero.subState = 1;
                            Hero_TransAnim(4, 2, FastScaleRoundInt(8));
                            Hero.runStartBlending = 1;
                        }

                        Hero_SetTiltWobbleParams(0.016f, 0.002f, 5, 2, 1, 0);
                        break;
                    }

                    if (HeroJumpSpeeds.minRunSpeed < Hero.idealSpeed) {
                        if (Hero.onIceGround != 0 || Hero.wading != 0) {
                            Hero_InitBodyState(HERO_STATE_WALK, 1);
                            break;
                        }

                        Hero_InitBodyState(HERO_STATE_WALK, 0);

                        if (Hero.state == HERO_STATE_WALK) {
                            Hero.subState = 1;
                            Hero_TransAnim(4, HeroSlideAnimFrames[1], FastScaleRoundInt(0xC));
                        }

                        Hero_SetTiltWobbleParams(0.016f, 0.002f, 5, 2, 1, 0);
                        break;
                    }

                    if (Hero.framesNotGrounded == 0) {
                        if (Hero_InitBodyState(HERO_STATE_IDLE, 0) == 0)
                            break;
                        Hero_TransAnim(Hero_GetIdleAnim(0), 0, -2.0f);
                        Hero_SetTiltWobbleParams(0.016f, 0.002f, 5, 2, 0, 1);
                        break;
                    }

                    if (Hero_InitBodyState(HERO_STATE_IDLE, 0) == 0)
                        break;
                    Hero_TransAnim(7, 0x17, FastScaleRoundInt(9));
                    Hero_SetTiltWobbleParams(0.016f, 0.002f, 5, 2, 0, 1);
                    break;

                case HERO_STATE_JUMP:
                case HERO_STATE_RUN_JUMP:
                case HERO_STATE_HELI_PACK_FWD_JUMP:
                case HERO_STATE_FLIP_JUMP:
                case HERO_STATE_STORED_HEADING_JUMP:
                case HERO_STATE_ROCKET_JUMP:
                case HERO_STATE_DOUBLE_JUMP:
                case HERO_STATE_HELI_JUMP:
                case HERO_STATE_THRUSTER_PACK_FORWARD_JUMP:
                case HERO_STATE_WALL_JUMP:
                case HERO_STATE_WATER_JUMP:
                case HERO_STATE_LEDGE_JUMP:
                case HERO_STATE_TAKING_DAMAGE_LAVA:
                case HERO_STATE_QUICKSAND_JUMP:
                    if (Hero.canChainHighJump != 0) {
                        int jumpHoldFrames = Hero_GetJumpHoldTime();

                        if (jumpHoldFrames > 0 && (Hero.stateTimer < jumpHoldFrames || Hero.dustHoverState != 0) &&
                            Hero.framesGroundedCnt != 0) {
                            if (Hero.state != HERO_STATE_FLIP_JUMP ||
                                PadRingBitsOn(PAD_CROSS, FastScaleRoundInt(7), 0)) {
                                int holdAllowed = 1;

                                if (Hero.state == HERO_STATE_LEDGE_JUMP || Hero.dustHoverState != 0) {
                                    if (PadRingBitsOn(PAD_CROSS, FastScaleRoundInt(7), 0) == 0)
                                        holdAllowed = 0;
                                }

                                if (Hero.state == HERO_STATE_FLIP_JUMP) {
                                    if (Hero.dustHoverState == 0)
                                        holdAllowed = 0;
                                }

                                if (holdAllowed) {
                                    if (PadRingBitsOn(0x1F000, FastScaleRoundInt(5), 0)) {
                                        if (padState.bits & (PAD_R2 | PAD_R1)) {
                                            Hero_InitBodyState(HERO_STATE_FLIP_JUMP, 1);
                                            break;
                                        }
                                    }
                                }
                            }
                        }
                    }

                    if (Hero_GetGadgetMoby(3) == ITEM_THRUSTER_PACK && Hero.hasClank == 0 &&
                        Hero.state != HERO_STATE_THRUSTER_PACK_FORWARD_JUMP &&
                        Hero.state != HERO_STATE_WALL_JUMP && Hero.state != HERO_STATE_WATER_JUMP &&
                        Hero.state != HERO_STATE_TAKING_DAMAGE_LAVA && Hero.state != HERO_STATE_HELI_JUMP &&
                        Hero.state != HERO_STATE_HELI_PACK_FWD_JUMP && Hero.state != HERO_STATE_QUICKSAND_JUMP &&
                        (Hero.state == HERO_STATE_DOUBLE_JUMP || FastScaleRoundInt(9) < Hero.stateTimer) &&
                        (padState.bits & (PAD_R2 | PAD_R1))) {
                        if (PadRingBitsOn(PAD_CROSS, FastScaleRoundInt(8), 0)) {
                            Hero_InitBodyState(HERO_STATE_THRUSTER_PACK_FORWARD_JUMP, 1);
                            break;
                        }
                    }

                    if (FastScaleRoundInt(7) > Hero.stateTimer && PadRingBitsOn(PAD_R2 | PAD_R1, 2, 0) &&
                        Hero.state != HERO_STATE_THRUSTER_PACK_FORWARD_JUMP &&
                        Hero.state != HERO_STATE_HELI_PACK_FWD_JUMP && Hero.state != HERO_STATE_WATER_JUMP &&
                        Hero.state != HERO_STATE_TAKING_DAMAGE_LAVA && Hero.state != HERO_STATE_WALL_JUMP &&
                        Hero.state != HERO_STATE_DOUBLE_JUMP && Hero.state != HERO_STATE_QUICKSAND_JUMP) {
                        if (Hero_GetGadgetMoby(3) == ITEM_HELI_PACK && UnlockableItems[ITEM_HELI_PACK] != 0 &&
                            Hero.hasClank == 0 &&
                            frameTime * 0.9f < Hero.forwardSpeed) {
                            Hero_InitBodyState(HERO_STATE_HELI_PACK_FWD_JUMP, 1);
                        }

                        else if (Hero_GetGadgetMoby(3) == ITEM_THRUSTER_PACK && Hero.hasClank == 0 &&
                                   frameTime * 0.9f < Hero.forwardSpeed &&
                                   Hero.longJumpLockout == 0) {
                            Hero_InitBodyState(HERO_STATE_THRUSTER_PACK_FORWARD_JUMP, 1);
                        }
                    }

                    if (Hero.takeoffFrame + FastScaleRoundInt(8) < Hero.stateTimer &&
                        (Hero.pastJumpApex == 0 ||
                         FastScaleRoundInt(0xA) < Hero.framesToLand) &&
                        Hero.padMagnitude < 0.3f &&
                        (Hero.state == HERO_STATE_JUMP ||
                         Hero.state == HERO_STATE_RUN_JUMP || Hero.state == HERO_STATE_ROCKET_JUMP ||
                         Hero.state == HERO_STATE_HELI_JUMP || Hero.state == HERO_STATE_DOUBLE_JUMP)) {
                        if (PadRingBitsOn(PAD_R2 | PAD_R1, FastScaleRoundInt(9), 0)) {
                            if (Hero_GetGadgetMoby(3) != ITEM_THRUSTER_PACK)
                                break;
                            if (Hero.hasClank != 0)
                                break;
                            Hero_InitBodyState(HERO_STATE_ROCKET_STOMP, 1);
                            break;
                        }
                    }

                    if (Hero.jumpMaxFrames < Hero.stateTimer) {
                        if (Hero.dustHoverState == 0) {
                            Hero_InitBodyState(HERO_STATE_FALL, 1);
                            break;
                        }
                    }

                    else if (Hero.dustHoverState == 0 &&
                               (Hero.state == HERO_STATE_HELI_PACK_FWD_JUMP ||
                                Hero.state == HERO_STATE_THRUSTER_PACK_FORWARD_JUMP) &&
                               Hero.wallProbeDistance < 0.9f && Hero.wallHit != 0) {
                        if (FastVec3Length2(&Hero.velocity) > frameTime * 7.0f) {
                            float displacementLength = FastVec3Length2(&Hero.displacement);

                            if (displacementLength <
                                    FastVec3Length2(&Hero.velocity) * 0.5f &&
                                Hero.ledgeFound == 0 && Hero.groundDist < 2.0f) {
                                Hero_InitBodyState(HERO_STATE_JUMP_BOUNCE, 1);
                                break;
                            }
                        }
                    }

                    {
                        int earlyDoubleJumpAnim;

                        earlyDoubleJumpAnim = 0;

                        if (Hero.state == HERO_STATE_DOUBLE_JUMP && Hero.animFrame < 35.0f)
                            earlyDoubleJumpAnim = 1;

                        if (!(Hero.stateTimer > Hero.takeoffFrame))
                            break;
                        if (Hero.stateTimer == Hero.takeoffFrame + 1) {
                            if (Hero.velocityKeysActive != 0) {
                                float framesToKeyStart = Hero.velocityKeysStartFrame - Hero.stateTimer;

                                if (0.0f < framesToKeyStart)
                                    Hero_GetAnimFrameBlend(
                                        Hero.keyedMoveTargetFrame,
                                        framesToKeyStart,
                                        Hero.jumpAnimRetimeScale,
                                        -1.0f);
                                break;
                            }

                            if (Hero.state == HERO_STATE_DOUBLE_JUMP)
                                break;
                            Hero_GetJumpPeak(&Hero.position,
                                                      &Hero.velocity,
                                                      &predictedSteps,
                                                      Hero.jumpGravity);
                            Hero_GetAnimFrameBlend(
                                Hero.apexAnimFrame,
                                predictedSteps,
                                Hero.jumpAnimRetimeScale,
                                -1.0f);

                            if (1.5f < Hero.animSpeed)
                                Hero.animSpeed = 1.5f;
                            break;
                        }

                        if (Hero.velocityKeysActive != 0 &&
                            !(Hero.stateTimer < Hero.velocityKeysStartFrame) &&
                            Hero.stateTimer < Hero.velocityKeysEndFrame) {
                            float framesToApexAnim = Hero.keyedAnimTargetFrame - Hero.velocityKeysStartFrame;

                            if (0.0f < framesToApexAnim)
                                Hero_GetAnimFrameBlend(
                                    Hero.apexAnimFrame, framesToApexAnim, Hero.jumpAnimRetimeScale, -1.0f);
                            break;
                        }

                        if (Hero.inWaterFrames == 1) {
                            Hero_PlaySound(0x11, 0);
                            Hero_SpawnWaterSplash(3, 0x18, 1);
                        }

                        if (Hero.dustHoverState != 0)
                            Hero.dustHoverState = Hero.dustHoverState + 1;

                        else if (Hero.framesNotGrounded == 0 && Hero.pastJumpApex != 0 && !earlyDoubleJumpAnim) {
                            int landAnimFrame;

                            Hero.dustHoverState = FastScaleRoundInt(1);
                            Hero_SetTiltWobbleParams(0.016f, 0.002f, 5, 2, 0, 1);
                            landAnimFrame = FastFloatToInt(Hero.jumpLandAnimFrame) + 2;

                            if (Hero.targetAnimFrame - 1.5f > Hero.animFrame)
                                Hero_TransAnim(
                                    Hero_GetAnim(moby->animationId),
                                    landAnimFrame,
                                    FastScaleRoundInt(7));
                        }

                        if (Hero.dustHoverState != 0)
                            Hero.animSpeed = 1.0f;

                        else if (Hero.pastJumpApex != 0) {
                            if (moby->animationFrame <
                                FastFloatToInt(Hero.jumpLandAnimFrame)) {
                                if (Hero.state == HERO_STATE_DOUBLE_JUMP && Hero.animFrame < 37.0f)
                                    Delt(Hero.animSpeed, 1.0f, transStepScaleSq * 0.15f);

                                else {
                                    int jumpInterceptFrames = FastFloatToInt(
                                        Hero_PredictLand(
                                            60.0f, Hero.jumpGravity, -1.0f));
                                    Hero.framesToLand = jumpInterceptFrames;
                                    Hero_GetAnimFrameBlend(
                                        Hero.targetAnimFrame,
                                        jumpInterceptFrames,
                                        Hero.jumpAnimRetimeScale,
                                        transStepScaleSq * 0.2f);
                                }

                                if (!earlyDoubleJumpAnim) {
                                    int landAnimFrame = FastFloatToInt(Hero.jumpLandAnimFrame) + 2;

                                    if (Hero.animSpeed > 1.8f)
                                        Hero_TransAnim(Hero_GetAnim(
                                                               moby->animationId),
                                                           landAnimFrame,
                                                           Hero.framesToLand + 3);
                                }

                                if (0.2f > Hero.animSpeed)
                                    Hero.animSpeed = 0.2f;

                                if (Hero.animSpeed > 2.7f)
                                    Hero.animSpeed = 2.7f;
                            }

                            if (Hero.state == HERO_STATE_RUN_JUMP &&
                                Hero.targetAnimFrame - Hero.animFrame > 6.0f &&
                                (Hero_GetAnim(moby->updateId) == 8 ||
                                 Hero_GetAnim(moby->updateId) == 9) &&
                                moby->updateId == moby->animationId &&
                                HeroJumpSpeeds.stepSpeed * frameTime * 0.1f > Hero.idealSpeed &&
                                frameTime * 2.5f > Hero.flatSpeed) {
                                float landBlendFrames = (float)FastScaleRoundInt(9) / Hero.animSpeed;

                                if ((float)FastScaleRoundInt(0xA) < landBlendFrames)
                                    landBlendFrames = FastScaleRoundInt(0xA);
                                Hero_TransAnim(
                                    7, (FastFloatToInt(Hero.animFrame) + 4) / 2, landBlendFrames);
                                Hero.state = HERO_STATE_JUMP;
                            }

                            if (FastFloatToInt(Hero.animFrame) ==
                                FastFloatToInt(Hero.targetAnimFrame)) {
                                Hero.animSpeed = 0.0f;
                            }
                        }
                    }

                    if (Hero.dustHoverState != 0) {
                        if (Hero.state == HERO_STATE_HELI_PACK_FWD_JUMP) {
                            if (Hero_InitBodyState(HERO_STATE_SKID, 0) == 0)
                                break;
                            Hero_TransAnim(5, 0, -2.0f);
                            FastVec3Scale(&Hero.externalMomentum, &Hero.externalMomentum, 0.8f);
                            break;
                        }

                        if (Hero.onSlipGround == 0 && Hero.moveLockTimer == 0) {
                            if (PadRingBitsOn(PAD_CROSS, FastScaleRoundInt(8), 0)) {
                                if (Hero.framesNotGrounded < FastScaleRoundInt(4)) {
                                    if (Hero.idealSpeed > HeroJumpSpeeds.minRunSpeed &&
                                        FastDiffRots(Hero.idealRotZ,
                                                                          Hero.rotation.z) <
                                            1.0471976f &&
                                        HeroJumpSpeeds.stepSpeed * frameTime * 0.85f <
                                            Hero.flatSpeed) {
                                        Hero_InitBodyState(HERO_STATE_RUN_JUMP, 1);
                                        break;
                                    }

                                    Hero_InitBodyState(HERO_STATE_JUMP, 1);
                                    break;
                                }
                            }
                        }
                    }

                    if (Hero.dustHoverState > FastScaleRoundInt(1) &&
                        Hero.state != HERO_STATE_HELI_PACK_FWD_JUMP) {
                        Hero_JumpLandTransitions();
                    }

                    else if (Hero.pastJumpApex != 0 &&
                               !(Hero.fallDelayFrames > Hero.stateTimer) &&
                               Hero.groundDist > Hero.fallStartDistance) {
                        Hero_InitBodyState(HERO_STATE_FALL, 1);
                    }

                    if (Hero.state == HERO_STATE_THRUSTER_PACK_FORWARD_JUMP &&
                        FastScaleRoundInt(0x3C) < Hero.stateTimer && Hero.groundDist > 1.5f) {
                        Hero_InitBodyState(HERO_STATE_FALL, 1);
                        break;
                    }

                    {
                        int inJumpState = 0;

                        if (Hero.state == HERO_STATE_JUMP ||
                            Hero.state == HERO_STATE_RUN_JUMP ||
                            Hero.state == HERO_STATE_WALL_JUMP) {
                            inJumpState = 1;
                        }

                        if (Hero.wallJumpOk != 0 && Hero.dustHoverState == 0 && inJumpState) {
                            if (Hero.state != HERO_STATE_WALL_JUMP ||
                                FastScaleRoundInt(0x19) < Hero.stateTimer) {
                                int jumpPressWindow = FastScaleRoundInt(7);

                                if (Hero.state == HERO_STATE_WALL_JUMP)
                                    jumpPressWindow = FastScaleRoundInt(7);

                                if (PadRingBitsOn(PAD_CROSS, jumpPressWindow, &jumpPressAge)) {
                                    if (jumpPressAge < Hero.stateTimer) {
                                        Hero_InitBodyState(HERO_STATE_WALL_JUMP, 1);
                                        break;
                                    }
                                }
                            }
                        }
                    }

                    if (Hero.state == HERO_STATE_HELI_PACK_FWD_JUMP ||
                        Hero.state == HERO_STATE_THRUSTER_PACK_FORWARD_JUMP) {
                        if (FastScaleRoundInt(0x19) < Hero.stateTimer &&
                            Hero.onFlaggedGroundMoby != 0) {
                            Hero.packGlideDelay = FastScaleRoundInt(0x14);
                        }
                    }

                    {
                        int jumpPackDelay;
                        int jumpPressFrames;

                        jumpPackDelay = FastScaleRoundInt(0x14);

                        if (Hero.state == HERO_STATE_THRUSTER_PACK_FORWARD_JUMP)
                            jumpPackDelay = FastScaleRoundInt(8);

                        if (Hero.state == HERO_STATE_DOUBLE_JUMP && Hero.groundDist > 4.0f) {
                            if (Hero.pastJumpApex == 0 && Hero.animSpeed < 1.3f)
                                Delt(Hero.animSpeed, 1.3f, transStepScale * 0.1f);
                            jumpPackDelay = FastScaleRoundInt(0x11);
                            Hero.packGlideDelay = jumpPackDelay;
                        }

                        jumpPressFrames = Hero.stateTimer - 4;

                        if (jumpPressFrames < 2)
                            jumpPressFrames = 2;

                        if (FastScaleRoundInt(0x1E) < jumpPressFrames)
                            jumpPressFrames = FastScaleRoundInt(0x1E);

                        if (Hero.dustHoverState == 0 && Hero.state != HERO_STATE_WATER_JUMP &&
                            Hero.state != HERO_STATE_LEDGE_JUMP && Hero.state != HERO_STATE_WALL_JUMP &&
                            Hero.state != HERO_STATE_FLIP_JUMP &&
                            Hero.state != HERO_STATE_TAKING_DAMAGE_LAVA && Hero.state != HERO_STATE_QUICKSAND_JUMP) {
                            if (PadRingBitsOn(PAD_CROSS, jumpPressFrames, 0) || Hero.state == HERO_STATE_DOUBLE_JUMP ||
                                Hero.state == HERO_STATE_HELI_JUMP || Hero.state == HERO_STATE_ROCKET_JUMP) {
                                if (Hero.state != HERO_STATE_DOUBLE_JUMP && Hero.itemAnimActive == 0 &&
                                    (Hero.onSlipGround == 0 || !(Hero.groundDist < 0.4f)) &&
                                    Hero.canDoubleJump != 0 &&
                                    FastScaleRoundInt(0xE) < Hero.stateTimer &&
                                    (Hero.pastJumpApex == 0 ||
                                     (Hero.groundDist > 0.7f &&
                                      FastAbsF(Hero_RelativeZComponent(&Hero.velocity)) <
                                          frameTime * 5.8f))) {
                                    Hero_InitBodyState(HERO_STATE_DOUBLE_JUMP, 1);
                                }

                                else if (UnlockableItems[ITEM_HELI_PACK] != 0 && Hero_GetGadgetMoby(3) != ITEM_HYDRO_PACK &&
                                           Hero.hasClank == 0 &&
                                           (padState.bits & PAD_CROSS) &&
                                           jumpPackDelay < Hero.stateTimer &&
                                           Hero.packGlideDelay < Hero.stateTimer) {
                                    float maxGroundDistance = 0.6f;

                                    if (Hero.state == HERO_STATE_RUN_JUMP ||
                                        Hero.state == HERO_STATE_JUMP) {
                                        maxGroundDistance = 1.0f;
                                    }

                                    if (Hero.state == HERO_STATE_DOUBLE_JUMP)
                                        maxGroundDistance = 1.5f;

                                    if (maxGroundDistance < Hero.groundDist)
                                        Hero_InitBodyState(HERO_STATE_LAND, 1);
                                }
                            }
                        }
                    }

                    if (Hero.ledgeFound != 0 && Hero.state != HERO_STATE_FLIP_JUMP)
                        Hero_InitBodyState(HERO_STATE_LEDGE_GRAB, 1);
                    break;

                case HERO_STATE_GET_HIT:
                    if (12.5f < Hero.animFrame && Hero.framesNotGrounded != 0 &&
                        Hero.groundDist > 1.0f) {
                        Hero_InitBodyState(HERO_STATE_FALL, 1);
                        break;
                    }

                    if (Hero.stateTimer > FastScaleRoundInt(0x1B)) {
                        if (Hero.health <= 0) {
                            Hero_InitBodyState(HERO_STATE_DEATH, 1);
                            break;
                        }

                        if (Hero.prevState == HERO_STATE_ROCKET_HOVER) {
                            Hero_InitBodyState(HERO_STATE_ROCKET_HOVER, 1);
                            break;
                        }

                        Hero_InitBodyState(HERO_STATE_IDLE, 0);
                    }
                    break;

                case HERO_STATE_HOLOGUISE_STANDING:
                    if (Hero.animFlags & 2) {
                        if (Hero.moby->animationId != 0)
                            Hero_TransAnim(0, 0, FastScaleRoundInt(0xC));

                        else if (MB_randRangeFloat(0.0f, 1.0f) < 0.5f)
                            Hero_TransAnim(5, 0, FastScaleRoundInt(8));
                    }

                    if (padState.bits & (PAD_L2 | PAD_L1)) {
                        Hero_InitBodyState(HERO_STATE_LOOK, 1);
                        break;
                    }

                    if (Hero.framesNotGrounded != 0) {
                        Hero_InitBodyState(HERO_STATE_HOLOGUISE_FALLING, 1);
                        break;
                    }

                    if (padState.bitsOn & PAD_CIRCLE) {
                        Hero_InitBodyState(HERO_STATE_HOLOGUISE_WAVE, 1);
                        break;
                    }

                    if (PadRingBitsOn(PAD_SQUARE, FastScaleRoundInt(7), 0)) {
                        if (Hero.vehicleToggleTimer == 0) {
                            Hero_PlaySound(0x19, 0);
                            Hero.vehicleToggleTimer = 0x12;
                            Hero.scalePulseStep = 1;
                        }

                        Hero_HandleGadgetSwitching(0);
                        break;
                    }

                    Hero_GetIdealThrustFromPad(1.0f, 0);

                    if (Hero.padMagnitude > 0.22f && Hero.idealSpeed > 0.0f)
                        Hero_InitBodyState(HERO_STATE_HOLOGUISE_WALKING, 1);
                    break;

                case HERO_STATE_HOLOGUISE_SLIP:
                    if (FastScaleRoundInt(0x12C) < Hero.stateTimer)
                        HandleHeroDeath();

                    if (Hero.onSlipGround != 0)
                        break;
                    if (Hero.framesNotGrounded != 0) {
                        Hero_InitBodyState(HERO_STATE_HOLOGUISE_FALLING, 1);
                        break;
                    }

                    Hero_InitBodyState(HERO_STATE_HOLOGUISE_STANDING, 1);
                    break;

                case HERO_STATE_HOLOGUISE_WAVE:
                    if (Hero.stateTimer > FastScaleRoundInt(0x2D) &&
                        !(padState.bits & PAD_CIRCLE)) {
                        Hero_InitBodyState(HERO_STATE_HOLOGUISE_STANDING, 0);
                        Hero_TransAnim(0, 0, FastScaleRoundInt(0x14));
                    }
                    break;

                case HERO_STATE_HOLOGUISE_FALLING:
                    if (Hero.framesNotGrounded != 0)
                        break;
                    if (frameTime * -9.0f > Hero.displacement.z)
                        Hero.displacement.z = frameTime * -9.0f;

                    if (frameTime * -9.0f > Hero.velocity.z)
                        Hero.velocity.z = frameTime * -9.0f;

                    if (Hero.health <= 0) {
                        Hero_InitBodyState(HERO_STATE_HOLOGUISE_DYING, 1);
                        break;
                    }

                    if (Hero.padMagnitude > 0.5f && FastScaleRoundInt(0x28) > Hero.stateTimer &&
                        Hero.moveLockTimer == 0) {
                        Hero_InitBodyState(HERO_STATE_HOLOGUISE_WALKING, 1);
                        break;
                    }

                    Hero_InitBodyState(HERO_STATE_HOLOGUISE_STANDING, 0);
                    Hero_TransAnim(7, 0, -1.0f);
                    Hero.animSpeed = 0.35f;
                    Hero.moveLockTimer = FastScaleRoundInt(0x14);
                    break;

                case HERO_STATE_HOLOGUISE_WALKING:
                    Hero.animSpeed = Hero.speedXY * 54.0f;

                    if (!(Hero.framesNotGrounded < FastScaleRoundInt(5))) {
                        if (Hero.groundDist > 0.8f || Hero.groundSlope > 0.87266463f) {
                            Hero_InitBodyState(HERO_STATE_HOLOGUISE_FALLING, 1);
                            break;
                        }
                    }

                    if (PadRingBitsOn(PAD_SQUARE, FastScaleRoundInt(7), 0)) {
                        if (Hero.vehicleToggleTimer == 0) {
                            Hero_PlaySound(0x19, 0);
                            Hero.vehicleToggleTimer = 0x12;
                            Hero.scalePulseStep = 1;
                        }

                        Hero_HandleGadgetSwitching(0);
                        break;
                    }

                    if (padState.bitsOn & PAD_CIRCLE) {
                        Hero_InitBodyState(HERO_STATE_HOLOGUISE_WAVE, 1);
                        break;
                    }

                    if (Hero.framesNotGrounded == 0 && Hero.padMagnitude < 0.17f)
                        Hero_InitBodyState(HERO_STATE_HOLOGUISE_STANDING, 1);
                    break;

                case HERO_STATE_HOLOGUISE_DAMAGE:
                    if (!(Hero.stateTimer < FastScaleRoundInt(0x20)) && Hero.framesNotGrounded != 0 &&
                        Hero.groundDist > 1.0f) {
                        Hero_InitBodyState(HERO_STATE_HOLOGUISE_FALLING, 1);
                        break;
                    }

                    if (Hero.animFlags & 2) {
                        Hero_InitBodyState(HERO_STATE_HOLOGUISE_STANDING, 1);
                        break;
                    }

                    if (FastScaleRoundInt(0x2D) < Hero.stateTimer) {
                        if (Hero.health <= 0) {
                            Hero_InitBodyState(HERO_STATE_HOLOGUISE_DYING, 1);
                            break;
                        }

                        Hero_InitBodyState(HERO_STATE_HOLOGUISE_STANDING, 0);
                    }
                    break;

                case HERO_STATE_WEAPON_FIRST_PERSON_VIEW:
                    if (Hero.type == HERO_TYPE_RATCHET) {
                        if (Hero.weaponUp == 0 || Hero.invisible != 0) {
                            if (padState.bits & (PAD_R2 | PAD_R1)) {
                                if (Hero.moby->animationId != 0xD)
                                    Hero_TransAnim(0xD, 0, FastScaleRoundInt(8));
                            }

                            else {
                                int idleAnimation = Hero_GetIdleAnim(1);

                                if (Hero.moby->animationId != idleAnimation)
                                    Hero_TransAnim(idleAnimation, 0, FastScaleRoundInt(8));
                            }
                        }
                    }

                    if (padState.bits & (PAD_L2 | PAD_L1))
                        break;
                    if (Hero.state == HERO_STATE_WEAPON_FIRST_PERSON_VIEW) {
                        int idleAnimation;

                        Hero_InitBodyState(HERO_STATE_IDLE, 0);
                        idleAnimation = Hero_GetIdleAnim(1);

                        if (Hero.moby->animationId != idleAnimation)
                            Hero_TransAnim(idleAnimation, 0, FastScaleRoundInt(8));
                    }

                    ScreenColorEffectDefault.enabled = 0;
                    break;

                case HERO_STATE_WALLOPER_ATTACK:
                    if (Hero.items[0].moby != 0 && Hero.animChanging == 0 &&
                        Hero.animFrame > 20.0f) {
                        Hero_InitBodyState(HERO_STATE_IDLE, 0);
                    }
                    break;

                case HERO_STATE_THROWING_ITEM:
                    if (19.0f < Hero.animFrame &&
                        PadRingBitsOn(PAD_CROSS, FastScaleRoundInt(0xB), 0)) {
                        if (padState.bits & (PAD_R2 | PAD_R1)) {
                            Hero_CrouchJumpTransitions();
                            break;
                        }

                        Hero_InitBodyState(HERO_STATE_JUMP, 1);
                        break;
                    }

                    if (21.0f <= Hero.animFrame)
                        Hero_InitBodyState(HERO_STATE_IDLE, 0);
                    break;
                }
            }
        }
    }

    if (previousStateType != Hero.stateType)
        Hero_KillLoopingSounds();

    if ((Hero.prevState == HERO_STATE_FIDGET && Hero.state != HERO_STATE_FIDGET_ALT) ||
        (Hero.prevState == HERO_STATE_FIDGET_ALT && Hero.fidgetPropMoby != 0)) {
        Hero_CleanupAttachedMobys();
    }

    if (previousSubState != Hero.subState)
        Hero.stepFrames = 0;

    if (previousAnimation != moby->animationId)
        Hero.animSeqFrames = 0;
}


INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_PlayBackpackIdleAnim);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_GetBackpackAnimTable);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_TransBackpackAnim);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_GetBackpackAnim);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_SyncBackpackAnimSpeed);

void Hero_ClearBoardMoby(void)
{
    Hero.animLinkMoby = 0;
    Hero.animLinkTable = 0;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_GetBoardAnim);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_TransBoardAnim);

int Hero_GetBoardAnim(int animation, int *boardAnimation);

void Hero_SyncBoardAnimSpeed(void)
{
    int boardAnimation;

    if (Hero.animLinkMoby && Hero.animLinkTable && Hero_GetBoardAnim(Hero.moby->animationId, &boardAnimation))
        Hero.animLinkMoby->animIScale = Hero.animSpeed;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_SyncBoardAnimFrame);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_TransAnim);

void UpdateMobyFrameData(MobyInstance *moby);

void Hero_SnapAnim(int animation, int frame)
{
    MobyInstance *moby = Hero.moby;

    moby->animationFrame = frame + 1;
    moby->updateId = animation;
    moby->animationId = animation;
    moby->previousAnimationFrame = frame;
    moby->animationBlend = 0.0f;

    UpdateMobyFrameData(moby);
}

void Hero_SetNextAnimFrame(int animation, int frame)
{
    if (animation >= 0) {
        MobyInstance *moby = Hero.moby;
        if (frame < moby->pClass->animations[moby->animationId]->frameCount) {
            Hero.nextAnimation = animation;
            Hero.nextAnimationFrame = frame;
        }
    }
}

void Hero_ClearNextAnim(void)
{
    Hero.nextAnimation = -1;
    Hero.queuedFrameRequest = 0;
}

void Hero_SetNextAnimBlend(int frames)
{
    if (frames == -1)
        frames = FastScaleRoundInt(5);

    Hero.queuedFrameRequest = frames;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_UpdateAnim);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", func_00248264);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_PredictLand);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_MakeInvisible);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_MakeVisible);

enum { HERO_MOBY_HIDDEN = 1 };

void Hero_HideHeroMoby(void)
{
    Hero.moby->modeBits |= HERO_MOBY_HIDDEN;
}

void Hero_ShowHeroMoby(void)
{
    Hero.moby->modeBits &= ~HERO_MOBY_HIDDEN;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", func_00248918);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_SetTiltWobbleParams);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_GetThrustRelativeToGravity);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_GetSpecialPadState);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_AddGravity);

void FastVecZero(Vec4 *vector);
void FastTransformVec4(Vec4 *out, Vec4 *in, Mtx4 *matrix);
void FastVec3Add(Vec4 *out, Vec4 *first, Vec4 *second);

void Hero_GetPolarOffset(Vec4 *out, float x, float y, float z)
{
    out->x = FastAngleSinF(y) * x;
    out->y = FastAngleCosF(y) * x;
    out->z = z;

    FastTransformVec4(out, out, &Hero.mtx);
    FastVec3Add(out, out, &Hero.position);
}

void FastVecZero(Vec4 *vector);
void FastTransformVec4(Vec4 *out, Vec4 *in, Mtx4 *matrix);
void FastVec3Add(Vec4 *out, Vec4 *first, Vec4 *second);

void Hero_GetHeroRelativePos(Vec4 *out, float x, float y, float z)
{
    FastVecZero(out);
    out->x = x;
    out->y = y;
    out->z = z;

    FastTransformVec4(out, out, &Hero.mtx);
    FastVec3Add(out, out, &Hero.position);
}

void Hero_AddGravity(float amount, float *out, float *in);

void Hero_SubGravity(float amount, float *out, float *in)
{
    Hero_AddGravity(-amount, out, in);
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_ToWorldVector);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_ToWorldPos);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_ForwardComponent);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_RelativeXYLength);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_RelativeZComponent);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_ToHeroRelative);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_SetRelativeZ);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_GetJumpPeak);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_RelativeZAngle);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", hero_ConsumeAmmo);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", hero_GiveAmmo);

int Hero_GetWeaponAmmo(int item)
{
    if (item == -1)
        item = Hero.items[0].itemId;

    if (!VendorPrices[item].maxAmmo)
        return 1;

    return WeaponAmmo[item];
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_StartHit);

int Hero_GetSpecialStateKind(void)
{
    switch (Hero.state) {
    case HERO_STATE_WALK_TO_POS:
    case HERO_STATE_SKID_TO_POS:
        return 1;
    case HERO_STATE_IDLE_TO_POS:
        return 2;
    default:
        return 0;
    }
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_MoveWithPlatform);

int MB_CollideSplineWall(int spline, float radius, Vec4 *position, Vec4 *out);

void Hero_CollideSplineWall(void)
{
    if (MB_CollideSplineWall(Hero.splineWall, Hero.collRadius, &Hero.position, &Hero.position))
        Hero.splineWallHitTimer = 4;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_UpdateManipulatorSpin);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_UpdateGadgetsInScene);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_UpdateInScene);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_SnapMobyToBonePose);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", SetPositionAfterMovie);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_RegisterHealthHud);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_FindHudEntry);
