#include "common.h"
#include "tfrag.h"
#include "camera.h"
#include "draw.h"
#include "fastfunc.h"
#include "framebuf.h"
#include "initlevel.h"
#include "viewcontext.h"
#include "vuchain.h"

// Tfrag distances become fixed point in 1/1024 units.
#define TFRAG_DIST_FIXED_SCALE 1024.0f

// GS memory the tfrag textures may use before they overflow it.
#define TFRAG_GS_MEMORY_LIMIT 0x400000

// GS texture address bits of a texture register word.
#define GS_TEXTURE_ADDRESS_MASK 0xFFFFC000

// Scratchpad range TfragProc leaves its results in.
#define TFRAG_SPR_RESULT_ADDRESS 0x3000
#define TFRAG_SPR_RESULT_QWORDS 0x40

// VU1 memory addresses of the view matrix, written to both of its copies.
#define TFRAG_VU1_MATRIX_ADDRESS 5
#define TFRAG_VU1_MATRIX_COPY_ADDRESS 0x14D

// Camera position is scaled by this to match the fixed point tfrag positions.
#define TFRAG_POSITION_SCALE -1024.0f


void SetTfragDists(void)
{
    float farRange;
    float middleRange;
    float nearRange;
    float farScale;
    float nearScale;

    TfragIntDists[0] = FastFloatToInt(TfragDists[0] * TFRAG_DIST_FIXED_SCALE);
    TfragIntDists[1] = FastFloatToInt(TfragDists[1] * TFRAG_DIST_FIXED_SCALE);
    TfragIntDists[2] = FastFloatToInt(TfragDists[2] * TFRAG_DIST_FIXED_SCALE);

    farRange = TfragDists[0] * VC.fogMult;
    middleRange = TfragDists[1] * VC.fogMult;
    nearRange = TfragDists[2] * VC.fogMult;
    farScale = 1.0f / (farRange - middleRange);
    nearScale = 1.0f / (middleRange - nearRange);

    FastMemSetZero(TfragSetupConsts, sizeof(TfragSetupConsts));
    TfragSetupConsts[0][0] = farScale * 0.5f;
    TfragSetupConsts[0][1] = -farScale;
    TfragSetupConsts[1][0] = nearScale * 0.5f;
    TfragSetupConsts[1][1] = -nearScale;
    TfragSetupConsts[2][0] = middleRange * farScale * -0.5f;
    TfragSetupConsts[2][1] = farRange * farScale;
    TfragSetupConsts[3][0] = nearRange * nearScale * -0.5f;
    TfragSetupConsts[3][1] = middleRange * nearScale;
    TfragSetupConsts[1][3] = middleRange;
    TfragSetupConsts[0][3] = farRange;
}

void DmaTfragTextures(void)
{
    DmaTag *start = vu1_bufPtr.tag++;

    TfragVu1Marker.tag->tag = DMA_TAG_NEXT;
    TfragVu1Marker.tag->addr = (unsigned int)vu1_bufPtr.tag;
    TfragVu1Marker.tag->vif0 = 0;
    TfragVu1Marker.tag->vif1 = 0;

    if (drawConfig.tfrag) {
        if (drawConfig.tfrag_texture_paging) {
            int gsEnd;

            ComputeTfragTextureUsage();
            gsEnd = BuildTfragTextureDma(GSloc);

            VU1_texFlush();

            if (gsEnd > TFRAG_GS_MEMORY_LIMIT)
                printf_stub("tfrag texture overflow\n");

            if (TfragGsMax < gsEnd)
                TfragGsMax = gsEnd;
        }
    }

    // Return from the texture uploads to the packets after the opening marker.
    vu1_bufPtr.tag->tag = DMA_TAG_NEXT;
    vu1_bufPtr.tag->addr = (unsigned int)(TfragVu1Marker.tag + 1);
    vu1_bufPtr.tag->vif0 = 0;
    vu1_bufPtr.tag->vif1 = 0;
    vu1_bufPtr.tag++;

    // The first link jumps over the uploads to this point.
    start->tag = DMA_TAG_NEXT;
    start->addr = (unsigned int)vu1_bufPtr.tag;
    start->vif0 = 0;
    start->vif1 = 0;
}

void PatchTfragGifs(void)
{
    TfragGifGroup *group;
    TfragDraw *draw;
    GsTextureLoc *location;
    int drawIndex;
    int count;

    for (group = TfragGifRectify; group->draws != 0; group++) {
        draw = group->draws;
        count = group->count;

        for (drawIndex = 0; drawIndex < count; drawIndex++) {
            location = &TfragGsLocStash[draw->stash_index];

            if (location->base != 0)
                draw->base_tex = (draw->base_tex & GS_TEXTURE_ADDRESS_MASK) | location->base;

            if (location->mip != 0)
                draw->mip_tex = (draw->mip_tex & GS_TEXTURE_ADDRESS_MASK) | location->mip;

            draw++;
        }
    }
}

void DrawTfrag(void)
{
    Mtx4 matrix;

    TfragVu1Marker.tag = vu1_bufPtr.tag++;
    GSloc = GSbase;

    printf_stub3("tfrag texs", 1);

    FastMtx4Identity(&matrix.v0.x);
    FastVec3Scale(&matrix.v3, (Vec4 *)&GameCamera.posX, TFRAG_POSITION_SCALE);
    matrix.v3.w = 1.0f;
    FastMtxTransform(&matrix, &GameCamera.matrix, &matrix);
    VU1_addDataDirect(TFRAG_VU1_MATRIX_ADDRESS, &matrix, 4);
    VU1_addDataDirect(TFRAG_VU1_MATRIX_COPY_ADDRESS, &matrix, 4);

    if (drawConfig.tfrag) {
        FlushCache(0);
        TfragProc();
    }

    printf_stub3("tfrag draw", 2);
    DmaTfragTextures();

    if (drawConfig.tfrag)
        FastFromSpr(TfragSprStash, TFRAG_SPR_RESULT_ADDRESS, TFRAG_SPR_RESULT_QWORDS);

    printf_stub2("tfrag draw", 2);
}
