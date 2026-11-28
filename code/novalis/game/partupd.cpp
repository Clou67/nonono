#include "ambience.h"
#include "camera.h"
#include "common.h"
#include "eeregs.h"
#include "fastfunc.h"
#include "gameglobals.h"
#include "hero.h"
#include "libc.h"
#include "mathfunc_inline.h"
#include "mobyutil.h"
#include "part.h"
#include "vuchain.h"

extern float frameTimeSq __attribute__((section(".sdata")));

int CollSphere(Vec4 *position, int flags, MobyInstance *ignore, float radius);
int CollSphere(float radius, Vec4 *position, int flags, MobyInstance *ignore);
int CollLine(Vec4 *start, Vec4 *end, int flags, MobyInstance *ignore, COLL_DAM_IN *damage);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", ResetParticles);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_000);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_001);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_001);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_002);

void UpdatePart_002(PartInstance *particle)
{
    Part002 *motion = (Part002 *)particle->update;
    Vec4 positionStep;
    Vec4 initialMotion;
    Vec4 finalMotion;
    float ratio;

    if (worldUpdateTime & 1)
        particle->rot++;
    if (motion->shootTimer != 0) {
        *T0_COUNT = 0;
        MB_decompressVector(&positionStep, (unsigned int *)&motion->vel1);
        FastVec3Add(&particle->pos, &particle->pos, &positionStep);
        ratio = FastIntToFloat(particle->timer) / FastIntToFloat(motion->shootTimer);
        particle->rgba = FastTweenColor(motion->rgba1 & 0xFFFFFF, motion->rgba1, 1.0f - ratio);
        particle->scale = (float)(motion->initScale * 1000);
        if (FastDecTimer(particle->timer)) {
            motion->shootTimer = 0;
            particle->timer = motion->slowTimer;
        }
    }

    else if (motion->slowTimer != 0) {
        MB_decompressVector(&initialMotion, (unsigned int *)&motion->vel1);
        MB_decompressVector(&finalMotion, (unsigned int *)&motion->vel2);
        ratio = FastIntToFloat(particle->timer) / FastIntToFloat(motion->slowTimer);
        FastVecLerp(&positionStep, &finalMotion, &initialMotion, ratio);
        FastVec3Add(&particle->pos, &particle->pos, &positionStep);
        particle->scale = ((float)(motion->initScale - motion->finalScale) * ratio + (float)motion->finalScale) * 1000.0f;
        particle->rgba = FastTweenColor(motion->rgba2, motion->rgba1, ratio);
        if (FastDecTimer(particle->timer)) {
            motion->slowTimer = 0;
            particle->timer = motion->fadeTimer;
        }
    }

    else {
        int packedRgb;
        MB_decompressVector(&positionStep, (unsigned int *)&motion->vel2);
        FastVec3Add(&particle->pos, &particle->pos, &positionStep);
        packedRgb = motion->rgba2 & 0xFFFFFF;
        particle->rgba = FastTweenColor(packedRgb, motion->rgba2, FastIntToFloat(particle->timer) / FastIntToFloat(motion->fadeTimer));
        particle->scale = (float)(motion->finalScale * 1000);
        if (FastDecTimer(particle->timer))
            DeletePart(particle);
    }
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", func_0027E0D0);

void UpdatePart_003(PartInstance *particle)
{
    Part003 *motion = (Part003 *)particle->update;
    Vec4 positionScratch;
    float cameraDistance, cameraAngleDelta;
    int collisionCounter, remainingLifetime, alpha;
    AmbienceState *wind;
    Vec4 *cameraPosition;
    GAMECAMERA *camera;
    Vec4 *particlePosition;

    collisionCounter = motion->numFramesSinceColl;
    if (collisionCounter >= 3) {
        remainingLifetime = particle->timer;
        particlePosition = &particle->pos;
        if (remainingLifetime > FastScaleRoundInt(0x78) && CollSphere(7.99f, particlePosition, PART_DRIFT_COLLISION_FLAGS, 0)) {
            motion->state = 1;
            particle->timer = FastScaleRoundInt(0x78);
            motion->numFramesSinceColl = -1;
        }

        else
            motion->numFramesSinceColl = 0;
    }

    else {
        particlePosition = &particle->pos;
        // Negative counters disable wind motion without skipping the distance fade.
        if (collisionCounter < 0)
            goto updateDistanceFade;
        motion->numFramesSinceColl = collisionCounter + 1;
    }

    if (motion->numFramesSinceColl >= 0) {
        wind = &WindState;
        motion->vel.x = FastAngleSinF(wind->rotation) * wind->strength / 2.5f;
        motion->vel.y = FastAngleCosF(wind->rotation) * wind->strength / 2.5f;
        motion->vel.z = 0.0f;
        FastVec3Add(particlePosition, particlePosition, &motion->vel);
    }
updateDistanceFade:
    cameraPosition = &GameCamera.position;
    camera = &GameCamera;

    cameraDistance = FastVec3Dist(particlePosition, cameraPosition);
    cameraAngleDelta = FastSubRots(FastArcTan(particle->pos.x - camera->position.x, particle->pos.y - camera->position.y), camera->rot.z);

    if (FastAbsF(cameraAngleDelta) > 1.0471976f) {
        if ((motion->numFlipColls)++ >= 6) {
            *motion->existFlag = 0;
            DeletePart(particle);
            return;
        }
        positionScratch.x = FastAngleSinF(FastAddRots(camera->rot.z, cameraAngleDelta > 0.0f ? -1.0471976f : 1.0471976f)) * cameraDistance;
        positionScratch.y = FastAngleCosF(FastAddRots(camera->rot.z, cameraAngleDelta > 0.0f ? -1.0471976f : 1.0471976f)) * cameraDistance;
        positionScratch.z = particle->pos.z - camera->position.z;
        FastVec3Add(particlePosition, &positionScratch, cameraPosition);
        CopyVec4Inline(&positionScratch, particlePosition);
        positionScratch.z = positionScratch.z + 32.0f;
        if (CollLine(particlePosition, &positionScratch, PART_DRIFT_COLLISION_FLAGS, 0, 0)) {
            *motion->existFlag = 0;
            DeletePart(particle);
            return;
        }
    }

    if ((worldUpdateTime & 3) == 0)
        particle->rot++;

    remainingLifetime = particle->timer;
    if (FastScaleRoundInt(0x78) >= remainingLifetime)
        if (motion->state)
            alpha = particle->timer * 0x14 / FastScaleRoundInt(0x78);

        else
            alpha = (FastScaleRoundInt(0x78) - particle->timer) * 0x14 / FastScaleRoundInt(0x78);

    else
        alpha = 0x14;

    if (cameraDistance < 8.0f || cameraDistance > 96.0f) {
        *motion->existFlag = 0;
        DeletePart(particle);
        return;
    }
    if (cameraDistance < 16.0f)
        alpha = FastFloatToInt(FastIntToFloat(alpha) * (cameraDistance - 8.0f) * 0.125f);

    else if (cameraDistance > 80.0f)
        alpha = FastFloatToInt(FastIntToFloat(alpha) * (96.0f - cameraDistance) * 0.0625f);

    particle->rgba = (alpha << 24) | (particle->rgba & 0xFFFFFF);

    if (FastDecTimer(particle->timer)) {
        if (motion->state) {
            *motion->existFlag = 0;
            DeletePart(particle);
        }

        else {
            motion->state = 1;
            particle->timer = MB_randRange(FastScaleRoundInt(0x78) * 3, FastScaleRoundInt(0x78) * 9);
        }
    }
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_004);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_004);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_005);

void UpdatePart_005(PartInstance *part)
{
    Part005 *scale = (Part005 *)part->update;

    if (FastDecTimer(scale->fadeTimer)) {
        DeletePart(part);
        return;
    }

    part->scale += scale->scaleDelta;

    if (FastScaleRoundInt(6) > scale->fadeTimer)
        part->rgba = (part->rgba & 0xFFFFFF) | (((scale->fadeTimer * 0x7F) / FastScaleRoundInt(6)) << 24);
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_006);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_006);

void UpdatePart_007(PartInstance *part)
{
    Part007 *scale = (Part007 *)part->update;

    if (FastDecTimer(scale->fadeTimer)) {
        DeletePart(part);
        return;
    }

    part->scale += scale->scaleDelta;

    if (FastScaleRoundInt(6) > scale->fadeTimer)
        part->rgba = (part->rgba & 0xFFFFFF) | (((scale->fadeTimer * 0x7F) / FastScaleRoundInt(6)) << 24);
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_008);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_008);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", func_0027F4D0);

int PartGrayscaleFadeFrames = 600;
void UpdatePart_009(PartInstance *particle)
{
    Part009 *motion = (Part009 *)particle->update;
    int alpha;

    if (FastDecTimer(motion->timer)) {
        DeletePart(particle);
        return;
    }

    motion->curRot = FastAddRots(motion->curRot, motion->rotRange);
    particle->rot = FastFloatToInt(motion->curRot * 128.0f / 3.1415927f) - 0x80;
    if (FastScaleRoundInt(PartGrayscaleFadeFrames) * 3 / 4 < motion->timer) {
        int fadeDuration = FastScaleRoundInt(PartGrayscaleFadeFrames);
        alpha = motion->alpha * (fadeDuration - motion->timer) / (FastScaleRoundInt(PartGrayscaleFadeFrames) / 4);
    }

    else if (motion->timer < FastScaleRoundInt(PartGrayscaleFadeFrames) / 4)
        alpha = motion->alpha * motion->timer / (FastScaleRoundInt(PartGrayscaleFadeFrames) / 4);

    else
        alpha = motion->alpha;

    particle->rgba = (alpha << 24) + ((unsigned char)particle->gs_alpha == 0x48 ? 0x4F4F4F : 0x7F7F7F);
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_010);

void UpdatePart_010(PartInstance *particle)
{
    Part010 *motion = (Part010 *)particle->update;
    int blue, alpha;
    float timeScale;

    motion->alpha += transStepScale * -0.04f;
    if (motion->alpha <= 0.0f || FastDecTimer(particle->timer)) {
        DeletePart(particle);
        return;
    }

    timeScale = transStepScale;
    particle->scale += timeScale * 12000.0f;
    if (motion->b < 0.225f)
        motion->b += timeScale * 0.0484f;
    blue = FastFloatToInt(motion->b * 255.0f) & 0xFF;
    alpha = FastFloatToInt(motion->alpha * 255.0f);
    particle->rgba = *(unsigned short *)&particle->rgba | (blue << 16) | (alpha << 24);

    FastVec3Add(&particle->pos, &particle->pos, &motion->vel);
    FastVec3Scale(&motion->vel, &motion->vel, transStepScale * -0.100000024f + 1.0f);
    particle->rot--;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_011);

void UpdatePart_011(PartInstance *particle)
{
    Part011 *motion = (Part011 *)particle->update;
    particle->rot++;
    if (!(motion->stateFlags & PART_BRANCH_FADING)) {
        int childIndex;
        FastVec3Add(&particle->pos, &particle->pos, &motion->vel);
        if (motion->stateFlags & PART_BRANCH_GRAVITY)
            motion->vel.z += frameTimeSq * 9.8f;
        {
            float scaleFactor = 0.8f;
            if (motion->stateFlags & PART_BRANCH_BOOST)
                scaleFactor = 0.6f;
            FastVec3Scale(&motion->vel, &motion->vel, scaleFactor);
        }

        if (particle->timer == FastFloatToInt((float)motion->lifeSpan * 0.85f) && motion->generationCount < 2 && !(motion->stateFlags & PART_BRANCH_GRAVITY)) {
            for (childIndex = 4; childIndex >= 0; childIndex--) {
                int childLifetime = FastFloatToInt((float)motion->lifeSpan * MB_randRangeFloat(0.9f, 1.1f));
                int childTimer = motion->totalTime;
                float childVelocityScale = MB_randRangeFloat(0.85f, 1.0f);
                SpawnPart_011(&particle->pos, &motion->vel, motion->beginRGBA, motion->endRGBA, motion->maxScale, childLifetime, childTimer, motion->generationCount + 1, motion->stateFlags, motion->vel.w * childVelocityScale);
            }
        }

        if (!(motion->stateFlags & PART_BRANCH_GRAVITY)) {
            float sizeCurve = motion->maxScale;
            float totalFrames = FastIntToFloat(motion->lifeSpan);
            float linearCoeff = (totalFrames * 8.0f - totalFrames * 3.0f * sizeCurve) / (sizeCurve * 8.0f * sizeCurve + sizeCurve * 8.0f);
            float quadraticCoeff = (totalFrames * 3.0f + linearCoeff * 8.0f * sizeCurve) / (sizeCurve * -8.0f);
            float remainingFrames = FastIntToFloat(particle->timer);
            float scaleFactor = FastFSqrt(linearCoeff * linearCoeff - quadraticCoeff * 4.0f * (totalFrames - remainingFrames));
            float rootPlus = (-linearCoeff + scaleFactor) / (quadraticCoeff + quadraticCoeff);
            float rootMinus = (-linearCoeff - scaleFactor) / (quadraticCoeff + quadraticCoeff);
            float referenceDistance;
            if (rootMinus < rootPlus)
                particle->scale = rootPlus;

            else
                particle->scale = rootMinus;
            referenceDistance = FastVec3Dist(&particle->pos, &GameCamera.position);
            if (referenceDistance < 10.0f)
                particle->scale *= referenceDistance * 0.075f + 0.25f;
        }

        if (motion->stateFlags & PART_BRANCH_BOOST)
            particle->rgba = FastTweenColor(motion->beginRGBA, 0xFFFFFFF, (float)particle->timer / (float)motion->lifeSpan);

        else
            particle->rgba = FastTweenColor(motion->endRGBA, motion->beginRGBA, (float)particle->timer / (float)motion->lifeSpan);

        FastDecTimer(motion->totalTime);
        if (FastDecTimer(particle->timer)) {
            if (motion->stateFlags & PART_BRANCH_BOOST) {
                int tripledLifetime = motion->lifeSpan * 3;
                particle->timer = tripledLifetime;
                motion->lifeSpan = tripledLifetime;
                motion->stateFlags = (motion->stateFlags & ~PART_BRANCH_BOOST) | PART_BRANCH_GRAVITY;
                FastVec3Normalize(&motion->vel, &motion->vel, motion->vel.w * MB_randRangeFloat(1.6f, 2.0f));
            }

            else {
                int fadeLifetime;
                motion->beginRGBA = motion->endRGBA;
                motion->endRGBA = ((unsigned char)particle->gs_alpha == 0x48) ? 0 : 0xF2F3F3F;
                motion->stateFlags |= PART_BRANCH_FADING;
                fadeLifetime = MB_randRange(motion->lifeSpan * 2, motion->lifeSpan * 3);
                if (motion->stateFlags & PART_BRANCH_LONG_FADE)
                    fadeLifetime *= 5;
                motion->lifeSpan = fadeLifetime;
                particle->timer = (unsigned char)fadeLifetime;
            }
        }
    }

    else {
        int fadeDuration = FastFloatToInt((float)motion->lifeSpan * 0.75f) + 1;
        int blendDuration = FastFloatToInt((float)motion->lifeSpan * 0.25f) + 1;
        int timer;
        motion->vel.z += frameTimeSq * 3.0f;
        FastVec3Add(&particle->pos, &particle->pos, &motion->vel);
        FastVec3Scale(&motion->vel, &motion->vel, 0.98f);
        timer = particle->timer;
        if (fadeDuration < timer)
            particle->rgba = FastTweenColor(motion->endRGBA, motion->beginRGBA, (float)(timer - fadeDuration) / (float)blendDuration);

        else if ((unsigned char)particle->gs_alpha == 0x48)
            particle->timer = 0;

        else
            particle->rgba = (particle->rgba & 0xFFFFFF) | ((timer * 15 / fadeDuration) << 24);

        if (FrameLoad > 1.0f)
            FastDecTimer(particle->timer);
        if (FastDecTimer(particle->timer))
            DeletePart(particle);
    }
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_012);

int PartSpinInitialColorSource = 0x20202080;
int PartSpinInitialColorTarget = 0x20208080;
int PartSpinFinalColorSource = 0x1820c0c0;
int PartSpinFinalColorTarget = 0x182080c0;
float PartSpinInitialScale = 0.25f;
float PartSpinFinalScale = 1.25f;
int PartSpinMinLifetime = 0x14;
int PartSpinMaxLifetime = 0x1e;
int PartSpinAlternateInitialColorSource = 0x8002040;
int PartSpinAlternateInitialColorTarget = 0x8004040;
int PartSpinAlternateFinalColorSource = 0x10004040;
int PartSpinAlternateFinalColorTarget = 0x10002040;
float PartSpinAlternateInitialScale = 1.0f;
float PartSpinAlternateFinalScale = 3.0f;
int PartSpinAlternateMinLifetime = 0x19;
int PartSpinAlternateMaxLifetime = 0x23;
float PartSpinDeceleration = 48.0f;
float PartSpinVerticalSpeed = 1.0f;
// Unreferenced retail literal-pool words retained between the tuning values.
extern const unsigned int PartSpinLiteral00 __attribute__((section(".sdata"))) = 0x80000000;
float PartBeamFirstOffsetScale = 0.93f;
float PartBeamSecondOffsetScale = 0.929f;
extern const unsigned int PartSpinLiteral03 __attribute__((section(".sdata"))) = 0x0000005A;
extern const unsigned int PartSpinLiteral04 __attribute__((section(".sdata"))) = 0x4808B800;
extern const unsigned int PartSpinLiteral05 __attribute__((section(".sdata"))) = 0x20FFFF20;
extern const unsigned int PartSpinLiteral06 __attribute__((section(".sdata"))) = 0x00000000;
extern const unsigned int PartSpinLiteral07 __attribute__((section(".sdata"))) = 0x00000001;
extern const unsigned int PartSpinLiteral08 __attribute__((section(".sdata"))) = 0x3E800000;
extern const unsigned int PartSpinLiteral09 __attribute__((section(".sdata"))) = 0x3E800000;
extern const unsigned int PartSpinLiteral10 __attribute__((section(".sdata"))) = 0x3F000000;
extern const unsigned int PartSpinLiteral11 __attribute__((section(".sdata"))) = 0x3F000000;
extern const unsigned int PartSpinLiteral12 __attribute__((section(".sdata"))) = 0x3F400000;
extern const unsigned int PartSpinLiteral13 __attribute__((section(".sdata"))) = 0x0000000A;

void UpdatePart_012(PartInstance *particle)
{
    Part012 *motion = (Part012 *)particle->update;
    float negativeSpeed;
    float endpointScale = 1.0f;
    float ratio;

    particle->rot += (unsigned char)motion->rotSpeed;
    if ((unsigned char)motion->flags & PART_SPIN_SIZE_BOOST)
        endpointScale = FastIntToFloat(PartSpinSizeBoost[0]) * 0.5f + endpointScale;
    FastVec3Add(&particle->pos, &particle->pos, &motion->vel);
    negativeSpeed = -FastVec3Length2(&motion->vel);
    OrganicDelt(&motion->dist, &negativeSpeed, 0.0f, 0.0f, PartSpinDeceleration * frameTimeSq, negativeSpeed);
    FastVec3Normalize(&motion->vel, &motion->vel, -negativeSpeed);
    particle->pos.z += PartSpinVerticalSpeed * frameTime;
    ratio = FastIntToFloat(particle->timer) / FastIntToFloat((unsigned char)motion->lifetime);
    if ((unsigned char)motion->flags & PART_SPIN_ALTERNATE_SCALE) {
        float finalScale = PartSpinAlternateFinalScale * endpointScale;
        particle->scale = ((PartSpinAlternateInitialScale - finalScale) * ratio + finalScale) * 210000.0f;
    }

    else {
        float finalScale = PartSpinFinalScale * endpointScale;
        particle->scale = ((PartSpinInitialScale - finalScale) * ratio + finalScale) * 210000.0f;
    }
    particle->rgba = FastTweenColor(motion->finalRGBA, motion->initRGBA, ratio);
    if (particle->timer < FastScaleRoundInt(15)) {
        float remaining = FastIntToFloat(particle->timer);
        float fadeRatio = remaining / FastIntToFloat(FastScaleRoundInt(10));
        particle->rgba = FastTweenColor(particle->rgba & 0xFFFFFF, particle->rgba, fadeRatio);
    }
    if (particle->pos.x < 2.0f || particle->pos.x > 1021.0f || particle->pos.y < 2.0f || particle->pos.y > 1021.0f || particle->pos.z < 2.0f || particle->pos.z > 1021.0f || FastDecTimer(particle->timer) != 0)
        DeletePart(particle);

    else if (motion->dist < 0.01f)
        particle->timer--;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_013);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_013);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_014);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_014);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_015);

void UpdatePart_015(PartInstance *particle)
{
    Vec4 updatedPosition, spawnVelocity, randomDirection;
    Part015 *motion = (Part015 *)particle->update;
    Vec4 *position;
    float lifetimeSize, lifetimeOrSpeed;

    if (FastDecTimer(particle->timer)) {
        DeletePart(particle);
        return;
    }

    position = &particle->pos;
    lifetimeSize = FastIntToFloat(particle->timer);
    lifetimeOrSpeed = FastIntToFloat(motion->lifeSpan);
    lifetimeSize *= motion->maxScale;
    lifetimeSize /= lifetimeOrSpeed;
    particle->scale = lifetimeSize;
    lifetimeSize = FastIntToFloat(particle->timer);
    particle->rgba = TweenColor(motion->endRGBA, motion->beginRGBA, lifetimeSize / FastIntToFloat(motion->lifeSpan));
    FastVec3Add(position, position, &motion->vel);
    motion->vel.z -= frameTimeSq * 14.6f;
    CopyVec4Inline(&updatedPosition, position);

    if (motion->master && (worldUpdateTime & 1)) {
        ClearVec4(&randomDirection);
        randomDirection.x = MB_randRangeFloat(-1.0f, 1.0f);
        randomDirection.y = MB_randRangeFloat(-1.0f, 1.0f);
        randomDirection.z = MB_randRangeFloat(-1.0f, 1.0f);
        CopyVec4(&spawnVelocity, &randomDirection);
        lifetimeOrSpeed = FastVec3Length2(&motion->vel);
        FastVec3Normalize(&spawnVelocity, &spawnVelocity, lifetimeOrSpeed * MB_randRangeFloat(0.15f, 0.25f));
        FastVec3Add(&spawnVelocity, &spawnVelocity, &motion->vel);
        FastVec3Scale(&spawnVelocity, &spawnVelocity, MB_randRangeFloat(0.75f, 0.95f));
        SpawnPart_015(position, &spawnVelocity, particle->rgba, motion->endRGBA, particle->scale, FastScaleRoundInt(MB_randRange(15, 30)), 0, (unsigned char)particle->tex, (unsigned char)particle->gs_alpha);
    }

    else
        FastVec3Scale(&motion->vel, &motion->vel, 0.96f);
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_016);

void UpdatePart_016(PartInstance *particle)
{
    Vec4 savedPosition;
    float gravity[4] = {frameTimeSq * 4.8f, frameTimeSq * 24.5f, frameTimeSq * 9.8f, -(frameTimeSq * 0.24f)};
    Part016 *motion = (Part016 *)particle->update;
    int alpha, spawnLifetime, kind;
    float distanceOrSpawnScale;

    if (motion->partClass == PART_DEBRIS_UPWARD_ACCELERATING && FrameLoad > 0.95f)
        FastDecTimer(particle->timer);
    if (FastDecTimer(particle->timer)) {
        DeletePart(particle);
        return;
    }

    {
        float remaining_lifetime_float = FastIntToFloat(particle->timer);
        particle->rgba = TweenColor(motion->endRGBA, motion->beginRGBA, remaining_lifetime_float / FastIntToFloat(motion->lifeSpan));
        alpha = particle->rgba >> 24;
        distanceOrSpawnScale = FastVec3Dist(&particle->pos, &GameCamera.position);
        if (particle->timer < FastScaleRoundInt(6))
            alpha = alpha * particle->timer / FastScaleRoundInt(6);
        if (distanceOrSpawnScale < 4.0f) {

            DeletePart(particle);
            return;
        }
        if (distanceOrSpawnScale < 8.0f)
            alpha = FastFloatToInt(FastIntToFloat(alpha) * (distanceOrSpawnScale - 4.0f) * 0.25f);

        particle->rgba = (alpha << 24) | (particle->rgba & 0xFFFFFF);

        FastVec3Add(&particle->pos, &particle->pos, &motion->vel);
        kind = motion->partClass;
        motion->vel.z -= gravity[kind];
        CopyVec4Inline(&savedPosition, &particle->pos);

        if (particle->pos.z < motion->vel.w) {
            if (kind == PART_DEBRIS_SPAWN_ON_LANDING) {
                int spawnStartColor, spawnEndColor, minSpawnLifetime;
                spawnStartColor = TweenColor(0x7F000000, 0x7F182030, MB_randRangeFloat(0.25f, 1.0f));
                spawnEndColor = TweenColor(0, 0x5F5F5F, MB_randRangeFloat(0.5f, 1.0f));

                motion->vel.z = 0;
                distanceOrSpawnScale = MB_randRangeFloat(200000.0f, 300000.0f);
                minSpawnLifetime = FastScaleRoundInt(0x5A);
                spawnLifetime = MB_randRange(minSpawnLifetime, FastScaleRoundInt(0x96));
                SpawnPart_016(&particle->pos, &motion->vel, spawnStartColor, spawnEndColor, distanceOrSpawnScale, spawnLifetime, PART_DEBRIS_UPWARD_ACCELERATING);
            }

            DeletePart(particle);
        }

        else
            particle->rot++;
    }
}

void UpdatePart_017(PartInstance *part)
{
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_018);

void UpdatePart_018(PartInstance *particle)
{
    Part018 *motion = (Part018 *)particle->update;

    motion->alpha += transStepScale * 0.013f * motion->asign;
    if (motion->alpha <= 0.0f || FastDecTimer(particle->timer)) {
        DeletePart(particle);
        return;
    }
    if (0.22f <= motion->alpha) {
        motion->asign = -motion->asign;
        motion->alpha = motion->alpha + transStepScale * 0.013f * motion->asign;
    }

    particle->scale += transStepScale * 8190.0f;
    particle->rgba = (particle->rgba & 0xFFFFFF) | (FastFloatToInt(motion->alpha * 255.0f) << 24);
    motion->rot += transStepScale * 0.012f;
    if (1.0f < motion->rot)
        motion->rot -= 1.0f;

    particle->rot = (int)(motion->rot * 255.0f);
    particle->pos.z -= 0.02f;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_019);

void FastVec3Add(Vec4 *out, Vec4 *first, Vec4 *second);
int FastDecTimer(short &timer);
void DeletePart(PartInstance *part);

void UpdatePart_019(PartInstance *part)
{
    FastVec3Add(&part->pos, &part->pos, &((PartLineMotion *)part->update)->velocity);
    FastVec3Add(&((PartLineMotion *)part->update)->origin, &((PartLineMotion *)part->update)->origin, &((PartLineMotion *)part->update)->velocity);

    part->rgba -= 6 << 24;
    *(int *)&part->scale = part->rgba;
    if (part->rgba < 0)
        DeletePart(part);
}

void UpdatePart_020(PartInstance *particle)
{
    Part020 *motion = (Part020 *)particle->update;
    Vec4 targetPosition, offset, rotatedOffset;
    Mtx4 basis;

    if (motion->offset != 0.0f) {
        float zero = 0.0f;
        CopyVec4(&basis.v0, &motion->rotmatrix->v0);
        CopyVec4(&basis.v1, &motion->rotmatrix->v1);
        CopyVec4(&basis.v2, &motion->rotmatrix->v2);
        offset.y = FastAngleCosF(motion->angle) * motion->offset;
        offset.z = FastAngleSinF(motion->angle) * motion->offset;
        offset.x = zero;
        offset.w = zero;
        FastTransformVec4(&rotatedOffset, &offset, &basis);
        FastSubVec3(&particle->pos, &particle->pos, &rotatedOffset);

        motion->vel += transStepScale * 0.06001f;
        MB_GetBonePos(motion->target, 0, &targetPosition);
        FastSubVec3(&offset, &targetPosition, &particle->pos);
        FastVec3Normalize(&offset, &offset, motion->vel);
        FastVec3Add(&particle->pos, &particle->pos, &offset);

        motion->angle = FastAddRots(motion->angle, transStepScale * 0.5235988f);
        motion->offset *= transStepScale * -0.10000002384185791f + 1.0f;
        offset.y = FastAngleCosF(motion->angle) * motion->offset;
        offset.z = FastAngleSinF(motion->angle) * motion->offset;
        offset.x = zero;
        offset.w = zero;
        FastTransformVec4(&rotatedOffset, &offset, &basis);
        FastVec3Add(&particle->pos, &particle->pos, &rotatedOffset);
        if (zero < MB_GetNormalizedMtxElem(&targetPosition, &motion->target->transform, &particle->pos, 1)) {
            DeletePart(particle);
            return;
        }
    }

    motion->alpha += transStepScale * 0.011f * motion->asign;
    if (motion->alpha <= 0.0f || FastDecTimer(particle->timer)) {
        DeletePart(particle);
        return;
    }

    if (1.0f <= motion->alpha) {
        motion->asign = -motion->asign;
        motion->alpha += transStepScale * 0.011f * motion->asign;
    }

    particle->scale += transStepScale * -2940.0f;
    particle->rgba = (particle->rgba & 0xFFFFFF) | (FastFloatToInt(motion->alpha * 255.0f) << 24);

    motion->rot += transStepScale * 0.006f;
    if (1.0f < motion->rot)
        motion->rot -= 1.0f;

    particle->rot = (int)(motion->rot * 255.0f);
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_021);

void UpdatePart_021(PartInstance *particle)
{
    Vec4 updatedPosition, spawnVelocity, randomDirection;
    Part021 *motion = (Part021 *)particle->update;
    Vec4 *position;
    float lifetimeSize, lifetimeOrSpeed;

    if (FastDecTimer(particle->timer)) {
        DeletePart(particle);
        return;
    }

    position = &particle->pos;
    lifetimeSize = FastIntToFloat(particle->timer);
    lifetimeOrSpeed = FastIntToFloat(motion->lifeSpan);
    lifetimeSize *= motion->maxScale;
    lifetimeSize /= lifetimeOrSpeed;
    particle->scale = lifetimeSize;
    lifetimeSize = FastIntToFloat(particle->timer);
    particle->rgba = TweenColor(motion->endRGBA, motion->beginRGBA, lifetimeSize / FastIntToFloat(motion->lifeSpan));
    FastVec3Add(position, position, &motion->vel);
    motion->vel.z -= transStepScaleSq * 0.001f;
    CopyVec4Inline(&updatedPosition, position);

    if (motion->master && (worldUpdateTime & 1)) {
        ClearVec4(&randomDirection);
        randomDirection.x = MB_randRangeFloat(-1.0f, 1.0f);
        randomDirection.y = MB_randRangeFloat(-1.0f, 1.0f);
        randomDirection.z = MB_randRangeFloat(-1.0f, 1.0f);
        CopyVec4(&spawnVelocity, &randomDirection);
        lifetimeOrSpeed = FastVec3Length2(&motion->vel);
        FastVec3Normalize(&spawnVelocity, &spawnVelocity, lifetimeOrSpeed * MB_randRangeFloat(0.21f, 0.25f));
        FastVec3Add(&spawnVelocity, &spawnVelocity, &motion->vel);
        FastVec3Scale(&spawnVelocity, &spawnVelocity, MB_randRangeFloat(0.75f, 0.95f));
        SpawnPart_021(position, &spawnVelocity, particle->rgba, motion->endRGBA, particle->scale, FastScaleRoundInt(MB_randRange(15, 20)), 0);
    }

    else
        FastVec3Scale(&motion->vel, &motion->vel, 0.96f);
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_022);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_023);

void UpdatePart_023(PartInstance *particle)
{
    Part023 *motion = (Part023 *)particle->update;
    float alphaFade;
    int phaseDuration;
    int alpha;

    particle->rot += (unsigned char)motion->rotDir;
    FastVec3Add(&particle->pos, &particle->pos, &motion->vel);
    particle->scale *= (motion->scale - 1.0f) * transStepScale + 1.0f;
    if (motion->state == PART_PULSE_FADE_IN) {
        if (FastDecTimer(particle->timer)) {
            motion->state = PART_PULSE_FADE_OUT;
            particle->timer = FastScaleRoundInt(20);
            particle->rgba = motion->rgb | 0x7F000000;
        }

        else {
            phaseDuration = FastScaleRoundInt(10);
            alpha = FastFloatToInt((float)(phaseDuration - particle->timer) * (96.0f / (float)FastScaleRoundInt(10)));
            particle->rgba = ((alpha + 0x20) << 24) | motion->rgb;
        }
    }

    else if (motion->state == PART_PULSE_CUSTOM_FADE_OUT) {
        if (FastDecTimer(particle->timer))
            goto kill;
        alphaFade = FastIntToFloat(motion->initTimer);
        alpha = FastFloatToInt((float)motion->initAlpha * ((float)particle->timer / alphaFade) + 0.0f);
        particle->rgba = (alpha << 24) | (motion->rgb & 0xFFFFFF);
    }

    else if (motion->state == PART_PULSE_CUSTOM_FADE_IN) {
        FastDecTimer(particle->timer);
        alphaFade = FastIntToFloat(motion->initTimer - particle->timer);
        alphaFade = alphaFade / FastIntToFloat(FastScaleRoundInt(30));
        if (1.0f < alphaFade)
            alphaFade = 1.0f;
        alpha = FastFloatToInt((float)motion->initAlpha * alphaFade + 0.0f);
        particle->rgba = (alpha << 24) | (motion->rgb & 0xFFFFFF);
        if (motion->initTimer - particle->timer >= FastScaleRoundInt(30)) {
            phaseDuration = FastScaleRoundInt(30);
            motion->state = PART_PULSE_CUSTOM_FADE_OUT;
            motion->initTimer -= phaseDuration;
        }
    }

    else {
        if (FastDecTimer(particle->timer)) {
        kill:
            DeletePart(particle);
            return;
        }
        alpha = FastFloatToInt((float)particle->timer * (127.0f / (float)FastScaleRoundInt(20)));
        particle->rgba = (alpha << 24) | motion->rgb;
    }
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_024);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_025);

void UpdatePart_025(PartInstance *particle)
{
    Vec4 nextPosition;
    Part025 *motion;
    float red, green, blue, timeScale;
    int reverseColors;
    if (particle == 0)
        return;

    motion = (Part025 *)particle->update;
    red = motion->r;
    reverseColors = 0;
    green = motion->g;
    blue = motion->b;
    if (red < 0.0f || green < 0.0f || blue < 0.0f) {
        red = -red;
        reverseColors = 1;
        green = -green;
        blue = -blue;
    }

    motion->alpha += transStepScale * 0.0f;
    particle->scale += transStepScale * -100.0f;
    FastVec3Add(&nextPosition, &particle->pos, &motion->vel);
    if (motion->vel.x != 0.0f || motion->vel.y != 0.0f || motion->vel.z != 0.0f) {
        if (CollLine(&particle->pos, &nextPosition, PART_COLOR_DECAY_COLLISION_FLAGS, Hero.moby, 0)) {
            CopyVec4(&particle->pos, &MemSlots.collisionPoint);
            FastVecZero(&motion->vel);
            particle->scale += particle->scale;
        }

        else {
            CopyVec4(&particle->pos, &nextPosition);
            if (motion->vel.w != 0.0f)
                motion->vel.z += motion->vel.w;

            else
                motion->vel.z += transStepScaleSq * -0.0063f;
        }
    }

    if (motion->alpha <= 0.0f || FastDecTimer(particle->timer) || particle->scale < 0.0f || nextPosition.x < 0.01f || nextPosition.y < 0.01f || nextPosition.z < 0.01f) {
        DeletePart(particle);
        return;
    }

    if (!reverseColors) {
        red += transStepScale * -0.01f;
        timeScale = transStepScale;
        if (red < 0.0f)
            red = 0.0f;
        green += timeScale * -0.03001f;
        if (green < 0.0f)
            green = 0.0f;
    }

    else {
        green += transStepScale * -0.01f;
        timeScale = transStepScale;
        if (green < 0.0f)
            green = 0.0f;
        red += timeScale * -0.03001f;
        if (red < 0.0f)
            red = 0.0f;
    }

    blue += timeScale * -0.05f;
    if (blue < 0.0f)
        blue = 0.0f;

    motion->alpha += timeScale * 0.0f;
    if (motion->alpha < 0.0f)
        motion->alpha = 0.0f;

    particle->rgba = Float_To_RGBA(red, green, blue, motion->alpha);

    if (reverseColors > 0) {
        motion->r = -red;
        motion->g = -green;
        motion->b = -blue;
    }

    else {
        motion->r = red;
        motion->g = green;
        motion->b = blue;
    }

    particle->rot--;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_026);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_026);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_027);

void UpdatePart_027(PartInstance *part)
{
    Part027 *fade = (Part027 *)part->update;

    FastVec3Add(&part->pos, &part->pos, &fade->vel);

    part->rgba = (part->rgba & 0xFFFFFF) + (((fade->alpha * fade->timer) / fade->lifeSpan) << 24);

    if (FastDecTimer(fade->timer) != 0)
        DeletePart(part);
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_028);

void UpdatePart_028(PartInstance *particle)
{
    Part028 *motion = (Part028 *)particle->update;
    float direction = motion->asign;
    float alphaBeforeReversal;
    float timeScale;

    if (0.0f < direction)
        motion->alpha += transStepScale * 0.007f * direction;

    else if (0.03f < motion->alpha)
        motion->alpha = motion->alpha + transStepScale * 0.007f * direction;

    else {
        timeScale = transStepScale;
        motion->alpha = motion->alpha + timeScale * 0.007f * direction * 0.2f;
        particle->scale += timeScale * 5460.0f;
    }

    if (motion->alpha <= 0.0244f || FastDecTimer(particle->timer) != 0) {
        DeletePart(particle);
        return;
    }

    alphaBeforeReversal = motion->alpha;
    if (0.12f <= alphaBeforeReversal) {
        motion->asign = -motion->asign;
        motion->alpha = alphaBeforeReversal + transStepScale * 0.007f * motion->asign;
    }

    particle->scale += transStepScale * 5460.0f;
    particle->rgba = (particle->rgba & 0xFFFFFF) | (FastFloatToInt(motion->alpha * 255.0f) << 24);
    motion->rot += transStepScale * 0.002f;
    if (1.0f < motion->rot)
        motion->rot -= 1.0f;
    particle->rot = (int)(motion->rot * 255.0f);
    FastVec3Add(&particle->pos, &particle->pos, &motion->vel);
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", func_00283400);

void UpdatePart_029(PartInstance *particle)
{
    Part029Attachment *motion;
    float alphaThreshold;
    Vec4 attachmentPosition;
    Vec4 cameraOffset;

    if (particle == 0)
        return;

    motion = (Part029Attachment *)particle->update;
    if (FastDecTimer(particle->timer) || motion->parent == 0 || (signed char)motion->parent->state < 0)
        goto kill;

    motion->textureFrame = (motion->textureFrame + 1) & PART_ATTACHMENT_FRAME_MASK;
    if (particle->scale < 159600.0f) {
        particle->scale += transStepScale * 3989.99976f;
        if (159600.0f < particle->scale)
            particle->scale = 159600.0f;
    }

    else if (159600.0f < particle->scale) {
        particle->scale -= transStepScale * 15959.999f;
        if (particle->scale < 159600.0f)
            particle->scale = 159600.0f;
    }

    motion->rot += transStepScale * 0.001f;
    particle->rot = FastFloatToInt(motion->rot * 255.0f);
    particle->tex = PartClassTexs[PART_TEXTURE_ATTACHMENT_PULSE][motion->textureFrame];
    if (particle->scale <= 159600.0f || 0.0f < motion->alphaStep)
        motion->alpha += motion->alphaStep;
    {
        float alpha;
        if (particle->scale <= 159600.0f) {
            alpha = motion->alpha;
            alphaThreshold = 0.3f;
        }

        else {
            alpha = motion->alpha;
            alphaThreshold = 0.15f;
        }
        if (!(alphaThreshold < alpha)) {
            if (alpha < 0.0f) {
            kill:
                DeletePart(particle);
                return;
            }
        }

        else {
            motion->alphaStep = -motion->alphaStep;
            motion->alpha = alpha + motion->alphaStep;
        }
    }

    particle->rgba = (particle->rgba & 0xFFFFFF) + (FastFloatToInt(motion->alpha * 256.0f) << 24);
    motion->cameraOffset += (1.0f - motion->cameraOffset) * (transStepScale * 0.175f);
    if (motion->bone != -1) {
        MB_GetBonePos(motion->parent, motion->bone, &attachmentPosition);
        FastSubVec3(&cameraOffset, &GameCamera.position, &attachmentPosition);
        FastVec3Normalize(&cameraOffset, &cameraOffset, motion->cameraOffset);
        FastVec3Add(&particle->pos, &attachmentPosition, &cameraOffset);
    }
}

void UpdatePart_030(PartInstance *particle)
{
    Vec4 nextPosition, displacement, acceleration, projectedPosition;
    Part030 *motion = (Part030 *)particle->update;

    if (!(motion->type & PART_LINK_FIXED)) {
        PartInstance *linkedParticle = motion->next;
        Part030 *linkedMotion = 0;
        float linkRank = 2.0f, velocityScale;
        if (linkedParticle)
            linkedMotion = (Part030 *)linkedParticle->update;

        FastVecZero(&acceleration);
        velocityScale = 0.15f;
        if (motion->grounded == 0 && linkedParticle != 0 && !((*(long long *)&linkedMotion->ground) & PART_LINK_BLOCKED_MASK)) {
            float squaredRank;
            float linkStrength = 0.2f, rankStep = 1.0f, gainDecay = 0.999f;
            do {
                squaredRank = linkRank * linkRank;
                FastSubVec3(&nextPosition, &linkedParticle->pos, &particle->pos);
                linkRank += rankStep;
                velocityScale *= gainDecay;
                FastVec3Normalize(&nextPosition, &nextPosition, linkStrength / squaredRank);
                FastVec3Add(&acceleration, &acceleration, &nextPosition);
                linkedParticle = linkedMotion->next;
                if (linkedParticle)
                    linkedMotion = (Part030 *)linkedParticle->update;
                if (!linkedParticle)
                    break;
            } while (!((*(long long *)&linkedMotion->ground) & PART_LINK_BLOCKED_MASK));
        }

        velocityScale = (0.15f - velocityScale) + 1.07f;
        if (linkedMotion == 0 || linkedMotion->grounded == 0)
            FastVec3Add(&motion->vel, &motion->vel, &acceleration);

        else
            FastVec3Scale(&motion->vel, &motion->vel, 0.5f);

        if (motion->next)
            FastVec3Scale(&motion->vel, &motion->vel, velocityScale);

        else
            FastVec3Scale(&motion->vel, &motion->vel, 0.97f);

        motion->vel.z -= transStepScaleSq * 0.02f;
        FastVec3Add(&nextPosition, &particle->pos, &motion->vel);
    }

    else
        CopyVec4Inline(&nextPosition, &particle->pos);

    if (motion->prev) {
        FastSubVec3(&acceleration, &nextPosition, &motion->prev->pos);
        if (0.1f < FastAbsF(FastVec3Length2(&acceleration) - 0.15f)) {
            FastVec3Normalize(&acceleration, &acceleration, 0.15f);
            FastVec3Add(&nextPosition, &acceleration, &motion->prev->pos);
        }
        if (CollSphere(&nextPosition, 0, 0, 0.15f)) {
            if (motion->grounded == 0)
                CopyVec4Inline(&nextPosition, &MemSlots.collisionPush);

            else
                CopyVec4Inline(&nextPosition, &particle->pos);
            motion->grounded = 1;
        }

        else
            motion->grounded = 0;

        FastSubVec3(&acceleration, &motion->prev->pos, &GameCamera.position);
        FastTransformVec4(&acceleration, &acceleration, &GameCamera.mtx3);
        FastVec3Scale(&acceleration, &acceleration, 1.0f / acceleration.w);
        FastSubVec3(&projectedPosition, &nextPosition, &GameCamera.position);
        FastTransformVec4(&projectedPosition, &projectedPosition, &GameCamera.mtx3);
        FastVec3Scale(&projectedPosition, &projectedPosition, 1.0f / projectedPosition.w);
        FastSubVec3(&acceleration, &acceleration, &projectedPosition);
        particle->rot = FastFloatToInt(FastArcTan(acceleration.x, acceleration.y) * 128.0f / 3.1415927f) - 0x20;

        if (motion->grounded) {
            FastVec3NormalizeFrom(&motion->vel, &motion->vel, &MemSlots.collisionNormal);
            FastVec3Scale(&motion->vel, &motion->vel, 0.95f);
        }

        else {
            FastSubVec3(&displacement, &nextPosition, &particle->pos);
            FastVec3Add(&motion->vel, &motion->vel, &displacement);
            FastVec3Scale(&motion->vel, &motion->vel, 0.5f);
        }
        FastSubVec3(&displacement, &nextPosition, &particle->pos);
        FastVec3Add(&motion->vel, &motion->vel, &displacement);
        FastVec3Scale(&motion->vel, &motion->vel, 0.5f);
    }

    CopyVec4Inline(&particle->pos, &nextPosition);

    if (motion->type & PART_LINK_FADING) {
        int fadedAlpha = ((unsigned int)particle->rgba >> 24) - 2;
        if (fadedAlpha > 0)
            particle->rgba = (particle->rgba & 0xFFFFFF) | (fadedAlpha << 24);

        else if (motion->next == 0) {
            if (motion->prev)
                ((Part030 *)motion->prev->update)->next = 0;
            DeletePart(particle);
        }
    }
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", func_00283BE0);

void UpdatePart_031(PartInstance *particle)
{
    Vec4 offset[1];
    Vec4 position;
    MobyInstance *target = ((Part031TwoPoint *)particle->update)->attachment.target;
    if (target == 0 || target->state == 0xFE || target->state == 0xFD || FastDecTimer(particle->timer)) {
        DeletePart(particle);
        return;
    }

    FastSubVec3(&position, &((Part031TwoPoint *)particle->update)->attachment.target->pos, &particle->pos);
    CopyVec4(offset, &position);
    FastVec3Scale(offset, offset, (PartBeamFirstOffsetScale - 1.0f) * transStepScale + 1.0f);
    FastVec3Add(&position, offset, &((Part031TwoPoint *)particle->update)->attachment.target->pos);
    CopyVec4(&particle->pos, &position);
    FastSubVec3(&position, &((Part031TwoPoint *)particle->update)->attachment.target->pos, &((Part031TwoPoint *)particle->update)->end);
    CopyVec4(offset, &position);
    FastVec3Scale(offset, offset, (PartBeamSecondOffsetScale - 1.0f) * transStepScale + 1.0f);
    FastVec3Add(&position, offset, &((Part031TwoPoint *)particle->update)->attachment.target->pos);
    CopyVec4(&((Part031TwoPoint *)particle->update)->end, &position);

    if (FastVec3Dist(&particle->pos, &((Part031TwoPoint *)particle->update)->end) < 0.1f || FastVec3Dist(&particle->pos, &((Part031TwoPoint *)particle->update)->attachment.target->pos) < 1.0f)
        DeletePart(particle);
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_032);

void UpdatePart_032(PartInstance *particle)
{
    Part032 *motion;
    MobyInstance *parent;

    if (particle == 0)
        return;

    motion = (Part032 *)particle->update;
    parent = motion->parent;
    if (parent == 0 || (parent->state & 0xF0) == 0xF0)
        goto kill;

    CopyVec4Inline(&particle->pos, &parent->pos);
    motion->alpha += motion->dalpha;
    if (motion->alpha < 0.0f) {
    kill:
        DeletePart(particle);
        return;
    }
    if (0.6f < motion->alpha) {
        motion->dalpha = -motion->dalpha;
        motion->alpha += motion->dalpha;
    }

    motion->r += transStepScale * -0.0174f;
    if (motion->r < 0.0f)
        motion->r = 0.0f;
    motion->g += transStepScale * -0.01446f;
    if (motion->g < 0.0f)
        motion->g = 0.0f;
    motion->b += transStepScale * -0.0015f;
    if (motion->b < 0.0f)
        motion->b = 0.0f;
    {
        int packedColor = Float_To_RGBA(motion->r, motion->g, motion->b, motion->alpha);
        float phaseIncrement = transStepScale * 0.0011f;
        particle->rgba = packedColor;
        motion->rot += phaseIncrement;
    }
    if (1.0f < motion->rot)
        motion->rot -= 1.0f;

    particle->rot = FastFloatToInt(motion->rot * 255.0f);
    particle->scale = motion->parent->scale * 100000.0f * 30.0f + 50000.0f;
}

int FastDecTimer(short &timer);
void DeletePart(PartInstance *part);

void UpdatePart_033(PartInstance *part)
{
    if (FastDecTimer(part->timer))
        DeletePart(part);
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_034);

void UpdatePart_034(PartInstance *particle)
{
    Part034 *motion = (Part034 *)particle->update;
    Vec4 velocity;
    float length;
    float cameraAngle;
    float wave;

    if (FastDecTimer(particle->timer)) {
        DeletePart(particle);
        return;
    }

    if (particle->pos.z > motion->waterHeight) {
        motion->velz = 0.0f;
        if (particle->timer > FastScaleRoundInt(PART_WATER_FADE_FRAMES) - 2)
            particle->timer = FastScaleRoundInt(PART_WATER_FADE_FRAMES) - 2;
    }
    if (motion->waterHeight < particle->pos.z + frameTime * 1.3f * 40.0f) {
        if (MB_randInt(20) == 0) {
            if (particle->timer > FastScaleRoundInt(PART_WATER_FADE_FRAMES) - 2)
                particle->timer = FastScaleRoundInt(PART_WATER_FADE_FRAMES) - 2;
        }
    }
    if (particle->timer < FastScaleRoundInt(PART_WATER_FADE_FRAMES)) {
        int alpha = (unsigned int)particle->rgba >> 24;
        particle->rgba = ((alpha * (int)particle->timer / FastScaleRoundInt(PART_WATER_FADE_FRAMES)) << 24) | (particle->rgba & 0xFFFFFF);
    }

    particle->scale += transStepScale * 840.00006103515625f;
    if (motion->idealScale < particle->scale)
        particle->scale = motion->idealScale;

    velocity.x = motion->velx;
    velocity.y = motion->vely;
    velocity.z = motion->velz;
    length = FastVec3Length(&velocity.x);
    FastVec3RSqrtScale(&velocity, &velocity, transStepScale * -0.029999971389770508f * length + length);
    FastVec3Add(&particle->pos, &particle->pos, &velocity);
    Delt(velocity.z, frameTime * 1.3f, frameTimeSq * 5.0f);
    motion->velx = velocity.x;
    motion->vely = velocity.y;
    motion->velz = velocity.z;
    motion->t = FastAddRots(motion->t, motion->dt);
    cameraAngle = FastAddRots(GameCamera.rot.z, 1.5707963705062866f);
    wave = FastAngleCosF(motion->t) * motion->waveSpeed;
    velocity.x = FastAngleSinF(cameraAngle) * wave;
    velocity.y = FastAngleCosF(cameraAngle) * wave;
    velocity.z = 0.0f;
    FastVec3Add(&particle->pos, &particle->pos, &velocity);
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_035);

void UpdatePart_035(PartInstance *particle)
{
    Part035 *motion = (Part035 *)particle->update;
    int mode = motion->type;
    Vec4 nextPosition;
    Vec4 *position;

    if (mode == PART_BALLISTIC_NO_CONTACT)
        FastVec3Add(&particle->pos, &particle->pos, &motion->vel);

    else if (mode == PART_BALLISTIC_LINE_CONTACT) {
        position = &particle->pos;
        FastVec3Add(&nextPosition, position, &motion->vel);
        if (CollLine(position, &nextPosition, PART_COLOR_DECAY_COLLISION_FLAGS, 0, 0)) {
            if (CollHotspot() == 0)
                SpawnPart_045(&CollOutput.ip, 0, -1, 0.2f, 5250.0f);
            DeletePart(particle);
            return;
        }
        CopyVec4Inline(position, &nextPosition);
    }

    else if (mode == PART_BALLISTIC_WATER_CONTACT) {
        float waterHeight;
        position = &particle->pos;
        FastVec3Add(position, position, &motion->vel);
        waterHeight = Hero.waterHeight;
        if (particle->pos.z < waterHeight) {
            particle->pos.z = waterHeight;
            SpawnPart_045(position, 0, -1, 0.2f, 5250.0f);
            DeletePart(particle);
            return;
        }
    }

    else {
        position = &particle->pos;
        FastVec3Add(&nextPosition, position, &motion->vel);
        if (CollLine(position, &nextPosition, PART_COLOR_DECAY_COLLISION_FLAGS, 0, 0)) {
            if (CollHotspot() != 0) {
                COLLOUTPUT *collision = &CollOutput;
                collision->ip.z += 0.05f;
                SpawnPart_066(&collision->ip, -1, 0.25f, 3150.0f);
            }
            DeletePart(particle);
            return;
        }
        CopyVec4Inline(position, &nextPosition);
    }

    motion->vel.z -= motion->gravity;
    particle->rot += 2;
    motion->timer--;
    if (motion->timer <= 0 || particle->pos.z < motion->spawn_height) {
        particle->rgba += 0xF0000000;
        if (particle->rgba < 0)
            DeletePart(particle);
    }
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", func_002848F0);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_036);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", func_00284A58);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_037);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_038);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_039);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_040);

void UpdatePart_040(PartInstance *particle)
{
    Vec4 nextPosition;
    Vec4 probeStart;
    COLL_DAM_IN damage;
    Vec4 collisionOffset;
    Part040 *motion;
    PartInstance *spawnedParticle;
    unsigned char *textureFrames;
    unsigned char motionFlags;
    int rotationFlags;
    long long hitCollision;
    int age, collisionFlags, frameDivisor, dampingAge;
    COLL_DAM_IN *damageInput;
    MobyInstance *owner;
    Vec4 *start, *end;
    float factor, rotationSign, alpha;

    motion = (Part040 *)particle->update;
    if (particle->timer != 0 && FastDecTimer(particle->timer) != 0) {
        float positionSpread, minVelocityScale, maxVelocityScale, velocitySpread, zeroVelocity, minPositionSpread;
        motion->flags |= PART_SPLIT_FADING | PART_SPLIT_CHILD;
        minVelocityScale = 0.5f;
        positionSpread = particle->scale / 900000.0f;
        maxVelocityScale = 0.7f;
        velocitySpread = 0.2f;
        particle->scale = particle->scale * 0.8f;
        zeroVelocity = 0.0f;
        factor = MB_randRangeFloat(minVelocityScale, maxVelocityScale);
        minPositionSpread = -positionSpread;
        FastVec3Scale(&nextPosition, &motion->vel, factor);
        probeStart.x = particle->pos.x + MB_randRangeFloat(minPositionSpread, positionSpread);
        probeStart.y = particle->pos.y + MB_randRangeFloat(minPositionSpread, positionSpread);
        probeStart.z = particle->pos.z + MB_randRangeFloat(minPositionSpread, positionSpread);
        nextPosition.x = nextPosition.x + MB_randRangeFloat(-((Part040 *)particle->update)->vel.x * velocitySpread, ((Part040 *)particle->update)->vel.x * velocitySpread);
        nextPosition.y = nextPosition.y + MB_randRangeFloat(-motion->vel.y * velocitySpread, motion->vel.y * velocitySpread);
        nextPosition.z = nextPosition.z + MB_randRangeFloat(-motion->vel.z * velocitySpread, zeroVelocity);
        spawnedParticle = SpawnPart_040(&probeStart, &nextPosition, PART_SPLIT_FADING | PART_SPLIT_CHILD, motion->parent);
        if (spawnedParticle != 0) {
            spawnedParticle->timer = FastScaleRoundInt(2);
            spawnedParticle->scale = particle->scale;
        }
        FastVec3Scale(&motion->vel, &motion->vel, MB_randRangeFloat(minVelocityScale, maxVelocityScale));
        ((Part040 *)particle->update)->vel.x = ((Part040 *)particle->update)->vel.x + MB_randRangeFloat(-((Part040 *)particle->update)->vel.x * velocitySpread, ((Part040 *)particle->update)->vel.x * velocitySpread);
        motion->vel.y = motion->vel.y + MB_randRangeFloat(-motion->vel.y * velocitySpread, motion->vel.y * velocitySpread);
        motion->vel.z = motion->vel.z + MB_randRangeFloat(-motion->vel.z * velocitySpread, zeroVelocity);
        particle->pos.x = particle->pos.x + MB_randRangeFloat(minPositionSpread, positionSpread);
        particle->pos.y = particle->pos.y + MB_randRangeFloat(minPositionSpread, positionSpread);
        particle->pos.z = particle->pos.z + MB_randRangeFloat(minPositionSpread, positionSpread);
    }

    textureFrames = PartClassTexs[PART_TEXTURE_SPLITTING];
    particle->tex = textureFrames[(particle->timer + motion->posttimer + ((unsigned char)particle->tex - textureFrames[0])) &
                                  7];
    FastVec3Add(&nextPosition, &particle->pos, &motion->vel);
    age = motion->timer;
    if (FastScaleRoundInt(3) < age)
        FastSubVec3(&probeStart, &particle->pos, &motion->vel);

    else
        CopyVec4(&probeStart, &particle->pos);

    // Retail scales this scratch vector before filling the damage record.
    FastVec3Scale(&damage.momentum, &damage.momentum, 0.01f);
    motionFlags = motion->flags;
    if (motionFlags & PART_SPLIT_FADING) {
        if ((particle->rgba & 0xFF000000) == 0) {
            DeletePart(particle);
            return;
        }
        motion->flags = motionFlags | PART_SPLIT_FADING;
        owner = motion->parent;
        start = &probeStart;
        end = &nextPosition;
        collisionFlags = PART_SPLIT_COLLISION_NO_DAMAGE;
        damageInput = 0;
    }

    else {
        damage.pMoby = motion->parent;
        damage.damageFlags = PART_SPLIT_DAMAGE_FLAGS;
        damage.damageHp = 1.0f;
        CopyVec4(&damage.momentum, &motion->vel);
        if (motionFlags & PART_SPLIT_NO_MOMENTUM)
            FastVecZero(&damage.momentum);
        damage.flags = 1;
        owner = motion->parent;
        damageInput = &damage;
        start = &probeStart;
        end = &nextPosition;
        collisionFlags = 0;
    }

    hitCollision = CollLine(start, end, collisionFlags, owner, damageInput) != 0;
    if (hitCollision) {
        FastVec3Normalize(&collisionOffset, &MemSlots.collisionNormal, 1.0f);
        FastVec3NormalizeFrom(&motion->vel, &motion->vel, &MemSlots.collisionNormal);
        FastVec3Scale(&motion->vel, &motion->vel, 0.02f);
        FastVec3Normalize(&collisionOffset, &MemSlots.collisionNormal, 0.055f);
        FastVec3Add(&particle->pos, &MemSlots.collisionPoint, &collisionOffset);
        if (particle->scale < 200000.0f && (motion->flags & PART_SPLIT_FADING) == 0)
            particle->scale = particle->scale + particle->scale;
        motion->flags |= PART_SPLIT_FADING;
    }

    else {
        CopyVec4Inline(&particle->pos, &nextPosition);
    }

    if (motion->flags & PART_SPLIT_FADING) {
        float timeScale = transStepScale;
        float decayedScale;
        frameDivisor = (int)(8.0f / (timeScale * 0.443f));
        motion->posttimer++;
        decayedScale = particle->scale - 260000.0f / (float)frameDivisor * timeScale * 1.25f;
        particle->scale = decayedScale;
        if (decayedScale <= 0.0f) {
            DeletePart(particle);
            return;
        }
    }

    else {
        float timeScale = transStepScale;
        frameDivisor = (int)(8.0f / (timeScale * 0.443f));
        particle->scale = particle->scale + 260000.0f / (float)frameDivisor * timeScale;
    }

    factor = FastIntToFloat(motion->timer);
    {
        float timeScale = transStepScale;
        float divisor;
        frameDivisor = (int)(8.0f / (timeScale * 0.443f));
        divisor = (float)frameDivisor;
        alpha = 0.08f / divisor * timeScale * (factor / divisor) + 0.08f;
        if (alpha < 0.0f)
            alpha = 0.0f;
        if (0.08f < alpha)
            alpha = 0.08f;
    }
    if (motion->flags & PART_SPLIT_FADING)
        alpha = alpha / ((float)motion->posttimer / 7.0f + 1.0f);

    particle->rgba = (particle->rgba & 0xFFFFFF) | (FastFloatToInt(alpha * 256.0f) << 24);
    motion->vel.z = motion->vel.z + transStepScaleSq * 0.008f;
    dampingAge = motion->timer;
    if (FastScaleRoundInt(25) < dampingAge || (motion->flags & PART_SPLIT_FADING)) {
        motion->vel.x = motion->vel.x * 0.95f;
        motion->vel.y = motion->vel.y * 0.95f;
    }

    rotationFlags = motion->flags;
    rotationSign = -1.0f;
    if (rotationFlags & PART_SPLIT_REVERSE_ROTATION)
        rotationSign = 1.0f;
    if (rotationFlags & PART_SPLIT_FADING) {
        motion->vel.z = motion->vel.z + transStepScaleSq * 0.008f;
        factor = FastIntToFloat(motion->posttimer);
        motion->rot = motion->rot + rotationSign * (transStepScale * -0.01f) / factor;
    }

    else {
        motion->rot = motion->rot + rotationSign * (transStepScale * -0.01f);
    }

    if (1.0f < motion->rot)
        motion->rot = motion->rot - 1.0f;
    if (motion->rot < 0.0f)
        motion->rot = motion->rot + 1.0f;

    particle->rot = (int)(motion->rot * 256.0f);
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_041);

void UpdatePart_041(PartInstance *part)
{
    if (part->timer != -1 && FastDecTimer(part->timer))
        DeletePart(part);
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_042);

void UpdatePart_042(PartInstance *particle)
{
    Vec4 nextPosition, probeStart;
    COLL_DAM_IN damage;
    Part042 *motion = (Part042 *)particle->update;
    PartInstance *spawnedParticle;
    float positionSpread, minPositionSpread, alpha, factor;
    int hitCollision;
    unsigned char motionFlags;

    if (particle->timer != 0 && FastDecTimer(particle->timer)) {
        motion->flags |= PART_SPLIT_FADING | PART_SPLIT_CHILD;
        positionSpread = particle->scale / 900000.0f;
        particle->scale *= 0.8f;
        minPositionSpread = -positionSpread;
        FastVec3Scale(&nextPosition, &motion->vel, MB_randRangeFloat(0.5f, 0.7f));
        probeStart.x = particle->pos.x + MB_randRangeFloat(minPositionSpread, positionSpread);
        probeStart.y = particle->pos.y + MB_randRangeFloat(minPositionSpread, positionSpread);
        probeStart.z = particle->pos.z + MB_randRangeFloat(minPositionSpread, positionSpread);
        nextPosition.x += MB_randRangeFloat(-motion->vel.x * 0.2f, motion->vel.x * 0.2f);
        nextPosition.y += MB_randRangeFloat(-motion->vel.y * 0.2f, motion->vel.y * 0.2f);
        nextPosition.z += MB_randRangeFloat(-motion->vel.z * 0.2f, 0.0f);
        spawnedParticle = SpawnPart_042(&probeStart, &nextPosition, PART_SPLIT_FADING | PART_SPLIT_CHILD, motion->parent);
        if (spawnedParticle) {
            spawnedParticle->timer = FastScaleRoundInt(2);
            spawnedParticle->scale = particle->scale;
        }
        FastVec3Scale(&motion->vel, &motion->vel, MB_randRangeFloat(0.5f, 0.7f));
        motion->vel.x += MB_randRangeFloat(-motion->vel.x * 0.2f, motion->vel.x * 0.2f);
        motion->vel.y += MB_randRangeFloat(-motion->vel.y * 0.2f, motion->vel.y * 0.2f);
        motion->vel.z += MB_randRangeFloat(-motion->vel.z * 0.2f, 0.0f);
        particle->pos.x += MB_randRangeFloat(minPositionSpread, positionSpread);
        particle->pos.y += MB_randRangeFloat(minPositionSpread, positionSpread);
        particle->pos.z += MB_randRangeFloat(minPositionSpread, positionSpread);
    }

    particle->tex = PartClassTexs[PART_TEXTURE_SPLITTING]
                                [(particle->timer + motion->posttimer + ((unsigned char)particle->tex - PartClassTexs[PART_TEXTURE_SPLITTING][0])) &
                                 7];
    FastVec3Add(&nextPosition, &particle->pos, &motion->vel);
    hitCollision = 0;
    if (motion->timer > FastScaleRoundInt(3))
        FastSubVec3(&probeStart, &particle->pos, &motion->vel);

    else
        CopyVec4(&probeStart, &particle->pos);

    // Retail scales this scratch vector before filling the damage record.
    FastVec3Scale(&damage.momentum, &damage.momentum, 0.01f);
    motionFlags = motion->flags;
    if (motionFlags & PART_SPLIT_FADING) {
        if (!(particle->rgba & 0xFF000000)) {
            DeletePart(particle);
            return;
        }
        motion->flags = motionFlags | PART_SPLIT_FADING;
        if (!MB_randInt(3))
            hitCollision = CollLine(&probeStart, &nextPosition, 0, motion->parent, 0) != 0;
    }

    else {
        damage.pMoby = motion->parent;
        damage.damageHp = 1.0f;
        CopyVec4(&damage.momentum, &motion->vel);
        damage.damageFlags = 1;
        damage.flags = 1;
        if (!MB_randInt(3))
            hitCollision = CollLine(&probeStart, &nextPosition, 0, motion->parent, &damage) != 0;
    }

    if (hitCollision)
        motion->flags |= PART_SPLIT_FADING;

    else
        CopyVec4Inline(&particle->pos, &nextPosition);

    if (motion->flags & PART_SPLIT_FADING) {
        motion->posttimer++;
        particle->scale -= 260000.0f / (float)(int)(8.0f / (transStepScale * 0.443f)) * transStepScale * 1.25f;
        if (particle->scale <= 0.0f) {
            DeletePart(particle);
            return;
        }
    }

    else
        particle->scale += 260000.0f / (float)(int)(8.0f / (transStepScale * 0.443f)) * transStepScale;

    factor = FastIntToFloat(motion->timer);
    {
        float divisor = (float)(int)(8.0f / (transStepScale * 0.443f));
        alpha = 0.08f / divisor * transStepScale * (factor / divisor) + 0.08f;
    }
    if (alpha < 0.0f)
        alpha = 0.0f;
    if (0.08f < alpha)
        alpha = 0.08f;
    if (motion->flags & PART_SPLIT_FADING)
        alpha /= (float)motion->posttimer / 7.0f + 1.0f;

    particle->rgba = (particle->rgba & 0xFFFFFF) | (FastFloatToInt(alpha * 256.0f) << 24);
    motion->vel.z += transStepScaleSq * 0.008f;
    if (motion->timer > FastScaleRoundInt(0x19) || (motion->flags & PART_SPLIT_FADING)) {
        motion->vel.x *= 0.95f;
        motion->vel.y *= 0.95f;
    }

    {
        unsigned char rotationFlags = motion->flags;
        factor = -1.0f;
        if (rotationFlags & PART_SPLIT_REVERSE_ROTATION)
            factor = 1.0f;
        if (rotationFlags & PART_SPLIT_FADING) {
            motion->vel.z += transStepScaleSq * 0.008f;
            motion->rot += factor * (transStepScale * -0.01f) / FastIntToFloat(motion->posttimer);
        }

        else
            motion->rot += factor * (transStepScale * -0.01f);
    }

    if (1.0f < motion->rot)
        motion->rot -= 1.0f;
    if (motion->rot < 0.0f)
        motion->rot += 1.0f;

    particle->rot = (int)(motion->rot * 256.0f);
}

void UpdatePart_043(PartInstance *particle)
{
    Part043 *motion = (Part043 *)particle->update;
    short elapsed;
    float fadeRatio, initialAlpha;
    unsigned char red, green, blue, alpha;

    elapsed = ++particle->timer;
    if (motion->lifetime < elapsed) {
        DeletePart(particle);
        return;
    }

    fadeRatio = FastIntToFloat(elapsed);
    fadeRatio = fadeRatio / FastIntToFloat(motion->lifetime);
    fadeRatio = 1.0f - fadeRatio;
    red = FastFloatToInt(FastIntToFloat((unsigned char)motion->r) + fadeRatio * -0.001f);
    green = FastFloatToInt(FastIntToFloat((unsigned char)motion->g) + fadeRatio * -0.0011f);
    blue = FastFloatToInt(FastIntToFloat((unsigned char)motion->b) + fadeRatio * -0.00111f);
    if (particle->timer < FastScaleRoundInt(30)) {
        fadeRatio = FastIntToFloat(particle->timer);
        fadeRatio = fadeRatio / FastIntToFloat(FastScaleRoundInt(30));
        initialAlpha = FastIntToFloat((unsigned char)motion->a);
        alpha = FastFloatToInt(initialAlpha * fadeRatio);
    }

    else {
        fadeRatio = FastIntToFloat(particle->timer - FastScaleRoundInt(30));
        fadeRatio = fadeRatio / FastIntToFloat(motion->lifetime - FastScaleRoundInt(30));
        initialAlpha = FastIntToFloat((unsigned char)motion->a);
        fadeRatio = 1.0f - fadeRatio;
        alpha = FastFloatToInt(initialAlpha * fadeRatio);
    }
    {
        unsigned int packedColor = alpha << 24;
        packedColor |= blue << 16;
        packedColor |= green << 8;
        packedColor |= red;
        particle->rgba = packedColor;
    }

    particle->rot++;
    FastVec3Add(&particle->pos, &particle->pos, &motion->vel);
    motion->vel.z += transStepScaleSq * 0.0005f;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_044);

void UpdatePart_044(PartInstance *particle)
{
    Vec4 velocity;
    Vec4 platformCarry[1];
    Vec4 gravityDelta[1];
    Part044 *motion;
    Vec4 *position;
    float initialAlpha;
    int color;

    if (FastDecTimer(particle->timer))
        DeletePart(particle);

    else {
        motion = (Part044 *)particle->update;
        position = &particle->pos;
        initialAlpha = FastIntToFloat(motion->alpha);
        color = FastFloatToInt(initialAlpha * ((float)particle->timer / FastIntToFloat(motion->frames)));
        color = (color << 24) | (motion->b << 16);
        color |= motion->g << 8;
        color |= motion->r;
        particle->rgba = color;

        velocity.x = motion->vel.x;
        velocity.y = motion->vel.y;
        velocity.z = motion->vel.z;
        velocity.w = 0.0f;
        FastVec3Add(position, position, &velocity);

        CopyVec4(platformCarry, &Hero.frameMove);
        FastVecScaleSelf(gravityDelta, platformCarry, particle->pos.w);
        FastVecAddSelf(gravityDelta, position, platformCarry);
        FastVec3Scale(gravityDelta, &Hero.gravityDir, motion->gravity);
        FastVec3Add(&velocity, &velocity, gravityDelta);
        FastVec3Scale(&velocity, &velocity, motion->damp);
        motion->vel.x = velocity.x;
        motion->vel.y = velocity.y;
        motion->vel.z = velocity.z;

        particle->rot += (unsigned char)motion->rotSpeed;
        particle->scale += motion->scaleSpeed;
    }
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_045);

void UpdatePart_045(PartInstance *particle)
{
    Part045 *motion = (Part045 *)particle->update;
    float height;

    FastVec3Add(&particle->pos, &particle->pos, &motion->vel);
    if (particle->pos.x < 2.0f || 1021.0f < particle->pos.x || particle->pos.y < 2.0f || 1021.0f < particle->pos.y || (height = particle->pos.z) < 2.0f || 1021.0f < height) {
        DeletePart(particle);
        return;
    }

    particle->scale += motion->expandSpeed;
    particle->rot++;
    if (motion->zHeight && FastAbsF(height - *motion->zHeight) < 0.2f)
        particle->pos.z = *motion->zHeight + 0.02f;

    if (--particle->timer == 0) {
        particle->timer = 4;
        particle->rgba += 0xFF000000;
    }

    if (!(particle->rgba & 0xFF000000))
        DeletePart(particle);
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_046);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_046);

PartInstance *SpawnPart_047(Vec4 *position, Vec4 *velocity, float scale)
{
    PartInstance *part = CreatePart(0x2F);

    if (part != 0) {
        CopyVec4Inline(&part->pos, position);

        part->rgba = ((MB_randInt(8) + 0x28) << 0x18) | 0x808080;
        part->draw_dist = FastFloatToInt(2.0f) + 0x20;

        part->gs_alpha = 0x48;
        part->type = 0;
        part->tex = *PartClassTexs[0x2F];
        part->scale = scale;

        CopyVec4Inline(&((Part000 *)part->update)->vel, velocity);
        part->rot = MB_randInt(0x100);
    }

    return part;
}

void UpdatePart_047(PartInstance *part)
{
    PartSpinMotion *motion = (PartSpinMotion *)part->update;
    int rgba;

    FastVec3Scale(&motion->velocity, &motion->velocity, 0.975f);
    FastVec3Add(&part->pos, &part->pos, &motion->velocity);

    part->scale += 14700.0f;
    part->rot += motion->rotationStep;
    rgba = part->rgba + 0xFE000000;
    part->rgba = rgba;

    if (rgba < 0)
        DeletePart(part);
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", func_00286E18);

void UpdatePart_048(PartInstance *part)
{
    Part048 *spin = (Part048 *)part->update;

    part->rot += spin->rotSpeed;
    FastVec3Add(&part->pos, &part->pos, &spin->vel);

    part->rgba = FastTweenColor(spin->RGBA2, spin->RGBA1, FastAbsF(FastIntToFloat(part->timer) * spin->invTimer - 1.0f));

    if (FastDecTimer(part->timer) != 0)
        DeletePart(part);
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_049);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", func_00286F88);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_050);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_051);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_052);

void UpdatePart_052(PartInstance *part)
{
    if (FastDecTimer(part->timer))
        DeletePart(part);

    else {
        Part052 *fade = (Part052 *)part->update;
        float fraction = FastIntToFloat(part->timer) * fade->invTime;

        part->rgba = FastTweenColor(fade->finalRGBA, fade->initRGBA, fraction);
        part->scale = ((fade->initScale - fade->finalScale) * fraction + fade->finalScale) * 210000.0f;
    }
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_053);

static inline void CopyPartVelocity(Vec4 *destination, Vec3 *source)
{
    destination->x = source->x;
    destination->y = source->y;
    destination->z = source->z;
    destination->w = 0.0f;
}

void UpdatePart_053(PartInstance *particle)
{
    Part053 *motion = (Part053 *)particle->update;
    float fraction;
    Vec4 velocity;
    int alpha;

    particle->rot += (unsigned char)motion->rotSpeed;
    if (motion->initTime - particle->timer < 6) {
        int initialAlpha;
        int halfAlpha;
        fraction = (float)(motion->initTime - particle->timer) / 5.0f;
        particle->scale = motion->finalScale + ((motion->initScale + motion->finalScale) * 0.5f - motion->finalScale) * fraction;
        halfAlpha = (unsigned char)motion->initAlpha >> 1;
        initialAlpha = (unsigned char)motion->initAlpha;
        alpha = FastFloatToInt((float)initialAlpha + (float)(halfAlpha - initialAlpha) * fraction);
    }

    else {
        fraction = (float)particle->timer / FastIntToFloat(motion->initTime - 6);
        particle->scale = motion->initScale + ((motion->initScale + motion->finalScale) * 0.5f - motion->initScale) * fraction;
        alpha = FastFloatToInt((float)((unsigned char)motion->initAlpha >> 1) * fraction + 0.0f);
    }

    particle->rgba = (alpha << 24) | (particle->rgba & 0xFFFFFF);
    CopyPartVelocity(&velocity, &motion->vel);
    FastVec3Add(&particle->pos, &particle->pos, &velocity);
    motion->vel.z -= motion->gravity;

    if (particle->pos.x < 2.0f || particle->pos.x > 1021.0f || particle->pos.y < 2.0f || particle->pos.y > 1021.0f || particle->pos.z < 2.0f || particle->pos.z > 1021.0f)
        DeletePart(particle);

    else if (FastDecTimer(particle->timer))
        DeletePart(particle);
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", func_002876F8);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_054);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_055);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_055);

PartInstance *SpawnPart_056(Vec4 *position, Vec4 *velocity, float scale)
{
    PartInstance *part = CreatePart(0x38);
    int shade;

    if (part != 0) {
        int greenAlpha;

        CopyVec4Inline(&part->pos, position);

        shade = (MB_randInt(0x10) * 2) + 0x60;
        greenAlpha = (shade << 8) | 0x40000000;
        part->rgba = (shade << 0x10) | greenAlpha | shade;
        part->draw_dist = FastFloatToInt(4.0f) + 0x20;
        part->gs_alpha = 0x48;
        part->type = 0;
        part->tex = *PartClassTexs[0x38];
        part->scale = scale;

        CopyVec4Inline(&((Part000 *)part->update)->vel, velocity);
        part->rot = MB_randInt(0x100);
    }

    return part;
}

void UpdatePart_056(PartInstance *part)
{
    Part000 *motion = (Part000 *)part->update;
    FastVec3Scale(&motion->vel, &motion->vel, 0.975f);
    FastVec3Add(&part->pos, &part->pos, &motion->vel);

    part->scale += 6300.0f;
    int intensity = (part->rgba & 0xFF) - 4;
    if (intensity <= 0)
        DeletePart(part);

    else
        part->rgba = 0x60000000 | (intensity << 16) | (intensity << 8) | intensity;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_057);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_057);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_058);

void UpdatePart_058(PartInstance *particle)
{
    Vec4 scratch;
    Part058 *motion;
    Vec4 *heroPosition;
    HeroState *hero;
    int childIndex;
    float lifetime;
    float fraction;

    motion = (Part058 *)particle->update;

    switch (motion->state) {
    case PART_TWEEN_INITIAL: {
        float tweenDuration = FastIntToFloat(motion->fade_time);
        particle->rgba = FastTweenColor(0xFF4080FF, 0, (tweenDuration - FastIntToFloat(particle->timer)) / tweenDuration);
    }

        if (FastDecTimer(particle->timer)) {
            if (motion->type == 1)
                DeletePart(particle);

            else {
                motion->state = PART_TWEEN_EMITTING;
                particle->timer = motion->burst_time;
            }
        }
        break;
    case PART_TWEEN_EMITTING: {
        float speedScale;
        for (childIndex = 0; childIndex < motion->spawn_rate; childIndex++) {
            CopyVec4Inline(&scratch, &particle->pos);
            speedScale = 1.0f;
            MB_randOffset(&scratch, 0.05f);
            if (particle->timer < FastScaleRoundInt(10))
                speedScale = FastIntToFloat(particle->timer) / (float)FastScaleRoundInt(10);
            SpawnPart_058(&scratch, PART_TWEEN_EMITTED, motion->fade_time, motion->burst_time, motion->spawn_rate, motion->flame_time, motion->pParent, motion->damageHp, speedScale);
        }
    }

        if (FastDecTimer(particle->timer))
            DeletePart(particle);

        heroPosition = &Hero.position;
        if (FastVec3DistLen(&particle->pos, heroPosition) < 0.3f) {
            hero = &Hero;
            if (hero->position.z < particle->pos.z + 1.2f) {
                FastSubVec3(&scratch, heroPosition, &particle->pos);
                FastVec3Normalize(&scratch, &scratch, 1.0f);
                scratch.z = 1.0f;
                CollDamageMobyDirect_2(hero->moby, motion->pParent, 1, &particle->pos, &scratch, motion->damageHp);
            }
        }
        break;
    case PART_TWEEN_EMITTED:
        FastVec3Add(&particle->pos, &particle->pos, &motion->vel);
        lifetime = FastIntToFloat(motion->flame_time);
        fraction = lifetime - FastIntToFloat(particle->timer);
        fraction = fraction / lifetime;
        particle->rgba = FastTweenColor((motion->alpha_top << 24) | 0x4060, 0x8FAFFF, fraction);
        if (fraction < 0.6f)
            particle->scale += transStepScale * 0.043f * 210000.0f;

        else
            particle->scale -= transStepScale * 0.08f * 210000.0f;

        particle->tex = PartClassTexs[PART_TEXTURE_TWEEN_EMITTER][rand() & 7];

        if ((particle - (PartInstance *)PartInstances) & 1)
            particle->rot++;

        else
            particle->rot--;

        if (FastDecTimer(particle->timer))
            DeletePart(particle);
        break;
    }
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_059);

enum { PART_RELATIVE_TO_HERO = 1 };

void UpdatePart_059(PartInstance *part)
{
    Part059 *motion = (Part059 *)part->update;
    if (motion->type == PART_RELATIVE_TO_HERO)
        FastVec3Add(&part->pos, &Hero.position, &motion->ofs);

    if (FastDecTimer(part->timer))
        DeletePart(part);
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_060);

void UpdatePart_060(PartInstance *particle)
{
    enum { PART_MOVING_HERO_RELATIVE = 1 };
    Part060 *motion = (Part060 *)particle->update;
    float remaining;
    unsigned int color;

    if (motion->type == PART_MOVING_HERO_RELATIVE) {
        HeroState *hero = &Hero;
        particle->pos.x = hero->position.x + motion->ofs.x;
        particle->pos.y = hero->position.y + motion->ofs.y;
        particle->pos.z = hero->position.z + motion->ofs.z;
        FastVec3Add(&particle->pos, &particle->pos, &motion->vel);
        motion->ofs.x = particle->pos.x - hero->position.x;
        motion->ofs.y = particle->pos.y - hero->position.y;
        motion->ofs.z = particle->pos.z - hero->position.z;
    }

    else
        FastVec3Add(&particle->pos, &particle->pos, &motion->vel);

    if (particle->pos.x < 2.0f || 1021.0f < particle->pos.x || particle->pos.y < 2.0f || 1021.0f < particle->pos.y || particle->pos.z < 2.0f || 1021.0f < particle->pos.z || FastDecTimer(particle->timer)) {
        DeletePart(particle);
        return;
    }

    color = particle->rgba & 0xFFFFFF;
    remaining = FastIntToFloat(particle->timer - 1);
    particle->rgba = FastTweenColor(color, particle->rgba, remaining / FastIntToFloat(particle->timer));
}

void UpdatePart_061(PartInstance *particle)
{
    Part061 *motion;
    float alphaThreshold;
    Vec4 attachmentPosition;
    Vec4 cameraOffset;

    if (particle == 0)
        return;

    motion = (Part061 *)particle->update;
    if (FastDecTimer(particle->timer) || motion->parent == 0 || (signed char)motion->parent->state < 0)
        goto kill;

    motion->frame = (motion->frame + 1) & PART_ATTACHMENT_FRAME_MASK;
    if (particle->scale < 159600.0f) {
        particle->scale += transStepScale * 3989.99976f;
        if (159600.0f < particle->scale)
            particle->scale = 159600.0f;
    }

    else if (159600.0f < particle->scale) {
        particle->scale -= transStepScale * 15959.999f;
        if (particle->scale < 159600.0f)
            particle->scale = 159600.0f;
    }
    motion->rot += transStepScale * 0.001f;
    particle->rot = FastFloatToInt(motion->rot * 255.0f);
    particle->tex = PartClassTexs[PART_TEXTURE_JOINT_PULSE][motion->frame];
    if (particle->scale <= 159600.0f || 0.0f < motion->dalpha)
        motion->alpha += motion->dalpha;
    {
        float alpha;
        if (particle->scale <= 159600.0f) {
            alpha = motion->alpha;
            alphaThreshold = 0.3f;
        }

        else {
            alpha = motion->alpha;
            alphaThreshold = 0.15f;
        }
        if (!(alphaThreshold < alpha)) {
            if (alpha < 0.0f) {
            kill:
                DeletePart(particle);
                return;
            }
        }

        else {
            motion->dalpha = -motion->dalpha;
            motion->alpha = alpha + motion->dalpha;
        }
    }
    particle->rgba = (particle->rgba & 0xFFFFFF) + (FastFloatToInt(motion->alpha * 256.0f) << 24);
    motion->dist += (1.0f - motion->dist) * (transStepScale * 0.175f);
    MB_GetBonePos(motion->parent, motion->joint, &attachmentPosition);
    FastSubVec3(&cameraOffset, &GameCamera.position, &attachmentPosition);
    FastVec3Normalize(&cameraOffset, &cameraOffset, motion->dist);
    FastVec3Add(&particle->pos, &attachmentPosition, &cameraOffset);
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_062);

void UpdatePart_062(PartInstance *part)
{
    PartFollowFade *fade = (PartFollowFade *)part->update;
    int rgba;
    int alpha;

    if (fade->mode == 1)
        return;

    if (fade->mode == 2) {
        part->pos.x = fade->pMoby->pos.x + fade->offset.x;
        part->pos.y = fade->pMoby->pos.y + fade->offset.y;
        part->pos.z = fade->pMoby->pos.z + fade->offset.z;
    }

    rgba = part->rgba;
    alpha = rgba >> 24;
    alpha -= fade->fadeStep;

    if (alpha <= 0) {
        DeletePart(part);
        return;
    }

    part->rgba = (rgba & 0xFFFFFF) | (alpha << 24);
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", func_00288D50);

void UpdatePart_063(PartInstance *part)
{
    if (FastDecTimer(part->timer))
        DeletePart(part);
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_064);

unsigned int PartFloorBurstRandomLimit = 15;

void UpdatePart_064(PartInstance *particle)
{
    Part064 *motion = (Part064 *)particle->update;
    Vec4 emittedPosition;
    int red, green, blue;
    int emittedLifetime, debrisStartColor, debrisEndColor;
    float spawnScale;

    if (FastDecTimer(particle->timer))
        motion->vel.z -= motion->gravity;

    FastVec3Add(&particle->pos, &particle->pos, &motion->vel);
    particle->rot += 2;
    if (!(particle->pos.z < motion->height))
        return;

    red = particle->rgba & 0xFF;
    green = (particle->rgba & 0xFF00) >> 8;
    blue = ((unsigned int)particle->rgba >> 16) & 0xFF;

    if (!MB_randInt(PartFloorBurstRandomLimit - 1)) {
        particle->pos.z = motion->height;
        motion->vel.x *= MB_randRangeFloat(1.0f, 3.5f);
        motion->vel.y *= MB_randRangeFloat(1.0f, 3.5f);
        motion->vel.z *= MB_randRangeFloat(-1.0f, -1.5f);
        spawnScale = particle->scale;
        spawnScale *= 0.5f;
        emittedLifetime = MB_randRange(FastScaleRoundInt(0x3C), FastScaleRoundInt(0x78));
        SpawnPart_015(&particle->pos, &motion->vel, particle->rgba, motion->endRGBA, spawnScale, emittedLifetime, 0, (unsigned char)particle->tex, (unsigned char)particle->gs_alpha);
    }

    else {
        particle->pos.z = motion->height;
        motion->vel.x += MB_randRangeFloat(-5.0f, 5.0f) * frameTime;
        motion->vel.y += MB_randRangeFloat(-5.0f, 5.0f) * frameTime;
        motion->vel.z *= MB_randRangeFloat(-0.5f, -1.0f);
        spawnScale = particle->scale;
        spawnScale *= 0.25f;
        emittedLifetime = MB_randRange(FastScaleRoundInt(0x1E), FastScaleRoundInt(0x3C));
        SpawnPart_015(&particle->pos, &motion->vel, particle->rgba, motion->endRGBA, spawnScale, emittedLifetime, 0, (unsigned char)particle->tex, (unsigned char)particle->gs_alpha);
    }

    if (Level == LEVEL_ORXON) {
        if (!MB_randInt(0x13)) {
            CopyVec4(&emittedPosition, &particle->pos);
            emittedPosition.z += 0.1f;
            SpawnPart_045(&emittedPosition, 0, ((MB_randInt(6) + 0x34) << 24) | (blue << 16) | (green << 8) | red, 0.05f, 10500.0f);
        }
        if (!MB_randInt(9)) {
            debrisStartColor = TweenColor(0x7F000000, 0x7F000000 | (blue << 16) | (green << 8) | red, MB_randRangeFloat(0.25f, 1.0f));
            debrisEndColor = TweenColor(0, 0x5F00, MB_randRangeFloat(0.5f, 1.0f));
            motion->vel.x = MB_randRangeFloat(-1.0f, 1.0f);
            motion->vel.y = MB_randRangeFloat(-1.0f, 1.0f);
            motion->vel.z = 0.0f;
            FastVec3Normalize(&motion->vel, &motion->vel, MB_randRangeFloat(1.5f, 3.0f) * frameTime);
            motion->vel.z = frameTime * 3.0f;
            CopyVec4(&emittedPosition, &particle->pos);
            emittedPosition.z -= 1.5f;
            spawnScale = MB_randRangeFloat(420000.0f, 630000.0f);
            emittedLifetime = MB_randRange(FastScaleRoundInt(0x5A), FastScaleRoundInt(0x96));
            SpawnPart_016(&emittedPosition, &motion->vel, debrisStartColor, debrisEndColor, spawnScale, emittedLifetime, 3);
        }
    }

    DeletePart(particle);
}

void UpdatePart_065(PartInstance *particle)
{
    Vec4 nextPosition;
    Part065 *motion;
    Vec4 *position;

    if (particle == 0)
        return;

    motion = (Part065 *)particle->update;
    position = &particle->pos;
    motion->alpha += transStepScale * 0.0f;
    particle->scale += transStepScale * -100.0f;
    FastVec3Add(&nextPosition, position, &motion->vel);
    if (motion->vel.x != 0.0f || motion->vel.y != 0.0f || motion->vel.z != 0.0f) {
        if (CollLine(&particle->pos, &nextPosition, PART_COLOR_DECAY_COLLISION_FLAGS, (MobyInstance *)particle, 0)) {
            CopyVec4(&particle->pos, &MemSlots.collisionPoint);
            FastVecZero(&motion->vel);
            particle->scale += particle->scale;
        }

        else {
            CopyVec4(&particle->pos, &nextPosition);
            if (motion->vel.w != 0.0f)
                motion->vel.z += motion->vel.w;

            else
                motion->vel.z += transStepScaleSq * -0.0063f;
        }
    }

    if (motion->alpha <= 0.0f || FastDecTimer(particle->timer) || particle->scale < 0.0f || nextPosition.x < 0.01f || nextPosition.y < 0.01f || nextPosition.z < 0.01f) {
        DeletePart(particle);
        return;
    }

    motion->r += transStepScale * -0.01f;
    if (motion->r < 0.0f)
        motion->r = 0.0f;
    motion->g += transStepScale * -0.03001f;
    if (motion->g < 0.0f)
        motion->g = 0.0f;
    motion->b += transStepScale * -0.05f;
    if (motion->b < 0.0f)
        motion->b = 0.0f;
    motion->alpha += transStepScale * 0.0f;
    if (motion->alpha < 0.0f)
        motion->alpha = 0.0f;

    particle->rgba = Float_To_RGBA(motion->r, motion->g, motion->b, motion->alpha);
    particle->rot--;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_066);

void UpdatePart_066(PartInstance *part)
{
    Part066 *motion = (Part066 *)part->update;
    int timer;

    FastVec3Add(&part->pos, &part->pos, &motion->vel);

    part->scale += motion->expandSpeed;
    part->rot += 1;

    timer = (unsigned short)part->timer - 1;
    part->timer = timer;

    if ((short)timer == 0) {
        part->rgba += 0xFF000000;
        part->timer = 2;
    }

    if ((part->rgba & 0xFF000000) == 0)
        DeletePart(part);
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_067);

void UpdatePart_067(PartInstance *particle)
{
    Part067 *motion = (Part067 *)particle->update;
    Vec4 positionOffset;
    Vec4 secondaryOffset;
    Vec4 angles;
    Mtx4 secondaryRotation;
    PartInstance *spawnedParticle;
    float orbitRadius;
    float wobbleRadius;
    float initialAngle;

    if (motion->type == PART_ORBIT_TRAIL_FADE) {
        if (DecAlpha(&particle->rgba, motion->alphaSub))
            goto kill;
        if (motion->pParent == 0)
            return;
        positionOffset.x = motion->vel.x;
        positionOffset.y = motion->vel.y;
        positionOffset.z = motion->vel.z;
        FastVec3Scale(&positionOffset, &positionOffset, FastIntToFloat(motion->aliveTime));
        FastVec3Add(&particle->pos, &motion->pParent->pos, &positionOffset);
        return;
    }
    if (FastDecTimer(particle->timer))
        goto kill;
    if (particle->timer < FastScaleRoundInt(PART_ORBIT_FADE_FRAMES)) {
        if (DecAlpha(&particle->rgba, PART_ORBIT_ALPHA_STEP)) {
        kill:
            DeletePart(particle);
            return;
        }
    }
    if (motion->type == PART_ORBIT_EMITTER) {
        initialAngle = 0.0f;
        SpawnPart_067(0, &particle->pos, FastScaleRoundInt(PART_ORBIT_FADE_FRAMES), initialAngle, initialAngle, PART_ORBIT_TRAIL_FADE, (signed char)((unsigned int)particle->rgba >> 24), 0);
    }

    else {
        positionOffset.x = motion->vel.x;
        positionOffset.y = motion->vel.y;
        positionOffset.z = motion->vel.z;
        initialAngle = 0.0f;
        spawnedParticle = SpawnPart_067(motion->pParent, &particle->pos, FastScaleRoundInt(PART_ORBIT_FADE_FRAMES), initialAngle, initialAngle, PART_ORBIT_TRAIL_FADE, (signed char)((unsigned int)particle->rgba >> 24), &positionOffset);
        if (spawnedParticle)
            ((Part067 *)spawnedParticle->update)->aliveTime = motion->aliveTime;
    }
    if (motion->type != PART_ORBIT_EMITTER)
        return;
    CopyVec4Inline(&particle->pos, &motion->pParent->pos);
    orbitRadius = 2.25f;
    positionOffset.x = FastAngleSinF(motion->tOuter) * orbitRadius;
    wobbleRadius = 0.28f;
    positionOffset.y = FastAngleCosF(motion->tOuter) * orbitRadius;
    positionOffset.z = positionOffset.x;
    positionOffset.x = 0.0f;
    secondaryOffset.x = FastAngleSinF(motion->tInner) * wobbleRadius;
    secondaryOffset.y = FastAngleCosF(motion->tInner) * wobbleRadius;
    secondaryOffset.z = secondaryOffset.x;
    secondaryOffset.x = 0.0f;
    FastVecZero(&angles);
    angles.y = motion->tOuter;
    FastEulerToMtx1(&secondaryRotation, &angles);
    FastTransformVec4(&secondaryOffset, &secondaryOffset, &secondaryRotation);
    FastVec3Add(&positionOffset, &positionOffset, &secondaryOffset);
    FastVecMtx3Mult(&positionOffset, &positionOffset, &motion->pParent->transform);
    FastVec3Add(&particle->pos, &particle->pos, &positionOffset);
    motion->tOuter = FastAddRots(motion->tOuter, frameTime * 0.9599310755729675f);
    motion->tInner = FastAddRots(motion->tInner, frameTime * 4.363323211669922f);
}


INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", func_00289CB8);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_068);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_069);

void UpdatePart_070(PartInstance *part)
{
    if (--part->timer == 0) {
        part->rgba -= 1 << 24;
        part->timer = 2;
    }

    if (!(part->rgba & 0xFF000000))
        DeletePart(part);
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", func_0028A0D8);

void UpdatePart_071(PartInstance *particle)
{
    Part071 *motion = (Part071 *)particle->update;
    Vec4 appliedDelta, motionScratch, finalMotion;
    float blendOrDistance;
    int rgb;

    if (worldUpdateTime & 1)
        particle->rot++;

    blendOrDistance = FastVec3Dist(&particle->pos, &Hero.cgPos);
    if (blendOrDistance < 5.0f && 0.0f < motion->p78Var->closePt.z) {
        FastSubVec3(&motionScratch, &motion->p78Var->closePt, &particle->pos);
        if (0.5f < FastVec3Length2(&motionScratch)) {
            FastVec3Normalize(&motionScratch, &motionScratch, 0.1f / blendOrDistance);
            FastVec3Add(&particle->pos, &particle->pos, &motionScratch);
        }

        else {
            FastVec3Normalize(&motionScratch, &motionScratch, 0.005f);
            MB_compressVector(&motionScratch, &motion->vel2);
        }
    }

    blendOrDistance = (2.5f - (blendOrDistance - 0.5f)) / 2.5f;
    if (1.0f < blendOrDistance)
        blendOrDistance = 1.0f;

    else if (blendOrDistance < 0.0f)
        blendOrDistance = 0.0f;

    particle->rgba = FastTweenColor(motion->rgba1, motion->rgba2, blendOrDistance);

    if (motion->shootTimer) {
        *T0_COUNT = 0;
        MB_decompressVector(&appliedDelta, &motion->vel1);
        FastVec3Add(&particle->pos, &particle->pos, &appliedDelta);
        blendOrDistance = FastIntToFloat(particle->timer) / FastIntToFloat(motion->shootTimer);
        particle->rgba = FastTweenColor(particle->rgba & 0xFFFFFF, particle->rgba, 1.0f - blendOrDistance);
        if (FastDecTimer(particle->timer)) {
            motion->shootTimer = 0;
            particle->timer = motion->slowTimer;
        }
    }

    else if (motion->slowTimer) {
        MB_decompressVector(&motionScratch, &motion->vel1);
        MB_decompressVector(&finalMotion, &motion->vel2);
        FastVecLerp(&appliedDelta, &finalMotion, &motionScratch, FastIntToFloat(particle->timer) / FastIntToFloat(motion->slowTimer));
        FastVec3Add(&particle->pos, &particle->pos, &appliedDelta);
        if (FastDecTimer(particle->timer)) {
            motion->slowTimer = 0;
            particle->timer = motion->fadeTimer;
        }
    }

    else {
        MB_decompressVector(&appliedDelta, &motion->vel2);
        FastVec3Add(&particle->pos, &particle->pos, &appliedDelta);
        rgb = particle->rgba & 0xFFFFFF;
        particle->rgba = FastTweenColor(rgb, particle->rgba, FastIntToFloat(particle->timer) / FastIntToFloat(motion->fadeTimer));
        if (FastDecTimer(particle->timer))
            DeletePart(particle);
    }
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_072);

void UpdatePart_072(PartInstance *part)
{
    part->rot += ((PartRotationMotion *)part->update)->rotationStep;
    if (part->scale <= 0.0f) {
        part->scale = 0.0f;
        DeletePart(part);
    }
}

void UpdatePart_073(PartInstance *particle)
{
    Vec4 velocity;
    Vec4 groundProbe;
    Vec4 groundRecheck;
    Vec4 *motion = &((Part000 *)particle->update)->vel;
    float groundHeight;
    int gridX;
    int gridY;
    Vec4 *position;

    groundHeight = motion->w;
    if (particle->pos.x < 0.0f || particle->pos.y < 0.0f || 512.0f < particle->pos.x || 512.0f < particle->pos.y) {
        DeletePart(particle);
        return;
    }
    if (particle->pos.z < groundHeight) {
        CopyVec4(&velocity, &particle->pos);
        MB_SpawnGridParticles(&velocity);
        DeletePart(particle);
        return;
    }

    CopyVec4(&velocity, motion);
    gridX = particle->pos.x;
    gridY = particle->pos.y;
    velocity.w = 0.0f;
    FastVec3Add(&particle->pos, &particle->pos, &velocity);
    FastVec3Add(&particle->pos, &particle->pos, &PartGridDrift);
    if (gridX != (int)particle->pos.x || gridY != (int)particle->pos.y) {
        CopyVec4(&groundProbe, &particle->pos);
        groundHeight = MB_SampleByteGrid(&groundProbe);
        if (groundHeight < PartGridMinimumGround)
            groundHeight = PartGridMinimumGround;

        else {
            CopyVec4(&groundRecheck, &particle->pos);
            groundHeight = MB_SampleByteGrid(&groundRecheck);
        }
        if (particle->pos.z < groundHeight) {
            CopyVec4(&groundProbe, &particle->pos);
            MB_SpawnGridParticles(&groundProbe);
            DeletePart(particle);
            return;
        }
    }

    velocity.x = 0.0f;
    velocity.y = 0.0f;
    velocity.w = 0.0f;
    velocity.z = -(frameTimeSq * 0.5f);
    FastVec3Add(motion, &velocity, motion);
    motion->w = groundHeight + PartGridClearance;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_074);

void UpdatePart_074(PartInstance *particle)
{
    Part074 *motion = (Part074 *)particle->update;
    Part074_fixed *appearance = motion->fixed;
    Vec4 velocity;
    Vec4 offset;
    Vec4 transformedOffset;
    MobyInstance *parent;
    float decay;
    float scale;
    int elapsed;

    elapsed = appearance->lifeSpan - particle->timer;
    scale = FastIntToFloat(appearance->maxScale * elapsed / appearance->lifeSpan + appearance->startScale);
    decay = transStepScale * -0.01999998f + 1.0f;
    particle->scale = scale * 1000.0f;
    velocity.x = motion->vel.x;
    velocity.y = motion->vel.y;
    velocity.z = motion->vel.z;
    FastVec3Scale(&velocity, &velocity, decay);
    motion->vel.x = velocity.x;
    motion->vel.y = velocity.y;
    motion->vel.z = velocity.z;
    parent = motion->pParent;
    if (parent != 0 && parent->state != 0xFE && parent->state != 0xFD) {
        offset.x = motion->ofs.x;
        offset.y = motion->ofs.y;
        offset.z = motion->ofs.z;
        FastVec3Add(&offset, &offset, &velocity);
        motion->ofs.x = offset.x;
        motion->ofs.y = offset.y;
        motion->ofs.z = offset.z;
        FastVecMtx3Mult(&transformedOffset, &offset, &motion->pParent->transform);
        FastVec3Add(&particle->pos, &motion->pParent->pos, &transformedOffset);
    }

    else {
        DeletePart(particle);
        return;
    }

    particle->rot++;
    particle->rgba = TweenColor(appearance->endColor, appearance->beginColor, (float)particle->timer / FastIntToFloat(appearance->lifeSpan));
    if (FastDecTimer(particle->timer))
        DeletePart(particle);
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", func_0028AAE0);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_075);

// Unreferenced retail literal-pool entries between the two live small-data scalars.
extern const unsigned int PartLiteralSignedMask __attribute__((section(".sdata"))) = 0x7FFFFFFF;
extern const unsigned int PartLiteralByteMask __attribute__((section(".sdata"))) = 0xFF;
extern const float PartLiteralHalf __attribute__((section(".sdata"))) = 0.5f;
extern const float PartLiteralZero __attribute__((section(".sdata"))) = 0.0f;
extern const unsigned int PartLiteralNine __attribute__((section(".sdata"))) = 9;

int PartFadeAlphaStep = 19;

void UpdatePart_076(PartInstance *part)
{
    DecAlpha(&part->rgba, PartFadeAlphaStep);

    if (FastDecTimer(part->timer) != 0)
        DeletePart(part);
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", func_0028AC50);

typedef int Vec4Quad __attribute__((mode(TI)));

void UpdatePart_077(PartInstance *part)
{
    Vec4 origin;
    float duration;
    float fraction;

    *(Vec4Quad *)&origin = *(Vec4Quad *)&((Part000 *)part->update)->vel;

    duration = origin.w;
    origin.w = 0.0f;

    fraction = FastIntToFloat(part->timer) / duration;
    part->rgba = (FastFloatToInt(fraction * 38.0f) << 24) | 0x808080;
    part->rot = FastFloatToInt(fraction * 33.0f);

    FastVec3Add(&part->pos, &part->pos, &origin);

    if (FastDecTimer(part->timer))
        DeletePart(part);
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_078);



extern const unsigned int PartLiteralReservedZero __attribute__((section(".sdata"))) = 0;
extern const unsigned int PartLiteralSeventySix __attribute__((section(".sdata"))) = 76;
float PartProximityCorrectionLength = 0.2f;

void UpdatePart_078(PartInstance *particle)
{
    Part078 *motion = (Part078 *)particle->update;
    Vec4 *position;
    float fraction;
    Vec4 velocity;
    Vec4 targetDelta;
    Vec4 correction;
    Vec3 *particleVelocity;
    int alpha;

    particle->rot += (unsigned char)motion->rotSpeed;
    if (motion->initTime - particle->timer < 6) {
        int initialAlpha;
        int halfAlpha;
        fraction = (float)(motion->initTime - particle->timer) / 5.0f;
        particle->scale = motion->finalScale + ((motion->initScale + motion->finalScale) * 0.5f - motion->finalScale) * fraction;
        halfAlpha = (unsigned char)motion->initAlpha >> 1;
        initialAlpha = (unsigned char)motion->initAlpha;
        alpha = FastFloatToInt((float)initialAlpha + (float)(halfAlpha - initialAlpha) * fraction);
    }

    else {
        fraction = (float)particle->timer / FastIntToFloat(motion->initTime - 6);
        particle->scale = motion->initScale + ((motion->initScale + motion->finalScale) * 0.5f - motion->initScale) * fraction;
        alpha = FastFloatToInt((float)((unsigned char)motion->initAlpha >> 1) * fraction + 0.0f);
    }

    position = &particle->pos;
    particle->rgba = (alpha << 24) | (particle->rgba & 0xFFFFFF);
    CopyPartVelocity(&velocity, &motion->vel);
    FastVec3Add(position, position, &velocity);

    if (motion->pTarget != 0) {
        FastSubVec3(&targetDelta, &motion->pTarget->pos, position);
        if (targetDelta.x <= 2.0f && targetDelta.y <= 2.0f) {
            FastVec3Cross(&correction, &targetDelta, &ParticleProximityAxis);
            FastVec3Normalize(&correction, &correction, PartProximityCorrectionLength);
            FastVec3Add(position, position, &correction);
            if (targetDelta.x <= 0.5f && targetDelta.y <= 0.5f)
                FastVec3Normalize(&velocity, &targetDelta, 0.03f);

            else
                FastVec3Normalize(&velocity, &targetDelta, FastVec3Length2(&velocity));
            particleVelocity = &motion->vel;
            particleVelocity->x = velocity.x;
            particleVelocity->y = velocity.y;
            velocity.z += 0.02f;
            particleVelocity->z = velocity.z;
        }
    }

    if (FastDecTimer(particle->timer))
        DeletePart(particle);
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_079);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_080);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", func_0028B408);
