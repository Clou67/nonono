#ifndef NPC_H
#define NPC_H

#include "moby.h"

// One entry of a moby's hint list: the help text and scene it plays, and the entry
// that follows depending on a condition.
struct InfobotHintEntry {
    int message;
    // -1 for none; INFOBOT_HINT_MOVIE marks an infobot movie instead of a scene.
    short scene;
    short next;
    short condition;
    short conditionValue;
    short entryIfMet;
    short entryOtherwise;
    unsigned short flags;
    char unk12[0xA];
};

#define INFOBOT_HINT_MOVIE 0x4000

// InfobotHintEntry flags.
#define INFOBOT_HINT_ANY_DIRECTION 0x1
#define INFOBOT_HINT_AUTO_PLAY 0x4
#define INFOBOT_HINT_HAS_COST 0x8

// Conditions an entry can test.
enum infobot_hint_condition {
    INFOBOT_HINT_ALWAYS,
    INFOBOT_HINT_ENOUGH_BOLTS,
    INFOBOT_HINT_HAS_ITEM,
    INFOBOT_HINT_ITEM_NOT_OBTAINED,
    INFOBOT_HINT_ITEM_FLAG,
    INFOBOT_HINT_ENOUGH_GOLD_BOLTS,
    INFOBOT_HINT_PRICE
};

// Hint state kept by a moby.
struct InfobotHint {
    char unk0[4];
    short previousEntry;
    char unk6[2];
    // Copy of the entry's INFOBOT_HINT_ANY_DIRECTION flag; INFOBOT_HINT_DISABLED turns the hint off.
    unsigned char anyDirection;
    unsigned char initialized;
    char unkA[2];
    float radius;
    char unk10[0x26];
    short entry;
    int startTime;
    InfobotHintEntry *entries;
};

#define INFOBOT_HINT_DISABLED 0xFF

// The hint that was triggered last.
struct ActiveInfobotHint {
    char unk0[8];
    MobyInstance *moby;
    InfobotHint *hint;
    int nextTime;
    int message;
};

// Price table entry.
struct VendorPrice {
    int bolts;
    char unk4[0xA];
    unsigned short maxAmmo;
    char unk10[4];
    unsigned short goldBoltPrice;
    char unk16[2];
};

// Per-object state of the level's mobys (core).
struct LevelObjectState {
    char unk0[0xC];
    int state;
};

extern ActiveInfobotHint ActiveHint;
extern LevelObjectState LevelObjectStates[];
extern unsigned char ItemFlags[];
extern VendorPrice VendorPrices[];
// Per level, the first index into LevelObjectMobys.
extern int LevelObjectStart[];
extern MobyInstance *LevelObjectMobys[];
extern InfobotHintEntry *InfobotHintLists[];
extern int BoltHudHandle;

int InfobotHint_Update(MobyInstance *moby, InfobotHint *hint);
int InfobotHint_FindEntry(MobyInstance *moby);
void InfobotHint_SetEntryState(MobyInstance *moby, int state);
int InfobotHint_InitInstance(MobyInstance *moby, InfobotHint *hint);
void InfobotHint_SetState(MobyInstance *moby, InfobotHint *hint, int activate);

void PlayInfobotMovie(int movie);
void mode_movieUnInit(int scene);
int MB_GetUnspentGoldBolts(void);

#endif
