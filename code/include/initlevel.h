#ifndef INITLEVEL_H
#define INITLEVEL_H

#include "sce.h"

// Item each level adds to the vendor list when it is reached (0 for none).
extern int LevelVendorItems[];

// Per-level class tables: the index of each moby, tie and shrub class in the level's
// class list (-1 when the level has no such class), its texture lookup and its mip distances.
#define COLL_JOINT_CACHE_KEYS_SIZE 0x10
extern char CollJointCacheKeys[];
extern char MobyClassLookup[0x800];
extern char MobyTexLookup[0xE00];
extern unsigned int MobyMipDists[0xE0 / 4];
extern unsigned char TieClassLookup[0xC00];
extern u_long128 TieTexLookup[0x800 / 16];
extern int TieMipDists[0x80 / 4];
extern unsigned char ShrubClassLookup[0x400];
extern u_long128 ShrubTexLookup[0x400 / 16];
extern int ShrubMipDists[0x40 / 4];

extern int GSloc;
extern int GSbase;

struct GsTextureAllocation {
    int cursor;
    int start;
};

extern GsTextureAllocation gsTextureAllocation;

void ResetParticles(void);

void InitLevel(void);
void UnlockPurchasableItems(void);
void AddToUnlockedList(int level);

#endif
