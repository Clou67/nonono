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

// The disc table of contents (DL g_wad.misc; Wrench RacWadInfo, whose offsets match);
// only the entries known so far.
struct BootAssets {
    int version;                    // 0x0000
    int headerSize;                 // 0x0004
    WadEntry debugFont;             // 0x0008
    WadEntry savegame;              // 0x0010
    char unk_18[0x4F8 - 0x18];
    WadEntry frontbin;              // 0x04F8
    char unk_500[0x12C8 - 0x500];
    WadEntry spaceships[4];         // 0x12C8
    WadEntry spaceScenes[10];       // 0x12E8 (Wrench anim_looking_thing_2[20]: NTSC then PAL)
    WadEntry palSpaceScenes[10];    // 0x1338
    WadEntry spacePlates[6];        // 0x1388
    WadEntry transition;            // 0x13B8
    char unk_13C0[0x14F8 - 0x13C0];
    WadEntry hudHeader;             // 0x14F8
    WadEntry hudBanks[5];           // 0x1500
    WadEntry allText;               // 0x1528
    WadEntry weaponScenes[14];      // 0x1530 (Wrench things[28]: NTSC then PAL)
    WadEntry palWeaponScenes[14];   // 0x15A0
    char unk_1610[0x2968 - 0x1610];
    WadEntry soundBank;             // 0x2968 IOP sound bank archive
    WadEntry gameplayNtsc;          // 0x2970
    WadEntry gameplayPal;           // 0x2978
    char unk_2980[0x2AFC - 0x2980];
    NpcSceneSectors scenes[1];  // 0x2AFC; count unknown
};

extern BootAssets bootAssets;

#endif
