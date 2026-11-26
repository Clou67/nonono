#include "common.h"
#include "hero.h"
#include "fastfunc.h"
#include "part.h"
#include "mobyutil.h"
#include "mathfunc_inline.h"
#include "vuchain.h"
#include "gameglobals.h"
#include "camera.h"

extern float frameTimeSq __attribute__((section(".sdata")));

int CollLine(Vec4 *start, Vec4 *end, int flags, MobyInstance *ignore, COLL_DAM_IN *damage);


INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", ResetParticles);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_001);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_001);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_002);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_002);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_003);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", func_0027E0D0);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_004);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_004);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_005);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_005);

void UpdatePart_006(PartInstance *part)
{
    PartTimedScale *scale = &part->timedScale;

    if (FastDecTimer(scale->timer)) {
        DeletePart(part);
        return;
    }

    part->scale += scale->scaleStep;

    if (FastScaleRoundInt(6) > scale->timer)
        part->rgba = (part->rgba & 0xFFFFFF) | (((scale->timer * 0x7F) / FastScaleRoundInt(6)) << 24);
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_006);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_007);

void UpdatePart_008(PartInstance *part)
{
    PartTimedScale *scale = &part->timedScale;

    if (FastDecTimer(scale->timer)) {
        DeletePart(part);
        return;
    }

    part->scale += scale->scaleStep;

    if (FastScaleRoundInt(6) > scale->timer)
        part->rgba = (part->rgba & 0xFFFFFF) | (((scale->timer * 0x7F) / FastScaleRoundInt(6)) << 24);
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_008);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_009);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", func_0027F4D0);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_010);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_010);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_011);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_011);

void UpdatePart_012(PartInstance *particle)
{
    PartBranchingMotion *motion = &particle->branchingMotion;
    particle->rot++;
    if (!(motion->flags & PART_BRANCH_FADING)) {
        int childIndex;
        FastVec3Add(&particle->pos, &particle->pos, &motion->velocity);
        if (motion->flags & PART_BRANCH_GRAVITY)
            motion->velocity.z += frameTimeSq * 9.8f;
        {
            float scaleFactor = 0.8f;
            if (motion->flags & PART_BRANCH_BOOST)
                scaleFactor = 0.6f;
            FastVec3Scale(&motion->velocity, &motion->velocity, scaleFactor);
        }

        if (particle->timer == FastFloatToInt((float)motion->lifetime * 0.85f) &&
            motion->generation < 2 && !(motion->flags & PART_BRANCH_GRAVITY)) {
            for (childIndex = 4; childIndex >= 0; childIndex--) {
                int childLifetime =
                    FastFloatToInt((float)motion->lifetime * MB_randRangeFloat(0.9f, 1.1f));
                int childTimer = motion->timer;
                float childVelocityScale = MB_randRangeFloat(0.85f, 1.0f);
                SpawnPart_011(&particle->pos, &motion->velocity, motion->startColor,
                              motion->endColor, childLifetime, childTimer, motion->generation + 1,
                              motion->sizeCurve, motion->flags,
                              motion->velocity.w * childVelocityScale);
            }
        }

        if (!(motion->flags & PART_BRANCH_GRAVITY)) {
            float sizeCurve = motion->sizeCurve;
            float totalFrames = FastIntToFloat(motion->lifetime);
            float linearCoeff = (totalFrames * 8.0f - totalFrames * 3.0f * sizeCurve) /
                                (sizeCurve * 8.0f * sizeCurve + sizeCurve * 8.0f);
            float quadraticCoeff =
                (totalFrames * 3.0f + linearCoeff * 8.0f * sizeCurve) / (sizeCurve * -8.0f);
            float remainingFrames = FastIntToFloat(particle->timer);
            float scaleFactor = FastFSqrt(linearCoeff * linearCoeff -
                                          quadraticCoeff * 4.0f * (totalFrames - remainingFrames));
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

        if (motion->flags & PART_BRANCH_BOOST)
            particle->rgba = FastTweenColor(motion->startColor, 0xFFFFFFF,
                                            (float)particle->timer / (float)motion->lifetime);

        else
            particle->rgba = FastTweenColor(motion->endColor, motion->startColor,
                                            (float)particle->timer / (float)motion->lifetime);

        FastDecTimer(motion->timer);
        if (FastDecTimer(particle->timer)) {
            if (motion->flags & PART_BRANCH_BOOST) {
                int tripledLifetime = motion->lifetime * 3;
                particle->timer = tripledLifetime;
                motion->lifetime = tripledLifetime;
                motion->flags = (motion->flags & ~PART_BRANCH_BOOST) | PART_BRANCH_GRAVITY;
                FastVec3Normalize(&motion->velocity, &motion->velocity,
                                  motion->velocity.w * MB_randRangeFloat(1.6f, 2.0f));
            }

            else {
                int fadeLifetime;
                motion->startColor = motion->endColor;
                motion->endColor = ((unsigned char)particle->gs_alpha == 0x48) ? 0 : 0xF2F3F3F;
                motion->flags |= PART_BRANCH_FADING;
                fadeLifetime = MB_randRange(motion->lifetime * 2, motion->lifetime * 3);
                if (motion->flags & PART_BRANCH_LONG_FADE)
                    fadeLifetime *= 5;
                motion->lifetime = fadeLifetime;
                particle->timer = (unsigned char)fadeLifetime;
            }
        }
    }

    else {
        int fadeDuration = FastFloatToInt((float)motion->lifetime * 0.75f) + 1;
        int blendDuration = FastFloatToInt((float)motion->lifetime * 0.25f) + 1;
        int timer;
        motion->velocity.z += frameTimeSq * 3.0f;
        FastVec3Add(&particle->pos, &particle->pos, &motion->velocity);
        FastVec3Scale(&motion->velocity, &motion->velocity, 0.98f);
        timer = particle->timer;
        if (fadeDuration < timer)
            particle->rgba = FastTweenColor(motion->endColor, motion->startColor,
                                            (float)(timer - fadeDuration) / (float)blendDuration);

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

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_013);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_013);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_014);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_014);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_015);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_015);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_016);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_016);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_017);

void UpdatePart_018(PartInstance *part)
{
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_018);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_019);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_019);

void FastVec3Add(Vec4 *out, Vec4 *first, Vec4 *second);
int FastDecTimer(short &timer);
void DeletePart(PartInstance *part);

void UpdatePart_020(PartInstance *part)
{
    FastVec3Add(&part->pos, &part->pos, &part->motion20.velocity);
    FastVec3Add(&part->motion20.origin, &part->motion20.origin, &part->motion20.velocity);

    part->rgba -= 6 << 24;
    part->rgbaScale = part->rgba;
    if (part->rgba < 0)
        DeletePart(part);
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_021);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_021);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_022);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_022);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_023);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_024);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_025);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_025);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_026);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_026);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_027);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_027);

void UpdatePart_028(PartInstance *part)
{
    PartTimedFade *fade = &part->timedFade;

    FastVec3Add(&part->pos, &part->pos, &fade->velocity);

    part->rgba = (part->rgba & 0xFFFFFF) + (((fade->alpha * fade->timer) / fade->duration) << 24);

    if (FastDecTimer(fade->timer) != 0)
        DeletePart(part);
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_028);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_029);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", func_00283400);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_030);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_031);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", func_00283BE0);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_032);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_032);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_033);

int FastDecTimer(short &timer);
void DeletePart(PartInstance *part);

void UpdatePart_034(PartInstance *part)
{
    if (FastDecTimer(part->timer))
        DeletePart(part);
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_034);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_035);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_035);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_036);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", func_002848F0);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_037);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", func_00284A58);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_038);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_039);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_040);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_040);

void UpdatePart_041(PartInstance *particle)
{
    Vec4 nextPosition;
    Vec4 probeStart;
    COLL_DAM_IN damage;
    Vec4 collisionOffset;
    PartSplittingMotion *motion;
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

    motion = &particle->splittingMotion;
    if (particle->timer != 0 && FastDecTimer(particle->timer) != 0) {
        float positionSpread, minVelocityScale, maxVelocityScale, velocitySpread, zeroVelocity,
            minPositionSpread;
        motion->flags |= PART_SPLIT_FADING | PART_SPLIT_CHILD;
        minVelocityScale = 0.5f;
        positionSpread = particle->scale / 900000.0f;
        maxVelocityScale = 0.7f;
        velocitySpread = 0.2f;
        particle->scale = particle->scale * 0.8f;
        zeroVelocity = 0.0f;
        factor = MB_randRangeFloat(minVelocityScale, maxVelocityScale);
        minPositionSpread = -positionSpread;
        FastVec3Scale(&nextPosition, &motion->velocity, factor);
        probeStart.x = particle->pos.x + MB_randRangeFloat(minPositionSpread, positionSpread);
        probeStart.y = particle->pos.y + MB_randRangeFloat(minPositionSpread, positionSpread);
        probeStart.z = particle->pos.z + MB_randRangeFloat(minPositionSpread, positionSpread);
        nextPosition.x = nextPosition.x +
                         MB_randRangeFloat(-particle->splittingMotion.velocity.x * velocitySpread,
                                           particle->splittingMotion.velocity.x * velocitySpread);
        nextPosition.y = nextPosition.y + MB_randRangeFloat(-motion->velocity.y * velocitySpread,
                                                            motion->velocity.y * velocitySpread);
        nextPosition.z =
            nextPosition.z + MB_randRangeFloat(-motion->velocity.z * velocitySpread, zeroVelocity);
        spawnedParticle = SpawnPart_040(&probeStart, &nextPosition,
                                        PART_SPLIT_FADING | PART_SPLIT_CHILD, motion->owner);
        if (spawnedParticle != 0) {
            spawnedParticle->timer = FastScaleRoundInt(2);
            spawnedParticle->scale = particle->scale;
        }
        FastVec3Scale(&motion->velocity, &motion->velocity,
                      MB_randRangeFloat(minVelocityScale, maxVelocityScale));
        particle->splittingMotion.velocity.x =
            particle->splittingMotion.velocity.x +
            MB_randRangeFloat(-particle->splittingMotion.velocity.x * velocitySpread,
                              particle->splittingMotion.velocity.x * velocitySpread);
        motion->velocity.y =
            motion->velocity.y + MB_randRangeFloat(-motion->velocity.y * velocitySpread,
                                                   motion->velocity.y * velocitySpread);
        motion->velocity.z = motion->velocity.z +
                             MB_randRangeFloat(-motion->velocity.z * velocitySpread, zeroVelocity);
        particle->pos.x = particle->pos.x + MB_randRangeFloat(minPositionSpread, positionSpread);
        particle->pos.y = particle->pos.y + MB_randRangeFloat(minPositionSpread, positionSpread);
        particle->pos.z = particle->pos.z + MB_randRangeFloat(minPositionSpread, positionSpread);
    }

    textureFrames = PartTextures[PART_TEXTURE_SPLITTING];
    particle->tex = textureFrames[(particle->timer + motion->fadeFrames +
                                   ((unsigned char)particle->tex - textureFrames[0])) &
                                  7];
    FastVec3Add(&nextPosition, &particle->pos, &motion->velocity);
    age = motion->age;
    if (FastScaleRoundInt(3) < age)
        FastSubVec3(&probeStart, &particle->pos, &motion->velocity);

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
        owner = motion->owner;
        start = &probeStart;
        end = &nextPosition;
        collisionFlags = PART_SPLIT_COLLISION_NO_DAMAGE;
        damageInput = 0;
    }

    else {
        damage.pMoby = motion->owner;
        damage.damageFlags = PART_SPLIT_DAMAGE_FLAGS;
        damage.damageHp = 1.0f;
        CopyVec4(&damage.momentum, &motion->velocity);
        if (motionFlags & PART_SPLIT_NO_MOMENTUM)
            FastVecZero(&damage.momentum);
        damage.flags = 1;
        owner = motion->owner;
        damageInput = &damage;
        start = &probeStart;
        end = &nextPosition;
        collisionFlags = 0;
    }

    hitCollision = CollLine(start, end, collisionFlags, owner, damageInput) != 0;
    if (hitCollision) {
        FastVec3Normalize(&collisionOffset, &MemSlots.collisionNormal, 1.0f);
        FastVec3NormalizeFrom(&motion->velocity, &motion->velocity, &MemSlots.collisionNormal);
        FastVec3Scale(&motion->velocity, &motion->velocity, 0.02f);
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
        motion->fadeFrames++;
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

    factor = FastIntToFloat(motion->age);
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
        alpha = alpha / ((float)motion->fadeFrames / 7.0f + 1.0f);

    particle->rgba = (particle->rgba & 0xFFFFFF) | (FastFloatToInt(alpha * 256.0f) << 24);
    motion->velocity.z = motion->velocity.z + transStepScaleSq * 0.008f;
    dampingAge = motion->age;
    if (FastScaleRoundInt(25) < dampingAge || (motion->flags & PART_SPLIT_FADING)) {
        motion->velocity.x = motion->velocity.x * 0.95f;
        motion->velocity.y = motion->velocity.y * 0.95f;
    }

    rotationFlags = motion->flags;
    rotationSign = -1.0f;
    if (rotationFlags & PART_SPLIT_REVERSE_ROTATION)
        rotationSign = 1.0f;
    if (rotationFlags & PART_SPLIT_FADING) {
        motion->velocity.z = motion->velocity.z + transStepScaleSq * 0.008f;
        factor = FastIntToFloat(motion->fadeFrames);
        motion->rotation = motion->rotation + rotationSign * (transStepScale * -0.01f) / factor;
    }

    else {
        motion->rotation = motion->rotation + rotationSign * (transStepScale * -0.01f);
    }

    if (1.0f < motion->rotation)
        motion->rotation = motion->rotation - 1.0f;
    if (motion->rotation < 0.0f)
        motion->rotation = motion->rotation + 1.0f;

    particle->rot = (int)(motion->rotation * 256.0f);
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_041);

void UpdatePart_042(PartInstance *part)
{
    if (part->timer != -1 && FastDecTimer(part->timer))
        DeletePart(part);
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_042);

void UpdatePart_043(PartInstance *particle)
{
    Vec4 nextPosition, probeStart;
    COLL_DAM_IN damage;
    PartSplittingMotion *motion = &particle->splittingMotion;
    PartInstance *spawnedParticle;
    float positionSpread, minPositionSpread, alpha, factor;
    int hitCollision;
    unsigned char motionFlags;

    if (particle->timer != 0 && FastDecTimer(particle->timer)) {
        motion->flags |= PART_SPLIT_FADING | PART_SPLIT_CHILD;
        positionSpread = particle->scale / 900000.0f;
        particle->scale *= 0.8f;
        minPositionSpread = -positionSpread;
        FastVec3Scale(&nextPosition, &motion->velocity, MB_randRangeFloat(0.5f, 0.7f));
        probeStart.x = particle->pos.x + MB_randRangeFloat(minPositionSpread, positionSpread);
        probeStart.y = particle->pos.y + MB_randRangeFloat(minPositionSpread, positionSpread);
        probeStart.z = particle->pos.z + MB_randRangeFloat(minPositionSpread, positionSpread);
        nextPosition.x += MB_randRangeFloat(-motion->velocity.x * 0.2f, motion->velocity.x * 0.2f);
        nextPosition.y += MB_randRangeFloat(-motion->velocity.y * 0.2f, motion->velocity.y * 0.2f);
        nextPosition.z += MB_randRangeFloat(-motion->velocity.z * 0.2f, 0.0f);
        spawnedParticle = SpawnPart_042(&probeStart, &nextPosition,
                                        PART_SPLIT_FADING | PART_SPLIT_CHILD, motion->owner);
        if (spawnedParticle) {
            spawnedParticle->timer = FastScaleRoundInt(2);
            spawnedParticle->scale = particle->scale;
        }
        FastVec3Scale(&motion->velocity, &motion->velocity, MB_randRangeFloat(0.5f, 0.7f));
        motion->velocity.x +=
            MB_randRangeFloat(-motion->velocity.x * 0.2f, motion->velocity.x * 0.2f);
        motion->velocity.y +=
            MB_randRangeFloat(-motion->velocity.y * 0.2f, motion->velocity.y * 0.2f);
        motion->velocity.z += MB_randRangeFloat(-motion->velocity.z * 0.2f, 0.0f);
        particle->pos.x += MB_randRangeFloat(minPositionSpread, positionSpread);
        particle->pos.y += MB_randRangeFloat(minPositionSpread, positionSpread);
        particle->pos.z += MB_randRangeFloat(minPositionSpread, positionSpread);
    }

    particle->tex =
        PartTextures[PART_TEXTURE_SPLITTING]
                    [(particle->timer + motion->fadeFrames +
                      ((unsigned char)particle->tex - PartTextures[PART_TEXTURE_SPLITTING][0])) &
                     7];
    FastVec3Add(&nextPosition, &particle->pos, &motion->velocity);
    hitCollision = 0;
    if (motion->age > FastScaleRoundInt(3))
        FastSubVec3(&probeStart, &particle->pos, &motion->velocity);

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
            hitCollision = CollLine(&probeStart, &nextPosition, 0, motion->owner, 0) != 0;
    }

    else {
        damage.pMoby = motion->owner;
        damage.damageHp = 1.0f;
        CopyVec4(&damage.momentum, &motion->velocity);
        damage.damageFlags = 1;
        damage.flags = 1;
        if (!MB_randInt(3))
            hitCollision = CollLine(&probeStart, &nextPosition, 0, motion->owner, &damage) != 0;
    }

    if (hitCollision)
        motion->flags |= PART_SPLIT_FADING;

    else
        CopyVec4Inline(&particle->pos, &nextPosition);

    if (motion->flags & PART_SPLIT_FADING) {
        motion->fadeFrames++;
        particle->scale -=
            260000.0f / (float)(int)(8.0f / (transStepScale * 0.443f)) * transStepScale * 1.25f;
        if (particle->scale <= 0.0f) {
            DeletePart(particle);
            return;
        }
    }

    else
        particle->scale +=
            260000.0f / (float)(int)(8.0f / (transStepScale * 0.443f)) * transStepScale;

    factor = FastIntToFloat(motion->age);
    {
        float divisor = (float)(int)(8.0f / (transStepScale * 0.443f));
        alpha = 0.08f / divisor * transStepScale * (factor / divisor) + 0.08f;
    }
    if (alpha < 0.0f)
        alpha = 0.0f;
    if (0.08f < alpha)
        alpha = 0.08f;
    if (motion->flags & PART_SPLIT_FADING)
        alpha /= (float)motion->fadeFrames / 7.0f + 1.0f;

    particle->rgba = (particle->rgba & 0xFFFFFF) | (FastFloatToInt(alpha * 256.0f) << 24);
    motion->velocity.z += transStepScaleSq * 0.008f;
    if (motion->age > FastScaleRoundInt(0x19) || (motion->flags & PART_SPLIT_FADING)) {
        motion->velocity.x *= 0.95f;
        motion->velocity.y *= 0.95f;
    }

    {
        unsigned char rotationFlags = motion->flags;
        factor = -1.0f;
        if (rotationFlags & PART_SPLIT_REVERSE_ROTATION)
            factor = 1.0f;
        if (rotationFlags & PART_SPLIT_FADING) {
            motion->velocity.z += transStepScaleSq * 0.008f;
            motion->rotation +=
                factor * (transStepScale * -0.01f) / FastIntToFloat(motion->fadeFrames);
        }

        else
            motion->rotation += factor * (transStepScale * -0.01f);
    }

    if (1.0f < motion->rotation)
        motion->rotation -= 1.0f;
    if (motion->rotation < 0.0f)
        motion->rotation += 1.0f;

    particle->rot = (int)(motion->rotation * 256.0f);
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_044);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_044);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_045);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_045);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_046);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_046);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_047);

PartInstance *SpawnPart_047(Vec4 *position, Vec4 *velocity, float scale)
{
    PartInstance *part = CreatePart(0x2F);

    if (part != 0) {
        CopyVec4Inline(&part->pos, position);

        part->rgba = ((MB_randInt(8) + 0x28) << 0x18) | 0x808080;
        part->draw_dist = FastFloatToInt(2.0f) + 0x20;

        part->gs_alpha = 0x48;
        part->type = 0;
        part->tex = *PartTextures[0x2F];
        part->scale = scale;

        CopyVec4Inline(&part->motion20.origin, velocity);
        part->rot = MB_randInt(0x100);
    }

    return part;
}

void UpdatePart_048(PartInstance *part)
{
    PartSpinMotion *motion = &part->spinMotion;
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

void UpdatePart_049(PartInstance *part)
{
    PartTweenSpin *spin = &part->tweenSpin;

    part->rot += spin->rotationStep;
    FastVec3Add(&part->pos, &part->pos, &spin->velocity);

    part->rgba = FastTweenColor(spin->colorA, spin->colorB, FastAbsF(FastIntToFloat(part->timer) * spin->rate - 1.0f));

    if (FastDecTimer(part->timer) != 0)
        DeletePart(part);
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_050);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", func_00286F88);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_051);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_052);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_052);

void UpdatePart_053(PartInstance *part)
{
    if (FastDecTimer(part->timer))
        DeletePart(part);

    else {
        PartScaleFade *fade = &part->scaleFade;
        float fraction = FastIntToFloat(part->timer) * fade->rate;

        part->rgba = FastTweenColor(fade->endColor, fade->startColor, fraction);
        part->scale = ((fade->startScale - fade->endScale) * fraction + fade->endScale) * 210000.0f;
    }
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_053);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_054);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", func_002876F8);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_055);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_055);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_056);

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
        part->tex = *PartTextures[0x38];
        part->scale = scale;

        CopyVec4Inline(&part->motion20.origin, velocity);
        part->rot = MB_randInt(0x100);
    }

    return part;
}

void UpdatePart_057(PartInstance *part)
{
    PartSpinMotion *motion = &part->spinMotion;
    FastVec3Scale(&motion->velocity, &motion->velocity, 0.975f);
    FastVec3Add(&part->pos, &part->pos, &motion->velocity);

    part->scale += 6300.0f;
    int intensity = (part->rgba & 0xFF) - 4;
    if (intensity <= 0)
        DeletePart(part);
    else
        part->rgba = 0x60000000 | (intensity << 16) | (intensity << 8) | intensity;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_057);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_058);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_058);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_059);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_059);

enum { PART_RELATIVE_TO_HERO = 1 };

void UpdatePart_060(PartInstance *part)
{
    PartSpinMotion *motion = &part->spinMotion;
    if (motion->relativeToHero == PART_RELATIVE_TO_HERO)
        FastVec3Add(&part->pos, &Hero.position, &motion->velocity);

    if (FastDecTimer(part->timer))
        DeletePart(part);
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_060);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_061);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_062);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_062);

void UpdatePart_063(PartInstance *part)
{
    PartFollowFade *fade = &part->followFade;
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

void UpdatePart_064(PartInstance *part)
{
    if (FastDecTimer(part->timer))
        DeletePart(part);
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_064);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_065);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_066);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_066);

void UpdatePart_067(PartInstance *part)
{
    PartFadingMotion *motion = &part->fadingMotion;
    int timer;

    FastVec3Add(&part->pos, &part->pos, &motion->velocity);

    part->scale += motion->scaleStep;
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

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_068);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", func_00289CB8);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_069);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_070);

void UpdatePart_071(PartInstance *part)
{
    if (--part->timer == 0) {
        part->rgba -= 1 << 24;
        part->timer = 2;
    }

    if (!(part->rgba & 0xFF000000))
        DeletePart(part);
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", func_0028A0D8);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_072);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_072);

void UpdatePart_073(PartInstance *part)
{
    part->rot += part->rotationMotion.rotationStep;
    if (part->scale <= 0.0f) {
        part->scale = 0.0f;
        DeletePart(part);
    }
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_074);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_074);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_075);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", func_0028AAE0);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_076);

int PartFadeAlphaStep = 19;

void UpdatePart_077(PartInstance *part)
{
    DecAlpha(&part->rgba, PartFadeAlphaStep);

    if (FastDecTimer(part->timer) != 0)
        DeletePart(part);
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", func_0028AC50);

typedef int Vec4Quad __attribute__((mode(TI)));

void UpdatePart_078(PartInstance *part)
{
    Vec4 origin;
    float duration;
    float fraction;

    *(Vec4Quad *)&origin = *(Vec4Quad *)&part->motion20.origin;

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

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_079);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_080);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_081);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", func_0028B408);
