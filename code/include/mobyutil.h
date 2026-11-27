#ifndef MOBYUTIL_H
#define MOBYUTIL_H

enum { MOBY_GROUP_INDEX_MASK = 0x7FFF };

#include "moby.h"

struct MobyPath;
struct Manipulator;

// Trail of translucent copies that follow a moby.
struct MotionBlur {
    Vec4 posHistory[8];        // 0x000
    Vec4 rotHistory[8];        // 0x080
    int alpha[4];              // 0x100
    int delay[4];              // 0x110
    MobyInstance *copies[4];   // 0x120
    short head;                // 0x130
    short filled;              // 0x132
    MobyInstance *pMoby;       // 0x134
    int count;                 // 0x138
    int active;                // 0x13C
};

// Movement tuning shared by the scripted movers (names from Deadlocked's MoveVars).
struct MoveVars {
    int collRadius;       // 0x00
    float kneeHeight;     // 0x04
    float maxStepDown;    // 0x08
    float maxStepUp;      // 0x0C
    float realSpeed;      // 0x10
    float turnSpeed;      // 0x14
    float vertVel;        // 0x18
    float accel;          // 0x1C
    float deccel;         // 0x20
    float maxSpeed;       // 0x24
    float heading;        // 0x28
    float distThresh;     // 0x2C
    float zDepth;         // 0x30
    char unk_34[4];
    int flags;            // 0x38
    float turnAccel;      // 0x3C
    float turnDeccel;     // 0x40
    float turnLimit;      // 0x44
    int moveTimer;        // 0x48
    float moveHeading;    // 0x4C
};

int MB_RequestHelpMessage(int selector, int messageId);

void DeleteMoby(MobyInstance *moby);
void AttachManipulator(MobyInstance *moby, int animJoint, Manipulator *manipulator);
void DetachManipulator(MobyInstance *moby, Manipulator *manipulator);
void MB_ToastMessageByIndex(int level);
extern MobyInstance *MobyInstances;

void CreateMotionBlur(MobyInstance *pMoby, MotionBlur *blur);
void DeleteMotionBlur(MotionBlur *blur);
void MB_ToastMessage(int message, int time);
void MB_ToggleManipulator(MobyInstance *moby, int animJoint, Manipulator *manipulator, float scale);
float MB_WrapRot(float angle);
int MB_PathFollowToPos(MobyPath *path, Vec4 *point, Vec4 *nearest, int *segment, float *fraction, int wrap, float limit, float step, float tolerance);
void MB_DeleteMobyFromDynamicGroup(MobyInstance *moby, short *group);
void MB_InitMoveVars(MoveVars *vars);

void MB_UnlockLevel(int level);
void MB_UnlockItem(int item, char equip);

float Lerp(float from, float to, float weight);

struct COLL_DAM_IN {
    Vec4 momentum;
    MobyInstance *pMoby;
    int damageFlags;
    unsigned char damageClass;
    unsigned char damageStrength;
    unsigned short damageIndex;
    float damageHp;
    int flags;
    float damageHeroHp;
    int shotUID;
    int pad;
};
// Damage reported against a moby by a collision query.
struct COLL_DAM_OUT {
    Vec4 ip;
    Vec4 momentum;
    MobyInstance *pDamager;
    int damageFlags;
    unsigned char damageClass;
    unsigned char damageStrength;
    unsigned short damageIndex;
    float damageHp;
    int flags;
    float damageHeroHp;
    int shotUID;
    MobyInstance *pMoby;
};

// Invalidates cached collision counters when changing levels.
#define COLLISION_COUNTER_INVALIDATE 0x80000000

// The result of the last collision query.
struct COLLOUTPUT {
    char *grid;               // 0x00: the env collision grid
    char *jointCache;         // 0x04
    char *jointCacheKeys;     // 0x08
    int jointCacheNext;       // 0x0C
    int collCount;            // 0x10
    int damageNext;           // 0x14
    MobyInstance *pMoby;      // 0x18: the moby that was hit
    int poly;                 // 0x1C
    Vec4 ip;                  // 0x20: impact point
    Vec4 push;                // 0x30
    Vec4 normal;              // 0x40
    Vec4 v0;                  // 0x50: the hit triangle
    Vec4 v1;                  // 0x60
    Vec4 v2;                  // 0x70
};

extern COLLOUTPUT CollOutput;

struct MobyVolume {
    Vec4 axisX;
    Vec4 axisY;
    Vec4 axisZ;
    Vec4 origin;
    Mtx4 inverseTransform;
};

struct Vec4;
struct Mtx4;

void MB_SetZBoundsFromPos(MobyInstance *moby, float z);

int TweenColor(int from, int to, float fraction);

int DecAlpha(int *rgba, int decrement);

float MB_CollLineWrapper(Vec4 *position);

float MB_catmullRom(float first, float second, float third, float fourth, float fraction);

void *MB_GetPvarsIfMobyHasThem(MobyInstance *moby);

void MB_CopyHeroLights(MobyInstance *moby);

int MB_randInt(int limit);

int MB_randRange(int low, int high);

float MB_randRangeFloat(float low, float high);

float MB_randRangeSigned(float low, float high);

float MB_randRot(void);

void MB_randVector(Vec4 *vector, float low, float high);

void SetCollDamIn(COLL_DAM_IN &damage, MobyInstance *damager, int damageFlags, float damageHp);

void SetCollDamIn_2(COLL_DAM_IN &damage, MobyInstance *damager, int damageFlags, float damageHp, Vec4 *momentum);

void ReorderRGB_Swap(int *red, int *green, int *blue, int mask);

int MB_GetPVarsField10(MobyInstance *moby);

void MB_TransformToQuat(Vec4 *quaternion, Mtx4 *transform);

float Delt(float &value, float target, float step);

void MB_AxisAngleToQuat(Vec4 *quaternion, Vec4 *axis, float angle);

void MB_AddVectorSphere(Vec4 *out, Vec4 *origin, float radius, float azimuth, float elevation);

MobyInstance *MB_GetPlatformParent(MobyInstance *moby);

void ClampVec3Magnitude(Vec4 *vector, float maximum);

int MB_ScaledVecWrapper(Vec4 *vector, float radius);

enum { GOLD_BOLT_LEVEL_COUNT = 20, GOLD_BOLT_SLOTS_PER_LEVEL = 4 };
extern unsigned char GoldBoltFlags[GOLD_BOLT_LEVEL_COUNT][GOLD_BOLT_SLOTS_PER_LEVEL];

enum { GOLD_WEAPON_FLAG_COUNT = 37 };
extern unsigned char GoldWeaponFlags[GOLD_WEAPON_FLAG_COUNT];

enum { SKILL_POINT_FLAG_COUNT = 32 };
extern unsigned char SkillPointFlags[SKILL_POINT_FLAG_COUNT];

int MB_CountGoldBolts(void);

int MB_CountGoldWeapons(void);

int MB_CountSkillPoints(void);

int MB_GetUnspentGoldBolts(void);

void MB_SetGroupField(int group, int value);

float MB_CosineInterpolate(float start, float end, float weight);

float MB_lerpRotCosine(float start, float end, float weight);

float MB_BallisticTicksToHeight(Vec4 *start, Vec4 *velocity, float gravity, int *ticksOut);

void MB_BallisticPosAtTicks(Vec4 *out, Vec4 *start, Vec4 *velocity, float gravity, int ticks);

void MB_RemoveVecComponent(Vec4 *out, Vec4 *vector, Vec4 *axis, float weight);

void MB_BobMotion(MobyInstance *moby, float *phase, float *offset, float height, float phaseStep);

void MB_SphericalToVector(Vec4 *out, float radius, float azimuth, float elevation);

void MB_randSphere(Vec4 *out, float minimum, float maximum);

void MB_randOffset(Vec4 *vector, float range);

void MB_QuatMultiply(Vec4 *out, Vec4 *vector, Vec4 *rotation);

void MB_QuatToEuler(Vec4 *out, Vec4 *angles);

void MB_RotateQuatAxisAngle(Vec4 *out, Vec4 *vector, Vec4 *axis, float angle);

unsigned int Float_To_RGBA(float red, float green, float blue, float alpha);

unsigned int ReorderRGB(unsigned int rgba, int mask);

void MB_SetStateByGroup(int group, int value);

int MB_PushMobyOutOfWalls(MobyInstance *moby, Vec4 *move, float height, float stepHeight, int radiusFixed, int flags);

void MB_RotateMoby(MobyInstance *moby, float xAngle, float yAngle, float zAngle);

float MB_computeLobVelocity(Vec4 *from, Vec4 *to, float speed, float gravity, float *timeOut);

int MB_IsInvalidOrClass502(MobyInstance *moby);

int MB_HasCollPrims(MobyInstance *moby);

float MB_CollLineDown(Vec4 *position, float height, int flags);

float DeltAng(float &angle, float target, float speed, int direction);

float AccelDelt(float &value, float target, float &speed, float gain, float damping, float limit);

float MB_RoundToDecimals(float value, int digits);

float SubRots(float target, float angle, int direction);

int MB_SolveQuad(float first, float second, float third, float *largerRoot, float *smallerRoot);

void MB_CosineInterpolateUnitVec(float fraction, Vec4 *out, Vec4 *from, Vec4 *to);

unsigned int MB_SplineSegmentsReachable(int spline, unsigned int targets, unsigned int from);

void GainDampLimit(float delta, float &speed, float gain, float damping, float limit);

void MB_CosineInterpolateAngVec(float fraction, Vec4 *out, Vec4 *from, Vec4 *to);

int MB_isCrate(MobyInstance *moby);

void MB_DistributeBoltsNearHero(MobyInstance *moby);

float AccelDeltAng(float &angle, float target, float &speed, float gain, float damping, float limit, int direction);

bool MB_isAmmo(MobyInstance *moby);

int MB_HeroStandingOnMoby(MobyInstance *moby);

int MB_MayaFrameTrigger(MobyInstance *moby, float frame);

void MB_SetZBoundsFromGround(MobyInstance *moby);

int MB_IsPntInSphere(Vec4 *point, int index);

int MB_IsPntInCuboid(Vec4 *point, int index);

int MB_IsPntInCylinder(Vec4 *point, int index);

void MB_ReadDamagePush(Vec4 impact, float *angle, float *speed, float *height);


MobyInstance *CreateMoby(int oClass);
void InitMobyInstance(MobyInstance *moby, int oClass);
void PostUpdateMoby(MobyInstance *moby);
void SetMobyLights(MobyInstance *moby, int color, int a, int b, int c);
void MB_SetAnimationNoBlend(MobyInstance *moby, int animation, int frame);

// Plays an animation from a frame, blending from the current pose over blend frames.
void MB_SetAnimation(MobyInstance *moby, int animation, int frame, int blend);

// The frame the moby is currently showing, including the blend fraction.
float MB_BlendAnimFrame(MobyInstance *moby);
void Map_RegisterLevelObject(MobyInstance *moby, int object);
void SetupSpaceShipVars(MobyInstance *moby);
void UpdateMoby_Spaceship(MobyInstance *moby);

// The level's trigger volumes, from the gameplay file.
extern MobyVolume *CuboidVolumes;
extern MobyVolume *SphereVolumes;
extern MobyVolume *CylinderVolumes;
extern AnimLayer AnimLayerPool[];

float MB_GetNormalizedMtxElem(Vec4 *origin, Mtx4 *matrix, Vec4 *position, int axis);

void CollDamageMobyDirect_2(MobyInstance *moby, int damage, int flags, Vec4 *position,
                            Vec4 *direction, float scale);

// Four signed bytes: xyz normalized to the largest component, plus a shared scale.
void MB_compressVector(Vec4 *vector, unsigned int *packed);
void MB_decompressVector(Vec4 *vector, unsigned int *packed);

#endif
