#ifndef SPACE_H
#define SPACE_H

enum SpaceShipVariant {
    SPACE_SHIP_INITIAL = 0,
    SPACE_SHIP_BATALIA = 1,
    SPACE_SHIP_OLTANIS = 2
};

enum SpacePlateUpload {
    SPACE_PLATE_SHARED_CLUT,
    SPACE_PLATE_SHARED_TEXTURE,
    SPACE_PLATE_FIRST_CLUT,
    SPACE_PLATE_FIRST_TEXTURE,
    SPACE_PLATE_LAST_CLUT,
    SPACE_PLATE_LAST_TEXTURE,
    SPACE_PLATE_UPLOAD_COUNT
};

// TEX0 low fields: PSMT8, with TBW/TW for 64x64 or 512x64 images.
enum {
    SPACE_PLATE_SHARED_TEX0_LOW = 0x19304000,
    SPACE_PLATE_IMAGE_TEX0_LOW = 0x25320000
};

#define SPACE_PLATE_TEX0_HIGH ((6ULL << 30) | (1ULL << 34)) // TH=6, TCC=RGBA
#define SPACE_PLATE_TEX0_CLD (4ULL << 61)

// Serialized space WAD header; offsets are relative to the header or its data block.
struct SpaceWadHeader {
    int permTexData;    /* 0x00 */
    int dataOffset;     /* 0x04 */
    int permTexCount;   /* 0x08 */
    int permTexDefs;    /* 0x0C */
    int mobyCount;      /* 0x10 */
    int mobys;          /* 0x14 */
    int mobyTexCount;   /* 0x18 */
    int mobyTexDefs;    /* 0x1C */
    int partTexCount;   /* 0x20 */
    int partTexDefs;    /* 0x24 */
    int effectTexCount; /* 0x28 */
    int effectTexDefs;  /* 0x2C */
    int mobyTexData;
    int partTexData;
    int textureData;
    int partTexHeaders;
    int specialTextureBase;
    int specialClutBase;
    int sky; /* 0x48 */
    int planetTextures;
    int scenes[5]; /* 0x50 */
    int sound;     /* 0x64 */
};

struct SpaceMobyEntry {
    int offset;
    int oClass;
    int unk_08[2];
    unsigned char textureRefs[0x10];
};

struct QuadCornerIndex {
    short vertexIndex;
    short normalIndex;
};
struct IndexedQuad {
    QuadCornerIndex corners[4];
};

struct Vec4;
extern Vec4 SpaceEnvNormals0[];
extern Vec4 SpaceEnvNormals1[];
extern Vec4 SpaceEnvNormals2[];
extern Vec4 SpaceEnvNormals3[];
extern Vec4 SpaceEnvPositions0[];
extern Vec4 SpaceEnvPositions1[];
extern Vec4 SpaceEnvPositions2[];
extern Vec4 SpaceEnvPositions3[];
extern IndexedQuad SpaceEnvQuads0[];
extern IndexedQuad SpaceEnvQuads1[];
extern IndexedQuad SpaceEnvQuads2[];
extern IndexedQuad SpaceEnvQuads3[];
extern Vec4 SpaceEnvTransformedPositions[];
extern float SpaceEnvUVs[][2];
extern float SpaceEnvSavedUVs[][2];
extern int SpaceEnvRefresh;
extern int SpaceEnvWasActive;
extern int SpaceEnvTimer;
extern int SpaceTransitionSequenceFrames[3];
extern int SpaceVariantEffectQuadCounts[3];
extern float SpaceWarpTrailWidths[3];
extern int SpaceEnvColors[4];
extern int SpaceEnvVertexCounts[4];
extern int SpaceEnvQuadCounts[4];
extern Vec4 *SpaceEnvNormals[4];
extern Vec4 *SpaceEnvPositions[4];
extern IndexedQuad *SpaceEnvQuads[4];

struct DirectionalLight;
extern Vec4 SpaceQuadBase;
extern Vec4 SpaceQuadOffset;
extern Vec4 SpaceQuadStep;
extern unsigned long long SpacePlanetTex0;
extern unsigned long long SpacePlanetTextTex0;
extern DirectionalLight SpaceDefaultDirectionalLight;
// Scene workspaces reset before streaming a new cutscene.
extern unsigned char SceneScratchA[];
extern unsigned char SceneScratchB[];

extern const char SpaceUnloadBankFormat[];

void UpdateSpace(void);
void space_DefaultDraw(void);
void SpaceTransition_LoadWad(void);
void LoadSpacePlate(int language, int firstImage, int lastImage, unsigned long long *sharedTexture,
                    unsigned long long *firstTexture, unsigned long long *lastTexture);
void SpacePlate_DrawQuad(int screenX, int screenY, int width, int height, unsigned long long color,
                         unsigned long long texture, float minU, float maxU, float minV, float maxV);
void PlaySpacePlate(int language, int firstImage, int lastImage, int frames, int wait);
void DisplayLoadingScreen(int screen);
void DoSpaceTransition(void);

#endif
