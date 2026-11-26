#include "common.h"
#include "fastfunc.h"
#include "hero.h"
#include "mathfunc_inline.h"
#include "music.h"
#include "sound.h"
#include "respawn.h"

int FindOrAssignBoltSourceSlot(int level, int uid)
{
    int index = -1;

    if (uid >= 0) {
        uid++;
        index = 63;
        while (index >= 0 && BoltSources[level][index].uid != uid &&
               BoltSources[level][index].uid != 0) {
            index--;
        }

        if (index >= 0)
            BoltSources[level][index].uid = uid;
    }

    return index;
}

struct CheckpointData {
    int set;
    unsigned char padding[12];
    Vec4 position;
    Vec4 rotation;
    unsigned int color;
    unsigned int light;
    int colorManipulator;
    int reverbDepth;
    unsigned char reverbType;
    unsigned char reverbDelay;
    unsigned char reverbFeedback;
    unsigned char unk_43;
    int heroType;
    MobyInstance *hero;
    int heroState;
    MobyVarList vars;
    unsigned char objectState[0x800];
    int musicTrack;
    unsigned char trailingPadding[8];
};

extern CheckpointData LiveCheckpoint;
extern CheckpointData CheckpointSet;
extern unsigned char occlCharTable[][16];
extern MobyVarList LiveMobyVars;
extern MobyVarList SavedMobyVars;
extern int Level;

void ClearCheckpointData(void)
{
    FastMemSet(&LiveCheckpoint, 0, sizeof(LiveCheckpoint));
    FastMemSet(&CheckpointSet, 0, sizeof(CheckpointSet));
    FastMemSet(CheckpointBits, 0, sizeof(CheckpointBits));
}

void SetSpawnPoint(Vec4 *position, Vec4 *rotation)
{
    MobyVarList *savedVars = &SavedMobyVars;
    MobyVarList *liveVars = &LiveMobyVars;
    FastMemCopy32(savedVars, liveVars, sizeof(MobyVarList));

    int level = Level;
    unsigned char *source = (unsigned char *)(liveVars + 1);
    unsigned char *destination = (unsigned char *)(savedVars + 1);

    for (int index = 0; index < 0x7FF; index++, source++) {
        int state = *source;
        unsigned char objectState = state;
        if (objectState != 0 && (objectState == 1 || occlCharTable[level][objectState - 2] == 0xFF)) {
            unsigned int mask = 1 << (index & 31);
            *((unsigned char *)(index + (unsigned int)destination)) = state;
            LevelCheckpointBits[level][index >> 5] |= mask;
            CheckpointBits[index >> 5] |= mask;
        }
    }

    CheckpointSet.set = 1;
    CopyVec4Inline(&CheckpointSet.position, position);
    CopyVec4Inline(&CheckpointSet.rotation, rotation);

    MobyInstance *moby = Hero.moby;
    CheckpointSet.color = moby->color;
    CheckpointSet.light = moby->light;
    CheckpointSet.colorManipulator = moby->colorManipulator;
    CheckpointSet.heroType = Hero.type;
    CheckpointSet.hero = moby;
    CheckpointSet.heroState = Hero.requestedState;
    CheckpointSet.reverbDepth = audioState.reverb_depth;
    CheckpointSet.reverbType = audioState.reverb_type;
    CheckpointSet.reverbDelay = audioState.reverb_delay;
    CheckpointSet.reverbFeedback = audioState.reverb_feedback;

    if (musicTransition.requested_track != -1)
        CheckpointSet.musicTrack = musicTransition.requested_track;
    else
        CheckpointSet.musicTrack = musicTransition.primary_track;
}

extern MobyInstance *MobyInstances;
extern MobyInstance *MobyInstancePermEnd;
void PostUpdateMoby(MobyInstance *moby);
void SetHeroType(int type, int state, MobyInstance *moby);
void FastEulerToMtx(Mtx4 *transform, Vec4 *rotation);
void Camera_resetToFollow(void);

void RestoreCheckpoint(void)
{
    if (!CheckpointSet.set) {
        FastMemSet(&LiveCheckpoint, 0, sizeof(CheckpointData));
        return;
    }

    FastMemCopy32(&LiveCheckpoint, &CheckpointSet, sizeof(CheckpointData));

    CopyVec4Inline(&Hero.position, &CheckpointSet.position);
    CopyVec4Inline(&Hero.rotation, &CheckpointSet.rotation);

    Hero.moby->color = CheckpointSet.color;
    Hero.moby->light = CheckpointSet.light;
    Hero.moby->colorManipulator = CheckpointSet.colorManipulator;

    audioState.reverb_depth = CheckpointSet.reverbDepth;
    audioState.reverb_type = CheckpointSet.reverbType;
    audioState.reverb_delay = CheckpointSet.reverbDelay;
    audioState.reverb_feedback = CheckpointSet.reverbFeedback;
    audioState.reverb_commands |= 7;
    musicTransition.primary_track = CheckpointSet.musicTrack;
    int type = CheckpointSet.heroType;

    if (type != 0 && type != 3) {
        int oClass = 0;
        switch (type) {
        case 1:
            oClass = 0x57;
            break;
        case 2:
            oClass = 0x1A3;
            break;
        default:
            FastTrap();
            break;
        }

        for (int index = 0; &MobyInstances[index] < MobyInstancePermEnd; index++) {
            MobyInstance *moby = &MobyInstances[index];
            if ((short)moby->oClass == oClass) {
                SetHeroType(CheckpointSet.heroType, CheckpointSet.heroState, moby);
                break;
            }
        }
    }

    PostUpdateMoby(Hero.moby);
    FastEulerToMtx(&Hero.moby->transform, &Hero.rotation);
    Camera_resetToFollow();
    RestoreSavedMobyVars();
}


MobyInstance *FindMobyByUID(int unused, int uid)
{
    for (MobyInstance *moby = MobyInstances; moby != MobyInstancePermEnd; moby++) {
        if ((short)moby->uid == uid)
            return moby;
    }

    return 0;
}

void RestoreMobyVarList(MobyVarList *list)
{
    for (int index = 0; index < list->count; index++) {
        MobyVarEntry *entry = &list->entries[index];
        MobyInstance *moby = FindMobyByUID(entry->oClass, entry->uid);
        if (moby != 0) {
            unsigned char *destination;
            if (entry->isMoby == 1)
                destination = (unsigned char *)(entry->offset + (int)moby);
            else
                destination = (unsigned char *)(entry->offset + (int)moby->pVar);
            FastMemCopy32(destination, entry->data, entry->size);
        }
    }
}

void RestoreSavedMobyVars(void)
{
    RestoreMobyVarList(&SavedMobyVars);
}

void SaveCheckpointMobyVar(void *data, int size, MobyInstance *moby, int isMoby, MobyVarList *list)
{
    short uid = moby->uid;
    short oClass = moby->oClass;
    int offset = (short)(isMoby == 1
                       ? (unsigned int)data - (unsigned int)moby
                       : (unsigned int)data - (unsigned short)(unsigned int)moby->pVar);

    for (int index = 0; index < list->count; index++) {
        MobyVarEntry *entry = &list->entries[index];
        if (entry->offset == offset && entry->size == size && uid == entry->uid && oClass == entry->oClass) {
            // A matching entry can change where a newly appended value will be restored.
            isMoby = entry->isMoby;
            if (isMoby != 0) {
                FastMemCopy32(entry->data, data, size);
                return;
            }
        }
    }

    MobyVarEntry *entry = &list->entries[list->count++];
    entry->offset = offset;
    FastMemCopy32(entry->data, data, size);
    entry->size = size;
    entry->isMoby = isMoby;
    entry->uid = uid;
    entry->oClass = oClass;
}
