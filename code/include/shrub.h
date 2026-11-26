#ifndef SHRUB_H
#define SHRUB_H

#include "moby.h"
#include "vuchain.h"

// A shrub instance (DL's PS2 layout).
struct ShrubInstance {
    BSphere bSphere;
    float draw_dist;
    char pad[2];
    char flags;
    unsigned char bboard_dist;
    short index;
    unsigned char s_class;
    // Set when no point light is left on it.
    char dir_lights_upd;
    unsigned short dir_lights;
    // Four 4-bit point light slots, 0xF is empty.
    unsigned short point_lights;
};

// Impostor drawn in place of a far shrub.
struct ShrubBillboard {
    float fade_dist;
    float width;
    float height;
    float z_ofs;
    unsigned long tex_1[2];
    unsigned long tex_0[2];
    unsigned long mip_1[2];
};

// One DMA packet of a shrub class: data and its size in bytes.
struct ShrubPacket {
    void *data;
    int size;
};

// A shrub class, followed by its packets.
struct ShrubClass {
    BSphere bSphere;
    float mip_dist;
    short mode_bits;
    short instance_cnt;
    ShrubInstance *instances;
    ShrubBillboard *billboard;
    float scale;
    short o_class;
    short s_class;
    short packet_cnt;
    short pad;
    int *palette;
    int pad_i;
    short drawn_cnt;
    short scis_cnt;
    short bboard_cnt;
    short pad_s[3];
    ShrubPacket packets[0];
};

// Header of the draw list in a shrub packet, 0x10 bytes into its data.
struct ShrubDrawList {
    int draw_cnt;
    // Quadwords between this header and the first draw.
    int skip_qwords;
    int pad[2];
};

// A draw in a shrub packet. Its texture is picked by stash_index.
struct ShrubDraw {
    unsigned char pad_00[0x13];
    unsigned char stash_index;
    unsigned char pad_14[0xC];
    // GS texture address bits of the mipmap level and of the base texture.
    unsigned int mip_tex;
    unsigned char pad_24[0xC];
    unsigned int base_tex;
    unsigned char pad_34[0xC];
};

#define SHRUB_CLASS_MAX 96
#define SHRUB_GS_LOC_MAX 256
#define SHRUB_GIF_RECTIFY_MAX 64

extern ShrubInstance *ShrubInstances;
extern ShrubInstance *ShrubInstanceEnd;

extern ShrubClass *ShrubClasses[SHRUB_CLASS_MAX];
extern GsTextureLoc ShrubGsLocStash[SHRUB_GS_LOC_MAX];
// Class indices whose GS texture addresses need patching, ended by a negative value.
extern int ShrubGifRectify[SHRUB_GIF_RECTIFY_MAX];
extern char ShrubSprStash[0x400];
// Chain packet that opens the shrub DMA stage.
extern Vu1ChainCursor ShrubVu1Marker;
extern int ShrubGsMax;

void ShrubProc(void);
int BuildShrubTextureDma(int gsLocation);
void DmaShrubTextures(void);
void PatchShrubGifs(void);
void DrawShrub(void);

void LightShrubs(void *sprStash);

#endif
