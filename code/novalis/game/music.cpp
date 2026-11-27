#include "common.h"
#include "vuchain.h"
#include "music.h"

// Device prefix for music files on the disc; nothing in the overlay reads it.
char MusicCdromDevice[] = "cdrom0:";

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/music", music_Init);

void snd_StreamSafeCdCallback(void (*callback)(int reason));
void music_LoadBankCB(int reason);

void music_RegisterBankCB(void)
{
    snd_StreamSafeCdCallback(music_LoadBankCB);
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/music", music_StartSpeech_Helpgirl);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/music", music_StartSpeech_Qwark);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/music", music_StartSpeech_Space);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/music", music_StartSpeech_Help);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/music", music_StartSpeech_Bindata);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/music", music_StartSpeech_Vendor);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/music", music_StartSpeech);

enum { MUSIC_STATE_PLAYING = 4 };

void snd_ContinueVAGStream(unsigned int handle);

int music_PlayPreseekedSpeech(void)
{
    if (musicTransition.speechHandle && musicTransition.state == MUSIC_STATE_READY) {
        snd_ContinueVAGStream(musicTransition.speechHandle);
        musicTransition.state = MUSIC_STATE_PLAYING;
        return 1;
    }

    return 0;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/music", music_PreseekTrack);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/music", music_StartTrack);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/music", music_StartTrackBody);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/music", music_Transition);

void music_SetTransition(int track, int transition)
{
    if (musicTransition.primary_track == track && musicTransition.requested_track == -1)
        return;

    if (!musicTransition.primary_bank && !musicTransition.transition_bank)
        musicTransition.primary_track = track;

    else {
        musicTransition.requested_track = track;
        musicTransition.requested_transition = transition;
    }
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/music", music_Stop);

enum { MUSIC_COMMAND_PAUSE = -0x8000 };

void music_Pause(int speech)
{
    if (speech) {
        musicTransition.secondary_command = MUSIC_COMMAND_PAUSE;
        musicTransition.secondary_unpause = 0;
    }

    musicTransition.primary_command = MUSIC_COMMAND_PAUSE;
    musicTransition.primary_unpause = 0;
    musicTransition.transition_command = MUSIC_COMMAND_PAUSE;
    musicTransition.transition_unpause = 0;
}

enum { MUSIC_COMMAND_RESUME = 4 };

void music_Unpause(void)
{
    musicTransition.primary_command = MUSIC_COMMAND_RESUME;
    musicTransition.transition_command = MUSIC_COMMAND_RESUME;
    musicTransition.secondary_command = MUSIC_COMMAND_RESUME;
}

enum { MUSIC_PAUSED_FLAG = 0x8000 };

void music_UnpauseDelay(int time)
{
    if (musicTransition.primary_command & MUSIC_PAUSED_FLAG)
        musicTransition.primary_unpause = time;
    if (musicTransition.transition_command & MUSIC_PAUSED_FLAG)
        musicTransition.transition_unpause = time;
    if (musicTransition.secondary_command & MUSIC_PAUSED_FLAG)
        musicTransition.secondary_unpause = time;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/music", music_UpdateStream);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/music", music_Update);

int snd_StreamSafeCdBreak(void);

void music_StopLoad(void)
{
    if (musicTransition.read_state != 0) {
        snd_StreamSafeCdBreak();
        musicTransition.cancel_read = 1;
    }
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/music", music_LoadBankFromEE);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/music", music_LoadFile);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/music", music_LoadFileSync);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/music", music_Sync);

int snd_StreamSafeCdGetError(void);
enum { MUSIC_READ_COMPLETE = 1, MUSIC_READ_IDLE = 0, MUSIC_READ_FAILED = 2 };

void music_LoadBankCB(int reason)
{
    if (reason == MUSIC_READ_COMPLETE) {
        musicTransition.read_state = MUSIC_READ_IDLE;
        if (snd_StreamSafeCdGetError() != 0)
            musicTransition.read_state = MUSIC_READ_FAILED;
    }
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/music", func_0027AD88);

void music_StartSpeech(int track, int flags, int volume);

void music_SpeechPreseekCB(unsigned int result, unsigned long long data)
{
    MusicPlaying *playing = (MusicPlaying *)(int)data;
    if (playing) {
        playing->handle = result;
        if (result) {
            if (playing->status == MUSIC_PRESEEK_PENDING)
                playing->status = MUSIC_PRESEEK_COMPLETE;
        }

        else
            music_StartSpeech(musicTransition.speechId, musicTransition.speechFlags, musicTransition.speechVolume);
    }
}

void music_PreseekTrack(int track, int flags, int volume);

void music_PreseekTrackCB(unsigned int result, unsigned long long data)
{
    MusicPlaying *playing = (MusicPlaying *)(int)data;
    if (playing) {
        playing->handle = result;
        if (result) {
            if (playing->status == MUSIC_PRESEEK_PENDING)
                playing->status = MUSIC_PRESEEK_COMPLETE;
        }

        else
            music_PreseekTrack(musicTransition.primary_track, musicTransition.primaryFlags, musicTransition.primaryVolume);
    }
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/music", func_0027AE78);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/music", func_0027AEC8);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/music", func_0027AF20);

static const unsigned int MUSIC_STOP_PENDING = 0xFFFFFFFF;
enum { MUSIC_STOP_COMPLETE = 7 };

void music_StopCB(unsigned int result, unsigned long long data)
{
    MusicPlaying *playing = (MusicPlaying *)(int)data;
    if (playing) {
        if (playing->handle != MUSIC_STOP_PENDING)
            printf_stub("wtf\n");

        else {
            playing->handle = result;
            if (!result)
                playing->status = MUSIC_STOP_COMPLETE;
        }
    }
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/music", func_0027AFB8);
