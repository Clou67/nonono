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
