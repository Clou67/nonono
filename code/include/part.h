#ifndef PART_H
#define PART_H

#include "moby.h"

struct PartInstance;

// Numbered effect records use DL debug names. RaC1 update labels are shifted by one.

struct Part000 {
    Vec4 vel;
};

struct Part003 {
    Vec4 vel;
    char *existFlag;
    int state;
    int numFlipColls;
    int numFramesSinceColl;
};

struct Part005 {
    int fadeTimer;
    float scaleDelta;
};

struct Part007 {
    int fadeTimer;
    float scaleDelta;
};

// RaC1 reads the state bytes unsigned; DL uses the same names and offsets.

struct Part011 {
    Vec4 vel;
    int beginRGBA;
    int endRGBA;
    unsigned char totalTime;
    unsigned char stateFlags;
    unsigned char generationCount;
    unsigned char lifeSpan;
    float maxScale;
};

struct Part016 {
    Vec4 vel;
    int beginRGBA;
    int endRGBA;
    short lifeSpan;
    short partClass;
    float maxScale;
};

struct Part020 {
    Mtx3 *rotmatrix;
    float alpha;
    float rot;
    float asign;
    float offset;
    float angle;
    MobyInstance *target;
    float vel;
};

struct Part025 {
    Vec4 vel;
    float r;
    float g;
    float b;
    float alpha;
};

struct Part027 {
    Vec4 vel;
    int timer;
    int lifeSpan;
    int alpha;
};

struct Part030 {
    Vec4 vel;
    PartInstance *prev;
    PartInstance *next;
    float ground;
    short grounded;
    unsigned short type;
};

struct Part040 {
    Vec4 vel;
    float rot;
    short timer;
    short posttimer;
    unsigned char flags;
    unsigned char scaleFactor;
    short sPad;
    MobyInstance *parent;
};

struct Part042 {
    Vec4 vel;
    float rot;
    short timer;
    short posttimer;
    unsigned char flags;
    unsigned char pad_19[3];
    MobyInstance *parent;
};

// RaC1 uses an 8-bit rotSpeed; DL widened it to 16 bits.

struct Part048 {
    Vec4 vel;
    float invTimer;
    int RGBA1;
    int RGBA2;
    char rotSpeed;
    unsigned char pad_1D[3];
};

struct Part052 {
    float initScale;
    float finalScale;
    int initRGBA;
    int finalRGBA;
    float invTime;
};

struct Part058 {
    Vec4 vel;
    unsigned char type;
    unsigned char fade_time;
    unsigned char burst_time;
    unsigned char spawn_rate;
    unsigned char state;
    unsigned char flame_time;
    unsigned char alpha_top;
    unsigned char pad;
    MobyInstance *pParent;
    float damageHp;
};

struct Part059 {
    Vec4 ofs;
    int type;
    MobyInstance *hero;
    int pad[2];
};

struct Part064 {
    Vec4 vel;
    float height;
    float gravity;
    int endRGBA;
};

struct Part066 {
    Vec4 vel;
    float expandSpeed;
};

struct update78 {
    Vec4 closePt;
    int generator;
    int fadeTime;
    int pad[2];
};

struct Part071 {
    unsigned int vel1;
    unsigned int vel2;
    int rgba1;
    int rgba2;
    short shootTimer;
    short slowTimer;
    short fadeTimer;
    short pad_16;
    update78 *p78Var;
};

// RaC1-specific layouts without a verified named DL equivalent.

struct PartLineMotion {
    Vec4 origin;
    Vec4 velocity;
};

struct PartSpinMotion {
    Vec4 velocity;
    char rotationStep;
};

struct PartRotationMotion {
    char unk_00[0x18];
    char rotationStep;
};

struct PartFollowFade {
    short fadeStep; // alpha removed each frame
    short mode;     // 1 = frozen, 2 = follows pMoby
    MobyInstance *pMoby;
    char unk_08[8];
    Vec4 offset; // offset from pMoby
};

enum PartSplittingFlags {
    PART_SPLIT_REVERSE_ROTATION = 1,
    PART_SPLIT_FADING = 8,
    PART_SPLIT_NO_MOMENTUM = 0x40,
    PART_SPLIT_CHILD = 0x80
};

enum {
    PART_TEXTURE_SPLITTING = 12,
    PART_SPLIT_COLLISION_NO_DAMAGE = 4,
    PART_SPLIT_DAMAGE_FLAGS = 0x10001
};

enum PartBranchingFlags {
    PART_BRANCH_FADING = 1,
    PART_BRANCH_BOOST = 2,
    PART_BRANCH_GRAVITY = 4,
    PART_BRANCH_LONG_FADE = 8
};

enum { PART_DRIFT_COLLISION_FLAGS = 0x12 };

enum { PART_COLOR_DECAY_COLLISION_FLAGS = 2 };

enum PartDebrisKind {
    PART_DEBRIS_SPAWN_ON_LANDING = 1,
    PART_DEBRIS_UPWARD_ACCELERATING = 3
};

enum PartLinkedFlags {
    PART_LINK_FIXED = 1,
    PART_LINK_FADING = 2
};

enum PartTweenEmitterPhase {
    PART_TWEEN_INITIAL = 0,
    PART_TWEEN_EMITTING = 1,
    PART_TWEEN_EMITTED = 2
};

enum { PART_TEXTURE_TWEEN_EMITTER = 58 };

// Retail tests grounded/type with a packed 64-bit load beginning at ground.
#define PART_LINK_BLOCKED_MASK 0x1FFFF00000000LL

struct PartInstance {
    char i_class;
    char type;
    char tex;
    char gs_alpha;
    int rgba;
    char rot;
    char draw_dist;
    short timer;
    float scale;
    Vec4 pos;
    // Original fixed-size storage; the particle class selects its effect struct.
    int update[8];
};
// Texture slot of each particle class, indexed by the iClass passed to CreatePart.
extern unsigned char *PartTextures[];

// The level's particle texture data, and the GS address words built for each particle texture.
struct PartTex {
    int unk_00;
    int unk_04;
};

extern unsigned char PartTexData[];
extern int PartTexCnt;
extern PartTex PartTexs[];

PartInstance *CreatePart(int iClass);
void DeletePart(PartInstance *part);

void UpdatePart_018(PartInstance *part);

void UpdatePart_034(PartInstance *part);

void UpdatePart_042(PartInstance *part);

void UpdatePart_064(PartInstance *part);
void UpdatePart_065(PartInstance *particle);

extern unsigned int PartFloorBurstRandomLimit;
// Original unreferenced small-data constants retained for the overlay layout.
extern const unsigned int PartLiteralSignedMask;
extern const unsigned int PartLiteralByteMask;
extern const float PartLiteralHalf;
extern const float PartLiteralZero;
extern const unsigned int PartLiteralNine;

PartInstance *SpawnPart_015(Vec4 *pos, Vec4 *vel, int beginRGBA, int endRGBA, float maxScale, int numFrames, int master, int useTex, int useGsAlpha);
PartInstance *SpawnPart_045(Vec4 *position, int flags, int color, float scale, float scaleStep);

void SpawnPart_008(Vec4 *position, Vec4 *velocity, int startColor, int endColor, int lifetime, float scale);

void UpdatePart_020(PartInstance *part);

void UpdatePart_057(PartInstance *part);

void UpdatePart_060(PartInstance *part);

void UpdatePart_071(PartInstance *part);
void UpdatePart_072(PartInstance *particle);

void UpdatePart_073(PartInstance *part);

PartInstance *SpawnPart_040(Vec4 *position, Vec4 *velocity, int flags, MobyInstance *owner);
void UpdatePart_041(PartInstance *particle);
PartInstance *SpawnPart_042(Vec4 *position, Vec4 *velocity, int flags, MobyInstance *owner);
void UpdatePart_043(PartInstance *particle);

// RaC1 places randomVelSpeed last; DL places it before generationCount.
void SpawnPart_011(Vec4 *pos, Vec4 *vel, int beginRGBA, int endRGBA, float maxScale, int numFrames, int totalTime, int generationCount, int state, float randomVelSpeed);
void UpdatePart_012(PartInstance *particle);

void UpdatePart_004(PartInstance *particle);

void UpdatePart_026(PartInstance *particle);

PartInstance *SpawnPart_016(Vec4 *position, Vec4 *velocity, int startColor, int endColor,
                             float scale, int lifetime, int kind);
void UpdatePart_017(PartInstance *particle);

void UpdatePart_031(PartInstance *particle);

void UpdatePart_021(PartInstance *particle);

extern PartInstance *PartInstances;
PartInstance *SpawnPart_058(Vec4 *position, int phase, int tweenFrames, int emitFrames, int emitCount, int lifetime, MobyInstance *pParent, float damageScale, float speedScale);
void UpdatePart_059(PartInstance *particle);

#endif
