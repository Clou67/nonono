#ifndef GALAXYMAP_H
#define GALAXYMAP_H

// Places the two buffers a save is read into at the end of the VU1 chain memory; fails if the save is too big.
int GetSaveBuffers(unsigned int size, void **first, void **second);

// Level select map. DrawGalaxyMap draws the planet map of the level select screen.
struct LevelMapMarker {
    int x;
    int y;
    int labelOffsetX;
    int labelOffsetY;
};

struct LevelSelectText {
    int descriptionText;
    int labelText;
    int unk8;
};

extern LevelSelectText LevelSelectTexts[];
extern LevelMapMarker LevelMapMarkers[];
extern unsigned char g_SeenPlanets[];
extern int GalacticMap[];

extern int MediumFontHeight;
void DrawGalaxyMap(int left, int right, int top, int bottom);

#endif
