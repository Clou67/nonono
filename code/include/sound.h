#ifndef SOUND_H
#define SOUND_H

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

struct SoundData {
    char unk_00[8];
    SoundDef *pSoundDef;
};

struct MobyInstance;

struct SoundVoice {
    unsigned char unk_00[0x0E];
    short soundId;
    int volume;
    int pitch_bend;
    MobyInstance *pMoby;
    unsigned char unk_1C[0x54];
};

struct SoundAudioState {
    unsigned char unk_00[0x48];
    int group_volume[6];
    int reverb_owner;
    int reverb_depth;
    unsigned char reverb_type;
    unsigned char reverb_delay;
    unsigned char reverb_feedback;
    unsigned char reverb_commands;
    int pending_commands;
    SoundVoice voices[30];
};

extern SoundAudioState audioState;
char sound_Update(void);
int sound_LevelPlay(int entry, int flags, int owner);

int sound_SetVol(int handle, int volume);

int sound_SetPitch(int handle, int pitch);

void sound_SetReverb(int owner, int type, int depth, int delay, int feedback);

int sound_GetFadeChannel(SoundData *channel, Vec4 *position);

void sound_KillChannel(int handle);
int sound_PlayMobySound(int sound, int flags, MobyInstance *moby);
#endif
