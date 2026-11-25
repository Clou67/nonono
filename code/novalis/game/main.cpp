#include "common.h"
#include "draw.h"
#include "framebuf.h"
#include "gameglobals.h"
#include "hero.h"
#include "hud.h"
#include "memcard.h"
#include "music.h"
#include "pad.h"
#include "sce.h"
#include "vuchain.h"
#include "fastfunc.h"
#include "galaxymap.h"
#include "sound.h"

// How long a level has been visited and played, kept per level in the save.
struct LevelRecord {
    unsigned short visits;
    unsigned short playTime; // longest stay, in 10 second units
    unsigned int flags;
};

// Pause menu state; only the memory card icon switch is named so far.
struct PauseMenuState {
    char unk_000[0x13C];
    int hideActivityIcon;
};

// Debug switches set up for each level (DL's debug globals).
struct DebugSettings {
    char unk_00[0x8];
    int update;
    int selectedCol;
    char unk_10[0x8];
    int profile;
    char unk_1C[0x14];
    int tvMode;
    char unk_34[0x4];
    int scene;
    char unk_3C[0xB8];
    int actuator;
};

extern char StartLevelClearStart[];
extern char StartLevelClearEnd[];
extern LevelRecord LevelRecords[];
extern unsigned char g_MiscLevelFlags[] __attribute__((section(".data")));
extern PauseMenuState PauseMenu;
extern DebugSettings Debug;
extern int g_newlevel;
extern int FramesSinceStateChange;
extern float FrameLoad;
extern int FrameOverrun;
extern short g_SceneRecording;
extern unsigned long frm_clock_time;
extern int gsFrame;

extern "C" void snd_UnkFunction_0012eaf0(void);
extern "C" void snd_UnkFunction_0012eb00(void);

void Stash_InitOnce(void);
void InitLevel(void);
void InitLevelFromWad(int firstLoad, int reload);
void map_LoadPlanetMap(void);
void hud_InitBanks(void);
void LoadHudSeqs(void);
void space_StartLevelArrival(void);
void music_StartTrack(int track, int unpause, int volume);
void music_Unpause(void);
void music_Stop(void);
void ResetLevelCounters(void);
void VU1_sendChain(void);
void VU1_swapChain(void);
void VU1_initChain(void);
void UpdateDebugSelections(void);
void DrawDebugMenu(void);
void UpdateGameplay(void);
void SetupDefaultDraw(void);
void UpdateCinematic(void);
void UpdateInLevelMovie(void);
void UpdatePause(void);
void UpdateModeFreeze(void);
void SetupDefaultDrawFreeze(void);
void vendor_PreUpdate(void);
void vendor_PostUpdate(void);
void UpdateSpace(void);
void space_DefaultDraw(void);
void UpdateCredits(void);
void DrawFrameEnd(void);
void memcard_Update(void);
void UpdateMCState(void);
void DebugFontFlush(void);
void Respawn_IncCounter(void);
void ResetGsRegistersPr(void);
void sound_StopAllSounds(void);
void DoSpaceTransition(void);

// The level record keeps the longest stay; TotalPlayTime counts frames, the record 10 second units.
static inline void UpdateLevelPlayTime(LevelRecord *record)
{
    if (record->playTime < FastScaleRoundInt(TotalPlayTime) / 600) {
        record->playTime = FastScaleRoundInt(TotalPlayTime) / 600;
    }
}

// Loads the level and runs the main loop until another level is asked for.
void startLevel(void)
{
    int reloadLevel;
    int reloadMode;
    int mode;
    float angle;

    // Clear the per-level state: with FastMemSetZero when it is quadword aligned, else a byte at a time.
    if (((StartLevelClearEnd - StartLevelClearStart) & 15) == 0 && ((unsigned int)StartLevelClearStart & 15) == 0) {
        FastMemSetZero(StartLevelClearStart, StartLevelClearEnd - StartLevelClearStart);
    } else {
        printf_stub("crap\n");
        for (int i = 0; i < StartLevelClearEnd - StartLevelClearStart; i++) {
            StartLevelClearStart[i] = 0;
        }
    }
    Stash_InitOnce();
    FramesSinceStateChange = 0;
    gameMode = 6;
    InitLevel();
    musicTransition.primary_track = 0;
    InitLevelFromWad(1, 0);
    Debug.update = 0xF;
    Debug.tvMode = videoModePal;
    Debug.scene = -1;
    Debug.actuator = 1;
    Debug.selectedCol = 1;
    ResetDebugEnables();
    map_LoadPlanetMap();
    hud_InitBanks();
    LoadHudSeqs();
    space_StartLevelArrival();
    gsFrame = 0;
    sceGsSyncV(0);
    PutDispBuffer();

    music_StartTrack(musicTransition.primary_track, 1, 0x400);
    if ((Level == 1 && g_SeenPlanets[3] == 0) || (Level == 0 && g_MiscLevelFlags[0] != 0)) {
        music_Unpause();
    } else {
        music_Pause(0);
    }

    if (LevelVisited[Level] == 0) {
        LevelVisited[Level] = 1;
    }
    if (LevelRecords[Level].visits < 0xFFFF) {
        LevelRecords[Level].visits++;
    }
    UpdateLevelPlayTime(&LevelRecords[Level]);
    LevelRecords[Level].flags |= (1 << Level) | 0x80000000;
    snd_UnkFunction_0012eaf0();

    while (!g_newlevel) {
        reloadLevel = 0;
        reloadMode = 0;
        frm_clock_time += *T0_COUNT;
        *T0_COUNT = 0;
        ResetLevelCounters();
        CutscenePlaying = 0;
        VU1_sendChain();
        VU1_swapChain();
        PutDrawBufferSmall();
        {
            int opaque; // never set: retail passes whatever is in $a0
            AA_DisplayPass(opaque);
        }
        PutDrawBufferLarge();
        snd_FlushSoundCommands();

        mode = gameMode;
        switch (gameMode) {
        case -1:
            UpdatePad();
            UpdateDebugSelections();
            DrawDebugMenu();
            break;
        case 0:
            UpdatePad();
            UpdateGameplay();
            SetupDefaultDraw();
            break;
        case 1:
            UpdateCinematic();
            break;
        case 2:
            UpdatePad();
            UpdateInLevelMovie();
            {
                int black; // never set, as in retail
                SetupDefaultDrawMovie(black);
            }
            break;
        case 3:
            UpdatePad();
            UpdatePause();
            CallDrawOverlayIfNoCutscene();
            break;
        case 4:
            UpdatePad();
            UpdateModeFreeze();
            SetupDefaultDrawFreeze();
            break;
        case 5:
            UpdatePad();
            vendor_PreUpdate();
            vendor_PostUpdate();
            break;
        case 6:
            UpdatePad();
            UpdateSpace();
            space_DefaultDraw();
            break;
        case 7:
            UpdatePad();
            UpdateCredits();
            DrawFrameEnd();
            break;
        }
        if (gameMode == mode) {
            FramesSinceStateChange++;
        } else {
            FramesSinceStateChange = 0;
        }

        if (CutscenePlaying) {
            VU1_syncChain(1);
            VU1_initChain();
            continue;
        }

        memcard_Update();
        UpdateMCState();
        if ((g_memcard.stage >= 3 || g_memcard.nextstage >= 0) && !PauseMenu.hideActivityIcon) {
            FlipAndExploreTimersVU1(0);
            VU1_addGSregister(0x47, 0x3004B);
            Hud_DrawTexQuad(HudTex_GetFrame(0x755D, 0), 50, 300, 64, 64, 0x80);
            angle = (float)(gsFrame % 55) * -6.2831855f / (float)55;
            Hud_DrawRotatedSprite16(1312.0f, 5312.0f, 272.0f, 272.0f, angle, 64, 64,
                                    HudTex_Bind(HudTex_GetFrame(0x755D, 1)));
            FinalizeVU1FramePacketChain();
        }
        PauseMenu.hideActivityIcon = 0;

        DebugFontFlush();
        printf_stub2("system misc", 0x10);
        printf_stub3("system misc", 0x10);
        VU1_syncChain(1);
        FrameLoad = FastIntToFloat(*T0_COUNT) / (videoModePal ? 11520.0f : 9600.0f);
        if (gameMode == 0 && Debug.profile) {
            STUB_00218990();
        }

        if (!Hero.outOfBounds) {
            if (gameMode == 0 || gameMode == 2) {
                // The frame overran its budget: run one more update to catch up.
                if ((int)*T0_COUNT > (videoModePal ? 0x2D00 : 0x2580)) {
                    if (gameMode == 0) {
                        UpdatePad();
                        UpdateGameplay();
                    } else if (gameMode == 2 && !g_SceneRecording) {
                        UpdatePad();
                        UpdateInLevelMovie();
                    }
                }
                sceGsSyncV(0);
                gsFrame++;
                Respawn_IncCounter();
                FrameOverrun = 0;
            } else {
                sceGsSyncV(0);
                gsFrame++;
                Respawn_IncCounter();
                FrameOverrun = 0;
            }
        }
        ResetGsRegistersPr();

        // Fell out of the level: reload it in place.
        if (gameMode == 0 && Hero.outOfBounds) {
            reloadLevel = 1;
            reloadMode = 1;
        }
        if (reloadLevel) {
            VU1_initChain();
            snd_UnkFunction_0012eb00();
            snd_FlushSoundCommands();
            sound_StopAllSounds();
            music_Stop();
            InitLevelFromWad(0, reloadMode);
            gameMode = 0;
            music_StartTrack(musicTransition.primary_track, 1, 0x400);
            hud_InitBanks();
        }
        UpdateLevelPlayTime(&LevelRecords[Level]);
    }
    DoSpaceTransition();
}
