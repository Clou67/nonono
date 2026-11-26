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
void PlaySpacePlate(int language, int firstImage, int lastImage, int frames, int wait);
void DisplayLoadingScreen(int screen);
void DoSpaceTransition(void);

#endif
