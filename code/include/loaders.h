#ifndef LOADERS_H
#define LOADERS_H

struct MobyClass;

void STUB_RET_255950(void *data, int count);

void ParseMobySeq(MobyClass *mobyClass, int animation);

void ParseWeaponSceneChunk(int chunk);

void ParseSpaceSceneChunk(int chunk);

// State of the npc scene (cutscene) being streamed in.
struct SceneLoadState {
    char unk_00[0x30];
    int sceneId;                    // 0x30
    char unk_34[0x24];
    unsigned char *decodedChunk;    // 0x58
    unsigned char *buffer;          // 0x5C
    unsigned char *chunks[1];       // 0x60
};

extern SceneLoadState SceneLoad;

int PreLoadNpcChunk(int chunk);
void ParseNpcChunk(void);

#endif
