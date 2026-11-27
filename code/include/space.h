#ifndef SPACE_H
#define SPACE_H

enum SpaceShipVariant {
    SPACE_SHIP_INITIAL = 0,
    SPACE_SHIP_BATALIA = 1,
    SPACE_SHIP_OLTANIS = 2
};

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
