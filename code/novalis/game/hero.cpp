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
#include "camera.h"

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

void Hero_SetTweaker0(float gain, float damp)
{
    HeroTweaks[0].gain = gain;
    HeroTweaks[0].damp = damp;
}

void Hero_SetTweaker1(float gain, float damp)
{
    HeroTweaks[1].gain = gain;
    HeroTweaks[1].damp = damp;
}

void Hero_SetTweaker2(float gain, float damp)
{
    HeroTweaks[2].gain = gain;
    HeroTweaks[2].damp = damp;
}

void Hero_SetTweaker3(float gain, float damp)
{
    HeroTweaks[3].gain = gain;
    HeroTweaks[3].damp = damp;
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

// Jump tables and data of the gadget helpers that are not decompiled yet. They sit in the same .rodata
// piece as the jump table of Hero_DoBehavior.
extern const unsigned int HeroUpdateGadgetGlowsJumpTable[8] __attribute__((section(".rodata"), aligned(16))) = {
    0x00229E30, 0x00229EF4, 0x00229EF4, 0x00229A48, 0x00229904, 0x00229EF4, 0x00229B98,
    0x00229CB8
};

extern const int HeroJoint9Gadgets[12] __attribute__((section(".rodata"), aligned(16))) = {
    0, 1, 2, 3, 4, 5, 6,
    29, 30, 0, 0, 0
};

extern const unsigned int HeroGetGadgetAnimBlendJumpTable[84] __attribute__((section(".rodata"), aligned(16))) = {
    0x0022DF5C, 0x0022DF5C, 0x0022DF90, 0x0022DF5C, 0x0022DF90, 0x0022DF90, 0x0022DF90,
    0x0022DF90, 0x0022DF90, 0x0022DF90, 0x0022DF90, 0x0022DF90, 0x0022DF90, 0x0022DF90,
    0x0022DF90, 0x0022DF90, 0x0022DF90, 0x0022DF90, 0x0022DF90, 0x0022DF90, 0x0022DF90,
    0x0022DF54, 0x0022DF54, 0x0022DF90, 0x0022DF90, 0x0022DF90, 0x0022DF90, 0x0022DF3C,
    0x0022DF90, 0x0022DF90, 0x0022DF90, 0x0022DF90, 0x0022DF90, 0x0022DF90, 0x0022DF90,
    0x0022DF90, 0x0022DF90, 0x0022DF90, 0x0022DF90, 0x0022DF90, 0x0022DF90, 0x0022DF90,
    0x0022DF90, 0x0022DF90, 0x0022DF90, 0x0022DF90, 0x0022DF54, 0x0022DF54, 0x0022DF90,
    0x0022DF90, 0x0022DF90, 0x0022DF90, 0x0022DF54, 0x0022DF90, 0x0022DF90, 0x0022DF90,
    0x0022DF90, 0x0022DF90, 0x0022DF90, 0x0022DF90, 0x0022DF90, 0x0022DF90, 0x0022DF90,
    0x0022DF90, 0x0022DF90, 0x0022DF90, 0x0022DF90, 0x0022DF90, 0x0022DF54, 0x0022DF90,
    0x0022DF90, 0x0022DF90, 0x0022DF90, 0x0022DF90, 0x0022DF90, 0x0022DF90, 0x0022DF90,
    0x0022DF90, 0x0022DF90, 0x0022DF90, 0x0022DF90, 0x0022DF54, 0x0022DF54, 0x00000000
};

extern const unsigned int HeroSetGadgetSwitchTimerAJumpTable[16] __attribute__((section(".rodata"), aligned(16))) = {
    0x002306F4, 0x00230710, 0x002306F4, 0x00230710, 0x002306F4, 0x00230710, 0x00230710,
    0x002306F4, 0x00230710, 0x00230710, 0x00230710, 0x00230710, 0x00230710, 0x00230710,
    0x002306F4, 0x00000000
};

extern const unsigned int HeroSetGadgetSwitchTimerBJumpTable[20] __attribute__((section(".rodata"), aligned(16))) = {
    0x00230750, 0x00230760, 0x00230750, 0x00230760, 0x00230750, 0x00230750, 0x00230750,
    0x00230750, 0x00230760, 0x00230750, 0x00230750, 0x00230760, 0x00230760, 0x00230750,
    0x00230750, 0x00230760, 0x00230760, 0x00230750, 0x00000000, 0x00000000
};

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
void Hero_GetIdealThrustFromPad(float scale, int mode);
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

// Callees of Hero_DoBehavior.
void Hero_SpawnWaterRings(int first, int second);
void Hero_SpawnWaterWake(int first, int second);
void Hero_SpawnWaterDrops(int first, int second);
void Hero_SpawnWaterBubbles(int first, int second);
void Hero_ThrustToMotion(float scale, float step);
void Hero_EdgeStop(float first, float second);
int FastDecTimer_220e78(int *timer);
int FastDecTimer_220ea8(short *timer);
void Hero_GunTurnWalk(void);
void Hero_TurnWalk(void);
float Hero_GetAnimFrameBlend(float a, float b, float c, float d);
void Hero_ApplyFriction(float amount);
void Hero_AddGravity(Vec4 *out, Vec4 *vector, float scale);
void Hero_SubGravity(float scale, Vec4 *out, Vec4 *vector);
void Hero_KneeBumpMotion(int mode);
void Hero_WallSloopMotion(void);
void Hero_ThrustToMotionFwd(float speed);
void Hero_SurfBob(void);
void Hero_SetBankTwistSway(void);
void Hero_SetBackpackSway(void);
void Hero_JumpTranslation(float amount);
void Hero_JumpThrustGrav(void);
void Hero_JumpTurnTrans(void);
void Hero_UpdateLedge(void);
void Hero_CheckLedgeGrab(void);
void Hero_ThrowWrench(void);
void Hero_JumpOrSnapJumpCheck(int first, int second);
void Hero_ToWorldVector(Vec4 *out, Vec4 *vector, float scale);
void Hero_ToWorldPos(Vec4 *out, Vec4 *vector, float scale);
float Hero_SinCosDot(Vec4 *vector);
void Hero_SetRelativeZ(Vec4 *out, Vec4 *vector, float z);
void Hero_ForwardComponent(Vec4 *out, Vec4 *vector);
float Hero_RelativeZComponent(Vec4 *vector);
float Hero_GetLoopedAnimFrame(float *table, int frames);
void Hero_GetIdealThrustForWalk(void);
float FastVec3DistLen(Vec4 *from, Vec4 *to);
void FastSubVec3(Vec4 *out, Vec4 *minuend, Vec4 *subtrahend);
float FastVec3Dot(Vec4 *first, Vec4 *second);
void FastVec3Normalize(Vec4 *out, Vec4 *vector, float length);
int FastVecNormalizeScaled(float scale, Vec4 *out, Vec4 *vector);
float FastSubRots(float first, float second);
float FastDiffRots(float first, float second);
float FastVec3Length(Vec4 *vector);
int CollMobySphere(float radius, Vec4 *center, int flags, MobyInstance *ignore, COLL_DAM_IN *damage);
int CollLine(Vec4 *start, Vec4 *end, int flags, MobyInstance *ignore, MobyInstance *ignoreSecond);
void CollDamageMobyDirect_2(MobyInstance *target, MobyInstance *damager, int damageFlags, Vec4 *position, Vec4 *momentum, float damageHp);
int SpawnPart_034(Vec4 *position, Vec4 *velocity, float first, float second);
void *SpawnPart_047(Vec4 *position, Vec4 *velocity, float scale);
void UpdateMotionBlur(MotionBlur *blur, int count);




extern float transStepScaleSq;
extern float HeroYawReference[];
extern HeroJumpSpeedTweaks HeroJumpSpeeds;
extern MobyInstance *HeroSphereQueryResults[];
extern float HeroSwimSpeedWeights[];
extern float HeroLedgeShimmySpeeds[];

// Stack scratch space shared by the states of Hero_DoBehavior; each state views it as its own set
// of vectors.
union HeroDoBehaviorScratch {
    Vec4 vectors[6];
    struct {
        Vec4 cameraAxis;
    } look;
    struct {
        Vec4 bonePos;
        Vec4 velocity;
        Vec4 offset;
    } particle;
    struct {
        Vec4 hitPos;
        Vec4 hitDirection;
        Vec4 unused;
        COLL_DAM_IN hit;
    } rocketStomp;
    struct {
        Vec4 hitPos;
        COLL_DAM_IN hit;
        Vec4 hitDirection;
    } jumpAttack;
    struct {
        COLL_DAM_IN hit;
        Vec4 hitDirection;
        Vec4 hitPos;
    } walloper;
    struct {
        Vec4 impulse;
    } wade;
    struct {
        Vec4 bubblePos;
        Vec4 bubbleVelocity;
    } slide;
    struct {
        Vec4 grabA;
        Vec4 grabB;
        Vec4 position;
        Vec4 offsetPosition;
        Vec4 sideStep;
        Vec4 midpoint;
    } ledge;
    struct {
        Vec4 start;
        Vec4 end;
    } jumpProbe;
    struct {
        Vec4 center;
        Vec4 shove;
    } crateSmash;
    struct {
        Vec4 toTarget;
    } walk;
    struct {
        Vec4 toTarget;
    } skid;
};

void Hero_DoBehavior(void)
{
    HeroDoBehaviorScratch scratch;
    MobyInstance *moby;
    int prevState;
    int prevAnim;
    int fast;
    Vec4 *heroVelocity;

    moby = Hero.moby;
    prevState = Hero.subState;
    prevAnim = moby->animationId;

    switch (Hero.state) {
    case HERO_STATE_IDLE:
    case HERO_STATE_LOOK:
    case HERO_STATE_SKID:
    case HERO_STATE_CROUCH:
    case HERO_STATE_ITEM_BUTTON_RELEASE_WAIT:
    case HERO_STATE_VISIBOMB:
    case HERO_STATE_WEAPON_FIRST_PERSON_VIEW:
    case HERO_STATE_ACTIVATE_SONIC_SUMMONER_MOUSE:
    case HERO_STATE_DEATH:
    case HERO_STATE_MAGNE_ATTACK:
    case HERO_STATE_MAGNE_JUMP:
    case HERO_STATE_CUT_SCENE:
    case HERO_STATE_ELECTRIC_DEATH: {
        float speed;

        if (Hero.wading != 0)
            Hero_SpawnWaterRings(0xF, 0x1E);

        Hero_ThrustToMotion(0.5f, frameTime * 2.0f);
        Hero_EdgeStop(3.7f, 0.0f);
        Hero_GetIdealThrustFromPad(1.0f, 0);

        if (Hero.state == HERO_STATE_LOOK || Hero.state == HERO_STATE_WEAPON_FIRST_PERSON_VIEW) {
            if (Hero.invisible != 0) {
                ClearVec4(&scratch.look.cameraAxis);
                scratch.look.cameraAxis.x = 1.0f;
                FastVecMtx3Mult(&Hero.moveDirection, &scratch.look.cameraAxis,
                                (Mtx4 *)&GameCamera.orientMtx);
                Hero.idealRotZ = GameCamera.rot.radius;
                Hero_Turn(transStepScaleSq, transStepScaleSq * 0.0f, frameTime * 174.53293f, 0);

                if (HelpHintTimer > 0) {
                    if (FastDecTimer_220e78(&HelpHintTimer)) {
                        if (ActionUsageStats[18].count < 0xFFFF)
                            ActionUsageStats[18].count++;

                        if (FastScaleRoundInt(TotalPlayTime) / 600 >
                            ActionUsageStats[18].latestTimeBucket)
                            ActionUsageStats[18].latestTimeBucket =
                                FastScaleRoundInt(TotalPlayTime) / 600;

                        ActionUsageStats[18].levelMask =
                            ActionUsageStats[18].levelMask | (1 << Level) | 0x80000000;
                        HelpHintTimer = -1;
                        HeroSdata15F68C++;
                    }
                }
            }
        }

        if (Hero.state == HERO_STATE_SKID) {
            if (Hero_CheckGadgetReady() != 0)
                break;
        }

        if (Hero.state == HERO_STATE_CROUCH || Hero.state == HERO_STATE_ITEM_BUTTON_RELEASE_WAIT) {
            if (Hero.padMagnitude > 0.2f || Hero.moby->animationId == HERO_ANIM_CROUCH_MOVE_RIGHT ||
                Hero.moby->animationId == HERO_ANIM_CROUCH_MOVE_LEFT) {
                if (Hero.state == HERO_STATE_CROUCH)
                    Hero_Turn(transStepScaleSq * 0.002f, transStepScaleSq * 0.07f,
                              frameTime * 6.981317f, 0);

                else if (Hero.state == HERO_STATE_ITEM_BUTTON_RELEASE_WAIT)
                    Hero_GunTurnWalk();

                if (FastAbsF(Hero.turnSpeed) > frameTime * 0.34906584f) {
                    int neg;
                    int anim;

                    neg = 1;

                    if (!(Hero.turnSpeed < 0.0f))
                        neg = 0;

                    anim = neg + HERO_ANIM_CROUCH_MOVE_RIGHT;

                    if (Hero.moby->animationId != anim)
                        Hero_TransAnim(anim, 0, FastScaleRoundInt(5));

                    Hero.animSpeed = FastAbsF(Hero.turnSpeed) / (frameTime * 3.3161256f);

                    if (Hero.animSpeed < 0.55f)
                        Hero.animSpeed = 0.55f;

                    if (Hero.animSpeed > 2.5f)
                        Hero.animSpeed = 2.5f;
                }

                else if (Hero.turnSpeed == 0.0f) {
                    int anim;

                    anim = HERO_ANIM_CROUCH;

                    if (Hero.state == HERO_STATE_ITEM_BUTTON_RELEASE_WAIT)
                        anim = Hero_GetIdleAnim(0);

                    if (Hero.moby->animationId != anim)
                        Hero_TransAnim(anim, 0, FastScaleRoundInt(7));
                }
            }
        }

        Hero.idealSpeed = 0.0f;

        if (Hero.state == HERO_STATE_SKID) {
            float slopeScale;

            slopeScale = Hero.moveSlope + 1.0f;

            if (slopeScale > 1.0f)
                slopeScale = 1.0f;

            speed = frameTimeSq * 12.0f * slopeScale;
            Hero.skidDecel = speed;

            if (Hero.moby->updateId == Hero.moby->animationId && Hero.moby->updateId != HERO_ANIM_SLIDE) {
                float animRatio;

                animRatio = Hero.flatSpeed / speed;

                if (FastScaleRoundInt(5) < animRatio && Hero.moby->animationFrame < 5.5f) {
                    Hero_GetAnimFrameBlend(13.0f, animRatio, 0.5f, -1.0f);

                    if (Hero.animSpeed > 1.1f)
                        Hero.animSpeed = 1.1f;
                }

                else if (Hero.moby->animationFrame > 6.5f)
                    Hero.animSpeed = 1.0f;
            }
        }

        else {
            if (Hero.state == HERO_STATE_CROUCH)
                speed = frameTimeSq * 6.48f;

            else
                speed = frameTimeSq * 12.6f;
        }

        Hero_ThrustModeAccel(0.0f, speed);
        FastVecZero(&Hero.velocity);
        Hero_ApplyFriction(speed);

        if (Hero.onMagnetGround != 0 && UnlockableItems[ITEM_MAGNEBOOTS] != 0) {
            if (Hero.groundDist > 0.2f)
                Hero_AddGravity(&Hero.velocity, &Hero.resolvedVelocity, frameTimeSq * 24.0f);

            else {
                Hero_AddGravity(&Hero.velocity, &Hero.velocity, frameTimeSq * 54.0f);

                if (Hero.standingOnMoby != 0) {
                    CopyVec4Inline(&Hero.position, &Hero.groundPoint);
                    Hero.groundDist = 0.0f;
                    Hero.framesNotGrounded = 0;
                }
            }
        }

        else {
            Hero_KneeBumpMotion(0);

            if (Hero.framesNotGrounded != 0) {
                Hero_AddGravity(&Hero.velocity, &Hero.resolvedVelocityZ, frameTimeSq * 25.0f);
                Hero_WallSloopMotion();
            }

            else
                Hero_AddGravity(&Hero.velocity, &Hero.velocity, frameTimeSq * 54.0f);
        }
    } break;
    case HERO_STATE_ICEWATER_FREEZE:
        if (Hero.sinkEffectMoby == 0) {
            MobyInstance *itemMoby;

            itemMoby = CreateMoby(0x52A);
            Hero.sinkEffectMoby = itemMoby;

            if (Hero.sinkEffectMoby != 0) {
                CopyVec4Inline(&itemMoby->pos, &Hero.position);
                CopyVec4Inline(&itemMoby->rotation, &Hero.rotation);
                itemMoby->drawDistance = 0x40;
                Hero.sinkEffectMoby->enabled = 1;
                Hero.sinkEffectMoby->updateDistance = 0;
                Hero.sinkEffectMoby->alpha = 0;
                Hero.sinkEffectMoby->modeBits |= 0x800;
                PostUpdateMoby(Hero.sinkEffectMoby);
                sound_PlayMobySound(0, 0, Hero.sinkEffectMoby);
            }
        }

        if (Hero.sinkEffectMoby != 0) {
            Hero.sinkEffectMoby->alpha += FastFloatToInt(transStepScale * 5.0f);

            if (Hero.sinkEffectMoby->alpha > 0x80)
                Hero.sinkEffectMoby->alpha = 0x80;

            {
                MobyInstance *sinkFollowerMoby = Hero.sinkEffectMoby;
                MobyInstance *heroMoby = Hero.moby;

                CopyVec4Inline(&sinkFollowerMoby->pos, &heroMoby->pos);
                CopyVec4Inline(&sinkFollowerMoby->rotation, &heroMoby->rotation);
                PostUpdateMoby(sinkFollowerMoby);
            }
        }

        Hero.velocity.z = 0.0f;
        {
            float len;

            len = FastVec3Length(&Hero.velocity);
            FastVecNormalizeScaled(transStepScale * -0.07999998f * len + len, &Hero.velocity,
                                   &Hero.velocity);
        }

        Hero_SurfBob();
        break;
    case HERO_STATE_SWIMUNDER:
    case HERO_STATE_IDLEUNDER:
    case HERO_STATE_CHARGEUNDER: {
        float lim;
        float turn;
        float trig;
        float bankDamping;
        float bankSpring;
        float old;
        float roll;
        float swimVelocityPitch;
        float lean;

        if (Hero.state == HERO_STATE_CHARGEUNDER)
            Hero_PlayLoopSound(5, Hero.moby, 0x13);

        else {
            if (Hero.loopSounds[5] != -1) {
                SoundVoice *voiceRow = &audioState.rows[Hero.loopSounds[5]];

                if (voiceRow[1].pMoby == Hero.moby) {
                    if (voiceRow[1].inUse != 0)
                        sound_KillChannel(Hero.loopSounds[5]);
                }
            }

            Hero.loopSounds[5] = -1;
        }

        if (Hero.splashEffectTimer != 0) {
            int bubbleCount;

            FastDecTimer_220ea8(&Hero.splashEffectTimer);
            bubbleCount = Hero.splashEffectTimer >> 2;

            if (bubbleCount > 8)
                bubbleCount = 8;

            Hero_SpawnWaterBubbles(bubbleCount, 0);
        }

        if (Hero.state == HERO_STATE_SWIMUNDER && Hero.animChanging == 0) {
            if (Hero.animFrame > 0.0f && Hero.animFrame < 10.0f)
                Hero_SpawnWaterBubbles(4, 1);
        }

        if (Hero.state == HERO_STATE_IDLEUNDER && Hero.prevState == HERO_STATE_CHARGEUNDER &&
            Hero.stateTimer < FastScaleRoundInt(0xF))
            Hero_SpawnWaterBubbles((FastScaleRoundInt(0x14) - Hero.stateTimer) / 3 + 1, 1);

        if (Hero.subState == 1) {
            if (Hero.stateTimer == 1) {
                Hero_SpawnWaterSplash(3, 0x10, 0);

                if (WaterTiles != 0)
                    WaterTile_PutDrop(WaterTiles, WaterTileCnt, 0, Hero.position.x, Hero.position.y,
                                      0.4f, -0.3f);

                Hero.splashEffectTimer = FastScaleRoundInt(0x46);
            }

            if (++Hero.swimEntryFrames > FastScaleRoundInt(0x28))
                Hero.subState = 0;
        }

        lim = frameTime * 0.6981317f;
        turn = 0.0f;
        trig =
            padState.analog[10] < padState.analog[11] ? padState.analog[11] : padState.analog[10];
        bankDamping = transStepScaleSq * 0.2f;
        bankSpring = transStepScaleSq * 0.015f;
        lim = lim + (frameTime * 1.2217305f - lim) * trig;

        if (((padState.bits & PAD_SQUARE) && !(padState.bits & PAD_CROSS)) || Hero.subState == 1) {
            float turnStrength;

            turnStrength = padState.analog[11] * 1.5f;

            if (turnStrength > 1.0f)
                turnStrength = 1.0f;

            if (turnStrength < 0.2f)
                turnStrength = 0.2f;

            if (padState.term_id != 0x79) {
                Hero.cwTurnFrames = 0;
                Hero.swimSquareHoldFrames++;
                turnStrength = Hero.swimSquareHoldFrames * 0.5f / FastScaleRoundInt(0x14) + 0.5f;

                if (turnStrength > 1.0f)
                    turnStrength = 1.0f;
            }

            if (Hero.subState == 1 && turnStrength < 0.35f)
                turnStrength = 0.35f;

            turn = turnStrength * 1.3613569f;
        }

        else if (padState.bits & PAD_CROSS) {
            float turnStrength;

            turnStrength = padState.analog[10] * 1.5f;

            if (turnStrength > 1.0f)
                turnStrength = 1.0f;

            if (turnStrength < 0.2f)
                turnStrength = 0.2f;

            if (padState.term_id != 0x79) {
                Hero.swimSquareHoldFrames = 0;
                Hero.cwTurnFrames++;
                turnStrength = Hero.cwTurnFrames * 0.5f / FastScaleRoundInt(0x14) + 0.5f;

                if (turnStrength > 1.0f)
                    turnStrength = 1.0f;
            }

            if (Hero.oxygen < 1500.0f)
                turnStrength = 1.0f;

            turn = turnStrength * -1.3613569f;
        }

        else {
            Hero.cwTurnFrames = 0;
            Hero.swimSquareHoldFrames = 0;
        }

        if (padState.bits & PAD_CROSS) {
            Hero.jumpButtonFrames++;

            if (padState.analog[10] > 0.75f) {
                if (++Hero.swimHardPressFrames > FastScaleRoundInt(0x5A)) {
                    if (ActionUsageStats[11].count < 0xFFFF)
                        ActionUsageStats[11].count++;
                }

                if (FastScaleRoundInt(TotalPlayTime) / 600 >
                    ActionUsageStats[11].latestTimeBucket)
                    ActionUsageStats[11].latestTimeBucket = FastScaleRoundInt(TotalPlayTime) / 600;

                ActionUsageStats[11].levelMask =
                    ActionUsageStats[11].levelMask | (1 << Level) | 0x80000000;
            }

            else
                Hero.swimHardPressFrames = 0;
        }

        else {
            Hero.jumpButtonFrames = 0;
            Hero.swimHardPressFrames = 0;
        }

        if (padState.bitsOn & PAD_CROSS) {
            if (worldUpdateTime - Hero.lastCrossPressFrame < FastScaleRoundInt(0x46))
                Hero.swimCrossTapCount++;

            Hero.lastCrossPressFrame = worldUpdateTime;
        }

        if (Hero.jumpButtonFrames > FastScaleRoundInt(0x46))
            Hero.swimCrossTapCount = 0;

        if (padState.bits & PAD_SQUARE)
            Hero.swimCrossTapCount = 0;

        if (Hero.state == HERO_STATE_IDLEUNDER)
            turn = 0.0f;

        old = Hero.rotation.y;
        AccelDeltAng(Hero.rotation.y, turn, Hero.swimBankSpeed, bankSpring, bankDamping, lim, 0);
        roll = FastSubRots(Hero.rotation.y, old);
        Hero_GetIdealThrustFromPad(1.0f, 0);
        Hero_Turn(transStepScaleSq * 0.007f, transStepScaleSq * 0.08f, frameTime * 5.2359877f, 0);
        Hero.swimYawSpeed = Hero.turnSpeed;
        FastDecTimer_220e78(&Hero.swimThrustTimer);

        if (Hero.subState == 1)
            Hero.idealSpeed = frameTime * 6.0f;

        else if (Hero.state == HERO_STATE_CHARGEUNDER) {
            if (padState.bits & (PAD_R2 | PAD_R1))
                Hero.idealSpeed = frameTime * 7.0f;

            else
                Hero.idealSpeed = frameTime * 7.0f * 0.4f;
        }

        else
            Hero.idealSpeed = frameTime * 3.0f;

        {
            float speedScale;

            speedScale = Hero.padMagnitude;

            if ((padState.bits & (PAD_CROSS | PAD_SQUARE)) || Hero.subState == 1) {
                if (speedScale < 1.0f)
                    speedScale = 1.0f;
            }

            if (Hero.padMagnitude > 0.15f) {
                float minScale;

                minScale = 0.35f;

                if (Hero.state == HERO_STATE_CHARGEUNDER)
                    minScale = 0.4f;

                if (speedScale < minScale)
                    speedScale = minScale;
            }

            if (Hero.state != HERO_STATE_CHARGEUNDER || !(padState.bits & (PAD_R2 | PAD_R1)))
                Hero.idealSpeed *= speedScale;
        }

        if (FastDecTimer_220e78(&Hero.swimBubbleTimer)) {
            MB_GetBonePos(Hero.moby, 4, &scratch.particle.bonePos);
            ClearVec4(&scratch.particle.offset);
            scratch.particle.offset.x = 0.4f;
            FastVecMtx3Mult(&scratch.particle.offset, &scratch.particle.offset,
                            &Hero.moby->transform);
            FastVec3Add(&scratch.particle.bonePos, &scratch.particle.bonePos,
                        &scratch.particle.offset);
            CopyVec4Inline(&scratch.particle.velocity, &Hero.displacement);
            FastVec3Normalize(&scratch.particle.offset, &scratch.particle.offset, frameTime * 1.5f);
            FastVec3Add(&scratch.particle.velocity, &scratch.particle.velocity,
                        &scratch.particle.offset);
            scratch.particle.velocity.z += frameTime * 2.0f;
            SpawnPart_034(&scratch.particle.bonePos, &scratch.particle.velocity, 25200.0f, -1.0f);

            if (MB_randInt(0x64) < 40.0f)
                Hero.swimBubbleTimer = MB_randRange(FastScaleRoundInt(4), FastScaleRoundInt(0xB));

            else
                Hero.swimBubbleTimer =
                    MB_randRange(FastScaleRoundInt(0x28), FastScaleRoundInt(0x5A));
        }

        if (Hero.state == HERO_STATE_CHARGEUNDER) {
            if (FastDecTimer_220ea8(&Hero.packParticleTimer)) {
                MobyInstance *itemMoby;

                itemMoby = Hero.items[3].moby;

                if (itemMoby != 0 && (short)itemMoby->oClass == 0x261) {
                    int partIndex;

                    for (partIndex = 0; partIndex < 4; partIndex++) {
                        MB_GetBonePos(itemMoby, partIndex % 2, &scratch.particle.bonePos);
                        ClearVec4(&scratch.particle.offset);
                        scratch.particle.offset.x = -0.15f;
                        FastVecMtx3Mult(&scratch.particle.offset, &scratch.particle.offset,
                                        &Hero.moby->transform);
                        FastVec3Add(&scratch.particle.bonePos, &scratch.particle.bonePos,
                                    &scratch.particle.offset);
                        scratch.particle.bonePos.x += MB_randRangeFloat(0.0f, 0.03f);
                        scratch.particle.bonePos.y += MB_randRangeFloat(0.0f, 0.03f);
                        scratch.particle.bonePos.z += MB_randRangeFloat(0.0f, 0.03f);
                        CopyVec4Inline(&scratch.particle.velocity, &Hero.displacement);
                        MB_AddVectorSphere(&scratch.particle.velocity, &scratch.particle.velocity,
                                           frameTime * -0.75f, Hero.rotation.z, Hero.rotation.y);
                        Hero.packParticleTimer =
                            FastFloatToInt((frameTime * 7.0f - Hero.storedNeutralSpeed) /
                                           (frameTime * 7.0f) * FastScaleRoundInt(5));
                        SpawnPart_034(&scratch.particle.bonePos, &scratch.particle.velocity,
                                      MB_randRangeFloat(6300.0f, 9450.0f), -1.0f);
                    }
                }
            }
        }

        if (Hero.state == HERO_STATE_CHARGEUNDER)
            Hero_ThrustModeAccel(frameTimeSq * 13.0f, frameTimeSq * 8.0f);

        else
            Hero_ThrustModeAccel(frameTimeSq * 7.0f, frameTimeSq * 4.0f);

        swimVelocityPitch = FastAddRots(-Hero.rotation.y, 0.0f);

        if (Hero.state == HERO_STATE_CHARGEUNDER)
            MB_SphericalToVector(&Hero.velocity, Hero.storedNeutralSpeed, Hero.rotation.z,
                                 swimVelocityPitch);

        else if (Hero.state == HERO_STATE_SWIMUNDER) {
            float swimSpeed;

            swimSpeed = Hero.storedNeutralSpeed * Hero_GetLoopedAnimFrame(HeroSwimSpeedWeights, 0x1E) *
                5.0f;

            if (Hero.prevState == HERO_STATE_CHARGEUNDER &&
                Hero.stateTimer < FastScaleRoundInt(0xF)) {
                if (swimSpeed < frameTime * 4.5f)
                    swimSpeed = frameTime * 4.5f;
            }

            MB_SphericalToVector(&Hero.velocity, swimSpeed, Hero.rotation.z, swimVelocityPitch);
        }

        else if (Hero.state == HERO_STATE_IDLEUNDER) {
            float len;

            len = FastVec3Length2(&Hero.externalMomentum);

            if (Hero.prevState == HERO_STATE_CHARGEUNDER)
                Delt(len, 0.0f, frameTimeSq * 8.0f);

            else
                Delt(len, 0.0f, frameTimeSq * 4.0f);

            FastVec3Normalize(&Hero.externalMomentum, &Hero.externalMomentum, len);
            CopyVec4Inline(&Hero.velocity, &Hero.externalMomentum);
        }

        Hero_KneeBumpMotion(0);
        lean = Hero.swimYawSpeed * FastAngleSinF(swimVelocityPitch) * -7.0f;
        AccelDeltAng(Hero.rotation.x, lean, Hero.swimPitchSpeed, 0.007f, 0.17f,
                     frameTime * 1.2217305f, 0);
        Hero_SetTweaker1(0.009f, 0.22f);
        Hero_SetTweaker2(0.04f, 0.2f);
        Hero_SetTweaker3(0.02f, 0.2f);
        HeroTweaks[1].target.y = roll * 47.0f;
        HeroTweaks[1].target.z = lean * 1.5f;
        HeroTweaks[1].target.x = lean * 1.4f;

        if (HeroTweaks[1].target.y > 0.87266463f)
            HeroTweaks[1].target.y = 0.87266463f;

        else if (HeroTweaks[1].target.y < -0.87266463f)
            HeroTweaks[1].target.y = -0.87266463f;

        {
            float tweakRotY;
            float tweakRotZ;

            tweakRotY = roll * 40.0f;
            tweakRotZ = lean * 1.1f;
            HeroTweaks[4].gain = 0.03f;
            HeroTweaks[4].damp = 0.22f;
            HeroTweaks[4].target.y = tweakRotY;
            HeroTweaks[4].target.z = tweakRotZ;
            HeroTweaks[5].gain = 0.03f;
            HeroTweaks[5].damp = 0.22f;
            HeroTweaks[5].target.y = tweakRotY;
            HeroTweaks[5].target.z = tweakRotZ;
        }
    } break;
    case HERO_STATE_GET_HIT_UNDER: {
        int bubbleCount;

        bubbleCount = 0xA - Hero.stateTimer / 3;

        if (bubbleCount > 8)
            bubbleCount = 8;

        Hero_SpawnWaterBubbles(bubbleCount, 0);
        Hero.velocity.z = 0.0f;
        {
            float len;

            len = FastVec3Length(&Hero.velocity);
            FastVecNormalizeScaled(transStepScale * -0.07999998f * len + len, &Hero.velocity,
                                   &Hero.velocity);
        }

        Hero_KneeBumpMotion(0);
    } break;
    case HERO_STATE_GET_HIT_SURF:
        Hero_SpawnWaterRings(0xF, 0x1E);
        Hero.velocity.z = 0.0f;
        {
            float len;

            len = FastVec3Length(&Hero.velocity);
            FastVecNormalizeScaled(transStepScale * -0.07999998f * len + len, &Hero.velocity,
                                   &Hero.velocity);
        }

        Hero_KneeBumpMotion(0);
        Hero_SurfBob();
        break;
    case HERO_STATE_DROWN:
    case HERO_STATE_ELECTRIC_DEATH_UNDER: {
        float len;

        len = FastVec3Length2(&Hero.externalMomentum);
        Delt(len, 0.0f, frameTimeSq * 4.0f);
        FastVec3Normalize(&Hero.externalMomentum, &Hero.externalMomentum, len);
        CopyVec4Inline(&Hero.velocity, &Hero.externalMomentum);

        if (FastDecTimer_220e78(&Hero.swimBubbleTimer) == 2) {
            MB_GetBonePos(Hero.moby, 4, &scratch.particle.bonePos);
            ClearVec4(&scratch.particle.offset);
            scratch.particle.offset.x = 0.4f;
            FastVecMtx3Mult(&scratch.particle.offset, &scratch.particle.offset,
                            &Hero.moby->transform);
            FastVec3Add(&scratch.particle.bonePos, &scratch.particle.bonePos,
                        &scratch.particle.offset);
            CopyVec4Inline(&scratch.particle.velocity, &Hero.displacement);
            FastVec3Normalize(&scratch.particle.offset, &scratch.particle.offset, frameTime * 1.5f);
            FastVec3Add(&scratch.particle.velocity, &scratch.particle.velocity,
                        &scratch.particle.offset);
            scratch.particle.velocity.z += frameTime * 2.0f;
            SpawnPart_034(&scratch.particle.bonePos, &scratch.particle.velocity, 25200.0f, -1.0f);

            if (Hero.stateTimer < FastScaleRoundInt(0x28))
                Hero.swimBubbleTimer =
                    MB_randRange(FastScaleRoundInt(2), FastScaleRoundInt(5)) + Hero.stateTimer / 5;

            else if (Hero.stateTimer > FastScaleRoundInt(0x46))
                Hero.swimBubbleTimer =
                    MB_randRange(FastScaleRoundInt(0xA), FastScaleRoundInt(0x14));
        }

        if (Hero.drownSinkSpeed > 0.0f)
            Hero.drownSinkSpeed = 0.0f;

        Delt(Hero.drownSinkSpeed, -(frameTime * 1.5f), frameTimeSq * 1.5f);
        Hero.velocity.z = Hero.drownSinkSpeed;
    } break;
    case HERO_STATE_SWIMSURF:
    case HERO_STATE_IDLESURF:
        if (Hero.state == HERO_STATE_IDLESURF)
            Hero_SpawnWaterRings(0xF, 0x1E);

        if (Hero.flatSpeed > frameTime * 1.5f)
            Hero_SpawnWaterDrops(4, 0xC);

        if (Hero.state == HERO_STATE_SWIMSURF && Hero.flatSpeed > frameTime)
            Hero_SpawnWaterWake(0, 1);

        if (Hero.splashEffectTimer != 0) {
            int bubbleCount;

            Hero.splashEffectTimer--;
            bubbleCount = Hero.splashEffectTimer >> 3;

            if (bubbleCount > 6)
                bubbleCount = 6;

            Hero_SpawnWaterBubbles(bubbleCount, 0);
        }

        Hero.animSpeed = 0.6f;
        Hero_GetIdealThrustFromPad(frameTime * 3.0f, 0);

        if (padState.handsOffStick == 0) {
            if (Hero.idealSpeed < frameTime * 3.0f * 0.5f)
                Hero.idealSpeed = frameTime * 3.0f * 0.5f;
        }

        Hero_Turn(transStepScaleSq * 0.007f, transStepScaleSq * 0.08f, frameTime * 5.2359877f, 0);
        FastDecTimer_220e78(&Hero.swimStrokeTimer);

        if (Hero.state == HERO_STATE_SWIMSURF) {
            float swimSpeed;

            if (padState.handsOffStick != 0 && Hero.swimStrokeTimer != 0)
                Hero.idealSpeed = frameTime * 3.0f;

            if (FastAbsF(Hero.turnDelta) > 0.7853982f)
                Hero.idealSpeed = 0.0f;

            Hero_ThrustModeAccel(frameTimeSq * 4.0f, frameTimeSq * 5.0f);
            swimSpeed = Hero.storedNeutralSpeed * Hero_GetLoopedAnimFrame(HeroSwimSpeedWeights, 0x1E) *
                5.5f;
            Hero.velocity.x = FastAngleSinF(Hero.rotation.z) * swimSpeed;
            Hero.velocity.y = FastAngleCosF(Hero.rotation.z) * swimSpeed;
            Hero.velocity.z = 0.0f;
        }

        else {
            Hero.storedNeutralSpeed = 0.0f;
            FastVecZero(&Hero.velocity);
        }

        if (Hero.state == HERO_STATE_SWIMSURF && Hero.animChanging == 0 && Hero.animFrame > 0.0f &&
            Hero.animFrame < 10.0f)
            Hero_SpawnWaterBubbles(4, 1);

        Hero_ApplyFriction(frameTimeSq * 4.2f);
        Hero_KneeBumpMotion(0);
        Hero_SurfBob();
        break;
    case HERO_STATE_WAIT_FOR_ITEM_RELEASE_THEN_IDLE: {
        int anim;
        int frames;

        anim = -1;
        frames = 0;

        if (Hero.onIceGround != 0)
            Hero_ThrustToMotion(0.7f, frameTime * 0.0f);

        else
            Hero_ThrustToMotion(0.5f, frameTime * 2.0f);

        Hero_EdgeStop(3.7f, 0.0f);
        Hero_GetIdealThrustFromPad(1.0f, 0);
        Hero_ThrustModeAccel(frameTimeSq * 12.6f, frameTimeSq * 12.6f);
        FastVecZero(&Hero.velocity);
        Hero_ApplyFriction(frameTimeSq * 12.6f);

        if (Hero.framesNotGrounded != 0) {
            Hero_AddGravity(&Hero.velocity, &Hero.displacement, frameTimeSq * 25.0f);
            Hero_WallSloopMotion();
        }

        else
            Hero_AddGravity(&Hero.velocity, &Hero.velocity, frameTimeSq * 54.0f);

        if (anim != -1 && Hero.moby->updateId != HERO_ANIM_SHOOT_C)
            Hero_TransAnim(anim, 0, frames);

        else if ((Hero.moby->unk70 & 2) && Hero.moby->updateId == HERO_ANIM_SHOOT_C)
            Hero_TransAnim(Hero_GetIdleAnim(0), 0, FastScaleRoundInt(5));
    } break;
    case HERO_STATE_ROCKET_STOMP: {
        int windowStart;
        int windowEnd;
        float targetVelocityZ;
        float stepSize;

        Hero.idealSpeed = 0.0f;
        Hero_ThrustModeAccel(frameTimeSq * 30.0f, frameTimeSq * 30.0f);
        Hero_SetRelativeZ(&Hero.velocity, &Hero.velocity, Hero.storedNeutralSpeed);
        windowStart = FastScaleRoundInt(0xC);
        targetVelocityZ = frameTime * 5.7f;
        stepSize = frameTimeSq * 70.0f;
        windowEnd = FastScaleRoundInt(0x21);

        if (Hero.stateTimer < windowStart) {
            float velocityZ;

            velocityZ = Hero_RelativeZComponent(&Hero.velocity);
            Delt(velocityZ, targetVelocityZ, stepSize);
            Hero_ToHeroRelative(&Hero.velocity, &Hero.velocity, velocityZ);
        }

        else if (Hero.stateTimer > windowEnd) {
            Hero_AddGravity(&Hero.velocity, &Hero.velocity, Hero.riseFallGravity);

            if (Hero_RelativeZComponent(&Hero.velocity) < 0.0f)
                Hero.pastApex = 1.0f;
        }

        if (Hero.pastApex != 0.0f) {
            if (Hero.framesNotGrounded != 0) {
                CopyVec4Inline(&scratch.rocketStomp.hitPos, &Hero.position);
                scratch.rocketStomp.hitPos.z -= 0.5f;
                scratch.rocketStomp.hitDirection.x = FastAngleSinF(Hero.rotation.z);
                scratch.rocketStomp.hitDirection.y = FastAngleCosF(Hero.rotation.z);
                scratch.rocketStomp.hitDirection.z = 0.0f;
                SetCollDamIn_2(scratch.rocketStomp.hit, Hero.moby, 0x30000, 1.0f,
                               &scratch.rocketStomp.hitDirection);
                CollMobySphere(0.8f, &scratch.rocketStomp.hitPos, 0x10, Hero.moby,
                               &scratch.rocketStomp.hit);
            }
        }

        if (Hero.pastApex != 0.0f) {
            if (Hero.framesNotGrounded == 0) {
                if (Hero.riseFallLandFrames == 0) {
                    GameCamera.shake.strength = 0.2f;
                    GameCamera.shake.time = FastScaleRoundInt(0x28);
                }

                Hero.riseFallLandFrames++;
            }
        }
    } break;
    case HERO_STATE_JUMP_ATTACK: {
        int windowStart;
        int windowEnd;
        float targetVelocityZ;
        float acc;

        if (Hero.animChanging != 0 ||
            Hero.animFrame < HeroAttackTable[Hero.attackRecord].endFrame)
            Hero.items[0].timer = 2;

        Hero.idealSpeed = 0.0f;

        if (Hero.meleeTarget != 0) {
            float targetDistance;

            targetDistance = FastVec3DistLen(&Hero.position, &Hero.meleeTarget->pos);

            if (targetDistance > 2.0f && targetDistance < 5.0f)
                Hero.idealSpeed = frameTime * 4.5f;

            Hero_ThrustModeAccel(frameTimeSq * 25.0f, frameTimeSq * 25.0f);
            Hero.velocity.x = FastAngleSinF(Hero.rotation.z) * Hero.storedNeutralSpeed;
            Hero.velocity.y = FastAngleCosF(Hero.rotation.z) * Hero.storedNeutralSpeed;
        }

        else {
            Hero_ThrustModeAccel(frameTimeSq * 15.0f, frameTimeSq * 15.0f);
            Hero_SetRelativeZ(&Hero.velocity, &Hero.velocity, Hero.storedNeutralSpeed);
        }

        if (Hero.headingLocked != 0 || Hero.meleeTarget != 0) {
            Hero.idealRotZ = Hero.attackTargetYaw;
            Hero_Turn(transStepScaleSq * 0.05f, transStepScaleSq * 0.2f, frameTime * 15.009831f, 0);
        }

        else if (Hero.animFrame < 25.0f)
            Hero_UpdateAutoTargetAim(8.0f, 1.0471976f, 1.0471976f);

        windowStart = FastScaleRoundInt(9);
        targetVelocityZ = frameTime * 7.7f;

        if (Hero.groundDist > 2.25f)
            targetVelocityZ *= 0.5f;

        else if (Hero.groundDist > 1.8f)
            targetVelocityZ *= 0.7f;

        acc = frameTimeSq * 150.0f;
        windowEnd = FastScaleRoundInt(0xE);

        if (Hero.animChanging == 0 && Hero.animFrame > 23.5f && Hero.displacement.z < 0.0f &&
            Hero.framesNotGrounded != 0) {
            CopyVec4Inline(&scratch.jumpAttack.hitPos, &Hero.position);
            Hero_SubGravity(-0.5f, &scratch.jumpAttack.hitPos, &scratch.jumpAttack.hitPos);
            scratch.jumpAttack.hitDirection.x = FastAngleSinF(Hero.rotation.z) * 2.0f;
            scratch.jumpAttack.hitDirection.y = FastAngleCosF(Hero.rotation.z) * 2.0f;
            scratch.jumpAttack.hitDirection.z = 0.0f;
            SetCollDamIn_2(scratch.jumpAttack.hit, Hero.moby, 0x10000, 2.0f,
                           &scratch.jumpAttack.hitDirection);
            scratch.jumpAttack.hit.momentum.w = 5627.925f;
            scratch.jumpAttack.hit.damageStrength = 1;
            scratch.jumpAttack.hit.damageIndex = 0x47;
            scratch.jumpAttack.hit.damageClass = 0;
            CollMobySphere(0.4f, &scratch.jumpAttack.hitPos, 0x10, Hero.moby,
                           &scratch.jumpAttack.hit);
        }

        Hero_AnimFrameInWindow(27.0f);

        if (Hero.stateTimer < windowStart) {
            float velocityZ;

            velocityZ = Hero_RelativeZComponent(&Hero.velocity);
            Delt(velocityZ, targetVelocityZ, acc);
            Hero_ToHeroRelative(&Hero.velocity, &Hero.velocity, velocityZ);
        }

        else if (Hero.stateTimer > windowEnd) {
            Hero_AddGravity(&Hero.velocity, &Hero.velocity, frameTimeSq * 130.0f);

            if (Hero_RelativeZComponent(&Hero.velocity) < 0.0f)
                Hero.slamDescending = 1.0f;

            if (Hero_RelativeZComponent(&Hero.velocity) < frameTime * -37.0f)
                Hero_ToHeroRelative(&Hero.velocity, &Hero.velocity, frameTime * -37.0f);
        }
    } break;
    case HERO_STATE_THROW_ATTACK: {
        int skip;

        Hero.idealSpeed = 0.0f;

        if (Hero.animChanging != 0 ||
            Hero.animFrame < HeroAttackTable[Hero.attackRecord].endFrame)
            Hero.items[0].timer = 2;

        skip = 0;

        if (Hero.prevState == 1 && FastScaleRoundInt(0x14) < Hero.prevStateTimer)
            skip = 1;

        if (!skip) {
            if (Hero.headingLocked != 0 || Hero.meleeTarget != 0) {
                int near;

                near = 1;

                if (Hero.onMagnerail == 0) {
                    float yawDelta;
                    float turnAngle;

                    yawDelta = FastSubRots(Hero.attackTargetYaw, Hero.rotation.z);
                    turnAngle = SubRots(Hero.attackTargetYaw, Hero.rotation.z, 1);

                    if (turnAngle > 4.363323f)
                        near = 0;

                    if (yawDelta > 0.0f)
                        Hero.animSpeed = 1.0f / (turnAngle + 1.0f);
                }

                else
                    near = 0;

                Hero.idealRotZ = Hero.attackTargetYaw;

                if (near)
                    Hero_Turn(transStepScaleSq * 0.05f, transStepScaleSq * 0.2f,
                              frameTime * 15.009831f, 1);

                else
                    Hero_Turn(transStepScaleSq * 0.05f, transStepScaleSq * 0.2f,
                              frameTime * 15.009831f, 0);
            }

            else {
                int canAutoAim;

                canAutoAim = 1;

                if (Hero.animChanging == 0 && Hero.animFrame > 6.0f)
                    canAutoAim = 0;

                if (canAutoAim) {
                    if (Hero.gravityMode == HERO_GRAVITY_WORLD_DOWN)
                        Hero_UpdateAutoTargetAim(14.0f, 0.5235988f, 0.7853982f);
                }
            }
        }

        if (Hero.animChanging == 0 && Hero_AnimFrameInWindow(33.0f))
            Hero_ThrowWrench();

        Hero_ThrustModeAccel(frameTimeSq * 37.0f, frameTimeSq * 28.0f);
        Hero_ThrustToMotionFwd(99999.0f);

        if (Hero.framesNotGrounded != 0)
            Hero_AddGravity(&Hero.velocity, &Hero.resolvedVelocityZ, frameTimeSq * 25.0f);

        else
            Hero_AddGravity(&Hero.velocity, &Hero.velocity, frameTimeSq * 54.0f);
    } break;
    case HERO_STATE_COMBO_ATTACK: {
        HeroAttackRow *attackRow;

        if (Hero.animChanging != 0 ||
            Hero.animFrame < HeroAttackTable[Hero.attackRecord].hitEndFrame)
            Hero.items[0].timer = 2;

        Hero.idealSpeed = 0.0f;
        attackRow = &HeroAttackTable[Hero.attackRecord];

        if (Hero.meleeTarget != 0 && Hero.stateTimer < FastScaleRoundInt(4)) {
            float targetDistance;
            float attackKindDistanceOffset;
            float range;
            float cap;
            float distanceError;

            targetDistance = FastVec3DistLen(&Hero.meleeTarget->pos, &Hero.position) - 0.5f;

            if (targetDistance < 0.0f)
                targetDistance = 0.0f;

            if (attackRow->kind == HERO_COMBO_FORWARD_ADVANCE) {
                attackKindDistanceOffset = 0.75f;
                range = 0.8f;
                cap = 4.0f;
            }

            else if (attackRow->kind == HERO_COMBO_FORWARD_DECELERATION) {
                attackKindDistanceOffset = 0.6f;
                range = 1.7f;
                cap = 4.0f;
            }

            else {
                attackKindDistanceOffset = 1.3f;
                range = 1.7f;
                cap = 1.9f;
            }

            distanceError = targetDistance - attackKindDistanceOffset;

            if (FastAbsF(distanceError) < range + 3.0f) {
                float approachSpeedScale;

                approachSpeedScale = distanceError / 0.9f;

                if (approachSpeedScale > cap)
                    approachSpeedScale = cap;

                if (approachSpeedScale > 1.0f)
                    Hero.speedScale = approachSpeedScale;
            }
        }

        switch (attackRow->kind) {
        case HERO_COMBO_FORWARD_ADVANCE:
            if (Hero.animFrame < 18.0f)
                Hero.idealSpeed = frameTime * 4.4f * Hero.speedScale;

            break;
        case HERO_COMBO_FORWARD_DECELERATION:
            if (Hero.animChanging != 0 || Hero.animFrame < 9.0f) {
                if (Hero.animFrame > 8.0f)
                    Hero.idealSpeed = frameTime * 3.0f * Hero.speedScale;

                else if (Hero.animFrame > 7.0f)
                    Hero.idealSpeed = frameTime * 4.5f * Hero.speedScale;

                else
                    Hero.idealSpeed = frameTime * 5.7f * Hero.speedScale;
            }

            break;
        case HERO_COMBO_CONDITIONAL_FORWARD_ADVANCE:
            if (Hero.animChanging != 0 || Hero.animFrame < 12.0f)
                Hero.idealSpeed = frameTime * 3.7f * Hero.speedScale;

            break;
        }

        Delt(Hero.animSpeed, 1.0f, 0.2f);

        if (Hero.headingLocked != 0 || Hero.meleeTarget != 0) {
            if (attackRow->kind == HERO_COMBO_FORWARD_DECELERATION &&
                FastSubRots(Hero.attackTargetYaw, Hero.rotation.z) > 0.0f)
                Hero.animSpeed =
                    1.0f / (FastDiffRots(Hero.attackTargetYaw, Hero.rotation.z) + 1.0f);

            Hero.idealRotZ = Hero.attackTargetYaw;
            Hero_Turn(transStepScaleSq * 0.05f, transStepScaleSq * 0.2f, frameTime * 15.009831f, 0);
        }

        else {
            int canAutoAim;

            canAutoAim = 1;

            if (attackRow->kind == HERO_COMBO_FORWARD_DECELERATION && Hero.animChanging == 0 &&
                Hero.animFrame > 7.0f)
                canAutoAim = 0;

            if (canAutoAim)
                Hero_UpdateAutoTargetAim(5.0f, 0.7853982f, 0.7853982f);
        }

        Hero_ThrustModeAccel(frameTimeSq * 37.0f, frameTimeSq * 28.0f);

        if (Hero.headingLocked != 0)
            Hero_ThrustToMotionFwd(Hero.attackTargetYaw);

        else
            Hero_ThrustToMotionFwd(99999.0f);

        if (Hero.framesNotGrounded != 0)
            Hero_AddGravity(&Hero.velocity, &Hero.resolvedVelocityZ, frameTimeSq * 25.0f);

        else
            Hero_AddGravity(&Hero.velocity, &Hero.velocity, frameTimeSq * 54.0f);

        Hero_EdgeStop(3.7f, 0.0f);
    } break;
    case HERO_STATE_UNK_BONK:
    case HERO_STATE_JUMP_BOUNCE:
        Delt(Hero.storedNeutralSpeed, 0.0f, frameTimeSq * 24.0f);
        Hero.velocity.x = FastAngleSinF(Hero.pushbackYaw) * Hero.storedNeutralSpeed;
        Hero.velocity.y = FastAngleCosF(Hero.pushbackYaw) * Hero.storedNeutralSpeed;

        if (Hero.groundDist > 0.0f)
            Hero.velocity.z = Hero.resolvedVelocity.z - frameTimeSq * 25.0f;

        else
            Hero.velocity.z = 0.0f;

        Hero.idealRotZ = FastAddRots(Hero.pushbackYaw, 3.1415927f);
        Hero_Turn(transStepScaleSq * 0.05f, transStepScaleSq * 0.2f, frameTime * 15.009831f, 0);
        break;
    case HERO_STATE_WALLOPER_ATTACK: {
        int windowStart;
        int windowEnd;
        int trailMode;

        if (Hero.headingLocked != 0 || Hero.meleeTarget != 0) {
            Hero.idealRotZ = Hero.attackTargetYaw;
            Hero_Turn(transStepScaleSq * 0.05f, transStepScaleSq * 0.2f, frameTime * 15.009831f, 0);
        }

        else if (Hero.stateTimer < FastScaleRoundInt(4))
            Hero_UpdateAutoTargetAim(11.0f, 0.87266463f, -1.0f);

        windowStart = FastScaleRoundInt(0xA);
        Hero.idealSpeed = 0.0f;
        windowEnd = windowStart + FastScaleRoundInt(8);

        if (Hero.stateTimer > windowStart && Hero.stateTimer < windowEnd)
            Hero.idealSpeed = frameTime * 18.0f;

        if (Hero.stateTimer == FastScaleRoundInt(8)) {
            CreateMotionBlur(Hero.moby, &Hero.trail);
            AddMotionBlurElem(&Hero.trail, 0x30, 2);
            AddMotionBlurElem(&Hero.trail, 0x17, 4);
            AddMotionBlurElem(&Hero.trail, 0xC, 6);
        }

        trailMode = 5;

        if (!(Hero.stateTimer > windowEnd))
            trailMode = 0;

        UpdateMotionBlur(&Hero.trail, trailMode);

        if (Hero.stateTimer > windowStart)
            Hero_ThrustModeAccel(frameTimeSq * 190.0f, frameTimeSq * 90.0f);

        if (Hero.headingLocked != 0)
            Hero_ThrustToMotionFwd(Hero.attackTargetYaw);

        else
            Hero_ThrustToMotionFwd(99999.0f);

        if (Hero.state == HERO_STATE_WALLOPER_ATTACK && Hero.stateTimer > windowStart) {
            if (Hero.stateTimer < windowEnd + FastScaleRoundInt(4)) {
                MobyInstance *attackItemMoby;

                attackItemMoby = Hero.items[0].moby;

                if (attackItemMoby != 0) {
                    float yaw;

                    scratch.walloper.hitDirection.x = FastAngleSinF(Hero.rotation.z) * 2.0f;
                    scratch.walloper.hitDirection.y = FastAngleCosF(Hero.rotation.z) * 2.0f;
                    scratch.walloper.hitDirection.z = 1.3f;
                    SetCollDamIn_2(scratch.walloper.hit, Hero.moby, 0x30000, 3.0f,
                                   &scratch.walloper.hitDirection);
                    scratch.walloper.hit.damageStrength = 3;
                    scratch.walloper.hit.momentum.w = 5627.925f;
                    scratch.walloper.hit.damageClass = 0;
                    yaw = Hero.rotation.z;
                    scratch.walloper.hit.damageIndex = attackItemMoby->oClass;
                    scratch.walloper.hitPos.x = FastAngleSinF(yaw) * 0.8f;
                    scratch.walloper.hitPos.y = FastAngleCosF(yaw) * 0.8f;
                    scratch.walloper.hitPos.z = 0.55f;
                    FastVec3Add(&scratch.walloper.hitPos, &scratch.walloper.hitPos, &Hero.position);
                    Hero_JumpOrSnapJumpCheck((int)attackItemMoby,
                                             CollMobySphere(0.8f, &scratch.walloper.hitPos, 0,
                                                            attackItemMoby,
                                                            &scratch.walloper.hit));
                    yaw = FastAddRots(Hero.rotation.z, -0.87266463f);
                    scratch.walloper.hitPos.x = FastAngleSinF(yaw) * 0.8f;
                    scratch.walloper.hitPos.y = FastAngleCosF(yaw) * 0.8f;
                    scratch.walloper.hitPos.z = 0.55f;
                    FastVec3Add(&scratch.walloper.hitPos, &scratch.walloper.hitPos, &Hero.position);
                    Hero_JumpOrSnapJumpCheck((int)attackItemMoby,
                                             CollMobySphere(0.8f, &scratch.walloper.hitPos, 0,
                                                            Hero.moby, &scratch.walloper.hit));
                    yaw = FastAddRots(Hero.rotation.z, 0.87266463f);
                    scratch.walloper.hitPos.x = FastAngleSinF(yaw) * 0.8f;
                    scratch.walloper.hitPos.y = FastAngleCosF(yaw) * 0.8f;
                    scratch.walloper.hitPos.z = 0.55f;
                    FastVec3Add(&scratch.walloper.hitPos, &scratch.walloper.hitPos, &Hero.position);
                    Hero_JumpOrSnapJumpCheck((int)attackItemMoby,
                                             CollMobySphere(0.8f, &scratch.walloper.hitPos, 0,
                                                            attackItemMoby,
                                                            &scratch.walloper.hit));
                }
            }
        }

        if (Hero.stateTimer > FastScaleRoundInt(0xA))
            Hero_EdgeStop(3.7f, 0.0f);

        Hero_KneeBumpMotion(1);

        if (Hero.framesNotGrounded != 0) {
            Hero_AddGravity(&Hero.velocity, &Hero.resolvedVelocity, frameTimeSq * 24.0f);
            Hero_WallSloopMotion();
        }

        else
            Hero_AddGravity(&Hero.velocity, &Hero.velocity, frameTimeSq * 54.0f);
    } break;
    case HERO_STATE_THROWING_ITEM:
        Hero.idealSpeed = 0.0f;

        if (Hero.headingLocked != 0) {
            Hero.idealRotZ = Hero.attackTargetYaw;
            Hero_Turn(transStepScaleSq * 0.04f, transStepScaleSq * 0.2f, frameTime * 15.009831f, 0);
        }

        else
            Hero_UpdateAutoTargetAim(11.0f, 0.87266463f, -1.0f);

        Hero_ThrustModeAccel(frameTimeSq * 30.0f, frameTimeSq * 35.0f);
        Hero_ThrustToMotionFwd(99999.0f);

        if (Hero.framesNotGrounded != 0) {
            Hero.velocity.z = Hero.displacement.z - frameTimeSq * 25.0f;
            Hero_WallSloopMotion();
        }

        else
            Hero.velocity.z -= frameTimeSq * 54.0f;

        break;
    case HERO_STATE_WALK:
    case HERO_STATE_WADE: {
        int quiet;
        float thrustScale;
        float upThrust;
        float down;

        quiet = 0;

        if (Hero.hotSpotWater != 0 && Hero.waterDepth < 0.25f)
            quiet = 1;

        if (Hero.wading != 0 || quiet) {
            if (Hero.flatSpeed > frameTime)
                Hero_SpawnWaterWake(0, 2);

            if (Hero.flatSpeed > frameTime * 0.5f)
                Hero_SpawnWaterDrops(2, 4);

            Hero_SpawnWaterBubbles(5, 2);
        }

        if (Hero.flatSpeed < frameTime * 0.3f && Hero.padMagnitude > 0.85f)
            Hero.moveAlongStick = 1;

        if (FastAbsF(Hero.turnDelta) < 0.05235988f || Hero.itemAnimActive != 0 ||
            Hero.subState == 1)
            Hero.moveAlongStick = 0;

        if (Hero.sharpTurn != 0) {
            if (FastAbsF(Hero.turnDelta) < 0.06981317f || Hero.itemAnimActive != 0)
                Hero.sharpTurn = 0;
        }

        Hero_GetIdealThrustForWalk();

        if (Hero.pushLength > 0.0f) {
            Hero_ThrustToMotion(0.7f, 0.0f);
            CopyVec4(&scratch.wade.impulse, &Hero.moveImpulse);
            Hero.idealSpeed = Hero.idealSpeed + Hero_SinCosDot(&scratch.wade.impulse);

            if (Hero.idealSpeed < frameTime * 0.7f)
                Hero.idealSpeed = frameTime * 0.7f;

            FastVecZero(&Hero.moveImpulse);
        }

        thrustScale = 1.0f;

        if (Hero.subState == 1 && Hero.sharpTurn == 0)
            Hero_Turn(transStepScaleSq * 0.008f, transStepScaleSq * 0.15f, frameTime * 9.948377f,
                      0);

        else {
            float stickMagnitude;
            float remainingTurnAngle;

            stickMagnitude = Hero.padMagnitude;
            remainingTurnAngle = Hero.turnDelta;

            if (Hero.itemAnimActive != 0) {
                thrustScale = 1.0f - remainingTurnAngle * 0.55f;

                if (thrustScale < 0.0f)
                    thrustScale = 0.0f;
            }

            else if (stickMagnitude < 0.8f) {
                if (remainingTurnAngle > 0.5235988f)
                    thrustScale = 0.0f;
            }

            if (stickMagnitude > HeroJumpSpeeds.minRunSpeed)
                Hero_TurnWalk();

            else {
                float turnScale;

                turnScale = Hero.padMagnitude + 0.35f;
                Hero_Turn(transStepScaleSq * 0.005f * turnScale, transStepScaleSq * 0.1f,
                          frameTime * 4.712389f * turnScale, 0);
            }
        }

        Hero_SetBankTwistSway();
        Hero_SetBackpackSway();
        upThrust = frameTimeSq * 7.5f * thrustScale;
        down = frameTimeSq * 8.5f;

        if (Hero.sharpTurn != 0) {
            float speedScale;

            speedScale = 2.6179938f - Hero.turnDelta;

            if (speedScale > 1.0f)
                speedScale = 1.0f;

            if (speedScale < 0.2f)
                speedScale = 0.2f;

            Hero.idealSpeed *= speedScale;
            down = frameTimeSq * 17.0f;
        }

        Hero_ThrustModeAccel(upThrust, down);

        if (Hero.moveAlongStick != 0 && Hero.onMagnerail == 0)
            Hero_ThrustToMotionFwd(Hero.idealRotZ);

        else
            Hero_ThrustToMotionFwd(99999.0f);

        Hero_KneeBumpMotion(1);

        if (Hero.edgeStop != 0)
            Hero_EdgeStop(5.0f, 0.2f);

        if (Hero.framesNotGrounded != 0) {
            Hero_AddGravity(&Hero.velocity, &Hero.resolvedVelocityZ, frameTimeSq * 25.0f);
            Hero_WallSloopMotion();
        }

        else
            Hero_AddGravity(&Hero.velocity, &Hero.velocity, frameTimeSq * 54.0f);
    } break;
    case HERO_STATE_SLIDE:
        if (Level == LEVEL_QUARTU)
            Hero_PlayLoopSound(2, Hero.moby, 0x1D);

        else
            Hero_PlayLoopSound(2, Hero.moby, 6);

        if (Level != LEVEL_QUARTU) {
            Hero_SpawnWaterBubbles(4, 2);
            scratch.slide.bubblePos.x = Hero.position.x + MB_randRangeFloat(-0.25f, 0.25f);
            scratch.slide.bubblePos.y = Hero.position.y + MB_randRangeFloat(-0.25f, 0.25f);
            scratch.slide.bubblePos.z = Hero.position.z + MB_randRangeFloat(-0.1f, 0.4f);
            FastVec3Scale(&scratch.slide.bubbleVelocity, &Hero.displacement, 0.9f);
            scratch.slide.bubbleVelocity.x +=
                MB_randRangeFloat(frameTime * -0.7f, frameTime * 0.7f);
            scratch.slide.bubbleVelocity.y +=
                MB_randRangeFloat(frameTime * -0.7f, frameTime * 0.7f);
            scratch.slide.bubbleVelocity.z += MB_randRangeFloat(frameTime, frameTime * 2.0f);
            SpawnPart_047(&scratch.slide.bubblePos, &scratch.slide.bubbleVelocity,
                          MB_randRangeFloat(37800.0f, 75600.0f));
        }

        {
            float platformSpeed;
            float old;
            float yawChange;
            float lean;

            platformSpeed = FastVec3Length2(&Hero.platformDelta);

            if (platformSpeed > frameTime * 0.5f)
                Hero.idealRotZ = FastArcTan(Hero.platformDelta.x, Hero.platformDelta.y);

            else
                Hero.idealRotZ = Hero.rotation.z;

            old = Hero.rotation.z;
            Hero_Turn(platformSpeed * 0.125f * transStepScaleSq, transStepScaleSq * 0.2f,
                      frameTime * 4.1887903f, 0);
            yawChange = FastDiffRots(Hero.rotation.z, old);
            FastVecZero(&Hero.velocity);
            Hero_ApplyFriction(frameTimeSq * 5.0f);
            Hero.velocity.z = Hero.displacement.z - frameTimeSq * 50.0f;

            if (Hero.velocity.z > frameTimeSq * -40.0f)
                Hero.velocity.z = frameTimeSq * -40.0f;

            if (yawChange > frameTime * 1.3962634f)
                yawChange = frameTime * 1.3962634f;

            lean = yawChange * 9.0f;
            AccelDeltAng(Hero.rotation.x, lean * 0.5f, Hero.rollSpringVelocity, 0.007f, 0.17f,
                         frameTime * 1.2217305f, 0);

            if (Hero.stateTimer > FastScaleRoundInt(0x64))
                AccelDeltAng(Hero.rotation.y, -Hero.railRidePitch, Hero.railRidePitchVelocity,
                             transStepScaleSq * 0.035f, transStepScaleSq * 0.3f,
                             frameTime * 1.9198622f, 0);

            Hero_SetTweaker1(0.009f, 0.22f);
            Hero_SetTweaker2(0.04f, 0.2f);
            Hero_SetTweaker3(0.02f, 0.2f);
            HeroTweaks[1].target.z = lean * 2.1f;
            HeroTweaks[1].target.x = lean * 3.5f;
        }

        break;
    case HERO_STATE_LEDGE_GRAB:
    case HERO_STATE_LEDGE_IDLE:
        Hero.idealRotZ = FastAddRots(Hero.ledgeWallAngZ, 3.1415927f);
        Hero_Turn(transStepScaleSq * 0.04f, transStepScaleSq * 0.2f, frameTime * 6.2831855f, 0);
        DeltAng(Hero.rotation.y, 0.0f, frameTime * 4.712389f, 0);
        FastSubVec3(&Hero.velocity, &Hero.ledgeGrabPos, &Hero.position);
        ClampVec3Magnitude(&Hero.velocity, frameTime * 4.0f);
        Delt(Hero.smoothedAirZ, Hero.position.z, frameTime * 3.0f);
        break;
    case HERO_STATE_LEDGE_TRAVERSE_LEFT:
    case HERO_STATE_LEDGE_TRAVERSE_RIGHT: {
        float originalProbeYaw;
        float offsetProbeYaw;

        Hero.velocity.x = 0.0f;
        Hero.velocity.y = 0.0f;
        Hero.velocity.z = 0.0f;
        CopyVec4Inline(&scratch.ledge.position, &Hero.position);

        if (Hero.state == HERO_STATE_LEDGE_TRAVERSE_LEFT) {
            scratch.ledge.sideStep.x =
                FastAngleSinF(FastAddRots(Hero.rotation.z, 1.5707964f)) * 0.3f;
            scratch.ledge.sideStep.y =
                FastAngleCosF(FastAddRots(Hero.rotation.z, 1.5707964f)) * 0.3f;
            scratch.ledge.sideStep.z = 0.0f;
        }

        else {
            scratch.ledge.sideStep.x =
                FastAngleSinF(FastAddRots(Hero.rotation.z, -1.5707964f)) * 0.3f;
            scratch.ledge.sideStep.y =
                FastAngleCosF(FastAddRots(Hero.rotation.z, -1.5707964f)) * 0.3f;
            scratch.ledge.sideStep.z = 0.0f;
        }

        FastVec3Add(&scratch.ledge.offsetPosition, &scratch.ledge.position,
                    &scratch.ledge.sideStep);
        Hero_CheckLedgeGrab();

        if (Hero.ledgeFound != 0) {
            CopyVec4Inline(&scratch.ledge.grabA, &Hero.ledgeGrabPos);
            originalProbeYaw = FastAddRots(Hero.ledgeWallAngZ, 3.1415927f);
            CopyVec4Inline(&Hero.position, &scratch.ledge.offsetPosition);
            Hero_CheckLedgeGrab();
            CopyVec4Inline(&Hero.position, &scratch.ledge.position);

            if (Hero.ledgeFound != 0) {
                CopyVec4Inline(&scratch.ledge.grabB, &Hero.ledgeGrabPos);
                offsetProbeYaw = FastAddRots(Hero.ledgeWallAngZ, 3.1415927f);

                if (!(FastDiffRots(originalProbeYaw, offsetProbeYaw) > 0.5235988f)) {
                    float mid;
                    float spd;

                    mid = FastAddRots(FastSubRots(originalProbeYaw, offsetProbeYaw) * 0.5f,
                                      originalProbeYaw);
                    FastVec3Add(&scratch.ledge.midpoint, &scratch.ledge.grabA,
                                &scratch.ledge.grabB);
                    FastVec3Scale(&scratch.ledge.midpoint, &scratch.ledge.midpoint, 0.5f);
                    Hero.idealRotZ = mid;
                    Hero_Turn(transStepScaleSq * 0.04f, transStepScaleSq * 0.2f,
                              frameTime * 6.2831855f, 0);
                    spd = Hero.flatSpeed;
                    Delt(spd, Hero.idealSpeed * frameTime, frameTimeSq * 5.0f);
                    FastSubVec3(&Hero.velocity, &scratch.ledge.midpoint, &Hero.position);
                    FastVec3RSqrtScale(&Hero.velocity, &Hero.velocity,
                                       HeroLedgeShimmySpeeds[FastFloatToInt(Hero.animFrame)] *
                                           0.5f);
                }
            }
        }
    } break;
    case HERO_STATE_SLOPESLIDE:
        Hero.idealRotZ = Hero.groundAngZ;
        Hero.idealSpeed = frameTime * 5.5f;
        Hero_JumpTranslation(frameTimeSq * 25.0f);
        Hero_AddGravity(&Hero.velocity, &Hero.resolvedVelocityZ, frameTimeSq * 18.0f);
        break;
    case HERO_STATE_FALL:
    case HERO_STATE_SWING_FALL:
        Hero_GetIdealThrustForWalk();

        if (Hero.moveLockTimer == 0)
            Hero_JumpTurnTrans();

        Hero_SetBankTwistSway();
        Hero_ThrustToMotion(0.7f, frameTime * 0.0f);
        Hero_AddGravity(&Hero.velocity, &Hero.velocity, Hero.fallStateGravity);

        if (Hero_RelativeZComponent(&Hero.velocity) < -(frameTime * 50.0f))
            Hero_ToHeroRelative(&Hero.velocity, &Hero.velocity, -(frameTime * 50.0f));

        break;
    case HERO_STATE_DEATH_FALL:
        Hero.itemUseLocked = 1;
        Delt(Hero.fatalFallRollRate, Hero.pivotRotXTarget, frameTimeSq * 8.726646f);
        Delt(Hero.fixedPivotRotY, Hero.fatalFallTumbleTargetY, frameTimeSq * 8.726646f);
        Hero_ApplyRootMotion(Hero.fatalFallRollRate, Hero.fixedPivotRotY, 0.0f);
        {
            float len;

            len = FastVec3Length(&Hero.velocity);
            FastVecNormalizeScaled(transStepScale * -0.100000024f * len + len, &Hero.velocity,
                                   &Hero.velocity);
        }

        Hero_AddGravity(&Hero.velocity, &Hero.velocity, Hero.fallStateGravity);

        if (Hero_RelativeZComponent(&Hero.velocity) < -(frameTime * 50.0f))
            Hero_ToHeroRelative(&Hero.velocity, &Hero.velocity, -(frameTime * 50.0f));

        break;
    case HERO_STATE_ROCKET_HOVER: {
        float airAccel;
        float airStickSpeed;
        float jumpAccel;

        fast = 1;
        Hero_PlayLoopSound(4, Hero.moby, 0x12);

        if (!(Hero.groundDist > 0.7f))
            fast = 0;

        airAccel = frameTime * 4.0f;
        airStickSpeed = frameTime * 5.75f;

        if (fast)
            airStickSpeed = airAccel;

        Hero_GetIdealThrustFromPad(Hero.padMagnitude * airStickSpeed, 0);

        if (Hero.padMagnitude > 0.2f && !(padState.bits & (PAD_L2 | PAD_R2)))
            Hero_Turn(transStepScaleSq * 0.027f, transStepScaleSq * 0.3f,
                      frameTime * 5.934119f * Hero.padMagnitude, 0);

        if (padState.bits & (PAD_L2 | PAD_R2)) {
            float keep;

            keep = Hero.idealRotZ;
            Hero.idealRotZ = HeroYawReference[0];
            Hero_Turn(transStepScaleSq * 0.017f, transStepScaleSq * 0.3f, frameTime * 4.712389f, 0);
            Hero.idealRotZ = keep;
        }

        jumpAccel = frameTimeSq * 7.0f;

        if (Hero.padMagnitude < 0.2f)
            jumpAccel = frameTimeSq * 3.5f;

        Hero_JumpTranslation(jumpAccel);
        Hero_SetBankTwistSway();
        Hero_KneeBumpMotion(1);

        if (fast) {
            Hero_ForwardComponent(&Hero.velocity, &Hero.velocity);
            Hero_AddGravity(&Hero.velocity, &Hero.velocity, airAccel * 0.72f);
            Hero.groundSpringVelocity = Hero.velocity.z;
        }

        else
            AccelDelt(Hero.position.z, Hero.groundHeight + 0.17f, Hero.groundSpringVelocity,
                      transStepScaleSq * 0.02f, transStepScaleSq * 0.35f, frameTime * 2.5f);
    } break;
    case HERO_STATE_LAND: {
        float airSpeed;

        if (Hero_GetGadgetMoby(3) == 2) {
            if (Hero.loopSounds[4] != -1) {
                SoundVoice *voiceRow = &audioState.rows[Hero.loopSounds[4]];

                if (voiceRow[1].pMoby == Hero.moby && voiceRow[1].inUse != 0)
                    sound_KillChannel(Hero.loopSounds[4]);
            }

            Hero.loopSounds[4] = -1;
            Hero_PlayLoopSound(3, Hero.moby, 2);
        }

        else {
            if (Hero.loopSounds[3] != -1) {
                SoundVoice *voiceRow = &audioState.rows[Hero.loopSounds[3]];

                if (voiceRow[1].pMoby == Hero.moby && voiceRow[1].inUse != 0)
                    sound_KillChannel(Hero.loopSounds[3]);
            }

            Hero.loopSounds[3] = -1;
            Hero_PlayLoopSound(4, Hero.moby, 0x12);
        }

        airSpeed = frameTime * 3.0f;

        if (Hero.items[3].itemId == 3)
            airSpeed = frameTime * 5.0f;

        Hero_GetIdealThrustFromPad(airSpeed, 0);
        Hero_Turn(transStepScaleSq * 0.025f, transStepScaleSq * 0.3f, frameTime * 12.566371f, 0);
        Hero_ThrustModeAccel(frameTimeSq * 15.0f, frameTimeSq * 7.0f);
        Hero_ThrustToMotionFwd(99999.0f);
        Hero_SetBankTwistSway();
        Hero_ForwardComponent(&Hero.velocity, &Hero.velocity);
        Hero_AddGravity(&Hero.velocity, &Hero.velocity, airSpeed * 0.72f);

        if (Hero.position.z < Hero.smoothedGroundZ)
            Delt(Hero.smoothedGroundZ, Hero.position.z, frameTime * 4.0f);

        Hero_UpdateLedge();
    } break;
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
    case HERO_STATE_CLANK_JUMP:
    case HERO_STATE_CLANK_EDGE_JUMP:
    case HERO_STATE_GIANT_CLANK_JUMP:
    case HERO_STATE_QUICKSAND_JUMP:
        if (Hero.state == HERO_STATE_LEDGE_JUMP && Hero.hasClank == 0 &&
            Hero.items[3].itemId == 3) {
            if (Hero_AnimFrameInWindow(10.0f))
                Hero_PlaySound(4, 0);
        }

        if (Hero.tookOffFromIce != 0 && Hero.onIceGround != 0)
            Hero.idealSpeed = Hero.storedNeutralSpeed;

        else {
            if (Hero.dustHoverState != 0)
                Hero_GetIdealThrustFromPad(frameTime * 5.7f, 0);

            Hero_GetIdealThrustFromPad(Hero.airStickSpeed, 0);
        }

        if (Hero.state == HERO_STATE_WATER_JUMP) {
            if (Hero.stateTimer == FastScaleRoundInt(0x14)) {
                Hero_SpawnWaterSplash(3, 0x10, 1);

                if (WaterTiles != 0)
                    WaterTile_PutDrop(WaterTiles, WaterTileCnt, 0, Hero.position.x, Hero.position.y,
                                      0.4f, 0.35f);
            }

            if (Hero.animFrame >= 4.0f && Hero.animFrame <= 7.0f)
                Hero_SpawnWaterBubbles(7, 0);
        }

        {
            int timer;
            int lim;

            timer = Hero.stateTimer;
            lim = Hero.takeoffFrame;

            if (timer == lim)
                CopyVec4Inline(&Hero.takeoffPos, &Hero.position);

            if (Hero.dustHoverState != 0 ||
                (timer < lim && Hero.state != HERO_STATE_FLIP_JUMP &&
                 Hero.state != HERO_STATE_THRUSTER_PACK_FORWARD_JUMP &&
                 Hero.state != HERO_STATE_STORED_HEADING_JUMP &&
                 Hero.state != HERO_STATE_WALL_JUMP && Hero.state != HERO_STATE_LEDGE_JUMP &&
                 Hero.state != HERO_STATE_CLANK_EDGE_JUMP)) {
                float keep;

                Hero_Turn(transStepScaleSq * 0.015f, transStepScaleSq * 0.2f,
                          frameTime * 15.009831f, 0);
                keep = Hero.storedNeutralSpeed;

                if (Hero.dustHoverState > 1)
                    Hero.storedNeutralSpeed = keep * 0.4f;

                Hero_ThrustToMotionFwd(99999.0f);
                Hero.storedNeutralSpeed = keep;

                if (Hero.dustHoverState != 1)
                    Hero_ThrustModeAccel(Hero.airSpeedStepUp, Hero.jumpDecel);

                if (Hero.onMagnerail != 0)
                    Hero.storedNeutralSpeed = 0.0f;

                if (Hero.dustHoverState != 0) {
                    if (padState.handsOffStick != 0) {
                        if (Hero.onFlaggedGroundMoby != 0)
                            Hero.storedNeutralSpeed = 0.0f;
                    }
                }

                if (Hero.dustHoverState != 0)
                    Hero_ApplyFriction(Hero.jumpDecel);

                Hero_ThrustToMotion(0.5f, frameTime * 2.0f);

                if (Hero.state == HERO_STATE_RUN_JUMP &&
                    Hero.stateTimer < Hero.takeoffFrame + FastScaleRoundInt(4))
                    Hero_ToWorldVector(&Hero.velocity, &Hero.velocity,
                                       frameTimeSq * 16.0f * Hero.stateTimer);

                if (Hero.state == HERO_STATE_HELI_PACK_FWD_JUMP) {
                    if (Hero.stateTimer < FastScaleRoundInt(0x22))
                        Hero_ToWorldVector(&Hero.velocity, &Hero.velocity,
                                           frameTimeSq * 53.0f * Hero.stateTimer);
                }

                if (Hero.stateTimer < FastScaleRoundInt(0xA) && Hero.padMagnitude > 0.2f) {
                    CopyVec4Inline(&scratch.jumpProbe.start, &Hero.position);
                    Hero_ToWorldPos(&scratch.jumpProbe.start, &scratch.jumpProbe.start, 0.5f);
                    CopyVec4Inline(&scratch.jumpProbe.end, &scratch.jumpProbe.start);
                    scratch.jumpProbe.end.x += FastAngleSinF(Hero.rotation.z) * 0.85f;
                    scratch.jumpProbe.end.y += FastAngleCosF(Hero.rotation.z) * 0.85f;

                    if (CollLine(&scratch.jumpProbe.start, &scratch.jumpProbe.end, 4, Hero.moby,
                                 0))
                        Hero.jumpBlockedAhead = 1;
                }
            }

            else {
                Hero_JumpTurnTrans();

                if (Hero.state == HERO_STATE_WATER_JUMP) {
                    float len;

                    len = FastVec3Length(&Hero.velocity);

                    if (len > frameTime * 3.7f)
                        len = frameTime * 3.7f;

                    FastVec3RSqrtScale(&Hero.velocity, &Hero.velocity, len);
                }
            }
        }

        if (Hero.groundHeight > Hero.smoothedGroundZ) {
            Hero.smoothedGroundZ = Hero.smoothedGroundZ + frameTime * 6.0f;

            if (Hero.smoothedGroundZ > Hero.groundHeight)
                Hero.smoothedGroundZ = Hero.groundHeight;
        }

        if (Hero.position.z < Hero.smoothedGroundZ)
            Hero.smoothedGroundZ = Hero.position.z;

        if (Hero.stateTimer > Hero.takeoffFrame &&
            Hero_RelativeZComponent(&Hero.velocity) < 0.001f &&
            (Hero.velocityKeysActive == 0 || Hero.stateTimer > Hero.velocityKeysEndFrame)) {
            Hero.pastJumpApex = 1;

            if (Hero.fallGravity != 0.0f)
                Hero.jumpGravity = Hero.fallGravity;
        }

        if (Hero.type == HERO_TYPE_RATCHET)
            Hero_SetBankTwistSway();

        if (Hero.state == HERO_STATE_THRUSTER_PACK_FORWARD_JUMP ||
            Hero.state == HERO_STATE_ROCKET_JUMP) {
            int late;

            late = Hero.stateTimer > FastScaleRoundInt(0xC);
            UpdateMotionBlur(&Hero.trail, late * 2);
        }

        if (Hero.state == HERO_STATE_THRUSTER_PACK_FORWARD_JUMP &&
            Hero.stateTimer > FastScaleRoundInt(8)) {
            if (Hero.animFrame < 28.0f) {
                int hitCount;

                Hero_GetHeroRelativePos(&scratch.crateSmash.center, 0.8f, 0.0f, 0.3f);
                hitCount = CollMobySphere(0.9f, &scratch.crateSmash.center, 0, Hero.moby, 0);

                if (hitCount != 0) {
                    int crateIndex;

                    FastVec3Scale(&scratch.crateSmash.shove, &Hero.displacement, 7.0f);

                    for (crateIndex = 0; crateIndex < hitCount; crateIndex++) {
                        if (MB_isCrate(HeroSphereQueryResults[crateIndex]))
                            CollDamageMobyDirect_2(HeroSphereQueryResults[crateIndex], Hero.moby, 0x10000,
                                                   &Hero.position, &scratch.crateSmash.shove, 1.0f);
                    }
                }
            }
        }

        Hero_JumpThrustGrav();
        Hero_UpdateLedge();
        break;
    case HERO_STATE_GET_HIT: {
        float len;
        float dec;

        len = FastVec3Length(&Hero.velocity);
        dec = frameTimeSq * 4.0f;

        if (Hero.framesNotGrounded == 0 && Hero.stateTimer > FastScaleRoundInt(0xA))
            dec = frameTimeSq * 10.0f;

        len -= dec;

        if (len < 0.0f)
            len = 0.0f;

        if (Hero.onMagnetGround != 0)
            Hero_EdgeStop(3.7f, 0.0f);

        FastVec3RSqrtScale(&Hero.velocity, &Hero.velocity, len);
        Hero_AddGravity(&Hero.velocity, &Hero.velocity, 0.004f);
    } break;
    case HERO_STATE_WALK_TO_POS: {
        float len;
        float thrustScale;

        FastSubVec3(&scratch.walk.toTarget, &Hero.targetPose, &Hero.position);
        Hero.idealRotZ = FastArcTan(scratch.walk.toTarget.x, scratch.walk.toTarget.y);
        len = FastVec3Length(&scratch.walk.toTarget);

        if (len > 0.2f) {
            Hero.padMagnitude = 1.0f;
            Hero.idealRotZ = FastArcTan(scratch.walk.toTarget.x, scratch.walk.toTarget.y);
            Hero.idealSpeed = len;

            if (len < HeroJumpSpeeds.minRunSpeed)
                Hero.idealSpeed = HeroJumpSpeeds.lowStepSpeed * frameTime;

            else
                Hero.idealSpeed = HeroJumpSpeeds.stepSpeed * frameTime;

            if (Hero.type == 3)
                Hero.idealSpeed = frameTime * 1.5f;

            else if (Hero.type == HERO_TYPE_CLANK)
                Hero.idealSpeed = frameTime * 0.9f;
        }

        else {
            Hero.padMagnitude = 0.5f;
            Hero.idealRotZ = Hero.targetPose.w;
            Hero.idealSpeed = 0.0f;
        }

        thrustScale = 1.0f;

        if (Hero.type == 3)
            Hero_Turn(transStepScaleSq * 0.03f, transStepScaleSq * 0.3f, frameTime * 5.5850534f, 0);

        else if (Hero.type == HERO_TYPE_CLANK)
            Hero_Turn(transStepScaleSq * 0.03f, transStepScaleSq * 0.3f, frameTime * 7.8539815f, 0);

        else if (Hero.type == HERO_TYPE_RATCHET) {
            if (Hero.subState == 1)
                Hero_Turn(transStepScaleSq * 0.016f, transStepScaleSq * 0.15f,
                          frameTime * 9.948377f, 0);

            else
                Hero_TurnWalk();
        }

        if (Hero.type == HERO_TYPE_RATCHET)
            Hero_SetBankTwistSway();

        Hero_ThrustModeAccel(frameTimeSq * 7.5f * thrustScale, frameTimeSq * 8.5f);
        Hero_ThrustToMotionFwd(99999.0f);

        if (Hero.type == HERO_TYPE_RATCHET)
            Hero_KneeBumpMotion(1);

        if (Hero.framesNotGrounded != 0) {
            Hero_AddGravity(&Hero.velocity, &Hero.displacement, frameTimeSq * 25.0f);
            Hero_WallSloopMotion();
        }

        else
            Hero_AddGravity(&Hero.velocity, &Hero.velocity, frameTimeSq * 54.0f);
    } break;
    case HERO_STATE_SKID_TO_POS: {
        FastSubVec3(&scratch.skid.toTarget, &Hero.targetPose, &Hero.position);

        if (FastVec3Dot(&scratch.skid.toTarget, &Hero.externalMomentum) < 0.0f)
            FastVecZero(&Hero.externalMomentum);

        FastVecZero(&Hero.velocity);
        Hero_ApplyFriction(frameTimeSq * 12.0f);
        Hero_KneeBumpMotion(0);

        if (Hero.framesNotGrounded != 0) {
            Hero_AddGravity(&Hero.velocity, &Hero.displacement, frameTimeSq * 25.0f);
            Hero_WallSloopMotion();
        }

        else
            Hero_AddGravity(&Hero.velocity, &Hero.velocity, frameTimeSq * 54.0f);
    } break;
    case HERO_STATE_FIDGET:
    case HERO_STATE_IDLE_TO_POS:
        FastVecZero(&Hero.velocity);
        break;
    case HERO_STATE_HOLOGUISE_STANDING:
    case HERO_STATE_HOLOGUISE_DYING:
    case HERO_STATE_HOLOGUISE_WAVE:
        Hero_EdgeStop(3.7f, 0.0f);
        Hero_GetIdealThrustFromPad(1.0f, 0);
        Hero.idealSpeed = 0.0f;
        Hero_ThrustModeAccel(0.0f, frameTimeSq * 12.6f);
        FastVecZero(&Hero.velocity);
        Hero_ApplyFriction(frameTimeSq * 12.6f);
        Hero_KneeBumpMotion(0);

        if (Hero.framesNotGrounded != 0) {
            Hero_AddGravity(&Hero.velocity, &Hero.resolvedVelocityZ, frameTimeSq * 25.0f);
            Hero_WallSloopMotion();
        }

        else
            Hero_AddGravity(&Hero.velocity, &Hero.velocity, frameTimeSq * 54.0f);

        break;
    case HERO_STATE_HOLOGUISE_SLIP:
        Hero.idealRotZ = Hero.groundAngZ;
        Hero.idealSpeed = frameTime * 5.5f;
        Hero_JumpTranslation(frameTimeSq * 25.0f);
        Hero_AddGravity(&Hero.velocity, &Hero.resolvedVelocityZ, frameTimeSq * 18.0f);
        break;
    case HERO_STATE_HOLOGUISE_FALLING:
        Hero_GetIdealThrustFromPad(frameTime * 1.5f, 0);

        if (Hero.moveLockTimer == 0)
            Hero_JumpTurnTrans();

        Hero_AddGravity(&Hero.velocity, &Hero.velocity, frameTimeSq * 21.0f);

        if (Hero.velocity.z < frameTime * -15.0f)
            Hero.velocity.z = frameTime * -15.0f;

        break;
    case HERO_STATE_HOLOGUISE_WALKING: {
        float yawDifference;
        float thrustScale;
        float turnScale;

        yawDifference = FastDiffRots(Hero.rotation.z, Hero.idealRotZ);
        Hero_GetIdealThrustFromPad(frameTime * 1.5f, 0);

        if (Hero.idealSpeed < frameTime * 1.5f * 0.55f)
            Hero.idealSpeed = frameTime * 1.5f * 0.55f;

        thrustScale = 1.0f;
        thrustScale -= yawDifference * 0.3f;
        turnScale = Hero.padMagnitude + 0.35f;

        if (thrustScale < 0.0f)
            thrustScale = 0.0f;

        Hero_Turn(transStepScaleSq * 0.035f * turnScale, transStepScaleSq * 0.1f, frameTime * 2.268928f * turnScale,
                  0);
        Hero_ThrustModeAccel(frameTimeSq * 7.5f * thrustScale, frameTimeSq * 8.5f);

        if (Hero.moveAlongStick != 0 && Hero.onMagnerail == 0)
            Hero_ThrustToMotionFwd(Hero.idealRotZ);

        else
            Hero_ThrustToMotionFwd(99999.0f);

        Hero_KneeBumpMotion(1);

        if (Hero.framesNotGrounded != 0) {
            Hero_AddGravity(&Hero.velocity, &Hero.resolvedVelocityZ, frameTimeSq * 25.0f);
            Hero_WallSloopMotion();
        }

        else
            Hero_AddGravity(&Hero.velocity, &Hero.velocity, frameTimeSq * 54.0f);
    } break;
    case HERO_STATE_HOLOGUISE_DAMAGE: {
        float len;

        heroVelocity = &Hero.velocity;
        len = FastVec3Length(heroVelocity);
        FastVecNormalizeScaled((Hero.framesNotGrounded != 0 ? transStepScale * -0.00999999f
                                                            : transStepScale * -0.07999998f) *
                                       len +
                                   len,
                               &Hero.velocity, &Hero.velocity);
        Hero.velocity.z = 0.0f;

        if (Hero.framesNotGrounded != 0)
            Hero_AddGravity(&Hero.velocity, &Hero.resolvedVelocity, frameTimeSq * 24.0f);

        else
            Hero_AddGravity(&Hero.velocity, &Hero.velocity, 0.004f);
    } break;
    case HERO_STATE_NPC:
    case HERO_STATE_CUSTOM_UI:
        FastVecZero(&Hero.velocity);
        break;
    }

    if (prevState != Hero.subState)
        Hero.stepFrames = 0;

    if (prevAnim != moby->animationId)
        Hero.animSeqFrames = 0;
}

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
            Hero_TransAnim(HERO_ANIM_DEATH_FALL, 0, (float)FastScaleRoundInt(0xC));

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
            Hero_TransAnim(HERO_ANIM_FACE_SHOCKED, 0, (float)FastScaleRoundInt(0xB));

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
                Hero_TransAnim(HERO_ANIM_SWIM_FORWARD, 0, (float)blendFrames);
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
            Hero_TransAnim(HERO_ANIM_HYDRO_PACK_SWIM, 0, (float)blendFrames);

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
            Hero_TransAnim(HERO_ANIM_UNDERWATER_IDLE, 0, (float)blendFrames);

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
                Hero_TransAnim(HERO_ANIM_WATER_IDLE, 0, (float)FastScaleRoundInt(0x16));
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
                    Hero_TransAnim(HERO_ANIM_SWIM_HIT_B, 3, -3.0f);

                else
                    Hero_TransAnim(HERO_ANIM_SWIM_HIT_A, 3, -3.0f);

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
            Hero_TransAnim(HERO_ANIM_SWIM_SLIDE, 0, (float)FastScaleRoundInt(0x11));

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
            Hero_TransAnim(HERO_ANIM_DROWNING, 0, (float)FastScaleRoundInt(0xA));

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
        Hero_TransAnim(HERO_ANIM_SHOOT_A, 0, (float)FastScaleRoundInt(5));
        break;
    }

    case HERO_STATE_WALK:
    case HERO_STATE_MAGNE_WALK:

    case HERO_STATE_WADE: {
        HeroState *hero = &Hero;

        hero->stateType = HERO_STATE_TYPE_RUN;
        hero->requestedCamType = 0;

        if (hero->prevStateType != HERO_STATE_TYPE_JUMP &&
            hero->prev2StateType != HERO_STATE_TYPE_JUMP)
            hero->storedNeutralSpeed = FastVec3Length(&hero->resolvedVelocity.x);

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
                Hero_TransAnim(HERO_ANIM_WADE_STRUGGLE, 0, (float)FastScaleRoundInt(8));
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
                Hero_TransAnim(HERO_ANIM_LOOK_RIGHT, 0, (float)FastScaleRoundInt(8));

            else if (hero->type == HERO_TYPE_CLANK)
                Hero_TransAnim(HERO_ANIM_LOOK_LEFT, 0, (float)FastScaleRoundInt(8));

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
            Hero_TransAnim(HERO_ANIM_WATER_SLIDE, 0, (float)FastScaleRoundInt(0xF));

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

            if (Hero_GetAnim(moby->updateId) == HERO_ANIM_RUN && 3.0f < frame && frame < 16.0f)
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

            if (Hero_GetAnim(moby->updateId) == HERO_ANIM_RUN && 3.0f < frame && frame < 16.0f)
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
                    Hero_TransAnim(HERO_ANIM_CROUCH, 2, (float)FastScaleRoundInt(9));

                else
                    Hero_TransAnim(HERO_ANIM_CROUCH, 2, (float)FastScaleRoundInt(0xE));

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
            Hero_TransAnim(HERO_ANIM_GROUND_POUND_DOWN, 0, (float)FastScaleRoundInt(6));

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
                Hero_TransAnim(HERO_ANIM_LEDGE_GRAB, 0, (float)FastScaleRoundInt(9));

            else
                Hero_TransAnim(HERO_ANIM_LEDGE_GRAB, 1, (float)(FastScaleRoundInt(9) + 2));
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
            Hero_TransAnim(HERO_ANIM_LEDGE_HANG, 0, (float)FastScaleRoundInt(6));

        break;
    }

    case HERO_STATE_LEDGE_TRAVERSE_LEFT: {
        HeroState *hero = &Hero;

        hero->stateType = HERO_STATE_TYPE_LEDGE;
        hero->requestedCamType = 0xD;
        hero->itemSelectBlocked = 1;

        if (animMode)
            Hero_TransAnim(HERO_ANIM_LEDGE_MOVE_RIGHT_HAND, 0, (float)FastScaleRoundInt(6));

        break;
    }

    case HERO_STATE_LEDGE_TRAVERSE_RIGHT: {
        HeroState *hero = &Hero;

        hero->stateType = HERO_STATE_TYPE_LEDGE;
        hero->requestedCamType = 0xD;
        hero->itemSelectBlocked = 1;

        if (animMode)
            Hero_TransAnim(HERO_ANIM_LEDGE_MOVE_LEFT_HAND, 0, (float)FastScaleRoundInt(6));

        break;
    }

    case HERO_STATE_SLOPESLIDE: {
        HeroState *hero = &Hero;

        hero->stateType = HERO_STATE_TYPE_FALL;
        hero->requestedCamType = 0;
        CopyVec4Inline(&hero->velocity, &hero->resolvedVelocity);

        if (animMode)
            Hero_TransAnim(HERO_ANIM_FALL, 0, (float)FastScaleRoundInt(0xC));

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
                    Hero_TransAnim(HERO_ANIM_SKID_LEFT, 0, (float)FastScaleRoundInt(8));
                    return 1;
                }

                if (1.75f < hero->groundDist) {
                    Hero_TransAnim(HERO_ANIM_FALL, 0, (float)FastScaleRoundInt(0xC));
                    hero->subState = 1;
                }

                else
                    Hero_TransAnim(HERO_ANIM_FALL_STATIC, 0, (float)FastScaleRoundInt(0xA));
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
            Hero_TransAnim(HERO_ANIM_GLIDE, 0, (float)animation_timing_override);

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
            Hero_TransAnim(HERO_ANIM_GLIDE, 0, (float)animation_timing_override);

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
            state <= HERO_STATE_GRIND_SWITCH_JUMP)
            hero->requestedCamType = 3;

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
                    Hero_TransAnim(HERO_ANIM_JUMP, 0, (float)FastScaleRoundInt(5));

                else if (currentState == HERO_STATE_WATER_JUMP)
                    Hero_TransAnim(HERO_ANIM_WATER_EXIT_JUMP, 1, -1.0f);

                else if (currentState == HERO_STATE_RUN_JUMP) {
                    int animation = 8;
                    int frameIndex = FastFloatToInt(hero->animFrame);

                    if (Hero_GetAnim(moby->updateId) == HERO_ANIM_RUN)
                        animation = HeroRunJumpAnims[frameIndex];

                    Hero_TransAnim(animation, 0, (float)FastScaleRoundInt(5));
                }

                else if (currentState == HERO_STATE_HELI_PACK_FWD_JUMP)
                    Hero_TransAnim(HERO_ANIM_LONG_JUMP_HELI, 0, (float)FastScaleRoundInt(5));

                else if (currentState == HERO_STATE_THRUSTER_PACK_FORWARD_JUMP) {
                    if (hero->prevStateType == HERO_STATE_TYPE_JUMP ||
                        (hero->prevState == HERO_STATE_CROUCH && FastScaleRoundInt(7) > hero->stateTimer)) {
                        Hero_TransAnim(HERO_ANIM_THRUSTER_PACK_FORWARD, 0, (float)FastScaleRoundInt(8));
                        hero->takeoffFrame += FastScaleRoundInt(3);
                    }

                    else
                        Hero_TransAnim(HERO_ANIM_THRUSTER_PACK_FORWARD, 0, (float)FastScaleRoundInt(5));
                }

                else if (currentState == HERO_STATE_LEDGE_JUMP)
                    Hero_TransAnim(HERO_ANIM_LEDGE_PULL_UP, 0, (float)FastScaleRoundInt(4));

                else if (currentState == HERO_STATE_WALL_JUMP)
                    Hero_TransAnim(HERO_ANIM_WALL_JUMP, 2, (float)FastScaleRoundInt(7));

                else if (currentState == HERO_STATE_ROCKET_JUMP)
                    Hero_TransAnim(HERO_ANIM_GROUND_POUND, 0, (float)FastScaleRoundInt(5));

                else if (currentState == HERO_STATE_DOUBLE_JUMP) {
                    Hero_TransAnim(HERO_ANIM_DOUBLE_JUMP, 3, (float)FastScaleRoundInt(7));
                    hero->animSpeed = transStepScale * 0.8f;
                }

                else if (currentState == HERO_STATE_HELI_JUMP)
                    Hero_TransAnim(HERO_ANIM_HIGH_JUMP_HELI, 0, (float)FastScaleRoundInt(5));

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

                Hero_TransAnim(HERO_ANIM_HYPERSTRIKE, 4, (float)blendFrames);
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
                itemUsage[ITEM_COUNT].latestTimeBucket)
                itemUsage[ITEM_COUNT].latestTimeBucket = FastScaleRoundInt(TotalPlayTime) / 600;

            itemUsage[ITEM_COUNT].levelMask =
                itemUsage[ITEM_COUNT].levelMask | (1 << Level) | USAGE_STAT_USED;
            hero = &Hero;
            hero->attackRecord = 3;
            hero->savedItem[0] = 0;
            Hero_UpdateAutoTargetAim(14.0f, 0.5235988f, -1.0f);
            hero->crouchSwingToggle = hero->crouchSwingToggle == 0;

            if (animMode) {
                int blendFrames = FastScaleRoundInt(0xA);

                if (hero->moby->animationId == HERO_ANIM_WRENCH_THROW)
                    blendFrames = FastScaleRoundInt(3);

                if (hero->prevState == HERO_STATE_LOOK)
                    blendFrames = FastScaleRoundInt(0x11);

                Hero_TransAnim(HERO_ANIM_WRENCH_THROW, 0, (float)blendFrames);
                Hero_SetNextAnimFrame(6, 0x15);
            }

            break;
        }

        case HERO_STATE_WALLOPER_ATTACK: {
            HeroState *hero = &Hero;

            if (hero->items[0].moby == 0)
                break;

            if (animMode) {
                Hero_TransAnim(HERO_ANIM_WALLOPER_PUNCH, 4, -1.0f);
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
                hero->animFrame < (float)attack->chainBeforeFrame)
                comboKind = (attack->kind + 1) % 3;

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
                Hero_TransAnim(comboKind + HERO_ANIM_WRENCH_SWING_RIGHT, animOffset, (float)blendFrames);
                gadget = Hero_HandGadgetID(0);

                if (Hero_isMobyWrench(gadget))
                    MB_SetAnimation(gadget, comboKind + 3, animOffset, blendFrames);
            }

            break;
        }

        case HERO_STATE_THROWING_ITEM: {
            HeroState *hero;

            if (animMode)
                Hero_TransAnim(HERO_ANIM_THROW, 7, (float)FastScaleRoundInt(9));

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
            Hero_TransAnim(comboKind + HERO_ANIM_BONK_0, 5, (float)blendFrames);
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
            Hero_TransAnim(HERO_ANIM_BONK_2, 5, (float)FastScaleRoundInt(8));

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
                Hero_TransAnim(HERO_ANIM_HIT, 3, -3.0f);
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
            Hero_TransAnim(HERO_ANIM_IDLE, 0, (float)FastScaleRoundInt(0xE));

        break;
    }

    case HERO_STATE_HOLOGUISE_WAVE: {
        HeroState *hero = &Hero;

        hero->stateType = HERO_STATE_TYPE_IDLE;
        hero->requestedCamType = 0;

        if (animMode) {
            Hero_TransAnim(HERO_ANIM_RUN, 0, (float)FastScaleRoundInt(7));
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
            Hero_TransAnim(HERO_ANIM_SKID_LEFT, 0, (float)FastScaleRoundInt(0xC));

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
            Hero_TransAnim(HERO_ANIM_SKID_LEFT, 0, (float)FastScaleRoundInt(7));

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
                Hero_TransAnim(HERO_ANIM_LOOK_RIGHT, 0, (float)FastScaleRoundInt(8));
        }

        break;
    }

    case HERO_STATE_HOLOGUISE_DYING: {
        HeroState *hero = &Hero;

        hero->stateType = HERO_STATE_TYPE_DYING;
        hero->requestedCamType = 0;
        CopyVec4Inline(&hero->externalMomentum, &hero->resolvedVelocity);

        if (animMode)
            Hero_TransAnim(HERO_ANIM_WALK, 0, (float)FastScaleRoundInt(0xC));

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
            Hero_TransAnim(HERO_ANIM_LOOK_LEFT, 3, -3.0f);
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
            Hero_TransAnim(HERO_ANIM_HIT, 2, -3.0f);

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
            Hero_GetIdleAnim(1))
            Hero_TransAnim(Hero_GetIdleAnim(1), 0, (float)FastScaleRoundInt(5));

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
            Hero_TransAnim(HERO_ANIM_FALL, 0, -1.0f);

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
        Hero_TransAnim(HERO_ANIM_PUSH_SIDEWAYS, 2, (float)blendFrames);
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
            hero->savedItem[1] != 0)
            hero->restoreItem[1] = 1;
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
float FastVec3DistLen(Vec4 *from, Vec4 *to);
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
            (Hero.state == HERO_STATE_IDLE || Hero.state == HERO_STATE_WALK))
            Hero_InitBodyState(HERO_STATE_DEATH, 1);

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
                            ActionUsageStats[31].latestTimeBucket)
                            ActionUsageStats[31].latestTimeBucket =
                                FastScaleRoundInt(TotalPlayTime) / 600;

                        ActionUsageStats[31].levelMask = ActionUsageStats[31].levelMask |
                                                          (1 << Level) | 0x80000000;
                        Hero.pendingItem[0] = quickSwapTarget;
                        Hero.quickSwapTapTimer = 0;
                        Hero.quickSwapTapWindow = 0;
                    }
                }
            }

            if (HeroDeathHeight > Hero.position.z && Hero.groundDist > 2.0f &&
                Hero.type != HERO_TYPE_GIANT_CLANK && Hero.state != HERO_STATE_DEATH_FALL)
                Hero_InitBodyState(HERO_STATE_DEATH_FALL, 1);

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
                                Hero_GetIdleAnim(0))
                                Hero_TransAnim(Hero_GetIdleAnim(0), 0, -2.0f);

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

                        if (0.61086524f < HeroTweaks[3].rot.z ||
                            HeroTweaks[3].rot.y > 0.43633232f) {
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
                                    Hero.heldItemAnimMoby[0] != 0)
                                    keepHoldAnimation = 1;
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
                                if (0.55850536f > HeroTweaks[3].rot.z &&
                                    HeroTweaks[3].rot.y < 0.34906584f && Hero.items[3].state == 2) {
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
                                        Hero.idealRotZ, HeroYawReference[0]) > 1.2217305f)
                                    walkAllowed = 0;
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
                        !(padState.bits & (PAD_R2 | PAD_R1)))
                        Hero_InitBodyState(HERO_STATE_IDLEUNDER, 1);

                    break;

                case HERO_STATE_IDLEUNDER:
                    if (Hero.animFlags & 2) {
                        if (Hero.moby->animationId != 0x3C)
                            Hero_TransAnim(HERO_ANIM_UNDERWATER_IDLE, 0, FastScaleRoundInt(0xB));
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
                        Hero_TransAnim(HERO_ANIM_WADE_STRUGGLE, 0, FastScaleRoundInt(0x11));
                        Hero.velocity.z = 0.0f;
                        Hero.displacement.z = 0.0f;
                    }

                    if (0.1f > Hero.padMagnitude && Hero.storedNeutralSpeed == 0.0f &&
                        Hero.swimStrokeTimer == 0)
                        Hero_InitBodyState(HERO_STATE_IDLESURF, 1);

                    break;

                case HERO_STATE_GET_HIT_UNDER:
                    if (Hero.health <= 0) {
                        if (Level == LEVEL_QUARTU ||
                            Level == LEVEL_VELDIN_ORBIT) {
                            Hero_InitBodyState(HERO_STATE_ELECTRIC_DEATH_UNDER, 1);
                            break;
                        }

                        Hero_InitBodyState(HERO_STATE_DROWN, 1);
                        Hero_TransAnim(HERO_ANIM_DROWNING, 0x28, FastScaleRoundInt(0x12));
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
                        Hero_TransAnim(HERO_ANIM_DROWNING, 0x25, FastScaleRoundInt(0x12));
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
                                    Hero_TransAnim(HERO_ANIM_CROUCH, 0, FastScaleRoundInt(8));
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
                        (moby->animationBlend > 0.9f || moby->updateId != 0xFF))
                        Hero.runStartBlending = 0;

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
                        if ((padState.bitsOn & PAD_STICK_FLICK) && Hero.weaponUp == 0)
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
                                        Hero_TransAnim(HERO_ANIM_SLIDE, 7, FastScaleRoundInt(9));

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
                            frameTime * 2.7f <= Hero.speedXY)
                            Hero_InitBodyState(HERO_STATE_SKID_TO_POS, 1);

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
                            voiceRow[1].inUse != 0)
                            sound_KillChannel(Hero.loopSounds[2]);
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
                        Hero.prevState != HERO_STATE_TAKING_DAMAGE_LAVA && (padState.bitsOn & PAD_CROSS))
                        Hero_InitBodyState(HERO_STATE_THRUSTER_PACK_FORWARD_JUMP, 1);

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
                        Hero_TransAnim(HERO_ANIM_LEDGE_HANG, 0, FastScaleRoundInt(6));

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
                                                  &positiveShimmyProbeYaw))
                            Hero_InitBodyState(HERO_STATE_LEDGE_TRAVERSE_LEFT, 1);

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
                                                  &negativeShimmyProbeYaw))
                            Hero_InitBodyState(HERO_STATE_LEDGE_TRAVERSE_RIGHT, 1);
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
                            Hero_TransAnim(HERO_ANIM_FALL, 0, FastScaleRoundInt(0x10));
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
                                Hero_TransAnim(HERO_ANIM_LAND, 4, FastScaleRoundInt(6));

                            if (landedOffMoby)
                                Hero.moveLockTimer = FastScaleRoundInt(0x16);

                            Hero_SetTiltWobbleParams(0.022f, 0.004f, 0xA, 4, 0, 1);
                            break;
                        }

                        if (Hero.subState == heavyLandSubState) {
                            if (Hero_InitBodyState(HERO_STATE_IDLE, 0))
                                Hero_TransAnim(HERO_ANIM_LAND, 9, -1.0f);

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

                            Hero_TransAnim(HERO_ANIM_SKID_LEFT, 0, FastScaleRoundInt(0xC));
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

                        Hero_TransAnim(HERO_ANIM_JUMP, 0x17, FastScaleRoundInt(9));
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
                                Hero.prevState == HERO_STATE_DOUBLE_JUMP || Hero.prevState == HERO_STATE_WALL_JUMP)
                                wasAirborne = 1;

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
                        !(Hero.position.z - Hero.groundHeight < 0.4f))
                        break;

                    if (FastScaleRoundInt(0xA) > Hero.stateTimer)
                        Hero.jumpBufferLockout = FastScaleRoundInt(0xC) - Hero.stateTimer;

                    Hero_GetIdealThrustFromPad(1.0f, 0);

                    if (Hero.prevState == HERO_STATE_THRUSTER_PACK_FORWARD_JUMP && FastScaleRoundInt(4) > Hero.stateTimer) {
                        if (Hero_InitBodyState(HERO_STATE_SKID, 0) == 0)
                            break;

                        Hero_TransAnim(HERO_ANIM_SKID_RIGHT, 0, -1.0f);
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
                            Hero_TransAnim(HERO_ANIM_RUN, 2, FastScaleRoundInt(8));
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
                            Hero_TransAnim(HERO_ANIM_RUN, HeroSlideAnimFrames[1], FastScaleRoundInt(0xC));
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

                    Hero_TransAnim(HERO_ANIM_JUMP, 0x17, FastScaleRoundInt(9));
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
                            frameTime * 0.9f < Hero.forwardSpeed)
                            Hero_InitBodyState(HERO_STATE_HELI_PACK_FWD_JUMP, 1);

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
                                FastFloatToInt(Hero.targetAnimFrame))
                                Hero.animSpeed = 0.0f;
                        }
                    }

                    if (Hero.dustHoverState != 0) {
                        if (Hero.state == HERO_STATE_HELI_PACK_FWD_JUMP) {
                            if (Hero_InitBodyState(HERO_STATE_SKID, 0) == 0)
                                break;

                            Hero_TransAnim(HERO_ANIM_SKID_RIGHT, 0, -2.0f);
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
                        Hero.state != HERO_STATE_HELI_PACK_FWD_JUMP)
                        Hero_JumpLandTransitions();

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
                            Hero.state == HERO_STATE_WALL_JUMP)
                            inJumpState = 1;

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
                            Hero.onFlaggedGroundMoby != 0)
                            Hero.packGlideDelay = FastScaleRoundInt(0x14);
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
                                          frameTime * 5.8f)))
                                    Hero_InitBodyState(HERO_STATE_DOUBLE_JUMP, 1);

                                else if (UnlockableItems[ITEM_HELI_PACK] != 0 && Hero_GetGadgetMoby(3) != ITEM_HYDRO_PACK &&
                                           Hero.hasClank == 0 &&
                                           (padState.bits & PAD_CROSS) &&
                                           jumpPackDelay < Hero.stateTimer &&
                                           Hero.packGlideDelay < Hero.stateTimer) {
                                    float maxGroundDistance = 0.6f;

                                    if (Hero.state == HERO_STATE_RUN_JUMP ||
                                        Hero.state == HERO_STATE_JUMP)
                                        maxGroundDistance = 1.0f;

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
                            Hero_TransAnim(HERO_ANIM_IDLE, 0, FastScaleRoundInt(0xC));

                        else if (MB_randRangeFloat(0.0f, 1.0f) < 0.5f)
                            Hero_TransAnim(HERO_ANIM_SKID_RIGHT, 0, FastScaleRoundInt(8));
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
                        Hero_TransAnim(HERO_ANIM_IDLE, 0, FastScaleRoundInt(0x14));
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
                    Hero_TransAnim(HERO_ANIM_JUMP, 0, -1.0f);
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
                                    Hero_TransAnim(HERO_ANIM_CROUCH, 0, FastScaleRoundInt(8));
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
                        Hero.animFrame > 20.0f)
                        Hero_InitBodyState(HERO_STATE_IDLE, 0);

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
        (Hero.prevState == HERO_STATE_FIDGET_ALT && Hero.fidgetPropMoby != 0))
        Hero_CleanupAttachedMobys();

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
