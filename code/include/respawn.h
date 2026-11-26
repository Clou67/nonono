#ifndef RESPAWN_H
#define RESPAWN_H

struct MobyVarEntry {
    int offset;
    unsigned char data[4];
    unsigned short size;
    short isMoby;
    short uid;
    short oClass;
};

struct MobyVarList {
    int count;
    MobyVarEntry entries[64];
};

struct Vec4;
void ClearCheckpointData(void);
void RestoreCheckpoint(void);
void SetSpawnPoint(Vec4 *position, Vec4 *rotation);

struct MobyInstance;
MobyInstance *FindMobyByUID(int unused, int uid);

void RestoreMobyVarList(MobyVarList *vars);
void RestoreSavedMobyVars(void);

void SaveCheckpointMobyVar(void *data, int size, MobyInstance *moby, int isMoby, MobyVarList *list);

struct BoltSourceStats {
    short uid;
    short bolts;
};
extern BoltSourceStats BoltSources[][64];

int FindOrAssignBoltSourceSlot(int level, int uid);

// One bit per moby uid: set at the checkpoint, and per level for every checkpoint reached.
extern int CheckpointBits[64];
extern int LevelCheckpointBits[][64];

#endif
