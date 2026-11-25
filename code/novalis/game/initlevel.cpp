#include "common.h"
#include "initlevel.h"
#include "draw.h"
#include "fastfunc.h"
#include "framebuf.h"
#include "hero.h"
#include "memcard.h"
#include "mobyutil.h"
#include "music.h"
#include "vendor.h"
#include "vuchain.h"

#define COLL_JOINT_CACHE_EMPTY 0x87654321

// Game time added for each level load.
#define LEVEL_LOAD_ELAPSED_TIME 180

void InitLevel(void)
{
    music_RegisterBankCB();
    VU1_setBufSizeByLevel();
    InitMemSlots();

    GSloc = GSmemBase;
    GSbase = GSmemBase;

    FastMemSet(CollJointCacheKeys, COLL_JOINT_CACHE_EMPTY, COLL_JOINT_CACHE_KEYS_SIZE);
    FastMemSet(MobyClassLookup, -1, sizeof(MobyClassLookup));
    FastMemSet(MobyTexLookup, -1, sizeof(MobyTexLookup));
    FastMemSet(MobyMipDists, 0, sizeof(MobyMipDists));
    FastMemSet(TieClassLookup, -1, sizeof(TieClassLookup));
    FastMemSet(TieTexLookup, -1, sizeof(TieTexLookup));
    FastMemSet(TieMipDists, 0, sizeof(TieMipDists));
    FastMemSet(ShrubClassLookup, -1, sizeof(ShrubClassLookup));
    FastMemSet(ShrubTexLookup, -1, sizeof(ShrubTexLookup));
    FastMemSet(ShrubMipDists, 0, sizeof(ShrubMipDists));

    InitViewContext();
    UpdateViewContext();
    VU1_initChain();
    ResetParticles();
    DMAC_VIF1_Enable();

    UnlockPurchasableItems();
    if (Level != 0) {
        MB_UnlockLevel(Level);
    }

    ElapsedTime += LEVEL_LOAD_ELAPSED_TIME;
}

void UnlockPurchasableItems(void)
{
    int index;
    int item;
    int level;

    // Levels past the last story level start with every item.
    if (Level >= LEVEL_COUNT) {
        int itemId;

        for (itemId = 0; itemId < ITEM_COUNT; itemId++) {
            UnlockableItems[itemId] = 1;
            ObtainedItems[itemId] = 1;
        }

        PurchasableVendorItems[0] = VENDOR_ITEM_AMMO | ITEM_BOMB_GLOVE;
        PurchasableVendorItems[1] = VENDOR_ITEM_AMMO | ITEM_PYROCITOR;
        PurchasableVendorItems[2] = VENDOR_ITEM_AMMO | ITEM_BLASTER;
        PurchasableVendorItems[3] = VENDOR_ITEM_AMMO | ITEM_GLOVE_OF_DOOM;
        PurchasableVendorItems[4] = VENDOR_ITEM_AMMO | ITEM_MINE_GLOVE;
        PurchasableVendorItems[5] = VENDOR_ITEM_AMMO | ITEM_TAUNTER;
        PurchasableVendorItems[6] = VENDOR_ITEM_AMMO | ITEM_DEVASTATOR;
        PurchasableVendorItems[7] = VENDOR_ITEM_AMMO | ITEM_WALLOPER;
        PurchasableVendorItems[8] = VENDOR_ITEM_AMMO | ITEM_VISIBOMB_GUN;
        PurchasableVendorItems[9] = VENDOR_ITEM_AMMO | ITEM_DECOY_GLOVE;
        PurchasableVendorItems[10] = VENDOR_ITEM_AMMO | ITEM_DRONE_DEVICE;
        PurchasableVendorItems[11] = VENDOR_ITEM_AMMO | ITEM_TESLA_CLAW;

        QuickSelectItems[0] = ITEM_BLASTER;
        QuickSelectItems[1] = ITEM_SWINGSHOT;
        QuickSelectItems[2] = ITEM_VISIBOMB_GUN;
        QuickSelectItems[3] = ITEM_DEVASTATOR;
        QuickSelectItems[4] = ITEM_MINE_GLOVE;
        QuickSelectItems[5] = ITEM_BOMB_GLOVE;
        QuickSelectItems[6] = ITEM_PYROCITOR;
        QuickSelectItems[7] = ITEM_TESLA_CLAW;
        return;
    }

    // The bomb glove is always owned once a level is reached.
    if (!UnlockableItems[ITEM_BOMB_GLOVE]) {
        MB_UnlockItem(ITEM_BOMB_GLOVE, 1);
        PurchasableVendorItems[0] = VENDOR_ITEM_AMMO | ITEM_BOMB_GLOVE;
        EquippedItems[0] = ITEM_BOMB_GLOVE;
    }

    // Drop vendor entries no level has unlocked yet.
    for (index = 0; index < VENDOR_ITEM_COUNT; index++) {
        if (PurchasableVendorItems[index] == VENDOR_ITEM_NONE) {
            continue;
        }

        item = PurchasableVendorItems[index] & VENDOR_ITEM_ID_MASK;
        if (item == ITEM_BOMB_GLOVE) {
            continue;
        }

        for (level = 0; level < LEVEL_COUNT && LevelVendorItems[level] != item; level++) {
        }

        if (level == LEVEL_COUNT || item == 0) {
            PurchasableVendorItems[index] = VENDOR_ITEM_NONE;
        }
    }

    AddToUnlockedList(Level);
}

void AddToUnlockedList(int level)
{
    int item;
    int index;

    item = LevelVendorItems[level];
    if (item == 0) {
        return;
    }

    for (index = 0; (PurchasableVendorItems[index] & VENDOR_ITEM_ID_MASK) != item && PurchasableVendorItems[index] != VENDOR_ITEM_NONE; index++) {
    }

    if (PurchasableVendorItems[index] == VENDOR_ITEM_NONE) {
        PurchasableVendorItems[index] = item;
    }
}

TEXT_PADDING(0x27BD0090, 0x00000000);
