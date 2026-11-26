#include "common.h"
#include "walk.h"
#include "fastfunc.h"
#include "mobyutil.h"
#include "vuchain.h"
#include "gameglobals.h"

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/walk", walk_GetLegRangeMask__FP10w_2legAnimf);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/walk", walk_ResetLegTwist__FP10w_2legData);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/walk", walk_SolveStepTiming__FP12MobyInstanceP10w_2legData);

// Runs the walker's gait state machine once a frame: picks the next walk, run, hill, jump or landing
// animation from the speed, heading and which feet are planted (contacts, WalkContact bits).
void walk_UpdateStateMachine(float speed, float angle, float accel, MobyInstance *moby,
                             w_2legData *walker, unsigned int contacts)
{
    Vec4 probePos;

    switch (walker->state) {
    case WALK_STATE_IDLE:
        walker->stepZ = 0.0f;

        if (accel > 0.0008f && speed > walker->anims[WALK_ANIM_WALK]->speed * 1.35f) {
            {
                w_2legAnim *anim = walker->anims[WALK_ANIM_RUN];
                int trigger = MB_FindNearestAnimTrigger(moby->pClass->animations[anim->anim],
                                                        (float)anim->fromIdle);
                MB_SetAnimation(moby, anim->anim, trigger, 10);
                walk_ResetLegTwist(walker);
            }

            walker->state = WALK_STATE_RUN;
            walker->onground = walk_GetLegRangeMask(walker->anims[WALK_ANIM_RUN],
                                                    (float)walker->anims[WALK_ANIM_RUN]->fromIdle);
            walker->counter = 0;
        }

        else if (speed > frameTime * 0.21f ||
                 FastDiffRots(moby->rotation.z, angle) > 0.10471976f) {
            walker->counter++;

            if (walker->counter >= 4) {
                {
                    w_2legAnim *anim = walker->anims[WALK_ANIM_WALK];
                    int trigger = MB_FindNearestAnimTrigger(moby->pClass->animations[anim->anim],
                                                            (float)anim->fromIdle);
                    MB_SetAnimation(moby, anim->anim, trigger, 10);
                    walk_ResetLegTwist(walker);
                }

                walker->state = WALK_STATE_WALK;
                walker->onground = walk_GetLegRangeMask(
                    walker->anims[WALK_ANIM_WALK], (float)walker->anims[WALK_ANIM_WALK]->fromIdle);
                walker->counter = 0;
            }
        }

        break;
    case WALK_STATE_WALK:
    case WALK_STATE_UP_A:
    case WALK_STATE_UP_B:
    case WALK_STATE_UP_HIGH:
    case WALK_STATE_UP_A_TOP:
    case WALK_STATE_UP_B_TOP:
        if (contacts & (WALK_CONTACT_FOOT0 | WALK_CONTACT_FOOT1))
            walker->flags &= ~WALK_FLAG_STEP_DOWN;
    case WALK_STATE_DOWN_A:
    case WALK_STATE_DOWN_B:
    case WALK_STATE_DOWN_LOW:
    case WALK_STATE_DOWN_A_END:
    case WALK_STATE_DOWN_B_END: {
        int animSlot = WalkStateAnim[walker->state];

        if (moby->animIScale < 0.25f && FastDiffRots(moby->rotation.z, angle) < 0.09239978f &&
            speed < frameTime * 0.19f) {
            MB_SetAnimation(moby, walker->idle, 0, 10);
            walk_ResetLegTwist(walker);
            walker->state = WALK_STATE_IDLE;
        }

        else if (moby->updateId == walker->anims[animSlot]->anim) {
            float speedThreshold =
                (walker->anims[WALK_ANIM_RUN]->speed + walker->anims[WALK_ANIM_WALK]->speed) *
                0.375f;

            if (speed > speedThreshold && walker->speed > speedThreshold &&
                !(walker->onground & (WALK_CONTACT_HEEL0 | WALK_CONTACT_HEEL1 | WALK_CONTACT_MOVE1 |
                                      WALK_CONTACT_MOVE2))) {
                float currentFrame = MB_BlendAnimFrame(moby);

                int framesToFootUp0 =
                    FastFloatToInt(walker->anims[animSlot]->footUp[0] - currentFrame +
                                   walker->anims[animSlot]->frames) %
                    FastFloatToInt(walker->anims[animSlot]->frames);
                int framesToFootUp1 =
                    FastFloatToInt(walker->anims[animSlot]->footUp[1] - currentFrame +
                                   walker->anims[animSlot]->frames) %
                    FastFloatToInt(walker->anims[animSlot]->frames);
                int runFrame;
                int blendFrames;

                if (framesToFootUp0 < framesToFootUp1)
                    runFrame = FastFloatToInt(walker->anims[WALK_ANIM_RUN]->footUp[0] -
                                              walker->anims[WALK_ANIM_RUN]->frame0);

                else
                    runFrame = FastFloatToInt(walker->anims[WALK_ANIM_RUN]->footUp[1] -
                                              walker->anims[WALK_ANIM_RUN]->frame0);

                runFrame = (runFrame + FastFloatToInt(walker->anims[WALK_ANIM_RUN]->frames)) %
                           FastFloatToInt(walker->anims[WALK_ANIM_RUN]->frames);
                blendFrames = FastFloatToInt(10.0f / (speed / walker->anims[WALK_ANIM_RUN]->speed));
                {
                    float runStartFrame = (float)runFrame;

                    w_2legAnim *anim = walker->anims[WALK_ANIM_RUN];
                    int trigger = MB_FindNearestAnimTrigger(moby->pClass->animations[anim->anim],
                                                            runStartFrame);
                    MB_SetAnimation(moby, anim->anim, trigger, blendFrames);
                    walk_ResetLegTwist(walker);
                }

                walker->state = WALK_STATE_RUN;
            }

            else if (contacts & (WALK_CONTACT_FOOT0 | WALK_CONTACT_FOOT1)) {
                if (walker->flags & WALK_FLAG_JUMP) {
                    walker->flags = (walker->flags & ~WALK_FLAG_JUMP) | WALK_FLAG_JUMPING;
                    walker->stepZ = moby->pos.z;

                    if (contacts & WALK_CONTACT_FOOT0) {
                        int blendFrames =
                            FastFloatToInt(walker->anims[WALK_ANIM_JUMP_B]->footRange[0] * 0.25f /
                                           (speed / walker->anims[WALK_ANIM_JUMP_B]->speed));
                        int startFrame =
                            FastFloatToInt(walker->anims[WALK_ANIM_JUMP_B]->footDown[0] +
                                           walker->anims[WALK_ANIM_JUMP_B]->footRange[0] * 0.125f -
                                           walker->anims[WALK_ANIM_JUMP_B]->frame0) %
                            FastFloatToInt(walker->anims[WALK_ANIM_JUMP_B]->frames);
                        w_2legAnim *anim = walker->anims[WALK_ANIM_JUMP_B];
                        int trigger = MB_FindNearestAnimTrigger(
                            moby->pClass->animations[anim->anim], (float)startFrame);
                        MB_SetAnimation(moby, anim->anim, trigger, blendFrames);
                        walk_ResetLegTwist(walker);
                        walker->state = WALK_STATE_JUMP_B;
                    }

                    else {
                        int blendFrames =
                            FastFloatToInt(walker->anims[WALK_ANIM_JUMP_A]->footRange[1] * 0.25f /
                                           (speed / walker->anims[WALK_ANIM_JUMP_A]->speed));
                        int startFrame =
                            FastFloatToInt(walker->anims[WALK_ANIM_JUMP_A]->footDown[1] +
                                           walker->anims[WALK_ANIM_JUMP_A]->footRange[1] * 0.125f -
                                           walker->anims[WALK_ANIM_JUMP_A]->frame0) %
                            FastFloatToInt(walker->anims[WALK_ANIM_JUMP_A]->frames);
                        w_2legAnim *anim = walker->anims[WALK_ANIM_JUMP_A];
                        int trigger = MB_FindNearestAnimTrigger(
                            moby->pClass->animations[anim->anim], (float)startFrame);
                        MB_SetAnimation(moby, anim->anim, trigger, blendFrames);
                        walk_ResetLegTwist(walker);
                        walker->state = WALK_STATE_JUMP_A;
                    }
                }

                else {
                    float groundHeight;

                    probePos.x = FastAngleSinF(angle) * walker->anims[animSlot]->stride * 0.5f;
                    probePos.y = FastAngleCosF(angle) * walker->anims[animSlot]->stride * 0.5f;
                    probePos.z = 0.0f;

                    if (contacts & WALK_CONTACT_FOOT0)
                        FastVec3Add(&probePos, &probePos, &walker->fpos[1]);

                    else
                        FastVec3Add(&probePos, &probePos, &walker->fpos[3]);

                    groundHeight = MB_CollLineDown(&probePos, 0.5f, 0);
                    walker->stepZ = groundHeight;

                    switch (walker->state) {
                    case WALK_STATE_WALK:
                        if ((groundHeight - probePos.z) + walker->anims[animSlot]->stride * 0.5f *
                                                              FastAngleCosF(walker->yrot) >
                            walker->stepHeight * 0.75f) {
                            if (contacts & WALK_CONTACT_FOOT0) {
                                int blendFrames = FastFloatToInt(
                                    walker->anims[WALK_ANIM_UP_B]->footRange[0] * 0.25f /
                                    (speed / walker->anims[WALK_ANIM_UP_B]->speed));
                                int startFrame =
                                    FastFloatToInt(walker->anims[WALK_ANIM_UP_B]->footDown[0] +
                                                   walker->anims[WALK_ANIM_UP_B]->footRange[0] *
                                                       0.125f -
                                                   walker->anims[WALK_ANIM_UP_B]->frame0) %
                                    FastFloatToInt(walker->anims[WALK_ANIM_UP_B]->frames);
                                w_2legAnim *anim = walker->anims[WALK_ANIM_UP_B];
                                int trigger = MB_FindNearestAnimTrigger(
                                    moby->pClass->animations[anim->anim], (float)startFrame);
                                MB_SetAnimation(moby, anim->anim, trigger, blendFrames);
                                walk_ResetLegTwist(walker);
                                walker->state = WALK_STATE_UP_B;
                            }

                            else {
                                int blendFrames = FastFloatToInt(
                                    walker->anims[WALK_ANIM_UP_A]->footRange[1] * 0.25f /
                                    (speed / walker->anims[WALK_ANIM_UP_A]->speed));
                                int startFrame =
                                    FastFloatToInt(walker->anims[WALK_ANIM_UP_A]->footDown[1] +
                                                   walker->anims[WALK_ANIM_UP_A]->footRange[1] *
                                                       0.125f -
                                                   walker->anims[WALK_ANIM_UP_A]->frame0) %
                                    FastFloatToInt(walker->anims[WALK_ANIM_UP_A]->frames);
                                w_2legAnim *anim = walker->anims[WALK_ANIM_UP_A];
                                int trigger = MB_FindNearestAnimTrigger(
                                    moby->pClass->animations[anim->anim], (float)startFrame);
                                MB_SetAnimation(moby, anim->anim, trigger, blendFrames);
                                walk_ResetLegTwist(walker);
                                walker->state = WALK_STATE_UP_A;
                            }
                        }

                        else if ((groundHeight - probePos.z) + walker->anims[animSlot]->stride *
                                                                   0.5f *
                                                                   FastAngleCosF(walker->yrot) <
                                 -walker->stepHeight * 0.75f) {
                            walker->flags |= WALK_FLAG_STEP_DOWN;

                            if (contacts & WALK_CONTACT_FOOT0) {
                                int blendFrames = FastFloatToInt(
                                    walker->anims[WALK_ANIM_DOWN_B]->footRange[0] * 0.25f /
                                    (speed / walker->anims[WALK_ANIM_DOWN_B]->speed));
                                int startFrame =
                                    FastFloatToInt(walker->anims[WALK_ANIM_DOWN_B]->footDown[0] +
                                                   walker->anims[WALK_ANIM_DOWN_B]->footRange[0] *
                                                       0.125f -
                                                   walker->anims[WALK_ANIM_DOWN_B]->frame0) %
                                    FastFloatToInt(walker->anims[WALK_ANIM_DOWN_B]->frames);
                                w_2legAnim *anim = walker->anims[WALK_ANIM_DOWN_B];
                                int trigger = MB_FindNearestAnimTrigger(
                                    moby->pClass->animations[anim->anim], (float)startFrame);
                                MB_SetAnimation(moby, anim->anim, trigger, blendFrames);
                                walk_ResetLegTwist(walker);
                                walker->state = WALK_STATE_DOWN_B;
                            }

                            else {
                                int blendFrames = FastFloatToInt(
                                    walker->anims[WALK_ANIM_DOWN_A]->footRange[1] * 0.25f /
                                    (speed / walker->anims[WALK_ANIM_DOWN_A]->speed));
                                int startFrame =
                                    FastFloatToInt(walker->anims[WALK_ANIM_DOWN_A]->footDown[1] +
                                                   walker->anims[WALK_ANIM_DOWN_A]->footRange[1] *
                                                       0.125f -
                                                   walker->anims[WALK_ANIM_DOWN_A]->frame0) %
                                    FastFloatToInt(walker->anims[WALK_ANIM_DOWN_A]->frames);
                                w_2legAnim *anim = walker->anims[WALK_ANIM_DOWN_A];
                                int trigger = MB_FindNearestAnimTrigger(
                                    moby->pClass->animations[anim->anim], (float)startFrame);
                                MB_SetAnimation(moby, anim->anim, trigger, blendFrames);
                                walk_ResetLegTwist(walker);
                                walker->state = WALK_STATE_DOWN_A;
                            }
                        }

                        break;
                    case WALK_STATE_UP_A:
                        if ((groundHeight - probePos.z) + walker->anims[animSlot]->stride * 0.5f *
                                                              FastAngleCosF(walker->yrot) <
                            -walker->stepHeight * 0.75f) {
                            int blendFrames;
                            int startFrame;

                            w_2legAnim *anim;
                            int trigger;

                            walker->flags |= WALK_FLAG_STEP_DOWN;
                            blendFrames = FastFloatToInt(
                                walker->anims[WALK_ANIM_DOWN_B]->footRange[0] * 0.25f /
                                (speed / walker->anims[WALK_ANIM_DOWN_B]->speed));
                            startFrame =
                                FastFloatToInt(walker->anims[WALK_ANIM_DOWN_B]->footDown[0] +
                                               walker->anims[WALK_ANIM_DOWN_B]->footRange[0] *
                                                   0.125f -
                                               walker->anims[WALK_ANIM_DOWN_B]->frame0) %
                                FastFloatToInt(walker->anims[WALK_ANIM_DOWN_B]->frames);
                            anim = walker->anims[WALK_ANIM_DOWN_B];
                            trigger = MB_FindNearestAnimTrigger(
                                moby->pClass->animations[anim->anim], (float)startFrame);
                            MB_SetAnimation(moby, anim->anim, trigger, blendFrames);
                            walk_ResetLegTwist(walker);
                            walker->state = WALK_STATE_DOWN_B;
                        }

                        else if ((groundHeight - probePos.z) + walker->anims[animSlot]->stride *
                                                                   0.5f *
                                                                   FastAngleCosF(walker->yrot) <
                                 walker->stepHeight * 0.75f)
                          walker->state = WALK_STATE_UP_A_TOP;

                      else {
                            int blendFrames = FastFloatToInt(
                                walker->anims[WALK_ANIM_UP_HIGH]->footRange[0] * 0.25f /
                                (speed / walker->anims[WALK_ANIM_UP_HIGH]->speed));
                            int startFrame =
                                FastFloatToInt(walker->anims[WALK_ANIM_UP_HIGH]->footDown[0] +
                                               walker->anims[WALK_ANIM_UP_HIGH]->footRange[0] *
                                                   0.125f -
                                               walker->anims[WALK_ANIM_UP_HIGH]->frame0) %
                                FastFloatToInt(walker->anims[WALK_ANIM_UP_HIGH]->frames);
                            w_2legAnim *anim = walker->anims[WALK_ANIM_UP_HIGH];
                            int trigger = MB_FindNearestAnimTrigger(
                                moby->pClass->animations[anim->anim], (float)startFrame);
                            MB_SetAnimation(moby, anim->anim, trigger, blendFrames);
                            walk_ResetLegTwist(walker);
                            walker->state = WALK_STATE_UP_HIGH;
                        }

                        break;
                    case WALK_STATE_UP_B:
                        if ((groundHeight - probePos.z) + walker->anims[animSlot]->stride * 0.5f *
                                                              FastAngleCosF(walker->yrot) <
                            -walker->stepHeight * 0.75f) {
                            int blendFrames;
                            int startFrame;

                            w_2legAnim *anim;
                            int trigger;

                            walker->flags |= WALK_FLAG_STEP_DOWN;
                            blendFrames = FastFloatToInt(
                                walker->anims[WALK_ANIM_DOWN_A]->footRange[1] * 0.25f /
                                (speed / walker->anims[WALK_ANIM_DOWN_A]->speed));
                            startFrame =
                                FastFloatToInt(walker->anims[WALK_ANIM_DOWN_A]->footDown[1] +
                                               walker->anims[WALK_ANIM_DOWN_A]->footRange[1] *
                                                   0.125f -
                                               walker->anims[WALK_ANIM_DOWN_A]->frame0) %
                                FastFloatToInt(walker->anims[WALK_ANIM_DOWN_A]->frames);
                            anim = walker->anims[WALK_ANIM_DOWN_A];
                            trigger = MB_FindNearestAnimTrigger(
                                moby->pClass->animations[anim->anim], (float)startFrame);
                            MB_SetAnimation(moby, anim->anim, trigger, blendFrames);
                            walk_ResetLegTwist(walker);
                            walker->state = WALK_STATE_DOWN_A;
                        }

                        else if ((groundHeight - probePos.z) + walker->anims[animSlot]->stride *
                                                                   0.5f *
                                                                   FastAngleCosF(walker->yrot) <
                                 walker->stepHeight * 0.75f)
                          walker->state = WALK_STATE_UP_B_TOP;

                      else {
                            int blendFrames = FastFloatToInt(
                                walker->anims[WALK_ANIM_UP_HIGH]->footRange[1] * 0.25f /
                                (speed / walker->anims[WALK_ANIM_UP_HIGH]->speed));
                            int startFrame =
                                FastFloatToInt(walker->anims[WALK_ANIM_UP_HIGH]->footDown[1] +
                                               walker->anims[WALK_ANIM_UP_HIGH]->footRange[1] *
                                                   0.125f -
                                               walker->anims[WALK_ANIM_UP_HIGH]->frame0) %
                                FastFloatToInt(walker->anims[WALK_ANIM_UP_HIGH]->frames);
                            w_2legAnim *anim = walker->anims[WALK_ANIM_UP_HIGH];
                            int trigger = MB_FindNearestAnimTrigger(
                                moby->pClass->animations[anim->anim], (float)startFrame);
                            MB_SetAnimation(moby, anim->anim, trigger, blendFrames);
                            walk_ResetLegTwist(walker);
                            walker->state = WALK_STATE_UP_HIGH;
                        }

                        break;
                    case WALK_STATE_UP_HIGH:
                        if ((groundHeight - probePos.z) + walker->anims[animSlot]->stride * 0.5f *
                                                              FastAngleCosF(walker->yrot) <
                            -walker->stepHeight * 0.75f) {
                            walker->flags |= WALK_FLAG_STEP_DOWN;

                            if (contacts & WALK_CONTACT_FOOT0) {
                                int blendFrames = FastFloatToInt(
                                    walker->anims[WALK_ANIM_DOWN_B]->footRange[0] * 0.25f /
                                    (speed / walker->anims[WALK_ANIM_DOWN_B]->speed));
                                int startFrame =
                                    FastFloatToInt(walker->anims[WALK_ANIM_DOWN_B]->footDown[0] +
                                                   walker->anims[WALK_ANIM_DOWN_B]->footRange[0] *
                                                       0.125f -
                                                   walker->anims[WALK_ANIM_DOWN_B]->frame0) %
                                    FastFloatToInt(walker->anims[WALK_ANIM_DOWN_B]->frames);
                                w_2legAnim *anim = walker->anims[WALK_ANIM_DOWN_B];
                                int trigger = MB_FindNearestAnimTrigger(
                                    moby->pClass->animations[anim->anim], (float)startFrame);
                                MB_SetAnimation(moby, anim->anim, trigger, blendFrames);
                                walk_ResetLegTwist(walker);
                                walker->state = WALK_STATE_DOWN_B;
                            }

                            else {
                                int blendFrames = FastFloatToInt(
                                    walker->anims[WALK_ANIM_DOWN_A]->footRange[1] * 0.25f /
                                    (speed / walker->anims[WALK_ANIM_DOWN_A]->speed));
                                int startFrame =
                                    FastFloatToInt(walker->anims[WALK_ANIM_DOWN_A]->footDown[1] +
                                                   walker->anims[WALK_ANIM_DOWN_A]->footRange[1] *
                                                       0.125f -
                                                   walker->anims[WALK_ANIM_DOWN_A]->frame0) %
                                    FastFloatToInt(walker->anims[WALK_ANIM_DOWN_A]->frames);
                                w_2legAnim *anim = walker->anims[WALK_ANIM_DOWN_A];
                                int trigger = MB_FindNearestAnimTrigger(
                                    moby->pClass->animations[anim->anim], (float)startFrame);
                                MB_SetAnimation(moby, anim->anim, trigger, blendFrames);
                                walk_ResetLegTwist(walker);
                                walker->state = WALK_STATE_DOWN_A;
                            }
                        }

                        else if ((groundHeight - probePos.z) + walker->anims[animSlot]->stride *
                                                                   0.5f *
                                                                   FastAngleCosF(walker->yrot) <
                                 walker->stepHeight * 0.75f) {
                            if (contacts & WALK_CONTACT_FOOT0) {
                                int blendFrames = FastFloatToInt(
                                    walker->anims[WALK_ANIM_UP_A]->footRange[0] * 0.25f /
                                    (speed / walker->anims[WALK_ANIM_UP_A]->speed));
                                int startFrame =
                                    FastFloatToInt(walker->anims[WALK_ANIM_UP_A]->footDown[0] +
                                                   walker->anims[WALK_ANIM_UP_A]->footRange[0] *
                                                       0.125f -
                                                   walker->anims[WALK_ANIM_UP_A]->frame0) %
                                    FastFloatToInt(walker->anims[WALK_ANIM_UP_A]->frames);
                                w_2legAnim *anim = walker->anims[WALK_ANIM_UP_A];
                                int trigger = MB_FindNearestAnimTrigger(
                                    moby->pClass->animations[anim->anim], (float)startFrame);
                                MB_SetAnimation(moby, anim->anim, trigger, blendFrames);
                                walk_ResetLegTwist(walker);
                                walker->state = WALK_STATE_UP_A_TOP;
                            }

                            else {
                                int blendFrames = FastFloatToInt(
                                    walker->anims[WALK_ANIM_UP_B]->footRange[1] * 0.25f /
                                    (speed / walker->anims[WALK_ANIM_UP_B]->speed));
                                int startFrame =
                                    FastFloatToInt(walker->anims[WALK_ANIM_UP_B]->footDown[1] +
                                                   walker->anims[WALK_ANIM_UP_B]->footRange[1] *
                                                       0.125f -
                                                   walker->anims[WALK_ANIM_UP_B]->frame0) %
                                    FastFloatToInt(walker->anims[WALK_ANIM_UP_B]->frames);
                                w_2legAnim *anim = walker->anims[WALK_ANIM_UP_B];
                                int trigger = MB_FindNearestAnimTrigger(
                                    moby->pClass->animations[anim->anim], (float)startFrame);
                                MB_SetAnimation(moby, anim->anim, trigger, blendFrames);
                                walk_ResetLegTwist(walker);
                                walker->state = WALK_STATE_UP_B_TOP;
                            }
                        }

                        break;
                    case WALK_STATE_UP_A_TOP:
                        if ((groundHeight - probePos.z) + walker->anims[animSlot]->stride * 0.5f *
                                                              FastAngleCosF(walker->yrot) <
                            -walker->stepHeight * 0.75f) {
                            int blendFrames;
                            int startFrame;

                            w_2legAnim *anim;
                            int trigger;

                            walker->flags |= WALK_FLAG_STEP_DOWN;
                            blendFrames = FastFloatToInt(
                                walker->anims[WALK_ANIM_DOWN_A]->footRange[1] * 0.25f /
                                (speed / walker->anims[WALK_ANIM_DOWN_A]->speed));
                            startFrame =
                                FastFloatToInt(walker->anims[WALK_ANIM_DOWN_A]->footDown[1] +
                                               walker->anims[WALK_ANIM_DOWN_A]->footRange[1] *
                                                   0.125f -
                                               walker->anims[WALK_ANIM_DOWN_A]->frame0) %
                                FastFloatToInt(walker->anims[WALK_ANIM_DOWN_A]->frames);
                            anim = walker->anims[WALK_ANIM_DOWN_A];
                            trigger = MB_FindNearestAnimTrigger(
                                moby->pClass->animations[anim->anim], (float)startFrame);
                            MB_SetAnimation(moby, anim->anim, trigger, blendFrames);
                            walk_ResetLegTwist(walker);
                            walker->state = WALK_STATE_DOWN_A;
                        }

                        else if ((groundHeight - probePos.z) + walker->anims[animSlot]->stride *
                                                                   0.5f *
                                                                   FastAngleCosF(walker->yrot) >
                                 walker->stepHeight * 0.75f)
                          walker->state = WALK_STATE_UP_A;

                      else {
                            int blendFrames =
                                FastFloatToInt(walker->anims[WALK_ANIM_WALK]->footRange[1] * 0.25f /
                                               (speed / walker->anims[WALK_ANIM_WALK]->speed));
                            int startFrame =
                                FastFloatToInt(walker->anims[WALK_ANIM_WALK]->footDown[1] +
                                               walker->anims[WALK_ANIM_WALK]->footRange[1] *
                                                   0.125f -
                                               walker->anims[WALK_ANIM_WALK]->frame0) %
                                FastFloatToInt(walker->anims[WALK_ANIM_WALK]->frames);
                            w_2legAnim *anim = walker->anims[WALK_ANIM_WALK];
                            int trigger = MB_FindNearestAnimTrigger(
                                moby->pClass->animations[anim->anim], (float)startFrame);
                            MB_SetAnimation(moby, anim->anim, trigger, blendFrames);
                            walk_ResetLegTwist(walker);
                            walker->state = WALK_STATE_WALK;
                        }

                        break;
                    case WALK_STATE_UP_B_TOP:
                        if ((groundHeight - probePos.z) + walker->anims[animSlot]->stride * 0.5f *
                                                              FastAngleCosF(walker->yrot) <
                            -walker->stepHeight * 0.75f) {
                            int blendFrames;
                            int startFrame;

                            w_2legAnim *anim;
                            int trigger;

                            walker->flags |= WALK_FLAG_STEP_DOWN;
                            blendFrames = FastFloatToInt(
                                walker->anims[WALK_ANIM_DOWN_B]->footRange[0] * 0.25f /
                                (speed / walker->anims[WALK_ANIM_DOWN_B]->speed));
                            startFrame =
                                FastFloatToInt(walker->anims[WALK_ANIM_DOWN_B]->footDown[0] +
                                               walker->anims[WALK_ANIM_DOWN_B]->footRange[0] *
                                                   0.125f -
                                               walker->anims[WALK_ANIM_DOWN_B]->frame0) %
                                FastFloatToInt(walker->anims[WALK_ANIM_DOWN_B]->frames);
                            anim = walker->anims[WALK_ANIM_DOWN_B];
                            trigger = MB_FindNearestAnimTrigger(
                                moby->pClass->animations[anim->anim], (float)startFrame);
                            MB_SetAnimation(moby, anim->anim, trigger, blendFrames);
                            walk_ResetLegTwist(walker);
                            walker->state = WALK_STATE_DOWN_B;
                        }

                        else if ((groundHeight - probePos.z) + walker->anims[animSlot]->stride *
                                                                   0.5f *
                                                                   FastAngleCosF(walker->yrot) >
                                 walker->stepHeight * 0.75f)
                          walker->state = WALK_STATE_UP_B;

                      else {
                            int blendFrames =
                                FastFloatToInt(walker->anims[WALK_ANIM_WALK]->footRange[0] * 0.25f /
                                               (speed / walker->anims[WALK_ANIM_WALK]->speed));
                            int startFrame =
                                FastFloatToInt(walker->anims[WALK_ANIM_WALK]->footDown[0] +
                                               walker->anims[WALK_ANIM_WALK]->footRange[0] *
                                                   0.125f -
                                               walker->anims[WALK_ANIM_WALK]->frame0) %
                                FastFloatToInt(walker->anims[WALK_ANIM_WALK]->frames);
                            w_2legAnim *anim = walker->anims[WALK_ANIM_WALK];
                            int trigger = MB_FindNearestAnimTrigger(
                                moby->pClass->animations[anim->anim], (float)startFrame);
                            MB_SetAnimation(moby, anim->anim, trigger, blendFrames);
                            walk_ResetLegTwist(walker);
                            walker->state = WALK_STATE_WALK;
                        }

                        break;
                    case WALK_STATE_DOWN_A:
                        if ((groundHeight - probePos.z) + walker->anims[animSlot]->stride * 0.5f *
                                                              FastAngleCosF(walker->yrot) >
                            walker->stepHeight * 0.75f) {
                            int blendFrames =
                                FastFloatToInt(walker->anims[WALK_ANIM_UP_B]->footRange[0] * 0.25f /
                                               (speed / walker->anims[WALK_ANIM_UP_B]->speed));
                            int startFrame =
                                FastFloatToInt(walker->anims[WALK_ANIM_UP_B]->footDown[0] +
                                               walker->anims[WALK_ANIM_UP_B]->footRange[0] *
                                                   0.125f -
                                               walker->anims[WALK_ANIM_UP_B]->frame0) %
                                FastFloatToInt(walker->anims[WALK_ANIM_UP_B]->frames);
                            w_2legAnim *anim = walker->anims[WALK_ANIM_UP_B];
                            int trigger = MB_FindNearestAnimTrigger(
                                moby->pClass->animations[anim->anim], (float)startFrame);
                            MB_SetAnimation(moby, anim->anim, trigger, blendFrames);
                            walk_ResetLegTwist(walker);
                            walker->state = WALK_STATE_UP_B;
                        }

                        else if ((groundHeight - probePos.z) + walker->anims[animSlot]->stride *
                                                                   0.5f *
                                                                   FastAngleCosF(walker->yrot) >
                                 -walker->stepHeight * 0.75f)
                          walker->state = WALK_STATE_DOWN_A_END;

                      else {
                            int blendFrames = FastFloatToInt(
                                walker->anims[WALK_ANIM_DOWN_LOW]->footRange[0] * 0.25f /
                                (speed / walker->anims[WALK_ANIM_DOWN_LOW]->speed));
                            int startFrame =
                                FastFloatToInt(walker->anims[WALK_ANIM_DOWN_LOW]->footDown[0] +
                                               walker->anims[WALK_ANIM_DOWN_LOW]->footRange[0] *
                                                   0.125f -
                                               walker->anims[WALK_ANIM_DOWN_LOW]->frame0) %
                                FastFloatToInt(walker->anims[WALK_ANIM_DOWN_LOW]->frames);
                            w_2legAnim *anim = walker->anims[WALK_ANIM_DOWN_LOW];
                            int trigger = MB_FindNearestAnimTrigger(
                                moby->pClass->animations[anim->anim], (float)startFrame);
                            MB_SetAnimation(moby, anim->anim, trigger, blendFrames);
                            walk_ResetLegTwist(walker);
                            walker->state = WALK_STATE_DOWN_LOW;
                        }

                        break;
                    case WALK_STATE_DOWN_B:
                        if ((groundHeight - probePos.z) + walker->anims[animSlot]->stride * 0.5f *
                                                              FastAngleCosF(walker->yrot) >
                            walker->stepHeight * 0.75f) {
                            int blendFrames =
                                FastFloatToInt(walker->anims[WALK_ANIM_UP_A]->footRange[1] * 0.25f /
                                               (speed / walker->anims[WALK_ANIM_UP_A]->speed));
                            int startFrame =
                                FastFloatToInt(walker->anims[WALK_ANIM_UP_A]->footDown[1] +
                                               walker->anims[WALK_ANIM_UP_A]->footRange[1] *
                                                   0.125f -
                                               walker->anims[WALK_ANIM_UP_A]->frame0) %
                                FastFloatToInt(walker->anims[WALK_ANIM_UP_A]->frames);
                            w_2legAnim *anim = walker->anims[WALK_ANIM_UP_A];
                            int trigger = MB_FindNearestAnimTrigger(
                                moby->pClass->animations[anim->anim], (float)startFrame);
                            MB_SetAnimation(moby, anim->anim, trigger, blendFrames);
                            walk_ResetLegTwist(walker);
                            walker->state = WALK_STATE_UP_A;
                        }

                        else if ((groundHeight - probePos.z) + walker->anims[animSlot]->stride *
                                                                   0.5f *
                                                                   FastAngleCosF(walker->yrot) >
                                 -walker->stepHeight * 0.75f)
                          walker->state = WALK_STATE_DOWN_B_END;

                      else {
                            int blendFrames = FastFloatToInt(
                                walker->anims[WALK_ANIM_DOWN_LOW]->footRange[1] * 0.25f /
                                (speed / walker->anims[WALK_ANIM_DOWN_LOW]->speed));
                            int startFrame =
                                FastFloatToInt(walker->anims[WALK_ANIM_DOWN_LOW]->footDown[1] +
                                               walker->anims[WALK_ANIM_DOWN_LOW]->footRange[1] *
                                                   0.125f -
                                               walker->anims[WALK_ANIM_DOWN_LOW]->frame0) %
                                FastFloatToInt(walker->anims[WALK_ANIM_DOWN_LOW]->frames);
                            w_2legAnim *anim = walker->anims[WALK_ANIM_DOWN_LOW];
                            int trigger = MB_FindNearestAnimTrigger(
                                moby->pClass->animations[anim->anim], (float)startFrame);
                            MB_SetAnimation(moby, anim->anim, trigger, blendFrames);
                            walk_ResetLegTwist(walker);
                            walker->state = WALK_STATE_DOWN_LOW;
                        }

                        break;
                    case WALK_STATE_DOWN_LOW:
                        if ((groundHeight - probePos.z) + walker->anims[animSlot]->stride * 0.5f *
                                                              FastAngleCosF(walker->yrot) >
                            walker->stepHeight * 0.75f) {
                            if (contacts & WALK_CONTACT_FOOT0) {
                                int blendFrames = FastFloatToInt(
                                    walker->anims[WALK_ANIM_UP_B]->footRange[0] * 0.25f /
                                    (speed / walker->anims[WALK_ANIM_UP_B]->speed));
                                int startFrame =
                                    FastFloatToInt(walker->anims[WALK_ANIM_UP_B]->footDown[0] +
                                                   walker->anims[WALK_ANIM_UP_B]->footRange[0] *
                                                       0.125f -
                                                   walker->anims[WALK_ANIM_UP_B]->frame0) %
                                    FastFloatToInt(walker->anims[WALK_ANIM_UP_B]->frames);
                                w_2legAnim *anim = walker->anims[WALK_ANIM_UP_B];
                                int trigger = MB_FindNearestAnimTrigger(
                                    moby->pClass->animations[anim->anim], (float)startFrame);
                                MB_SetAnimation(moby, anim->anim, trigger, blendFrames);
                                walk_ResetLegTwist(walker);
                                walker->state = WALK_STATE_UP_B;
                            }

                            else {
                                int blendFrames = FastFloatToInt(
                                    walker->anims[WALK_ANIM_UP_A]->footRange[1] * 0.25f /
                                    (speed / walker->anims[WALK_ANIM_UP_A]->speed));
                                int startFrame =
                                    FastFloatToInt(walker->anims[WALK_ANIM_UP_A]->footDown[1] +
                                                   walker->anims[WALK_ANIM_UP_A]->footRange[1] *
                                                       0.125f -
                                                   walker->anims[WALK_ANIM_UP_A]->frame0) %
                                    FastFloatToInt(walker->anims[WALK_ANIM_UP_A]->frames);
                                w_2legAnim *anim = walker->anims[WALK_ANIM_UP_A];
                                int trigger = MB_FindNearestAnimTrigger(
                                    moby->pClass->animations[anim->anim], (float)startFrame);
                                MB_SetAnimation(moby, anim->anim, trigger, blendFrames);
                                walk_ResetLegTwist(walker);
                                walker->state = WALK_STATE_UP_A;
                            }
                        }

                        else if ((groundHeight - probePos.z) + walker->anims[animSlot]->stride *
                                                                   0.5f *
                                                                   FastAngleCosF(walker->yrot) >
                                 -walker->stepHeight * 0.75f) {
                            if (contacts & WALK_CONTACT_FOOT0) {
                                int blendFrames = FastFloatToInt(
                                    walker->anims[WALK_ANIM_DOWN_A]->footRange[0] * 0.25f /
                                    (speed / walker->anims[WALK_ANIM_DOWN_A]->speed));
                                int startFrame =
                                    FastFloatToInt(walker->anims[WALK_ANIM_DOWN_A]->footDown[0] +
                                                   walker->anims[WALK_ANIM_DOWN_A]->footRange[0] *
                                                       0.125f -
                                                   walker->anims[WALK_ANIM_DOWN_A]->frame0) %
                                    FastFloatToInt(walker->anims[WALK_ANIM_DOWN_A]->frames);
                                w_2legAnim *anim = walker->anims[WALK_ANIM_DOWN_A];
                                int trigger = MB_FindNearestAnimTrigger(
                                    moby->pClass->animations[anim->anim], (float)startFrame);
                                MB_SetAnimation(moby, anim->anim, trigger, blendFrames);
                                walk_ResetLegTwist(walker);
                                walker->state = WALK_STATE_DOWN_A_END;
                            }

                            else {
                                int blendFrames = FastFloatToInt(
                                    walker->anims[WALK_ANIM_DOWN_B]->footRange[1] * 0.25f /
                                    (speed / walker->anims[WALK_ANIM_DOWN_B]->speed));
                                int startFrame =
                                    FastFloatToInt(walker->anims[WALK_ANIM_DOWN_B]->footDown[1] +
                                                   walker->anims[WALK_ANIM_DOWN_B]->footRange[1] *
                                                       0.125f -
                                                   walker->anims[WALK_ANIM_DOWN_B]->frame0) %
                                    FastFloatToInt(walker->anims[WALK_ANIM_DOWN_B]->frames);
                                w_2legAnim *anim = walker->anims[WALK_ANIM_DOWN_B];
                                int trigger = MB_FindNearestAnimTrigger(
                                    moby->pClass->animations[anim->anim], (float)startFrame);
                                MB_SetAnimation(moby, anim->anim, trigger, blendFrames);
                                walk_ResetLegTwist(walker);
                                walker->state = WALK_STATE_DOWN_B_END;
                            }
                        }

                        break;
                    case WALK_STATE_DOWN_A_END:
                        if ((groundHeight - probePos.z) + walker->anims[animSlot]->stride * 0.5f *
                                                              FastAngleCosF(walker->yrot) >
                            walker->stepHeight * 0.75f) {
                            int blendFrames =
                                FastFloatToInt(walker->anims[WALK_ANIM_UP_A]->footRange[1] * 0.25f /
                                               (speed / walker->anims[WALK_ANIM_UP_A]->speed));
                            int startFrame =
                                FastFloatToInt(walker->anims[WALK_ANIM_UP_A]->footDown[1] +
                                               walker->anims[WALK_ANIM_UP_A]->footRange[1] *
                                                   0.125f -
                                               walker->anims[WALK_ANIM_UP_A]->frame0) %
                                FastFloatToInt(walker->anims[WALK_ANIM_UP_A]->frames);
                            w_2legAnim *anim = walker->anims[WALK_ANIM_UP_A];
                            int trigger = MB_FindNearestAnimTrigger(
                                moby->pClass->animations[anim->anim], (float)startFrame);
                            MB_SetAnimation(moby, anim->anim, trigger, blendFrames);
                            walk_ResetLegTwist(walker);
                            walker->state = WALK_STATE_UP_A;
                        }

                        else if ((groundHeight - probePos.z) + walker->anims[animSlot]->stride *
                                                                   0.5f *
                                                                   FastAngleCosF(walker->yrot) <
                                 -walker->stepHeight * 0.75f)
                          walker->state = WALK_STATE_DOWN_A;

                      else {
                            int blendFrames =
                                FastFloatToInt(walker->anims[WALK_ANIM_WALK]->footRange[1] /
                                               (speed / walker->anims[WALK_ANIM_WALK]->speed));
                            int startFrame =
                                FastFloatToInt(walker->anims[WALK_ANIM_WALK]->footDown[1] +
                                               walker->anims[WALK_ANIM_WALK]->footRange[1] * 0.5f -
                                               walker->anims[WALK_ANIM_WALK]->frame0) %
                                FastFloatToInt(walker->anims[WALK_ANIM_WALK]->frames);
                            w_2legAnim *anim = walker->anims[WALK_ANIM_WALK];
                            int trigger = MB_FindNearestAnimTrigger(
                                moby->pClass->animations[anim->anim], (float)startFrame);
                            MB_SetAnimation(moby, anim->anim, trigger, blendFrames);
                            walk_ResetLegTwist(walker);
                            walker->state = WALK_STATE_WALK;
                        }

                        break;
                    case WALK_STATE_DOWN_B_END:
                        if ((groundHeight - probePos.z) + walker->anims[animSlot]->stride * 0.5f *
                                                              FastAngleCosF(walker->yrot) >
                            walker->stepHeight * 0.75f) {
                            int blendFrames =
                                FastFloatToInt(walker->anims[WALK_ANIM_UP_B]->footRange[0] * 0.25f /
                                               (speed / walker->anims[WALK_ANIM_UP_B]->speed));
                            int startFrame =
                                FastFloatToInt(walker->anims[WALK_ANIM_UP_B]->footDown[0] +
                                               walker->anims[WALK_ANIM_UP_B]->footRange[0] *
                                                   0.125f -
                                               walker->anims[WALK_ANIM_UP_B]->frame0) %
                                FastFloatToInt(walker->anims[WALK_ANIM_UP_B]->frames);
                            w_2legAnim *anim = walker->anims[WALK_ANIM_UP_B];
                            int trigger = MB_FindNearestAnimTrigger(
                                moby->pClass->animations[anim->anim], (float)startFrame);
                            MB_SetAnimation(moby, anim->anim, trigger, blendFrames);
                            walk_ResetLegTwist(walker);
                            walker->state = WALK_STATE_UP_B;
                        }

                        else if ((groundHeight - probePos.z) + walker->anims[animSlot]->stride *
                                                                   0.5f *
                                                                   FastAngleCosF(walker->yrot) <
                                 -walker->stepHeight * 0.75f)
                          walker->state = WALK_STATE_DOWN_B;

                      else {
                            int blendFrames =
                                FastFloatToInt(walker->anims[WALK_ANIM_WALK]->footRange[0] /
                                               (speed / walker->anims[WALK_ANIM_WALK]->speed));
                            int startFrame =
                                FastFloatToInt(walker->anims[WALK_ANIM_WALK]->footDown[0] +
                                               walker->anims[WALK_ANIM_WALK]->footRange[0] * 0.5f -
                                               walker->anims[WALK_ANIM_WALK]->frame0) %
                                FastFloatToInt(walker->anims[WALK_ANIM_WALK]->frames);
                            w_2legAnim *anim = walker->anims[WALK_ANIM_WALK];
                            int trigger = MB_FindNearestAnimTrigger(
                                moby->pClass->animations[anim->anim], (float)startFrame);
                            MB_SetAnimation(moby, anim->anim, trigger, blendFrames);
                            walk_ResetLegTwist(walker);
                            walker->state = WALK_STATE_WALK;
                        }

                        break;
                    }
                }
            }
        }

        break;
    }
    case WALK_STATE_RUN: {
        float speedThreshold =
            (walker->anims[WALK_ANIM_RUN]->speed + walker->anims[WALK_ANIM_WALK]->speed) * 0.35f;

        if (moby->updateId == walker->anims[WALK_ANIM_RUN]->anim &&
            !(walker->onground & (WALK_CONTACT_MOVE1 | WALK_CONTACT_MOVE2))) {
            if (speed < speedThreshold && walker->speed <= speedThreshold) {
                int startFrame;

                if (walker->onground & (WALK_CONTACT_FOOT0 | WALK_CONTACT_HEEL0))
                    startFrame =
                        FastFloatToInt(walker->anims[WALK_ANIM_WALK]->footRange[0] * 2.0f / 3.0f +
                                       walker->anims[WALK_ANIM_WALK]->footDown[0] -
                                       walker->anims[WALK_ANIM_WALK]->frame0) %
                        FastFloatToInt(walker->anims[WALK_ANIM_WALK]->frames);

                else
                    startFrame =
                        FastFloatToInt(walker->anims[WALK_ANIM_WALK]->footRange[1] * 2.0f / 3.0f +
                                       walker->anims[WALK_ANIM_WALK]->footDown[1] -
                                       walker->anims[WALK_ANIM_WALK]->frame0) %
                        FastFloatToInt(walker->anims[WALK_ANIM_WALK]->frames);

                {
                    w_2legAnim *anim = walker->anims[WALK_ANIM_WALK];
                    float runStartFrame = (float)startFrame;

                    int trigger = MB_FindNearestAnimTrigger(moby->pClass->animations[anim->anim],
                                                            runStartFrame);
                    MB_SetAnimation(moby, anim->anim, trigger, 10);
                    walk_ResetLegTwist(walker);
                }

                walker->state = WALK_STATE_WALK;
            }

            else if (contacts & (WALK_CONTACT_FOOT0 | WALK_CONTACT_FOOT1)) {
                if (walker->flags & WALK_FLAG_JUMP) {
                    walker->flags = (walker->flags & ~WALK_FLAG_JUMP) | WALK_FLAG_JUMPING;
                    walker->stepZ = moby->pos.z;

                    if (contacts & WALK_CONTACT_FOOT0) {
                        int blendFrames =
                            FastFloatToInt(walker->anims[WALK_ANIM_JUMP_B]->footRange[0] * 0.25f /
                                           (speed / walker->anims[WALK_ANIM_JUMP_B]->speed));
                        int startFrame =
                            FastFloatToInt(walker->anims[WALK_ANIM_JUMP_B]->footDown[0] +
                                           walker->anims[WALK_ANIM_JUMP_B]->footRange[0] * 0.125f -
                                           walker->anims[WALK_ANIM_JUMP_B]->frame0) %
                            FastFloatToInt(walker->anims[WALK_ANIM_JUMP_B]->frames);
                        w_2legAnim *anim = walker->anims[WALK_ANIM_JUMP_B];
                        int trigger = MB_FindNearestAnimTrigger(
                            moby->pClass->animations[anim->anim], (float)startFrame);
                        MB_SetAnimation(moby, anim->anim, trigger, blendFrames);
                        walk_ResetLegTwist(walker);
                        walker->state = WALK_STATE_JUMP_B;
                    }

                    else {
                        int blendFrames =
                            FastFloatToInt(walker->anims[WALK_ANIM_JUMP_A]->footRange[1] * 0.25f /
                                           (speed / walker->anims[WALK_ANIM_JUMP_A]->speed));
                        int startFrame =
                            FastFloatToInt(walker->anims[WALK_ANIM_JUMP_A]->footDown[1] +
                                           walker->anims[WALK_ANIM_JUMP_A]->footRange[1] * 0.125f -
                                           walker->anims[WALK_ANIM_JUMP_A]->frame0) %
                            FastFloatToInt(walker->anims[WALK_ANIM_JUMP_A]->frames);
                        w_2legAnim *anim = walker->anims[WALK_ANIM_JUMP_A];
                        int trigger = MB_FindNearestAnimTrigger(
                            moby->pClass->animations[anim->anim], (float)startFrame);
                        MB_SetAnimation(moby, anim->anim, trigger, blendFrames);
                        walk_ResetLegTwist(walker);
                        walker->state = WALK_STATE_JUMP_A;
                    }
                }

                else {
                    probePos.x =
                        FastAngleSinF(angle) * walker->anims[WALK_ANIM_WALK]->stride * 0.5f;
                    probePos.y =
                        FastAngleCosF(angle) * walker->anims[WALK_ANIM_WALK]->stride * 0.5f;
                    probePos.z = 0.0f;

                    if (contacts & WALK_CONTACT_FOOT0)
                        FastVec3Add(&probePos, &probePos, &walker->fpos[1]);

                    else
                        FastVec3Add(&probePos, &probePos, &walker->fpos[3]);

                    probePos.z += 1.0f;
                    walker->stepZ = MB_CollLineDown(&probePos, 0.5f, 0);
                }
            }
        }

        if (walker->speed < speedThreshold)
            walker->speed = speedThreshold;

        break;
    }
    case WALK_STATE_STOP:
        MB_SetAnimation(moby, walker->idle, 0, 10);
        walk_ResetLegTwist(walker);
        walker->state = WALK_STATE_IDLE;
        break;
    case WALK_STATE_JUMP_B:
        if (contacts & (WALK_CONTACT_MOVE1 | WALK_CONTACT_MOVE2)) {
            float jumpDistance = FastVec3DistLen(&moby->pos, &walker->jumpPos);

            printf_stub("jumpdist = %f\n", jumpDistance);
            walker->zVel = MB_computeLobVelocity(&moby->pos, &walker->jumpPos, walker->speed,
                                                 -walker->grav, 0);
            walker->flags |= WALK_FLAG_AIRBORNE;
            walker->jumpPos.w =
                FastArcTan(walker->jumpPos.x - moby->pos.x, walker->jumpPos.y - moby->pos.y);
        }

        if (MB_BlendAnimFrame(moby) >= walker->anims[WALK_ANIM_JUMP_B]->frame0 +
                                           walker->anims[WALK_ANIM_JUMP_B]->frames -
                                           moby->animIScale) {
            MB_SetAnimation(moby, walker->rjumpc, 0, 10);
            walk_ResetLegTwist(walker);
            walker->state = WALK_STATE_AIR;
        }

        else if ((walker->flags & WALK_FLAG_AIRBORNE) && walker->zVel < 0.0f) {
            float landTiming = walk_SolveStepTiming(moby, walker);

            float landAnimLength = (walker->anims[WALK_ANIM_LAND_B]->footDown[1] -
                                    walker->anims[WALK_ANIM_LAND_B]->frame0) *
                                   2.0f;

            if (landTiming < landAnimLength + 15.0f) {
                int blendFrames = FastFloatToInt(landTiming - landAnimLength) >> 1;

                w_2legAnim *anim;
                int trigger;

                if (blendFrames < 0)
                    blendFrames = 0;

                anim = walker->anims[WALK_ANIM_LAND_B];
                trigger = MB_FindNearestAnimTrigger(moby->pClass->animations[anim->anim], 0.0f);
                MB_SetAnimation(moby, anim->anim, trigger, blendFrames);
                walk_ResetLegTwist(walker);
                walker->state = WALK_STATE_LAND_B;
            }
        }

        break;
    case WALK_STATE_JUMP_A:
        if (contacts & (WALK_CONTACT_MOVE1 | WALK_CONTACT_MOVE2)) {
            float jumpDistance = FastVec3Dist(&moby->pos, &walker->jumpPos);

            printf_stub("jumpdist = %f\n", jumpDistance);
            walker->zVel = MB_computeLobVelocity(&moby->pos, &walker->jumpPos, walker->speed,
                                                 -walker->grav, 0);
            walker->flags |= WALK_FLAG_AIRBORNE;
            walker->jumpPos.w =
                FastArcTan(walker->jumpPos.x - moby->pos.x, walker->jumpPos.y - moby->pos.y);
        }

        if (MB_BlendAnimFrame(moby) >= walker->anims[WALK_ANIM_JUMP_A]->frame0 +
                                           walker->anims[WALK_ANIM_JUMP_A]->frames -
                                           moby->animIScale) {
            MB_SetAnimation(moby, walker->rjumpc, 0, 10);
            walk_ResetLegTwist(walker);
            walker->state = WALK_STATE_AIR;
        }

        else if ((walker->flags & WALK_FLAG_AIRBORNE) && walker->zVel < 0.0f) {
            float landTiming = walk_SolveStepTiming(moby, walker);

            float landAnimLength = (walker->anims[WALK_ANIM_LAND_A]->footDown[1] -
                                    walker->anims[WALK_ANIM_LAND_A]->frame0) *
                                   2.0f;

            if (landTiming < landAnimLength + 15.0f) {
                int blendFrames = FastFloatToInt(landTiming - landAnimLength) >> 1;

                w_2legAnim *anim;
                int trigger;

                if (blendFrames < 0)
                    blendFrames = 0;

                anim = walker->anims[WALK_ANIM_LAND_A];
                trigger = MB_FindNearestAnimTrigger(moby->pClass->animations[anim->anim], 0.0f);
                MB_SetAnimation(moby, anim->anim, trigger, blendFrames);
                walk_ResetLegTwist(walker);
                walker->state = WALK_STATE_LAND_A;
            }
        }

        break;
    case WALK_STATE_AIR:
        if (moby->updateId == walker->rjumpc) {
            float landTiming = walk_SolveStepTiming(moby, walker);

            float landAnimLength = (walker->anims[WALK_ANIM_LAND_B]->footDown[1] -
                                    walker->anims[WALK_ANIM_LAND_B]->frame0) *
                                   2.0f;

            if (landTiming < landAnimLength + 15.0f) {
                int blendFrames = FastFloatToInt(landTiming - landAnimLength) >> 1;

                w_2legAnim *anim = walker->anims[WALK_ANIM_LAND_B];
                int trigger = MB_FindNearestAnimTrigger(moby->pClass->animations[anim->anim], 0.0f);

                MB_SetAnimation(moby, anim->anim, trigger, blendFrames);
                walk_ResetLegTwist(walker);
                walker->state = WALK_STATE_LAND_B;
            }
        }

        break;
    case WALK_STATE_LAND_B:
        if (moby->updateId == walker->anims[WALK_ANIM_LAND_B]->anim) {
            float landTiming = walk_SolveStepTiming(moby, walker);

            if (landTiming > 1.0f) {
                float currentFrame =
                    FastIntToFloat(moby->previousAnimationFrame) + moby->animationBlend;
                landTiming = walker->anims[WALK_ANIM_LAND_B]->footDown[1] + 2.0f -
                             landTiming * 0.5f - walker->anims[WALK_ANIM_LAND_B]->frame0;

                if (landTiming < currentFrame + 0.1f)
                    landTiming = currentFrame + 0.1f;

                moby->animIScale = animationSpeed * (landTiming - currentFrame);
            }

            else {
                float currentFrame =
                    FastIntToFloat(moby->previousAnimationFrame) + moby->animationBlend;
                landTiming = walker->anims[WALK_ANIM_LAND_B]->footDown[1] -
                             walker->anims[WALK_ANIM_LAND_B]->frame0;

                if (landTiming < currentFrame + 0.1f)
                    landTiming = currentFrame + 0.1f;

                moby->animIScale = animationSpeed * (landTiming - currentFrame);
                {
                    int nextState = WALK_STATE_LANDED_B;
                    int contactBits = WALK_CONTACT_FOOT1;

                    walker->onground = contactBits;
                    walker->state = nextState;
                }

                walker->flags &= ~WALK_FLAG_AIRBORNE;
            }
        }

        break;
    case WALK_STATE_LAND_A:
        if (moby->updateId == walker->anims[WALK_ANIM_LAND_A]->anim) {
            float landTiming = walk_SolveStepTiming(moby, walker);

            if (landTiming > 1.0f) {
                float currentFrame =
                    FastIntToFloat(moby->previousAnimationFrame) + moby->animationBlend;
                landTiming = walker->anims[WALK_ANIM_LAND_A]->footDown[1] + 2.0f -
                             landTiming * 0.5f - walker->anims[WALK_ANIM_LAND_A]->frame0;

                if (landTiming < currentFrame + 0.1f)
                    landTiming = currentFrame + 0.1f;

                moby->animIScale = animationSpeed * (landTiming - currentFrame);
            }

            else {
                float currentFrame =
                    FastIntToFloat(moby->previousAnimationFrame) + moby->animationBlend;
                landTiming = walker->anims[WALK_ANIM_LAND_A]->footDown[1] -
                             walker->anims[WALK_ANIM_LAND_A]->frame0;

                if (landTiming < currentFrame + 0.1f)
                    landTiming = currentFrame + 0.1f;

                moby->animIScale = animationSpeed * (landTiming - currentFrame);
                {
                    int nextState = WALK_STATE_LANDED_A;
                    int contactBits = WALK_CONTACT_FOOT1;

                    walker->onground = contactBits;
                    walker->state = nextState;
                }

                walker->flags &= ~WALK_FLAG_AIRBORNE;
            }
        }

        break;
    case WALK_STATE_LANDED_B:
        if (contacts & WALK_CONTACT_FOOT0) {
            int blendFrames =
                FastFloatToInt((walker->anims[WALK_ANIM_RUN]->footRange[0] * 0.25f + 2.0f) /
                               (speed / walker->anims[WALK_ANIM_RUN]->speed));
            int startFrame = FastFloatToInt(walker->anims[WALK_ANIM_RUN]->footDown[0] + 1.0f +
                                            walker->anims[WALK_ANIM_RUN]->footRange[0] * 0.125f -
                                            walker->anims[WALK_ANIM_RUN]->frame0) %
                             FastFloatToInt(walker->anims[WALK_ANIM_RUN]->frames);
            w_2legAnim *anim = walker->anims[WALK_ANIM_RUN];
            int trigger =
                MB_FindNearestAnimTrigger(moby->pClass->animations[anim->anim], (float)startFrame);
            MB_SetAnimation(moby, anim->anim, trigger, blendFrames);
            walk_ResetLegTwist(walker);
            walker->zVel = 0.0f;
            walker->state = WALK_STATE_RUN;
            walker->onground = WALK_CONTACT_FOOT0;
            walker->flags &= ~WALK_FLAG_JUMPING;
            probePos.x = FastAngleSinF(angle) * walker->anims[WALK_ANIM_RUN]->stride * 0.5f;
            probePos.y = FastAngleCosF(angle) * walker->anims[WALK_ANIM_RUN]->stride * 0.5f;
            probePos.z = 0.0f;
            FastVec3Add(&probePos, &probePos, &walker->fpos[1]);
            probePos.z += 1.0f;
            walker->stepZ = MB_CollLineDown(&probePos, 0.5f, 0);
        }

        break;
    case WALK_STATE_LANDED_A:
        if (contacts & WALK_CONTACT_FOOT0) {
            int blendFrames =
                FastFloatToInt((walker->anims[WALK_ANIM_RUN]->footRange[1] * 0.25f + 2.0f) /
                               (speed / walker->anims[WALK_ANIM_RUN]->speed));
            int startFrame = FastFloatToInt(walker->anims[WALK_ANIM_RUN]->footDown[1] + 1.0f +
                                            walker->anims[WALK_ANIM_RUN]->footRange[0] * 0.125f -
                                            walker->anims[WALK_ANIM_RUN]->frame0) %
                             FastFloatToInt(walker->anims[WALK_ANIM_RUN]->frames);
            w_2legAnim *anim = walker->anims[WALK_ANIM_RUN];
            int trigger =
                MB_FindNearestAnimTrigger(moby->pClass->animations[anim->anim], (float)startFrame);
            MB_SetAnimation(moby, anim->anim, trigger, blendFrames);
            walk_ResetLegTwist(walker);
            walker->zVel = 0.0f;
            walker->state = WALK_STATE_RUN;
            walker->onground = WALK_CONTACT_FOOT0;
            walker->flags &= ~WALK_FLAG_JUMPING;
            probePos.x = FastAngleSinF(angle) * walker->anims[WALK_ANIM_RUN]->stride * 0.5f;
            probePos.y = FastAngleCosF(angle) * walker->anims[WALK_ANIM_RUN]->stride * 0.5f;
            probePos.z = 0.0f;
            FastVec3Add(&probePos, &probePos, &walker->fpos[1]);
            probePos.z += 1.0f;
            walker->stepZ = MB_CollLineDown(&probePos, 0.5f, 0);
        }

        break;
    }
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/walk", func_002B7A30);
