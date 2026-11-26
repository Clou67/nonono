#include "common.h"
#include "vuchain.h"
#include "moby.h"
#include "loaders.h"
#include "initlevel.h"
#include "part.h"
#include "sky.h"
#include "framebuf.h"
#include "sce.h"
#include "fastfunc.h"
#include "music.h"
#include "sound.h"
#include "wad.h"
#include "draw.h"
#include "hud.h"
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

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/loaders", RelocEffectTable);

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

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/loaders", ParseMobyPack);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/loaders", LoadHudBanks);

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

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/loaders", ParseTieClass);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/loaders", ParseShrubClass);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/loaders", ParseTfrag);

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

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/loaders", PrintMobyMemory);

void STUB_RET_255950(void *data, int count)
{
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/loaders", ResetLevelData);

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

// Start of the sound bank archive; the bank itself sits bankOffset bytes in.
struct SoundBankWad {
    int unk_0[2];
    int bankOffset;
};

// Top of the IOP memory the level streams its archives into, working downwards.
extern char IopLevelTop[];
extern short SpaceshipVariant[];
// State of the level file load (one small-data object).
struct LevelLoadState {
    unsigned short stage;
    short hold;               // set while the level must not swap sound banks yet
    SoundBankWad *soundBank;  // IOP sound bank archive
    char *gameplay;           // IOP gameplay archive
    char *spaceships;         // IOP spaceship archive
};

extern LevelLoadState LevelLoad;
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

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/loaders", InitLevelFromWad);

// loaders.cpp's small data, in retail order. Defined after the functions above so they reach it
// with lui, as retail does.

// Texture definitions and texture remap of the spaceship pack's two moby classes (ParseMobyPack).
short ShipTexDefA[8] = { 0, 0, 0x100, 0x100, 4, 0, 0, 0 };
short ShipTexDefB[8] = { 0, 0, 0x80, 0x80, 1, 0, 0, 0 };
unsigned char ShipTexRefs[16] = {
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
};

// Stand-ins for LoadHudBanks' and InitLevelFromWad's string literals until those are decompiled.
char LoadersTimerLabel[] = "loaders.cpp";
char HudBankLabel0[] = "hud bank 0";
char HudBankLabel2[] = "hud bank 2";
char HudBankLabel3[] = "hud bank 3";
char HudBankLabel4[] = "hud bank 4";
char MemoryMapNewline[] = "\n";

// The current level's occlusion character table, copied in by InitLevelFromWad.
unsigned char LevelOcclChars[16] = { 0 };

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

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/loaders", QueuePifLoad_Raw);
