#include <stddef.h>

#include "common.h"
#include "draw.h"
#include "fastfunc.h"
#include "framebuf.h"
#include "gameglobals.h"
#include "gsregs.h"
#include "initlevel.h"
#include "mathfunc_inline.h"
#include "moby.h"
#include "sce.h"
#include "sky.h"
#include "vuchain.h"

struct SkyGifPageMarker {
    DmaTag *tag;
};

extern SkyGifPageMarker sky_gif_page_markerA;
extern SkyGifPageMarker sky_gif_page_markerB;
extern int GifLoadCnt;
extern unsigned int skyTexturedSetup[];
extern unsigned int skyGouraudSetup[];

unsigned char *g_SkyVuBufferAddrs[2] = {
    (unsigned char *)0x70000000,
    (unsigned char *)0x70001000
};
int g_SkyVuBuffer = 0;

// Sky packet data that nothing reads any more; kept for the data layout.
unsigned long SkyUnusedQword0 = 0;
unsigned long SkyUnusedGifTag = 0x8000000401300000;
unsigned long SkyUnusedQword1 = 0;
unsigned int SkyUnusedColors0[4] = { 0x00386070, 0x00386070, 0x00386070, 0 };
unsigned int SkyUnusedColors1[4] = { 0x802020F0, 0x8020F0F0, 0x80F02080, 0x8020F020 };

void FastEulerToMtx2(Mtx4 *matrix, Vec4 *angles);
void BuildGifTextureDma(void);
void SprDmaToSpr_Start(void *source, int quadwords, void *destination);
void SprDmaToSpr_Wait(void);

void SkyLevelNone(void)
{
    FastMtx4Identity(&outMatrix.v0.x);

    for (int shell_index = 0; shell_index < Sky->shell_cnt; shell_index++)
        SkyDrawShell(shell_index);
}

void SkyLevel_01(void)
{
    const float pi = 3.14159265358979323846f;
    const int slow_rotation_period = 0x40000;
    const int medium_rotation_period = 0x20000;
    const int fast_rotation_period = 0x10000;
    Vec4 rotation;

    Sky->clear_screen = 0;
    ClearVec4Inline(&rotation);

    for (int shell_index = 0; shell_index < Sky->shell_cnt; shell_index++) {
        switch (shell_index) {
        case 2:
            rotation.z = (worldUpdateTime & (slow_rotation_period - 1)) * (2.0f * pi / slow_rotation_period) - pi;
            FastEulerToMtx2(&outMatrix, &rotation);
            break;

        case 3:
            rotation.z = (worldUpdateTime & (medium_rotation_period - 1)) * (2.0f * pi / medium_rotation_period) - pi;
            FastEulerToMtx2(&outMatrix, &rotation);
            break;

        case 4:
            rotation.z = (worldUpdateTime & (fast_rotation_period - 1)) * (2.0f * pi / fast_rotation_period) - pi;
            FastEulerToMtx2(&outMatrix, &rotation);
            break;

        default:
            FastMtx4Identity(&outMatrix.v0.x);
            break;
        }

        SkyDrawShell(shell_index);
    }
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/skyfunc", func_0029EF90);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/skyfunc", func_0029F258);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/skyfunc", SkySpace);

void SetupSkyGifPaging(void)
{
    sky_gif_page_markerA.tag = vu1_bufPtr.tag++;
    printf_stub3("sky texs", 1);

    GSloc = GSbase;
    GifLoadCnt = 0;

    for (int texture_index = 0; texture_index < Sky->tex_cnt; texture_index++)
        Sky->tex_defs[texture_index].tex0 = 0;
}

void DoSkyGifPaging(void)
{
    // The first link jumps to the optional upload packets.
    sky_gif_page_markerB.tag = vu1_bufPtr.tag++;
    sky_gif_page_markerA.tag->tag = DMA_TAG_NEXT;
    sky_gif_page_markerA.tag->addr = (unsigned int)vu1_bufPtr.tag;
    sky_gif_page_markerA.tag->vif0 = 0;
    sky_gif_page_markerA.tag->vif1 = 0;

    if (drawConfig.sky_texture_paging != 0) {
        BuildGifTextureDma();
        VU1_texFlush();
    }

    // Return from the uploads to the sky packets after the opening marker.
    DmaTag *page_link = vu1_bufPtr.tag;
    page_link->tag = DMA_TAG_NEXT;
    vu1_bufPtr.tag->addr = (unsigned int)(sky_gif_page_markerA.tag + 1);
    vu1_bufPtr.tag->vif0 = 0;
    vu1_bufPtr.tag->vif1 = 0;

    // The bypass link rejoins the chain after this return link.
    vu1_bufPtr.tag++;
    sky_gif_page_markerB.tag->tag = DMA_TAG_NEXT;
    sky_gif_page_markerB.tag->addr = (unsigned int)vu1_bufPtr.tag;
    sky_gif_page_markerB.tag->vif0 = 0;
    sky_gif_page_markerB.tag->vif1 = 0;

    gsTextureAllocation.cursor = gsTextureAllocation.start;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/skyfunc", func_0029F660);

void SkyDrawShell(int shell_index)
{
    if (shell_index < Sky->shell_cnt) {
        sky_shell *shell = Sky->shells[shell_index];

        if (shell->gouraud)
            SkyDrawShellGouraud(shell);

        else
            SkyDrawShellTextured(shell);
    }
}

void SkyDrawShellTextured(sky_shell *shell)
{
    const int setup_quadwords = 7;
    void *const transformed = (void *)0x70002000;
    unsigned char visible[shell->cluster_cnt];

    if (!shell->cluster_cnt)
        return;

    SkyBsphereCheck(shell->clusters, shell->cluster_cnt, visible);

    vu1_bufPtr.tag->tag = DMA_TAG_REF | setup_quadwords;
    vu1_bufPtr.tag->addr = (unsigned int)skyTexturedSetup;
    vu1_bufPtr.tag->vif0 = 0;
    *(int *)(vu1_bufPtr.bytes + offsetof(DmaTag, vif1)) = VIF_DIRECT | setup_quadwords;
    vu1_bufPtr.words += 4;

    // Queue the first visible cluster before entering the double-buffered loop.
    g_SkyVuBuffer = 1 - g_SkyVuBuffer;

    if (visible[0] == 1)
        SprDmaToSpr_Start(shell->clusters[0].data, shell->clusters[0].data_size >> 4,
                          g_SkyVuBufferAddrs[g_SkyVuBuffer]);

    for (int cluster_index = 0; cluster_index < shell->cluster_cnt; cluster_index++) {
        if (visible[cluster_index] == 1)
            SprDmaToSpr_Wait();

        g_SkyVuBuffer = 1 - g_SkyVuBuffer;
        int next_index = cluster_index + 1;
        if (next_index < shell->cluster_cnt && visible[next_index] == 1) {
            SprDmaToSpr_Start(shell->clusters[next_index].data, shell->clusters[next_index].data_size >> 4,
                              g_SkyVuBufferAddrs[g_SkyVuBuffer]);
        }

        if (visible[cluster_index] == 1) {
            unsigned char *buffer = g_SkyVuBufferAddrs[1 - g_SkyVuBuffer];
            int vertex_offset = shell->clusters[cluster_index].vert_ofs;
            unsigned char *triangles = buffer + shell->clusters[cluster_index].tri_ofs;
            unsigned char *texcoords = buffer + shell->clusters[cluster_index].st_ofs;

            if (SkyProcessVerts(buffer + vertex_offset, transformed, shell->clusters[cluster_index].vert_cnt) == 0)
                SkyDrawClusterTextured(shell->clusters[cluster_index].tri_cnt, triangles, texcoords, transformed);
        }
    }
}

void SkyDrawShellGouraud(sky_shell *shell)
{
    const int setup_quadwords = 7;
    void *const transformed = (void *)0x70002000;
    unsigned char visible[shell->cluster_cnt];

    if (!shell->cluster_cnt)
        return;

    SkyBsphereCheck(shell->clusters, shell->cluster_cnt, visible);

    vu1_bufPtr.tag->tag = DMA_TAG_REF | setup_quadwords;
    vu1_bufPtr.tag->addr = (unsigned int)skyGouraudSetup;
    vu1_bufPtr.tag->vif0 = 0;
    *(int *)(vu1_bufPtr.bytes + offsetof(DmaTag, vif1)) = VIF_DIRECT | setup_quadwords;
    vu1_bufPtr.words += 4;

    // Queue the first visible cluster before entering the double-buffered loop.
    g_SkyVuBuffer = 1 - g_SkyVuBuffer;

    if (visible[0] == 1)
        SprDmaToSpr_Start(shell->clusters[0].data, shell->clusters[0].data_size >> 4,
                          g_SkyVuBufferAddrs[g_SkyVuBuffer]);

    for (int cluster_index = 0; cluster_index < shell->cluster_cnt; cluster_index++) {
        if (visible[cluster_index] == 1)
            SprDmaToSpr_Wait();

        g_SkyVuBuffer = 1 - g_SkyVuBuffer;
        int next_index = cluster_index + 1;
        if (next_index < shell->cluster_cnt && visible[next_index] == 1) {
            SprDmaToSpr_Start(shell->clusters[next_index].data, shell->clusters[next_index].data_size >> 4,
                              g_SkyVuBufferAddrs[g_SkyVuBuffer]);
        }

        if (visible[cluster_index] == 1) {
            unsigned char *buffer = g_SkyVuBufferAddrs[1 - g_SkyVuBuffer];
            int vertex_offset = shell->clusters[cluster_index].vert_ofs;
            unsigned char *triangles = buffer + shell->clusters[cluster_index].tri_ofs;
            unsigned char *colors = buffer + shell->clusters[cluster_index].st_ofs;

            if (SkyProcessVerts(buffer + vertex_offset, transformed, shell->clusters[cluster_index].vert_cnt) == 0)
                SkyDrawClusterGouraud(shell->clusters[cluster_index].tri_cnt, triangles, colors, transformed);
        }
    }

    VU1_addGSregister(GS_REG_TEST_1, GS_TEST_ATE | GS_TEST_ATST_GEQUAL | GS_TEST_AREF(0x80)
                      | GS_TEST_AFAIL_FB_ONLY | GS_TEST_ZTE | GS_TEST_ZTST_ALWAYS);
    VU1_addGSregister(GS_REG_ZBUF_1, SCE_GS_SET_ZBUF(GSmemZbuf >> 13, 1, 1));
}
