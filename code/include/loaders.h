#ifndef LOADERS_H
#define LOADERS_H

struct MobyClass;
struct WadEntry;

// The level WAD buffer starts with a table of offsets from its start to each part.
enum {
    LEVEL_WAD_SOUND_BANK = 0      // word 0; see LevelWadHeader for the rest
};

// Points at the level WAD buffer at the top of RAM.
extern int *levelRoot;

struct LevelWadHudBank {
    int offset;
    int size;
};

// The start of the level WAD buffer seen as a struct.
struct LevelWadHeader {
    int soundBank;                    // 0x00
    char unk_04[0x24];
    LevelWadHudBank hudBanks[6];      // 0x28
};

// End of the space the level WAD buffer is placed below.
extern char LevelWadBufferEnd[];

// The level's byte grid: stride * rows bytes mapping 0..255 onto min..max.
extern int byteGridStride;
extern int byteGridRows;
extern float byteGridMin;
extern float byteGridMax;
extern unsigned char *byteGridData;

// Hero-only collision cell (the camera passes through it).
struct HeroCollCell {
    short bsphereX;
    short bsphereY;
    short bsphereZ;
    short bsphereRad;
    short triCount;
    short vertCount;
    char *data;               // 0x0C: offset from the header, relocated by ParseColl
};

struct HeroCollHeader {
    int cellCount;
    int pad[3];
    HeroCollCell cells[1];
};

extern HeroCollHeader *HeroCollision;

// The result of the last collision query; only the fields known so far.
struct CollOutputData {
    char *grid;               // 0x00: the env collision grid
    char unk_04[0x7C];
};

extern CollOutputData CollOutput;

void LoadByteGrid(int *grid);
void ParseColl(char *data);
void LoadCompressedHudBank(int bank, char *destination);
int SetupLevelWadBuffer(void);
void WadDecompress(void *source, void *destination);

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
