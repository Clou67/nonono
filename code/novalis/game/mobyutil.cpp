#include <stddef.h>

#include "common.h"
#include "path.h"
#include "vuchain.h"
#include "mathfunc_inline.h"
#include "fastfunc.h"
#include "moby.h"
#include "hero.h"
#include "mobyutil.h"
#include "pad.h"
#include "galaxymap.h"
#include "help.h"
#include "libc.h"
#include "gameglobals.h"
#include "memcard.h"
#include "movie.h"
#include "loaders.h"
#include "camera.h"
#include "part.h"
#include "sound.h"
#include "lights.h"

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_DropAmmo);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_SpawnBoltsFromCrate);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_SetAnimationNoBlend);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_SetAnimation);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_SetAnimationFrame);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", func_0026C900);

int RandomNext(void);

int MB_randInt(int limit)
{
    return ((RandomNext() >> 16) & 0x7FFF) % limit;
}

int MB_randRange(int low, int high)
{
    return ((RandomNext() >> 16) & 0x7FFF) % (high - low + 1) + low;
}

float MB_randRangeFloat(float low, float high)
{
    int sample = (RandomNext() >> 16) & 0x7FFF;
    float range = high - low;

    return low + (float)sample * range * (1.0f / 32768.0f);
}

float MB_randRangeSigned(float low, float high)
{
    int sample = RandomNext() >> 16;
    float range = high - low;
    float value = low + (float)(sample & 0xFFF) * range * (1.0f / 4096.0f);

    if (sample & 1)
        value = -value;

    return value;
}

float MB_randRot(void)
{
    int sample = (RandomNext() >> 16) & 0xFFF;

    return (float)(sample - 2048) * 3.14159265358979323846f * (1.0f / 2048.0f);
}

float MB_randRot(void);
float MB_randRangeFloat(float low, float high);
void MB_SphericalToVector(Vec4 *out, float radius, float azimuth, float elevation);

void MB_randVector(Vec4 *vector, float low, float high)
{
    float azimuth = MB_randRot();
    float elevation = MB_randRot();
    float radius = MB_randRangeFloat(low, high);

    MB_SphericalToVector(vector, radius, azimuth, elevation);
}

void MB_randSphere(Vec4 *out, float minimum, float maximum)
{
    float radius = MB_randRangeFloat(minimum, maximum);
    float azimuth = MB_randRot();
    float elevation = MB_randRot();

    out->x = FastAngleSinF(azimuth) * FastAngleCosF(elevation) * radius;
    out->y = FastAngleCosF(azimuth) * FastAngleCosF(elevation) * radius;
    out->z = FastAngleSinF(elevation) * radius;
}

float MB_catmullRom(float first, float second, float third, float fourth, float fraction)
{
    float firstDelta = first - second;
    float cubic = (fourth - third) - firstDelta;
    float fractionSquared = fraction * fraction;
    float linear = third - first;
    float fractionCubed = fractionSquared * fraction;
    float quadratic = firstDelta - cubic;

    return cubic * fractionCubed + quadratic * fractionSquared + linear * fraction + second;
}

float MB_CosineInterpolate(float start, float end, float weight)
{
    if (weight == 0.0f)
        return start;
    if (weight == 1.0f)
        return end;

    float blend = (1.0f - FastAngleSinF(weight * 3.14159265358979323846f)) * 0.5f;
    return start + (end - start) * blend;
}

float FastSubRots(float first, float second);

float MB_lerpRotCosine(float start, float end, float weight)
{
    float delta = FastSubRots(end, start);
    float blend = (1.0f - FastAngleSinF(weight * 3.14159265358979323846f)) * 0.5f;

    return FastAddRots(start, delta * blend);
}

void FastSubVec3(Vec4 *out, Vec4 *first, Vec4 *second);
void FastVec3Add(Vec4 *out, Vec4 *first, Vec4 *second);

void MB_CosineInterpolateUnitVec(float fraction, Vec4 *out, Vec4 *from, Vec4 *to)
{
    if (fraction == 0.0f) {
        CopyVec4Inline(out, from);
        return;
    }
    if (fraction == 1.0f) {
        CopyVec4Inline(out, to);
        return;
    }

    float weight = (1.0f - FastAngleSinF(fraction * 3.141592653589793f)) * 0.5f;
    Vec4 delta;
    FastSubVec3(&delta, to, from);
    FastVec3Scale(&delta, &delta, weight);
    FastVec3Add(out, from, &delta);
}

void MB_CosineInterpolateAngVec(float fraction, Vec4 *out, Vec4 *from, Vec4 *to)
{
    float weight = (1.0f - FastAngleSinF(fraction * 3.141592653589793f)) * 0.5f;
    out->x = FastAddRots(from->x, FastSubRots(to->x, from->x) * weight);
    out->y = FastAddRots(from->y, FastSubRots(to->y, from->y) * weight);
    out->z = FastAddRots(from->z, FastSubRots(to->z, from->z) * weight);
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_DeltAngSpeed);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", OrganicDeltAngSpeed);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", func_0026D1C0);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", GetGroundZ);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", CollMovingSphere);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", func_0026D608);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_PushOutOfWalls);

int MB_PushOutOfWalls(MobyInstance *moby, Vec4 *move, float height, float radius, float stepHeight, int flags);

int MB_PushMobyOutOfWalls(MobyInstance *moby, Vec4 *move, float height, int radiusFixed,
                          float stepHeight, int flags)
{
    float radius = FastIntToFloat(radiusFixed) * (1.0f / 1024.0f);
    return MB_PushOutOfWalls(moby, move, height, radius, stepHeight, flags);
}

void MB_InitMoveVars(MoveVars *vars)
{
    vars->collRadius = 0x280;
    vars->kneeHeight = 1.0f;
    vars->maxStepDown = 0.5f;
    vars->maxStepUp = 0.5f;
    vars->turnSpeed = 0.0f;
    vars->realSpeed = 0.0f;
    vars->vertVel = 0.0f;
    vars->maxSpeed = 2.7f;
    vars->deccel = 0.3f;
    vars->accel = 0.3f;
    vars->heading = 1.57f;
    vars->distThresh = 0.1f;
}

int MB_MoveAndCollide(MobyInstance *moby, MoveVars *vars, Vec4 *target, Vec4 *movement,
                      float speedScale)
{
    Vec4 startPosition;
    Vec4 displacement;
    Vec4 direction;
    Vec4 lookaheadPosition;
    COLLOUTPUT *groundHit;
    int resultFlags = 0;
    int collisionFlags;
    float targetDistance;
    float accelerationStep;
    float speedLimit;
    float probeHeight;
    float speedIncrement;
    float stepGroundHeight;
    float lookaheadGroundHeight;
    float groundHeight;
    float slopeAngle;
    float stepDistance;

    accelerationStep = vars->accel * speedScale;
    speedLimit = vars->maxSpeed * speedScale;
    FastSubVec3(&displacement, target, &moby->pos);
    targetDistance = FastVec3Length(&displacement.x);
    CopyVec4(&startPosition, &moby->pos);
    speedIncrement = accelerationStep * targetDistance;
    if (accelerationStep < speedIncrement)
        speedIncrement = accelerationStep;
    vars->realSpeed = vars->realSpeed + speedIncrement;
    if (targetDistance < vars->realSpeed * 10.0f)
        vars->realSpeed = vars->realSpeed - vars->deccel * vars->realSpeed;
    if (speedLimit < vars->realSpeed)
        vars->realSpeed = speedLimit;

    else if (vars->realSpeed < -speedLimit)
        vars->realSpeed = -speedLimit;

    if (vars->flags & MOVE_USE_HEADING) {
        displacement.x = FastAngleSinF(vars->moveHeading) * vars->realSpeed;
        displacement.y = FastAngleCosF(vars->moveHeading) * vars->realSpeed;
    }

    else {
        displacement.x = FastAngleSinF(moby->rotation.z) * vars->realSpeed;
        displacement.y = FastAngleCosF(moby->rotation.z) * vars->realSpeed;
    }
    if (vars->flags & MOVE_NO_GRAVITY) {
        displacement.z = 0.0f;
    }

    else {
        displacement.z = vars->vertVel;
        vars->vertVel = vars->vertVel - frameTimeSq * 9.0f;
    }

    probeHeight = moby->pos.z + 0.04f;
    FastVec3Add(&direction, &moby->pos, &displacement);
    direction.z = moby->pos.z - vars->zDepth;
    if (GetGroundZ(&direction, moby, vars->flags & MOVE_GROUND_QUERY, vars->maxStepDown,
                   vars->maxStepUp)) {
        groundHit = &CollOutput;
        slopeAngle = FastArcTan(groundHit->normal.z, FastVec3Length(&groundHit->normal.x));
        stepGroundHeight = groundHit->ip.z;
        if (0.5f < slopeAngle && 0.1f < FastVec3Length(&displacement.x)) {
            {
                FastVec3Normalize(&lookaheadPosition, &displacement, 0.57f);
                FastVec3Add(&lookaheadPosition, &lookaheadPosition, &moby->pos);
                lookaheadPosition.z = moby->pos.z - vars->zDepth;
                if (GetGroundZ(&lookaheadPosition, moby, vars->flags & MOVE_GROUND_QUERY,
                               vars->maxStepDown, vars->maxStepUp)) {
                    lookaheadGroundHeight = groundHit->ip.z;
                    if (0.5f <=
                        FastArcTan(groundHit->normal.z, FastVec3Length(&groundHit->normal.x))) {
                        resultFlags = MOVE_BLOCKED | MOVE_UNSAFE_GROUND;
                        if ((vars->flags & MOVE_ALLOW_FALLING) &&
                            lookaheadGroundHeight < probeHeight && stepGroundHeight < probeHeight)
                            resultFlags = MOVE_FALLING;
                    }
                }

                else {
                    resultFlags = MOVE_BLOCKED | MOVE_UNSAFE_GROUND;
                    if ((vars->flags & MOVE_ALLOW_FALLING) && stepGroundHeight < probeHeight)
                        resultFlags = MOVE_FALLING;
                }
            }
        }
    }

    else {
        resultFlags =
            (vars->flags & MOVE_ALLOW_FALLING) ? MOVE_FALLING : MOVE_BLOCKED | MOVE_UNSAFE_GROUND;
    }

    if (!(resultFlags & MOVE_BLOCKED)) {
        stepDistance = FastVec3Length(&displacement.x);
        FastVec3Scale(&direction, &displacement, 1.0f / stepDistance);
        collisionFlags = MB_PushMobyOutOfWalls(moby, &displacement, vars->kneeHeight,
                                               vars->collRadius, vars->zDepth, vars->flags);
        if (collisionFlags & 2)
            vars->vertVel = transStepScale * -0.01f;
        if (collisionFlags & 1) {
            resultFlags |= MOVE_WALL;
            if (displacement.x * direction.x + displacement.y * direction.y < stepDistance * 0.2f)
                resultFlags |= MOVE_BLOCKED;
            groundHeight = MB_CollLineDown(&moby->pos, 0.5f, 0);
            if (vars->maxStepDown < startPosition.z - groundHeight ||
                vars->maxStepUp < groundHeight - startPosition.z) {
                resultFlags |= MOVE_BLOCKED | MOVE_UNSAFE_GROUND;
                CopyVec4(&moby->pos, &startPosition);
            }
        }
        CopyVec4Inline(movement, &displacement);
    }

    else {
        if (!(vars->flags & MOVE_NO_GRAVITY))
            vars->vertVel = transStepScale * -0.01f;
    }

    if (targetDistance < vars->distThresh)
        resultFlags |= MOVE_ARRIVED;
    return resultFlags;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", func_0026DE78);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_MoveAndCollide2);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", func_0026DFF8);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_CountActiveMobysByGroup);

extern short *MobyGroupEntries[];
extern MobyInstance *MobyInstances;
void MB_SetGroupField(int group, int value)
{
    if (MobyGroupEntries[group]) {
        short *entry = MobyGroupEntries[group];
        do {
            int mobyIndex = *entry & MOBY_GROUP_INDEX_MASK;
            MobyInstances[mobyIndex].setByGroup = value;
        } while (*entry++ >= 0);
    }
}

void MB_SetStateByGroup(int group, int value)
{
    if (MobyGroupEntries[group]) {
        short *entry = MobyGroupEntries[group];
        do {
            int mobyIndex = *entry & MOBY_GROUP_INDEX_MASK;
            if ((signed char)MobyInstances[mobyIndex].state >= 0)
                MobyInstances[mobyIndex].state = value;
        } while (*entry++ >= 0);
    }
}

TEXT_PADDING(0, 0, 0, 0, 0, 0);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_GetFirstMobyInGroup);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_GetNextMobyInGroup);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", func_0026E3A0);

int DecAlpha(int *rgba, int decrement)
{
    int color = *rgba;
    int alpha = (color >> 24) - decrement;

    if (alpha < 0)
        alpha = 0;

    *rgba = (color & 0x00FFFFFF) | (alpha << 24);
    return alpha == 0;
}

float MB_BallisticTicksToHeight(Vec4 *start, Vec4 *velocity, float gravity, int *ticksOut)
{
    int ticks = FastFloatToInt(velocity->z / gravity);
    float duration = FastIntToFloat(ticks);
    float gravityDuration = FastIntToFloat((ticks * ticks + ticks) >> 1);
    float height = start->z + velocity->z * duration - gravityDuration * gravity;

    if (ticksOut)
        *ticksOut = ticks;

    return height;
}

void FastVec3Add(Vec4 *out, Vec4 *first, Vec4 *second);

void MB_BallisticPosAtTicks(Vec4 *out, Vec4 *start, Vec4 *velocity, float gravity, int ticks)
{
    Vec4 displacement;

    FastVec3Scale(&displacement, velocity, FastIntToFloat(ticks));
    displacement.z -= FastIntToFloat((ticks * ticks + ticks) >> 1) * gravity;
    FastVec3Add(out, start, &displacement);
}

float FastAbsF(float value);
float FastFSqrt(float value);

int MB_SolveQuad(float first, float second, float third, float *largerRoot, float *smallerRoot)
{
    float discriminant = second * second - first * 4.0f * third;
    if (discriminant == 0.0f) {
        *largerRoot = -second / (first + first);
        return 1;
    }

    float root = FastFSqrt(FastAbsF(discriminant));
    float denominator = first + first;
    *largerRoot = (-second + root) / denominator;
    *smallerRoot = (-second - root) / denominator;

    if (*largerRoot < *smallerRoot) {
        float value = *largerRoot;
        float other = *smallerRoot;
        *smallerRoot = value;
        *largerRoot = other;
    }
    return discriminant > 0.0f ? 2 : 0;
}

enum { COLL_LINE_GROUND_QUERY = 2 };
int CollLine(Vec4 *start, Vec4 *end, int flags, MobyInstance *ignore, MobyInstance *ignoreOther);

float MB_CollLineDown(Vec4 *position, float height, int flags)
{
    Vec4 ground;
    Vec4 start;
    CopyVec4Inline(&ground, position);
    ground.z = 0.01f;
    CopyVec4Inline(&start, position);
    start.z += height;

    if (CollLine(&start, &ground, flags | COLL_LINE_GROUND_QUERY, 0, 0))
        return MemSlots.collisionPoint.z;
    return 0.0f;
}

enum { COLLISION_PROBE_FLAGS = 0x20 };

float MB_CollLineWrapper(Vec4 *position)
{
    return MB_CollLineDown(position, 0.5f, COLLISION_PROBE_FLAGS);
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", func_0026E6B8);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", PointInsideComplexPoly);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", func_0026E790);

int MB_HasCollPrims(MobyInstance *moby)
{
    MobyCollPrims *prims = moby->pCollPrims;
    if (prims && prims->count)
        return 1;

    return 0;
}

void FastVecZero(Vec4 *vector);

void SetCollDamIn(COLL_DAM_IN &damage, MobyInstance *damager, int damageFlags, float damageHp)
{
    damage.pMoby = damager;
    damage.damageFlags = damageFlags;
    damage.damageHp = damageHp;
    damage.flags = 0;

    FastVecZero(&damage.momentum);
}

enum { COLL_DAMAGE_HAS_MOMENTUM = 1 };

void SetCollDamIn_2(COLL_DAM_IN &damage, MobyInstance *damager, int damageFlags, float damageHp, Vec4 *momentum)
{
    damage.pMoby = damager;
    damage.damageFlags = damageFlags;
    damage.damageHp = damageHp;
    damage.flags = COLL_DAMAGE_HAS_MOMENTUM;

    CopyVec4Inline(&damage.momentum, momentum);
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", DamageSphereAtPos);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", CollDamageMobyDirect);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", CollDamageMobyDirect_2);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", func_0026EBE0);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_CollLineMulti);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", CollWaterHeight);

void FastQuatToEuler(Vec4 *out, float angle, int axis);
void FastQuaternionMult(Vec4 *out, Vec4 *left, Vec4 *right);

void MB_QuatToEuler(Vec4 *out, Vec4 *angles)
{
    Vec4 zRotation, yRotation, xRotation;

    FastQuatToEuler(&xRotation, angles->x, 0);
    FastQuatToEuler(&yRotation, angles->y, 1);
    FastQuatToEuler(&zRotation, angles->z, 2);
    FastQuaternionMult(out, &xRotation, &yRotation);
    FastQuaternionMult(out, out, &zRotation);
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_RegisterLameShadow);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", func_0026EFF0);

void MB_SetZBoundsFromPos(MobyInstance *moby, float z)
{
    const float padding = 0.2f;
    moby->shadowPlane = z - padding;
    moby->shadowRange = z + padding;
}

void MB_SetZBoundsFromGround(MobyInstance *moby)
{
    Vec4 ground;
    Vec4 start;
    const float clearance = 0.5f;
    const float depth = 16.0f;
    const float padding = 0.2f;

    CopyVec4Inline(&ground, &moby->pos);
    ground.z -= depth;
    if (ground.z < clearance)
        ground.z = clearance;

    CopyVec4Inline(&start, &moby->pos);
    start.z += clearance;

    if (CollLine(&start, &ground, COLLISION_PROBE_FLAGS | COLL_LINE_GROUND_QUERY, 0, 0)) {
        moby->shadowPlane = CollOutput.ip.z - padding;
        moby->shadowRange = CollOutput.ip.z + padding;
    }

    else {
        moby->shadowPlane = 0.0f;
        moby->shadowRange = 0.0f;
    }
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_SetZBoundsFromFloorCeil);

int TweenColor(int from, int to, float fraction)
{
    return FastTweenColor(from, to, fraction);
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_FindSlotByMask);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_HandleDamage);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", func_0026F868);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_DamageMobyList);

static const float DAMAGE_PUSH_TAG = 5627.9248046875f;

void MB_ReadDamagePush(Vec4 impact, float *angle, float *speed, float *height)
{
    if (impact.w != DAMAGE_PUSH_TAG)
        *angle = FastArcTan(impact.x, impact.y);

    else {
        *angle = FastArcTan(impact.x, impact.y);
        float length = FastVec3Length(&impact.x);
        impact.w = 0.0f;
        *speed *= length;
        *height *= impact.z;
    }
}

void FastSubVec3(Vec4 *out, Vec4 *first, Vec4 *second);

float MB_computeLobVelocity(Vec4 *from, Vec4 *to, float speed, float gravity, float *timeOut)
{
    Vec4 offset;
    FastSubVec3(&offset, to, from);
    float time = FastVec3Length(&offset.x) / speed;
    if (timeOut)
        *timeOut = time;
    if (time == 0.0f)
        return 0.0f;

    return -(from->z - to->z + gravity * (time * time) * 0.5f) / time;
}

int MB_randPrimPoints(float density, MobyInstance *moby, int maximum, Vec4 *points, int mask)
{
    enum HitShape {
        SHAPE_INLINE_CENTER_SPHERE = 0x0,
        SHAPE_INLINE_CENTER_SPHERE_ALT = 1,
        SHAPE_INDEXED_CENTER_SPHERE = 0x2,
        SHAPE_XY_DISK_WITH_Z_EXTENT = 0x3,
        SHAPE_ENDPOINT_SEGMENT_WITH_BALL_OFFSET = 0x4
    };

    float weights[20];
    CollPrim *eligiblePrimitives[20];
    Vec4 shapeCenter, sampleOffset, segmentDelta, segmentPoint, capsuleOffset;
    CollPrimShape *shape;
    CollPrim *primitive;
    int eligibleCount, primitiveIndex, selectedIndex, pointIndex, pointCount;
    unsigned int primitiveFlags;
    unsigned int lastPrimitive;
    float totalVolume, sampleWeight, radius, sampleExtent, sampleDistance;
    int primitiveType;

    {
        CollPrim *primitive;
        MobyCollPrims *collision = moby->pClass->collision;
        primitive = (CollPrim *)collision;
        if (!primitive)
            return 0;
        if (collision->primSetB)
            MobyComputeJointMtxs(moby, collision->primSetB, 0);
        if (collision->unk04 <= 0)
            return 0;
        eligibleCount = 0;
        primitiveIndex = 0;
        totalVolume = 0.0f;
        primitive = collision->primitives;
        {
            CollPrimShape *shape;
            shape = &primitive->shape;
            do {
                float radius, sampleExtent;
                int primitiveType;
                unsigned int enabled;
                primitiveFlags = primitive->flags;
                lastPrimitive = (primitiveFlags & COLLPRIM_LAST) != 0;
                primitiveType = primitiveFlags & 0xff;
                bool excludedByMask = ((mask >> primitiveIndex) & 1) == 0;
                enabled = primitiveFlags & COLLPRIM_RANDOM_POINTS;
                if (!excludedByMask && enabled) {
                    eligiblePrimitives[eligibleCount] = primitive;
                    switch (primitiveType) {
                    case SHAPE_INLINE_CENTER_SPHERE:
                    case SHAPE_INLINE_CENTER_SPHERE_ALT:
                    case SHAPE_INDEXED_CENTER_SPHERE: {
                        if (primitiveType < SHAPE_INDEXED_CENTER_SPHERE) {
                            CopyVec4Inline(&shapeCenter, &primitive->offset);
                            FastScaleVec4(&shapeCenter, &shapeCenter, moby->scale * 0.0009765625f);
                            radius = shapeCenter.w;
                        }

                        else {
                            CopyVec4Inline(&shapeCenter, &SPAD_JOINTS[shape->joint]);
                            CopyVec4Inline(&sampleOffset, &primitive->offset);
                            FastVec3Add(&shapeCenter, &shapeCenter, &sampleOffset);
                            FastVec3Scale(&shapeCenter, &shapeCenter, moby->scale * 0.0009765625f);
                            radius = moby->scale;
                            radius = primitive->radius * radius * 0.0009765625f;
                        }
                        weights[eligibleCount] = radius * 4.1887903f * radius * radius;
                        break;
                    }
                    case SHAPE_XY_DISK_WITH_Z_EXTENT: {
                        float radius, sampleExtent;
                        CopyVec4Inline(&shapeCenter, &primitive->offset);
                        FastVec3Scale(&shapeCenter, &shapeCenter, moby->scale);
                        radius = shapeCenter.w * moby->scale;
                        radius *= 0.0009765625f;
                        sampleExtent = shape->length * (moby->scale * 0.0009765625f);
                        weights[eligibleCount] = radius * 4.187743f * radius * radius +
                                                 radius * 1.5707964f * radius * sampleExtent;
                        break;
                    }
                    case SHAPE_ENDPOINT_SEGMENT_WITH_BALL_OFFSET: {
                        ScaleJointPosition(&shapeCenter, &SPAD_JOINTS[shape->ends.a],
                                           moby->scale * 0.0009765625f);
                        ScaleJointPosition(&sampleOffset, &SPAD_JOINTS[shape->ends.b],
                                           moby->scale * 0.0009765625f);
                        FastSubVec3(&segmentDelta, &shapeCenter, &sampleOffset);
                        radius = FastVec3Length2(&segmentDelta);
                        sampleExtent = primitive->radius * moby->scale * 0.0009765625f;
                        weights[eligibleCount] = sampleExtent * 1.5707964f * sampleExtent * radius;
                        break;
                    }
                    }
                    totalVolume += weights[eligibleCount];
                    eligibleCount++;
                }
                primitiveIndex++;
                shape = (CollPrimShape *)((unsigned char *)shape + sizeof(CollPrim));
                primitive++;
            } while (!lastPrimitive);
        }
    }

    pointCount = (int)(density * totalVolume + 0.5f);
    if (maximum < pointCount)
        pointCount = maximum;

    for (pointIndex = 0; pointIndex < pointCount; pointIndex++) {
        sampleDistance = MB_randRangeFloat(0.0f, totalVolume);
        for (selectedIndex = 0; selectedIndex < eligibleCount; selectedIndex++) {
            if (sampleDistance < weights[selectedIndex])
                break;
            sampleDistance -= weights[selectedIndex];
        }
        primitive = eligiblePrimitives[selectedIndex];
        switch (primitiveType = primitive->collType) {
        case SHAPE_INLINE_CENTER_SPHERE:
        case SHAPE_INLINE_CENTER_SPHERE_ALT:
        case SHAPE_INDEXED_CENTER_SPHERE: {
            float radius, sampleExtent;
            if (primitiveType < SHAPE_INDEXED_CENTER_SPHERE) {
                CopyVec4Inline(&shapeCenter, &primitive->offset);
                FastVec3Scale(&shapeCenter, &shapeCenter, moby->scale);
                sampleExtent = shapeCenter.w * moby->scale;
            }

            else {
                CopyVec4Inline(&shapeCenter, &SPAD_JOINTS[primitive->joint]);
                CopyVec4Inline(&sampleOffset, &primitive->offset);
                FastVec3Add(&shapeCenter, &shapeCenter, &sampleOffset);
                FastVec3Scale(&shapeCenter, &shapeCenter, moby->scale);
                sampleExtent = primitive->radius * moby->scale;
            }
            sampleExtent *= 0.0009765625f;
            FastVecDivScalar(&shapeCenter, &shapeCenter, 1024.0f);
            for (;;) {
                sampleOffset.x = MB_randRangeFloat(-sampleExtent, sampleExtent);
                sampleOffset.y = MB_randRangeFloat(-sampleExtent, sampleExtent);
                sampleOffset.z = MB_randRangeFloat(-sampleExtent, sampleExtent);
                if (FastVec3Length2(&sampleOffset) <= sampleExtent) {
                    FastVec3Add(&sampleOffset, &sampleOffset, &shapeCenter);
                    FastVecMtx3Mult(&sampleOffset, &sampleOffset, &moby->transform);
                    FastVec3Add(&points[pointIndex], &sampleOffset, &moby->pos);
                    break;
                }
            }
            break;
        }
        case SHAPE_XY_DISK_WITH_Z_EXTENT: {
            float radius, sampleExtent, sampleWeight, sampleDistance, angle;
            CopyVec4Inline(&shapeCenter, &primitive->offset);
            FastVec3Scale(&shapeCenter, &shapeCenter, moby->scale);
            radius = shapeCenter.w * moby->scale;
            sampleExtent = primitive->length * moby->scale;
            FastVecDivScalar(&shapeCenter, &shapeCenter, 1024.0f);
            radius *= 0.0009765625f;
            sampleExtent *= 0.0009765625f;
            sampleWeight = MB_randRangeFloat(0.0f, radius * radius);
            sampleWeight = FastFSqrt(sampleWeight);
            sampleDistance = MB_randRangeFloat(0.0f, sampleExtent);
            angle = MB_randRot();
            sampleOffset.x = FastAngleSinF(angle) * sampleWeight;
            sampleOffset.y = FastAngleCosF(angle) * sampleWeight;
            sampleOffset.z = sampleDistance;
            FastVec3Add(&sampleOffset, &sampleOffset, &moby->pos);
            FastVec3Add(&points[pointIndex], &shapeCenter, &sampleOffset);
            break;
        }
        case SHAPE_ENDPOINT_SEGMENT_WITH_BALL_OFFSET: {
            float sampleExtent, sampleWeight;
            shape = &primitive->shape;
            ScaleJointPosition(&shapeCenter, &SPAD_JOINTS[shape->ends.a], moby->scale);
            ScaleJointPosition(&sampleOffset, &SPAD_JOINTS[shape->ends.b], moby->scale);
            FastSubVec3(&segmentDelta, &sampleOffset, &shapeCenter);
            sampleWeight = MB_randRangeFloat(0.0f, 1.0f);
            FastVec3Scale(&segmentDelta, &segmentDelta, sampleWeight);
            FastVec3Add(&segmentPoint, &segmentDelta, &shapeCenter);
            FastVecDivScalar(&segmentPoint, &segmentPoint, 1024.0f);
            sampleExtent = primitive->radius * moby->scale;
            sampleExtent = sampleExtent * 0.0009765625f;
            do {
                capsuleOffset.x = MB_randRangeFloat(-sampleExtent, sampleExtent);
                capsuleOffset.y = MB_randRangeFloat(-sampleExtent, sampleExtent);
                capsuleOffset.z = MB_randRangeFloat(-sampleExtent, sampleExtent);
            } while (!(FastVec3Length2(&capsuleOffset) <= sampleExtent));
            FastVec3Add(&capsuleOffset, &capsuleOffset, &segmentPoint);
            FastVecMtx3Mult(&capsuleOffset, &capsuleOffset, &moby->transform);
            FastVec3Add(&points[pointIndex], &capsuleOffset, &moby->pos);
            break;
        }
        }
    }
    return pointCount;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", func_00270330);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_updateJump);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", func_002705A0);

float Lerp(float from, float to, float weight)
{
    return from + (to - from) * weight;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", Lerp_vec4);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", func_00270650);

void GainDampLimit(float delta, float &speed, float gain, float damping, float limit)
{
    speed += gain * delta - damping * speed;
    if (limit > 0.0f) {
        if (speed > limit)
            speed = limit;
        else if (speed < -limit)
            speed = -limit;
    }

    if (speed > FastAbsF(delta))
        speed = FastAbsF(delta);
    else if (speed < -FastAbsF(delta))
        speed = -FastAbsF(delta);
}

float FastAbsF(float value);

float Delt(float &value, float target, float step)
{
    float delta = target - value;

    if (delta > step)
        delta = step;
    else if (delta < -step)
        delta = -step;

    value += delta;
    return FastAbsF(target - value);
}

void GainDampLimit(float delta, float &speed, float gain, float damping, float limit);

float AccelDelt(float &value, float target, float &speed, float gain, float damping, float limit)
{
    GainDampLimit(target - value, speed, gain, damping, limit);
    value += speed;
    float remaining = target - value;
    if (FastAbsF(remaining) < limit * 0.01f) {
        value = target;
        speed = 0.0f;
        return speed;
    }
    return remaining;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", OrganicDelt);

static const float SAME_ANGLE = 0.001745329238474369f;
static const float FULL_ROTATION = 6.283185307179586f;

float SubRots(float target, float angle, int direction)
{
    float delta = FastSubRots(target, angle);
    if (!direction || delta * direction > 0.0f)
        return delta;
    if (FastAbsF(delta) <= SAME_ANGLE)
        return 0.0f;
    if (delta > 0.0f)
        return delta - FULL_ROTATION;
    return delta + FULL_ROTATION;
}

float SubRots(float target, float angle, int direction);

float DeltAng(float &angle, float target, float speed, int direction)
{
    float delta = SubRots(target, angle, direction);
    if (delta > speed)
        delta = speed;
    else if (delta < -speed)
        delta = -speed;
    angle = FastAddRots(angle, delta);
    return SubRots(target, angle, direction);
}

enum { TURN_DIRECTION_AUTO = 2 };

float AccelDeltAng(float &angle, float target, float &speed, float gain, float damping, float limit, int direction)
{
    if (direction == TURN_DIRECTION_AUTO) {
        if ((target > 0.0f && angle < 0.0f) || (target < 0.0f && angle > 0.0f))
            direction = target < 0.0f ? -1 : 1;
        else
            direction = 0;
    }

    GainDampLimit(SubRots(target, angle, direction), speed, gain, damping, limit);
    angle = FastAddRots(angle, speed);
    float remaining = SubRots(target, angle, direction);
    if (FastAbsF(remaining) < limit * 0.01f) {
        angle = target;
        speed = 0.0f;
        return speed;
    }
    return remaining;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", OrganicDeltAng);

unsigned int Float_To_RGBA(float red, float green, float blue, float alpha)
{
    int redByte = FastFloatToInt(red * 255.0f) & 0xFF;
    int greenByte = FastFloatToInt(green * 255.0f) & 0xFF;
    int blueByte = FastFloatToInt(blue * 255.0f) & 0xFF;
    unsigned int alphaByte = FastFloatToInt(alpha * 255.0f);

    return redByte | (greenByte << 8) | (blueByte << 16) | (alphaByte << 24);
}

enum { SWAP_RED_GREEN = 1, SWAP_GREEN_BLUE = 2, SWAP_BLUE_RED = 4 };

void ReorderRGB_Swap(int *red, int *green, int *blue, int mask)
{
    if (mask & SWAP_RED_GREEN) {
        int saved = *red;
        *red = *green;
        *green = saved;
    }

    if (mask & SWAP_GREEN_BLUE) {
        int saved = *green;
        *green = *blue;
        *blue = saved;
    }

    if (mask & SWAP_BLUE_RED) {
        int saved = *blue;
        *blue = *red;
        *red = saved;
    }
}

unsigned int ReorderRGB(unsigned int rgba, int mask)
{
    if (!mask)
        return rgba;

    int red = rgba & 0xFF;
    int green = (int)(rgba & 0xFF00) >> 8;
    int blue = (rgba >> 16) & 0xFF;
    unsigned int alpha = rgba >> 24;

    ReorderRGB_Swap(&red, &green, &blue, mask);
    return (alpha << 24) | (blue << 16) | (green << 8) | red;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_NormalizeMtx3Columns);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_GetNormalizedMtxElem);

void FastVec3Normalize(Vec4 *out, Vec4 *vector, float magnitude);
float FastVec3Dot(Vec4 *first, Vec4 *second);
void FastSubVec3(Vec4 *out, Vec4 *first, Vec4 *second);

void MB_RemoveVecComponent(Vec4 *out, Vec4 *vector, Vec4 *axis, float weight)
{
    Vec4 component;
    Vec4 unitAxis;

    FastVec3Normalize(&unitAxis, axis, 1.0f);
    float scale = FastVec3Dot(&unitAxis, vector) * weight;
    FastVec3Scale(&component, &unitAxis, scale);
    FastSubVec3(out, vector, &component);
}

struct MobySpecialVars {
    void *pVars;
    char unk_04[4];
    MobyInstance *platformParent;
    char unk_0C[4];
    int unk_10;
};

void *MB_GetPvarsIfMobyHasThem(MobyInstance *moby)
{
    if (!moby)
        return 0;

    if (moby->modeBits & HAS_SPECIAL_VARS)
        return ((MobySpecialVars *)moby->pVar)->pVars;

    return 0;
}

int MB_GetPVarsField10(MobyInstance *moby)
{
    if (!moby)
        return 0;

    if (moby->modeBits & HAS_SPECIAL_VARS)
        return ((MobySpecialVars *)moby->pVar)->unk_10;

    return 0;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_MistDeathEffect);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_StartKick);

int MB_UpdateKick(MobyInstance *moby, KnockbackMotion *motion)
{
    enum { MOTION_RISING = 0, MOTION_FALLING = 1, MOTION_GROUNDED = 2 };
    Vec4 sweepStart;
    Vec4 heightProbe;
    Vec4 collisionProbe;
    Vec4 predictedPosition;
    Vec4 surfaceNormal;
    Vec4 normalResponse;
    float horizontalSpeed, largerRoot, smallerRoot, remainingSpeed;

    Vec4 *collisionPosition;
    COLLOUTPUT *collisionResult;
    int resultFlags = 0;

    float coordinateScale, groundHeight, landingTicks, targetValue, animationStep, unitLength;
    int hitCount, hitIndex;

    motion->velocity.z = motion->velocity.z - motion->gravity;
    if (motion->particleMode == 1) {
        if (motion->particleMask != 0)
            MB_MistDeathEffect(moby, &motion->velocity, motion->particleMask);
    }

    horizontalSpeed = FastVec3Length(&motion->velocity.x);
    targetValue = (motion->phase == MOTION_GROUNDED) ? 0.0f : motion->targetSpeed;
    Delt(horizontalSpeed, targetValue, motion->speedApproachStep);
    FastVec3RSqrtScale(&motion->velocity, &motion->velocity, horizontalSpeed);
    if (motion->verticalSpeed < motion->velocity.z)
        motion->velocity.z = motion->verticalSpeed;

    CopyVec4Inline(&heightProbe, &moby->pos);
    heightProbe.z = heightProbe.z + motion->collisionZOffset;
    groundHeight = MB_CollLineDown(&heightProbe, 0.5f, 0);
    if (CollHotspot() == 0) {
        if (motion->groundBounces == 0.0f && groundHeight <= heightProbe.z &&
            heightProbe.z + motion->velocity.z < groundHeight) {
            motion->groundBounces = 1.0f;
            heightProbe.z = groundHeight;
            M775_SpawnSplash(&heightProbe, 3.0f);
        }
        groundHeight = MB_CollLineWrapper(&moby->pos);
    }

    else if ((motion->flags & KICK_STOP_AT_LEDGE) || motion->phase == MOTION_GROUNDED) {
        FastVec3Add(&collisionProbe, &moby->pos, &motion->velocity);
        if (MB_CollLineWrapper(&collisionProbe) < groundHeight - 0.25f)
            FastVec3RSqrtScale(&motion->velocity, &motion->velocity, 0.0f);
    }

    if (motion->groundBounces != 0.0f) {
        if (motion->groundBounces < 4.0f)
            FastVec3Scale(&motion->velocity, &motion->velocity, 0.7f);
        if (motion->groundBounces < 7.0f) {
            motion->groundBounces = motion->groundBounces + 1.0f;
            motion->gravity = motion->gravity * 0.75f;
        }
    }

    if (moby->pos.x < 2.0f || 1021.0f < moby->pos.x || moby->pos.y < 2.0f ||
        1021.0f < moby->pos.y || moby->pos.z < 2.0f || 1021.0f < moby->pos.z) {
        resultFlags = KICK_OUT_OF_BOUNDS;
    }

    if (motion->landingAnimationFrame != -1.0f && motion->apexAnimationFrame != -1.0f) {
        switch (motion->phase) {
        case MOTION_RISING: {
            float ratio;
            ratio = FastAbsF(motion->velocity.z / motion->gravity);
            if (2.0f < ratio) {
                targetValue = MB_BlendAnimFrame(moby);
                animationStep = (motion->apexAnimationFrame - targetValue) / ratio;
                if (0.0f < animationStep)
                    Delt(moby->animIScale, animationStep, transStepScale * 0.1f);
            }
            break;
        }
        case MOTION_FALLING:
            targetValue = MB_BlendAnimFrame(moby);

            if (motion->landingAnimationFrame <= targetValue) {
                moby->animIScale = 0.0f;
            }

            else {
                float negativeHalfGravity = motion->gravity * -0.5f;
                landingTicks = 60.0f;
                hitCount =
                    MB_SolveQuad(negativeHalfGravity, motion->velocity.z - negativeHalfGravity,
                                 moby->pos.z - groundHeight, &largerRoot, &smallerRoot);
                if (hitCount > 0 && 0.0f < largerRoot && largerRoot < landingTicks)
                    landingTicks = largerRoot;
                if (landingTicks < 0.0001f)
                    landingTicks = 0.0001f;
                targetValue = MB_BlendAnimFrame(moby);
                animationStep = (motion->landingAnimationFrame - targetValue) / landingTicks;
                if (2.0f < animationStep)
                    animationStep = 2.0f;

                else if (animationStep < 0.0f)
                    animationStep = 0.0f;
                Delt(moby->animIScale, animationStep, transStepScale * 0.1f);
            }
            break;
        case MOTION_GROUNDED:
            moby->animIScale = 1.0f;
            break;
        }
    }

    if (moby->animationFlags & MOBY_ANIMATION_ENDED)
        resultFlags |= KICK_ANIMATION_ENDED;
    if (!(motion->flags & KICK_NO_TURN)) {
        OrganicDeltAngSpeed(moby, &motion->turnVelocity, motion->turnTarget, 0.02f, 0.3f,
                            motion->maxTurnStep);
    }

    hitIndex = 0;
    CopyVec4Inline(&sweepStart, &moby->pos);
    sweepStart.z = sweepStart.z + motion->collisionZOffset;
    FastVec3Add(&moby->pos, &moby->pos, &motion->velocity);
    CopyVec4Inline(&collisionProbe, &moby->pos);
    collisionProbe.z = collisionProbe.z + motion->collisionZOffset;
    FastVec3Add(&predictedPosition, &collisionProbe, &motion->velocity);
    hitCount = CollMobySphere(FastIntToFloat(motion->collisionRadius) * 0.0010742187732830644f,
                              &predictedPosition, 16, moby, 0);
    if (hitIndex < hitCount) {
        MobyInstance **hitMoby = HeroSphereQueryResults;
        int remainingHits = hitCount;
        do {
            if (MB_isCrate(*hitMoby) == 0) {
                if (motion->flags & KICK_STOP_AFTER_COLLISION) {
                    if (motion->phase == MOTION_GROUNDED)
                        resultFlags |= KICK_OUT_OF_BOUNDS;
                }
            }

            else {
                CollDamageMobyDirect_2(*hitMoby, moby, 0x10000, &moby->pos, &motion->velocity,
                                       1.0f);
            }
            hitMoby++;
        } while (--remainingHits != 0);
    }

    coordinateScale = 0.0009765625f;
    targetValue = FastVec3Length2(&motion->velocity);
    if ((float)motion->collisionRadius * coordinateScale < targetValue) {
        CollLine(&sweepStart, &collisionProbe, 36, moby, 0);
        CopyVec4Inline(&collisionProbe, &CollOutput.ip);
    }
    if (CollSphere(&collisionProbe, FastIntToFloat(motion->collisionRadius) * coordinateScale, 36,
                   moby) != 0) {
        resultFlags |= KICK_COLLISION;
        collisionPosition = &CollOutput.push;
        CopyVec4Inline(&moby->pos, collisionPosition);
        unitLength = 1.0f;
        moby->pos.z = moby->pos.z - motion->collisionZOffset;
        FastVec3Normalize(&surfaceNormal, collisionPosition + 1, unitLength);
        if (0.7070000171661377f <= surfaceNormal.z) {
            float normalSpeed = FastVec3Dot(&motion->velocity, &surfaceNormal);
            if (normalSpeed < 0.0f) {
                collisionResult =
                    (COLLOUTPUT *)((char *)collisionPosition - offsetof(COLLOUTPUT, push));
                if (collisionResult->pMoby == 0 || collisionResult->poly > 0) {
                    resultFlags |= KICK_GROUNDED;
                    motion->phase = MOTION_GROUNDED;
                }
                FastVec3Normalize(&normalResponse, &surfaceNormal, normalSpeed);
                FastSubVec3(&motion->velocity, &motion->velocity, &normalResponse);
                if (motion->phase == MOTION_GROUNDED) {
                    remainingSpeed = FastVec3Length2(&motion->velocity);
                    Delt(remainingSpeed, 0.0f, motion->gravity);
                    FastVec3Normalize(&motion->velocity, &motion->velocity, remainingSpeed);
                }
            }
        }

        else {
            float responseScale = FastVec3Dot(&motion->velocity, &surfaceNormal);
            if (responseScale < 0.0f) {
                responseScale = responseScale * -(motion->restitution + unitLength);
                FastVec3Normalize(&normalResponse, &surfaceNormal, responseScale);
                FastVec3Add(&motion->velocity, &motion->velocity, &normalResponse);
            }
        }
    }

    if (motion->phase == MOTION_RISING) {
        if (motion->velocity.z < 0.0f)
            motion->phase = MOTION_FALLING;
    }
    return resultFlags;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_MtxToQuat);

void FastMtx3x4Copy(Mtx4 *destination, Mtx4 *source);
void FastMtx4Copy(Mtx4 *destination, Mtx4 *source);
void MB_MtxToQuat(Vec4 *quaternion, Mtx4 *matrix);

void MB_TransformToQuat(Vec4 *quaternion, Mtx4 *transform)
{
    Mtx4 matrix;

    FastMtx3x4Copy(&matrix, transform);
    MB_MtxToQuat(quaternion, &matrix);
    FastMtx4Copy(transform, &matrix);
}

void MB_CopyHeroLights(MobyInstance *moby)
{
    moby->lights = Hero.moby->lights;
}

void MB_AxisAngleToQuat(Vec4 *quaternion, Vec4 *axis, float angle)
{
    float halfAngle = angle * 0.5f;

    FastVec3Scale(quaternion, axis, FastAngleCosF(halfAngle));
    quaternion->w = FastAngleSinF(halfAngle);
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_ClampVecToPlanes);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_GetOrientationMtx);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_UpdateLightsTransition);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_ColorDyingMoby);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_PathStepIndex);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_PathMoveDist);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", func_0027292C);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_DistIgnoreSmallZ);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_SegmentPushDist2D);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_SegmentPush);

float MB_DistIgnoreSmallZ(Vec4 *first, Vec4 *second, float tolerance);
int MB_PathMoveDist(MobyPath *path, Vec4 *position, int *segment, float *fraction, float distance, int wrap);
int MB_PathStepIndex(MobyPath *path, int index, int step, int wrap);
float MB_SegmentPush(Vec4 *nearest, Vec4 *point, Vec4 *start, Vec4 *end, float tolerance);

int MB_PathFollowToPos(MobyPath *path, Vec4 *point, Vec4 *nearest, int *segment, float *fraction, int wrap, float limit, float step, float tolerance)
{
    Vec4 points[4];
    int current = 0;
    int pointCount;
    int crossed;
    float currentFraction = 0.0f;
    float nextDist;
    float bestFraction;
    float dist;
    int bestSegment;
    float expandedLimit;
    int start;
    int end;
    float prevDist;

    CopyVec4Inline(&points[0], &path->points[0]);
    CopyVec4(&points[1], point);

    bestFraction = 0.0f;
    dist = MB_DistIgnoreSmallZ(&points[0], &points[1], tolerance);
    bestSegment = 0;

    if (path->pointCount == 0) {
        FastVecZero(nearest);
        return 0;
    }

    expandedLimit = step + limit;

    do {
        crossed = MB_PathMoveDist(path, &points[0], &current, &currentFraction, step, wrap);
        CopyVec4(&points[1], point);
        nextDist = MB_DistIgnoreSmallZ(&points[0], &points[1], tolerance);

        if (nextDist < dist) {
            dist = nextDist;
            bestSegment = current;
            bestFraction = currentFraction;
        }
    } while (!crossed);

    if (expandedLimit < dist)
        return 0;

    start = bestSegment;
    currentFraction = bestFraction;
    MB_PathMoveDist(path, &points[0], &start, &currentFraction, -step, wrap);

    currentFraction = bestFraction;
    end = bestSegment;
    MB_PathMoveDist(path, &points[0], &end, &currentFraction, step, wrap);

    end = MB_PathStepIndex(path, end, 1, wrap);
    current = start;
    dist = 1000000000.0f;

    do {
        CopyVec4(&points[1], &path->points[current]);
        CopyVec4(&points[2], point);
        nextDist = MB_DistIgnoreSmallZ(&points[1], &points[2], tolerance);

        if (nextDist < dist) {
            dist = nextDist;
            bestSegment = current;
        }

        if (current == end)
            break;

        current = (current + 1) % path->pointCount;
    } while (1);

    prevDist = 1000000000.0f;

    if (bestSegment > 0 || wrap) {
        float segmentDist;
        int previous;

        pointCount = path->pointCount;
        previous = pointCount - 1;
        previous = (bestSegment + previous) % pointCount;
        segmentDist = MB_SegmentPush(nearest, point, &path->points[previous], &path->points[bestSegment], tolerance);

        *segment = previous;
        CopyVec4(&points[1], &path->points[previous]);
        CopyVec4(&points[2], nearest);

        *fraction = MB_DistIgnoreSmallZ(&points[1], &points[2], 0.0f);
        prevDist = segmentDist;
    }

    pointCount = path->pointCount;

    if (bestSegment < pointCount - 1 || wrap) {
        nextDist = MB_SegmentPush(&points[1], point, &path->points[bestSegment], &path->points[(bestSegment + 1) % pointCount], tolerance);

        if (nextDist < prevDist) {
            CopyVec4Inline(nearest, &points[1]);
            *segment = bestSegment;

            CopyVec4(&points[2], &path->points[bestSegment]);
            CopyVec4(&points[3], nearest);

            *fraction = MB_DistIgnoreSmallZ(&points[2], &points[3], 0.0f);
        }
    }

    return 1;
}

// Retail leaves two words after the compiled tail of MB_PathFollowToPos.
TEXT_PADDING(0x27BD0080, 0);

float MB_WrapRot(float angle)
{
    float whole;
    float wrapped = angle + 3.14159274f;

    wrapped /= 6.2831855f;
    wrapped = FastFrac(&whole, wrapped);
    wrapped *= 6.2831855f;

    return wrapped - 3.14159274f;
}

int MB_isCrate(MobyInstance *moby);
enum { MOBY_CLASS_502 = 502 };

int MB_IsInvalidOrClass502(MobyInstance *moby)
{
    if (!moby)
        return 0;
    if (MB_isCrate(moby)) {
        short oClass = moby->oClass;
        return oClass == MOBY_CLASS_502;
    }

    return 1;
}

extern MobyInstance *MobyInstanceEnd;

enum { OCLASS_CRATE_FIRST = 500, OCLASS_CRATE_LAST = 540 };

int MB_isCrate(MobyInstance *moby)
{
    if (!moby)
        return 0;

    if (moby < MobyInstances || moby > MobyInstanceEnd)
        return 0;

    return (unsigned int)(moby->oClass - OCLASS_CRATE_FIRST)
        <= OCLASS_CRATE_LAST - OCLASS_CRATE_FIRST;
}

enum {
    OCLASS_DEVASTATOR_AMMO = 204,
    OCLASS_TESLA_CLAW_AMMO = 213,
    OCLASS_PYROCITOR_AMMO = 214,
    OCLASS_VISIBOMB_AMMO = 222,
    OCLASS_GLOVE_OF_DOOM_AMMO = 223,
    OCLASS_MINE_GLOVE_AMMO = 225,
    OCLASS_BOMB_GLOVE_AMMO = 226,
    OCLASS_BLASTER_AMMO = 1006
};

bool MB_isAmmo(MobyInstance *moby)
{
    short oClass = moby->oClass;

    if (oClass == OCLASS_BOMB_GLOVE_AMMO || oClass == OCLASS_DEVASTATOR_AMMO ||
        oClass == OCLASS_VISIBOMB_AMMO || oClass == OCLASS_BLASTER_AMMO ||
        oClass == OCLASS_PYROCITOR_AMMO || oClass == OCLASS_MINE_GLOVE_AMMO ||
        oClass == OCLASS_TESLA_CLAW_AMMO || oClass == OCLASS_GLOVE_OF_DOOM_AMMO)
        return true;

    return false;
}

void MB_genericExplosion(MobyInstance *owner, void *unused, Vec4 *position, float damageRadius,
                         float damageHp, int burstCount, int particlePairCount, int smokeCount,
                         float glowScale, float whiteGlowScale, float minGlowDistance,
                         float effectScale, int soundId, float flashRadius, int shakeCamera,
                         int debrisCount, int reductionLevel,
                         unsigned char colorSwap)
{
    Vec4 baseVelocity;
    Vec4 cameraDelta;
    float cameraDistance;
    float frameLoad;
    float speedReduction;
    int nearbyPairCount;
    int particleIndex;

    ClearVec4(&cameraDelta);
    cameraDelta.z = frameTime * 8.0f * effectScale;
    frameLoad = PerfLoad + FrameLoad;
    CopyVec4(&baseVelocity, &cameraDelta);
    if (reductionLevel == -1) {
        reductionLevel = 0;
        if (1.7f < frameLoad)
            reductionLevel = 1;
    }

    if (position == 0) {
        if (owner == 0)
            return;
        position = &owner->pos;
    }
    {
        if (damageRadius > 0.0f) {
            COLL_DAM_IN damage;
            SetCollDamIn(damage, owner, EXPLOSION_DAMAGE_FLAGS, damageHp);
            damage.damageClass = EXPLOSION_DAMAGE_CLASS;
            damage.damageStrength = EXPLOSION_DAMAGE_STRENGTH;
            damage.damageIndex = ((unsigned short)owner->oClass);
            CollMobySphere(damageRadius, position, 0x10, owner, &damage);
        }
    }

    for (particleIndex = 0; particleIndex < burstCount; particleIndex++) {
        {
            Vec4 burstVelocity;
            float elevation;
            float azimuth;
            elevation = MB_randRangeFloat(0.2617994f, 1.3962634f);
            azimuth = MB_randRot();
            MB_SphericalToVector(&burstVelocity,
                                 effectScale * (MB_randRangeFloat(7.0f, 10.5f) * frameTime),
                                 azimuth, elevation);
            burstVelocity.z += frameTime * 3.0f;
            cameraDistance = effectScale * 40000.0f;
            SpawnPart_015(position, &burstVelocity, ReorderRGB(0x4F007FFF, colorSwap),
                          ReorderRGB(0x1F00007F, colorSwap), cameraDistance,
                          MB_randRange(FastScaleRoundInt(0x3C), FastScaleRoundInt(0x78)) -
                              reductionLevel * 10,
                          1, -1, -1);
        }
    }

    FastSubVec3(&cameraDelta, &GameCamera.position, position);
    cameraDistance = FastVec3Length2(&cameraDelta);
    {
        if (debrisCount != 0) {
            Vec4 nearbyVelocity;
            Vec4 randomVelocity;
            int particleIndex;
            ClearVec4(&randomVelocity);
            randomVelocity.x = MB_randRangeFloat(-1.0f, 1.0f);
            randomVelocity.y = MB_randRangeFloat(-1.0f, 1.0f);
            randomVelocity.z = MB_randRangeFloat(-1.0f, 1.0f);
            CopyVec4(&nearbyVelocity, &randomVelocity);
            if (cameraDistance < 14.0f) {
                cameraDelta.z += cameraDistance * 0.5f;
                FastVec3Normalize(&nearbyVelocity, &nearbyVelocity,
                                  cameraDistance / 5.0f * frameTime);
                FastVec3Normalize(&cameraDelta, &cameraDelta,
                                  (cameraDistance + cameraDistance) * frameTime);
                FastVec3Add(&nearbyVelocity, &nearbyVelocity, &cameraDelta);
                FastVec4ScaleLength(&nearbyVelocity, &nearbyVelocity, frameTime * 10.0f);
                M122_SpawnDebris(position, &nearbyVelocity,
                                 MB_randRange(FastScaleRoundInt(0x3C), FastScaleRoundInt(0x5A)), 0,
                                 0);
            }
            debrisCount = debrisCount - 1;
            for (particleIndex = 0; particleIndex < debrisCount; particleIndex++) {
                float elevation;
                float azimuth;
                int variant;
                elevation = MB_randRangeFloat(0.2617994f, 1.3089969f);
                azimuth = MB_randRot();
                MB_SphericalToVector(&randomVelocity,
                                     effectScale * (MB_randRangeFloat(7.0f, 10.5f) * frameTime),
                                     azimuth, elevation);
                randomVelocity.z += frameTime + frameTime;
                variant = 0;
                if (particleIndex % 3 == 0)
                    variant = 1;
                M122_SpawnDebris(position, &randomVelocity,
                                 MB_randRange(FastScaleRoundInt(0x3C), FastScaleRoundInt(0x5A)),
                                 variant, 0);
            }
        }
    }

    if (cameraDistance < FastIntToFloat(particlePairCount) * 2.0f)
        nearbyPairCount = FastFloatToInt(cameraDistance) / 2;

    else
        nearbyPairCount = particlePairCount;

    speedReduction = 0.0f;
    if (cameraDistance < 7.0f)
        speedReduction = 7.0f - cameraDistance;
    {
        int particleIndex;
        for (particleIndex = 0; particleIndex < nearbyPairCount; particleIndex++) {
            ExplosionColorPalette startColors;
            ExplosionColorPalette endColors;
            float speed;
            speed = MB_randRangeFloat(8.0f, 10.0f) * frameTime;
            startColors = ExplosionStartColors;
            endColors = ExplosionEndColors;
            speed = speed - speedReduction * frameTime;
            speed = speed * effectScale;
            SpawnPart_011(
                position, &baseVelocity, ReorderRGB(startColors.colors[MB_randInt(6)], colorSwap),
                ReorderRGB(endColors.colors[MB_randInt(6)], colorSwap), effectScale * 400000.0f,
                MB_randRange(FastScaleRoundInt(0xF), FastScaleRoundInt(0x14)) - reductionLevel * 3,
                MB_randRange(FastScaleRoundInt(0x1E), FastScaleRoundInt(0x2D)) - reductionLevel * 5,
                0, 0, speed);
            SpawnPart_011(
                position, &baseVelocity, 0x7FFFFFFF, 0xFFFFFF, effectScale * 400000.0f,
                MB_randRange(FastScaleRoundInt(5), FastScaleRoundInt(0xA)) - reductionLevel * 2,
                MB_randRange(FastScaleRoundInt(0xF), FastScaleRoundInt(0x14)) - reductionLevel * 3,
                0, 0, speed * 0.5f);
        }
    }
    {
        int particleIndex;
        for (particleIndex = 0; particleIndex < smokeCount; particleIndex++) {
            ExplosionColorPalette startColors = ExplosionStartColors;
            ExplosionColorPalette endColors = ExplosionEndColors;
            Vec4 smokeVelocity;
            Vec4 randomVelocity;
            int startColor;
            int endColor;
            ClearVec4(&randomVelocity);
            randomVelocity.x = MB_randRangeFloat(-1.0f, 1.0f);
            randomVelocity.y = MB_randRangeFloat(-1.0f, 1.0f);
            randomVelocity.z = MB_randRangeFloat(-1.0f, 1.0f);
            CopyVec4(&smokeVelocity, &randomVelocity);
            FastVec3Normalize(&smokeVelocity, &smokeVelocity,
                              effectScale * (MB_randRangeFloat(0.0f, 3.0f) * frameTime));
            startColor = ReorderRGB(startColors.colors[MB_randInt(6)], colorSwap);
            endColor = ReorderRGB(endColors.colors[MB_randInt(6)], colorSwap);
            SpawnPart_008(position, &smokeVelocity, startColor, endColor,
                          MB_randRange(FastScaleRoundInt(0x1E), FastScaleRoundInt(0x2D)) -
                              reductionLevel * 5,
                          200000.0f);
        }
    }

    if (owner != 0 && glowScale > 0.0f) {
        int firstGlowRed = 150;
        int firstGlowBlue = 150;
        int laterGlowRed = 127;
        int laterGlowByte;
        if (colorSwap) {
            firstGlowRed = 70;
            firstGlowBlue = 70;
            laterGlowRed = 60;
        }
        laterGlowByte = laterGlowRed & 0xFF;
        if (FrameLoad < 0.95f && minGlowDistance < cameraDistance) {
            M112_SpawnGlow(owner, position, &baseVelocity, glowScale, FastScaleRoundInt(0x10),
                           firstGlowRed, 0x96, firstGlowBlue, 0x20);
            M112_SpawnGlow(owner, position, &baseVelocity, glowScale, FastScaleRoundInt(0x16),
                           laterGlowByte, 0x7F, 0x50, 0x20);
        }
        M112_SpawnGlow(owner, position, &baseVelocity, glowScale, FastScaleRoundInt(0x1E),
                       laterGlowByte, 0x7F, 0, 0x30);
    }

    if (owner != 0 && whiteGlowScale > 0.0f) {
        M112_SpawnGlow(owner, position, &baseVelocity, whiteGlowScale, FastScaleRoundInt(0x1B),
                       0xFF, 0xFF, 0xFF, 0x20);
    }
    {
        if (shakeCamera) {
            Vec4 sphere;
            CopyVec4(&sphere, position);
            sphere.w = 2.0f;
            if (FastBsphereCheck(&sphere, 10.0f) != -1) {
                GameCamera.shake.strength =
                    (cameraDistance < 20.0f) ? 0.4f - cameraDistance * 0.0175f : 0.050000012f;
                GameCamera.shake.time = FastScaleRoundInt(0x19);
            }
        }
    }

    if (owner != 0 && soundId != -1)
        sound_PlayMobySound(soundId, 0, owner);

    if (flashRadius != 0.0f) {
        if (reductionLevel == 0) {
            Vec4 sphere;
            CopyVec4Inline(&sphere, position);
            sphere.w = flashRadius;
            if (FastBsphereCheck(&sphere, 100.0f) != -1) {
                if (0.0f < flashRadius) {
                    DefaultExplosionFlash.radiusMax = flashRadius;
                    DefaultExplosionFlash.radiusMin = flashRadius;
                    DefaultExplosionFlash.radiusInitial = flashRadius;
                }

                else {
                    DefaultExplosionFlash.radiusMax = 15.0f;
                    DefaultExplosionFlash.radiusMin = 15.0f;
                    DefaultExplosionFlash.radiusInitial = 15.0f;
                }
                if (colorSwap)
                    M639_SpawnExplosionLight(&AlternateExplosionFlash, position, 0, 0);

                else
                    M639_SpawnExplosionLight(&DefaultExplosionFlash, position, 0, 0);
            }
        }
    }
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_SpawnExplosionSparks);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_SpawnExplosionSparks2);

float FastVec3Length2(Vec4 *vector);
void FastVec3Normalize(Vec4 *out, Vec4 *vector, float magnitude);

void ClampVec3Magnitude(Vec4 *vector, float maximum)
{
    if (FastVec3Length2(vector) > maximum)
        FastVec3Normalize(vector, vector, maximum);
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_AddMobyToDynamicGroup);

void MB_DeleteMobyFromDynamicGroup(MobyInstance *moby, short *group)
{
    int entry;

    for (entry = 1; entry <= group[0]; entry++) {
        if (&MobyInstances[group[entry]] == moby) {
            group[entry] = group[group[0]];
            group[0]--;
            return;
        }
    }
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_FindMobyByVarId);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", func_00274798);

void MB_randOffset(Vec4 *vector, float range)
{
    vector->x += MB_randRangeFloat(-range, range);
    vector->y += MB_randRangeFloat(-range, range);
    vector->z += MB_randRangeFloat(-range, range);
}

void FastVecMtx3Mult(Vec4 *out, Vec4 *vector, Mtx4 *matrix);

int MB_IsPntInCuboid(Vec4 *point, int index)
{
    if (index == -1)
        return 0;

    MobyVolume *volume = &CuboidVolumes[index];
    Vec4 offset;
    Vec4 local;

    FastSubVec3(&offset, point, &volume->origin);
    offset.w = 0.0f;
    FastVecMtx3Mult(&local, &offset, &volume->inverseTransform);

    if (local.x >= -1.0f && local.x <= 1.0f && local.y >= -1.0f && local.y <= 1.0f && local.z >= -1.0f && local.z <= 1.0f)
        return 1;

    return 0;
}


int MB_IsPntInCylinder(Vec4 *point, int index)
{
    if (index < 0)
        return 0;

    MobyVolume *volume = &CylinderVolumes[index];
    Vec4 offset;
    Vec4 local;

    FastSubVec3(&offset, point, &volume->origin);
    offset.w = 0.0f;
    FastVecMtx3Mult(&local, &offset, &volume->inverseTransform);

    if (FastVec3Length(&local.x) < 1.0f && local.z >= -1.0f && local.z <= 1.0f)
        return 1;

    return 0;
}

void FastVecMtx3Mult(Vec4 *out, Vec4 *vector, Mtx4 *matrix);

int MB_IsPntInSphere(Vec4 *point, int index)
{
    if (index < 0)
        return 0;

    MobyVolume *volume = &SphereVolumes[index];
    Vec4 offset;
    Vec4 local;

    FastSubVec3(&offset, point, &volume->origin);
    offset.w = 0.0f;
    FastVecMtx3Mult(&local, &offset, &volume->inverseTransform);

    if (FastVec3Length2(&local) < 1.0f)
        return 1;

    return 0;
}

void FastQuaternionMult(Vec4 *out, Vec4 *left, Vec4 *right);

void MB_QuatMultiply(Vec4 *out, Vec4 *vector, Vec4 *rotation)
{
    Vec4 inverse, point, rotated;

    FastVec3Scale(&inverse, rotation, -1.0f);
    inverse.w = rotation->w;
    CopyVec4Inline(&point, vector);
    point.w = 0.0f;

    FastQuaternionMult(&rotated, rotation, &point);
    FastQuaternionMult(out, &rotated, &inverse);
}

void MB_QuatMultiply(Vec4 *out, Vec4 *vector, Vec4 *rotation);

void MB_RotateQuatAxisAngle(Vec4 *out, Vec4 *vector, Vec4 *axis, float angle)
{
    Vec4 rotation;

    if (FastAbsF(angle) < 0.00001f) {
        CopyVec4Inline(out, vector);
        return;
    }

    FastVec3Normalize(&rotation, axis, 1.0f);
    MB_AxisAngleToQuat(&rotation, &rotation, angle);
    MB_QuatMultiply(out, vector, &rotation);
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", func_00274B70);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_getTarget);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_getTargetInArea);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", func_00275280);

MobyInstance *MB_GetPlatformParent(MobyInstance *moby)
{
    if (!moby)
        return 0;

    if (!(moby->modeBits & HAS_SPECIAL_VARS))
        return 0;

    return ((MobySpecialVars *)moby->pVar)->platformParent;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_TransformBetweenFrames);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_PlatformLocalToWorld);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_PlatformWorldToLocal);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_GetOrientation);

int FastBsphereCheck(Vec4 *sphere, float radius);

int MB_ScaledVecWrapper(Vec4 *vector, float radius)
{
    Vec4 scaled;

    FastScaleVec4(&scaled, vector, 1.0f / 1024.0f);
    return FastBsphereCheck(&scaled, radius);
}

void MB_UnlockLevel(int level)
{
    int unlockedCount = 0;
    int slot;

    if (g_SeenPlanets[level] == 0) {
        for (slot = 0; slot < 20; slot++) {
            if (g_SeenPlanets[slot] != 0)
                unlockedCount++;
        }

        g_SeenPlanets[level] = 1;
        GalacticMap[unlockedCount] = level;

        if (level != Level)
            MB_ToastMessageByIndex(level);
    }
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_UnlockItem);

void MB_DistributeBolts(MobyInstance *moby, int minimum, int maximum, unsigned int dropFlags,
                        int splineIndex)
{
    Vec4 baseVelocity, position, velocity, spread, landing, pathPoint, quarter;
    float firstRoot, secondRoot;
    int counted;
    int total, remaining, sum, rate, roots, ones;
    int upperTotal, upperFives, lowerTotal, upperTwenties, lowerTwenties, lowerFives, upperOnes,
        lowerFifties;
    int lowerOnes, upperFifties, twenties, fives, fifties;
    BoltSourceVars *sourceVars;
    float time;
    float gravity, rise, height, angle;

    fives = 0;
    twenties = 0;
    fifties = 0;
    FastVecZero(&baseVelocity);
    if (!(dropFlags & BOLT_DROP_UNCOUNTED)) {
        if (moby->levelFlagIdx != 0xFF && (unsigned)((unsigned short)moby->oClass - 0x1F4) >= 0x29)
            CountAdaptiveBolts = CheckpointLevelFlags[moby->levelFlagIdx] == 0xFF;
    }

    counted = 0;
    if (CountAdaptiveBolts) {
        if (!(dropFlags & BOLT_DROP_UNCOUNTED))
            counted = 1;
    }

    if (dropFlags == 0)
        return;
    if (minimum == 0 && maximum == 0)
        return;
    if (dropFlags & BOLT_DROP_INHERIT_VELOCITY) {
        sourceVars = (BoltSourceVars *)MB_GetPvarsIfMobyHasThem(moby);
        if (sourceVars)
            CopyVec4Inline(&baseVelocity, &sourceVars->velocity);
    }
    if (minimum <= 0)
        minimum = 1;

    total = MB_randInt(maximum - minimum + 1) + minimum;
    if (GoodiesMenuUnlocked || ChallengeMode)
        total <<= 1;
    if (total < 0x1F4) {
        if (counted && AdaptiveBoltFrames) {
            rate = (int)((float)FastScaleRoundInt(0x3C) * 60.0f) * AdaptiveBoltCount /
                   AdaptiveBoltFrames;
            if (GoodiesMenuUnlocked || ChallengeMode)
                rate /= 2;
            if (rate < 0x96) {
                if (rate < 0x5B) {
                    printf_stub(BoltScaleFiveMessage);
                    total *= 5;
                }

                else {
                    printf_stub(BoltIntegerScaleFormat, (0xBE - rate) / 20);
                    total *= (0xBE - rate) / 20;
                }
                if (GoodiesMenuUnlocked) {
                    if (total > 0x3E8)
                        total = 0x3E8;
                }

                else {
                    if (total > 0x1F4)
                        total = 0x1F4;
                }
            }

            else if (rate >= 0x12D) {
                if (rate >= 0x160) {
                    printf_stub(BoltFloatScaleFormat, (double)0.1f);
                    total /= 10;
                }

                else {
                    printf_stub(BoltFloatScaleFormat, FastIntToFloat(0x168 - rate) / 20.0f);
                    total *= (0x168 - rate) / 80;
                }
                if (total <= 0)
                    total = 1;
            }
        }
    }

    remaining = total;
    if (total >= 0x12C) {
        do {
            remaining -= 50;
            fifties++;
        } while (remaining >= 0x12C);
    }
    while (remaining >= 0xC8) {
        remaining -= 20;
        twenties++;
    }
    if (remaining >= 0x1E) {
        do {
            remaining -= 25;
            twenties++;
            fives++;
        } while (remaining >= 0x1E);
    }
    if (remaining >= 7) {
        do {
            remaining -= 5;
            fives++;
        } while (remaining >= 7);
    }

    ones = remaining;
    sum = fifties + twenties + fives + ones;
    if (sum >= 4 && (dropFlags & BOLT_DROP_THREE_COINS)) {
        lowerOnes = 0;
        lowerFives = 0;
        lowerTwenties = 0;
        lowerFifties = 3;
        upperOnes = 3;
        upperFives = 0;
        upperTwenties = 0;
        upperFifties = 0;
        lowerTotal = 0x96;
        upperTotal = 3;
        if (ones + fives + twenties + fifties >= 4) {
            if (total < lowerTotal) {
                do {
                    if (lowerFifties) {
                        lowerFifties--;
                        lowerTwenties++;
                    }

                    else if (lowerTwenties) {
                        lowerTwenties--;
                        lowerFives++;
                    }

                    else if (lowerFives) {
                        lowerFives--;
                        lowerOnes++;
                    }
                    lowerTotal =
                        lowerFifties * 50 + lowerTwenties * 20 + lowerFives * 5 + lowerOnes;
                } while (total < lowerTotal && lowerTotal >= 4);
            }
            upperTotal = 3;
            if (upperTotal < total) {
                do {
                    if (upperOnes) {
                        upperOnes--;
                        upperFives++;
                    }

                    else if (upperFives) {
                        upperFives--;
                        upperTwenties++;
                    }

                    else if (upperTwenties) {
                        upperTwenties--;
                        upperFifties++;
                    }
                    upperTotal =
                        upperFifties * 50 + upperTwenties * 20 + upperFives * 5 + upperOnes;
                } while (upperTotal < total && upperTotal < 0x96);
            }
        }
        if ((lowerTotal - total) < (total - upperTotal)) {
            ones = lowerOnes;
            fives = lowerFives;
            twenties = lowerTwenties;
            fifties = lowerFifties;
        }

        else {
            ones = upperOnes;
            fives = upperFives;
            twenties = upperTwenties;
            fifties = upperFifties;
        }
    }

    while (ones || fives || twenties || fifties) {
        CopyVec4Inline(&position, &moby->pos);
        position.z = position.z + 0.5f;
        angle = MB_randRot();
        velocity.x = FastAngleSinF(angle) * (MB_randRangeFloat(0.0f, 3.0f) * frameTime);
        velocity.y = FastAngleCosF(angle) * (MB_randRangeFloat(0.0f, 3.0f) * frameTime);
        velocity.z = 0.0f;
        velocity.z = MB_randRangeFloat(3.7f, 6.0f) * frameTime;
        spread.x = velocity.x;
        spread.y = velocity.y;
        spread.z = 0.0f;
        FastVec3Normalize(&spread, &spread, 0.5f);
        FastVec3Add(&position, &position, &spread);

        if (splineIndex >= 0) {
            gravity = frameTimeSq * 10.8f * -0.5f;
            rise = velocity.z - gravity;
            height = position.z - Splines[splineIndex]->points[0].z;
            time = 120.0f;
            roots = MB_SolveQuad(gravity, rise, height, &firstRoot, &secondRoot);
            if (1.0f <= (float)roots) {
                if (0.0f < firstRoot) {
                    if (firstRoot < time)
                        time = firstRoot;
                }
            }
            FastVec3Scale(&landing, &velocity, time);
            FastVec3Add(&landing, &landing, &moby->pos);
            roots = MB_SplineIntersect(splineIndex, &moby->pos, &landing, &pathPoint);
            FastSubVec3(&landing, &pathPoint, &position);
            landing.z = 0.0f;
            FastVec3Normalize(&quarter, &landing, 0.25f);
            FastSubVec3(&landing, &landing, &quarter);
            FastVec3Scale(&landing, &landing, 1.0f / time);
            velocity.x = landing.x;
            velocity.y = landing.y;
        }

        FastVec3Add(&velocity, &velocity, &baseVelocity);
        if (fifties) {
            SpawnBoltByValue(moby, &position, &velocity, dropFlags, 50, counted);
            fifties--;
        }

        else if (twenties) {
            SpawnBoltByValue(moby, &position, &velocity, dropFlags, 20, counted);
            twenties--;
        }

        else if (fives) {
            SpawnBoltByValue(moby, &position, &velocity, dropFlags, 5, counted);
            fives--;
        }

        else {
            SpawnBoltByValue(moby, &position, &velocity, dropFlags, 1, counted);
            ones--;
        }
    }
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", SetNtscPalTiming);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", func_00276378);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_compressVector);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_decompressVector);

float MB_RoundToDecimals(float value, int digits)
{
    int scale = 1;
    if (digits > 0) {
        do {
            scale *= 10;
        } while (--digits);
    }

    float factor = scale;
    value += 1.0f / (factor + factor);
    value *= factor;
    value = FastFloatToInt(value);
    return value / factor;
}

float MB_BlendAnimFrame(MobyInstance *moby);
float MB_RoundToDecimals(float value, int digits);

int MB_MayaFrameTrigger(MobyInstance *moby, float frame)
{
    float current = MB_BlendAnimFrame(moby);
    float offset = MB_RoundToDecimals(current - frame, 4);
    float step = MB_RoundToDecimals(moby->animIScale * moby->animSpeed, 4);

    if (frame <= current) {
        if (offset < step)
            return 1;
    }

    return 0;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_LineCrossesSpline);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_SplineIntersect);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_SplineCrossCheck);

enum { SPLINE_MASK_BITS = 32 };
extern MobyPath *Splines[];

unsigned int MB_SplineSegmentsReachable(int spline, unsigned int targets, unsigned int from)
{
    MobyPath *path = Splines[spline];
    int reached = from;
    for (int step = 0; step < SPLINE_MASK_BITS; ++step) {
        if (targets & reached)
            return targets & reached;

        int expanded = reached;
        for (int node = 0; node < SPLINE_MASK_BITS; ++node) {
            if ((reached >> node) & 1)
                expanded |= path->nodes[node].mask;
        }
        reached = expanded;
    }
    return 0;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", func_00276CB0);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_CollideSplineWall);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_SplineFindRouteNode);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_PathPosAtDist);

void FastEulerToMtx1(Mtx4 *out, Vec4 *angles);
void MB_GetOrientationMtx(Mtx4 *matrix, Vec4 *out);

void MB_RotateMoby(MobyInstance *moby, float xAngle, float yAngle, float zAngle)
{
    Vec4 angles;
    Mtx4 rotationDelta;
    Mtx4 orientation;

    angles.x = xAngle;
    angles.y = yAngle;
    angles.z = zAngle;
    FastEulerToMtx1(&rotationDelta, &angles);
    FastEulerToMtx1(&orientation, &moby->rotation);
    FastMtxTransform(&orientation, &orientation, &rotationDelta);
    MB_GetOrientationMtx(&orientation, &moby->rotation);
}

void CreateMotionBlur(MobyInstance *pMoby, MotionBlur *blur)
{
    if (blur->active == 0) {
        blur->pMoby = pMoby;
        blur->head = 0;
        blur->filled = 0;
        blur->count = 0;
        blur->active = 1;
    }
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", AddMotionBlurElem);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", UpdateMotionBlur);

void DeleteMotionBlur(MotionBlur *blur)
{
    int slot;

    if (blur->active != 0) {
        for (slot = 0; slot < blur->count; slot++) {
            if (blur->copies[slot] != 0) {
                DeleteMoby(blur->copies[slot]);
                blur->copies[slot] = 0;
            }
        }

        blur->active = 0;
    }
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", func_002777C0);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_TurnHeadJoint);

void MB_BobMotion(MobyInstance *moby, float *phase, float *offset, float height, float phaseStep)
{
    *phase = FastAddRots(*phase, phaseStep);
    moby->pos.z -= *offset;
    *offset = FastAngleCosF(*phase) * height;
    moby->pos.z += *offset;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_SwingMotion);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", func_00277B48);

void MB_SphericalToVector(Vec4 *out, float radius, float azimuth, float elevation)
{
    out->x = FastAngleSinF(azimuth) * radius * FastAngleSinF(elevation);
    out->y = FastAngleCosF(azimuth) * radius * FastAngleSinF(elevation);
    out->z = FastAngleCosF(elevation) * radius;
}

void FastVec3Add(Vec4 *out, Vec4 *first, Vec4 *second);

void MB_AddVectorSphere(Vec4 *out, Vec4 *origin, float radius, float azimuth, float elevation)
{
    Vec4 offset;

    MB_SphericalToVector(&offset, radius, azimuth, elevation);
    FastVec3Add(out, &offset, origin);
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_ToastMessageByIndex);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_PathEvalSpline);

int MB_HeroStandingOnMoby(MobyInstance *moby)
{
    if (Hero.stateType == HERO_STATE_TYPE_LEDGE || Hero.state == HERO_STATE_LEDGE_JUMP) {
        if (Hero.ledgeMoby == moby)
            return 1;
    }

    else if (Hero.framesNotGrounded == 0 && Hero.standingOnMoby == moby)
        return 1;

    return 0;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", func_00278010);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_SampleByteGrid);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_SpawnGridParticles);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_DrawGlowFX);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", func_002783A0);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_SetPointAheadOfMoby);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_SpawnBonePartFx);

void MB_ToggleManipulator(MobyInstance *moby, int animJoint, Manipulator *manipulator, float scale)
{
    if (CheatsActivated[CHEAT_BIG_HEAD] != 0) {
        if (manipulator->state == 0)
            AttachManipulator(moby, animJoint, manipulator);

        manipulator->scale.x = scale;
        manipulator->scale.y = scale;
        manipulator->scale.z = scale;
    }

    else if (manipulator->state != 0)
        DetachManipulator(moby, manipulator);
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", func_00278790);

enum { BOLTS_SPAWN = 2 };

extern Vec4 HeroPosition __attribute__((section(".data")));
float FastVec3DistLen(Vec4 *first, Vec4 *second);
void MB_DistributeBolts(MobyInstance *moby, int minimum, int maximum, unsigned int flags, int splineIndex);

void MB_DistributeBoltsNearHero(MobyInstance *moby)
{
    int flags = 0;
    if (FastVec3DistLen(&moby->pos, &HeroPosition) < 7.0f)
        flags = BOLTS_SPAWN;

    MB_DistributeBolts(moby, 4, 7, flags, -1);
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_SpawnSparksPair);

extern int ToastMsgTimer;
extern char ToastMsgBuff[];

void MB_ToastMessage(int message, int time)
{
    if (time == -1)
        time = FastScaleRoundInt(0xB4);

    strcpy(ToastMsgBuff, msg_string(message));
    ToastMsgTimer = time;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_ToastMessageFmt);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", func_00278AD0);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_SpawnDebrisMoby);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_SpawnReplacementMoby);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_HandleGameplayHud);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_ShowPersistentMessage);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_RequestHelpMessage);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", MB_ClearHelpMessage);

enum { GOLD_WEAPON_GOLD_BOLT_COST = 4 };

int MB_GetUnspentGoldBolts(void)
{
    int goldBolts = MB_CountGoldBolts();
    int balance = goldBolts - MB_CountGoldWeapons() * GOLD_WEAPON_GOLD_BOLT_COST;

    if (balance < 0)
        balance = 0;
    if (balance > 40)
        balance = 40;
    return balance;
}

int MB_CountGoldBolts(void)
{
    int count = 0;

    for (int level = 0; level < GOLD_BOLT_LEVEL_COUNT; ++level) {
        unsigned char *flag = GoldBoltFlags[level];
        for (int slot = GOLD_BOLT_SLOTS_PER_LEVEL - 1; slot >= 0; --slot) {
            if (*flag++)
                ++count;
        }
    }

    if (count < 0)
        count = 0;
    if (count > 40)
        count = 40;
    return count;
}

int MB_CountGoldWeapons(void)
{
    int count = 0;

    for (int index = 0; index < GOLD_WEAPON_FLAG_COUNT; ++index) {
        if (GoldWeaponFlags[index])
            ++count;
    }

    if (count < 0)
        count = 0;
    if (count > 10)
        count = 10;
    return count;
}

int MB_CountSkillPoints(void)
{
    int count = 0;

    for (int index = 0; index < SKILL_POINT_FLAG_COUNT; ++index) {
        if (SkillPointFlags[index])
            ++count;
    }

    if (count < 0)
        count = 0;
    if (count > 30)
        count = 30;
    return count;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mobyutil", SetupMobyFunctions);
