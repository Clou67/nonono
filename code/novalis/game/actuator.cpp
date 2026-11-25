#include "common.h"
#include "fastfunc.h"

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/actuator", func_0020C600);

struct ActuatorWave {
    short type;          // 0 = unused, 1 = square, 2 = triangle, 3 = ramp up, 4 = ramp down, 5 = sine
    unsigned char side;  // which motor (0 or 1) the wave drives
    unsigned char scale; // nonzero: scales the other waves on this motor instead of adding to them
    short delay;
    short lifeSpan;
    short timer;
    short on;
    short off;
    unsigned char power;
    unsigned char minpower;
};

extern ActuatorWave ActuatorWaves[];

int actuator_CalcPower(int *out)
{
    // Rows: summed scale waves, scale wave counts, output wave counts.
    int scratch[3][4];
    int *outputCount;
    int *scaleCount;
    int active;
    int index;

    active = 0;
    scaleCount = scratch[1];
    outputCount = scratch[2];

    for (index = 0; index < 2; index++) {
        out[index] = 0;
        scratch[0][index] = 0;
        scratch[1][index] = 0;
        scratch[2][index] = 0;
    }

    for (index = 0; index < 8; index++) {
        ActuatorWave *wave;
        int phase;
        int value;
        unsigned short duration;

        if (ActuatorWaves[index].type == 0)
            continue;

        wave = &ActuatorWaves[index];
        active++;
        duration = ActuatorWaves[index].lifeSpan;
        ActuatorWaves[index].lifeSpan = duration - 1;

        if ((short)duration <= 0)
            wave->type = 0;

        if (ActuatorWaves[index].delay != 0) {
            ActuatorWaves[index].delay = ActuatorWaves[index].delay - 1;
            continue;
        }

        value = 0;
        ActuatorWaves[index].timer++;
        phase = wave->timer % (wave->on + wave->off);

        switch (wave->type) {
        case 0:
            break;

        case 1:
            if (phase < wave->on)
                value = wave->power + wave->minpower;

            else
                value = wave->minpower;
            break;

        case 2:
            if (phase < wave->on)
                value = (wave->power * phase) / wave->on;

            else
                value = (wave->power * (wave->off + wave->on - phase)) / wave->off;

            value = value + wave->minpower;
            break;

        case 3:
            if (phase < wave->on)
                value = (wave->power * phase) / wave->on + wave->minpower;
            break;

        case 4:
            if (phase >= wave->on)
                value = (wave->power * (wave->off + wave->on - phase)) / wave->off + wave->minpower;
            break;

        case 5: {
            float angle;
            float amplitude;

            if (phase < wave->off)
                angle = FastIntToFloat(phase) * 3.1415927f / FastIntToFloat(wave->off);

            else
                angle = 3.1415927f - FastIntToFloat(phase - wave->off) * 3.1415927f / FastIntToFloat(wave->on);

            angle = FastAngleSinF(angle);
            amplitude = FastIntToFloat(wave->power);
            value = FastFloatToInt((angle * amplitude + amplitude) * 0.5f) + wave->minpower;

            if (value >= 256)
                value = 255;
            break;
        }
        }

        if (wave->scale != 0) {
            int *count;

            scratch[0][wave->side] = scratch[0][wave->side] + value;
            count = scaleCount + wave->side;
            *count = *count + 1;
        }

        else {
            int *count;

            out[wave->side] = out[wave->side] + value;
            count = outputCount + wave->side;
            *count = *count + 1;
        }
    }

    for (index = 0; index < 2; index++) {
        if (outputCount[index] != 0)
            out[index] = out[index] / outputCount[index];

        if (scaleCount[index] != 0) {
            scratch[0][index] = scratch[0][index] / scaleCount[index];
            out[index] = (out[index] * scratch[0][index]) / 255;
        }
    }

    return active;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/actuator", func_0020CA20);
