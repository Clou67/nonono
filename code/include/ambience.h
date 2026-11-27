#ifndef AMBIENCE_H
#define AMBIENCE_H

struct AmbienceState {
    float baseRotation;
    float rotation;
    float rotationStep;
    short state;
    short phase;
    float baseStrength;
    float strength;
    float strengthStep;
    short duration;
    short timer;
};

extern AmbienceState WindState;

#endif
