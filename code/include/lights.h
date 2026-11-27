#ifndef LIGHTS_H
#define LIGHTS_H

#include "moby.h"
#include "shrub.h"
#include "tfrag.h"
#include "tie.h"

#define MAX_POINT_LIGHTS 8
#define POINT_LIGHT_LIST_LENGTH 512

// DL debug type; the RaC1 light template has the same 0x50-byte layout.
struct M639_paramInit {
    Vec4 offset; // 0x00
    unsigned char backlight; // 0x10
    unsigned char r_start;
    unsigned char r_peak;
    unsigned char r_min;
    unsigned char r_inc;
    unsigned char r_dec;
    unsigned char g_start;
    unsigned char g_peak;
    unsigned char g_min;
    unsigned char g_inc;
    unsigned char g_dec;
    unsigned char b_start;
    unsigned char b_peak;
    unsigned char b_min;
    unsigned char b_inc;
    unsigned char b_dec;
    float radius_start; // 0x20
    float radius_peak;
    float radius_min;
    float radius_inc;
    float radius_dec;
    int lifetime; // 0x34
    unsigned int flags;
    unsigned char drawDist; // 0x3C
    unsigned char r_sustain;
    unsigned char g_sustain;
    unsigned char b_sustain;
    short r_duty_cycle; // 0x40
    short g_duty_cycle;
    short b_duty_cycle;
    short radius_duty_cycle;
    unsigned char radius_sustain; // 0x48
    unsigned char delay;
    unsigned char pad2[2];
    int pad3;
};

struct ExplosionColorPalette {
    int colors[6];
};

extern ExplosionColorPalette ExplosionStartColors;
extern ExplosionColorPalette ExplosionEndColors;
extern M639_paramInit DefaultExplosionFlash;
extern M639_paramInit AlternateExplosionFlash;
MobyInstance *SpawnMoby_639(M639_paramInit *params, Vec4 *pos, MobyInstance *parent, Vec4 *offset);

// One point light: its colour (w is the backlight) and position (w is the radius).
struct PointLight {
    Vec4 color;
    Vec4 pos;
};

// What a point light is attached to: ranges into list of tie, tfrag and shrub indices.
struct PL_Data {
    short tie_offset;
    short tie_count;
    short shrub_offset;
    short shrub_count;
    short tfrag_offset;
    short tfrag_count;
    short *list;
    int state;
    int pad[3];
    // Light position the lists were last built at.
    Vec4 update_pos;
};

struct DirectionalLight {
    Vec4 color1;
    Vec4 direction1;
    Vec4 color2;
    Vec4 direction2;
};

extern PointLight PointLights[MAX_POINT_LIGHTS];
extern PL_Data PointLightData[MAX_POINT_LIGHTS];
extern short PointLightLists[MAX_POINT_LIGHTS][POINT_LIGHT_LIST_LENGTH];
extern DirectionalLight DirectionalLights[16];

// Fraction of the frame budget in use; no new point lights are made above 0.8.
extern float PerfLoad;

void STUB_RET_2525f0(void);
// Packed colour 0xBBGGRR, 0x80 = 1.0.
int CreatePointLightRGB(Vec4 &pos, float radius, float backlight, int rgb);
int CreatePointLight(Vec4 &pos, float radius, float backlight, float r, float g, float b);
void DeletePointLight(int index);
void UpdatePointLights(void);
// Builds the light's lists of the ties, tfrags and shrubs it touches.
void AttachPointLight(int light);
void RefreshPointLight(int light);
void DetachPointLight(int index);

#endif
