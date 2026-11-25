#ifndef PART_H
#define PART_H

#include "moby.h"

struct PartLineMotion {
    Vec4 origin;
    Vec4 velocity;
};

struct PartTimedFade {
    Vec4 velocity;
    int timer;
    int duration;
    int alpha;
};

struct PartSpinMotion {
    Vec4 velocity;
    union {
        char rotationStep;
        int relativeToHero;
    };
};

struct PartScaleFade {
    float startScale;
    float endScale;
    int startColor;
    int endColor;
    float rate;
};

struct PartFadingMotion {
    Vec4 velocity;
    float scaleStep;
};

struct PartRotationMotion {
    char unk_00[0x18];
    char rotationStep;
};

struct PartTweenSpin {
    Vec4 velocity;
    float rate;       // timer-to-fraction scale for the colour tween
    int colorB;
    int colorA;
    char rotationStep;
};

struct PartFollowFade {
    short fadeStep;   // alpha removed each frame
    short mode;       // 1 = frozen, 2 = follows pMoby
    MobyInstance *pMoby;
    char unk_08[8];
    Vec4 offset;      // offset from pMoby
};

struct PartTimedScale {
    int timer;
    float scaleStep;
};

struct PartInstance {
    char i_class;
    char type;
    char tex;
    char gs_alpha;
    int rgba;
    char rot;
    char draw_dist;
    short timer;
    union {
        float scale;
        int rgbaScale;
    };
    Vec4 pos;
    union {
        int update[8];
        PartLineMotion motion20;
        PartTimedFade timedFade;
        PartSpinMotion spinMotion;
        PartScaleFade scaleFade;
        PartFadingMotion fadingMotion;
        PartRotationMotion rotationMotion;
        PartTweenSpin tweenSpin;
        PartFollowFade followFade;
        PartTimedScale timedScale;
    };
};

PartInstance *CreatePart(int iClass);
void DeletePart(PartInstance *part);

void UpdatePart_018(PartInstance *part);

void UpdatePart_034(PartInstance *part);

void UpdatePart_042(PartInstance *part);

void UpdatePart_064(PartInstance *part);

void UpdatePart_020(PartInstance *part);

void UpdatePart_057(PartInstance *part);

void UpdatePart_060(PartInstance *part);

void UpdatePart_071(PartInstance *part);

void UpdatePart_073(PartInstance *part);

#endif
