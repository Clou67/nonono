#include "common.h"
#include "vuchain.h"
#include "moby.h"
#include "loaders.h"
#include "initlevel.h"
#include "part.h"
#include "sky.h"
#include "tfrag.h"
#include "framebuf.h"
#include "sce.h"
#include "gameglobals.h"
#include "pad.h"
#include "respawn.h"
#include "libc.h"
#include "debug.h"
#include "viewcontext.h"
#include "camera.h"
#include "hero.h"
#include "help.h"
#include "lights.h"
#include "shrub.h"
#include "tie.h"
#include "sound.h"
#include "mobyutil.h"
#include "fastfunc.h"
#include "music.h"
#include "sound.h"
#include "wad.h"
#include "draw.h"
#include "hud.h"
#include "npc.h"
#include "stash.h"
#include "initlevel.h"
#include "mathfunc_inline.h"
#include "sce.h"
#include "fastfunc.h"

void LoadByteGrid(int *grid)
{
    byteGridStride = *grid++;
    byteGridRows = *grid++;
    byteGridMin = *(float *)grid++;
    byteGridMax = *(float *)grid++;
    byteGridData = (unsigned char *)grid;
}

extern int EffectTableCnt;
extern int *EffectTableEntries;
extern int *EffectTableOffsets;

// Fixes up the level's effect table: 0x20-byte entries, then one offset per entry to
// its data, whose second word is also an offset. Both become pointers.
void RelocEffectTable(int *table)
{
    int i, j;
    int count;

    count = *table;
    table += 4;
    EffectTableEntries = table;
    table = (int *)((char *)table + (count << 5));
    EffectTableCnt = count;
    EffectTableOffsets = table;
    for (i = 0; i < EffectTableCnt; i++)
        *(int *)((int)EffectTableOffsets + i * 4) += (int)EffectTableOffsets;

    for (j = 0; j < EffectTableCnt; j++)
        *(int *)(*(int *)((int)EffectTableOffsets + j * 4) + 4) += (int)EffectTableOffsets;
}

int FastLog2(int value);

// Uploads a pif (clut and every mip level) at the GS texture allocation cursor and
// writes its TEX0, TEX1 and MIPTBP1 register values.
int ParseGsRamTextures(PifHeader *pif, unsigned long long *gsRegisters)
{
    PifParser parsed;
    sceGsLoadImage packet;
    int level;
    int size;
    unsigned long long tex0;   // GS TEX0
    unsigned long long mip;    // GS MIPTBP1
    unsigned long long clut;
    unsigned long long lod;    // GS TEX1 mip count

    FastMemSet(&parsed, 0, sizeof(parsed));

    switch (pif->texFormat) {
    case PIF_PSMCT32:
    case PIF_PSMCT16:
        parsed.pClut = 0;
        parsed.cSize = 0;
        break;

    case PIF_PSMT8:
    case PIF_PSMT4:
        parsed.pClut = pif + 1;
        if (pif->texFormat == PIF_PSMT4) {
            if (pif->clutFormat == 0)
                parsed.cSize = 0x40;
            else
                parsed.cSize = 0x20;
        }

        else {
            if (pif->clutFormat == 0)
                parsed.cSize = 0x400;
            else
                parsed.cSize = 0x200;
        }
        break;
    }

    parsed.uLog = FastLog2(pif->uSize);
    parsed.vLog = FastLog2(pif->vSize);
    parsed.pTex[0] = (char *)(pif + 1) + parsed.cSize;

    switch (pif->texFormat) {
    case PIF_PSMCT32:
        parsed.tSize[0] = pif->uSize * pif->vSize * 4;
        break;

    case PIF_PSMCT16:
        parsed.tSize[0] = pif->uSize * pif->vSize * 2;
        break;

    case PIF_PSMT8:
        parsed.tSize[0] = pif->uSize * pif->vSize;
        break;

    case PIF_PSMT4:
        parsed.tSize[0] = (pif->uSize * pif->vSize) >> 1;
        break;
    }

    if (pif->texFormat == PIF_PSMT8 || pif->texFormat == PIF_PSMT4) {
        parsed.cPos = GSloc >> 8;
        if (pif->texFormat == PIF_PSMT4) {
            GSloc += 0x100;
            sceGsSetDefLoadImage(&packet, parsed.cPos, 1, pif->clutFormat, 0, 0, 8, 2);
        }

        else {
            GSloc += parsed.cSize;
            sceGsSetDefLoadImage(&packet, parsed.cPos, 1, pif->clutFormat, 0, 0, 16, 16);
        }

        FlushCache(0);
        sceGsExecLoadImage(&packet, (u_long128 *)parsed.pClut);
        sceGsSyncPath(0, 0);
    }

    for (level = 1; level < pif->mipLevels; level++) {
        parsed.tSize[level] = parsed.tSize[level - 1] >> 2;
        parsed.pTex[level] = (char *)parsed.pTex[level - 1] + parsed.tSize[level - 1];
    }

    for (level = 0; level < pif->mipLevels; level++) {
        parsed.tbw[level] = pif->uSize >> (level + 6);
        if (parsed.tbw[level] <= 0)
            parsed.tbw[level] = 1;

        parsed.tPos[level] = GSloc >> 8;
        sceGsSetDefLoadImage(&packet, parsed.tPos[level], parsed.tbw[level], pif->texFormat, 0, 0, pif->uSize >> level, pif->vSize >> level);
        FlushCache(0);
        sceGsExecLoadImage(&packet, (u_long128 *)parsed.pTex[level]);
        sceGsSyncPath(0, 0);

        size = parsed.tSize[0] >> (level * 2);
        if (size <= 0xFF)
            size = 0x100;

        GSloc += size;
    }

    tex0 = (unsigned long long)parsed.tPos[0];
    tex0 |= (unsigned long long)parsed.tbw[0] << 14;
    tex0 |= (unsigned long long)pif->texFormat << 20;
    tex0 |= (unsigned long long)parsed.uLog << 26;
    tex0 |= (unsigned long long)parsed.vLog << 30;
    clut = (unsigned long long)parsed.cPos << 37;
    clut |= (unsigned long long)1 << 34;
    tex0 |= clut;
    tex0 |= (unsigned long long)pif->clutFormat << 51;
    tex0 |= (unsigned long long)1 << 63;
    gsRegisters[0] = tex0;

    mip = (unsigned long long)parsed.tPos[1];
    mip |= (unsigned long long)parsed.tbw[1] << 14;
    mip |= (unsigned long long)parsed.tPos[2] << 20;
    mip |= (unsigned long long)parsed.tbw[2] << 34;
    lod = (unsigned long long)(pif->mipLevels - 1) << 2;
    mip |= (unsigned long long)parsed.tPos[3] << 40;
    mip |= (unsigned long long)parsed.tbw[3] << 54;
    gsRegisters[1] = lod | 0xFFA0000000E0ULL;
    gsRegisters[2] = mip;
    return -1;
}

TEXT_PADDING(0x27BD0060, 0x00000000);

// Copies the level's particle texture data into PartTexData, points each particle class's
// texture slot into it, and builds the GS addresses of each particle texture.
void ParseParticleTexs(int *header, int gsBase, int *texDefs, int count)
{
    int classCount = header[0];
    int dataOffset = header[2];
    int dataSize = header[3];
    int *texOffset = header + 4;

    for (int index = 0; index < classCount; index++, texOffset++) {
        if (*texOffset == 0)
            PartTextures[index] = PartTexData;

        else
            PartTextures[index] = (unsigned char *)(*texOffset - (dataOffset - (int)PartTexData));
    }

    FastMemCopy32(PartTexData, (char *)header + dataOffset, dataSize);

    for (PartTexCnt = 0; PartTexCnt < count; PartTexCnt++) {
        int texBlock = gsBase + *texDefs++;
        int texWidth = *texDefs++;
        int clutBlock = gsBase + *texDefs++;
        int clutSize = *texDefs++;

        PartTexs[PartTexCnt].unk_00 = (texBlock << 4) + texWidth;
        PartTexs[PartTexCnt].unk_04 = (clutBlock << 4) + FastLog2(clutSize);
    }
}

// Each texture definition is {clut address, texture address, width, height}.
void ParseEffectTexs(int *texDefs, int count)
{
    for (EffectTexCnt = 0; EffectTexCnt < count; EffectTexCnt++) {
        int clutAddr = *texDefs++;
        int texAddr = *texDefs++;
        int width = *texDefs++;
        int height = *texDefs++;

        EffectTexs[EffectTexCnt].palOfs = clutAddr >> 4;
        EffectTexs[EffectTexCnt].texOfs = texAddr >> 4;
        EffectTexs[EffectTexCnt].uLog = FastLog2(width);
        EffectTexs[EffectTexCnt].vLog = FastLog2(height);
        EffectTexs[EffectTexCnt].tex0 = 0;
    }
}

// Relocates the level's sky file in place. Its texture definitions are rewritten as sky_tex.
void ParseSky(char *data)
{
    SKY *sky = (SKY *)data;

    Sky = sky;
    sky->clear_screen = 1;
    sky->tex_defs = (sky_tex *)((char *)sky->tex_defs + (int)sky);
    sky->tex_data = (char *)sky->tex_data + (int)sky;
    sky->fx_list = sky->fx_list + (int)sky;

    if (sky->sprites)
        sky->sprites = (sky_sprite *)((char *)sky->sprites + (int)sky);

    int *texDef = (int *)Sky->tex_defs;

    for (int tex = 0; tex < Sky->tex_cnt; tex++) {
        int clutAddr = *texDef++;
        int texAddr = *texDef++;
        int width = *texDef++;
        int height = *texDef++;

        Sky->tex_defs[tex].pal_ofs = clutAddr >> 4;
        Sky->tex_defs[tex].tex_ofs = texAddr >> 4;
        Sky->tex_defs[tex].u_log = FastLog2(width);
        Sky->tex_defs[tex].v_log = FastLog2(height);
        Sky->tex_defs[tex].tex0 = 0;
    }

    for (int shellIndex = 0; shellIndex < Sky->shell_cnt; shellIndex++) {
        Sky->shells[shellIndex] = (sky_shell *)((char *)Sky->shells[shellIndex] + (int)sky);

        sky_shell *shell = Sky->shells[shellIndex];

        for (int cluster = 0; cluster < shell->cluster_cnt; cluster++)
            shell->clusters[cluster].data = (char *)shell->clusters[cluster].data + (int)sky;
    }
}

// Texture definitions of the spaceship pack's two moby classes (their clut and image blocks
// are filled in at load) and the texture remap both use. They start loaders.cpp's small data.
TextureDef ShipTexDefA = { 0, 0x100, 0x100, 4, 0, 0, 0 };
TextureDef ShipTexDefB = { 0, 0x80, 0x80, 1, 0, 0, 0 };
unsigned char ShipTexRefs[16] = {
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
};

// The spaceship pack: offsets of its two moby classes and their textures.
struct SpaceshipPack {
    int mobyA;
    int texturesA;
    int mobyB;
    int texturesB;
};

#define SHIP_TEXTURE_A_SIZE 0x14000
#define SHIP_TEXTURE_B_SIZE 0x4000
#define SHIP_TEXTURE_IMAGE 0x430        // the image follows the 0x30-byte header and the 256-colour clut

extern int SpaceshipOClassesB[];
// Retail reads GSmemBase here as the word after GSmemZbuf, which keeps the delay-slot loads
// off $gp.
extern int GSmemZbuf __attribute__((section(".sdata")));
#define GSmemAfterZbuf ((&GSmemZbuf)[1])
extern int ShipPackLoaded;
extern int ShipPackReady;
extern int ShipPackUnk;
extern int MobySdata15FFC8;     // moby texture count
extern int MobyTexLocs[];
extern TextureDef MobyTexDefs[];

// Copies the current spaceship's pack out of its WAD buffer, uploads its two images and
// cluts to the GS blocks the level header reserved, and registers its two moby classes.
// Returns the end of the pack's textures.
char *ParseMobyPack(char *pack, LevelCoreHeader *header)
{
    sceGsLoadImage image;
    int upload = 0;
    int mobyA;
    int texturesAOffset;
    int mobyB;
    int texturesBOffset;
    char *texturesA;
    char *destination;
    char *source;
    char *packStart;
    int texIndex;
    int nextTexIndex;

    FastMemCopy16(pack, LevelLoad.spaceships, bootAssets.spaceships[bootSpaceTransitionState.shipVariant + 1].length << 11);
    mobyA = ((SpaceshipPack *)pack)->mobyA;
    texturesAOffset = ((SpaceshipPack *)pack)->texturesA;
    texturesA = pack + texturesAOffset;
    mobyB = ((SpaceshipPack *)pack)->mobyB;
    texturesBOffset = ((SpaceshipPack *)pack)->texturesB;
    do {
        if (upload == 0) {
            sceGsSetDefLoadImage(&image, (GSmemAfterZbuf + header->shipGsRam[0]) >> 8, 1, GS_PSMT8, 0, 0, 64, 64);
            destination = pack + texturesAOffset;
            source = texturesA + 0x14430;
        } else if (upload == 1) {
            sceGsSetDefLoadImage(&image, (GSmemAfterZbuf + header->shipGsRam[1]) >> 8, 1, GS_PSMT8, 0, 0, 32, 32);
            destination = pack + texturesAOffset;
            source = texturesA + 0x15430;
        } else if (upload == 2) {
            sceGsSetDefLoadImage(&image, (GSmemAfterZbuf + header->shipGsRam[2]) >> 8, 1, GS_PSMCT32, 0, 0, 16, 16);
            source = texturesA + 0x30;
            destination = pack + texturesAOffset;
        } else {
            sceGsSetDefLoadImage(&image, (GSmemAfterZbuf + header->shipGsRam[3]) >> 8, 1, GS_PSMCT32, 0, 0, 16, 16);
            destination = pack + texturesAOffset;
            source = pack + texturesBOffset + 0x30;
        }
        FlushCache(0);
        upload++;
        sceGsExecLoadImage(&image, (u_long128 *)source);
        sceGsSyncPath(0, 0);
    } while (upload < 4);

    // The images are packed down over the pack's texture area.
    packStart = pack;
    pack = destination;
    ShipTexDefA.clut = header->shipGsRam[2] >> 8;
    texIndex = MobySdata15FFC8;
    ShipTexDefA.mip1 = header->shipGsRam[0] >> 8;
    ShipTexDefA.mip2 = header->shipGsRam[1] >> 8;
    CopyVec4Inline((Vec4 *)&MobyTexDefs[texIndex], (Vec4 *)&ShipTexDefA);
    MobyTexLocs[texIndex] = (int)pack - 0x80000000;
    FastMemCopy16(pack, packStart + texturesAOffset + SHIP_TEXTURE_IMAGE, SHIP_TEXTURE_A_SIZE);
    pack += SHIP_TEXTURE_A_SIZE;
    ShipTexRefs[0] = MobySdata15FFC8;
    if ((unsigned char)MobyClassLookup[SpaceshipOClasses[bootSpaceTransitionState.shipVariant]] == 0xFF)
        ParseMoby(packStart + mobyA, (short *)(&ShipTexDefA - MobySdata15FFC8), (char *)ShipTexRefs,
                  SpaceshipOClasses[bootSpaceTransitionState.shipVariant]);

    nextTexIndex = MobySdata15FFC8 + 1;
    ShipTexDefB.clut = header->shipGsRam[3] >> 8;
    MobySdata15FFC8 = nextTexIndex;
    CopyVec4Inline((Vec4 *)&MobyTexDefs[nextTexIndex], (Vec4 *)&ShipTexDefB);
    MobyTexLocs[nextTexIndex] = (int)pack + 0x70000000;
    FastMemCopy16(pack, packStart + texturesBOffset + SHIP_TEXTURE_IMAGE, SHIP_TEXTURE_B_SIZE);
    pack += SHIP_TEXTURE_B_SIZE;
    ShipTexRefs[0] = MobySdata15FFC8;
    if ((unsigned char)MobyClassLookup[SpaceshipOClassesB[bootSpaceTransitionState.shipVariant]] == 0xFF)
        ParseMoby(packStart + mobyB, (short *)(&ShipTexDefB - MobySdata15FFC8), (char *)ShipTexRefs,
                  SpaceshipOClassesB[bootSpaceTransitionState.shipVariant]);

    ShipPackLoaded = 1;
    ShipPackReady = 1;
    MobySdata15FFC8 = MobySdata15FFC8 + 1;
    ShipPackUnk = 0;
    return pack;
}

void Hud_SetupBank(int bank, void *data);
void Hud_UploadBankIcons(int bank, char *staging, int upload);

#define ALIGN_64(size) (((size) + 0x3F) & ~0x3FU)

// The HUD heap allocator takes the allocation's alignment and source location too (from a
// debug signature); the release function ignores them.
#define HUD_HEAP_ALLOC(size, line) \
    ((void *(*)(int, int, const char *, int))HudHeap_Alloc)(size, 0, "loaders.cpp", line)

// Loads the level's HUD data: the header into the HUD heap, then its banks: bank 0 is
// decompressed into the second VU1 chain buffer, its icons uploaded and the bank sent to the
// IOP stash; bank 1 goes into the HUD heap; banks 2 to 4 are sent to the stash.
void LoadHudBanks(void)
{
    LevelWadHeader *wad = (LevelWadHeader *)levelRoot;
    HudBankHeader *header;
    void *bank1;
    int bank;
    unsigned int size;
    unsigned int qwords;
    char *staging;
    unsigned int *bankSize;
    int *wadBankSize;
    HudStateData *hud;
    MEMSLOTS *slots;

    bankSize = (unsigned int *)HudState.bankSizes;
    wadBankSize = &wad->hudBanks[0].size;
    for (bank = 0; bank < 5; bank++) {
        *bankSize++ = ALIGN_64(*wadBankSize);
        wadBankSize += 2;
    }

    size = ALIGN_64(wad->hudHeader.size);
    slots = &MemSlots;
    header = (HudBankHeader *)HUD_HEAP_ALLOC(size, 570);
    hud = &HudState;
    FastMemCopy16(header, (void *)(wad->hudHeader.offset + (int)wad), size);
    hud->header = header;
    hud->icons = (HudIconTableEntry *)((char *)header + header->icons);
    staging = (char *)slots->vu1_chain[1] + 0x60000;
    hud->frameRefs = (char *)header + header->frameRefs;
    hud->palettePages = (char *)header + header->palettePages;
    hud->imagePages = (char *)header + header->imagePages;

    if (header->hasBank0) {
        qwords = ALIGN_64(wad->hudBanks[0].size) >> 4;
        LoadCompressedHudBank(0, staging);
        hud->header->bankStash[0] = Stash_SendData((void *)(wad->hudBanks[0].offset + (int)wad), qwords, qwords, "hud bank 0");
        Hud_UploadBankIcons(0, staging, 1);
    }

    if (hud->header->bank1Size) {
        bank1 = HUD_HEAP_ALLOC(hud->header->bank1Size, 609);
        LoadCompressedHudBank(1, (char *)bank1);
        FlushCache(0);
        Hud_SetupBank(1, bank1);
    }

    if (hud->header->hasBank2) {
        unsigned int bank2Qwords = ALIGN_64(wad->hudBanks[2].size) >> 4;

        hud->header->bankStash[2] = Stash_SendData((void *)(wad->hudBanks[2].offset + (int)wad), bank2Qwords, bank2Qwords, "hud bank 2");
    }

    if (hud->header->hasBank3) {
        unsigned int bank3Qwords = ALIGN_64(wad->hudBanks[3].size) >> 4;

        hud->header->bankStash[3] = Stash_SendData((void *)(wad->hudBanks[3].offset + (int)wad), bank3Qwords, bank3Qwords, "hud bank 3");
    }

    if (hud->header->hasBank4) {
        unsigned int bank4Qwords = ALIGN_64(wad->hudBanks[4].size) >> 4;

        hud->header->bankStash[4] = Stash_SendData((void *)(wad->hudBanks[4].offset + (int)wad), bank4Qwords, bank4Qwords, "hud bank 4");
    }
}

void LoadCompressedHudBank(int bank, char *destination)
{
    char *aligned = (char *)((unsigned int)(destination + 15) & 0xFFFFFFF0);

    // The bank's offset is relative to the start of the level WAD buffer.
    if (aligned)
        WadDecompress((void *)(((LevelWadHeader *)levelRoot)->hudBanks[bank].offset + (int)levelRoot), aligned);

    HudState.header->bankData[bank] = 0;
}

// Writes a class texture's TEX1, CLAMP, TEX0 and MIPTBP1 register words into a GIF packet
// (one per qword). Negative indices are the special textures, as in SetUpVisGifViewer.
void SetUpVisGif(unsigned long *gifRegs, short *texDef, int mipDist, int filter, int clampU, int clampV, int index)
{
    int texWidth = texDef[TEXDEF_WIDTH] >> 6;
    int mipWidth = texDef[TEXDEF_WIDTH] >> 7;

    if (texWidth <= 0)
        texWidth = 1;

    if (mipWidth <= 0)
        mipWidth = 1;

    int uLog = FastLog2(texDef[TEXDEF_WIDTH]);
    int vLog = FastLog2(texDef[TEXDEF_HEIGHT]);
    int gsBlock = GSmemBase >> 8;
    int mip2Block = texDef[TEXDEF_MIP2] + gsBlock;
    int clutBlock = texDef[TEXDEF_CLUT] + gsBlock;
    int mip1Block = texDef[TEXDEF_MIP1] + gsBlock;
    int mipCount = texDef[TEXDEF_MIP_COUNT];

    if (index >= 0) {
        unsigned long filterBits = ((unsigned long)filter << 6) | 0x20;
        unsigned long tex1 = ((unsigned long)(mipCount - 1) << 2) | filterBits;

        tex1 |= (unsigned long)mipDist << 32;
        *gifRegs = tex1;
        gifRegs += 2;
        *gifRegs = clampU | ((unsigned long)clampV << 2) | ((unsigned long)index << 24);
        gifRegs += 2;

        unsigned long format = ((unsigned long)uLog << 26) | 0x1300000;
        unsigned long tex0 = (((unsigned long)texWidth << 14) | format) | ((unsigned long)vLog << 30);
        unsigned long tex0Clut = ((unsigned long)0x8000 << 19) | ((unsigned long)clutBlock << 37);
        unsigned long miptbp = ((unsigned long)mipWidth << 14) | ((unsigned long)mip1Block << 20);
        unsigned long miptbp2 = ((unsigned long)mip2Block << 40) | ((unsigned long)0x8000 << 19);

        miptbp |= miptbp2;
        tex0 |= tex0Clut;
        tex0 |= (unsigned long)-1 << 63;
        miptbp |= (unsigned long)0x8000 << 39;
        *gifRegs = tex0;
        gifRegs[2] = miptbp;
    }

    else if (index < -1) {
        unsigned long *special = VisGifSpecialTemplate;

        if (index == -3)
            special = VisGifSpecialTemplateAlt;

        *gifRegs = ((unsigned long)filter << 6) | 0x20 | ((unsigned long)mipDist << 32);
        gifRegs += 2;
        *gifRegs = 5;
        gifRegs += 2;
        *gifRegs = special[0];
        gifRegs[2] = special[2];
    }

    else {
        *gifRegs = ((unsigned long)filter << 6) | 0x20 | ((unsigned long)mipDist << 32);
        gifRegs += 2;
        *gifRegs = 5;
        gifRegs += 2;
        *gifRegs = ((((unsigned long)0x8000 << 29) | 0x9980) << 19) | 0x7FFB;
        gifRegs[2] = 0;
    }
}

// Writes a texture's TEX1 and CLAMP-style register words into a GIF packet (one per qword),
// then two words from its row of VisGifTemplates. A negative index is a special one:
// -2 and -3 use the fixed special rows, -1 a constant.
void SetUpVisGifViewer(unsigned long *gifRegs, int mipDist, int filter, int clampU, int clampV, int index)
{
    unsigned long first = VisGifTemplates[index * 3];
    unsigned long mipLevels = VisGifTemplates[index * 3 + 1];
    unsigned long last = VisGifTemplates[index * 3 + 2];

    if (index >= 0) {
        unsigned long filterBits = ((unsigned long)filter << 6) | 0x20;

        *gifRegs = (mipLevels & 0x1C) | filterBits | ((unsigned long)mipDist << 32);
        gifRegs += 2;
        *gifRegs = clampU | ((unsigned long)clampV << 2) | ((unsigned long)index << 24);
        gifRegs += 2;
        *gifRegs = first;
        gifRegs[2] = last;
    }

    else if (index < -1) {
        unsigned long *special = VisGifSpecialTemplate;

        if (index == -3)
            special = VisGifSpecialTemplateAlt;

        unsigned long filterBits = (unsigned long)filter << 6;
        unsigned long lodBits = ((unsigned long)mipDist << 32) | 0x20;

        *gifRegs = filterBits | lodBits;
        gifRegs += 2;
        *gifRegs = 5;
        gifRegs += 2;
        *gifRegs = special[0];
        gifRegs[2] = special[2];
    }

    else {
        unsigned long filterBits = (unsigned long)filter << 6;
        unsigned long lodBits = ((unsigned long)mipDist << 32) | 0x20;

        *gifRegs = filterBits | lodBits;
        gifRegs += 2;
        *gifRegs = 5;
        gifRegs += 2;
        *gifRegs = 0x80000004CC007FFB;
        gifRegs[2] = 0;
    }
}

// Uploads the level's permanent textures into GS memory from GSmemBase on; GSloc and
// GSbase end up just past them.
void ParsePermGsRam(char *data, int count, PermGsTexture *texture)
{
    sceGsLoadImage loadImage;

    GSbase = GSloc = GSmemBase;

    for (int index = 0; index < count; index++, texture++) {
        char *image = data + texture->offset;
        int size = texture->size;
        int gsAddr = GSloc;
        int width = size & 0xFFFF;
        int height = size >> 16;

        if (texture->psm == GS_PSMT8) {
            int bufferWidth = width >> 6;

            if (bufferWidth < 1)
                bufferWidth = 1;

            sceGsSetDefLoadImage(&loadImage, gsAddr >> 8, bufferWidth, GS_PSMT8, 0, 0, width, height);

            int bytes = width * height;

            if (bytes < 0x100)
                bytes = 0x100;

            GSloc += bytes;
        }

        else if (texture->psm == GS_PSMCT16) {
            sceGsSetDefLoadImage(&loadImage, gsAddr >> 8, 1, GS_PSMCT16, 0, 0, 16, 16);
            GSloc += 0x200;
        }

        else if (texture->psm == GS_PSMCT32) {
            sceGsSetDefLoadImage(&loadImage, gsAddr >> 8, 1, GS_PSMCT32, 0, 0, 16, 16);
            GSloc += 0x400;
        }

        FlushCache(0);
        sceGsExecLoadImage(&loadImage, (u_long128 *)image);
        sceGsSyncPath(0, 0);
    }

    GSbase = GSloc;
}

void ParseMobySeq(MobyClass *mobyClass, int animation)
{
    MobySeq *sequence = mobyClass->animations[animation];
    char *base = (char *)sequence;

    if (sequence->triggers)
        sequence->triggers = (short *)(base + (int)sequence->triggers);

    if (sequence->frameCount) {
        int index = 0;
        MobySeqFrame **frame = sequence->frames;
        do {
            *frame = (MobySeqFrame *)(base + (int)*frame);
            ++frame;
        } while (++index < sequence->frameCount);
    }
}

void SetUpVisGifViewer(unsigned long *gifRegs, int mipDist, int filter, int clampU, int clampV, int index);

#define MOBY_GIF_STASH_END 0xFF

// Turns every offset in a loaded moby class into a pointer and sets up its texture gifs,
// remapping the class's texture indices through texRefs.
void ParseMobyClass(MobyClass *mobyClass, short *texDefs, char *texRefs, int oClass)
{
    char *base = (char *)mobyClass;
    int packetCount = mobyClass->packetCount0 + mobyClass->packetCount1 + mobyClass->metalCount;
    unsigned char *texLookup;
    MobyPacket *packet;
    int index;
    int sequenceIndex;
    int packetIndex;

    if (mobyClass->packets) {
        mobyClass->packets = (MobyPacket *)(base + (int)mobyClass->packets);
        MobyPacket *relocated = mobyClass->packets;

        if (packetCount) {
            int remaining = packetCount;
            do {
                remaining--;
                relocated->gifs = (MobyGifDef *)((char *)relocated->gifs + (int)base);
                relocated->data = (char *)relocated->data + (int)base;
                relocated++;
            } while (remaining);
        }
    }

    if (mobyClass->collision)
        mobyClass->collision = (MobyCollPrims *)(base + (int)mobyClass->collision);

    if (mobyClass->skeleton)
        mobyClass->skeleton = base + (int)mobyClass->skeleton;

    if (mobyClass->commonTranslations)
        mobyClass->commonTranslations = (Vec4 *)(base + (int)mobyClass->commonTranslations);

    if (mobyClass->animationJoints) {
        int jointCount;

        mobyClass->animationJoints = (MobyAnimationJoints *)(base + (int)mobyClass->animationJoints);
        jointCount = mobyClass->animationJoints->count;
        // Word 0 of the table is the joint count; the joint pointers follow it.
        for (index = 0; index < jointCount; index++)
            ((int *)mobyClass->animationJoints)[index + 1] += (int)base;
    }

    if (mobyClass->gifUsage) {
        MobyGifUsage *usage;

        mobyClass->gifUsage = (MobyGifUsage *)(base + (int)mobyClass->gifUsage);
        for (usage = mobyClass->gifUsage;; usage++) {
            unsigned char *stash = usage->stash;

            usage->draws = (MobyDraw *)((char *)usage->draws + (int)base);
            if (*stash != MOBY_GIF_STASH_END) {
                do {
                    *stash = texRefs[*stash];
                    stash++;
                } while (*stash != MOBY_GIF_STASH_END);
            }

            if ((int)usage->draws < 0)
                break;
        }
    }

    if (mobyClass->soundDefs)
        mobyClass->soundDefs = (SoundDef *)(base + (int)mobyClass->soundDefs);

    for (sequenceIndex = 0; sequenceIndex < mobyClass->sequenceCount; sequenceIndex++) {
        if (mobyClass->animations[sequenceIndex]) {
            MobySeq *sequence = (MobySeq *)(base + (int)mobyClass->animations[sequenceIndex]);
            int frame;

            mobyClass->animations[sequenceIndex] = sequence;
            if (sequence->triggers)
                sequence->triggers = (short *)(base + (int)sequence->triggers);

            for (frame = 0; frame < sequence->frameCount; frame++)
                sequence->frames[frame] = (MobySeqFrame *)(base + (int)sequence->frames[frame]);
        }
    }

    texLookup = (unsigned char *)&MobyTexLookup[(unsigned char)MobyClassLookup[oClass] * 16];
    CopyVec4Inline((Vec4 *)texLookup, (Vec4 *)texRefs);

    packet = mobyClass->packets;
    for (packetIndex = 0; packetIndex < packetCount; packetIndex++, packet++) {
        int gifQuads = packet->counts >> 16;
        int end = packet->counts & 0xFFFF;
        MobyGifDef *gif;
        int quad;

        packet->counts = end;
        gif = (MobyGifDef *)((char *)packet->gifs + (end - gifQuads) * 16);
        for (quad = 0; quad < gifQuads; quad += 4) {
            int texIndex = gif->texIndex;

            if (texIndex >= 0)
                texIndex = texLookup[texIndex];

            if (texDefs)
                SetUpVisGif((unsigned long *)gif, texDefs + texIndex * 8, gif->mipDist, gif->filter, gif->clampU, gif->clampV, texIndex);
            else
                SetUpVisGifViewer((unsigned long *)gif, gif->mipDist, gif->filter, gif->clampU, gif->clampV, texIndex);

            gif++;
        }
    }
}

// Gives a level moby class the next mClass slot, then relocates it (a null class only gets its functions).
void ParseMoby(char *classData, short *texDefs, char *texRefs, int oClass)
{
    MobyClass *mobyClass = (MobyClass *)classData;

    MobyClassLookup[oClass] = MobyClassIndex;
    MobyOClasses[MobyClassIndex] = oClass;
    MobyClasses[MobyClassIndex] = mobyClass;

    if (mobyClass == 0) {
        SetupMobyFunctions(oClass);
        MobyClassIndex++;
        return;
    }

    MobyMipDists[MobyClassIndex] = mobyClass->mipDistance;
    SetupMobyFunctions(oClass);
    MobyClassIndex++;
    ParseMobyClass(mobyClass, texDefs, texRefs, oClass);
}

// A class draw's GS register block as stored in the level file and filled in by the loader
// (the same memory as TieDraw / ShrubDraw): TEX0, TEX1, MIPTBP1 and CLAMP, one per qword.
// Before loading, TEX1 holds the mip distance and filter and CLAMP the wrap modes.
union GsRegWord {
    unsigned long d;
    int w[2];
};

struct ClassDrawRegs {
    GsRegWord tex0;         // 0x00
    long pad08;
    GsRegWord tex1;         // 0x10
    long pad18;
    GsRegWord miptbp1;      // 0x20
    long pad28;
    GsRegWord clamp;        // 0x30
    long pad38;
    unsigned long end;      // 0x40
    long pad48;
};

extern short TieClassOClasses[TIE_CLASS_MAX];

// Registers a tie class: relocates its packets and draws and builds each draw's GS texture
// registers, from the level texture (or, with no textures, from the special templates).
void ParseTieClass(char *classData, TextureDef *texDefs, char *texRefs, int oClass)
{
    TieClass *tieClass = (TieClass *)classData;
    int slot;
    int mipDist;
    int packet;
    int draw;
    int vertNorms;
    ClassDrawRegs *draws;
    ClassDrawRegs *regs;
    unsigned char *classTexRefs;
    int tex;
    int mipDistance;
    int material;
    int filter;
    int clampU;
    int clampV;
    int vLog;
    int width;
    int gsBlock;
    int mip2;
    int mip1;
    int mipCount;
    int template3;
    int entry;
    unsigned long tex1;
    unsigned long clamp;
    unsigned long templateTex1;
    unsigned long templateTex0;
    unsigned long templateMip;
    TextureDef *texDef;

    TieClassOClasses[TieClassIndex] = oClass;
    TieClassLookup[oClass] = TieClassIndex;
    TieClasses[TieClassIndex] = tieClass;
    tieClass->class_slot = TieClassIndex;
    mipDist = FastFloatToInt(tieClass->mip_dist * 1024.0f);
    slot = TieClassIndex;
    TieClassIndex = slot + 1;
    TieMipDists[slot] = mipDist;

    tieClass->instances = 0;
    tieClass->instance_cnt = 0;

    for (packet = 0; packet < 3; packet++) {
        if (tieClass->packets[packet] != 0) {
            tieClass->packets[packet] = (TiePacket *)((int)tieClass->packets[packet] + (int)tieClass);
            for (entry = 0; entry < tieClass->packet_cnt[packet]; entry++)
                tieClass->packets[packet][entry].offset += (int)tieClass->packets[packet];
        }
    }

    vertNorms = tieClass->vert_norms + (int)tieClass;
    draws = (ClassDrawRegs *)((int)tieClass->draws + (int)tieClass);
    tieClass->vert_norms = vertNorms;
    tieClass->draws = (TieDraw *)draws;

    classTexRefs = (unsigned char *)&TieTexLookup[(unsigned char)TieClassLookup[oClass]];
    CopyVec4Inline((Vec4 *)classTexRefs, (Vec4 *)texRefs);

    for (draw = 0, regs = draws; draw < tieClass->draw_cnt; draw++, regs++) {
        mipDistance = regs->tex1.w[0];
        material = classTexRefs[draw];
        filter = regs->tex1.w[1];
        clampU = regs->clamp.w[0];
        clampV = regs->clamp.w[1];

        if (texDefs != 0) {
            int texWidth;
            int mipWidth;
            int uLog;
            unsigned long tex0;
            unsigned long miptbp1;

            texDef = &texDefs[material];
            width = (unsigned short)texDef->width << 16;
            texWidth = width >> 22;
            mipWidth = width >> 23;
            if (texWidth <= 0)
                texWidth = 1;

            if (mipWidth <= 0)
                mipWidth = 1;

            uLog = FastLog2(width >> 16);
            vLog = FastLog2(texDef->height);
            gsBlock = GSmemBase >> 8;
            mip2 = texDef->mip2 + gsBlock;
            mip1 = texDef->mip1 + gsBlock;
            width = texDef->clut + gsBlock;
            mipCount = texDef->mipCount;

            // The signed/unsigned casts keep the compiler from regrouping the ORs, as in retail.
            tex0 = (long)((unsigned long)(((long)texWidth << 14) | ((long)GS_PSMT8 << 20) | ((long)uLog << 26))
                          | ((unsigned long)vLog << 30) | ((unsigned long)1 << 34) | ((unsigned long)width << 37))
                 | ((long)4 << 61);
            tex1 = (long)(((unsigned long)(mipCount - 1) << 2) | ((unsigned long)1 << 5) | ((unsigned long)filter << 6))
                 | ((long)mipDistance << 32);
            miptbp1 = (long)(((unsigned long)mipWidth << 14) | ((unsigned long)mip1 << 20) | ((unsigned long)1 << 34)
                             | ((unsigned long)mip2 << 40))
                    | ((long)1 << 54);
            clamp = (unsigned long)clampU | ((unsigned long)clampV << 2) | ((unsigned long)material << 24);

            regs->tex0.d = tex0;
            regs->tex1.d = tex1;
            regs->miptbp1.d = miptbp1;
            regs->clamp.d = clamp;
            regs->end = 0;
        } else {
            unsigned long filterBits;
            unsigned long tex1Word;
            unsigned long clampWord;

            templateTex0 = VisGifTemplates[material * 3];
            template3 = material * 3;
            templateTex1 = VisGifTemplates[template3 + 1];
            templateMip = VisGifTemplates[template3 + 2];
            filterBits = ((unsigned long)filter << 6) | 0x20;
            tex1Word = (templateTex1 & 0x1C) | filterBits | ((unsigned long)mipDistance << 32);
            clampWord = (unsigned long)clampU | ((unsigned long)clampV << 2) | ((unsigned long)material << 24);
            regs->tex0.d = templateTex0;
            regs->tex1.d = tex1Word;
            regs->miptbp1.d = templateMip;
            regs->clamp.d = clampWord;
            regs->end = 0;
        }
    }
}

// A shrub draw's GS register block (the same memory as ShrubDraw): TEX1, CLAMP, MIPTBP1
// and TEX0, one per qword. Before loading, TEX1 holds the mip distance and filter and
// CLAMP the wrap modes; the material index sits in the MIPTBP1 slot.
struct ShrubDrawRegs {
    GsRegWord tex1;         // 0x00
    long pad08;
    GsRegWord clamp;        // 0x10
    long pad18;
    GsRegWord miptbp1;      // 0x20
    long pad28;
    GsRegWord tex0;         // 0x30
    long pad38;
};

// The texture of a shrub class's billboard.
struct BillboardTexDef {
    short width;
    short height;
    short mipCount;
    short clut;
    short tex;
    short mip1;
    short mip2;
    short mip3;
};

extern short ShrubClassOClasses[];
extern int ShrubClassIndex;

// Registers a shrub class: relocates its packets, builds its billboard's GS texture
// registers and each draw's, from the level textures (or the special templates).
void ParseShrubClass(char *classData, TextureDef *texDefs, char *texRefs, BillboardTexDef *billboardTex, int oClass)
{
    ShrubClass *shrubClass = (ShrubClass *)classData;
    int packet;
    int index;
    int mipDist;
    unsigned char *classTexRefs;
    ShrubBillboard *packedBillboard;
    ShrubBillboard *billboard;
    ShrubDrawList *list;
    ShrubDrawRegs *regs;

    ShrubClassLookup[oClass] = ShrubClassIndex;
    ShrubClassOClasses[ShrubClassIndex] = oClass;
    ShrubClasses[ShrubClassIndex] = shrubClass;
    shrubClass->s_class = ShrubClassIndex;
    mipDist = FastFloatToInt(shrubClass->mip_dist * 1024.0f);
    ShrubMipDists[ShrubClassIndex] = mipDist;
    ShrubClassIndex++;
    shrubClass->instances = 0;
    shrubClass->instance_cnt = 0;

    if (shrubClass->palette != 0)
        shrubClass->palette = (int *)((int)shrubClass->palette + (int)shrubClass);

    for (packet = 0; packet < shrubClass->packet_cnt; packet++)
        shrubClass->packets[packet].data = (void *)((int)shrubClass->packets[packet].data + (int)shrubClass);

    packedBillboard = shrubClass->billboard;
    if (packedBillboard != 0) {
        int mipDistance;
        int filter;

        billboard = (ShrubBillboard *)((int)packedBillboard + (int)shrubClass);
        shrubClass->billboard = billboard;
        mipDistance = ((GsRegWord *)billboard->tex_1)->w[0];
        filter = ((GsRegWord *)billboard->tex_1)->w[1];
        if (billboardTex != 0) {
            int widths[4];
            int uLog;
            int vLog;
            int gsBlock;
            unsigned long miptbp1;
            int width;
            int level;
            int mipCount;
            int clut;
            int tex;
            int mip1;
            int mip2;
            int mip3;

            width = billboardTex->width;
            for (level = 0; level < 4; level++) {
                widths[level] = width >> (level + 6);
                if (widths[level] <= 0)
                    widths[level] = 1;
            }

            uLog = FastLog2(billboardTex->width);
            vLog = FastLog2(billboardTex->height);
            mipCount = billboardTex->mipCount;
            clut = billboardTex->clut;
            gsBlock = GSmemBase >> 8;
            tex = billboardTex->tex + gsBlock;
            mip1 = billboardTex->mip1 + gsBlock;
            mip2 = billboardTex->mip2 + gsBlock;
            mip3 = billboardTex->mip3 + gsBlock;

            // The signed/unsigned casts keep the compiler from regrouping the ORs, as in retail.
            billboard->tex_1[0] = (long)(((unsigned long)(mipCount - 1) << 2) | ((unsigned long)1 << 5) | ((unsigned long)filter << 6))
                                | ((long)mipDistance << 32);
            billboard->tex_0[0] = (long)((unsigned long)((long)tex | ((long)widths[0] << 14) | ((long)GS_PSMT8 << 20) | ((long)uLog << 26))
                                         | ((unsigned long)vLog << 30) | ((unsigned long)1 << 34) | ((unsigned long)(clut + gsBlock) << 37))
                                | ((long)4 << 61);
            miptbp1 = (unsigned long)mip1 | ((unsigned long)widths[1] << 14);
            miptbp1 |= (unsigned long)mip2 << 20;
            miptbp1 |= (unsigned long)widths[2] << 34;
            miptbp1 |= (unsigned long)mip3 << 40;
            miptbp1 |= (unsigned long)widths[3] << 54;
            billboard->mip_1[0] = miptbp1;
        } else {
            int templateIndex;
            int template3;
            unsigned long templateTex0;
            unsigned long templateTex1;
            unsigned long templateMip;
            unsigned long filterBits;
            unsigned long tex1;

            // The last template.
            for (templateIndex = 0; VisGifTemplates[(templateIndex + 1) * 3] != 0; templateIndex++) {
            }

            templateTex0 = VisGifTemplates[templateIndex * 3];
            template3 = templateIndex * 3;
            templateTex1 = VisGifTemplates[template3 + 1];
            templateMip = VisGifTemplates[template3 + 2];
            filterBits = ((unsigned long)filter << 6) | 0x20;
            tex1 = (templateTex1 & 0x1C) | filterBits | ((unsigned long)mipDistance << 32);
            billboard->tex_0[0] = templateTex0;
            billboard->mip_1[0] = templateMip;
            billboard->tex_1[0] = tex1;
            // Retail reloads billboardTex->width below rather than reusing it; clearing the
            // pointer here keeps that.
            billboardTex = 0;
        }
    }

    classTexRefs = (unsigned char *)&ShrubTexLookup[ShrubClassLookup[oClass]];
    CopyVec4Inline((Vec4 *)classTexRefs, (Vec4 *)texRefs);

    for (packet = 0; packet < shrubClass->packet_cnt; packet++) {
        list = (ShrubDrawList *)shrubClass->packets[packet].data + 1;
        regs = (ShrubDrawRegs *)((char *)list + list->skip_qwords * 16 + 0x10);
        for (index = 0; index < list->draw_cnt; index++) {
            int material;
            int clampU;
            int filter;
            int mipDistance;
            int clampV;

            material = classTexRefs[regs->miptbp1.w[0]];
            mipDistance = regs->tex1.w[0];
            filter = regs->tex1.w[1];
            clampU = regs->clamp.w[0];
            clampV = regs->clamp.w[1];
            if (texDefs != 0) {
                TextureDef *texDef;
                int width;
                int texWidth;
                int mipWidth;
                int uLog;
                int vLog;
                int gsBlock;
                int mip2;
                int mip1;
                int mipCount;
                unsigned long tex0;
                unsigned long tex1;
                unsigned long miptbp1;
                unsigned long clamp;

                texDef = &texDefs[material];
                width = (unsigned short)texDef->width << 16;
                texWidth = width >> 22;
                mipWidth = width >> 23;
                if (texWidth <= 0)
                    texWidth = 1;

                if (mipWidth <= 0)
                    mipWidth = 1;

                uLog = FastLog2(width >> 16);
                vLog = FastLog2(texDef->height);
                gsBlock = GSmemBase >> 8;
                mipCount = texDef->mipCount;
                width = texDef->clut + gsBlock;
                mip1 = texDef->mip1 + gsBlock;
                mip2 = texDef->mip2 + gsBlock;
                tex1 = (long)(((unsigned long)(mipCount - 1) << 2) | ((unsigned long)1 << 5) | ((unsigned long)filter << 6))
                     | ((long)mipDistance << 32);
                clamp = (unsigned long)clampU | ((unsigned long)clampV << 2) | ((unsigned long)material << 24);
                miptbp1 = (long)(((unsigned long)mipWidth << 14) | ((unsigned long)mip1 << 20) | ((unsigned long)1 << 34)
                                 | ((unsigned long)mip2 << 40))
                        | ((long)1 << 54);
                tex0 = (long)((unsigned long)(((long)texWidth << 14) | ((long)GS_PSMT8 << 20) | ((long)uLog << 26))
                              | ((unsigned long)vLog << 30) | ((unsigned long)1 << 34) | ((unsigned long)width << 37))
                     | ((long)4 << 61);
                regs->tex1.d = tex1;
                regs->clamp.d = clamp;
                regs->miptbp1.d = miptbp1;
                regs->tex0.d = tex0;
            } else {
                int template3;
                unsigned long templateTex0;
                unsigned long templateTex1;
                unsigned long templateMip;
                unsigned long filterBits;
                unsigned long tex1;
                unsigned long clamp;

                templateTex0 = VisGifTemplates[material * 3];
                template3 = material * 3;
                templateTex1 = VisGifTemplates[template3 + 1];
                templateMip = VisGifTemplates[template3 + 2];
                filterBits = ((unsigned long)filter << 6) | 0x20;
                tex1 = (templateTex1 & 0x1C) | filterBits | ((unsigned long)mipDistance << 32);
                clamp = (unsigned long)clampU | ((unsigned long)clampV << 2) | ((unsigned long)material << 24);
                regs->tex1.d = tex1;
                regs->clamp.d = clamp;
                regs->miptbp1.d = templateMip;
                regs->tex0.d = templateTex0;
            }
            regs++;
        }
    }
}

// Relocates the level's tfrags and sets up the GS registers of each of their textures.
void ParseTfrag(char *data, short *texDefs)
{
    TfragHeader *header = (TfragHeader *)data;
    float lodDist;
    char *base;

    float *headerLodDist = &header->lodDist;  // read through a pointer, as retail

    TfragsCnt = header->count;
    lodDist = *headerLodDist;
    TfragDists[0] = lodDist * 6.0f;
    TfragDists[1] = lodDist * 4.0f;
    TfragDists[2] = lodDist + lodDist;
    SetTfragDists();

    base = data + header->tfragOffset;
    Tfrags = (Tfrag *)base;

    int count = TfragsCnt;

    for (int index = 0; index < count; index++)
        ((Tfrag *)base)[index].data = base + (int)((Tfrag *)base)[index].data;

    for (int tfragIndex = 0; tfragIndex < TfragsCnt; tfragIndex++) {
        for (int gifIndex = 0; gifIndex < Tfrags[tfragIndex].gifCount; gifIndex++) {
            unsigned long *gifRegs = (unsigned long *)(Tfrags[tfragIndex].data + Tfrags[tfragIndex].gifOffset + gifIndex * sizeof(TfragGifDef));
            int texIndex = ((TfragGifDef *)gifRegs)->texIndex;
            int mipDist = ((TfragGifDef *)gifRegs)->mipDist;
            int filter = ((TfragGifDef *)gifRegs)->filter;
            int clampU = ((TfragGifDef *)gifRegs)->clampU;
            int clampV = ((TfragGifDef *)gifRegs)->clampV;
            short *texDef = texDefs + texIndex * 8;
            int texWidth = texDef[TEXDEF_WIDTH] >> 6;
            int mipWidth = texDef[TEXDEF_WIDTH] >> 7;
            int uLog;
            int vLog;
            int gsBlock;
            unsigned long tex0, tex1, clamp, miptbp1;

            if (texWidth <= 0)
                texWidth = 1;

            if (mipWidth <= 0)
                mipWidth = 1;

            uLog = FastLog2(texDef[TEXDEF_WIDTH]);
            vLog = FastLog2(texDef[TEXDEF_HEIGHT]);
            gsBlock = GSmemBase >> 8;
            tex0 = SCE_GS_SET_TEX0(0, texWidth, GS_PSMT8, uLog, vLog, 1, 0, texDef[TEXDEF_CLUT] + gsBlock, 0, 0, 0, 4);
            tex1 = SCE_GS_SET_TEX1(0, texDef[TEXDEF_MIP_COUNT] - 1, 1, filter, 0, 0, (unsigned int)mipDist);
            clamp = (unsigned long)clampU | ((unsigned long)clampV << 2) | ((unsigned long)texIndex << 24);
            miptbp1 = SCE_GS_SET_MIPTBP1(0, mipWidth, texDef[TEXDEF_MIP1] + gsBlock, 1, texDef[TEXDEF_MIP2] + gsBlock, 1);

            *gifRegs = tex0;
            gifRegs += 2;
            *gifRegs = tex1;
            gifRegs += 2;
            *gifRegs = clamp;
            gifRegs += 2;
            *gifRegs = miptbp1;
            gifRegs[2] = 0;
        }
    }
}

void ParseColl(char *data)
{
    int *offsets = (int *)data;

    if (offsets[0])
        CollOutput.grid = data + offsets[0];

    if (offsets[1]) {
        HeroCollision = (HeroCollHeader *)(data + offsets[1]);
        for (int cell = 0; cell < HeroCollision->cellCount; cell++)
            HeroCollision->cells[cell].data = (char *)HeroCollision + (int)HeroCollision->cells[cell].data;
    }
}

// One moby class's memory use, for the debug listing.
struct MobyClassSize {
    float oClass;
    float size;     // KB
};

// Prints the level's moby classes by memory use, largest first.
void PrintMobyMemory(int *classRecord, int count)
{
    MobyClassSize classes[512];
    int i;
    int j;
    int k;
    int sorted;

    for (i = 0; i < count; i++, classRecord += 8) {
        classes[i].oClass = (float)classRecord[1];
        if (classRecord[0] == 0) {
            classes[i].size = 0;
        } else {
            // A class's data runs up to the next class's (or the one after it).
            if (classRecord[8] != 0)
                classes[i].size = FastIntToFloat(classRecord[8] - classRecord[0]) * (1.0f / 1024.0f);
            else
                classes[i].size = FastIntToFloat(classRecord[0x10] - classRecord[0]) * (1.0f / 1024.0f);

            classes[i + 1].oClass = -1.0f;
            classes[i + 1].size = 0;
        }
    }

    do {
        sorted = 1;
        for (j = 0; j < count; j++) {
            if (classes[j].size < classes[j + 1].size) {
                float oClass = classes[j].oClass;
                float size = classes[j].size;

                sorted = 0;
                classes[j].oClass = classes[j + 1].oClass;
                classes[j].size = classes[j + 1].size;
                classes[j + 1].oClass = oClass;
                classes[j + 1].size = size;
            }
        }
    } while (!sorted);

    for (k = 0; k < count; k++) {
        int oClass = FastFloatToInt(classes[k].oClass);

        printf_stub("moby %d:      %.1fK\n", oClass, classes[k].size);
    }
}

void STUB_RET_255950(void *data, int count)
{
}

// Builds the level's objects from its gameplay file. Unless reload is set, the file is read
// from the disc first; then it is unpacked into the memory slot's level data and every
// section is copied to its runtime buffer, starting at that memory. Returns the memory left
// after the particles.
char *ResetLevelData(int reload)
{
    GameplayHeader *header = (GameplayHeader *)MemSlots.vu1_chain[0];
    char *mem = (char *)MemSlots.levelData;
    float *shipSpawn;
    short *mobyIndexRemap = MobyIndexRemap;
    // The level in the moby loop, then a group's offset and end flag in the group loop.
    int levelOrGroup;

    if (reload == 0) {
        if (videoModePal)
            music_LoadFileSync(mem, bootAssets.gameplayPal.offset, bootAssets.gameplayPal.length);

        else
            music_LoadFileSync(mem, bootAssets.gameplayNtsc.offset, bootAssets.gameplayNtsc.length);

        gameplayFile = mem;
    }

    FlushCache(0);
    WadDecompress(gameplayFile, header);
    FlushCache(0);

    FastMemSet(&Hero, 0, 0x2310);
    FastMemSet(&GameCamera, 0, 0x3A0);
    FastMemSet(AnimLayerPool, 0, 0x180);
    srand(1234);

    if (videoModePal) {
        if (transStepScale == 1.0f)
            SetNtscPalTiming(1);
    }

    else if (transStepScale != 1.0f) {
        SetNtscPalTiming(0);
    }

    CollOutput.jointCache = CollMobyJointCache;
    CollOutput.jointCacheKeys = CollJointCacheKeys;
    CollOutput.jointCacheNext = 0;
    CollOutput.collCount = 0;
    CollOutput.damageNext = 0;
    FastMemSetZero(MobyGrids, 0x10000);
    FastMemSetZero(MobyGridAlloc, 0x60);

    {
        int *settings = (int *)((char *)header + header->settings);
        int *shipSettings;

        VC.backR = *settings++;
        VC.backG = *settings++;
        VC.backB = *settings++;
        DrawSdata15F444 = *settings++;
        DrawSdata15F445 = *settings++;
        DrawSdata15F446 = *settings++;
        shipSpawn = (float *)(settings + 5);
        shipSettings = settings + 9;
        DrawSdata15F448 = *(float *)settings;
        DrawSdata15F44C = *(float *)(settings + 1);
        DrawSdata15F450 = *(float *)(settings + 2);
        DrawSdata15F454 = *(float *)(settings + 3);
        HeroDeathHeight = *(float *)(settings + 4);
        settings += 12;
        bootSpaceTransitionState.shipSplinePath = shipSettings[0];
        bootSpaceTransitionState.shipCameraStartCuboid = shipSettings[1];
        bootSpaceTransitionState.shipCameraEndCuboid = shipSettings[2];
    }

    UpdateFog();
    TfragDrawDist = 512000.0f;
    TieDrawDist = 720.0f;
    ShrubDrawDist = 500.0f;
    MobySdata15FFF0 = 500;
    PartClipDist = 0x1F4000;
    SetBackgroundColor(VC.backR, VC.backG, VC.backB);
    VU0_loadMicroProgram(LightVU0Program);

    FastMemSetZero(PointLights, 0x100);
    FastMemSetZero(PointLightData, 0x180);
    FastMemSetZero(DirectionalLights, 0x400);

    {
        char *section = (char *)header + header->directionalLights;
        int lightCount = *(int *)section;

        section += 0x10;
        if (lightCount >= MAX_DIRECTIONAL_LIGHTS) {
            printf_stub("!!!! Too many directional lights !!!! - Lighting will look bogus as a penalty.\n");
            lightCount = MAX_DIRECTIONAL_LIGHTS;
        }

        if (lightCount != 0)
            FastMemCopy32(DirectionalLights, section, lightCount << 6);
    }

    if (header->blenders != 0) {
        char *section = (char *)header + header->blenders;

        BlenderCnt = *(int *)section;
        section += 0x10;
        if (BlenderCnt != 0) {
            FastMemCopy32(BlenderInfo, section, BlenderCnt << 4);
            FastMemCopy32(Blenders, section + (BlenderCnt << 4), BlenderCnt << 7);

            for (int index = 0; index < BlenderCnt; index++) {
                Blender *blender = &Blenders[index];

                if (blender->dLightA < 0)
                    blender->dLightA = BLENDER_LIGHT_DEFAULT;

                if (blender->dLightB < 0)
                    blender->dLightB = BLENDER_LIGHT_DEFAULT;
            }
        }
    }

    else {
        BlenderCnt = 0;
    }

    for (int index = 0; index < TfragsCnt; index++)
        Tfrags[index].point_lights = 0xFFFF;

    {
        int index = 0;

        while (index < TfragsCnt) {
            unsigned short *list = (unsigned short *)SPR_TFRAG_LIGHT_LIST;

            for (int count = 0; count < 0x3FF && index < TfragsCnt; count++) {
                *list = index;
                list++;
                index++;
            }

            *list = 0xFFFF;
            LightTfrags((void *)SPR_TFRAG_LIGHT_LIST);
        }
    }

    if (header->help[0] != 0) {
        char *messages = (char *)header + header->help[gameLanguage];
        int size;

        Help.num_message = *(int *)messages;
        messages += 4;
        size = *(int *)messages;
        messages += 4;
        HelpMsgs = (HelpMsg *)mem;
        size += 3;
        size &= ~3;
        size -= 8;
        FastMemCopy32(mem, messages, size);

        // The text offsets count from the start of the help section.
        for (int index = 0; index < Help.num_message; index++) {
            int delta = (int)HelpMsgs - 8;

            HelpMsgs[index].text += delta;
        }

        mem = (char *)(((unsigned int)mem + size + 0x3F) & 0xFFFFFFC0);
    }

    {
        char *record = (char *)header + header->ties;
        int count = *(int *)record;
        int index;
        int lastClass;

        TieInstances = (TieInstance *)mem;
        record += 0x10;
        TieCnt = count;
        mem += count << 5;
        if (count != 0)
            FastMemSet(TieInstances, 0, count << 5);

        mem = (char *)(((unsigned int)mem + 0x3F) & 0xFFFFFFC0);
        TieMatrices = (TieMatrix *)mem;
        mem += TieCnt * 0x1C0;
        if (TieCnt != 0)
            FastMemSet(TieMatrices, 0, TieCnt * 0x1C0);

        lastClass = -1;
        TieInstanceEnd = TieInstances + TieCnt;

        for (index = 0; index < TieCnt; index++) {
            TieInstance *tie = TieInstances + index;
            TieMatrix *matrix = TieMatrices + index;
            int occlusionId;
            float scale;

            tie->tieClass = TieClassLookup[*(int *)record];
            if (tie->tieClass != lastClass) {
                TieClasses[tie->tieClass]->instances = tie;
                TieClasses[tie->tieClass]->instance_cnt = 0;
                lastClass = tie->tieClass;
            }

            TieClasses[tie->tieClass]->instance_cnt++;
            tie->matrix = matrix;
            tie->drawDist = (float)*(int *)(record + 4);
            tie->point_lights = 0xFFFF;
            tie->dir_lights_upd = 0;
            tie->dirLights = 0;
            occlusionId = *(int *)(record + 0xC);
            CopyVec4Inline(&matrix->mtx.v0, (Vec4 *)(record + 0x10));
            CopyVec4Inline(&matrix->mtx.v1, (Vec4 *)(record + 0x20));
            CopyVec4Inline(&matrix->mtx.v2, (Vec4 *)(record + 0x30));
            CopyVec4Inline(&matrix->mtx.v3, (Vec4 *)(record + 0x40));
            tie->occlIndex = occlusionId;
            record += 0x50;

            matrix->mtx.v3.w = TieClasses[tie->tieClass]->scale;
            FastVecMtx3Mult((Vec4 *)tie, (Vec4 *)&TieClasses[tie->tieClass]->bsphere, &matrix->mtx);
            scale = FastVec3Length2(&matrix->mtx.v0);
            scale = FastMaxF(scale, FastVec3Length2(&matrix->mtx.v1));
            tie->bSphere.rad = TieClasses[tie->tieClass]->bsphere.rad * FastMaxF(scale, FastVec3Length2(&matrix->mtx.v2));
            FastScaleVec4((Vec4 *)tie, (Vec4 *)tie, matrix->mtx.v3.w);
            FastVec3Add((Vec4 *)tie, (Vec4 *)tie, &matrix->mtx.v3);

            TieMatrices[index].mtx.v0.w = 1.0f / FastVec3Length2(&TieMatrices[index].mtx.v0);
            TieMatrices[index].mtx.v1.w = 1.0f / FastVec3Length2(&TieMatrices[index].mtx.v1);
            TieMatrices[index].mtx.v2.w = 1.0f / FastVec3Length2(&TieMatrices[index].mtx.v2);

            FastMemCopy32(matrix->colors, record, 0x80);
            record += 0x80;
            tie->dirLights = *(unsigned short *)record;
            record += 0x10;
        }
    }

    {
        unsigned short *list = (unsigned short *)SPR_LIGHT_LIST;

        for (int index = 0; index < TieCnt; index++)
            *list++ = index;

        *list = 0xFFFF;
        LightTies((void *)SPR_LIGHT_LIST);
    }

    {
        char *record = (char *)header + header->shrubs;
        int count = *(int *)record;
        int lastClass;
        int index;

        ShrubInstances = (ShrubInstance *)mem;
        record += 0x10;
        ShrubCnt = count;
        mem += count << 5;
        if (count != 0)
            FastMemSet(ShrubInstances, 0, count << 5);

        mem = (char *)(((unsigned int)mem + 0x3F) & 0xFFFFFFC0);
        ShrubMatrices = (ShrubMatrix *)mem;
        mem += ShrubCnt << 6;
        if (ShrubCnt != 0)
            FastMemSet(ShrubMatrices, 0, ShrubCnt << 6);

        ShrubVertexColors = (unsigned char *)mem;
        mem += ShrubCnt * 0x60;
        mem = (char *)(((unsigned int)mem + 0x3F) & 0xFFFFFFC0);
        if (ShrubCnt != 0)
            FastMemSet(ShrubVertexColors, 0, ShrubCnt * 0x60);

        lastClass = -1;
        ShrubColorBuffer.colors = ShrubVertexColors;
        ShrubInstanceEnd = ShrubInstances + ShrubCnt;

        for (index = 0; index < ShrubCnt; index++) {
            ShrubInstance *shrub = ShrubInstances + index;
            ShrubMatrix *matrix = ShrubMatrices + index;
            int shrubClass = ShrubClassLookup[*(int *)record];
            float scale;

            shrub->s_class = shrubClass;
            if (shrubClass != lastClass) {
                lastClass = shrubClass;
                ShrubClasses[shrubClass]->instances = shrub;
                ShrubClasses[shrubClass]->instance_cnt = 0;
            }

            ShrubClasses[shrubClass]->instance_cnt++;
            shrub->index = index;
            shrub->draw_dist = *(float *)(record + 4);
            if (shrub->draw_dist < 16.0f)
                shrub->draw_dist = 16.0f;

            shrub->dir_lights_upd = 0;
            shrub->point_lights = 0xFFFF;

            if (ShrubClasses[shrubClass]->billboard != 0) {
                float billboardDist;

                shrub->bboard_dist = FastFloatToInt(ShrubClasses[shrubClass]->billboard->fade_dist);
                billboardDist = FastIntToFloat(shrub->bboard_dist) + 24.0f;
                if (shrub->draw_dist < billboardDist)
                    shrub->draw_dist = billboardDist;
            }

            CopyVec4Inline(&matrix->mtx.v0, (Vec4 *)(record + 0x10));
            CopyVec4Inline(&matrix->mtx.v1, (Vec4 *)(record + 0x20));
            CopyVec4Inline(&matrix->mtx.v2, (Vec4 *)(record + 0x30));
            CopyVec4Inline(&matrix->mtx.v3, (Vec4 *)(record + 0x40));
            record += 0x50;

            matrix->mtx.v3.w = ShrubClasses[shrubClass]->scale;

            {
                float sideScale = (FastVec3Length2(&matrix->mtx.v0) + FastVec3Length2(&matrix->mtx.v1)) * 0.5f;
                float upScale = FastVec3Length2(&matrix->mtx.v2);
                int fixedSide = FastFloatToInt(sideScale * 4096.0f);
                int fixedUp = FastFloatToInt(upScale * 4096.0f);

                if (fixedUp > 0x10000)
                    fixedUp = 0x10000;

                if (fixedSide > 0x10000)
                    fixedSide = 0x10000;

                matrix->packedScale = fixedSide | (fixedUp << 16);
            }

            {
                int red;
                int green;
                int blue;

                red = *(int *)record;
                record += 4;
                green = *(int *)record;
                record += 4;
                blue = *(int *)record;
                record += 8;
                green = (green << 8) | 0x80000000;
                matrix->color = (blue << 16) | green | red;
            }

            shrub->dir_lights = *(unsigned short *)record;
            record += 0x10;

            FastVecMtx3Mult((Vec4 *)shrub, (Vec4 *)ShrubClasses[shrubClass], &matrix->mtx);
            scale = FastVec3Length2(&matrix->mtx.v0);
            scale = FastMaxF(scale, FastVec3Length2(&matrix->mtx.v1));
            shrub->bSphere.rad = ShrubClasses[shrubClass]->bSphere.rad * FastMaxF(scale, FastVec3Length2(&matrix->mtx.v2));
            FastScaleVec4((Vec4 *)shrub, (Vec4 *)shrub, matrix->mtx.v3.w);
            FastVec3Add((Vec4 *)shrub, (Vec4 *)shrub, &matrix->mtx.v3);
        }
    }

    {
        unsigned short *list = (unsigned short *)SPR_LIGHT_LIST;

        for (int index = 0; index < ShrubCnt; index++)
            *list++ = index;

        *list = 0xFFFF;
        LightShrubs((void *)SPR_LIGHT_LIST);
    }

    // Each shrub's colour is the average of its 24 vertex colours.
    for (int index = 0; index < ShrubCnt; index++) {
        unsigned char *color = ShrubVertexColors + index * 0x60;
        int red = 0;
        int green = 0;
        int blue = 0;
        int count = 24;

        for (int vertex = 0; vertex < count; vertex++) {
            red += color[0];
            green += color[1];
            blue += color[2];
            color += 4;
        }

        green /= count;
        blue /= count;
        red /= count;
        *(int *)((char *)ShrubMatrices + index * 0x40 + 0x1C) = (blue << 16) | (green << 8) | red;
    }

    if (header->cameras != 0) {
        char *record = (char *)header + header->cameras;
        int count = *(int *)record;

        ImportCameras = (ImportCamera *)mem;
        record += 0x10;
        ImportCameraCnt = count;
        mem += count << 5;
        if (count != 0)
            FastMemSet(ImportCameras, 0, count << 5);

        mem = (char *)(((unsigned int)mem + 0x3F) & 0xFFFFFFC0);

        for (int index = 0; index < ImportCameraCnt; index++) {
            ImportCameras[index].type = *(int *)record;
            record += 4;
            ImportCameras[index].pos[0] = ((float *)record)[0];
            ImportCameras[index].pos[1] = ((float *)record)[1];
            ImportCameras[index].pos[2] = ((float *)record)[2];
            record += 0xC;
            ImportCameras[index].rot[0] = ((float *)record)[0];
            ImportCameras[index].rot[1] = ((float *)record)[1];
            ImportCameras[index].rot[2] = ((float *)record)[2];
            record += 0xC;
            ImportCameras[index].pVar = *(int *)record;
            record += 4;
        }
    }

    if (header->sounds != 0) {
        char *record = (char *)header + header->sounds;
        int count = *(int *)record;

        record += 0x10;
        audioState.soundInstanceCnt = count;
        if (count != 0) {
            int size = count * 0x90;
            int index;

            audioState.soundInstances = (SoundInstance *)mem;
            mem += size;
            mem = (char *)(((unsigned int)mem + 0x3F) & 0xFFFFFFC0);
            FastMemSet(audioState.soundInstances, 0, size);

            for (index = 0; index < audioState.soundInstanceCnt; index++) {
                SoundInstance *sound = audioState.soundInstances + index;

                FastMemCopy32(sound, record, 0x90);
                record += 0x90;
                sound_SetupAmbientFunctions(sound);
            }
        }

        else {
            audioState.soundInstances = 0;
        }
    }

    {
        char *record = (char *)header + header->mobys;
        int extraMobys;
        int spawned = 0;
        int recordCnt;
        char *nextRecord;
        int index;

        recordCnt = *(int *)record;
        record += 4;
        extraMobys = *(int *)record;
        record += 0xC;
        MobyInstances = (MobyInstance *)mem;
        FastMemSet(mem, 0, (recordCnt + extraMobys) << 8);

        for (index = 0; index < recordCnt; index++) {
            int levelFlagIdx;
            int flags;
            int uid;
            int bolts;
            int boltsAlt;
            int boltsBase;
            int boltsAdjusted;
            unsigned char mapSlot = MAPSLOT_NONE;
            int skip = 0;

            nextRecord = record + ((*(int *)record >> 2) << 2);
            record += 4;
            levelFlagIdx = *(int *)record;
            record += 4;
            flags = *(int *)record;
            record += 4;
            uid = *(int *)record;
            record += 4;
            bolts = *(int *)record;
            record += 4;
            boltsAlt = *(int *)record;
            record += 4;
            boltsBase = bolts;
            boltsAdjusted = boltsBase;

            if (flags != 0) {
                levelOrGroup = Level;
                if (flags & MOBYSPAWN_MAP_SLOT)
                    mapSlot = FindOrAssignBoltSourceSlot(levelOrGroup, uid);

                else
                    mapSlot = MAPSLOT_UNSET;

                if (CheckpointObjState[uid] != 0) {
                    skip = 1;
                }

                else if (flags & (MOBYSPAWN_LEVEL_FLAG | MOBYSPAWN_NO_LEVEL_FLAG)) {
                    if (CheckpointLevelFlags[levelFlagIdx] == 0xFF) {
                        if (flags & MOBYSPAWN_NO_LEVEL_FLAG) {
                            boltsBase = boltsAlt;
                            if ((CheckpointBits[uid >> 5] >> (uid & 0x1F)) & 1)
                                boltsAdjusted = (boltsBase + 1) / 2;

                            else
                                boltsAdjusted = boltsBase;
                        }

                        else {
                            skip = 1;
                        }
                    }

                    else {
                        if (flags & MOBYSPAWN_LEVEL_FLAG) {
                            if ((LevelCheckpointBits[Level][uid >> 5] >> (uid & 0x1F)) & 1)
                                boltsAdjusted = (bolts + 1) / 2;
                        }

                        else {
                            skip = 1;
                        }
                    }
                }

                else if (flags & MOBYSPAWN_IF_CHECKPOINT) {
                    if ((CheckpointBits[uid >> 5] >> (uid & 0x1F)) & 1)
                        skip = 1;
                }

                else if ((flags & (MOBYSPAWN_IF_CHECKPOINT | MOBYSPAWN_IF_LEVEL)) == MOBYSPAWN_IF_LEVEL) {
                    if ((LevelCheckpointBits[Level][uid >> 5] >> (uid & 0x1F)) & 1)
                        skip = 1;
                }
            }

            if (skip) {
                mobyIndexRemap[index] = -1;
            }

            else {
                MobyInstance *moby;
                int onGround;
                float groundOffset;
                int pVar;
                int red;
                int green;
                int blue;
                int light;

                {
                    short *slot = mobyIndexRemap + index;

                    *slot = spawned;
                }
                moby = MobyInstances + spawned;
                InitMobyInstance(moby, *(int *)record);
                record += 4;
                moby->unkB1 = mapSlot;
                moby->uid = uid;
                moby->levelFlagIdx = levelFlagIdx;
                *(short *)&moby->unkB4[0] = boltsAdjusted;
                *(short *)&moby->unkB4[2] = boltsBase;
                if (moby->pClass != 0)
                    moby->scale = moby->pClass->scale * *(float *)record;

                record += 4;
                moby->drawDistance = *(unsigned short *)record;
                record += 4;
                moby->updateDistance = *(unsigned char *)record;
                record += 0xC;
                moby->pos.x = ((float *)record)[0];
                moby->pos.y = ((float *)record)[1];
                moby->pos.z = ((float *)record)[2];
                record += 0xC;
                moby->rotation.x = ((float *)record)[0];
                moby->rotation.y = ((float *)record)[1];
                moby->rotation.z = ((float *)record)[2];
                record += 0xC;
                moby->group = *(unsigned char *)record;
                record += 4;
                onGround = *(int *)record;
                record += 4;
                groundOffset = *(float *)record;
                record += 4;

                if (onGround != 0) {
                    float ground = MB_CollLineDown(&moby->pos, 0.5f, 0);

                    if (0.0f < ground)
                        moby->pos.z = ground + groundOffset;
                }

                record += 4;
                pVar = *(int *)record;
                moby->occlIndex = OCCL_NONE;
                record += 4;
                moby->pVar = (void *)pVar;
                if (*(int *)record == 0)
                    moby->occlIndex = 0;

                record += 4;
                if (moby->pClass != 0)
                    moby->pClass->modeBits |= *(unsigned short *)record;

                moby->modeBits |= *(unsigned short *)record;
                record += 4;
                if (moby->pClass != 0)
                    PostUpdateMoby(moby);

                red = *(int *)record;
                record += 4;
                green = *(int *)record;
                record += 4;
                blue = *(int *)record;
                record += 4;
                light = *(int *)record;
                record += 4;
                moby->colorManipulator = (blue << 16) + (green << 8) + red;
                SetMobyLights(moby, moby->colorManipulator, 0, 0, 0);
                moby->color = light;
                if (*(int *)record != -1)
                    Map_RegisterLevelObject(moby, *(int *)record);

                spawned++;
            }

            record = nextRecord;
        }

        MobyInstancePermEnd = MobyInstances + spawned;
        MobyInstancePermEnd->state = 0xFF;
        mem += (spawned + extraMobys) << 8;
        mobyVars = mem;
        mem += extraMobys << 7;
        mem = (char *)(((unsigned int)mem + 0x3F) & 0xFFFFFFC0);
        MobyInstanceEnd = (MobyInstance *)((int)MobyInstances + ((spawned + extraMobys) << 8) - 0x100);
    }

    if (header->pvarData != 0) {
        char *pvarData = (char *)header + header->pvarData;
        PvarEntry *pvarTable = (PvarEntry *)((char *)header + header->pvarTable);
        MobyInstance *moby;

        for (int index = 0; index < ImportCameraCnt; index++) {
            int entry = ImportCameras[index].pVar;

            if (entry < 0) {
                ImportCameras[index].pVar = 0;
            }

            else {
                int size = pvarTable[entry].size;
                char *source = pvarData + pvarTable[entry].offset;

                ImportCameras[index].pVar = (int)mem;
                FastMemCopy16(mem, source, size);
                pvarTable[entry].offset = (int)mem;
                mem += size;
            }
        }

        for (int index = 0; index < audioState.soundInstanceCnt; index++) {
            int entry = audioState.soundInstances[index].pVar;

            if (entry < 0) {
                audioState.soundInstances[index].pVar = 0;
            }

            else {
                int size = pvarTable[entry].size;
                char *source = pvarData + pvarTable[entry].offset;

                audioState.soundInstances[index].pVar = (int)mem;
                FastMemCopy16(mem, source, size);
                pvarTable[entry].offset = (int)mem;
                mem += size;
            }
        }

        for (moby = MobyInstances; moby != MobyInstancePermEnd; moby++) {
            int entry = (int)moby->pVar;

            if (entry < 0) {
                moby->pVar = 0;
            }

            else {
                int size = pvarTable[entry].size;
                char *source = pvarData + pvarTable[entry].offset;

                moby->pVar = mem;
                FastMemCopy16(mem, source, size);
                pvarTable[entry].offset = (int)mem;
                mem += size;
            }
        }

        mem = (char *)(((unsigned int)mem + 0x3F) & 0xFFFFFFC0);
    }

    if (header->mobyLinks != 0) {
        int *link = (int *)((char *)header + header->mobyLinks);
        PvarEntry *pvarTable = (PvarEntry *)((char *)header + header->pvarTable);

        while (link[0] >= 0) {
            int pVar = pvarTable[link[0]].offset;
            int fieldOffset = link[1];

            if (pVar >= (int)header) {
                int *field = (int *)(pVar + fieldOffset);

                if (*field >= 0)
                    *field = mobyIndexRemap[*field];
            }

            link += 2;
        }
    }

    if (header->pvarPointers != 0) {
        int *fix = (int *)((char *)header + header->pvarPointers);
        PvarEntry *pvarTable = (PvarEntry *)((char *)header + header->pvarTable);

        while (fix[0] >= 0) {
            int pVar = pvarTable[fix[0]].offset;
            int fieldOffset = fix[1];

            if (pVar >= (int)header) {
                int *field = (int *)(pVar + fieldOffset);

                *field += pVar;
            }

            fix += 2;
        }
    }

    if (header->mobyGroups != 0) {
        char *section = (char *)header + header->mobyGroups;
        char *groups = mem;
        int *offsets;
        int groupCnt;
        int size;

        groupCnt = *(int *)section;
        section += 4;
        size = *(int *)section;
        offsets = (int *)(section + 0xC);
        mem += size;
        section = (char *)offsets + (groupCnt << 2);
        mem = (char *)(((unsigned int)mem + 0x3F) & 0xFFFFFFC0);
        if (size != 0)
            FastMemCopy16(groups, section, size);

        FastMemSet(MobyGroupEntries, 0, 0x1C0);

        for (int index = 0; index < groupCnt; index++, offsets++) {
            levelOrGroup = *offsets;
            if (levelOrGroup >= 0) {
                int entry = (int)(groups + levelOrGroup);
                unsigned short *in;
                short *out;

                MobyGroupEntries[index] = (short *)entry;
                in = (unsigned short *)entry;
                out = (short *)in;
                MobySdata15FFF4 = index + 1;

                do {
                    int id = *in;
                    short moby;

                    levelOrGroup = *(short *)in;
                    entry = (id & 0x7FFF) << 1;
                    entry += (int)mobyIndexRemap;
                    levelOrGroup &= MOBY_GROUP_END;
                    moby = *(short *)entry;
                    if (moby >= 0)
                        *out++ = moby;

                    if (levelOrGroup) {
                        if ((int)MobyGroupEntries[index] < (int)out)
                            out[-1] |= MOBY_GROUP_END;

                        else
                            MobyGroupEntries[index] = 0;

                        break;
                    }

                    in++;
                } while (!levelOrGroup);
            }
        }
    }

    if (header->sharedData != 0) {
        char *section = (char *)header + header->sharedData;
        char *shared = mem;
        PvarEntry *pvarTable;
        int size;
        int fixCnt;

        size = *(int *)section;
        section += 4;
        fixCnt = *(int *)section;
        section += 0xC;
        mem += size;
        mem = (char *)(((unsigned int)mem + 0x3F) & 0xFFFFFFC0);
        if (size != 0)
            FastMemCopy16(shared, section, size);

        section += size;
        pvarTable = (PvarEntry *)((char *)header + header->pvarTable);

        for (int index = 0; index < fixCnt; index++) {
            int word = *(int *)section;
            int fieldOffset = word >> 16;
            int pVar = pvarTable[word & 0xFFFF].offset;

            if (pVar >= (int)header)
                *(int *)(pVar + fieldOffset) = (int)(shared + *(int *)(section + 4));

            section += 8;
        }
    }

    if (header->splines != 0) {
        char *section = (char *)header + header->splines;
        char *source;
        int size;

        SplineCnt = *(int *)section;
        source = section + *(int *)(section + 4);
        size = *(int *)(section + 8);
        SplineData = mem;
        mem += size;
        section += 0x10;
        mem = (char *)(((unsigned int)mem + 0x3F) & 0xFFFFFFC0);
        if (size != 0)
            FastMemCopy16(SplineData, source, size);

        for (int index = 0; index < SplineCnt; index++) {
            Splines[index] = SplineData + *(int *)section;
            section += 4;
        }
    }

    if (header->grindPaths != 0) {
        char *section = (char *)header + header->grindPaths;
        char *source;
        char *data;
        int count;
        int size;
        int index;

        count = *(int *)section;
        GrindPathCnt = count;
        source = section + *(int *)(section + 4);
        size = *(int *)(section + 8);
        GrindPaths = (GrindPath *)mem;
        mem += count << 5;
        section += 0x10;
        mem = (char *)(((unsigned int)mem + 0x3F) & 0xFFFFFFC0);

        if (count > 0) {
            GrindPath *path = GrindPaths;

            index = count;
            do {
                CopyVec4Inline((Vec4 *)&path->bSphere, (Vec4 *)section);
                section += 0x10;
                path->unk14 = *(int *)section;
                section += 0x10;
                path++;
            } while (--index != 0);
        }

        data = mem;
        mem += size;
        mem = (char *)(((unsigned int)mem + 0x3F) & 0xFFFFFFC0);
        if (size != 0)
            FastMemCopy16(data, source, size);

        for (index = 0; index < GrindPathCnt; index++) {
            GrindPaths[index].data = data + *(int *)section;
            section += 4;
        }
    }

    if (header->pills != 0) {
        char *section = (char *)header + header->pills;
        int count = *(int *)section;

        Pills = mem;
        PillCnt = count;
        section += 0x10;
        mem += count * 0x90;
        mem = (char *)(((unsigned int)mem + 0x3F) & 0xFFFFFFC0);
        if (count != 0)
            FastMemSet(Pills, 0, count * 0x90);

        for (int index = 0; index < PillCnt; index++) {
            FastMemCopy32(Pills + index * 0x90, section, 0x90);
            section += 0x80;
        }
    }

    if (header->cuboids != 0) {
        char *section = (char *)header + header->cuboids;
        int count = *(int *)section;

        CuboidVolumes = (MobyVolume *)mem;
        section += 0x10;
        CuboidCnt = count;
        mem += count << 7;
        mem = (char *)(((unsigned int)mem + 0x3F) & 0xFFFFFFC0);
        if (count != 0)
            FastMemSet(CuboidVolumes, 0, count << 7);

        for (int index = 0; index < CuboidCnt; index++) {
            FastMemCopy32(CuboidVolumes + index, section, 0x80);
            section += 0x80;
        }
    }

    if (header->spheres != 0) {
        char *section = (char *)header + header->spheres;
        int count = *(int *)section;

        SphereVolumes = (MobyVolume *)mem;
        section += 0x10;
        SphereCnt = count;
        mem += count << 7;
        mem = (char *)(((unsigned int)mem + 0x3F) & 0xFFFFFFC0);
        if (count != 0)
            FastMemSet(SphereVolumes, 0, count << 7);

        for (int index = 0; index < SphereCnt; index++) {
            FastMemCopy32(SphereVolumes + index, section, 0x80);
            section += 0x80;
        }
    }

    if (header->cylinders != 0) {
        char *section = (char *)header + header->cylinders;
        int count = *(int *)section;

        CylinderVolumes = (MobyVolume *)mem;
        section += 0x10;
        CylinderCnt = count;
        mem += count << 7;
        mem = (char *)(((unsigned int)mem + 0x3F) & 0xFFFFFFC0);
        if (count != 0)
            FastMemSet(CylinderVolumes, 0, count << 7);

        for (int index = 0; index < CylinderCnt; index++) {
            FastMemCopy32(CylinderVolumes + index, section, 0x80);
            section += 0x80;
        }
    }

    if (header->camCollGrid != 0) {
        char *section = (char *)header + header->camCollGrid;
        int size = *(int *)section;

        CamCollGrid = mem;
        section += 0x10;
        size += 0x4000;
        mem += size;
        FastMemCopy32(CamCollGrid, section, size);
        mem = (char *)(((unsigned int)mem + 0x3F) & 0xFFFFFFC0);
    }

    if (header->pointLightGrid != 0) {
        char *section = (char *)header + header->pointLightGrid;
        int size = *(int *)section;

        PointLightGrid = mem;
        section += 0x10;
        size += 0x4000;
        mem += size;
        FastMemCopy32(PointLightGrid, section, size);
        mem = (char *)(((unsigned int)mem + 0x3F) & 0xFFFFFFC0);
    }

    if (header->pointLights != 0) {
        char *section = (char *)header + header->pointLights;
        int count = *(int *)section;

        PointLightRecords = mem;
        section += 0x10;
        PointLightRecordCnt = count;
        mem += count << 5;
        mem = (char *)(((unsigned int)mem + 0x3F) & 0xFFFFFFC0);
        if (count != 0)
            FastMemCopy32(PointLightRecords, section, count << 5);
    }

    if (header->envSamples != 0) {
        char *section = (char *)header + header->envSamples;
        int count = *(int *)section;

        EnvSamples = mem;
        EnvSampleCnt = count;
        section += 0x10;
        mem += count * 0x30;
        mem = (char *)(((unsigned int)mem + 0x3F) & 0xFFFFFFC0);
        if (count != 0)
            FastMemCopy32(EnvSamples, section, count * 0x30);
    }

    PartInstances = mem;
    mem += 0x20000;
    PartIndexTop = -1;
    PartIndexNext = 0;
    PartActiveCnt = 0;
    FastMemSetZero(PartAlloc, 0x200);

    bootSpaceTransitionState.spaceship = 0;
    if (0.0f < shipSpawn[0]) {
        MobyInstance *moby;

        if (Level == LEVEL_GEMLIK && bootSpaceTransitionState.shipVariant == SHIP_VARIANT_GEMLIK) {
            if (SpaceshipPreplaced != 0) {
                for (moby = MobyInstances; moby->state != 0xFF; moby++) {
                    if ((short)moby->oClass == SpaceshipOClasses[bootSpaceTransitionState.shipVariant]) {
                        SetupSpaceShipVars(moby);
                        MB_SetAnimationNoBlend(moby, 1, 0);
                        break;
                    }
                }
            }
        }

        if (bootSpaceTransitionState.spaceship == 0) {
            float spawnRotation;

            moby = CreateMoby(SpaceshipOClasses[bootSpaceTransitionState.shipVariant]);
            moby->pos.x = shipSpawn[0];
            moby->pos.y = shipSpawn[1];
            moby->pos.z = shipSpawn[2];
            spawnRotation = shipSpawn[3];
            moby->pUpdate = (void *)UpdateMoby_Spaceship;
            moby->drawDistance = 0xFF;
            moby->rotation.z = spawnRotation;
            moby->updateDistance = 16;
            moby->modeBits &= ~NO_UPDATE;
            MB_SetAnimationNoBlend(moby, 1, 0);
            PostUpdateMoby(moby);
            bootSpaceTransitionState.spaceship = moby;
            Map_RegisterLevelObject(moby, 0);
        }
    }

    if (OcclGrid != 0 && header->occlusion != 0) {
        int *mapping = (int *)((char *)header + header->occlusion);
        int *section = mapping;
        int tfragMappingCnt;
        int tieMappingCnt;
        int mobyMappingCnt;
        int tfragsStale = 1;
        int tiesStale;

        tfragMappingCnt = mapping[0];
        tieMappingCnt = mapping[1];
        mobyMappingCnt = mapping[2];
        mapping += 4;

        if (TfragsCnt == tfragMappingCnt) {
            tfragsStale = 0;
            for (int index = 0; index < tfragMappingCnt; index++) {
                if (Tfrags[index].occlId != mapping[1])
                    tfragsStale = 1;

                mapping += 2;
            }
        }

        else {
            mapping += tfragMappingCnt * 2;
        }

        tiesStale = 1;
        if (TieInstanceEnd - TieInstances == tieMappingCnt) {
            tiesStale = 0;
            for (int index = 0; index < tieMappingCnt; index++) {
                int id = (unsigned short)mapping[1];

                if (TieInstances[index].occlIndex != id)
                    tiesStale = 1;

                mapping += 2;
            }
        }

        else {
            mapping += tieMappingCnt * 2;
        }

        {
            MobyInstance *moby;
            int stale = 0;
            int missing = 0;
            int occluded = 0;

            for (moby = MobyInstances; moby->state != 0xFF; moby++) {
                if (moby->occlIndex != OCCL_NONE) {
                    int uid = (short)moby->uid;
                    int entry;

                    occluded++;
                    for (entry = 0; entry < mobyMappingCnt; entry++) {
                        if (mapping[entry * 2 + 1] == uid)
                            break;
                    }

                    if (entry == mobyMappingCnt) {
                        moby->occlIndex = OCCL_NONE;
                        stale = 1;
                        missing++;
                    }

                    else {
                        int bit = mapping[entry * 2];

                        moby->occlIndex = ((bit >> 3) << 8) | (1 << (bit & 7));
                    }
                }
            }

            if (stale)
                printf_stub("***\nocclusion out of date on mobys (%d / %d)\n***\n", missing, occluded);
        }

        if (tfragsStale) {
            printf_stub("***\nocclusion out of date on tfrag\n***\n");
            for (int index = 0; index < TfragsCnt; index++)
                Tfrags[index].occlIndex = OCCL_NONE;
        }

        else {
            mapping = section + 4;
            for (int index = 0; index < tfragMappingCnt; index++) {
                int bit = mapping[0];

                Tfrags[index].occlIndex = ((bit >> 3) << 8) | (1 << (bit & 7));
                mapping += 2;
            }
        }

        if (tiesStale) {
            TieInstance *tie;
            int missing = 0;
            int occluded = 0;

            mapping = &section[tfragMappingCnt * 2 + 4];
            for (tie = TieInstances; tie != TieInstanceEnd; tie++) {
                int id = tie->occlIndex;
                int entry;

                occluded++;
                for (entry = 0; entry < tieMappingCnt; entry++) {
                    if (mapping[entry * 2 + 1] == id)
                        break;
                }

                if (entry == tieMappingCnt) {
                    tie->occlIndex = OCCL_NONE;
                    missing++;
                }

                else {
                    int bit = mapping[entry * 2];

                    tie->occlIndex = ((bit >> 3) << 8) | (1 << (bit & 7));
                }
            }

            printf_stub("***\nocclusion out of date on ties (%d / %d)\n***\n", missing, occluded);
        }

        else {
            mapping = &section[tfragMappingCnt * 2 + 4];
            for (int index = 0; index < tieMappingCnt; index++) {
                int bit = mapping[0];

                TieInstances[index].occlIndex = ((bit >> 3) << 8) | (1 << (bit & 7));
                mapping += 2;
            }
        }

        Debug.occlusionMode = 2;
    }

    else {
        MobyInstance *moby;
        TieInstance *tie;

        printf_stub("***\nno occlusion\n***\n");
        for (moby = MobyInstances; moby != MobyInstanceEnd; moby++)
            moby->occlIndex = OCCL_NONE;

        for (tie = TieInstances; tie != TieInstanceEnd; tie++)
            tie->occlIndex = OCCL_NONE;

        for (int index = 0; index < TfragsCnt; index++)
            Tfrags[index].occlIndex = OCCL_NONE;

        Debug.occlusionMode = 0;
    }

    ResetDrawGlobals();
    Hero_ResetHero();
    Hero_InitStuff();
    InitCameras();
    UpdateCameras();
    InitPadRing();
    EnableFontColors();

    MobyIdListA[0] = 0;
    MobyIdListB[0] = 0;
    MobyIdListC[0] = 0;
    worldUpdateTime = 0;
    LevelSdata15F63C = 0;
    if (bootSpaceTransitionState.spaceship != 0)
        bootSpaceTransitionState.spaceship->lights = Hero.moby->lights;

    switch (Level) {
    case 2:
    case 5:
    case 6:
    case 7:
    case 8:
    case 10:
        ScreenColorEffectLevel = &ScreenColorEffectSpace;
        break;

    default:
        ScreenColorEffectLevel = &ScreenColorEffectDefault;
        break;
    }

    ScreenColorEffectNow = ScreenColorEffectLevel;
    return mem;
}

int SetupLevelWadBuffer(void)
{
    // The level WAD goes at the top of RAM, page aligned and with room for its header.
    int size = (bootAssets.frontbin.length * 0x800 + 0x1057) & 0xFFFFF000;

    levelRoot = (int *)((int)(LevelWadBufferEnd - size) & ~0xF);

    // The sound bank is read in right after the 0x60-byte header.
    levelRoot[LEVEL_WAD_SOUND_BANK] = 0x60;
    music_LoadBankFromEE((char *)levelRoot + levelRoot[LEVEL_WAD_SOUND_BANK], bootAssets.frontbin.offset, bootAssets.frontbin.length);

    return 1;
}


#define SECTOR_SHIFT 11
#define ROUND_UP_4K(bytes) (((bytes) + 0xFFF) & 0xFFFFF000)

// How long a stalled read may run before the drive is slowed down and the read retried.
#define CD_STALL_FRAMES 720

enum LevelLoadStage {
    LOAD_STAGE_SOUND_BANK_READ,
    LOAD_STAGE_SPACESHIP_READ,
    LOAD_STAGE_GAMEPLAY_READ,
    LOAD_STAGE_STOP_SOUNDS,
    LOAD_STAGE_UNLOAD_BANK,
    LOAD_STAGE_RESOLVE_UNLOAD,
    LOAD_STAGE_LOAD_BANK,
    LOAD_STAGE_RESOLVE_BANK,
};

// Top of the IOP memory the level streams its archives into, working downwards.
extern char IopLevelTop[];
extern short SpaceshipVariant[];
extern int cdStallFrames;
extern int cdSlowedDown;
extern int cdSpindleControl;
extern unsigned int levelSoundBank;
extern int videoModePal;

int music_LoadBankFromEE(void *destination, int sector, int sectors);
void sound_LoadBankCB(unsigned int bank, unsigned long userData);

// One step of streaming the level's IOP files (sound bank, spaceship and gameplay
// archives) and swapping in the new sound bank. Returns 1 once everything is loaded.
int LoadLevelFiles(void)
{
    int ship = SpaceshipVariant[0] + 1;
    int bytes;
    int sector;
    int sectors;
    char *gameplayBuffer;
    char *spaceshipBuffer;
    char *soundBankBuffer;

    if (sceCdSync(1) != 0) {
        cdStallFrames++;

        if (cdSpindleControl == 1 && cdStallFrames > CD_STALL_FRAMES) {
            int retryStage;

            cdSlowedDown = cdSpindleControl;
            retryStage = LevelLoad.stage - 1;
            cdSpindleControl = 0;
            if ((unsigned short)retryStage < 3)
                LevelLoad.stage = retryStage;

            sceCdBreak();
        }
        return 0;
    }

    if (sceCdGetError() != 0 && cdSlowedDown == 0) {
        int retryStage;

        cdSlowedDown = 1;
        retryStage = LevelLoad.stage - 1;
        cdSpindleControl = 0;
        if ((unsigned short)retryStage < 3)
            LevelLoad.stage = retryStage;
    }

    switch ((short)LevelLoad.stage) {
    case LOAD_STAGE_SOUND_BANK_READ:
        if (videoModePal)
            bytes = ROUND_UP_4K(bootAssets.gameplayPal.length << SECTOR_SHIFT);
        else
            bytes = ROUND_UP_4K(bootAssets.gameplayNtsc.length << SECTOR_SHIFT);

        gameplayBuffer = IopLevelTop - bytes;
        bytes = ROUND_UP_4K(bootAssets.spaceships[ship].length << SECTOR_SHIFT);
        spaceshipBuffer = gameplayBuffer - bytes;
        sectors = bootAssets.soundBank.length;
        bytes = ROUND_UP_4K(sectors << SECTOR_SHIFT);
        soundBankBuffer = spaceshipBuffer - bytes;
        sector = bootAssets.soundBank.offset;

        LevelLoad.spaceships = spaceshipBuffer;
        LevelLoad.gameplay = gameplayBuffer;
        LevelLoad.soundBank = (SoundBankWad *)soundBankBuffer;

        music_LoadBankFromEE(soundBankBuffer, sector, sectors);
        LevelLoad.stage++;
        break;

    case LOAD_STAGE_SPACESHIP_READ:
        music_LoadBankFromEE(LevelLoad.spaceships, bootAssets.spaceships[ship].offset, bootAssets.spaceships[ship].length);
        LevelLoad.stage++;
        break;

    case LOAD_STAGE_GAMEPLAY_READ:
        if (videoModePal)
            music_LoadBankFromEE(LevelLoad.gameplay, bootAssets.gameplayPal.offset, bootAssets.gameplayPal.length);
        else
            music_LoadBankFromEE(LevelLoad.gameplay, bootAssets.gameplayNtsc.offset, bootAssets.gameplayNtsc.length);

        LevelLoad.stage++;
        break;

    case LOAD_STAGE_STOP_SOUNDS:
        if (LevelLoad.hold)
            return 0;

        snd_StopAllSounds();

        if (levelSoundBank != 0)
            LevelLoad.stage++;
        else
            LevelLoad.stage = LOAD_STAGE_LOAD_BANK;
        break;

    case LOAD_STAGE_UNLOAD_BANK:
        if (snd_FlushSoundCommands())
            return 0;

        snd_UnloadBank(levelSoundBank);
        levelSoundBank = 0;
        LevelLoad.stage++;
        break;

    case LOAD_STAGE_RESOLVE_UNLOAD:
        if (snd_FlushSoundCommands())
            return 0;

        snd_ResolveBankXREFS();
        LevelLoad.stage++;
        break;

    case LOAD_STAGE_LOAD_BANK:
        if (snd_FlushSoundCommands())
            return 0;

        levelSoundBank = 0xFFFFFFFF;
        snd_BankLoadFromEE_CB((char *)(LevelLoad.soundBank->bankOffset + (int)LevelLoad.soundBank), sound_LoadBankCB, (unsigned int)&levelSoundBank);
        LevelLoad.stage++;
        break;

    case LOAD_STAGE_RESOLVE_BANK:
        if (snd_FlushSoundCommands())
            return 0;

        if (levelSoundBank == 0xFFFFFFFF)
            return 0;

        snd_ResolveBankXREFS();
        return 1;
    }

    return 0;
}


// Retail clears the hint's next time with an unaligned store.
struct UnalignedHintTime {
    char unk0[0x10];
    int nextTime __attribute__((packed, aligned(1)));
};


// The core header's sound table: spans of 4-byte sound references (offset from the
// table, count), the level's own first, then one per moby class.
struct SoundSpan {
    short offset;
    short count;
};

#define LEVEL_TEXTURE_REF(texDef, texData) \
    ((texData) + (texDef).offset + (FastLog2((texDef).width) << 28))
#define KILOBYTES(bytes) (FastIntToFloat((int)(bytes)) * (1.0f / 1024.0f))
#define MEGABYTES(bytes) (FastIntToFloat((int)(bytes)) * (1.0f / 1048576.0f))
#define OS_MEMORY_SIZE 0x100000

extern int MobyRefCurrent;      // the moby reference last loaded, -1 for none
extern int MobyRefBuffer;       // which of the two reference buffers it went into
extern unsigned long VisGifSpecialTemplate3[3];
extern int DrawSdata15F40C;     // the level's texture data
extern int DrawSdata15F420;     // the level's effect texture data
extern unsigned char occlCharTable[][16];
extern int TfragTexCnt;
extern int TfragTexLocs[];
extern int MobySdata15FFC8;     // moby texture count
extern int MobyTexLocs[];
extern char MemoryMapNewline[];
extern char *OcclOct;
extern int EffectTableCnt;
extern int *EffectTableEntries;
extern int *EffectTableOffsets;
extern int TieTexCnt;
extern int ShrubTexCnt;
extern int TieTexLocs[];
extern int ShrubTexLocs[];
extern TextureDef MobyTexDefs[];
extern int savedLevelSoundBank;
extern int MobyRefCnt;
extern int MobyRefOClasses[];
extern char *MobyRefData[];
extern int MobyRefUnk[];
extern u_long128 MobyRefTexRefs[];
extern unsigned short MobyRefSounds[][16];
extern SoundDef *LevelSounds;
extern int LevelSoundCnt;
extern char LevelProgramEnd[];
extern int LevelUnkVars[16];

void ParseTieClass(char *classData, TextureDef *texDefs, char *texRefs, int oClass);
void UpdateMobysInitial(void);

// Loads the level: (on a full load) its core data, textures, classes, sounds and spaceship,
// then its gameplay objects. keep restores the checkpoint state instead of clearing it.
int InitLevelFromWad(int full, int keep)
{
    MEMSLOTS *slots = &MemSlots;
    LevelCoreHeader *header = (LevelCoreHeader *)slots->vu1_chain[0];
    int *levelFile = (int *)LevelLoad.soundBank;  // the level WAD
    char *base;
    int used;
    char *soundRefs;
    char *mem;
    char *end;
    SoundSpan *span;
    TextureDef *mobyTexDefs;
    TextureDef *tfragTexDefs;
    TextureDef *tieTexDefs;
    TextureDef *shrubTexDefs;
    char *soundTable;
    int i;
    int j;
    int soundCnt;
    int k;
    int tfragTex, mobyTex, tieTex, shrubTex;
    int mobyRef;
    char *seqOffset;
    int seq;
    char *mobyRefEntry;
    int var;
    int classIndex;
    int sound;
    char *classEntry;

    if (full)
        LoadHudBanks();

    base = (char *)slots->levelBase;
    if (full) {
        FastMemCopy16(header, (char *)(levelFile[4] + (int)levelFile), levelFile[5]);
        DrawSdata15F40C = 0;
        FastMemCopy32(CheckpointLevelFlags, occlCharTable[Level], 0x10);
        ParsePermGsRam((char *)(levelFile[6] + (int)levelFile), header->permTexCnt, (PermGsTexture *)((char *)header + header->permTexs));
        savedLevelSoundBank = levelSoundBank;
        FlushCache(0);
        used = WadDecompress((char *)(levelFile[0x14] + (int)levelFile), base);
        DrawSdata15F40C = (int)(base + header->texData);

        VisGifSpecialTemplate[0] = SCE_GS_SET_TEX0((GSmemBase + header->tex128) >> 8, 2, GS_PSMT8, 7, 7, 1, 0,
                                                   (GSmemBase + header->clut128) >> 8, 0, 0, 0, 4);
        VisGifSpecialTemplate[1] = 0x0000FFA0000000E0;
        VisGifSpecialTemplate[2] = 0x0040000400004000;
        VisGifSpecialTemplateAlt[0] = SCE_GS_SET_TEX0((GSmemBase + header->tex64) >> 8, 1, GS_PSMT8, 6, 6, 1, 0,
                                                      (GSmemBase + header->clut64) >> 8, 0, 0, 0, 4);
        VisGifSpecialTemplateAlt[1] = 0x0000FFA0000000E0;
        VisGifSpecialTemplateAlt[2] = 0x0040000400004000;
        VisGifSpecialTemplate3[0] = SCE_GS_SET_TEX0((GSmemBase + header->tex128B) >> 8, 2, GS_PSMT8, 7, 7, 1, 0,
                                                    (GSmemBase + header->clut128B) >> 8, 0, 0, 0, 4);
        VisGifSpecialTemplate3[1] = 0x0000FFA0000000E0;
        VisGifSpecialTemplate3[2] = 0x0040000400004000;

        tfragTexDefs = (TextureDef *)((char *)header + header->tfragTexs);
        TfragTexCnt = header->tfragTexCnt;
        for (tfragTex = 0; tfragTex < TfragTexCnt; tfragTex++)
            TfragTexLocs[tfragTex] = LEVEL_TEXTURE_REF(tfragTexDefs[tfragTex], DrawSdata15F40C);

        mobyTexDefs = (TextureDef *)((char *)header + header->mobyTexs);
        MobySdata15FFC8 = header->mobyTexCnt;
        for (mobyTex = 0; mobyTex < MobySdata15FFC8; mobyTex++)
            MobyTexLocs[mobyTex] = LEVEL_TEXTURE_REF(mobyTexDefs[mobyTex], DrawSdata15F40C);

        FastMemCopy16(MobyTexDefs, mobyTexDefs, MobySdata15FFC8 * 16);

        tieTexDefs = (TextureDef *)((char *)header + header->tieTexs);
        TieTexCnt = header->tieTexCnt;
        for (tieTex = 0; tieTex < TieTexCnt; tieTex++)
            TieTexLocs[tieTex] = LEVEL_TEXTURE_REF(tieTexDefs[tieTex], DrawSdata15F40C);

        shrubTexDefs = (TextureDef *)((char *)header + header->shrubTexs);
        ShrubTexCnt = header->shrubTexCnt;
        for (shrubTex = 0; shrubTex < ShrubTexCnt; shrubTex++)
            ShrubTexLocs[shrubTex] = LEVEL_TEXTURE_REF(shrubTexDefs[shrubTex], DrawSdata15F40C);

        ParseTfrag(base + header->tfrags, (short *)((char *)header + header->tfragTexs));
        if (header->occlusion)
            OcclGrid = base + header->occlusion;
        else
            OcclGrid = 0;

        if (header->sky)
            ParseSky(base + header->sky);
        else
            Sky = 0;

        ParseColl(base + header->collision);

        for (i = 0, classEntry = (char *)header + header->mobyClasses; i < header->mobyClassCnt; i++, classEntry += 0x20)
            ParseMoby(*(int *)classEntry ? base + *(int *)classEntry : 0, (short *)((char *)header + header->mobyTexs),
                      classEntry + 0x10, *(int *)(classEntry + 4));

        PrintMobyMemory((int *)((char *)header + header->mobyClasses), header->mobyClasses);

        // Ratchet's animations, shared by every level.
        for (seq = 0, seqOffset = (char *)header + header->ratchetSeqs; seq < MobyClasses[0]->sequenceCount; seq++, seqOffset += 4) {
            if (*(int *)seqOffset) {
                MobyClasses[0]->animations[seq] = (MobySeq *)(base + *(int *)seqOffset);
                ParseMobySeq(MobyClasses[0], seq);
            }
        }

        MobyRefCurrent = -1;
        mobyRefEntry = (char *)header + header->mobyRefs;
        MobyRefBuffer = 0;
        MobyRefCnt = header->mobyRefCnt;
        for (mobyRef = 0; mobyRef < header->mobyRefCnt; mobyRef++, mobyRefEntry += 0x10) {
            MobyRefOClasses[mobyRef] = *(int *)(mobyRefEntry + 4);
            MobyRefData[mobyRef] = base + *(int *)mobyRefEntry;
            MobyRefUnk[mobyRef] = *(int *)(mobyRefEntry + 8);
            {
                int texRefsOffset = (unsigned char)MobyClassLookup[*(int *)(mobyRefEntry + 4)] * 32 + 0x10;

                CopyVec4Inline((Vec4 *)&MobyRefTexRefs[mobyRef], (Vec4 *)((char *)header + header->mobyClasses + texRefsOffset));
            }
        }

        for (i = 0, classEntry = (char *)header + header->tieClasses; i < header->tieClassCnt; i++, classEntry += 0x20)
            ParseTieClass(base + *(int *)classEntry, (TextureDef *)((char *)header + header->tieTexs), classEntry + 0x10,
                          *(int *)(classEntry + 4));

        STUB_RET_255950((char *)header + header->tieClasses, header->tieClassCnt);

        for (i = 0, classEntry = (char *)header + header->shrubClasses; i < header->shrubClassCnt; i++, classEntry += 0x30)
            ParseShrubClass(base + *(int *)classEntry, (TextureDef *)((char *)header + header->shrubTexs), classEntry + 0x10,
                            (BillboardTexDef *)(classEntry + 0x20), *(int *)(classEntry + 4));

        DrawSdata15F420 = (int)(base + header->fxTexData);
        ParseEffectTexs((int *)((char *)header + header->fxTexs), header->fxTexCnt);

        if (header->effectTable) {
            RelocEffectTable((int *)(base + header->effectTable));
        } else {
            EffectTableCnt = 0;
            EffectTableEntries = 0;
            EffectTableOffsets = 0;
        }

        if (header->byteGrid) {
            LoadByteGrid((int *)(base + header->byteGrid));
        } else {
            byteGridStride = 0;
            byteGridRows = 0;
            byteGridMax = 0;
            byteGridMin = 0;
            byteGridData = 0;
        }

        if (header->occlOct)
            OcclOct = base + header->occlOct;
        else
            OcclOct = 0;

        {
            char *partTexData = base + header->partTexData;
            char *partTexDefs = (char *)header + header->partTexs;

            ParseParticleTexs((int *)((char *)header + header->partTexDefs), (int)partTexData, (int *)partTexDefs, header->partTexCnt);
        }

        // The level's sounds, then each moby class's.
        soundTable = (char *)header + header->sounds;
        span = (SoundSpan *)soundTable;
        mem = (char *)((unsigned int)(base + used + 0x3F) & ~0x3F);
        soundCnt = span->count;
        LevelSounds = (SoundDef *)mem;
        LevelSoundCnt = soundCnt;
        FastMemCopy32(mem, soundTable + span->offset, soundCnt * 32);
        span++;
        mem += soundCnt * 32;
        soundRefs = soundTable + span->offset;
        for (sound = 0; sound < LevelSoundCnt; sound++) {
            if (LevelSounds[sound].index >= span->count) {
                printf_stub("internal level sound mismatch\n");
                LevelSounds[sound].index = -1;
            } else {
                LevelSounds[sound].index = *(unsigned short *)(soundRefs + LevelSounds[sound].index * 4);
            }
            LevelSounds[sound].bank_index = levelSoundBank;
        }

        end = mem + 0x3F;
        span++;
        for (classIndex = 0; classIndex < MobyClassIndex; classIndex++, span++) {
            MobyClass *mobyClass = MobyClasses[classIndex];

            if (mobyClass == 0) {
                for (j = 0; j < MobyRefCnt; j++)
                    if (MobyRefOClasses[j] == MobyOClasses[classIndex])
                        break;

                if (j < MobyRefCnt) {
                    FastMemSet(MobyRefSounds[j], -1, 0x20);
                    soundRefs = soundTable + span->offset;
                    for (k = 0; k < span->count && k < 15; k++, soundRefs += 4)
                        MobyRefSounds[j][k] = *(unsigned short *)soundRefs;
                }
            } else {
                if (span->count != mobyClass->soundCount)
                    printf_stub("internal moby sound mismatch on moby %d\n", MobyOClasses[classIndex]);

                soundRefs = soundTable + span->offset;
                for (k = 0; k < MobyClasses[classIndex]->soundCount; k++, soundRefs += 4) {
                    MobyClasses[classIndex]->soundDefs[k].index = *(unsigned short *)soundRefs;
                    MobyClasses[classIndex]->soundDefs[k].bank_index = levelSoundBank;
                }
            }
        }

        MemSlots.levelData = (unsigned char *)ParseMobyPack((char *)((unsigned int)end & ~0x3F), header);
    }

    MemSlots.levelEnd = (unsigned char *)ResetLevelData(full);

    if (full) {
        char *codeEnd;

        printf_stub("\n*** MEMORY MAP ***\n\n");
        printf_stub("os:             %.1fK\n", KILOBYTES(OS_MEMORY_SIZE));
        codeEnd = LevelProgramEnd;
        printf_stub("code mem:       %.1fK\n", KILOBYTES(codeEnd - OS_MEMORY_SIZE));
        printf_stub("dead space:     %.1fK\n", KILOBYTES((char *)MemSlots.base - codeEnd));
        printf_stub("vu chain bufs:  %.1fK\n", KILOBYTES(MemSlots.hudHeap - (unsigned char *)MemSlots.base));
        printf_stub("hud:            %.1fK\n", KILOBYTES(MemSlots.gadgetBuffer - MemSlots.hudHeap));
        printf_stub("gadget buffer:  %.1fK\n", KILOBYTES(MemSlots.levelBase - MemSlots.gadgetBuffer));
        if (OcclGrid != 0)
            printf_stub("tfrag geom:     %.1fK\n", KILOBYTES((unsigned char *)OcclGrid - MemSlots.levelBase));
        else if (Sky != 0)
            printf_stub("tfrag geom:     %.1fK\n", KILOBYTES((unsigned char *)Sky - MemSlots.levelBase));
        else
            printf_stub("tfrag geom:     unknown\n");

        if (OcclGrid != 0) {
            if (Sky != 0)
                printf_stub("occlusion:      %.1fK\n", KILOBYTES((int)Sky - (int)OcclGrid));
            else
                printf_stub("occlusion:      %.1fK\n", KILOBYTES(CollOutput.grid - (char *)OcclGrid));
        }

        if (header->sky)
            printf_stub("sky:            %.1fK\n", KILOBYTES(CollOutput.grid - (char *)Sky));

        printf_stub("collision:      %.1fK\n", KILOBYTES(DrawSdata15F40C - (int)CollOutput.grid));
        printf_stub("shared vram:    %.1fK\n", KILOBYTES((PartTexs[0].unk_04 >> 4) - DrawSdata15F40C));
        printf_stub("particle vram:  %.1fK\n", KILOBYTES(DrawSdata15F420 - (PartTexs[0].unk_04 >> 4)));
        printf_stub("effects vram:   %.1fK\n", KILOBYTES((char *)MobyClasses[0] - (char *)DrawSdata15F420));
        printf_stub("mobys:          %.1fK\n", KILOBYTES((char *)TieClasses[0] - (char *)MobyClasses[0]));
        if (header->shrubClassCnt)
            printf_stub("ties:           %.1fK\n", KILOBYTES((char *)ShrubClasses[0] - (char *)TieClasses[0]));
        else
            printf_stub("ties:           %.1fK\n", KILOBYTES((char *)TieInstances - (char *)TieClasses[0]));

        if (header->shrubClassCnt)
            printf_stub("shrubs:         %.1fK\n", KILOBYTES((char *)MobyClasses[0]->animations[0] - (char *)ShrubClasses[0]));

        printf_stub("ratchett seqs:  %.1fK\n", KILOBYTES((char *)TieInstances - (char *)MobyClasses[0]->animations[0]));
        printf_stub("tie insts:      %.1fK\n", KILOBYTES((char *)ShrubInstances - (char *)TieInstances));
        printf_stub("shrub insts:    %.1fK\n", KILOBYTES((char *)MobyInstances - (char *)ShrubInstances));
        printf_stub("moby insts:     %.1fK\n", KILOBYTES((char *)mobyVars - (char *)MobyInstances));
        printf_stub("moby pvars:     %.1fK\n", KILOBYTES((char *)SplineData - (char *)mobyVars));
        printf_stub("paths:          %.1fK\n", KILOBYTES((char *)PartInstances - (char *)SplineData));
        printf_stub("part insts:     %.1fK\n", 128.0);
        printf_stub(MemoryMapNewline);
        printf_stub("end of mem:     %.1fM\n", MEGABYTES((int)PartInstances + 0x20000));
        printf_stub(MemoryMapNewline);
        {
            unsigned char *start = (unsigned char *)MemSlots.base - 0x2D0000;

            printf_stub("estimated mem:  %.1fM\n", MEGABYTES(MemSlots.levelEnd - start));
        }
        printf_stub(MemoryMapNewline);
    }

    if (keep) {
        RestoreCheckpoint();
    } else {
        ClearCheckpointData();
        for (var = 15; var >= 0; var--)
            LevelUnkVars[var] = 0;
    }

    ((UnalignedHintTime *)&ActiveHint)->nextTime = 0;
    UpdateMobysInitial();
    worldUpdateTime++;
    return 0;
}

// loaders.cpp's small data, in retail order. Defined after the functions above so they reach it
// with lui, as retail does.

// InitLevelFromWad's memory map line break.
char MemoryMapNewline[] = "\n";

// Per mission, 0xFF once its level flag is set (ResetLevelData).
unsigned char CheckpointLevelFlags[16] = { 0 };

int byteGridStride = 0;
int byteGridRows = 0;
float byteGridMin = 0;
float byteGridMax = 0;
unsigned char *byteGridData = 0;

// Starts streaming a chunk of the current npc scene from the disc into the scene buffer.
int PreLoadNpcChunk(int chunk)
{
    unsigned char *buffer = SceneLoad.buffer;
    int sector;
    int length;

    if (videoModePal) {
        length = bootAssets.scenes[SceneLoad.sceneId].palChunkSectors[chunk + 1] - bootAssets.scenes[SceneLoad.sceneId].palChunkSectors[chunk];
        sector = bootAssets.scenes[SceneLoad.sceneId].palChunkSectors[chunk];
    }

    else {
        length = bootAssets.scenes[SceneLoad.sceneId].chunkSectors[chunk + 1] - bootAssets.scenes[SceneLoad.sceneId].chunkSectors[chunk];
        sector = bootAssets.scenes[SceneLoad.sceneId].chunkSectors[chunk];
    }

    if (length > 0) {
        music_LoadFile(buffer, sector, length);
        music_Sync(0);
    }

    return 1;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/loaders", ParseNpcChunk);

// Points SceneLoad.chunks at each chunk of the scene file just loaded into the scene buffer.
static inline void SetSceneChunks(void)
{
    SceneChunkEntry *entry = (SceneChunkEntry *)SceneLoad.buffer;
    int chunk;

    for (chunk = 0; chunk < SCENE_MAX_CHUNKS && entry->length != 0; chunk++, entry++)
        SceneLoad.chunks[chunk] = SceneLoad.buffer + (entry->offset + SCENE_HEADER_SIZE);
}

void LoadWeaponCutscene(int weapon)
{
    if (!videoModePal)
        music_LoadFile(SceneLoad.buffer, bootAssets.weaponScenes[weapon].offset, bootAssets.weaponScenes[weapon].length);

    else
        music_LoadFile(SceneLoad.buffer, bootAssets.palWeaponScenes[weapon].offset, bootAssets.palWeaponScenes[weapon].length);

    music_Sync(0);
    FadeToBlack(4);
    music_Sync(1);

    SetSceneChunks();
}

void ParseWeaponSceneChunk(int chunk)
{
    SceneLoad.buffer = SceneLoad.chunks[chunk];
    ParseNpcChunk();
    SceneLoad.buffer = MemSlots.vu1_chain[1] + vu1_bufSize;
}

void LoadSpaceScene(int scene, int fadeFrames)
{
    if (!videoModePal)
        music_LoadFile(SceneLoad.buffer, bootAssets.spaceScenes[scene].offset, bootAssets.spaceScenes[scene].length);

    else
        music_LoadFile(SceneLoad.buffer, bootAssets.palSpaceScenes[scene].offset, bootAssets.palSpaceScenes[scene].length);

    if (fadeFrames) {
        music_Sync(0);
        FadeToBlack(fadeFrames);
    }

    music_Sync(1);

    SetSceneChunks();
}

void ParseSpaceSceneChunk(int chunk)
{
    SceneLoad.buffer = SceneLoad.chunks[chunk];
    ParseNpcChunk();
    SceneLoad.buffer = MemSlots.vu1_chain[1] + vu1_bufSize;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/loaders", LoadMobyModel);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/loaders", QueuePifLoad);

#define PIF_LOAD_QUEUE_SIZE 64

// One queued clut + texture upload to GS memory.
struct PifLoad {
    char *clut;             // 0x00
    short clutFormat;       // 0x04
    short clutBlock;        // 0x06
    char *tex;              // 0x08
    unsigned char uLog;     // 0x0C
    unsigned char vLog;     // 0x0D
    short texBlock;         // 0x0E
};

extern int GifLoadCnt;
extern PifLoad GifLoads[];

// Queues an 8-bit texture and its clut for upload and returns the TEX0 register value that
// will address it.
unsigned long QueuePifLoad(int uLog, int vLog, char *clut, char *tex, int clutAddr, int texAddr)
{
    int tbw = uLog - 6;
    unsigned long tex0;

    if (tbw < 0)
        tbw = 0;
    tbw = 1 << tbw;

    tex0 = SCE_GS_SET_TEX0(texAddr >> 8, tbw, GS_PSMT8, uLog, vLog, 1, 0, clutAddr >> 8, 0, 0, 0, 4);

    if (GifLoadCnt < PIF_LOAD_QUEUE_SIZE) {
        GifLoads[GifLoadCnt].clut = clut;
        GifLoads[GifLoadCnt].clutBlock = clutAddr >> 8;
        GifLoads[GifLoadCnt].clutFormat = 0;
        GifLoads[GifLoadCnt].tex = tex;
        GifLoads[GifLoadCnt].uLog = uLog;
        GifLoads[GifLoadCnt].vLog = vLog;
        GifLoads[GifLoadCnt].texBlock = texAddr >> 8;
        GifLoadCnt++;
    }

    return tex0;
}

// Debug-build paths of the NPC scene files; nothing in the release code reads them.
extern const char NpcScenePath[] = "host0:z:/i5/levels/level%d/npcs/scene_%d/scene.dat";
extern const char NpcScenePathPal[] = "host0:z:/i5/levels/level%d/npcs/scene_%d/scenep.dat";
