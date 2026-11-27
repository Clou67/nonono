#ifndef MUSIC_H
#define MUSIC_H

enum { MUSIC_PRESEEK_PENDING = 1, MUSIC_PRESEEK_COMPLETE = 2 };

struct MusicPlaying {
    unsigned int handle;
    char unk_04[6];
    short status;
};

struct MusicTransition {
    char unk0[8];
    short read_state;
    unsigned char cancel_read;
    unsigned char updatesSuspended;
    char unk0C[0x10];
    int queuedSpeech;
    char unk20[2];
    signed char requested_track;
    signed char requested_transition;
    char unk24[0x14];
    short primary_track;
    short primaryVolume;
    short primaryFlags;
    short primary_bank;
    short primary_command;
    short primary_unpause;
    char unk44[0xC];
    unsigned int speechHandle;
    short speechId;
    short speechVolume;
    short speechFlags;
    short state;
    short secondary_command;
    short secondary_unpause;
    char unk60[0x16];
    short transition_bank;
    short transition_command;
    short transition_unpause;
};

// Speech ids are offset by this much from the ids stored in the help messages.
#define MUSIC_SPEECH_ID_BASE 30000

// Values of MusicTransition::state seen so far; 6 and 7 are the finishing states.
#define MUSIC_STATE_READY 3
#define MUSIC_STATE_STOPPING 5
#define MUSIC_STATE_FINISHING 6

extern MusicTransition musicTransition;

int music_LoadBankFromEE(void *buffer, int sector, int sectorCount);

void music_Sync(int wait);
void music_Pause(int includeSpeech);
void music_Unpause(void);
void music_RegisterBankCB(void);
int music_PlayPreseekedSpeech(void);
// Nonzero while a music_LoadFile read is still streaming in.
extern short CdReadActive[];

void music_LoadFile(void *destination, int sector, int length);
int music_LoadFileSync(void *destination, int sector, int length);

void music_UnpauseDelay(int frames);

void music_LoadBankCB(int reason);

void music_StopLoad(void);

void music_SetTransition(int track, int transition);

void music_PreseekTrackCB(unsigned int result, unsigned long long data);

void music_SpeechPreseekCB(unsigned int result, unsigned long long data);

void music_StopCB(unsigned int result, unsigned long long data);

void music_Stop(void);

#endif
