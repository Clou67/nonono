#ifndef HERO_H
#define HERO_H

#include "moby.h"

enum { HERO_TYPE_RATCHET = 0, HERO_TYPE_HOLOGUISE = 3 };

#define HERO_NO_HUD_HANDLE -1
#define HERO_SHIP_FLAG_RESET 0x1
#define HERO_RACE_LAP_COUNT 3
#define HERO_RACE_MOBY_LAP_OFFSET 0xBC

// The hero. Field names from the PS3 project's hero globals (same layout), plus RC1-only fields.
extern int WeaponAmmo[];

struct HeroState {
    Mtx4 mtx;
    Mtx4 gravityMtx;
    Vec4 position;
    // z is the yaw.
    Vec4 rotation;
    char unkA0[0x20];
    // The point enemies aim at.
    Vec4 aimPos;
    Vec4 cgPos;
    Vec4 velocity;
    char unkF0[0x50];
    // How far the hero moved this frame.
    Vec4 frameMove;
    Vec4 externalMomentum;
    char unk160[0x20];
    float idealRotZ;
    float turnSpeed;
    float turnDelta;
    char unk18C[4];
    float idealSpeed;
    float storedNeutralSpeed;
    int stateTimer;
    int controlModeTimer;
    char unk1A0[0x2C];
    int ghostFrames;
    char unk1D0[0x16];
    short swingshotReleasedTimer;
    char unk1E8[0xE];
    short splineWallHitTimer;
    char unk1F8[0x28];
    float collTop;
    float collBottom;
    char unk228[0xC];
    float collRadius;
    char unk238[0x38];
    Vec4 groundNormal;
    char unk280[0x10];
    Vec4 gravityDir;
    Vec4 groundPoint;
    char unk2B0[0x28];
    float groundZ;
    float groundDist;
    float groundSlope;
    char unk2E4[0xC];
    float waterZ;
    char unk2F4[0x8];
    MobyInstance *standingOnMoby;
    int framesGroundedCnt;
    char unk304[0x4];
    short onMagnerail;
    char unk30A[0x4];
    short framesNotGrounded;
    char unk310[0x108];
    int dustHoverState;
    char unk41C[0xDC];
    MobyInstance *ledgeMoby;
    char unk4FC[0x64];
    // The data of the grind path the hero is on.
    int grindPath;
    char unk564[0x308];
    MobyInstance *boardMoby;
    char unk870[0x10];
    int trickHudHandle;
    char unk884[0xC];
    unsigned char *raceMoby;
    int raceTime;
    short racePathNode;
    short raceLap;
    char unk89C[0xC];
    int raceScore;
    char unk8AC[0x2];
    // Counts up while going the wrong way.
    unsigned char wrongWayFrames;
    char unk8AF[0x11];
    // Finishing place, 1 is first.
    int racePlace;
    char unk8C4[0xDA];
    short nearSwingshot;
    char unk9A0[0xE8];
    MobyInstance *ratchetMoby;
    char unkA8C[0x4];
    float animSpeed;
    char unkA94[0x14];
    float animFrame;
    float animFrameWindow;
    int nextAnimation;
    int nextAnimationFrame;
    int queuedFrameRequest;
    char unkABC[0x5D4];
    MobyInstance *currentWeaponMoby;
    char unk1094[0x24];
    int currentWeapon;
    char unk10BC[0x24];
    MobyInstance *bootMoby;
    char unk10E4[0x1FC];
    short groundType;
    char unk12E2[0x2];
    // The hero is in water.
    unsigned char hotSpotWater;
    unsigned char hotSpotLava;
    unsigned char hotSpotQuickSand;
    char unk12E7[0x4];
    unsigned char hotSpotDeathSand;
    unsigned char hotSpotIceWater;
    char unk12ED[0x322];
    unsigned char shipFlags;
    char unk1610[0x20];
    int giantClankHealth;
    char unk1634[0x4CC];
    Vec4 posHistory[32];
    float savedPosRot[8];
    float padStick[3];
    char unk1D2C[0xA4];
    Vec4 glowPos[14];
    short glowCount;
    short glowDrawRegistered;
    char unk1EB4[0x194];
    unsigned char metalDetectorSpotIsClose;
    char unk2049[0x37];
    MobyInstance *moby;
    // A PlayerState value.
    int state;
    char unk2088[0x4];
    int stateType;
    char unk2090[0x14];
    unsigned char type;
    unsigned char invisible;
    char unk20A6[0xB];
    unsigned char outOfBounds;
    char unk20B2[0x1];
    unsigned char gravityMode;
    char unk20B4[0x20];
    int weaponToSwapTo;
    char unk20D8[0x50];
    float rotZHistory[32];
    int rotZHistoryIdx;
    int rotZHistoryCount;
    int posHistoryIdx;
    int posHistoryCount;
    char unk21B8[0x20];
    short queuedSounds;
    char unk21DA[0x3E];
    int loopSounds[8];
    MobyInstance *loopSoundMobys[8];
    char unk2258[0x20];
    MobyInstance *animLinkMoby;
    int animLinkTable;
    char unk2280[4];
    int requestedCamType;
    char unk2288[0x14];
    float padMagnitude;
    int oxygen;
    char unk22A4[0x4];
    int health;
    int clankMaxNanotech;
    char unk22B0[0x10];
    // The command picked on the Clank command ring.
    int clankCommand;
    char unk22C4[0x8];
    short requestedState;
    char unk22CE[0xA];
    short hasClank;
    short splineWall;
    char unk22DC[0x34];
};

// Hero states (the PS3 project's PlayerState).
enum PlayerState {
    PLAYER_STATE_STANDING = 0,
    PLAYER_STATE_FIRST_PERSON_VIEW = 1,
    PLAYER_STATE_WALKING = 2,
    PLAYER_STATE_STOPPING = 3,
    PLAYER_STATE_CROUCHING = 4,
    PLAYER_STATE_UNK_5 = 5,
    PLAYER_STATE_NEUTRAL_JUMP = 6,
    PLAYER_STATE_GLIDING = 7,
    PLAYER_STATE_FALLING = 8,
    PLAYER_STATE_MOVEMENT_JUMP = 9,
    PLAYER_STATE_HELI_PACK_FWD_JUMP = 10,
    PLAYER_STATE_FLIP_JUMP = 11,
    PLAYER_STATE_UNK_C = 12,
    PLAYER_STATE_THRUSTER_PACK_HIGH_JUMP = 13,
    PLAYER_STATE_DOUBLE_JUMP = 14,
    PLAYER_STATE_HELI_PACK_HIGH_JUMP = 15,
    PLAYER_STATE_THRUSTER_PACK_FORWARD_JUMP = 16,
    PLAYER_STATE_WALL_JUMP = 17,
    PLAYER_STATE_WATER_JUMP = 18,
    PLAYER_STATE_WRENCH_ATTACK = 19,
    PLAYER_STATE_HYPER_STRIKE = 20,
    PLAYER_STATE_CROUCH_WRENCH_THROW = 21,
    PLAYER_STATE_TAKING_DAMAGE = 22,
    PLAYER_STATE_UNK_17 = 23,
    PLAYER_STATE_EDGE_GRAB = 24,
    PLAYER_STATE_EDGE_HANG = 25,
    PLAYER_STATE_EDGE_HANG_MOVE_LEFT = 26,
    PLAYER_STATE_EDGE_HANG_MOVE_RIGHT = 27,
    PLAYER_STATE_EDGE_JUMP = 28,
    PLAYER_STATE_VISIBOMB_CONTROL = 29,
    PLAYER_STATE_WEAPON_FIRST_PERSON_VIEW = 30,
    PLAYER_STATE_ACTIVATE_SONIC_SUMMONER_MOUSE = 31,
    PLAYER_STATE_WALLOPER_SOMETHING = 32,
    PLAYER_STATE_UNK_BONK = 33,
    PLAYER_STATE_THRUSTER_PACK_BONK_JUMP = 34,
    PLAYER_STATE_THROWING_ITEM = 35,
    PLAYER_STATE_THROWING_GREEN_SWINGSHOT = 36,
    PLAYER_STATE_PULLING_GREEN_SWINGSHOT = 37,
    PLAYER_STATE_UNK_26 = 38,
    PLAYER_STATE_UNK_27 = 39,
    PLAYER_STATE_GRINDRAIL_USE = 40,
    PLAYER_STATE_GRINDRAIL_JUMP = 41,
    PLAYER_STATE_GRINDRAIL_SWITCH = 42,
    PLAYER_STATE_GRINDRAIL_WRENCH_ATTACK = 43,
    PLAYER_STATE_SWINGING_YELLOW_SWINGSHOT = 44,
    PLAYER_STATE_DISENGAGE_YELLOW_SWINGSHOT = 45,
    PLAYER_STATE_UNK_2E = 46,
    PLAYER_STATE_ICE_SLIDING = 47,
    PLAYER_STATE_UNK_30 = 48,
    PLAYER_STATE_WATER_SLIDING = 49,
    PLAYER_STATE_TURRET_PLANE_UI = 50,
    PLAYER_STATE_UNDERWATER_MOVING = 51,
    PLAYER_STATE_UNDERWATER_STANDING = 52,
    PLAYER_STATE_HYDRO_PACK_MOVING = 53,
    PLAYER_STATE_WATER_SWIMMING = 54,
    PLAYER_STATE_UNK_37 = 55,
    PLAYER_STATE_HYDRODISPLACER_CONNECTING = 56,
    PLAYER_STATE_HYDRODISPLACER_WAITING = 57,
    PLAYER_STATE_HYDRODISPLACER_DISCONNECTING = 58,
    PLAYER_STATE_BOLT_CRANK_TURNING = 59,
    PLAYER_STATE_TAKING_DAMAGE_LAVA = 60,
    PLAYER_STATE_DYING_GROUNDED = 61,
    PLAYER_STATE_UNK_3E = 62,
    PLAYER_STATE_MAGNERAMP_WAITING = 63,
    PLAYER_STATE_UNK_40 = 64,
    PLAYER_STATE_UNK_41 = 65,
    PLAYER_STATE_GRINDRAIL_DAMAGE = 66,
    PLAYER_STATE_CLANK_STANDING = 67,
    PLAYER_STATE_CLANK_WALKING = 68,
    PLAYER_STATE_CLANK_FALLING = 69,
    PLAYER_STATE_CLANK_DAMAGE = 70,
    PLAYER_STATE_CLANK_DYING = 71,
    PLAYER_STATE_UNK_48 = 72,
    PLAYER_STATE_CLANK_JUMP = 73,
    PLAYER_STATE_CLANK_EDGE_ENGAGING = 74,
    PLAYER_STATE_CLANK_EDGE_HANG = 75,
    PLAYER_STATE_CLANK_EDGE_JUMP = 76,
    PLAYER_STATE_CLANK_EDGE_MOVE_LEFT = 77,
    PLAYER_STATE_CLANK_EDGE_MOVE_RIGHT = 78,
    PLAYER_STATE_CLANK_GLIDING = 79,
    PLAYER_STATE_UNK_50 = 80,
    PLAYER_STATE_CLANK_ATTACK = 81,
    PLAYER_STATE_UNK_52 = 82,
    PLAYER_STATE_HOLOGUISE_STANDING = 83,
    PLAYER_STATE_HOLOGUISE_WALKING = 84,
    PLAYER_STATE_UNK_55 = 85,
    PLAYER_STATE_UNK_56 = 86,
    PLAYER_STATE_HOLOGUISE_DYING = 87,
    PLAYER_STATE_UNK_58 = 88,
    PLAYER_STATE_HOLOGUISE_WAVE = 89,
    PLAYER_STATE_GIANT_CLANK_STANDING = 90,
    PLAYER_STATE_GIANT_CLANK_WALKING = 91,
    PLAYER_STATE_GIANT_CLANK_FALLING = 92,
    PLAYER_STATE_GIANT_CLANK_DAMAGE = 93,
    PLAYER_STATE_GIANT_CLANK_JUMP = 94,
    PLAYER_STATE_GIANT_CLANK_FIRE_WEAPONS = 95,
    PLAYER_STATE_GIANT_CLANK_ATTACK = 96,
    PLAYER_STATE_GIANT_CLANK_CHARGE_ATTACK = 97,
    PLAYER_STATE_GIANT_CLANK_DYING = 98,
    PLAYER_STATE_UNK_63 = 99,
    PLAYER_STATE_CUSTOM_UI = 100,
    PLAYER_STATE_ANIM_TARGET_WALK = 101,
    PLAYER_STATE_UNK_66 = 102,
    PLAYER_STATE_TELEPORTER_USE = 103,
    PLAYER_STATE_MUD_SINKING = 104,
    PLAYER_STATE_MUD_JUMP = 105,
    PLAYER_STATE_DEATH_DROWNING = 106,
    PLAYER_STATE_HOVERBOARD_RIDING = 107,
    PLAYER_STATE_HOVEDBOARD_JUMP = 108,
    PLAYER_STATE_HOVERBOARD_DYING = 109,
    PLAYER_STATE_HOVERBOARD_WATER_DYING = 110,
    PLAYER_STATE_HOVERBOARD_WALL_BONK = 111,
    PLAYER_STATE_MAGNERAMP_ATTACK = 112,
    PLAYER_STATE_MAGNERAMP_JUMP = 113,
    PLAYER_STATE_MOVEMENT_LOCKED = 114,
    PLAYER_STATE_WATER_WALKING = 115,
    PLAYER_STATE_UNK_74 = 116,
    PLAYER_STATE_UNK_75 = 117,
    PLAYER_STATE_UNDERWATER_DAMAGE = 118,
    PLAYER_STATE_DEATH_FALLING = 119,
    PLAYER_STATE_UNK_78 = 120,
    PLAYER_STATE_SLIDING_OFF_SOMETHING = 121,
    PLAYER_STATE_WALL_BONK = 122,
    PLAYER_STATE_DEATH_MUD = 123,
    PLAYER_STATE_DEATH_LAVA = 124,
    PLAYER_STATE_UNK_7D = 125,
    PLAYER_STATE_UNK_7E = 126,
    PLAYER_STATE_DEATH_ICE = 127,
    PLAYER_STATE_DEATH_LASER = 128,
    PLAYER_STATE_THRUSTER_PACK_HOVER = 129,
    PLAYER_STATE_DEATH_WATER_LASER = 130
};

extern HeroState Hero;

// Item ids (weapons, gadgets and upgrades).
enum item_id {
    ITEM_HELI_PACK = 2,
    ITEM_THRUSTER_PACK,
    ITEM_HYDRO_PACK,
    ITEM_SONIC_SUMMONER,
    ITEM_O2_MASK,
    ITEM_PILOTS_HELMET,
    ITEM_WRENCH,
    ITEM_SUCK_CANNON,
    ITEM_BOMB_GLOVE,
    ITEM_DEVASTATOR,
    ITEM_SWINGSHOT,
    ITEM_VISIBOMB_GUN,
    ITEM_TAUNTER,
    ITEM_BLASTER,
    ITEM_PYROCITOR,
    ITEM_MINE_GLOVE,
    ITEM_WALLOPER,
    ITEM_TESLA_CLAW,
    ITEM_GLOVE_OF_DOOM,
    ITEM_MORPH_O_RAY,
    ITEM_HYDRODISPLACER,
    ITEM_RYNO,
    ITEM_DRONE_DEVICE,
    ITEM_DECOY_GLOVE,
    ITEM_TRESPASSER,
    ITEM_METAL_DETECTOR,
    ITEM_MAGNEBOOTS,
    ITEM_GRINDBOOTS,
    ITEM_HOVERBOARD,
    ITEM_HOLOGUISE,
    ITEM_PDA,
    ITEM_MAP_O_MATIC,
    ITEM_BOLT_GRABBER,
    ITEM_PERSUADER,

    ITEM_COUNT = 37
};

// Items the hero has, and items picked up at least once (picking one up again shows a different message).
extern unsigned char UnlockableItems[ITEM_COUNT];
extern unsigned char ObtainedItems[ITEM_COUNT];

// The equipped item first, then the items equipped before it.
extern int EquippedItems[];

#define QUICK_SELECT_SLOT_COUNT 8
extern int QuickSelectItems[QUICK_SELECT_SLOT_COUNT];

void Hero_RevertToRatchet(void);
void Hero_Warp(float *position, float *rotation, int flags, int snap);

void Hero_SubGravity(float amount, float *out, float *in);

void Hero_ClearNextAnim(void);

void Hero_HideHeroMoby(void);

void Hero_ShowHeroMoby(void);

void Hero_ZeroThrustVars(void);

void Hero_ClearBoardMoby(void);

int Hero_IsWeaponGroupA(int slot);

int Hero_IsWearingBoots(int slot);

void Hero_UpdateAnimLayers(void);

int Hero_isMobyWrench(MobyInstance *moby);

void Hero_SnapAnim(int animation, int frame);

int Hero_GetSpecialStateKind(void);

void Hero_SetNextAnimBlend(int frames);

int Hero_IsInSpecialMovementState(void);

void Hero_TransitionToDefault(void);

void Hero_NormalizeThrust(Vec4 *direction, float horizontal, float vertical, int scaleComponents);

void Hero_ResetIfTypeThree(void);

float Hero_GetPadMagnitude(void);

void Hero_ThrustModeAccel(float acceleration, float deceleration);

void Hero_SyncBoardAnimSpeed(void);

void Hero_GetHeroRelativePos(Vec4 *out, float x, float y, float z);

void Hero_GetPolarOffset(Vec4 *out, float x, float y, float z);

int Hero_AnimFrameInWindow(float frame);

void Hero_ApplyRootMotion(float x, float y, float z);

int Hero_GetJumpHoldTime(void);

int STUB_00226fa0(int animation);

int Hero_GetWeaponAmmo(int item);

int Hero_GetOverlayAnimId(int overlay);

int Hero_IsWeaponGroupB(int slot);

void Hero_RegisterGlowDraw(void);

void Hero_RotateByEuler(float xAngle, float yAngle, float zAngle);

int Hero_DefaultByteIfFF(MobyInstance *moby, int animation);

void Hero_Turn(float gain, float damping, float limit, int direction);

float Hero_GetRotationHistory(int framesAgo);

void Hero_AlignToVec(Vec4 *direction, Vec4 *out);

void Hero_CollideSplineWall(void);

void Hero_SetNextAnimFrame(int animation, int frame);

void Hero_PlayLoopSound(int slot, MobyInstance *moby, int soundId);

struct HeroTweakValues {
    char unk_00[0xA4];
    float unk_A4;
    float unk_A8;
    char unk_AC[0xA8];
    float unk_154;
    float unk_158;
    char unk_15C[0xA8];
    float unk_204;
    float unk_208;
    char unk_20C[0xA8];
    float unk_2B4;
    float unk_2B8;
};

extern HeroTweakValues HeroTweaks;

void Hero_SetTweakPair_97b44(float first, float second);

void Hero_SetTweakPair_929e8(float first, float second);

void Hero_SetTweak_721dd4(float first, float second);

void Hero_SetTweak_721e84(float first, float second);

void Hero_PlayFootStep(int groundType, int whichFoot, int playSound);

void TakeDamage(int damage);

void Hero_ResetHero(void);
void Hero_InitStuff(void);

#endif
