#ifndef PART_H
#define PART_H

#include "moby.h"

struct PartLineMotion {
    Vec4 origin;
    Vec4 velocity;
};

struct PartTimedFade {
    Vec4 velocity;
    int timer;
    int duration;
    int alpha;
};

struct PartSpinMotion {
    Vec4 velocity;
    union {
        char rotationStep;
        int relativeToHero;
    };
};

struct PartScaleFade {
    float startScale;
    float endScale;
    int startColor;
    int endColor;
    float rate;
};

struct PartFadingMotion {
    Vec4 velocity;
    float scaleStep;
};

struct PartRotationMotion {
    char unk_00[0x18];
    char rotationStep;
};

struct PartTweenSpin {
    Vec4 velocity;
    float rate;       // timer-to-fraction scale for the colour tween
    int colorB;
    int colorA;
    char rotationStep;
};

struct PartFollowFade {
    short fadeStep;   // alpha removed each frame
    short mode;       // 1 = frozen, 2 = follows pMoby
    MobyInstance *pMoby;
    char unk_08[8];
    Vec4 offset;      // offset from pMoby
};

struct PartTimedScale {
    int timer;
    float scaleStep;
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

struct PartSplittingMotion {
    Vec4 velocity;              // 0x00
    float rotation;             // 0x10, fraction of a turn
    short age;                  // 0x14
    short fadeFrames;           // 0x16
    unsigned char flags;        // 0x18
    unsigned char unk_19[3];
    MobyInstance *owner;         // 0x1C
};

enum PartBranchingFlags {
    PART_BRANCH_FADING = 1,
    PART_BRANCH_BOOST = 2,
    PART_BRANCH_GRAVITY = 4,
    PART_BRANCH_LONG_FADE = 8
};

struct PartBranchingMotion {
    Vec4 velocity;              // w holds the child velocity scale
    int startColor;             // 0x10
    int endColor;               // 0x14
    unsigned char timer;        // 0x18
    unsigned char flags;        // 0x19
    unsigned char generation;   // 0x1A
    unsigned char lifetime;     // 0x1B
    float sizeCurve;            // 0x1C
};

enum { PART_DRIFT_COLLISION_FLAGS = 0x12 };

struct PartDriftingMotion {
    Vec4 velocity;
    unsigned char *active;
    int fading;
    int offscreenFrames;
    int collisionCounter;
};

enum { PART_COLOR_DECAY_COLLISION_FLAGS = 2 };

struct PartColorDecayMotion {
    Vec4 velocity;              // w holds the vertical acceleration override
    float red;
    float green;
    float blue;
    float alpha;
};

enum PartDebrisKind {
    PART_DEBRIS_SPAWN_ON_LANDING = 1,
    PART_DEBRIS_UPWARD_ACCELERATING = 3
};

struct PartDebrisMotion {
    Vec4 velocity;              // w holds the landing height
    int startColor;
    int endColor;
    short lifetime;
    short kind;
    float startScale;
};

struct PartInstance {
    char i_class;
    char type;
    char tex;
    char gs_alpha;
    int rgba;
    char rot;
    char draw_dist;
    short timer;
    union {
        float scale;
        int rgbaScale;
    };
    Vec4 pos;
    union {
        int update[8];
        PartLineMotion motion20;
        PartTimedFade timedFade;
        PartSpinMotion spinMotion;
        PartScaleFade scaleFade;
        PartFadingMotion fadingMotion;
        PartRotationMotion rotationMotion;
        PartTweenSpin tweenSpin;
        PartFollowFade followFade;
        PartTimedScale timedScale;
        PartSplittingMotion splittingMotion;
        PartBranchingMotion branchingMotion;
        PartDriftingMotion driftingMotion;
        PartColorDecayMotion colorDecayMotion;
        PartDebrisMotion debrisMotion;
    };
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

void UpdatePart_020(PartInstance *part);

void UpdatePart_057(PartInstance *part);

void UpdatePart_060(PartInstance *part);

void UpdatePart_071(PartInstance *part);

void UpdatePart_073(PartInstance *part);

PartInstance *SpawnPart_040(Vec4 *position, Vec4 *velocity, int flags, MobyInstance *owner);
void UpdatePart_041(PartInstance *particle);
PartInstance *SpawnPart_042(Vec4 *position, Vec4 *velocity, int flags, MobyInstance *owner);
void UpdatePart_043(PartInstance *particle);

void SpawnPart_011(Vec4 *position, Vec4 *velocity, int startColor, int endColor, int lifetime,
                   int timer, int generation, float sizeCurve, int flags, float velocityScale);
void UpdatePart_012(PartInstance *particle);

void UpdatePart_004(PartInstance *particle);

void UpdatePart_026(PartInstance *particle);

PartInstance *SpawnPart_016(Vec4 *position, Vec4 *velocity, int startColor, int endColor,
                             float scale, int lifetime, int kind);
void UpdatePart_017(PartInstance *particle);

#endif
