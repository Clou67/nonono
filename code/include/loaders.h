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

// A texture in GS memory; TEX0 is built when it is first drawn.
struct EffectTex {
    unsigned long tex0;           // 0x00
    unsigned short texOfs;        // 0x08
    unsigned short palOfs;        // 0x0A
    unsigned short uLog;          // 0x0C
    unsigned short vLog;          // 0x0E
};

extern int EffectTexCnt;
extern EffectTex EffectTexs[];

int FastLog2(int value);
void ParseParticleTexs(int *header, int gsBase, int *texDefs, int count);
void ParseEffectTexs(int *texDefs, int count);
void ParseSky(char *data);

// Per-template GS register words used when building class GIF packets (3 words per row).
extern unsigned long VisGifTemplates[];
extern unsigned long VisGifSpecialTemplate[3];
extern unsigned long VisGifSpecialTemplateAlt[3];

// A class texture definition (8 shorts).
enum {
    TEXDEF_WIDTH = 2,
    TEXDEF_HEIGHT = 3,
    TEXDEF_MIP_COUNT = 4,
    TEXDEF_CLUT = 5,
    TEXDEF_MIP1 = 6,
    TEXDEF_MIP2 = 7
};

#define GS_PSMCT32 0x00
#define GS_PSMCT16 0x02
#define GS_PSMT8 0x13

// One permanent texture in the level data: its format, size and where its pixels are.
struct PermGsTexture {
    int psm;        // 0x00
    int size;       // 0x04: width | height << 16
    int unk_08;
    int offset;     // 0x0C: from the data start
};

void ParsePermGsRam(char *data, int count, PermGsTexture *texture);

void SetUpVisGif(unsigned long *gifRegs, short *texDef, int mipDist, int filter, int clampU, int clampV, int index);
void SetUpVisGifViewer(unsigned long *gifRegs, int mipDist, int filter, int clampU, int clampV, int index);

void LoadByteGrid(int *grid);
void ParseColl(char *data);
void LoadCompressedHudBank(int bank, char *destination);
int SetupLevelWadBuffer(void);
void WadDecompress(void *source, void *destination);

void STUB_RET_255950(void *data, int count);

void ParseMobyClass(MobyClass *mobyClass, short *texDefs, char *texRefs, int oClass);
int LoadLevelFiles(void);

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
