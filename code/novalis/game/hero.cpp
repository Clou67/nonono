#include "common.h"
#include "mathfunc_inline.h"
#include "draw.h"
#include "npc.h"
#include "mobyutil.h"
#include "fastfunc.h"
#include "hero.h"

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_ResetHero);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_InitStuff);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_GetIdleAnim);

int STUB_00226fa0(int animation)
{
    return animation;
}

void Hero_RegisterHealthHud(void);

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
        if (Hero.bootMoby)
            magneboots = (short)Hero.bootMoby->oClass == OCLASS_MAGNEBOOTS;

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

enum { HERO_STATE_TYPE_SPECIAL = 17 };

int Hero_IsInSpecialMovementState(void)
{
    if ((unsigned int)(Hero.stateType - HERO_STATE_TYPE_SPECIAL) < 2 ||
        Hero.state == PLAYER_STATE_DEATH_DROWNING ||
        Hero.state == PLAYER_STATE_DEATH_WATER_LASER ||
        Hero.state == PLAYER_STATE_UNDERWATER_DAMAGE ||
        Hero.state == PLAYER_STATE_UNK_75)
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

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", HandleHeroMovement);

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

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", TransitionMovement);

void TransitionMovement(int state, int force);
void Hero_TransitionToDefault(void)
{
    switch (Hero.type) {
    case HERO_TYPE_RATCHET:
        TransitionMovement(PLAYER_STATE_STANDING, 1);
        break;
    case HERO_TYPE_HOLOGUISE:
        TransitionMovement(PLAYER_STATE_HOLOGUISE_STANDING, 1);
        break;
    }
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_IdleCycleFiringTransition);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", HandleUnderwaterSwimming);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_SwimSurfTransition);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_SurfBob);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_UpdateWeaponInput);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_JumpCheckHeld);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_UpdateWalkAnim);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_CleanupAttachedMobys);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_GetSpecialIdle);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", func_00242194);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_JumpLandTransitions);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_CrouchJumpTransitions);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_ProbeCollAlongVelocity);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_CheckGadgetReady);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", HeroMovement);

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
        item = Hero.currentWeapon;

    if (!VendorPrices[item].maxAmmo)
        return 1;

    return WeaponAmmo[item];
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hero", Hero_StartHit);

int Hero_GetSpecialStateKind(void)
{
    switch (Hero.state) {
    case PLAYER_STATE_ANIM_TARGET_WALK:
    case PLAYER_STATE_UNK_66:
        return 1;
    case PLAYER_STATE_TELEPORTER_USE:
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
