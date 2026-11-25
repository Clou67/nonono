#include "common.h"
#include "vuchain.h"
#include "draw.h"
#include "fastfunc.h"
#include "mathfunc_inline.h"
#include "vtbl.h"
#include "camera.h"

void Camera_ClearPolar(float *polar)
{
    polar[0] = 0.0f;
    polar[1] = 0.0f;
    polar[2] = 0.0f;
    polar[3] = 0.0f;
    polar[4] = 0.0f;
}

void Cam_CopyRotWrapped(float *out, float *polar, float yawOffset)
{
    out[0] = FastAddRots(polar[0], yawOffset);
    out[1] = polar[1];
    out[2] = polar[2];
    out[3] = polar[3];
    out[4] = polar[4];
}

struct CameraControlBlock {
    unsigned char data[0x280];
};

struct CameraControlBuffers {
    CameraControlBlock current;
    CameraControlBlock unk_280;
    CameraControlBlock backup;
};

extern UpdateCam BackupCamera;
extern CameraControlBuffers CameraControls;

void BackupCurrentCam(void)
{
    FastMemCopy16(&BackupCamera, GameCamera.pCurrentUpdCam, sizeof(BackupCamera));
    FastMemCopy16(&CameraControls.backup, &CameraControls.current, sizeof(CameraControls.backup));
    BackupCamera.control = &CameraControls.backup;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/camera", ExecuteCamPostUpdFuncs);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/camera", Camera_FindCameraOfType);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/camera", func_0020CE30);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/camera", Cam_InterpValues);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/camera", Cam_InterpAngles);

void Camera_DeactivateCurrent(void)
{
    GameCamera.pCurrentUpdCam->activation.deactivate = 1;
    GameCamera.pCurrentUpdCam->activation.activate = 0;
}

MobyInstance *SpawnMoby_1007(Vec4 *position);
void DeleteMoby(MobyInstance *moby);

void camera_HandleCollWithHero(UpdateCam *camera)
{
    CameraStatics *statics = &GameCamera.camStatics;

    if (!camera->type) {
        if (!statics->pCamColl)
            statics->pCamColl = SpawnMoby_1007(&GameCamera.position);
    }
    else if (statics->pCamColl) {
        DeleteMoby(statics->pCamColl);
        statics->pCamColl = 0;
    }
}

void Camera_runSetupToNewCam(UpdateCam *camera)
{
    void (*callback)(UpdateCam *) = cameraupdate_vtbl[camera->funcIdx].activate;

    if (callback)
        callback(camera);
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/camera", Camera_switchtoNewCam);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/camera", Camera_ActivationCheckPriority);

void Camera_Exit(UpdateCam *camera)
{
    void (*callback)(UpdateCam *) = cameraupdate_vtbl[camera->funcIdx].exit;

    if (callback)
        callback(camera);
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/camera", UpdateAllCameras);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/camera", Camera_Pos2Polar3d);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/camera", Camera_InitBlenderPolarHero);

extern Vec4 camPosOffset __attribute__((section(".data")));
void FastVec3Add(Vec4 *out, Vec4 *first, Vec4 *second);
enum { CAMERA_BLEND_WITH_POSITION_OFFSET = 2 };

void Camera_CopyLastQuatToPolar(void)
{
    CamBlender *blender = &GameCamera.blender;

    if (!blender->type) {
        Vec4 *position = &blender->blendData.polarData.pos;
        CopyVec4Inline(position, &blender->blendData.posData.pos);
        if (blender->reqType == CAMERA_BLEND_WITH_POSITION_OFFSET)
            FastVec3Add(position, &camPosOffset, position);
        CopyVec4Inline(&blender->blendData.polarData.q, &blender->blendData.posData.q);
    }
}

void Camera_CopyLastPolarToQuat(void)
{
    CamBlender *blender = &GameCamera.blender;

    if (blender->type) {
        CopyVec4Inline(&blender->blendData.posData.pos, &blender->blendData.polarData.pos);
        CopyVec4Inline(&blender->blendData.posData.q, &blender->blendData.polarData.q);
    }
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/camera", Camera_InitBlender);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/camera", Camera_BlendCamsPosQuat);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/camera", Camera_BlendCamsPolQuat);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/camera", Camera_BlendCams);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/camera", HandleCameraShake);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/camera", Camera_UpdateHeroInfo);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/camera", Camera_UpdateUnderWater);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/camera", func_0020EB38);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/camera", Camera_SetCollFlags);

void Camera_HandleScreenFade(void)
{
    if (GameCamera.camStatics.fadeSpeed != 0.0f) {
        screenFade -= GameCamera.camStatics.fadeSpeed;
        if (screenFade <= 0.0f) {
            GameCamera.camStatics.fadeSpeed = 0.0f;
            screenFade = 0.0f;
        }
    }
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/camera", UpdateCameras);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/camera", Camera_GetFuncIdx);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/camera", Camera_resetToFollow);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/camera", InitCameras);

void Camera_Polar2Pos(Vec4 *out, PolarSm *polar, Vec4 *origin)
{
    out->x = polar->radius * FastAngleSinF(polar->elevation) * FastAngleSinF(polar->azimuth);
    out->y = polar->radius * FastAngleSinF(polar->elevation) * FastAngleCosF(polar->azimuth);
    out->z = polar->radius * FastAngleCosF(polar->elevation);
    out->w = 0.0f;

    FastVec3Add(out, out, origin);
}

void FastSubVec3(Vec4 *out, Vec4 *first, Vec4 *second);
float FastSubRots(float first, float second);
float FastVec3Length2(Vec4 *vector);

int Camera_Pos2Polar(PolarSm *out, Vec4 *position, Vec4 *origin)
{
    Vec4 delta;
    FastSubVec3(&delta, position, origin);
    out->elevation = FastArcTan(FastVec3Length(&delta.x), delta.z);
    float azimuth = FastArcTan(delta.x, delta.y);
    FastSubRots(azimuth, out->azimuth);
    out->azimuth = azimuth;
    out->radius = FastVec3Length2(&delta);

    return 0;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/camera", Camera_CollSphereBump);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/camera", func_0020F478);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/camera", Camera_DrawReticule);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/camera", DrawCrosshairSprite);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/camera", func_0020FB58);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/camera", DrawTargetCrosshair);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/camera", TargetCrosshairDraw);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/camera", Camera_CollPrimTest);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/camera", IsPntInCollPrim);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/camera", Camera_UpdateFog);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/camera", func_00210448);
