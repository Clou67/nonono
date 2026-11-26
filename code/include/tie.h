#ifndef TIE_H
#define TIE_H

#include "moby.h"
#include "vuchain.h"

// A tie instance (field names from the PS3 project, PS2 offsets).
struct TieInstance {
    BSphere bSphere;
    struct TieMatrix *matrix;
    float drawDist;
    // The occlusion id from the gameplay file, then its occlusion bit as (byte << 8) | mask.
    unsigned short occlIndex;
    unsigned char tieClass;
    // Set when no point light is left on it.
    char dir_lights_upd;
    unsigned short dirLights;
    // Four 4-bit point light slots, 0xF is empty.
    unsigned short point_lights;
};

// A draw in a tie class's DMA packets. Its texture is picked by stash_index.
struct TieDraw {
    // GS texture address bits of the base texture.
    unsigned int base_tex;
    unsigned char pad_04[0x1C];
    // GS texture address bits of the mipmap level.
    unsigned int mip_tex;
    unsigned char pad_24[0xF];
    unsigned char stash_index;
    unsigned char pad_34[0x1C];
};

// One entry of a tie class's packet list (offset relocated by ParseTieClass).
struct TiePacket {
    int offset;
    char pad_04[0xC];
};

// A tie class (RC1 layout; DL's TieClass differs).
struct TieClass {
    TiePacket *packets[3];
    int vert_norms;
    unsigned char pad_10[0x10];
    unsigned char packet_cnt[3];
    unsigned char draw_cnt;
    // Bit 3 hides the class from the current draw pass.
    short mode_bits;
    unsigned short instance_cnt;
    TieInstance *instances;
    TieDraw *draws;
    BSphere bsphere;
    float scale;
    unsigned char pad_44[2];
    unsigned short class_slot;
    float mip_dist;
};

#define TIE_CLASS_MAX 128
#define TIE_GS_LOC_MAX 256
#define TIE_CLASS_HIDDEN 8

// A tie instance's transform (w of the rows: inverse row lengths, then the class scale),
// followed by its vertex colours.
struct TieMatrix {
    Mtx4 mtx;
    char unk40[0x100];
    char colors[0x80];
};

extern TieInstance *TieInstances;
extern TieMatrix *TieMatrices;
extern int TieCnt;
extern float TieDrawDist;
extern TieInstance *TieInstanceEnd;

extern int TieClassIndex;
extern TieClass *TieClasses[TIE_CLASS_MAX];
extern GsTextureLoc TieGsLocStash[TIE_GS_LOC_MAX];
// Classes whose GS texture addresses need patching, ended by a negative value.
extern int TieClassRectify[TIE_CLASS_MAX];
extern char TieSprStash[0x400];
// The draw pass that handles the odd classes keeps its own copies of the three above.
extern GsTextureLoc TieGsLocStashOdd[TIE_GS_LOC_MAX];
extern int TieClassRectifyOdd[TIE_CLASS_MAX];
extern char TieSprStashOdd[0x400];
// Closes the tie chain packet.
extern unsigned char TieChainEnd[0x20];
// Chain packet that opens the tie DMA stage.
extern Vu1ChainCursor TieVu1Marker;
extern int TieGsMax;

void TieProc(void);
int BuildTieTextureDma(int gsLocation);
void LightTies(void *sprStash);
void DmaTieTextures(void);
void PatchTieGifs(void);
void UpdateTieTextures(void);
void RefreshTieLights(void);
void DrawTie(void);
void DrawTiesEx(void);

#endif
