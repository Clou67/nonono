#include "common.h"
#include "tie.h"
#include "draw.h"
#include "fastfunc.h"
#include "initlevel.h"
#include "vuchain.h"

// GS memory the tie textures may use before they overflow it.
#define TIE_GS_MEMORY_LIMIT 0x400000

// GS texture address bits of a texture register word.
#define GS_TEXTURE_ADDRESS_MASK 0xFFFFC000

// Scratchpad range TieProc leaves its results in.
#define TIE_SPR_RESULT_ADDRESS 0x3600
#define TIE_SPR_RESULT_QWORDS 0x40


void DmaTieTextures(void)
{
    DmaTag *start = vu1_bufPtr.tag++;

    TieVu1Marker.tag->tag = DMA_TAG_NEXT;
    TieVu1Marker.tag->addr = (unsigned int)vu1_bufPtr.tag;
    TieVu1Marker.tag->vif0 = 0;
    TieVu1Marker.tag->vif1 = 0;

    if (drawConfig.tie) {
        if (drawConfig.tie_texture_paging) {
            int gsEnd = BuildTieTextureDma(GSloc);

            VU1_texFlush();

            if (gsEnd > TIE_GS_MEMORY_LIMIT)
                printf_stub("tie texture overflow\n");

            if (TieGsMax < gsEnd)
                TieGsMax = gsEnd;
        }
    }

    // Return from the texture uploads to the packets after the opening marker.
    vu1_bufPtr.tag->tag = DMA_TAG_NEXT;
    vu1_bufPtr.tag->addr = (unsigned int)(TieVu1Marker.tag + 1);
    vu1_bufPtr.tag->vif0 = 0;
    vu1_bufPtr.tag->vif1 = 0;
    vu1_bufPtr.tag++;

    // The first link jumps over the uploads to this point.
    start->tag = DMA_TAG_NEXT;
    start->addr = (unsigned int)vu1_bufPtr.tag;
    start->vif0 = 0;
    start->vif1 = 0;
}

void PatchTieGifs(void)
{
    int *rectify;
    TieClass *tieClass;
    TieDraw *draw;
    GsTextureLoc *location;
    int drawIndex;

    for (rectify = TieClassRectify; *rectify >= 0; rectify++) {
        tieClass = TieClasses[*rectify];
        draw = tieClass->draws;

        for (drawIndex = 0; drawIndex < tieClass->draw_cnt; drawIndex++) {
            location = &TieGsLocStash[draw->stash_index];

            if (location->base != 0)
                draw->base_tex = (draw->base_tex & GS_TEXTURE_ADDRESS_MASK) | location->base;

            if (location->mip != 0)
                draw->mip_tex = (draw->mip_tex & GS_TEXTURE_ADDRESS_MASK) | location->mip;

            draw++;
        }
    }
}

// Patches the texture addresses for both draw passes.
void UpdateTieTextures(void)
{
    PatchTieGifs();

    FastMemCopy16(TieClassRectify, TieClassRectifyOdd, sizeof(TieClassRectify));
    FastMemCopy16(TieGsLocStash, TieGsLocStashOdd, sizeof(TieGsLocStash));
    PatchTieGifs();
}

void RefreshTieLights(void)
{
    LightTies(TieSprStash);
    LightTies(TieSprStashOdd);
}

void DrawTie(void)
{
    TieVu1Marker.tag = vu1_bufPtr.tag++;
    GSloc = GSbase;

    printf_stub3("tie texs", 1);

    if (drawConfig.tie) {
        FlushCache(0);
        TieProc();
        FastFromSpr(TieSprStash, TIE_SPR_RESULT_ADDRESS, TIE_SPR_RESULT_QWORDS);
    }

    printf_stub3("tie draw", 5);
    DmaTieTextures();
    FastMemCopy16(vu1_bufPtr.tag, TieChainEnd, sizeof(TieChainEnd));
    printf_stub2("tie draw", 5);
}

#ifdef ALLOW_NON_MATCHING
void DrawTiesEx(void)
{
    {
        int a;
        int n = TieClassIndex;

        for (a = 1; a < n; a += 2)
            TieClasses[a]->mode_bits |= TIE_CLASS_HIDDEN;
    }

    {
        DmaTag *current = vu1_bufPtr.tag;

        TieVu1Marker.tag = current;
        GSloc = GSbase;
        current++;
        vu1_bufPtr.tag = current;
    }

    printf_stub3("tie texs", 1);

    {
        if (drawConfig.tie) {
            FlushCache(0);
            TieProc();
            FastFromSpr(TieSprStashOdd, TIE_SPR_RESULT_ADDRESS, TIE_SPR_RESULT_QWORDS);
        }
    }

    DmaTieTextures();

    FastMemCopy16(TieClassRectifyOdd, TieClassRectify, sizeof(TieClassRectify));
    FastMemCopy16(TieGsLocStashOdd, TieGsLocStash, sizeof(TieGsLocStash));

    {
        int b;
        int n = TieClassIndex;

        for (b = 1; b < n; b += 2)
            TieClasses[b]->mode_bits &= ~TIE_CLASS_HIDDEN;
    }

    {
        int c;
        int n = TieClassIndex;

        for (c = 0; c < n; c += 2)
            TieClasses[c]->mode_bits |= TIE_CLASS_HIDDEN;
    }

    {
        DmaTag *current = vu1_bufPtr.tag;

        TieVu1Marker.tag = current;
        GSloc = GSbase;
        current++;
        vu1_bufPtr.tag = current;

        if (drawConfig.tie) {
            FlushCache(0);
            TieProc();
            FastFromSpr(TieSprStash, TIE_SPR_RESULT_ADDRESS, TIE_SPR_RESULT_QWORDS);
        }
    }

    printf_stub3("tie draw", 5);
    DmaTieTextures();

    {
        int d;
        int n = TieClassIndex;

        for (d = 0; d < n; d += 2)
            TieClasses[d]->mode_bits &= ~TIE_CLASS_HIDDEN;
    }

    FastMemCopy16(vu1_bufPtr.tag, TieChainEnd, sizeof(TieChainEnd));
    printf_stub2("tie draw", 5);
}
#else
INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/tiefunc", DrawTiesEx);
#endif
