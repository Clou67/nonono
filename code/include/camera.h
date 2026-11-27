#ifndef CAMERA_H
#define CAMERA_H

#include "moby.h"

// Camera types from the PS3 project (game/camera.h); RC1 PS2 uses the same layout.

struct CameraControlActivation {
    int activationType;
    float blendSpeed;
    char priority;
    char activate;
    short deactivate;
    short repCam;
    short orgCam;
};

struct CameraControlBlock;

struct UpdateCam {
    char unk_00[0x70];
    CameraControlBlock *control;
    CameraControlActivation activation;
    short importCameraIdx;
    short type;
    char subType;
    char bumped;
    short bumpOff;
    short funcIdx;
    short active;
    char unk_90[0x10];
};

struct PolarSm {
    float azimuth;
    float elevation;
    float radius;
};

// A blend around the hero in polar coordinates (DL's CamBlenderPolarQuat).
struct CamBlenderPolarQuat {
    // Where the last camera was, around the hero.
    PolarSm orgPol;
    int interpFrames;
    float interpMaxInv;
    int reqInterpFrames;
    unsigned char pad18[8];
    // The hero's axes at the start.
    Vec4 fwd;
    Vec4 up;
    Vec4 orgQuat;
    Vec4 pos;
    Vec4 q;
};

// A blend of the camera's position and rotation from where the last camera left off
// (DL's CamBlenderPosQuat).
struct CamBlenderPosQuat {
    // 0 to 1, and the step per frame.
    float quatInterpFac;
    float quatInterpAdd;
    // The next blend's step.
    float reqQuatInterpAdd;
    float posInterpFac;
    float posInterpAdd;
    float reqPosInterpAdd;
    unsigned char pad18[8];
    // The last camera's rotation and position.
    Vec4 orgQuat;
    Vec4 orgPos;
    // The blended camera's.
    Vec4 pos;
    Vec4 q;
};

struct CamBlenderData {
    CamBlenderPosQuat posData;
    CamBlenderPolarQuat polarData;
};

// Blends a camera switch in (GameCamera.blender).
struct CamBlender {
    // 0 off, 1 starting, 2 starting over a running blend, then running.
    short state;
    // 0 position/rotation, else polar.
    unsigned char type;
    // The next blend's type.
    unsigned char reqType;
    unsigned char pad04[12];
    CamBlenderData blendData;
};

struct CameraMatrix {
    Vec4 forward;
    Vec4 right;
    Vec4 up;
    Vec4 position;
};

// A camera shake (DL's CameraShake): strength fades out with the square of the time left.
struct CamOffsetRec {
    float strength;
    // This frame's offset.
    float adjust;
    // Frames left, and the longest time it was set to.
    int time;
    int div;
};

// The camera's per-frame hero tracking and screen fade state (DL's CameraStatics up to
// fadeTimer; RC1 then tracks the moby the hero stands on).
struct CameraStatics {
    // The hero's position, its z held while jumping.
    Vec3 heroNoJump;
    float heroLastZ;
    float heroLastZSpeed;
    unsigned char pad14[12];
    // heroUpActual, smoothed.
    Vec4 heroUp;
    // Minus the hero's gravity direction.
    Vec4 heroUpActual;
    Vec4 heroUpLast;
    // Interpolation speeds for heroUp.
    Vec4 heroUpSpeed;
    Vec4 heroLastPos;
    // This frame's move, its part off heroUpActual and its part along it.
    Vec4 heroMoveVec;
    Vec4 heroMoveVec2D;
    Vec4 heroMoveVecUp;
    float heroSpeed;
    float heroSpeed2D;
    float heroSpeedUp;
    float heroLastRotZ[5];
    int hotspot;
    // The moby that keeps the hero's collision off the camera.
    MobyInstance *pCamColl;
    float fadeSpeed;
    float fadeIdeal;
    int fadeTimer;
    // The moby the hero stands on (not a train).
    MobyInstance *pGroundMoby;
    float groundMobyZ;
    // How far it rose this frame (0 under 0.001).
    float groundMobyDeltaZ;
};

// The game camera. From 0x140 on it follows DL's GAMECAMERA, with two shakes instead of
// three and a shorter CameraStatics.
struct GAMECAMERA {
    Mtx4 mtx0;
    Mtx4 matrix;
    Mtx4 mtx2;
    Mtx4 mtx3;
    Mtx4 mtx4;
    union {
        Vec4 position;
        struct {
            float posX;
            float posY;
            float posZ;
            float posW;
        };
    };
    // radius holds the yaw.
    PolarSm rot;
    float rotW;
    // Up and down, and back and forth.
    CamOffsetRec shake;
    CamOffsetRec shakeFwd;
    UpdateCam *pCurrentUpdCam;
    UpdateCam *pLastUpdCam;
    unsigned char pad188[8];
    CameraStatics camStatics;
    CamBlender blender;
    CameraMatrix orientMtx;
    // Run by the follow camera (CamZoomOfs_Update).
    void (*ofsUpdate)(void);
    unsigned int camUnderWater;
    unsigned int camTimer;
};

extern GAMECAMERA GameCamera;

void Camera_ClearPolar(float *polar);

void Camera_DeactivateCurrent(void);

void Camera_runSetupToNewCam(UpdateCam *camera);

void Camera_Exit(UpdateCam *camera);

void Camera_CopyLastPolarToQuat(void);

void Cam_CopyRotWrapped(float *out, float *polar, float yawOffset);

void Camera_CopyLastQuatToPolar(void);

void Camera_Polar2Pos(Vec4 *out, PolarSm *polar, Vec4 *origin);

int Camera_Pos2Polar(PolarSm *out, Vec4 *position, Vec4 *origin);

void Camera_CopyHeroPosition(MobyInstance *target, Vec4 *position);

void FUN_00318ad0(UpdateCam *camera);

void camera_HandleCollWithHero(UpdateCam *camera);

void Camera_HandleScreenFade(void);

void FUN_0030f338(UpdateCam *camera);

void FUN_00311008(UpdateCam *camera);

void FUN_0030f600(UpdateCam *camera, void *work);

void BackupCurrentCam(void);

void InitCameras(void);
void UpdateCameras(void);

#endif
