#include "common.h"
#include "hero.h"
#include "fastfunc.h"
#include "part.h"

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", ResetParticles);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_001);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_001);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_002);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_002);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_003);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", func_0027E0D0);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_004);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_004);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_005);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_005);

void UpdatePart_006(PartInstance *part)
{
    PartTimedScale *scale = &part->timedScale;

    if (FastDecTimer(scale->timer)) {
        DeletePart(part);
        return;
    }

    part->scale += scale->scaleStep;

    if (FastScaleRoundInt(6) > scale->timer)
        part->rgba = (part->rgba & 0xFFFFFF) | (((scale->timer * 0x7F) / FastScaleRoundInt(6)) << 24);
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_006);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_007);

void UpdatePart_008(PartInstance *part)
{
    PartTimedScale *scale = &part->timedScale;

    if (FastDecTimer(scale->timer)) {
        DeletePart(part);
        return;
    }

    part->scale += scale->scaleStep;

    if (FastScaleRoundInt(6) > scale->timer)
        part->rgba = (part->rgba & 0xFFFFFF) | (((scale->timer * 0x7F) / FastScaleRoundInt(6)) << 24);
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_008);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_009);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", func_0027F4D0);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_010);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_010);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_011);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_011);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_012);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_012);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_013);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_013);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_014);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_014);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_015);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_015);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_016);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_016);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_017);

void UpdatePart_018(PartInstance *part)
{
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_018);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_019);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_019);

void FastVec3Add(Vec4 *out, Vec4 *first, Vec4 *second);
int FastDecTimer(short &timer);
void DeletePart(PartInstance *part);

void UpdatePart_020(PartInstance *part)
{
    FastVec3Add(&part->pos, &part->pos, &part->motion20.velocity);
    FastVec3Add(&part->motion20.origin, &part->motion20.origin, &part->motion20.velocity);

    part->rgba -= 6 << 24;
    part->rgbaScale = part->rgba;
    if (part->rgba < 0)
        DeletePart(part);
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_021);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_021);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_022);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_022);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_023);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_024);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_025);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_025);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_026);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_026);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_027);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_027);

void UpdatePart_028(PartInstance *part)
{
    PartTimedFade *fade = &part->timedFade;

    FastVec3Add(&part->pos, &part->pos, &fade->velocity);

    part->rgba = (part->rgba & 0xFFFFFF) + (((fade->alpha * fade->timer) / fade->duration) << 24);

    if (FastDecTimer(fade->timer) != 0)
        DeletePart(part);
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_028);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_029);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", func_00283400);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_030);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_031);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", func_00283BE0);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_032);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_032);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_033);

int FastDecTimer(short &timer);
void DeletePart(PartInstance *part);

void UpdatePart_034(PartInstance *part)
{
    if (FastDecTimer(part->timer))
        DeletePart(part);
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_034);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_035);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_035);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_036);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", func_002848F0);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_037);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", func_00284A58);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_038);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_039);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_040);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_040);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_041);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_041);

void UpdatePart_042(PartInstance *part)
{
    if (part->timer != -1 && FastDecTimer(part->timer))
        DeletePart(part);
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_042);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_043);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_044);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_044);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_045);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_045);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_046);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_046);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_047);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_047);

void UpdatePart_048(PartInstance *part)
{
    PartSpinMotion *motion = &part->spinMotion;
    int rgba;

    FastVec3Scale(&motion->velocity, &motion->velocity, 0.975f);
    FastVec3Add(&part->pos, &part->pos, &motion->velocity);

    part->scale += 14700.0f;
    part->rot += motion->rotationStep;
    rgba = part->rgba + 0xFE000000;
    part->rgba = rgba;

    if (rgba < 0)
        DeletePart(part);
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", func_00286E18);

void UpdatePart_049(PartInstance *part)
{
    PartTweenSpin *spin = &part->tweenSpin;

    part->rot += spin->rotationStep;
    FastVec3Add(&part->pos, &part->pos, &spin->velocity);

    part->rgba = FastTweenColor(spin->colorA, spin->colorB, FastAbsF(FastIntToFloat(part->timer) * spin->rate - 1.0f));

    if (FastDecTimer(part->timer) != 0)
        DeletePart(part);
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_050);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", func_00286F88);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_051);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_052);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_052);

void UpdatePart_053(PartInstance *part)
{
    if (FastDecTimer(part->timer))
        DeletePart(part);

    else {
        PartScaleFade *fade = &part->scaleFade;
        float fraction = FastIntToFloat(part->timer) * fade->rate;

        part->rgba = FastTweenColor(fade->endColor, fade->startColor, fraction);
        part->scale = ((fade->startScale - fade->endScale) * fraction + fade->endScale) * 210000.0f;
    }
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_053);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_054);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", func_002876F8);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_055);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_055);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_056);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_056);

void UpdatePart_057(PartInstance *part)
{
    PartSpinMotion *motion = &part->spinMotion;
    FastVec3Scale(&motion->velocity, &motion->velocity, 0.975f);
    FastVec3Add(&part->pos, &part->pos, &motion->velocity);

    part->scale += 6300.0f;
    int intensity = (part->rgba & 0xFF) - 4;
    if (intensity <= 0)
        DeletePart(part);
    else
        part->rgba = 0x60000000 | (intensity << 16) | (intensity << 8) | intensity;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_057);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_058);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_058);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_059);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_059);

enum { PART_RELATIVE_TO_HERO = 1 };

void UpdatePart_060(PartInstance *part)
{
    PartSpinMotion *motion = &part->spinMotion;
    if (motion->relativeToHero == PART_RELATIVE_TO_HERO)
        FastVec3Add(&part->pos, &Hero.position, &motion->velocity);

    if (FastDecTimer(part->timer))
        DeletePart(part);
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_060);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_061);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_062);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_062);

void UpdatePart_063(PartInstance *part)
{
    PartFollowFade *fade = &part->followFade;
    int rgba;
    int alpha;

    if (fade->mode == 1)
        return;

    if (fade->mode == 2) {
        part->pos.x = fade->pMoby->pos.x + fade->offset.x;
        part->pos.y = fade->pMoby->pos.y + fade->offset.y;
        part->pos.z = fade->pMoby->pos.z + fade->offset.z;
    }

    rgba = part->rgba;
    alpha = rgba >> 24;
    alpha -= fade->fadeStep;

    if (alpha <= 0) {
        DeletePart(part);
        return;
    }

    part->rgba = (rgba & 0xFFFFFF) | (alpha << 24);
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", func_00288D50);

void UpdatePart_064(PartInstance *part)
{
    if (FastDecTimer(part->timer))
        DeletePart(part);
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_064);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_065);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_066);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_066);

void UpdatePart_067(PartInstance *part)
{
    PartFadingMotion *motion = &part->fadingMotion;
    int timer;

    FastVec3Add(&part->pos, &part->pos, &motion->velocity);

    part->scale += motion->scaleStep;
    part->rot += 1;

    timer = (unsigned short)part->timer - 1;
    part->timer = timer;

    if ((short)timer == 0) {
        part->rgba += 0xFF000000;
        part->timer = 2;
    }

    if ((part->rgba & 0xFF000000) == 0)
        DeletePart(part);
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_067);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_068);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", func_00289CB8);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_069);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_070);

void UpdatePart_071(PartInstance *part)
{
    if (--part->timer == 0) {
        part->rgba -= 1 << 24;
        part->timer = 2;
    }

    if (!(part->rgba & 0xFF000000))
        DeletePart(part);
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", func_0028A0D8);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_072);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_072);

void UpdatePart_073(PartInstance *part)
{
    part->rot += part->rotationMotion.rotationStep;
    if (part->scale <= 0.0f) {
        part->scale = 0.0f;
        DeletePart(part);
    }
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_074);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_074);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_075);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", func_0028AAE0);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_076);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_077);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", func_0028AC50);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_078);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", SpawnPart_078);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_079);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_080);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", UpdatePart_081);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/partupd", func_0028B408);
