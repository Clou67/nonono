#ifndef TFRAG_H
#define TFRAG_H

#include "moby.h"
#include "vuchain.h"

// A tfrag (field names from the PS3 project, PS2 offsets). Positions are fixed point.
struct Tfrag {
    BSphere bSphere;
    char *data;                     // 0x10: relocated by ParseTfrag
    char unk14[8];
    unsigned short gifOffset;       // 0x1C: of the first TfragGifDef in data
    char unk1E[0xA];
    unsigned char gifCount;         // 0x28
    char unk29[0xC];
    // Set when no point light is left on it.
    char dir_lights_upd;
    // Four 4-bit point light slots, 0xF is empty.
    unsigned short point_lights;
    char unk38[8];
};

// Start of the level's tfrag data.
struct TfragHeader {
    int tfragOffset;    // 0x00: from the header
    int count;          // 0x04
    float lodDist;      // 0x08
};

// A tfrag texture's GIF register block before ParseTfrag fills in its GS register words.
struct TfragGifDef {
    int texIndex;       // 0x00
    int unk_04[3];
    int mipDist;        // 0x10
    int filter;         // 0x14
    int unk_18[2];
    int clampU;         // 0x20
    int clampV;         // 0x24
    int unk_28[10];
};

// A draw in a tfrag's DMA packet. Its texture is picked by stash_index.
struct TfragDraw {
    // GS texture address bits of the base texture.
    unsigned int base_tex;
    unsigned char pad_04[0x1F];
    unsigned char stash_index;
    unsigned char pad_24[0xC];
    // GS texture address bits of the mipmap level.
    unsigned int mip_tex;
    unsigned char pad_34[0x1C];
};

// A run of draws whose GS texture addresses need patching.
struct TfragGifGroup {
    TfragDraw *draws;
    int count;
};

#define TFRAG_GS_LOC_MAX 192
#define TFRAG_GIF_GROUP_MAX 128

extern Tfrag *Tfrags;
extern int TfragsCnt;

extern GsTextureLoc TfragGsLocStash[TFRAG_GS_LOC_MAX];
// Groups to patch, ended by a group with no draws.
extern TfragGifGroup TfragGifRectify[TFRAG_GIF_GROUP_MAX];
extern char TfragSprStash[0x400];
// Distances at which the tfrag level of detail changes, and the same scaled to fixed point.
extern float TfragDists[];
extern int TfragIntDists[];
// Constants for the tfrag VU1 program. SetTfragDists rebuilds them.
extern float TfragSetupConsts[4][4];
// Chain packet that opens the tfrag DMA stage.
extern Vu1ChainCursor TfragVu1Marker;
extern int TfragGsMax;

void TfragProc(void);
void ComputeTfragTextureUsage(void);
int BuildTfragTextureDma(int gsLocation);
void SetTfragDists(void);
void DmaTfragTextures(void);
void PatchTfragGifs(void);
void DrawTfrag(void);

#endif
