#ifndef LOADERS_H
#define LOADERS_H

struct MobyClass;

void STUB_RET_255950(void *data, int count);

void ParseMobySeq(MobyClass *mobyClass, int animation);

void ParseWeaponSceneChunk(int chunk);

void ParseSpaceSceneChunk(int chunk);

#define SCENE_MAX_CHUNKS 70
#define SCENE_HEADER_SIZE 0x800

// State of the npc scene (cutscene) being streamed in.
struct SceneLoadState {
    char unk_00[0x30];
    int sceneId;                    // 0x30
    char unk_34[0x24];
    unsigned char *decodedChunk;    // 0x58
    unsigned char *buffer;          // 0x5C
    unsigned char *chunks[SCENE_MAX_CHUNKS]; // 0x60
};

// Table at the start of a loaded scene file: where each chunk sits, counted
// from the end of the 0x800-byte header. A zero length ends the table.
struct SceneChunkEntry {
    int offset;
    int length;
};

extern SceneLoadState SceneLoad;

int PreLoadNpcChunk(int chunk);
void LoadWeaponCutscene(int weapon);
void LoadSpaceScene(int scene, int fadeFrames);
void ParseNpcChunk(void);

#endif
