#ifndef VIEWCONTEXT_H
#define VIEWCONTEXT_H

#include "moby.h"

// The view the frame is drawn from (DL's ViewContext).
struct ViewContext {
    // Retail has 0x50 bytes of header here; VC points at the 0x10 bytes after the DL start.
    int headerBase[5][4];
    unsigned long headerTex[2];
    unsigned long headerTexNoFog[2];
    unsigned long headerGr[2];
    unsigned long headerGrNoFog[2];
    float D;
    float F;
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

#endif
