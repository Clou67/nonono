#ifndef SOUND_H
#define SOUND_H

#include "moby.h"

void sound_LoadBankCB(unsigned int bank, unsigned long userData);

void snd_PauseAllSoundsInGroup(int group);
void snd_ContinueAllSoundsInGroup(int group);
int snd_FlushSoundCommands(void);
void snd_StopAllSounds(void);
void snd_UnloadBank(int bank);
void snd_ResolveBankXREFS(void);
typedef void (*SndCompleteProc)(unsigned int result, unsigned long userData);
void snd_BankLoadFromEE_CB(void *eeLocation, SndCompleteProc callback, unsigned long userData);
void snd_SetMasterVolume(int group, int volume);

// Sound system state (only the fields known so far).
struct SoundDef {
    float minRange;
    float maxRange;
    int minVolume;
    int maxVolume;
    int minPitch;
    int maxPitch;
    char loop;
    unsigned char flags;
    short index;
    int bank_index;
};

struct Vec4;

struct SoundVoice {
    unsigned int handle; // 0x00
    unsigned char status;
    unsigned char flags;
    unsigned char unk_06[2];
    SoundDef *pSoundDef;
    unsigned short soundIndex;
    short soundId;
    int volume; // 0x10
    int pitch_bend;
    MobyInstance *pMoby;
    int ownerContext;
    Vec4 pos; // 0x20
    Vec4 offset;
    unsigned int occlpos; // 0x40
    unsigned char occl[36];
    unsigned char unk_68[8];
};

// An ambient sound placed in the level (PS3 names).
struct SoundInstance {
    short oClass;
    short mClass;
    void *pUpdate;
    // An index into the gameplay file's pVar table until the level is loaded.
    int pVar;
    char unk_0C[0x84];
};

struct SoundAudioState {
    Vec4 cam_history[4]; // 0x00
    int cam_history_pos;
    int load_busy;
    int group_volume[6]; // 0x48
    int reverb_owner;
    int reverb_depth;
    unsigned char reverb_type;
    unsigned char reverb_delay;
    unsigned char reverb_feedback;
    unsigned char reverb_commands;
    int pending_commands;
    SoundVoice voices[30]; // 0x70
    int soundInstanceCnt; // 0xD90
    SoundInstance *soundInstances;
    int occlFrame;
    int unk_D9C;
    Vec4 occlSamples[6]; // 0xDA0
};

// Retail indexes from the pool base and accesses a voice one stride later.
// This is an overlapping access window, not an array of headers or a second pool layout.
struct SoundVoiceWindow {
    unsigned char preceding[sizeof(SoundVoice)];
    SoundVoice voice;
};

extern SoundAudioState audioState;
char sound_Update(void);
void sound_SetupAmbientFunctions(SoundInstance *sound);
int sound_LevelPlay(int entry, int flags, int owner);

int sound_SetVol(int handle, int volume);

int sound_SetPitch(int handle, int pitch);

void sound_SetReverb(int owner, int type, int depth, int delay, int feedback);

int sound_GetFadeChannel(SoundVoice *channel, Vec4 *position);

void sound_KillChannel(int handle);
int sound_PlayMobySound(int sound, int flags, MobyInstance *moby);
extern SoundDef *LevelSounds;
extern unsigned int levelSoundBank;

void snd_SetReverbEx(int cores, int type, int depth, int delay, int feedback);
void snd_ResetStateAndFlushCommands(void);
void snd_StreamSafeCdCallback(void (*callback)(int reason));
int snd_StreamSafeCdSync(int wait);
void sound_StopAllSounds(void);

#endif
