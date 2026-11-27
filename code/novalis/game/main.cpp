#include "common.h"
#include "debug.h"
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
#include "pause.h"
#include "sound.h"


extern char bss_start[];
extern char bss_end[];

extern unsigned char g_MiscLevelFlags[] __attribute__((section(".data")));
extern int g_newlevel;
extern int FramesSinceStateChange;
extern float FrameLoad;
extern int FrameOverrun;
extern short g_SceneRecording[]; // incomplete type: retail loads it with lui/lh, not $gp
extern unsigned long frm_clock_time;
extern int gsFrame;

extern "C" void snd_UnkFunction_0012eaf0(void);
extern "C" void snd_UnkFunction_0012eb00(void);

void Stash_InitOnce(void);
void InitLevel(void);
int InitLevelFromWad(int full, int keep);
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


// Loads the level and runs the main loop until another level is asked for.
void startLevel(void)
{
    int i;
    int mode;
    int reloadLevel;
    int reloadMode;
    int one;
    int per;
    float angle;

    // Clear the level's .bss (bss_start..End): with FastMemSetZero when it is quadword aligned, else a byte at a time.
    if (((bss_end - bss_start) & 15) == 0 && ((unsigned int)bss_start & 15) == 0) {
        FastMemSetZero(bss_start, bss_end - bss_start);
    } else {
        printf_stub("crap\n");
        for (i = 0; i < bss_end - bss_start; i++) {
            bss_start[i] = 0;
        }
    }
    Stash_InitOnce();
    FramesSinceStateChange = 0;
    gameMode = GAME_MODE_SPACE;
    one = 1;
    InitLevel();
    musicGlobals.play.track = 0;
    InitLevelFromWad(1, 0);
    Debug.update = 0xF;
    Debug.tvMode = videoModePal;
    Debug.scene = -1;
    Debug.selectedCol = one;
    Debug.actuator = one;
    ResetDebugEnables();
    map_LoadPlanetMap();
    hud_InitBanks();
    LoadHudSeqs();
    space_StartLevelArrival();
    gsFrame = 0;
    sceGsSyncV(0);
    PutDispBuffer();

    music_StartTrack(musicGlobals.play.track, 1, 0x400);
    if ((Level == one && g_SeenPlanets[3] == 0) || (Level == 0 && g_MiscLevelFlags[0] != 0)) {
        music_Unpause();
    } else {
        music_Pause(0);
    }

    if (LevelVisited[Level] == 0) {
        LevelVisited[Level] = 1;
    }
    if (UsageStats[Level].count < 0xFFFF) {
        UsageStats[Level].count++;
    }
    per = 600;
    if (FastScaleRoundInt(TotalPlayTime) / per > UsageStats[Level].latestTimeBucket) {
        UsageStats[Level].latestTimeBucket = FastScaleRoundInt(TotalPlayTime) / 600;
    }
    UsageStats[Level].levelMask = UsageStats[Level].levelMask | (1 << Level) | 0x80000000;
    snd_UnkFunction_0012eaf0();

    while (!g_newlevel) {
        reloadLevel = 0;
        reloadMode = 0;
        frm_clock_time += *T1_COUNT;
        *T1_COUNT = 0;
        ResetLevelCounters();
        CutscenePlaying = 0;
        VU1_sendChain();
        VU1_swapChain();
        PutDrawBufferSmall();
        ((void (*)(void))AA_DisplayPass)(); // retail passes no argument
        PutDrawBufferLarge();
        snd_FlushSoundCommands();

        mode = gameMode;
        switch (mode) {
        case GAME_MODE_DEBUG:
            UpdatePad();
            UpdateDebugSelections();
            DrawDebugMenu();
            break;
        case GAME_MODE_NORMAL:
            UpdatePad();
            UpdateGameplay();
            SetupDefaultDraw();
            break;
        case GAME_MODE_MOVIE:
            UpdateCinematic();
            break;
        case GAME_MODE_SCENE:
            UpdatePad();
            UpdateInLevelMovie();
            ((void (*)(void))SetupDefaultDrawMovie)(); // retail passes no argument
            break;
        case GAME_MODE_PAUSE:
            UpdatePad();
            UpdatePause();
            CallDrawOverlayIfNoCutscene();
            break;
        case GAME_MODE_FREEZE:
            UpdatePad();
            UpdateModeFreeze();
            SetupDefaultDrawFreeze();
            break;
        case GAME_MODE_VENDOR:
            UpdatePad();
            vendor_PreUpdate();
            vendor_PostUpdate();
            break;
        case GAME_MODE_SPACE:
            UpdatePad();
            UpdateSpace();
            space_DefaultDraw();
            break;
        case GAME_MODE_CREDITS:
            UpdatePad();
            UpdateCredits();
            DrawFrameEnd();
            break;
        }
        if (gameMode != mode) {
            FramesSinceStateChange = 0;
        } else {
            FramesSinceStateChange++;
        }

        if (CutscenePlaying) {
            VU1_syncChain(1);
            VU1_initChain();
            continue;
        }

        memcard_Update();
        UpdateMCState();
        if ((g_memcard.stage >= 3 || g_memcard.nextstage >= 0) && !PauseMenu.hideActivityIcon) {
            int n = 55;
            float size;

            FlipAndExploreTimersVU1(0);
            size = 272.0f;
            VU1_addGSregister(0x47, 0x3004B);
            Hud_DrawTexQuad(HudTex_GetFrame(0x755D, 0), 50, 300, 64, 64, 0x80);
            angle = (float)(gsFrame % n) * -6.2831855f / (float)n;
            Hud_DrawRotatedSprite16(1312.0f, 5312.0f, size, size, angle, 64, 64,
                                    HudTex_Bind(HudTex_GetFrame(0x755D, 1)));
            FinalizeVU1FramePacketChain();
        }
        PauseMenu.hideActivityIcon = 0;

        DebugFontFlush();
        printf_stub2("system misc", 0x10);
        printf_stub3("system misc", 0x10);
        VU1_syncChain(1);
        FrameLoad = FastIntToFloat(*T1_COUNT) / (videoModePal ? 11520.0f : 9600.0f);
        if (gameMode == GAME_MODE_NORMAL && Debug.profile) {
            STUB_00218990();
        }

        if (!Hero.outOfBounds) {
            if (gameMode == GAME_MODE_NORMAL || gameMode == GAME_MODE_SCENE) {
                int limit = 9600;

                if (videoModePal) {
                    limit = 11520;
                }
                // The frame overran its budget: run one more update to catch up.
                if (limit < (int)*T1_COUNT) {
                    if (gameMode == GAME_MODE_NORMAL) {
                        UpdatePad();
                        UpdateGameplay();
                    } else if (gameMode == GAME_MODE_SCENE && !g_SceneRecording[0]) {
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
                *(float *)&FrameOverrun = 0.0f;
            }
        }
        ResetGsRegistersPr();

        // Fell out of the level: reload it in place.
        if (gameMode == GAME_MODE_NORMAL && Hero.outOfBounds) {
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
            gameMode = GAME_MODE_NORMAL;
            music_StartTrack(musicGlobals.play.track, 1, 0x400);
            hud_InitBanks();
        }
        per = 600;
        if (FastScaleRoundInt(TotalPlayTime) / per > UsageStats[Level].latestTimeBucket) {
            UsageStats[Level].latestTimeBucket = FastScaleRoundInt(TotalPlayTime) / 600;
        }
    }
    DoSpaceTransition();
}
