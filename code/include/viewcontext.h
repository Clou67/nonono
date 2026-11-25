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
    Vec4 iguard;
    Vec4 sphereCheckA;
    Vec4 sphereCheckB;
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
    int scis_b;
    int fogR;
    int fogG;
    int fogB;
    int backR;
    int backG;
    int backB;
    int splitScreenMode;
};

extern ViewContext VC;

// Copies of the view that the renderers and VU1 programs read; UpdateViewContext keeps them up.
extern Vec4 FastFrustum[8];
extern Vec4 part_constants;
extern Vec4 ViewConstsA[3];
extern unsigned char ViewConstsB[0x48];
extern unsigned char ViewConstsC[0x20];
extern unsigned char tfrag_setup_consts[0x1C];
extern unsigned char shrub_near_setup_consts[0x38];
extern unsigned char shrub_setup_consts[0x38];
extern unsigned char stripvif_head[0x40];
extern unsigned char watertile_blockvif_head[0x40];
extern float RenderConsts1;

#endif
