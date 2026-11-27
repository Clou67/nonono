#ifndef MUSIC_H
#define MUSIC_H

#include "sce.h"

enum { MUSIC_PRESEEK_PENDING = 1, MUSIC_PRESEEK_COMPLETE = 2 };

// RaC1 playback channel; DL's music_Playing later gained more fields.
struct MusicPlaying {
    unsigned int handle; // 0x00
    short track;
    short volume;
    short flags;
    short status; // 0x0A: playback state, not a bank number
    short pause;
    short unpause;
    short transition; // 0x10: remaining-time callback may start a crossfade
    short unk_12;
    int queuelen; // 0x14: remaining-time polling interval
    int remain;
};

// Resident music state at 0x1516D0, with three 0x1C-byte channel records.
struct MusicGlobals {
    int unk_00;
    int unk_04;
    short read_state; // 0x08
    unsigned char cancel_read;
    unsigned char updatesSuspended;
    int readSector;
    int readSectorCount;
    void *readDestination;
    int unk_18;
    int queuedSpeech;
    union {
        unsigned int transitionRequest; // Retail also tests these four state/request bytes together.
        struct {
            short crossfadeState;
            signed char requested_track;
            signed char requested_transition;
        };
    };
    int crossfadeRemainingTime; // 0x24
    int crossfadeInterval;
    int retryTimer;
    sceCdRMode cdReadMode; // 0x30
    MusicPlaying play; // 0x34
    MusicPlaying speech; // 0x50
    MusicPlaying trans; // 0x6C
};

// Speech ids are offset by this much from the ids stored in the help messages.
#define MUSIC_SPEECH_ID_BASE 30000
#define MUSIC_SCENE_SPEECH_BASE 40000

// Values of MusicGlobals::speech.status seen so far; 6 and 7 are the finishing states.
#define MUSIC_STATE_READY 3
#define MUSIC_STATE_STOPPING 5
#define MUSIC_STATE_FINISHING 6

extern MusicGlobals musicGlobals;

int music_LoadBankFromEE(void *buffer, int sector, int sectorCount);

void music_Sync(int wait);
void music_Pause(int speech);
void music_Unpause(void);
void music_RegisterBankCB(void);
int music_PlayPreseekedSpeech(void);
// Nonzero while a music_LoadFile read is still streaming in.
extern short CdReadActive[];

void music_LoadFile(void *destination, int sector, int length);
int music_LoadFileSync(void *destination, int sector, int length);

void music_UnpauseDelay(int time);

void music_LoadBankCB(int reason);

void music_StopLoad(void);

void music_SetTransition(int track, int transition);

void music_PreseekTrackCB(unsigned int result, unsigned long long data);

void music_SpeechPreseekCB(unsigned int result, unsigned long long data);

void music_StopCB(unsigned int result, unsigned long long data);

void music_Stop(void);

#endif
