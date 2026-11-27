#ifndef ENV_H
#define ENV_H

#include "moby.h"

// RaC1 environment-sample record, copied from the level archive in 0x30-byte units.
struct EnvSample {
    Vec4 pos;
    int colorR;
    int colorG;
    int colorB;
    int lights;
    int reverbDepth;
    unsigned char reverbType;
    unsigned char reverbDelay;
    unsigned char reverbFeedback;
    unsigned char hasReverb;
    int musicTrack;
    int unk_2C;
};

extern EnvSample *EnvSamples;
extern int EnvSampleCnt;

#endif
