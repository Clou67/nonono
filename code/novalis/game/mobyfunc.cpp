#include "common.h"
#include "vuchain.h"
#include "fastfunc.h"
#include "moby.h"
#include "mobyutil.h"
#include "hero.h"
#include "draw.h"
#include "sce.h"
#include "sound.h"
#include "music.h"
#include "mathfunc_inline.h"
#include "initlevel.h"

extern int worldUpdateTime;
extern MobyInstance *MobyInstancePermEnd;
extern MobyInstance *MobyInstanceEnd;
extern MobyInstance *MobyInstances;
extern int numSpawnableMobys;
void UpdateMobyFrameData(MobyInstance *moby);

void UpdateNumSpawnableMobys(void)
{
    MobyInstance *moby;
    bool pastEnd = false;

    numSpawnableMobys = 0;

    for (moby = MobyInstancePermEnd; moby < MobyInstanceEnd; moby++) {
        if (moby->state >= 0xfe && moby->lights <= (unsigned long long)(unsigned int)worldUpdateTime || pastEnd) {
            numSpawnableMobys++;

            if (moby->state == 0xff) {
                pastEnd = true;
            }
        }
    }
}

extern unsigned char *mobyVars;

extern void *MobyClassUpdate[];

void InitMobyInstance(MobyInstance *moby, int oClass);

MobyInstance *CreateMoby(int oClass)
{
    for (MobyInstance *moby = MobyInstancePermEnd; moby < MobyInstanceEnd; ++moby) {
        unsigned char state = moby->state;
        if (state < 0xFE)
            continue;

        if (moby->lights > (unsigned int)worldUpdateTime)
            continue;

        if (state == 0xFF)
            moby[1].state = state;

        InitMobyInstance(moby, oClass);

        void *vars = mobyVars + (moby - MobyInstancePermEnd) * 0x80;
        moby->pVar = vars;
        FastMemSet(vars, 0, 0x80);

        if (numSpawnableMobys != 0)
            --numSpawnableMobys;

        return moby;
    }

    printf_stub("Tried to create moby and couldn't. Time: %d, oClass: %d\n", worldUpdateTime, oClass);
    return 0;
}

void InitMobyInstance(MobyInstance *moby, int oClass)
{
    int index;
    MobyClass *mobyClass;
    unsigned char classIndex;

    FastMemSet(moby, 0, 0x100);
    classIndex = MobyClassLookup[oClass];

    moby->alpha = 0x80;
    moby->mClass = classIndex;
    moby->damage = 0xFF;
    moby->group = 0xFF;
    moby->unk71 = 0xFF;
    moby->lodTransition = 0xFF;
    moby->oClass = oClass;
    moby->lights = (((unsigned long long)0x8080 << 0x10) | 0x8000) << 0x17;

    index = ((char *)moby - (char *)MobyInstances) >> 8;
    moby->occlIndex = 0x7F80;
    moby->handle = index << 0x10;
    moby->index = index;

    moby->trigsCnt = 0;
    moby->soundDesired = 0xFF;
    moby->gridMinX = 0x7F;
    moby->gridMaxX = 0x80;
    moby->soundChannel = 0xFF;
    moby->gridMinY = 0x7F;
    moby->gridMaxY = 0x80;

    moby->pUpdate = MobyClassUpdate[moby->mClass];
    if (moby->pUpdate == 0)
        moby->modeBits |= NO_UPDATE;

    mobyClass = MobyClasses[moby->mClass];
    if (mobyClass != 0) {
        moby->pClass = mobyClass;
        moby->lodTransition = mobyClass->lodTransition;
        moby->modeBits |= mobyClass->modeBits;
        moby->collision = (unsigned short *)mobyClass->collision;
        moby->scale = mobyClass->scale;
        moby->animIScale = 1.0f;
        moby->animSpeed = 1.0f;

        if (mobyClass->glowRgba != 0) {
            moby->modeBits |= HAS_GLOW;
            moby->glowRgba = mobyClass->glowRgba;
        }

        if (moby->pClass->shadowCount != 0) {
            moby->shadow = 0x18;
            moby->modeBits |= DRAW_SHADOW;
            moby->shadowPlane = 0;
            moby->shadowRange = 0;
            moby->shadowIndex = 0;
        }

        if (moby->pClass->metalCount != 0)
            moby->metal = 0x18;

        if (moby->pClass->animations[0] == 0)
            return;

        UpdateMobyFrameData(moby);
        if (moby->pClass->animations[0]->frameCount >= 2)
            moby->modeBits &= ~NO_UPDATE;

        if (moby->pClass->sequenceCount == 1) {
            if (moby->pClass->animations[0]->frameCount < 2) {
                moby->animIScale = 0.0f;

                if (moby->pClass->animations[0]->sound < 0)
                    moby->modeBits |= UNK_40;
            }
        }

        return;
    }

    moby->pClass = 0;
    moby->modeBits |= DISABLED | NO_POST_UPDATE;
    moby->collision = 0;
}


void UpdateMobyGrids(MobyInstance *moby, unsigned int bounds);

void DeleteMoby(MobyInstance *moby)
{
    if (moby < MobyInstancePermEnd)
        moby->state = 0xFD;

    else
        moby->state = 0xFE;

    moby->lights = (unsigned long long)(worldUpdateTime + 2);
    UpdateMobyGrids(moby, 0x80807F7F);
}

extern unsigned char debugFontBuffer[] __attribute__((section(".data")));

void UpdateMobyFrameData(MobyInstance *moby)
{
    MobyClass *mobyClass;

    if (moby->updateId != 0xFF) {
        mobyClass = moby->pClass;
        moby->pPreviousAnimationData = mobyClass->animations[moby->updateId]->frames[moby->previousAnimationFrame];
        moby->trigsCnt = mobyClass->animations[moby->updateId]->triggerCount;
        moby->soundDesired = mobyClass->animations[moby->updateId]->sound;
    } else {
        moby->soundDesired = moby->updateId;
        moby->trigsCnt = 0;
        moby->pPreviousAnimationData = (void *)&((unsigned char *)debugFontBuffer)[moby->previousAnimationFrame << 11];
    }

    moby->pCurrentAnimationData =
        moby->pClass->animations[moby->animationId]->frames[moby->animationFrame];
}

void MB_PlayMobyDesiredSound(MobyInstance* pMoby) {
    int channel;
    SoundAudioState* state;

    if (pMoby->soundChannel != 0xFF) {
        channel = pMoby->soundChannel;
        state = (SoundAudioState*)((SoundVoice*)&audioState + channel);

        if (state->voices[0].pMoby != pMoby)
            pMoby->soundChannel = 0xFF;
            
        else if (state->voices[0].soundId != pMoby->soundDesired) {
            sound_KillChannel(channel);
            pMoby->soundChannel = 0xFF;
        }
        
    } 
    else if (pMoby->soundDesired != 0xFF)
        pMoby->soundChannel = sound_PlayMobySound(pMoby->soundDesired, 4, pMoby);
    
}

enum { ANIM_TICKS_PER_FRAME = 16 };

int MB_FindNearestAnimTrigger(MobySeq *sequence, float time)
{
    short key = FastFloatToInt(time * ANIM_TICKS_PER_FRAME);
    for (int index = 0; index < sequence->frameCount; ++index) {
        int frameTime = sequence->frames[index]->time;
        if (frameTime > key) {
            if (index > 0 && key - sequence->frames[index - 1]->time < frameTime - key)
                --index;
            return index;
        }
    }
    return -1;
}

TEXT_PADDING(0x27BD0050, 0x00000000);

float MB_BlendAnimFrame(MobyInstance *moby)
{
    MobySeqFrame *frame;

    if (moby->updateId != 0xFF)
        frame = (MobySeqFrame *)moby->pPreviousAnimationData;
    else
        frame = (MobySeqFrame *)moby->pCurrentAnimationData;

    if (moby->animationBlend == 0.0f)
        return FastIntToFloat(frame->time) * 0.0625f;

    if (moby->updateId != moby->animationId ||
        moby->previousAnimationFrame > moby->animationFrame) {
        return FastIntToFloat(frame->time) * 0.0625f + moby->animationBlend;
    } else {
        MobySeqFrame *previous = (MobySeqFrame *)moby->pCurrentAnimationData;
        float blendedTime = FastIntToFloat(frame->time) * (1.0f - moby->animationBlend);
        return (blendedTime + FastIntToFloat(previous->time) * moby->animationBlend) * 0.0625f;
    }
}

TEXT_PADDING(0x27BD0010, 0x00000000, 0x27BD0010, 0x00000000);

void FastSubVec3(Vec4 *out, Vec4 *first, Vec4 *second);
void FastTransformVec4(Vec4 *out, Vec4 *in, Mtx4 *matrix);
void FastVec3Add(Vec4 *out, Vec4 *first, Vec4 *second);
void FastEulerToMtx1(Mtx4 *out, Vec4 *euler);
void FastScaleVec4(float scale, Vec4 *out, Vec4 *in);
void FastVec3Scale(float scale, Vec4 *out, Vec4 *in);
float FastVec3Length2(Vec4 *vector);
void MobyComputeJointMtxs(MobyInstance *moby, int count, Mtx4 *out);
#define SPAD_JOINTS ((Vec4 *)0x70000000)

int MB_GetCollPrimWorld(MobyInstance* pMoby, int idx, unsigned int* pType, Vec4* pCenter, float* pRadius, float* pLength) {
    CollPrim* primitive = (CollPrim*)pMoby->collision;
    float scale;
    Mtx4 rot;

    if (primitive == 0) {
        return 0;
    }

    /* skip the 0x10-byte MobyCollHeader, then index 32-byte prims */
    primitive = (CollPrim*)((unsigned char*)primitive + 0x10) + idx;
    *pType = primitive->collType;
    scale = pMoby->scale * 0.0009765625f;   /* 1/1024 */

    FastEulerToMtx1(&rot, &pMoby->rotation);

    if (*pType < 2 || *pType == COLLPRIM_PILL) {
        CopyVec4Inline(pCenter, &primitive->offset);
        FastVec3Scale(scale, pCenter, pCenter);
        FastTransformVec4(pCenter, pCenter, &rot);
        FastVec3Add(pCenter, pCenter, &pMoby->pos);
        *pRadius = pCenter->w * scale;

        if (*pType < 2) {
            *pLength = 0.0f;
        } else {
            *pLength = primitive->length * scale;
        }
        return 1;
    }

    if (*pType == COLLPRIM_JOINT) {
        if (pMoby->pCollPrims->primSetB != 0) {
            MobyComputeJointMtxs(pMoby, pMoby->pCollPrims->primSetB, 0);
        }
        CopyVec4Inline(pCenter, &SPAD_JOINTS[primitive->joint]);
        FastVec3Scale(scale, pCenter, pCenter);
        FastTransformVec4(pCenter, pCenter, &rot);
        FastVec3Add(pCenter, pCenter, &pMoby->pos);
        *pRadius = primitive->radius * scale;
        *pLength = 0.0f;
        return 1;
    }

    if (*pType == COLLPRIM_CAPSULE) {
        Vec4 a, b;

        if (pMoby->pCollPrims->primSetB != 0) {
            MobyComputeJointMtxs(pMoby, pMoby->pCollPrims->primSetB, 0);
        }
        JointPair *joints = (JointPair *)&primitive->joint;
        FastScaleVec4(scale, &a, &SPAD_JOINTS[joints->a]);
        FastScaleVec4(scale, &b, &SPAD_JOINTS[joints->b]);

        if (a.z < b.z) {
            CopyVec4Inline(pCenter, &a);
        } else {
            CopyVec4Inline(pCenter, &b);
        }
        FastTransformVec4(pCenter, pCenter, &rot);
        FastVec3Add(pCenter, pCenter, &pMoby->pos);
        *pRadius = primitive->radius * scale;

        FastSubVec3(&b, &b, &a);
        *pLength = FastVec3Length2(&b);
        return 1;
    }
    return 0;
}

void FastMtx3Transpose(Mtx4 *, Mtx4 *);
void FastSubVec3(Vec4 *, Vec4 *, Vec4 *);
void FastTransformVec4(Vec4 *, Vec4 *, Mtx4 *);

void MB_SetCollPrimFromWorld(MobyInstance* pMoby, int idx, Vec4* pos, float rad, float len) {
    Mtx4 mtx;
    Vec4 localPos;
    float invScale;
    CollPrim* prim;

    prim = (CollPrim*)((unsigned char*)pMoby->collision + ((idx << 5) + 0x10));
    invScale = 1024.0f / pMoby->scale;

    FastMtx3Transpose(&mtx, &pMoby->transform);
    FastSubVec3(&localPos, pos, &pMoby->pos);
    FastTransformVec4(&localPos, &localPos, &mtx);
    FastVec3Scale(&localPos, &localPos, invScale);

    CopyVec4Inline(&prim->offset, &localPos);
    prim->length = len * invScale;
    prim->offset.w = rad * invScale;
}

void MB_AddShortPairOffset(MobyClass* pClass, int x, int y) {
    int packetCount = pClass->packetCount0 + pClass->packetCount1;
    unsigned char* packet = (unsigned char*)pClass->packets;

    for (int i = 0; i < packetCount; i++, packet += 16) {
        unsigned short* data = *(unsigned short**)packet;
        int count = ((unsigned char*)data)[2];
        data += 2;

        for (int pair = 0; pair < count; pair++) {
            data[0] += x;
            data[1] += y;
            data += 2;
        }
    }
}

extern unsigned char AnimLayerJointBuf[6][0x1500];
extern AnimLayer AnimLayerPool[6];

enum { NUM_ANIM_LAYERS = 6 };

AnimLayer* MB_AllocAnimLayer(MobyInstance* pMoby, int joint) {
    AnimLayer* layer;
    int i = 0;

    for (i = 0; i < NUM_ANIM_LAYERS; i++) {
        if (!AnimLayerPool[i].inUse)
            break;
    }

    layer = &AnimLayerPool[i];

    layer->inUse = 1;
    layer->joint = joint;
    joint = (short)joint;
    layer->jointBuf = AnimLayerJointBuf[i];
    layer->pClass = pMoby->pClass;

    unsigned char* jointData = ((unsigned char **)pMoby->pClass->animationJoints)[joint + 1];

    layer->jointCount = jointData[2];
    layer->jointMap = jointData + (jointData[0] + 4);

    layer->next = (AnimLayer *)pMoby->pAnimationLayers;
    pMoby->pAnimationLayers = layer;

    return layer;
}

void MB_FreeAnimLayer(MobyInstance *moby, AnimLayer **layerPtr)
{
    AnimLayer *layer;
    if (*layerPtr == 0)
        return;
    if (moby->pAnimationLayers == *layerPtr)
        moby->pAnimationLayers = (*layerPtr)->next;
    else {
        layer = moby->pAnimationLayers;
        while(layer->next != 0 && layer->next != *layerPtr)
            layer = layer->next;
        if(layer->next == *layerPtr)
            layer->next = (*layerPtr)->next;
    }
    FastMemSet(*layerPtr, 0, sizeof(AnimLayer));
    *layerPtr = 0;
}

void MB_BlendJointFrames(AnimLayer *layer);
void MB_InitAnimLayerBuffer(AnimLayer *layer, int seq, int frame, MobySeqFrame *seqFrame);

void MB_UpdateAnimLayer(MobyInstance *moby, AnimLayer *layer) {
    float speed;
    float t, f, len;
    int curFromBuf;

    layer->stepped = 0;
    speed = layer->speed;

    if (speed != 0.0f && layer->frameScale != 0.0f) {
        t = layer->blend + speed * layer->frameScale;
        layer->blend = t;

        if (speed > 0.0f) {
            if (t > 0.99f && t < 1.01f) {
                layer->blend = 1.0f;
            }

            if (layer->blend >= 1.0f) {
                curFromBuf = layer->curFromBuffer;
                do {
                    layer->prevFromBuffer = curFromBuf;
                    layer->stepped |= 1;
                    layer->prevFrame = layer->curFrame;
                    if ((unsigned char)curFromBuf != 0) {
                        layer->prevFrameData = layer->curFrameData;
                    }

                    layer->prevSeq = layer->curSeq;
                    layer->curFrame++;

                    if (layer->curFrame >= layer->pClass->animations[layer->curSeq]->frameCount) {
                        layer->curFrame = 0;
                        layer->stepped |= 2;
                    }

                    f = (layer->blend - 1.0f) / layer->frameScale;
                    layer->blend = f;

                    len = layer->pClass->animations[layer->prevSeq]->frames[layer->prevFrame]->length;
                    layer->frameScale = len;
                    layer->blend = f * len;
                } while (layer->blend >= 1.0f);
            }
        }
    }

    if (layer->prevFromBuffer != 0)
        MB_InitAnimLayerBuffer(layer, layer->prevSeq, layer->prevFrame, (MobySeqFrame *)layer->prevFrameData);
    else
        layer->prevFrameData = layer->pClass->animations[layer->prevSeq]->frames[layer->prevFrame];

    if (layer->curFromBuffer != 0)
        MB_InitAnimLayerBuffer(layer, layer->curSeq, layer->curFrame, (MobySeqFrame *)layer->curFrameData);
    else
        layer->curFrameData = layer->pClass->animations[layer->curSeq]->frames[layer->curFrame];

    MB_BlendJointFrames(layer);
}

void MB_StartAnimLayer(MobyInstance* pMoby, AnimLayer* layer, signed char seq, signed char frame, int frames, int update) 
{
    layer->prevSeq = pMoby->animationId;
    layer->prevFrame = pMoby->animationFrame;
    layer->curSeq = seq;
    layer->curFrame = frame;
    layer->blend = 0;
    layer->speed = 1.0f;
    layer->frameScale = 1.0f / frames;

    if (update != 0) 
        MB_UpdateAnimLayer(pMoby, layer);
    
}


void FastMemSetZero(void *destination, int size);

void MB_InitAnimLayerBuffer(AnimLayer *layer, int seq, int frame, MobySeqFrame *seqFrame)
{
    MobyClass *sourceClass = layer->animClass;
    MobyClass *destinationClass = layer->pClass;
    int sourceJointCount = sourceClass->jointCount;
    int destinationJointCount = destinationClass->jointCount;
    MobySeqFrame *source = sourceClass->animations[seq]->frames[frame];

    FastMemSetZero(seqFrame, ((destinationJointCount + 3) * 8) & 0xFF0);

    int numKeys = destinationJointCount + source->scaleKeys;
    numKeys += source->transKeys;
    seqFrame->jointBytes = destinationJointCount * 8;
    {
        void *restSource = &((unsigned long long *)source)[sourceJointCount + 2];

        seqFrame->qwords = (numKeys + 1) >> 1;
        unsigned short scaleKeys = source->scaleKeys;
        seqFrame->scaleKeys = scaleKeys;
        seqFrame->transOffset = (scaleKeys + destinationJointCount) * 8;
        seqFrame->transKeys = source->transKeys;

        int restBytes = source->qwords * 16 - sourceJointCount * 8;
        if (restBytes != 0)
            FastMemCopy32(&((unsigned long long *)seqFrame)[destinationJointCount + 2], restSource, restBytes);
    }

    unsigned char *jointMap = (unsigned char *)layer->animClass->animationJoints + 4;
    unsigned long long *sourceJoints = source->joints;
    if (sourceJointCount != 0) {
        int remaining = sourceJointCount;
        do {
            remaining--;
            ((unsigned long long *)seqFrame)[*jointMap + 2] = *sourceJoints;
            jointMap++;
            sourceJoints++;
        } while (remaining != 0);
    }

    unsigned long long *lastQword = (unsigned long long *)((char *)seqFrame + seqFrame->qwords * 16);
    if (*lastQword == 0)
        *lastQword = 1;

    FlushCache(0);
}

void AttachManipulator(MobyInstance *moby, int animJoint, Manipulator *manipulator)
{
    if (manipulator->state == 0) {
        manipulator->animJoint = animJoint;
        manipulator->state = 1;

        manipulator->rot.w = 1.0f;
        manipulator->scale.x = 1.0f;
        manipulator->scale.y = 1.0f;
        manipulator->scale.z = 1.0f;

        unsigned char *joint = *(unsigned char **)((unsigned char *)moby->pClass->animationJoints + manipulator->animJoint * 4 + 4);
        manipulator->jointId = joint[*joint + 4] * 0x40 + 0x70000000;

        manipulator->pChain = moby->pManipulators;
        moby->pManipulators = manipulator;
    }
}

void DetachManipulator(MobyInstance *moby, Manipulator *manipulator)
{
    if (manipulator == 0)
        return;

    if (moby->pManipulators == manipulator) {
        moby->pManipulators = manipulator->pChain;
    } else {
        Manipulator *previous = moby->pManipulators;

        for (;;) {
            if (previous->pChain == 0)
                break;
            if (previous->pChain == manipulator)
                break;
            previous = previous->pChain;
        }

        if (previous->pChain == manipulator)
            previous->pChain = manipulator->pChain;
    }

    FastMemSet(manipulator, 0, sizeof(Manipulator));
}

int AnimCache_Register(MobyInstance *moby)
{
    int index = 0;
    MobyInstance **entry = AnimationCacheRegistry;

    for (; index < ANIM_CACHE_COUNT; ++index, ++entry) {
        if (!*entry || *entry == moby) {
            *entry = moby;
            return index;
        }
    }

    return -1;
}

void CleanAnimationCache(void)
{
    for (int slot = 0; slot < ANIM_CACHE_COUNT; ++slot) {
        MobyInstance *moby = AnimationCacheRegistry[slot];
        if (moby != 0 && ((moby->state & 0x80) || moby->updateId != 0xFF))
            AnimationCacheRegistry[slot] = 0;
    }
}

void MobyComputeSelectedJoints(MobyInstance *moby, int count, int *indices, Mtx4 *joints);
void FastMtx3x4Copy(Mtx4 *out, Mtx4 *source);
void FastMtxTransform(Mtx4 *out, Mtx4 *left, Mtx4 *right);
void FastVec3Add(Vec4 *out, Vec4 *first, Vec4 *second);

void MB_GetBoneTransformation(MobyInstance *moby, int index, Mtx4 *out)
{
    Mtx4 world;
    float scale = moby->scale * (1.0f / 1024.0f);

    MobyComputeSelectedJoints(moby, 1, &index, out);
    FastVec3Scale(&out->v3, &out->v3, scale);
    FastMtx3x4Copy(&world, &moby->transform);
    FastMtxTransform(out, &world, out);
    FastVec3Add(&out->v3, &out->v3, &moby->pos);
}

void MobyComputeSelectedJoints(MobyInstance *moby, int count, int *indices, Mtx4 *joints);
void FastVecMtx3Mult(Vec4 *out, Vec4 *vector, Mtx4 *matrix);
void FastVec3Add(Vec4 *out, Vec4 *first, Vec4 *second);

void MB_GetBonePos(MobyInstance *moby, int index, Vec4 *out)
{
    Mtx4 joint;
    float scale = moby->scale * (1.0f / 1024.0f);

    MobyComputeSelectedJoints(moby, 1, &index, &joint);
    FastVec3Scale(out, &joint.v3, scale);
    FastVecMtx3Mult(out, out, &moby->transform);
    FastVec3Add(out, out, &moby->pos);
}

void MB_ComputeSelectedJointPos(MobyInstance *moby, int count, int *joints, Vec4 *out);
void FastVec3Add(Vec4 *out, Vec4 *left, Vec4 *right);

void GetMobyJointsWorldPos(MobyInstance *moby, int count, int *joints, Vec4 *out)
{
    float scale = moby->scale * (1.0f / 1024.0f);
    MB_ComputeSelectedJointPos(moby, count, joints, out);

    if (count > 0) {
        do {
            FastVec3Scale(out, out, scale);
            FastVecMtx3Mult(out, out, &moby->transform);
            FastVec3Add(out, out, &moby->pos);
            ++out;
        } while (--count);
    }
}

void MB_GetJointsWorldMtx(MobyInstance *moby, int count, int *indices, Mtx4 *joints)
{
    Mtx4 world;
    float scale = moby->scale * (1.0f / 1024.0f);

    FastMtx3x4Copy(&world, &moby->transform);
    MobyComputeSelectedJoints(moby, count, indices, joints);
    for (int index = 0; index < count; ++index) {
        Mtx4 *joint = &joints[index];
        FastMtxTransform(joint, &world, joint);
        FastVec3Scale(&joint->v3, &joint->v3, scale);
        FastVec3Add(&joint->v3, &joint->v3, &moby->pos);
    }
}

extern DmaTag *MobyVu1Marker;
extern int GSloc;
int BuildMobyTextureDma(unsigned int gsBase);

void DmaMobyTextures(void)
{
    DmaTag *start = vu1_bufPtr.tag++;

    VU1_CURSOR(MobyVu1Marker).tag->tag = DMA_TAG_NEXT;
    VU1_CURSOR(MobyVu1Marker).tag->addr = (unsigned int)vu1_bufPtr.tag;
    VU1_CURSOR(MobyVu1Marker).tag->vif0 = 0;
    VU1_CURSOR(MobyVu1Marker).tag->vif1 = 0;

    if (drawConfig.mobys != 0) {
        if (drawConfig.moby_texture_paging != 0) {
            BuildMobyTextureDma(GSloc);
            VU1_texFlush();
        }
    }

    vu1_bufPtr.tag->tag = DMA_TAG_NEXT;
    vu1_bufPtr.tag->addr = (unsigned int)(VU1_CURSOR(MobyVu1Marker).tag + 1);
    vu1_bufPtr.tag->vif0 = 0;
    vu1_bufPtr.tag->vif1 = 0;
    vu1_bufPtr.tag++;

    start->tag = DMA_TAG_NEXT;
    start->addr = (unsigned int)vu1_bufPtr.tag;
    start->vif0 = 0;
    start->vif1 = 0;
}

extern int MobyClassRectify[];
extern GsTextureLoc MobyGsLocStash[256];

#define GS_TEXTURE_ADDRESS_MASK 0xFFFFC000

void PatchMobyGifs(void) {
    int *rectify;
    MobyGifUsage *entry;
    MobyDraw *draw;
    GsTextureLoc *location;
    unsigned char *stash;

    for (rectify = MobyClassRectify; *rectify >= 0; rectify++) {
        entry = (MobyGifUsage *)MobyClasses[*rectify]->gifUsage;

        for (;; entry++) {
            draw = (MobyDraw *)((int)entry->draws & 0x7FFFFFFF);

            for (stash = entry->stash; *stash != 0xFF; stash++) {
                location = &MobyGsLocStash[*stash];

                if (location->base != 0)
                    draw->base_tex = (draw->base_tex & GS_TEXTURE_ADDRESS_MASK) | location->base;

                if (location->mip != 0)
                    (draw + 1)->mip_tex = ((draw + 1)->mip_tex & GS_TEXTURE_ADDRESS_MASK) | location->mip;

                draw++;
            }

            if ((int)entry->draws < 0)
                break;
        }
    }
}

void MB_UpdateLightAngle(void)
{
    Vec4 direction;
    float angle;

    MB_GetLightDirection(Hero.moby, &direction);
    angle = FastArcTan(direction.x, direction.y);

    LightDirection.x = FastAngleSinF(angle) * 0.14f;
    LightDirection.y = FastAngleCosF(angle) * 0.14f;
    LightDirection.z = -0.99f;
}

extern int MobyShadowCnt;
extern int ShadowScratchPad[];
extern Vu1ChainCursor MobyVu1ShadowMarker;

void DrawShadow(int *list);
void ShadowDrawStencil(void);

void ProcessMobyShadows(void)
{
    DmaTag *start;
    DmaTag *tag;

    if (MobyShadowCnt == 0) {
        MobyVu1ShadowMarker.tag->tag = DMA_TAG_CNT;
        MobyVu1ShadowMarker.tag->addr = 0;
        MobyVu1ShadowMarker.tag->vif0 = 0;
        MobyVu1ShadowMarker.tag->vif1 = 0;
        return;
    }

    tag = vu1_bufPtr.tag;
    start = tag;
    tag++;
    vu1_bufPtr.tag = tag;

    MobyVu1ShadowMarker.tag->tag = DMA_TAG_NEXT;
    MobyVu1ShadowMarker.tag->addr = (unsigned int)vu1_bufPtr.tag;
    MobyVu1ShadowMarker.tag->vif0 = 0;
    MobyVu1ShadowMarker.tag->vif1 = 0;

    ShadowDrawStencil();
    DrawShadow(ShadowScratchPad);

    vu1_bufPtr.tag->tag = DMA_TAG_NEXT;
    vu1_bufPtr.tag->addr = (unsigned int)(MobyVu1ShadowMarker.tag + 1);
    vu1_bufPtr.tag->vif0 = 0;
    vu1_bufPtr.tag->vif1 = 0;
    vu1_bufPtr.tag++;

    start->tag = DMA_TAG_NEXT;
    start->addr = (unsigned int)vu1_bufPtr.tag;
    start->vif0 = 0;
    start->vif1 = 0;

    printf_stub2("moby shadow", 8);
}

extern char cs_table[];
void MobyAnimProc(unsigned char *scratchPad, unsigned char *skinBuffer);

void ProcessMobyAnimData(void)
{
    FlushCache(0);
    FastMemCopy16((void *)0x70003800, cs_table, 0x800);
    MobyAnimProc(EngScratchPad, SkinVertexCache);
}

enum { DEFAULT_MOBY_CLASS_DISTANCE = 0x40000000, MOBY_CLASS_DISTS_SIZE = 0x380 };

static int *const MobyClassDists = (int *)0x70003A00;

void InitMobyClassDists(void)
{
    FastMemSet(MobyClassDists, DEFAULT_MOBY_CLASS_DISTANCE, MOBY_CLASS_DISTS_SIZE);
}

void StashMobyClassDists(void)
{
    FastMemCopy16(StashedMobyClassDists, MobyClassDists, MOBY_CLASS_DISTS_SIZE);
}

void RestoreMobyClassDists(void)
{
    FastMemCopy16(MobyClassDists, StashedMobyClassDists, MOBY_CLASS_DISTS_SIZE);
}

extern int mobyVu1State;
extern DmaTag *MobyVu1Marker;
extern int GSloc;
extern int GSbase;
extern int vu1_bufLimit;
extern Vu1ChainCursor MobyVu1ShadowMarker;
extern int MobyBuff;

void DrawMobysSetup(void)
{
    int packet;

    VU1_addDataRef(MobyVU1Data, MobyVu1HeaderData.qwc);
    mobyVu1State = 6;
    VU0_loadMicroProgram(MobyVU0Program);
    VU1_addGSregister(0x47, 0x5360B);

    packet = (int)vu1_bufPtr.bytes;
    VU1_CURSOR(MobyVu1Marker).bytes = (unsigned char *)packet;
    GSloc = GSbase;
    packet += 0x10;
    vu1_bufPtr.bytes = (unsigned char *)packet;

    printf_stub3("moby texs", 1);

    MobyVu1ShadowMarker.tag = 0;
    vu1_bufLimit = (int)SkinVertexCache - 0x10000;
    MobyBuff = (int)EngScratchPad;
}

extern int MobyBuff;
int MobyProc(MobyInstance *moby, int buffer, int count, long full);

void DrawMobyListProc(MobyInstance* moby, int count) {
    VU1_addGSregister(0x47, 0x5360B);
    FlushCache(0);
    RestoreMobyClassDists();
    MobyBuff = MobyProc(moby, MobyBuff, count, 0);
    StashMobyClassDists();
    MobyBuff -= 0x10;
}

extern Vu1ChainCursor MobyVu1ShadowMarker;
extern int MobyTexMarker;

void DmaMobyTextures(void);
void ProcessMobyShadows(void);
void SetMobyTexColors(void);

void DrawMobysCleanup(void)
{
    printf_stub3("moby draw", 3);
    DmaMobyTextures();
    printf_stub2("moby draw", 5);

    if (drawConfig.mobys != 0) {
        ProcessMobyAnimData();
        if (MobyTexMarker != 0)
            SetMobyTexColors();
    }

    printf_stub2("moby skin", 3);

    if (drawConfig.mobys != 0 && MobyVu1ShadowMarker.tag != 0)
        ProcessMobyShadows();
}

extern MobyInstance *MobyInstances;
extern int vu1_bufLimit;

void DrawMobysSetup(void);
void DrawMobysCleanup(void);

void DrawMobys(void)
{
    DrawMobysSetup();

    if (drawConfig.mobys) {
        InitMobyClassDists();
        MobyBuff = MobyProc(MobyInstances, MobyBuff, -1, 1);

        if ((int)vu1_bufPtr.bytes > vu1_bufLimit)
            printf_stub("vu chain overflow - mobys dropped\n");
    }

    DrawMobysCleanup();
}



typedef struct EnvSample {
    Vec4 pos;
    int  colorR;
    int  colorG;
    int  colorB;
    int  lights;
    int  reverbDepth;
    unsigned char   reverbType;
    unsigned char   reverbDelay;
    unsigned char   reverbFeedback;
    unsigned char   hasReverb;
    int  musicTrack;
    int  unk2C;
} EnvSample;

extern int EnvSampleCnt;        // 0x160014
extern EnvSample* EnvSamples;   // 0x160040
extern SoundAudioState audioState;
extern MusicTransition musicTransition;

void MB_SetVarsFromEnvSample(MobyInstance *moby) {
    Vec4 diff;
    float distSq;
    float bestDistSq = 999999.0f;
    int bestIdx = -1;
    int i;

    for (i = 0; i < EnvSampleCnt; i++) {
        FastSubVec3(&diff, &moby->pos, &EnvSamples[i].pos);
        distSq = FastVec3Length2(&diff);

        if (distSq <= 8.0f && distSq < bestDistSq) {
            bestDistSq = distSq;
            bestIdx = i;
        }
    }

    if (bestIdx == -1) {
        printf_stub("TJB - No env sample point found!\n");
        return;
    }

    SetMobyLights(moby, moby->colorManipulator = (EnvSamples[bestIdx].colorB << 16)
                                               + (EnvSamples[bestIdx].colorG << 8)
                                               +  EnvSamples[bestIdx].colorR, 0, 0, 0);

    *(int *)&moby->lights = EnvSamples[bestIdx].lights;

    if (EnvSamples[bestIdx].hasReverb != 0) {
        audioState.reverb_depth = EnvSamples[bestIdx].reverbDepth;
        audioState.reverb_type = EnvSamples[bestIdx].reverbType;
        audioState.reverb_delay = EnvSamples[bestIdx].reverbDelay;
        audioState.reverb_feedback = EnvSamples[bestIdx].reverbFeedback;
        audioState.reverb_commands |= 7;
    }

    if (EnvSamples[bestIdx].musicTrack >= 0) {
        if (musicTransition.primary_bank == 0) {
            if ((*(int *)&musicTransition.unk20[0] & 0xFFFFFF) == 0xFF0000) {
                musicTransition.primary_track = (unsigned short)EnvSamples[bestIdx].musicTrack;
            }
        }
    }
}

extern int Level;
extern unsigned char occlCharTable[][16];

void SetLevelFlag(int flag)
{
    if (flag != 0xFF)
        occlCharTable[Level][flag] = 0xFF;
}

// mobyfunc.cpp's small data after its timer labels, in retail order. Defined last so every function above
// reaches it with lui, as retail does.
int numSpawnableMobys = 0;
int MobyClassIndex = 0;
int MobySdata15FFC4 = 0;
int MobySdata15FFC8 = 0;
DmaTag *MobyVu1Marker = 0;
int MobySdata15FFD0 = 0;
int MobyBuff = 0;
MobyInstance *MobyInstances = 0;
MobyInstance *MobyInstancePermEnd = 0;
MobyInstance *MobyInstanceEnd = 0;
int MobyUpdateChainStart = 0;
unsigned char *mobyVars = 0;
int MobySdata15FFEC = 0;
int MobySdata15FFF0 = 0;
int MobySdata15FFF4 = 0;
int MobyTexMarker = 0;
int MobyShadowCnt = 0;
Vu1ChainCursor MobyVu1ShadowMarker = { 0 };
int savedLevelSoundBank = 0;
int MobyRefCnt = 0;
int MobySdata16000C = 0;
int MobySdata160010 = 0;
int EnvSampleCnt = 0;
int MobySdata160018 = 0;
int MobySdata16001C = 0;
int MobySdata160020 = 0;
int MobySdata160024 = 0;
int MobySdata160028 = 0;
int MobySdata16002C = 0;
int MobySdata160030 = 0;
int MobySdata160034 = 0;
int MobySdata160038 = 0;
int MobySdata16003C = 0;
EnvSample *EnvSamples = 0;
int MobySdata160044 = 0;
int MobySdata160048 = 0;
int MobySdata16004C = 0;
int MobySdata160050 = 0;
int MobySdata160054 = 0;
int MobySdata160058 = 0;
int MobySdata16005C = 0;
int MobySdata160060 = 0;
int MobySdata160064 = 0;
int MobySdata160068 = 0;
int MobySdata16006C = 0;
int MobySdata160070 = 0;
int MobySdata160074 = 0;
int MobySdata160078 = 0;
int MobySdata16007C = 0;
