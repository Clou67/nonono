#include "common.h"
#include "lights.h"
#include "camera.h"
#include "fastfunc.h"
#include "framebuf.h"
#include "mathfunc_inline.h"
#include "vuchain.h"

// Each light lists the ties, tfrags and shrubs its sphere (radius + POINT_LIGHT_MARGIN)
// touches, and writes its index into their point_lights masks: four 4-bit slots,
// 0xF is empty, kept packed from the low end.
#define POINT_LIGHT_MARGIN 8.0f
#define POINT_LIGHT_MAX_LOAD 0.8f
#define POINT_LIGHT_SLOTS_EMPTY 0xFFFF

// Tfrag positions are fixed point, 1024 units to a world unit.
#define TFRAG_POSITION_SCALE 1024.0f

// Packed colours are 0xBBGGRR with 0x80 meaning 1.0.
#define COLOR_CHANNEL_SCALE (1.0f / 128.0f)

// Directional light slot rebuilt every frame around the camera.
#define CAMERA_LIGHT 13

enum point_light_state {
    POINT_LIGHT_FREE,
    POINT_LIGHT_CREATED,
    POINT_LIGHT_ATTACHED
};

void STUB_RET_2525f0(void)
{
}

int CreatePointLightRGB(Vec4 &pos, float radius, float backlight, int rgb)
{
    PointLight *light;
    PL_Data *data;
    int index;

    if (PerfLoad > POINT_LIGHT_MAX_LOAD)
        return -1;

    for (index = 0; index < MAX_POINT_LIGHTS; index++) {
        if (PointLightData[index].state == POINT_LIGHT_FREE)
            break;
    }

    if (index == MAX_POINT_LIGHTS)
        return -1;

    light = &PointLights[index];
    data = &PointLightData[index];

    CopyVec4Inline(&light->pos, &pos);
    light->pos.w = radius;
    light->color.x = FastIntToFloat(rgb & 0xFF) * COLOR_CHANNEL_SCALE;
    light->color.y = FastIntToFloat((rgb >> 8) & 0xFF) * COLOR_CHANNEL_SCALE;
    light->color.z = FastIntToFloat((rgb >> 16) & 0xFF) * COLOR_CHANNEL_SCALE;
    light->color.w = backlight;

    FastMemSetZero(data, sizeof(PL_Data));
    data->state = POINT_LIGHT_CREATED;
    data->list = PointLightLists[index];

    return index;
}

int CreatePointLight(Vec4 &pos, float radius, float backlight, float r, float g, float b)
{
    PointLight *light;
    PL_Data *data;
    int index;

    if (PerfLoad > POINT_LIGHT_MAX_LOAD)
        return -1;

    for (index = 0; index < MAX_POINT_LIGHTS; index++) {
        if (PointLightData[index].state == POINT_LIGHT_FREE)
            break;
    }

    if (index == MAX_POINT_LIGHTS)
        return -1;

    light = &PointLights[index];
    data = &PointLightData[index];

    CopyVec4Inline(&light->pos, &pos);
    light->pos.w = radius;
    light->color.x = r;
    light->color.y = g;
    light->color.z = b;
    light->color.w = backlight;

    FastMemSetZero(data, sizeof(PL_Data));
    data->state = POINT_LIGHT_CREATED;
    data->list = PointLightLists[index];

    return index;
}

void DeletePointLight(int index)
{
    DetachPointLight(index);

    FastMemSetZero(&PointLights[index], sizeof(PointLight));
    FastMemSetZero(&PointLightData[index], sizeof(PL_Data));
}

void UpdatePointLights(void)
{
    float yaw;
    int index;

    // Grey light from above that turns with the camera.
    DirectionalLights[CAMERA_LIGHT].color1.x = 0.8f;
    DirectionalLights[CAMERA_LIGHT].color1.y = 0.8f;
    DirectionalLights[CAMERA_LIGHT].color1.z = 0.8f;
    DirectionalLights[CAMERA_LIGHT].color1.w = -0.3f;

    yaw = FastAddRots(GameCamera.rot.radius, -0.8f);
    DirectionalLights[CAMERA_LIGHT].direction1.x = FastAngleSinF(yaw) * 0.866f;
    DirectionalLights[CAMERA_LIGHT].direction1.y = FastAngleCosF(yaw) * 0.866f;
    DirectionalLights[CAMERA_LIGHT].direction1.z = -0.5f;
    DirectionalLights[CAMERA_LIGHT].direction1.w = 0.0f;

    // Rebuild the lists of lights that moved more than the margin since they were built.
    for (index = 0; index < MAX_POINT_LIGHTS; index++) {
        PointLight *light = &PointLights[index];
        PL_Data *data = &PointLightData[index];

        if (data->state == POINT_LIGHT_FREE)
            continue;

        if (FastVec3Dist(&light->pos, &data->update_pos) > POINT_LIGHT_MARGIN) {
            CopyVec4Inline(&data->update_pos, &light->pos);
            if (data->state == POINT_LIGHT_CREATED) {
                AttachPointLight(index);
                data->state = POINT_LIGHT_ATTACHED;
            } else if (data->state == POINT_LIGHT_ATTACHED) {
                RefreshPointLight(index);
            }
        }
    }
}

void AttachPointLight(int light)
{
    PointLight *pointLight;
    PL_Data *data;
    TieInstance *tie;
    Tfrag *tfrag;
    ShrubInstance *shrub;
    Vec4 sphere;
    short *entry;
    short *end;
    unsigned int slots;
    int tieIndex;
    int tfragIndex;
    int shrubIndex;

    pointLight = &PointLights[light];
    data = &PointLightData[light];
    entry = data->list;
    end = entry + POINT_LIGHT_LIST_LENGTH;

    CopyVec4Inline(&sphere, &pointLight->pos);
    sphere.w += POINT_LIGHT_MARGIN;

    if (entry < end) {
        data->tie_offset = 0;
        tieIndex = 0;
        for (tie = TieInstances; tie != TieInstanceEnd; tie++, tieIndex++) {
            if (FastVec3AddSubLen(&sphere, &tie->bSphere)) {
                *entry++ = tieIndex;
                slots = tie->point_lights;
                if (slots == POINT_LIGHT_SLOTS_EMPTY)
                    tie->point_lights = light | 0xFFF0;

                else if ((slots & 0xFFF0) == 0xFFF0)
                    tie->point_lights = (slots & 0xFF0F) | (light << 4);

                else if ((slots & 0xFF00) == 0xFF00)
                    tie->point_lights = (slots & 0xF0FF) | (light << 8);

                else if ((slots & 0xF000) == 0xF000)
                    tie->point_lights = (slots & 0x0FFF) | (light << 12);

                else
                    entry--;

                if (entry >= end)
                    break;
            }
        }

        data->tie_count = entry - data->list;
    }

    if (entry < end) {
        data->tfrag_offset = entry - data->list;
        FastScaleVec4(&sphere, &sphere, TFRAG_POSITION_SCALE);

        tfrag = Tfrags;
        for (tfragIndex = 0; tfragIndex < TfragsCnt; tfragIndex++, tfrag++) {
            if (FastVec3AddSubLen(&sphere, &tfrag->bSphere)) {
                *entry++ = tfragIndex;
                slots = tfrag->point_lights;
                if (slots == POINT_LIGHT_SLOTS_EMPTY)
                    tfrag->point_lights = light | 0xFFF0;

                else if ((slots & 0xFFF0) == 0xFFF0)
                    tfrag->point_lights = (slots & 0xFF0F) | (light << 4);

                else if ((slots & 0xFF00) == 0xFF00)
                    tfrag->point_lights = (slots & 0xF0FF) | (light << 8);

                else if ((slots & 0xF000) == 0xF000)
                    tfrag->point_lights = (slots & 0x0FFF) | (light << 12);

                else
                    entry--;

                if (entry >= end)
                    break;
            }
        }

        data->tfrag_count = (entry - data->list) - data->tfrag_offset;
    }

    if (entry < end) {
        data->shrub_offset = entry - data->list;
        shrubIndex = 0;
        for (shrub = ShrubInstances; shrub != ShrubInstanceEnd; shrub++, shrubIndex++) {
            if (FastVec3AddSubLen(&sphere, &shrub->bSphere)) {
                *entry++ = shrubIndex;
                slots = shrub->point_lights;
                if (slots == POINT_LIGHT_SLOTS_EMPTY)
                    shrub->point_lights = light | 0xFFF0;

                else if ((slots & 0xFFF0) == 0xFFF0)
                    shrub->point_lights = (slots & 0xFF0F) | (light << 4);

                else if ((slots & 0xFF00) == 0xFF00)
                    shrub->point_lights = (slots & 0xF0FF) | (light << 8);

                else if ((slots & 0xF000) == 0xF000)
                    shrub->point_lights = (slots & 0x0FFF) | (light << 12);

                else
                    entry--;

                if (entry >= end)
                    break;
            }
        }

        data->shrub_count = (entry - data->list) - data->shrub_offset;
    }
}


void RefreshPointLight(int light)
{
    DetachPointLight(light);
    AttachPointLight(light);
}

void DetachPointLight(int index)
{
    PL_Data *data;
    unsigned short slots;
    unsigned short slot0;
    unsigned short slot1;
    unsigned short slot2;
    unsigned short slot3;

    data = &PointLightData[index];

    // The light's index as it appears in each of the four slots.
    slot0 = index;
    slot1 = index << 4;
    slot2 = index << 8;
    slot3 = index << 12;

    // Take the light out of its slot and shift the slots above it down.
    {
        short *entry = data->list + data->tie_offset;
        short *end = entry + data->tie_count;

        for (; entry != end; entry++) {
            TieInstance *tie = &TieInstances[*entry];

            slots = tie->point_lights;
            if ((slots & 0x000F) == slot0)
                slots = (slots >> 4) | 0xF000;

            else if ((slots & 0x00F0) == slot1)
                slots = (slots & 0x000F) | ((slots >> 4) & 0x0FF0) | 0xF000;

            else if ((slots & 0x0F00) == slot2)
                slots = (slots & 0x00FF) | ((slots >> 4) & 0x0F00) | 0xF000;

            else if ((slots & 0xF000) == slot3)
                slots |= 0xF000;

            else
                printf_stub("screwed up point light on tie\n");

            if (slots == POINT_LIGHT_SLOTS_EMPTY)
                tie->dir_lights_upd = 1;

            tie->point_lights = slots;
        }
    }

    data->tie_offset = 0;
    data->tie_count = 0;

    {
        short *entry = data->list + data->tfrag_offset;
        short *end = entry + data->tfrag_count;

        for (; entry != end; entry++) {
            Tfrag *tfrag = &Tfrags[*entry];

            slots = tfrag->point_lights;
            if ((slots & 0x000F) == slot0)
                slots = (slots >> 4) | 0xF000;

            else if ((slots & 0x00F0) == slot1)
                slots = (slots & 0x000F) | ((slots >> 4) & 0x0FF0) | 0xF000;

            else if ((slots & 0x0F00) == slot2)
                slots = (slots & 0x00FF) | ((slots >> 4) & 0x0F00) | 0xF000;

            else if ((slots & 0xF000) == slot3)
                slots |= 0xF000;

            else
                printf_stub("screwed up point light on tfrag\n");

            if (slots == POINT_LIGHT_SLOTS_EMPTY)
                tfrag->dir_lights_upd = 1;

            tfrag->point_lights = slots;
        }
    }

    data->tfrag_offset = 0;
    data->tfrag_count = 0;

    {
        short *entry = data->list + data->shrub_offset;
        short *end = entry + data->shrub_count;

        for (; entry != end; entry++) {
            ShrubInstance *shrub = &ShrubInstances[*entry];

            slots = shrub->point_lights;
            if ((slots & 0x000F) == slot0)
                slots = (slots >> 4) | 0xF000;

            else if ((slots & 0x00F0) == slot1)
                slots = (slots & 0x000F) | ((slots >> 4) & 0x0FF0) | 0xF000;

            else if ((slots & 0x0F00) == slot2)
                slots = (slots & 0x00FF) | ((slots >> 4) & 0x0F00) | 0xF000;

            else if ((slots & 0xF000) == slot3)
                slots |= 0xF000;

            else
                printf_stub("screwed up point light on shrub\n");

            if (slots == POINT_LIGHT_SLOTS_EMPTY)
                shrub->dir_lights_upd = 1;

            shrub->point_lights = slots;
        }
    }

    data->shrub_offset = 0;
    data->shrub_count = 0;
}
