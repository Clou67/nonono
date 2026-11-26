#ifndef HERO_H
#define HERO_H

#include "moby.h"
#include "mobyutil.h"

enum { HERO_TYPE_RATCHET = 0, HERO_TYPE_CLANK = 1, HERO_TYPE_GIANT_CLANK = 2, HERO_TYPE_HOLOGUISE = 3 };

#define HERO_NO_HUD_HANDLE -1
#define HERO_SHIP_FLAG_RESET 0x1
#define HERO_RACE_LAP_COUNT 3
#define HERO_RACE_MOBY_LAP_OFFSET 0xBC

// One key of a jump's vertical velocity curve, played between velocityKeysStartFrame and EndFrame.
// Entering a key sets the vertical acceleration to value * frameTimeSq (-999999 keeps the old one),
// each later frame adds delta * frameTimeSq. A key lasts FastScaleRoundInt(frames) frames.
struct HeroVelocityKey {
    float value;
    float delta;
    int frames;
};

// Timer that fires after a random number of frames; a range of 0 holds it off.
struct HeroRandTimer {
    int fired;
    int deadline;
    int range;
};

// One of the hero's item slots. Slot 0 is the equipped gadget.
struct HeroItemSlot {
    MobyInstance *moby;         // 0x00: item moby
    MobyInstance *moby2;        // 0x04: second item moby
    char unk8[0x4];
    MobyInstance *moby3;        // 0x0C: third item moby
    int buttonMask;             // 0x10: pad buttons that hold the gadget states
    int respawnFrame;           // 0x14: set on release
    // Counts down; a slot change waits for 0.
    short timer;                // 0x18
    unsigned char thrown;       // 0x1A: cleared on a slot change
    unsigned char releasedFrames; // 0x1B: counts releases
    unsigned char switchLock;   // 0x1C: 2 blocks a slot change, 1 reloads timer
    unsigned char timerReload;  // 0x1D: timer reload value
    char unk1E[0x2];
    int readyFrames;            // 0x20
    // 0 empty, 2 ready, 3 released.
    int state;                  // 0x24
    // The item in the slot.
    int itemId;                 // 0x28
    float glowPhase;            // 0x2C: phase of the item moby's colour pulse
    float effectRandomBase;     // 0x30
    float effectRandomHalfRange; // 0x34
    int effectUpdatesLeft;      // 0x38
    short effectCountPerPoint;  // 0x3C
    unsigned short effectFlags; // 0x3E
    int lockedOn;               // 0x40: on slot 6, nonzero makes the Ryno aim along lockYaw
    char unk44[0x4];
    MobyInstance *lockTarget;   // 0x48: on slot 6, the moby the weapons lock on to
    float lockYaw;              // 0x4C
};

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
    char unkF0[0x10];
    Vec4 displacement;
    Vec4 resolvedVelocity;
    char unk120[0x20];
    // How far the hero moved this frame.
    Vec4 frameMove;
    Vec4 externalMomentum;
    float speedXY;
    float flatSpeed;
    float forwardSpeed;
    char unk16C[0x14];
    float idealRotZ;
    float turnSpeed;
    float turnDelta;
    char unk18C[4];
    float idealSpeed;
    float storedNeutralSpeed;
    int stateTimer;
    int controlModeTimer;
    int stepFrames;
    int animSeqFrames;
    char unk1A8[0x8];
    short noLedge;
    short allowQuickSelect;
    int wallJumpOk;
    int longJumpLockout;
    char unk1BC[0x4];
    int postHitInvinc;
    int moveLockTimer;
    char unk1C8[0x4];
    int ghostFrames;
    int idleReturnDelay;
    int jumpBufferLockout;
    short noWaterJump;
    char unk1DA[0x4];
    short noWaterDive;
    short sinkingFloorHold;
    short stillFrames;
    char unk1E4[0x2];
    short swingshotReleasedTimer;
    short fidgetCooldown;
    char unk1EA[0x4];
    short screenFlashRed;
    char unk1F0[0x2];
    short noJumps;
    char unk1F4[0x2];
    short splineWallHitTimer;
    char unk1F8[0x28];
    float collTop;
    float collBottom;
    char unk228[0xC];
    float collRadius;
    char unk238[0x10];
    float wallProbeDistance;
    char unk24C[0xB];
    unsigned char wallHit;
    char unk258[0x18];
    Vec4 groundNormal;
    char unk280[0x10];
    Vec4 gravityDir;
    Vec4 groundPoint;
    char unk2B0[0x28];
    float groundHeight;
    float groundDist;
    float groundSlope;
    char unk2E4[0xC];
    float waterHeight;
    char unk2F4[0x4];
    int inWaterFrames;
    MobyInstance *standingOnMoby;
    int framesGroundedCnt;
    char unk304[0x4];
    short onMagnerail;
    short onFlaggedGroundMoby;
    short framesOffGround;
    short framesNotGrounded;
    char unk310[0xA8];
    short moveAlongStick;
    char unk3BA[0x2];
    short runStartBlending;
    short sharpTurn;
    char unk3C0[0x10];
    int velocityKeysStartFrame;
    int velocityKeysEndFrame;
    float keyedMoveTargetFrame;
    float unk3DC;
    int keyedAnimTargetFrame;
    HeroVelocityKey *velocityKeys;
    int velocityKeyIndex;
    char unk3EC[0x8];
    float longJumpSpeed;
    float fallGravity;
    char unk3FC[0x14];
    float smoothedGroundZ;
    float airTurnRate;
    int dustHoverState;
    short velocityKeysActive;
    short pastJumpApex;
    int takeoffFrame;
    float airStickSpeed;
    float pendingJumpImpulse;
    float jumpImpulseTotal;
    float jumpHeight;
    float airCapsuleBottom;
    float highJumpDriftYaw;
    float takeoffYaw;
    float apexAnimFrame;
    float targetAnimFrame;
    float jumpLandAnimFrame;
    int framesToLand;
    int jumpStickDirection;
    float airTargetSpeed;
    float highJumpDriftSpeed;
    float ledgeJumpSpeed;
    Vec4 wallHitNormal;
    Vec4 wallJumpNormal;
    float airSpeedStepUp;
    float jumpDecel;
    float jumpHeightStart;
    float jumpHeightTarget;
    float fallStartDistance;
    float jumpAnimRetimeScale;
    short jumpRampFrames;
    short jumpMaxFrames;
    char unk49C[0x4];
    float jumpGravity;
    short jumpBlockedAhead;
    short packGlideDelay;
    short tookOffFromIce;
    short fallDelayFrames;
    short canUseItemInJump;
    unsigned char canChainHighJump;
    unsigned char canDoubleJump;
    float riseFallGravity;
    char unk4B4[0x4];
    float pastApex;
    int predictedLandFrames;
    float riseFallTargetFrame;
    int riseFallLandFrames;
    char unk4C8[0x20];
    int ledgeFound;
    float ledgeGravity;
    float smoothedAirZ;
    char unk4F4[0x4];
    MobyInstance *ledgeMoby;
    char unk4FC[0x64];
    // The data of the grind path the hero is on.
    int grindPath;
    char unk564[0xC];
    int railOffFrames;
    char unk574[0x38];
    int grindSpeedBoost;
    float grindBaseSpeed;
    char unk5B4[0x18];
    float grindRecoverySpeed;
    char unk5D0[0xC0];
    float swimBobOffset;
    float swimBobVelocity;
    int swimStrokeTimer;
    float swimWaterLevel;
    float swimWaterLevelVelocity;
    char unk6A4[0x1C8];
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
    char unk8C4[0x1C];
    int swimEntryFrames;
    char unk8E4[0x10];
    int swimThrustTimer;
    char unk8F8[0x4];
    float drownSinkSpeed;
    char unk900[0xA];
    short splashEffectTimer;
    char unk90C[0x2];
    short jumpButtonFrames;
    int swimCrossTapCount;
    char unk914[0x2C];
    float fallStateGravity;
    float sticklessDecel;
    char unk948[0x8];
    float pivotRotXTarget;
    float fatalFallTumbleTargetY;
    char unk958[0x46];
    short nearSwingshot;
    char unk9A0[0xB0];
    MobyInstance *throwTarget;
    MobyInstance *meleeTarget;
    int headingLocked;
    float attackTargetYaw;
    int attackRecord;
    int meleeHit;
    float pushbackYaw;
    float speedScale;
    float slamDescending;
    char unkA74[0x8];
    int crouchSwingToggle;
    char unkA80[0x8];
    MobyInstance *ratchetMoby;
    char unkA8C[0x4];
    float animSpeed;
    char unkA94[0x4];
    int animFlags;
    int animChanging;
    int animBlendCurve;
    int animBlendStep;
    float animFrame;
    float animFrameWindow;
    int nextAnimation;
    int nextAnimationFrame;
    int queuedFrameRequest;
    char unkABC[0x24C];
    MobyInstance *heldItemAnimMoby[2];
    char unkD10[0x4];
    int armLayerFade;
    char unkD18[0x2D8];
    // Random-interval timer; range 0 holds it off.
    HeroRandTimer randTimer;
    char unkFFC[0x14];
    int headLookTimer;
    char unk1014[0x7C];
    // Item slots; slot 0 is the equipped gadget.
    HeroItemSlot items[7];
    char unk12C0[0x20];
    short groundType;
    unsigned char onIceGround;
    unsigned char selector4;
    // The hero is in water.
    unsigned char hotSpotWater;
    unsigned char hotSpotLava;
    unsigned char hotSpotQuickSand;
    char unk12E7[0x3];
    unsigned char onSlipGround;
    unsigned char hotSpotDeathSand;
    unsigned char hotSpotIceWater;
    unsigned char groundSoundClass;
    char unk12EE[0x321];
    unsigned char shipFlags;
    char unk1610[0x4];
    MobyInstance *fidgetPropMoby;
    char unk1618[0x18];
    int giantClankHealth;
    char unk1634[0xC];
    Vec4 targetPose;
    int stateEntryOption;
    char unk1654[0x1C];
    // Translucent copies that follow the hero.
    MotionBlur trail;
    char unk17B0[0x350];
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
    // A HeroStateId value.
    int state;
    int subState;
    int stateType;
    int prevState;
    int prevStateType;
    int prevStateTimer;
    int prev2State;
    int prev2StateType;
    unsigned char type;
    unsigned char invisible;
    char unk20A6[0x1];
    unsigned char itemSelectBlocked;
    unsigned char itemAnimActive;
    unsigned char wading;
    unsigned char weaponUp;
    char unk20AB[0x1];
    unsigned char itemUseLocked;
    unsigned char tiltDisabled;
    char unk20AE[0x1];
    unsigned char handItemHidden;
    char unk20B0[0x1];
    unsigned char outOfBounds;
    unsigned char onHoverboard;
    unsigned char gravityMode;
    char unk20B4[0x4];
    int pendingItem[7];
    int weaponToSwapTo;
    char unk20D8[0x18];
    int savedItem[7];
    int restoreItem[7];
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
    char unk2258[0x18];
    int fidgetIndex;
    char unk2274[0x4];
    MobyInstance *animLinkMoby;
    int animLinkTable;
    char unk2280[4];
    int requestedCamType;
    char unk2288[0xC];
    int itemHoldAnim;
    int itemAnimItemId;
    float padMagnitude;
    int oxygen;
    float waterDepth;
    int health;
    int clankMaxNanotech;
    char unk22B0[0x2];
    short fallVoiceSlot;
    int wallJumped;
    char unk22B8[0x8];
    // The command picked on the Clank command ring.
    int clankCommand;
    int slot3AnimTimer;
    short weaponLowered;
    unsigned char hoverLatch;
    char unk22CB[0x1];
    short requestedState;
    char unk22CE[0x4];
    short itemSelectorTimer;
    short quickSwapTapTimer;
    short quickSwapTapWindow;
    short hasClank;
    short splineWall;
    short scalePulseStep;
    short vehicleToggleTimer;
    short glowPulseLevel;
    char unk22E2[0x2E];
};

// Hero control modes (Hero.stateType): what kind of movement a state belongs to.
// 9, 0xA, 0xB, 0x10, 0x13, 0x15, 0x16 and 0x18 are unnamed: what their states share is not clear.
enum HeroStateType {
    HERO_STATE_TYPE_IDLE = 0,
    HERO_STATE_TYPE_RUN = 1,
    HERO_STATE_TYPE_FALL = 2,
    HERO_STATE_TYPE_LEDGE = 3,
    HERO_STATE_TYPE_JUMP = 4,
    HERO_STATE_TYPE_LAND = 5,
    HERO_STATE_TYPE_ATTACK = 6,
    HERO_STATE_TYPE_HURT = 7,
    HERO_STATE_TYPE_ITEM_RELEASE_WAIT = 8,
    HERO_STATE_TYPE_BUSY = 9,
    HERO_STATE_TYPE_BOUNCE = 10,
    HERO_STATE_TYPE_STOMP = 11,
    HERO_STATE_TYPE_CROUCH = 12,
    HERO_STATE_TYPE_GRAPPLE = 13,
    HERO_STATE_TYPE_GRAPPLE_SWING = 14,
    HERO_STATE_TYPE_GRIND = 15,
    HERO_STATE_TYPE_SLIDE = 16,
    HERO_STATE_TYPE_SWIM = 17,
    HERO_STATE_TYPE_WATER_SURFACE = 18,
    HERO_STATE_TYPE_DYING = 20,
    HERO_STATE_TYPE_NPC = 24,
    HERO_STATE_TYPE_RESPAWN_WAIT = 25,
    HERO_STATE_TYPE_FOLLOW_PATH = 26
};

// Hero states, named after Deadlocked where the behaviour lines up.
enum HeroStateId {
    HERO_STATE_IDLE = 0,
    HERO_STATE_LOOK = 1,
    HERO_STATE_WALK = 2,
    HERO_STATE_SKID = 3,
    HERO_STATE_CROUCH = 4,
    HERO_STATE_QUICK_TURN = 5,
    HERO_STATE_FALL = 6,
    HERO_STATE_JUMP = 7,
    HERO_STATE_LAND = 8,
    HERO_STATE_RUN_JUMP = 9,
    HERO_STATE_HELI_PACK_FWD_JUMP = 10,
    HERO_STATE_FLIP_JUMP = 11,
    HERO_STATE_STORED_HEADING_JUMP = 12,
    HERO_STATE_ROCKET_JUMP = 13,
    HERO_STATE_DOUBLE_JUMP = 14,
    HERO_STATE_HELI_JUMP = 15,
    HERO_STATE_THRUSTER_PACK_FORWARD_JUMP = 16,
    HERO_STATE_WALL_JUMP = 17,
    HERO_STATE_WATER_JUMP = 18,
    HERO_STATE_COMBO_ATTACK = 19,
    HERO_STATE_JUMP_ATTACK = 20,
    HERO_STATE_THROW_ATTACK = 21,
    HERO_STATE_GET_HIT = 22,
    HERO_STATE_ITEM_BUTTON_RELEASE_WAIT = 23,
    HERO_STATE_LEDGE_GRAB = 24,
    HERO_STATE_LEDGE_IDLE = 25,
    HERO_STATE_LEDGE_TRAVERSE_LEFT = 26,
    HERO_STATE_LEDGE_TRAVERSE_RIGHT = 27,
    HERO_STATE_LEDGE_JUMP = 28,
    HERO_STATE_VISIBOMB = 29,
    HERO_STATE_WEAPON_FIRST_PERSON_VIEW = 30,
    HERO_STATE_ACTIVATE_SONIC_SUMMONER_MOUSE = 31,
    HERO_STATE_WALLOPER_ATTACK = 32,
    HERO_STATE_UNK_BONK = 33,
    HERO_STATE_ROCKET_STOMP = 34,
    HERO_STATE_THROWING_ITEM = 35,
    HERO_STATE_GRAPPLE_SHOOT = 36,
    HERO_STATE_GRAPPLE_PULL = 37,
    HERO_STATE_CONSTRAIN_TO_TARGET_RADIUS = 38,
    HERO_STATE_IDLE_ANIMATION_LONG_BLEND_ENTRY = 39,
    HERO_STATE_GRIND = 40,
    HERO_STATE_GRIND_JUMP = 41,
    HERO_STATE_GRIND_SWITCH_JUMP = 42,
    HERO_STATE_GRIND_ATTACK = 43,
    HERO_STATE_SWING = 44,
    HERO_STATE_SWING_FALL = 45,
    HERO_STATE_ITEM_BUTTON_HOLD_ANIMATION_WAIT = 46,
    HERO_STATE_ICE_SLIDING = 47,
    HERO_STATE_WAIT_FOR_ITEM_RELEASE_THEN_IDLE = 48,
    HERO_STATE_SLIDE = 49,
    HERO_STATE_TURRET_PLANE_UI = 50,
    HERO_STATE_SWIMUNDER = 51,
    HERO_STATE_IDLEUNDER = 52,
    HERO_STATE_CHARGEUNDER = 53,
    HERO_STATE_SWIMSURF = 54,
    HERO_STATE_IDLESURF = 55,
    HERO_STATE_HYDRODISPLACER_CONNECTING = 56,
    HERO_STATE_HYDRODISPLACER_WAITING = 57,
    HERO_STATE_HYDRODISPLACER_DISCONNECTING = 58,
    HERO_STATE_BOLT_CRANK = 59,
    HERO_STATE_TAKING_DAMAGE_LAVA = 60,
    HERO_STATE_DEATH = 61,
    HERO_STATE_BOARD = 62,
    HERO_STATE_MAGNE_WALK = 63,
    HERO_STATE_FIDGET = 64,
    HERO_STATE_FIDGET_ALT = 65,
    HERO_STATE_GRINDRAIL_DAMAGE = 66,
    HERO_STATE_CLANK_STANDING = 67,
    HERO_STATE_CLANK_WALKING = 68,
    HERO_STATE_CLANK_FALLING = 69,
    HERO_STATE_CLANK_DAMAGE = 70,
    HERO_STATE_CLANK_DYING = 71,
    HERO_STATE_UNK_48 = 72,
    HERO_STATE_CLANK_JUMP = 73,
    HERO_STATE_CLANK_EDGE_ENGAGING = 74,
    HERO_STATE_CLANK_EDGE_HANG = 75,
    HERO_STATE_CLANK_EDGE_JUMP = 76,
    HERO_STATE_CLANK_EDGE_MOVE_LEFT = 77,
    HERO_STATE_CLANK_EDGE_MOVE_RIGHT = 78,
    HERO_STATE_CLANK_GLIDING = 79,
    HERO_STATE_CLANK_SPEED_SCALED_RUN = 80,
    HERO_STATE_CLANK_ATTACK = 81,
    HERO_STATE_CLANK_SLIP = 82,
    HERO_STATE_HOLOGUISE_STANDING = 83,
    HERO_STATE_HOLOGUISE_WALKING = 84,
    HERO_STATE_HOLOGUISE_FALLING = 85,
    HERO_STATE_HOLOGUISE_DAMAGE = 86,
    HERO_STATE_HOLOGUISE_DYING = 87,
    HERO_STATE_HOLOGUISE_SLIP = 88,
    HERO_STATE_HOLOGUISE_WAVE = 89,
    HERO_STATE_GIANT_CLANK_STANDING = 90,
    HERO_STATE_GIANT_CLANK_WALKING = 91,
    HERO_STATE_GIANT_CLANK_FALLING = 92,
    HERO_STATE_GIANT_CLANK_DAMAGE = 93,
    HERO_STATE_GIANT_CLANK_JUMP = 94,
    HERO_STATE_GIANT_CLANK_FIRE_WEAPONS = 95,
    HERO_STATE_GIANT_CLANK_ATTACK = 96,
    HERO_STATE_GIANT_CLANK_CHARGE_ATTACK = 97,
    HERO_STATE_GIANT_CLANK_DYING = 98,
    HERO_STATE_NPC = 99,
    HERO_STATE_CUSTOM_UI = 100,
    HERO_STATE_WALK_TO_POS = 101,
    HERO_STATE_SKID_TO_POS = 102,
    HERO_STATE_IDLE_TO_POS = 103,
    HERO_STATE_QUICKSAND_SINK = 104,
    HERO_STATE_QUICKSAND_JUMP = 105,
    HERO_STATE_DROWN = 106,
    HERO_STATE_HOVERBOARD_RIDING = 107,
    HERO_STATE_HOVEDBOARD_JUMP = 108,
    HERO_STATE_HOVERBOARD_DYING = 109,
    HERO_STATE_HOVERBOARD_WATER_DYING = 110,
    HERO_STATE_HOVERBOARD_WALL_BONK = 111,
    HERO_STATE_MAGNE_ATTACK = 112,
    HERO_STATE_MAGNE_JUMP = 113,
    HERO_STATE_CUT_SCENE = 114,
    HERO_STATE_WADE = 115,
    HERO_STATE_ZIP = 116,
    HERO_STATE_GET_HIT_SURF = 117,
    HERO_STATE_GET_HIT_UNDER = 118,
    HERO_STATE_DEATH_FALL = 119,
    HERO_STATE_CLEAR_VELOCITY = 120,
    HERO_STATE_SLOPESLIDE = 121,
    HERO_STATE_JUMP_BOUNCE = 122,
    HERO_STATE_DEATHSAND_SINK = 123,
    HERO_STATE_LAVA_DEATH = 124,
    HERO_STATE_CLANK_DEATH_DESCENT = 125,
    HERO_STATE_UNK_7E = 126,
    HERO_STATE_ICEWATER_FREEZE = 127,
    HERO_STATE_ELECTRIC_DEATH = 128,
    HERO_STATE_ROCKET_HOVER = 129,
    HERO_STATE_ELECTRIC_DEATH_UNDER = 130
};

// One usage counter. Every user bumps count (saturating at 0xFFFF), raises latestTimeBucket
// to the play time in 10 second units, and sets bit 31 plus its level's bit in levelMask.
struct UsageStat {
    unsigned short count;
    unsigned short latestTimeBucket;
    int levelMask;
};

#define USAGE_STAT_USED 0x80000000 // levelMask bit 31: the record has been used at least once

// Records of UsageStats that hero actions count into (ActionUsageStats starts at record 57).
enum UsageAction {
    USAGE_HYPER_STRIKE = 0,
    USAGE_WRENCH_THROW = 1,
    USAGE_DROWN = 12,
    USAGE_DROWN_FLAIL = 29
};

extern UsageStat UsageStats[];
extern UsageStat ActionUsageStats[];

// One row of HeroAttackTable, indexed by HeroState::attackRecord.
struct HeroAttackRow {
    int comboEnds;          // 1: this is the finishing recovery animation
    int kind;
    int chainBeforeFrame;   // a wrench press before this animation frame chains to the next record
    int baseFrame;          // subtracted from the animation frame to time the forward motion
    int followUpFrame;      // frame from which a follow-up move may start
    int interruptFrame;     // once past this frame the swing can be cut short
    int endFrame;           // once past this frame the swing is over
    int hitStartFrame;      // the wrench hits between hitStartFrame and hitEndFrame
    int hitEndFrame;
    char pad24[0x8];
};

// One of the five idle fidget animations the hero picks between while standing still.
struct HeroIdleFidget {
    char pad00[0x44];
    int useSpecialState; // nonzero: enter the fidget state instead of playing the animation directly
    int animation;
    char pad4C[0x4];
    int itemId;          // only picked while this item is held, -1 for any
    char pad54[0x4];
    float interval;      // seconds between picks, 0 means never picked
    float duration;      // seconds
    int durationFrames;
    char pad64[0xC];
};

// Speed thresholds the grounded jump transitions compare against.
struct HeroJumpSpeedTweaks {
    char pad00[0xC];
    float minRunSpeed;
    char pad10[0x8];
    float stepSpeed;
};

extern HeroAttackRow HeroAttackTable[];
extern HeroIdleFidget HeroIdleFidgets[5];
extern float HeroAnimBlendCurves[][25];
extern unsigned char HeroRunJumpAnims[];
extern HeroVelocityKey HeroTrailJumpKeys[];
extern HeroVelocityKey HeroWaterJumpKeys[];

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

int Hero_GetAnim(int animation);

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
    char unk_20C[0x48];
    float unk_254;
    float unk_258;
    char unk_25C[0x58];
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
