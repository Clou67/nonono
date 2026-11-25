#ifndef WAD_H
#define WAD_H

// Where a file lives on the disc: start sector and length in sectors.
struct WadEntry {
    int offset;
    int length;
};

// Disc sectors of one npc scene's chunks; chunk i spans [i, i + 1). Where the
// PAL table starts is known, the split of the rest of the 0x250 bytes is a guess.
struct NpcSceneSectors {
    int chunkSectors[71];       // 0x000
    int palChunkSectors[77];    // 0x11C
};

// The boot WAD's table of contents (DL g_wad.misc); only the entries known so far.
struct BootAssets {
    int unk_0[2];
    WadEntry debugFont;
    WadEntry savegame;
    char unk_18[0x4F8 - 0x18];
    WadEntry frontbin;              // 0x4F8 (Wrench RacWadInfo.frontbin)
    char unk_500[0x12E8 - 0x500];
    WadEntry spaceScenes[10];       // 0x12E8
    WadEntry palSpaceScenes[10];    // 0x1338
    char unk_1388[0x1530 - 0x1388];
    WadEntry weaponScenes[14];      // 0x1530
    WadEntry palWeaponScenes[14];   // 0x15A0
    char unk_1610[0x2AFC - 0x1610];
    NpcSceneSectors scenes[1];  // 0x2AFC; count unknown
};

extern BootAssets bootAssets;

#endif
