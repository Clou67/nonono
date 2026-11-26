#ifndef LOADERS_H
#define LOADERS_H

#include "moby.h"

struct MobyClass;

// Texture file header; the clut and the mip levels follow it.
struct PifHeader {
    int pifID;
    int fileSize;
    int uSize;
    int vSize;
    int texFormat;
    int clutFormat;
    int clutOrder;
    int mipLevels;
};

// Where each part of a pif goes while it is uploaded.
struct PifParser {
    void* pClut;
    void* pTex[4];
    int cSize;
    int tSize[4];
    int cPos;
    int tPos[4];
    int tbw[4];
    int uLog;
    int vLog;
};

enum PifFormat {
    PIF_PSMCT32 = 0x00,
    PIF_PSMCT16 = 0x02,
    PIF_PSMT8 = 0x13,
    PIF_PSMT4 = 0x14,
};

int ParseGsRamTextures(PifHeader *pif, unsigned long long *gsRegisters);
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
    char *jointCache;         // 0x04
    char *jointCacheKeys;     // 0x08
    int jointCacheNext;       // 0x0C
    int collCount;            // 0x10
    int damageNext;           // 0x14
    char unk_18[0x68];
};

extern CollOutputData CollOutput;
extern char CollMobyJointCache[];

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


struct MobyInstance;
struct Vec4;

// Offsets from the start of the gameplay file to its sections (PS3 names). A section starts
// with its count, padded to 16 bytes, unless noted.
struct GameplayHeader {
    int settings;               // 0x00 background, fog and ship settings
    int directionalLights;      // 0x04
    int cameras;                // 0x08
    int sounds;                 // 0x0C
    int help[9];                // 0x10 per language
    int ties;                   // 0x34
    int unk_38;
    int shrubs;                 // 0x3C
    int unk_40;
    int mobys;                  // 0x44
    int mobyGroups;             // 0x48
    int sharedData;             // 0x4C
    int mobyLinks;              // 0x50
    int pvarTable;              // 0x54
    int pvarData;               // 0x58
    int pvarPointers;           // 0x5C
    int cuboids;                // 0x60
    int spheres;                // 0x64
    int cylinders;              // 0x68
    int pills;                  // 0x6C
    int splines;                // 0x70
    int grindPaths;             // 0x74
    int pointLightGrid;         // 0x78
    int pointLights;            // 0x7C
    int blenders;               // 0x80
    int camCollGrid;            // 0x84
    int envSamples;             // 0x88
    int occlusion;              // 0x8C
};

// A pVar block in the gameplay file; offset becomes its address once copied.
struct PvarEntry {
    int offset;
    int size;
};

// A camera placed in the level.
struct ImportCamera {
    float pos[3];
    int type;
    float rot[3];
    // An index into the pVar table until the level is loaded.
    int pVar;
};

// A rail the hero can grind on: a bounding sphere, then its points.
struct GrindPath {
    float bSphere[4];
    char *data;
    int unk14;
    char unk18[8];
};

// A colour blend region (PS3 Blender); its two light indices default to 11.
// A lighting/fog blend volume (field names from the PS3 project).
struct Blender {
    Mtx4 invMatrix;                 // 0x00
    unsigned int ambientA;          // 0x40: ABGR
    unsigned int ambientB;          // 0x44: ABGR
    int dLightA;                    // 0x48: directional light index (BLENDER_LIGHT_DEFAULT if none)
    int dLightB;                    // 0x4C
    unsigned int flags;             // 0x50
    unsigned int fogColor1;         // 0x54: ABGR
    unsigned int fogColor2;         // 0x58: ABGR
    float fogNearDist1;             // 0x5C
    float fogNearIntensity1;        // 0x60
    float fogFarDist1;              // 0x64
    float fogFarIntensity1;         // 0x68
    float fogNearDist2;             // 0x6C
    float fogNearIntensity2;        // 0x70
    float fogFarDist2;              // 0x74
    float fogFarIntensity2;         // 0x78
    int unk;                        // 0x7C
};

#define BLENDER_LIGHT_DEFAULT 11
#define MAX_DIRECTIONAL_LIGHTS 12

// A shrub instance's transform; the w of its rows hold its colour, its averaged vertex
// colour, its packed scale and its class scale.
struct ShrubMatrix {
    union {
        Mtx4 mtx;
        struct {
            float right[3];
            int color;
            float forward[3];
            int averageColor;
            float up[3];
            // Side and up scales in 4.12 fixed point.
            int packedScale;
            float position[3];
            float scale;
        };
    };
};

// Where the shrub vertex colours are kept for the renderer.
struct ShrubColorBufferInfo {
    int unk0;
    unsigned char *colors;
    char unk08[0x78];
};

// Scratchpad lists of the objects to light, ended by 0xFFFF.
#define SPR_LIGHT_LIST 0x70000000
#define SPR_TFRAG_LIGHT_LIST 0x70003000

// Moby spawn flags in the gameplay file.
enum MobySpawnFlag {
    MOBYSPAWN_LEVEL_FLAG = 1,
    MOBYSPAWN_NO_LEVEL_FLAG = 2,
    MOBYSPAWN_IF_LEVEL = 4,
    MOBYSPAWN_IF_CHECKPOINT = 8,
    MOBYSPAWN_MAP_SLOT = 0x10
};

#define MAPSLOT_NONE 0xFE
#define MAPSLOT_UNSET 0xFF
#define MOBY_GROUP_END 0x8000
#define OCCL_NONE 0x7F80

// The gameplay file as read from the disc, before it is unpacked.
extern char *levelBuffers[2];
#define gameplayFile levelBuffers[1]

extern ImportCamera *ImportCameras;
extern int ImportCameraCnt;
extern float HeroDeathHeight;
extern int BlenderCnt;
extern char BlenderInfo[];
extern Blender Blenders[];
extern char *CamCollGrid;
extern char *PointLightGrid;
extern char *PointLightRecords;
extern int PointLightRecordCnt;
extern GrindPath *GrindPaths;
extern int GrindPathCnt;
extern char *Pills;
extern int PillCnt;
extern int CuboidCnt;
extern int SphereCnt;
extern int CylinderCnt;
extern int SplineCnt;
// The spline points; Splines point into it.
extern char *SplineData;
extern char *Splines[];
extern char *EnvSamples;
extern int EnvSampleCnt;

extern int ShrubCnt;
extern ShrubMatrix *ShrubMatrices;
// 24 RGBA vertex colours per shrub.
extern unsigned char *ShrubVertexColors;
extern ShrubColorBufferInfo ShrubColorBuffer;
extern float ShrubDrawDist;
extern float TfragDrawDist;

// Per mission, 0xFF once its level flag is set (PS3 g_CheckpointLevelFlags).
extern unsigned char CheckpointLevelFlags[16];
// Per moby uid, set when the checkpoint removed it.
extern unsigned char CheckpointObjState[];
// Maps a moby record of the gameplay file to its instance, -1 when it did not spawn.
extern short MobyIndexRemap[];
extern short *MobyGroupEntries[];
extern int MobySdata15FFF0;
// One more than the last moby group in use.
extern int MobySdata15FFF4;
extern char *mobyVars;
extern MobyInstance *MobyInstancePermEnd;
extern MobyInstance *MobyInstanceEnd;
extern char MobyGrids[];
extern char MobyGridAlloc[];

// Set when the level places the player's ship itself; the ship's class per variant.
extern int SpaceshipPreplaced;
extern int SpaceshipOClasses[];

// Lists cleared for each level (their use is not known yet).
extern short MobyIdListA[];
extern short MobyIdListB[];
extern short MobyIdListC[];
extern int LevelSdata15F63C;

extern char *PartInstances;
extern int PartIndexTop;
extern int PartIndexNext;
extern int PartActiveCnt;
extern int PartClipDist;
extern char PartAlloc[];

// The space transition and player's ship state kept in the core.
struct SpaceTransitionState {
    MobyInstance *spaceship;        // 0x00
    char unk_04[0x22];
    short shipVariant;              // 0x26
    char unk_28[8];
    int shipSplinePath;             // 0x30
    int shipCameraStartCuboid;      // 0x34
    int shipCameraEndCuboid;        // 0x38
};

extern SpaceTransitionState bootSpaceTransitionState;

#define LEVEL_GEMLIK 13
#define SHIP_VARIANT_GEMLIK 2

char *ResetLevelData(int reload);

#endif
