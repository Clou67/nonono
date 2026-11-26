#ifndef VIEWCONTEXT_H
#define VIEWCONTEXT_H

#include "moby.h"

// The view the frame is drawn from (DL's ViewContext).
struct ViewContext {
    // The first row is the GIF tag for the fog far intensity, the five after it hold the GS register
    // values; the four rows after those are the texture and gradient GIF tags.
    int headerBase[6][4];
    int headerTex[4];
    int headerTexNoFog[4];
    int headerGr[4];
    int headerGrNoFog[4];
    float nearClip;
    float farClip;
    float xclipratio;
    float yclipratio;
    float xratio;
    float yratio;
    float xradpad;
    float yradpad;
    Mtx4 fMtx;
    Mtx4 nfMtx;
    Mtx4 hMtx;
    Vec4 hmgScale;
    Vec4 ihmgScale;
    Vec4 hvdf;
    Vec4 unSquish;
    Vec4 guard;
    Vec4 sphereCheckA;
    Vec4 sphereCheckB;
    Vec4 sphereCheckC;
    float xpix;
    float ypix;
    float xclip;
    float yclip;
    float fog0;
    float fog1;
    float fogNearDist;
    float fogFarDist;
    float fogMult;
    float fogAdd;
    float fogNearIntensity;
    float fogFarIntensity;
    int scis_l;
    int scis_r;
    int scis_t;
    // The level's background colour, from the gameplay file.
    int backR;
    int backG;
    int backB;
    int unk_248[5];
    int splitScreenMode;
};

extern ViewContext VC;

// Constants for the tfrag VU1 program that follow the view.
struct TfragVuConsts {
    char unk0[0x10];
    int fog0;
    int fogFarIntensity;
    int fogNearIntensity;
    char unk1C[0x44];
    Vec4 hvdf;
    Vec4 hmgScale;
    Vec4 ihmgScale;
    char unk90[0x10];
    int guardX;
    int guardY;
};

// Fog constants for the shrub VU1 programs (float bit patterns).
struct ShrubFogConsts {
    char unk0[0x28];
    int fog0;
    int max;
    int fogFarIntensity;
    int fogNearIntensity;
};

// The near shrub constants also carry the view's screen scale and offset.
struct ShrubNearConsts {
    char unk0[0x28];
    int fog0;
    int max;
    int fogFarIntensity;
    int fogNearIntensity;
    char unk38[0x8];
    Vec4 ihmgScale;
    Vec4 hvdf;
};

// Copies of the view that the renderers and VU1 programs read; UpdateViewContext keeps them up.
extern Vec4 FastFrustum[8];
extern float part_constants[];
extern Vec4 ViewConstsA[3];
extern TfragVuConsts tfrag_setup_consts;
extern ShrubFogConsts shrub_setup_consts;
extern ShrubNearConsts shrub_near_setup_consts;
extern float stripvif_head[16];
extern float watertile_blockvif_head[16];
extern float RenderConsts1;

#endif
