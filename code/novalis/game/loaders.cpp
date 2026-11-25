#include "common.h"
#include "vuchain.h"
#include "moby.h"
#include "loaders.h"
#include "music.h"
#include "wad.h"
#include "draw.h"
#include "hud.h"
#include "initlevel.h"
#include "mathfunc_inline.h"

void LoadByteGrid(int *grid)
{
    byteGridStride = *grid++;
    byteGridRows = *grid++;
    byteGridMin = *(float *)grid++;
    byteGridMax = *(float *)grid++;
    byteGridData = (unsigned char *)grid;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/loaders", RelocEffectTable);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/loaders", ParseGsRamTextures);

TEXT_PADDING(0x27BD0060, 0x00000000);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/loaders", ParseParticleTexs);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/loaders", ParseEffectTexs);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/loaders", ParseSky);

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

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/loaders", SetUpVisGif);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/loaders", SetUpVisGifViewer);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/loaders", ParsePermGsRam);

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

void SetUpVisGif(int *gif, short *texDef, int mipDist, int filter, int clampU, int clampV, int index);
void SetUpVisGifViewer(int *gif, int mipDist, int filter, int clampU, int clampV, int index);

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
                SetUpVisGif((int *)gif, texDefs + texIndex * 8, gif->mipDist, gif->filter, gif->clampU, gif->clampV, texIndex);
            else
                SetUpVisGifViewer((int *)gif, gif->mipDist, gif->filter, gif->clampU, gif->clampV, texIndex);

            gif++;
        }
    }
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/loaders", ParseMoby);

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

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/loaders", LoadLevelFiles);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/loaders", InitLevelFromWad);

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
