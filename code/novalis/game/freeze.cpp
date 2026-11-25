#include "common.h"
#include "freeze.h"
#include "mcstate.h"
#include "draw.h"
#include "fastfunc.h"
#include "font.h"
#include "gameglobals.h"
#include "hero.h"
#include "gsregs.h"
#include "help.h"
#include "hud.h"
#include "memcard.h"
#include "music.h"
#include "libc.h"
#include "pad.h"
#include "pause.h"
#include "sound.h"
#include "vuchain.h"

// Frames the prompt waits before it can be dismissed.
#define PROMPT_DEFAULT_TIMER 0x78
#define PROMPT_TIMER_FRAMES 30

// Sound group that is paused while the game is frozen.
#define FREEZE_SOUND_GROUP 0x1D

// Message ids of the texts the prompts show.
#define MSG_PROMPT_0_TITLE 0x4F6E
#define MSG_PROMPT_0_YES 0x5248
#define MSG_PROMPT_0_NO 0x5249
#define MSG_PROMPT_OK 0x524A
#define MSG_PROMPT_1_TITLE 0x5229
#define MSG_PROMPT_1_BODY 0x4EE0

// Message that is logged as seen when the save-failed prompt appears.
#define HELP_MSG_SAVE_FAILED 0x4E2B

// Frames of the delayed-continue freeze before the prompt fades and before it can be left.
#define FREEZE_DELAYED_FADE_FRAMES 0x5A
#define FREEZE_DELAYED_CONTINUE_FRAMES 0x78

#define SCRATCHPAD 0x70000000

#define FREEZE_DISPATCH_FADE_FRAMES 30
#define FREEZE_RETRY_TIME_FRAMES 0x1068
#define VIDEO_TEST_TIMEOUT_FRAMES 0x258
#define CONFIRM_BOX_STEPS 8

enum video_test_state {
    VIDEO_TEST_INPUT_DELAY,
    VIDEO_TEST_AWAIT_START,
    VIDEO_TEST_PREVIEW_ACTIVE,
    VIDEO_TEST_AWAIT_TIMEOUT_ACK
};

enum confirm_state {
    CONFIRM_PREPARE,
    CONFIRM_AWAIT_INPUT,
    CONFIRM_ACCEPT,
    CONFIRM_CANCEL
};

// Layout values and colors (RGBA, 0xAABBGGRR) of the freeze dialogs.
int FreezeAnsRow2 = 115;
int FreezeAnsRow1 = 130;
int FreezeTextColor = 0x00FFA888;
int FreezeTextColorBlend = 0x80FFA888;
int FreezeConfirmBoxCenterX = 256;
int FreezeConfirmBoxCenterY = 185;
int FreezeConfirmBoxHalfWidth = 100;
int FreezeConfirmBoxHalfHeight = 50;
int FreezeConfirmTextY = 150;
int FreezeStatsBoxCenterX = 256;
int FreezeStatsBoxCenterY = 205;
int FreezeStatsBoxHalfWidth = 100;
int FreezeStatsBoxHalfHeight = 120;
int FreezeStatsTextY = 110;
int FreezePulsePeriod = 180;
int FreezePulseColor = 0x80E08060;
int FreezePulseColorBlend = 0x80D06050;
int FreezeSharedTextColor = 0x00FFC0C0;
int FreezeSharedTextColorBlend = 0x80FFC0C0;
int FreezeMatchedTextColor = 0x0060EF60;
int FreezeMatchedTextColorBlend = 0x8060EF60;
int FreezeUnmatchedTextColor = 0x006060EF;
int FreezeUnmatchedTextColorBlend = 0x806060EF;

int GetLastFreezeDialogType(void)
{
    return Freeze.prevGameMode;
}

void mode_freezeInit(int dialog, int restorePage)
{
    if (gameMode != GAME_MODE_PAUSE) {
        snd_PauseAllSoundsInGroup(FREEZE_SOUND_GROUP);
        music_Pause(0);
    }

    Freeze.prevGameMode = gameMode;
    Freeze.restorePage = restorePage;
    gameMode = GAME_MODE_FREEZE;
    Freeze.mode = dialog;

    switch (dialog) {
    case FREEZE_DIALOG_CONFIRM:
        Freeze.query = msg_string(MSG_PROMPT_0_TITLE);
        Freeze.ans1 = msg_string(MSG_PROMPT_0_YES);
        Freeze.ans2 = msg_string(MSG_PROMPT_0_NO);
        Freeze.countdown = 0;
        Freeze.updTimers[0] = 0;
        Freeze.updTimers[1] = 0;
        Freeze.updTimers[2] = 0;
        Freeze.updTimers[3] = 0;
        break;
    case 2:
        Freeze.query = msg_string(MSG_PROMPT_OK);
        Freeze.ans1 = 0;
        Freeze.countdown = 0;
        break;
    case 1:
    case 4:
        Freeze.query = msg_string(MSG_PROMPT_1_TITLE);
        Freeze.ans1 = msg_string(MSG_PROMPT_1_BODY);
        Freeze.ans2 = msg_string(MSG_PROMPT_OK);
        Freeze.countdown = 0;
        break;
    case FREEZE_DIALOG_LOG_HELP:
        Help_AddToLog(HELP_MSG_SAVE_FAILED);
        Freeze.countdown = FastScaleRoundInt(PROMPT_TIMER_FRAMES);
        Freeze.updTimers[1] = 0;
        Freeze.updTimers[2] = FastScaleRoundInt(PROMPT_TIMER_FRAMES);
        break;
    case FREEZE_DIALOG_SAVE_FAILED:
        Freeze.countdown = FastScaleRoundInt(PROMPT_TIMER_FRAMES);
        Freeze.updTimers[1] = 0;
        Freeze.updTimers[2] = FastScaleRoundInt(PROMPT_TIMER_FRAMES);
        break;
    case 6:
        Freeze.countdown = FastScaleRoundInt(PROMPT_TIMER_FRAMES);
        Freeze.updTimers[0] = 0;
        break;
    default:
        Freeze.query = 0;
        Freeze.ans1 = 0;
        Freeze.ans2 = 0;
        Freeze.countdown = PROMPT_DEFAULT_TIMER;

        break;
    }
}

void DrawDialogText(void)
{
    static const FontWindow logWindow = {0x50, 0x154, 0x60, 0x1A0, 0x100, 0x54, 0, 0, 0x10, 1, 0, 0};
    static const FontWindow choiceWindow = {0x64, 0x12C, 0x60, 0x1A0, 0x100, 0x68, 0, 0, 0x10, 1, 0, 0};

    char formattedText[0x200];
    FontWindow box;

    FlipAndExploreTimersVU1(0);

    switch (Freeze.mode) {
    case FREEZE_DIALOG_LOG_HELP: {
        char *cursor;
        int color;
        int tint;
        int mid;
        int top;
        int bottom;
        float alpha;
        float iconY;
        float angle;
        float iconSize;

        alpha = 1.0f - (float)Freeze.countdown / (float)FastScaleRoundInt(30);
        DrawTextShadow(0x50, 0x154, 0x60, 0x1A0, (int)(alpha * 80.0f));

        box = logWindow;
        color = FastTweenColor(FreezeTextColor, FreezeTextColorBlend, alpha);

        strncpy((char *)SCRATCHPAD, msg_string(0x4E2B), 0x400);
        cursor = (char *)SCRATCHPAD;

        while (*(unsigned char *)cursor >= 2) {
            cursor++;
        }

        if (*(unsigned char *)cursor == 1) {
            do {
                *cursor++ = 0;
            } while (*(unsigned char *)cursor == 1);
        }

        FontPrintWindow(&box, color, (char *)SCRATCHPAD, -1, FontSet(1), FontNormalMetrics);

        iconSize = 272.0f;
        box.flags |= 4;
        bottom = box.text_y + box.max_height;
        FontPrintWindow(&box, color, cursor, -1, FontSet(1), FontNormalMetrics);

        box.flags ^= 4;
        box.text_y = 0x136 - box.max_height;
        FontPrintWindow(&box, color, cursor, -1, FontSet(1), FontNormalMetrics);

        tint = FastTweenColor(0x20FFFF, 0x8020FFFF, 1.0f - (float)Freeze.updTimers[2] / (float)FastScaleRoundInt(30));
        FontPrintCenter(0x100, 0x140, tint, msg_string(0x524A), -1);

        mid = (bottom + box.text_y) >> 1;
        VU1_addGSregister(GS_REG_TEST_1, 0x3004B);
        top = mid - 0x20;
        Hud_DrawTexQuad(HudTex_GetFrame(0x755D, 0), 0xE0, top, 0x40, 0x40, 0x80);

        iconY = (float)(mid << 4);
        angle = (float)(gsFrame % 55) * -6.2831855f / 55.0f;
        Hud_DrawRotatedSprite16(4096.0f, iconY, iconSize, iconSize, angle, 0x40, 0x40, HudTex_Bind(HudTex_GetFrame(0x755D, 1)));

        break;
    }
    case FREEZE_DIALOG_SAVE_FAILED: {
        char *text;
        int left;
        int right;
        int mid;
        int tint;
        int top;
        int dialogHeight;
        float alpha;

        text = "";
        left = 0;
        mid = 0;
        right = 0;

        switch (mc_state) {
        case CS_PROMPT_FORMAT:
            left = 0x524F;
            right = 0x524B;
            text = msg_string(0x4FAF);
            break;
        case CS_NOSAVE:
            if (!(mcstate_flags & MCSTATE_FLAG_SAVE)) {
                mid = 0x4FA8;
                text = msg_string(0x4FA7);
                break;
            }
        case CS_PROMPT_CREATE_SAVE:
            left = 0x524F;
            right = 0x524B;
            text = msg_string(0x4FAD);
            break;
        case CS_CHECK_SAVE:
        case CS_CHECKING_SAVE:
            text = msg_string(0x4FC1);
            break;
        case CS_FORMAT_PENDING:
        case CS_FORMATTING:
            text = msg_string(0x4FB7);
            break;
        case CS_CREATE_SAVE_PENDING:
        case CS_CREATING_SAVE:
            text = msg_string(0x4FB8);
            break;
        case CS_PROMPT_FORMAT_FAILED:
            mid = 0x524A;
            text = msg_string(0x4FBA);
            break;
        case CS_PROMPT_CREATE_FAILED:
            mid = 0x524A;
            text = msg_string(0x4FBC);
            break;
        case CS_GOOD_LOAD:
            mid = 0x524A;
            text = msg_string(0x4FA6);
            if (Freeze.countdown != 0) {
                mid = 0;
            }
            break;
        case CS_NO_ROOM:
            if (mcstate_flags & MCSTATE_FLAG_LOAD) {
                mid = 0x4FA8;
                text = msg_string(0x4FA7);
            } else if (InFrontEnd != 0) {
                left = 0x524E;
                right = 0x524B;
                sprintf(formattedText, "%s%c%c%s", msg_string(0x4FA9), 1, 1, msg_string(0x4FAA));
                text = formattedText;
            } else {
                mid = 0x4FA8;
                text = msg_string(0x4FA9);
            }
            break;
        case CS_PROMPT_SAVE_FAILED:
            mid = 0x524A;
            text = msg_string(0x4FBD);
            break;
        case CS_PROMPT_LOAD_FAILED:
            mid = 0x524A;
            text = msg_string(0x4FBB);
            break;
        case CS_PROMPT_BEGIN_NOSAVE:
            left = 0x524E;
            right = 0x524B;
            sprintf(formattedText, "%s%c%c%s", msg_string(0x4FAE), 1, 1, msg_string(0x4FAA));
            text = formattedText;
            break;
        case CS_PROMPT_BEGIN_UNFORMATTED:
            left = 0x524E;
            right = 0x524B;
            text = msg_string(0x4FB1);
            break;
        case CS_NOCARD:
        case CS_WAIT_FOR_CARD:
            if (InFrontEnd != 0 && (mcstate_flags & MCSTATE_FLAG_SAVE)) {
                left = 0x524E;
                right = 0x524B;
                text = msg_string(0x4FAB);
            } else {
                mid = 0x4FA8;
                text = msg_string(0x4FAC);
            }
            break;
        case CS_UNFORMATTED:
            mid = 0x4FA8;
            sprintf(formattedText, "%s%c%c%s", msg_string(0x4FB0), 1, 1, msg_string(0x4FA7));
            text = formattedText;
            break;
        }

        FontWindow initialWindow;
        memset(&initialWindow, 0, sizeof(initialWindow));
        initialWindow.win_bot = Scrn.paramY;
        initialWindow.win_left = 0x60;
        initialWindow.win_right = 0x1A0;
        initialWindow.text_x = 0x100;
        initialWindow.text_y = 0x68;
        initialWindow.line_spacing = 0x10;
        initialWindow.flags = 5;

        box = initialWindow;
        FontPrintWindowMedium(&box, 0, text, -1);

        dialogHeight = box.max_height + 0x28;
        top = (Scrn.paramY - dialogHeight) >> 1;
        box.win_bot = top + dialogHeight;
        box.text_y = top + 4;
        box.win_top = top;

        alpha = 1.0f - (float)Freeze.countdown / (float)FastScaleRoundInt(30);
        DrawTextShadow(box.win_top, box.win_bot, 0x60, 0x1A0, (int)(alpha * 80.0f));

        box.flags ^= 4;
        FontPrintWindowMedium(&box, FastTweenColor(FreezeTextColor, FreezeTextColorBlend, alpha), text, -1);

        tint = FastTweenColor(0x20FFFF, 0x8020FFFF, 1.0f - (float)Freeze.updTimers[2] / (float)FastScaleRoundInt(30));
        if (left != 0) {
            FontPrintCenter(0xCA, box.win_bot - 0x14, tint, msg_string(left), -1);
        }

        if (right != 0) {
            FontPrintCenter(0x135, box.win_bot - 0x14, tint, msg_string(right), -1);
        }

        if (mid != 0) {
            FontPrintCenter(0x100, box.win_bot - 0x14, tint, msg_string(mid), -1);
        }

        break;
    }
    case FREEZE_MODE_VIDEO_MODE_TEST: {
        int textColor;
        int buttonColor;
        int bodyMessage;
        float alpha;

        box = choiceWindow;

        alpha = 1.0f - (float)Freeze.countdown / (float)FastScaleRoundInt(30);
        DrawTextShadow(0x64, 0x12C, 0x60, 0x1A0, (int)(alpha * 80.0f));

        textColor = FastTweenColor(FreezeTextColor, FreezeTextColorBlend, alpha);
        buttonColor = FastTweenColor(0x20FFFF, 0x8020FFFF, alpha);

        switch (Freeze.updTimers[0]) {
        case 0:
        case 1:
            FontPrintCenter(0xCA, 0x118, buttonColor, msg_string(0x524E), -1);
            FontPrintCenter(0x135, 0x118, buttonColor, msg_string(0x524B), -1);
            bodyMessage = 0x522A;
            break;
        case 2:
            FontPrintCenter(0xCA, 0x118, buttonColor, msg_string(0x524E), -1);
            FontPrintCenter(0x135, 0x118, buttonColor, msg_string(0x524B), -1);
            bodyMessage = 0x522B;
            break;
        case 3:
            FontPrintCenter(0x100, 0x118, buttonColor, msg_string(0x524A), -1);
            bodyMessage = 0x522C;
            break;
        default:
            bodyMessage = 0;
            break;
        }

        if (bodyMessage != 0) {
            FontPrintWindow(&box, textColor, msg_string(bodyMessage), -1, FontSet(1), FontNormalMetrics);
        }

        break;
    }
    case FREEZE_DIALOG_CONFIRM: {
        char line[0x40];
        int pulse;
        int sharedColor;
        int matchedColor;
        int unmatchedColor;
        int best;
        int scoreReference;
        int unit;
        int remainder;
        int perSecond;
        int minutes;
        int seconds;
        int hundredths;
        float scale;
        float blend;

        pulse = FastTweenColor(FreezePulseColor, FreezePulseColorBlend, FastAngleCosF((float)(gsFrame % FreezePulsePeriod) / FastIntToFloat(FreezePulsePeriod) * 6.28318f - 3.14159f) * 0.5f + 0.5f);

        scale = (float)Freeze.updTimers[1] * 0.125f;
        if (scale > 1.0f) {
            scale = 1.0f;
        } else if (scale < 0.1f) {
            scale = 0.1f;
        }

        sharedColor = FreezeSharedTextColor;
        matchedColor = FreezeMatchedTextColor;
        unmatchedColor = FreezeUnmatchedTextColor;

        if (Freeze.updTimers[2] != 0) {
            blend = (float)Freeze.updTimers[2] * 0.125f;
            if (blend > 1.0f) {
                blend = 1.0f;
            } else if (blend < 0.0f) {
                blend = 0.0f;
            }

            sharedColor = FastTweenColor(FreezeSharedTextColor, FreezeSharedTextColorBlend, blend);
            matchedColor = FastTweenColor(FreezeMatchedTextColor, FreezeMatchedTextColorBlend, blend);
            unmatchedColor = FastTweenColor(FreezeUnmatchedTextColor, FreezeUnmatchedTextColorBlend, blend);
        }

        if (Hero.raceLap < 3) {
            DrawRoundedRect(FreezeConfirmBoxCenterY - FastFloatToInt((float)FreezeConfirmBoxHalfHeight * scale), FreezeConfirmBoxCenterY + FastFloatToInt((float)FreezeConfirmBoxHalfHeight * scale), FreezeConfirmBoxCenterX - FastFloatToInt((float)FreezeConfirmBoxHalfWidth * scale), FreezeConfirmBoxCenterX + FastFloatToInt((float)FreezeConfirmBoxHalfWidth * scale), pulse);

            FontPrintCenter(0x100, FreezeConfirmTextY, sharedColor, msg_string(0x4F6E), -1);
            FontPrintCenter(0x100, FreezeConfirmTextY + 0x18, sharedColor, msg_string(0x5249), -1);
            FontPrintCenter(0x100, FreezeConfirmTextY + 0x30, sharedColor, msg_string(0x5248), -1);
        } else {
            DrawRoundedRect(FreezeStatsBoxCenterY - FastFloatToInt((float)FreezeStatsBoxHalfHeight * scale), FreezeStatsBoxCenterY + FastFloatToInt((float)FreezeStatsBoxHalfHeight * scale), FreezeStatsBoxCenterX - FastFloatToInt((float)FreezeStatsBoxHalfWidth * scale), FreezeStatsBoxCenterX + FastFloatToInt((float)FreezeStatsBoxHalfWidth * scale), pulse);

            sprintf(line, "    %s", msg_string(0x5240));

            if (Hero.racePlace == 1) {
                sprintf(line, "%dst", 1);
            } else if (Hero.racePlace == 2) {
                sprintf(line, "%dnd", 2);
            } else if (Hero.racePlace == 3) {
                sprintf(line, "%drd", 3);
            } else {
                sprintf(line, "%dth", Hero.racePlace);
            }

            line[3] = ' ';
            if (Hero.racePlace == 1) {
                FontPrintCenter(0x100, FreezeStatsTextY, matchedColor, line, -1);
            } else {
                FontPrintCenter(0x100, FreezeStatsTextY, unmatchedColor, line, -1);
            }

            best = freezeStatsTimeRefA[(Level ^ 0x10) ? 0 : 1];

            if (best == Hero.raceTime) {
                unit = videoModePal ? 3000 : 3600;
                perSecond = unit / 60;
                minutes = best / unit;
                remainder = best - minutes * unit;
                seconds = remainder / perSecond;
                hundredths = (remainder - seconds * perSecond) * 100 / perSecond;

                sprintf(line, "%s", msg_string(0x50A3));
                FontPrintCenter(0x100, FreezeStatsTextY + 0x26, matchedColor, line, -1);
                sprintf(line, "%d:%02d:%02d", minutes, seconds, hundredths);
                FontPrintCenter(0x100, FreezeStatsTextY + 0x3A, matchedColor, line, -1);
            } else {
                sprintf(line, "%s", msg_string(0x50A2));
                FontPrintCenter(0x100, FreezeStatsTextY + 0x30, unmatchedColor, line, -1);
            }

            scoreReference = freezeStatsScoreRefA[(Level ^ 0x10) ? 0 : 1];

            if (scoreReference != 0 && scoreReference == Hero.raceScore) {
                sprintf(line, "%s", msg_string(0x50A5));
                FontPrintCenter(0x100, FreezeStatsTextY + 0x56, matchedColor, line, -1);
                sprintf(line, "%d", Hero.raceScore);
                FontPrintCenter(0x100, FreezeStatsTextY + 0x6A, matchedColor, line, -1);
            } else {
                sprintf(line, "%s", msg_string(0x50A4));
                FontPrintCenter(0x100, FreezeStatsTextY + 0x60, unmatchedColor, line, -1);
            }

            FontPrintCenter(0x100, FreezeStatsTextY + 0x90, sharedColor, msg_string(0x5249), -1);
            FontPrintCenter(0x100, FreezeStatsTextY + 0xA8, sharedColor, msg_string(0x5248), -1);
        }

        break;
    }
    case FREEZE_MODE_AWAIT_CROSS:
        DrawRoundedRect(0x64, 0xA0, 0xB0, 0x150, FastTweenColor(FreezePulseColor, FreezePulseColorBlend, FastAngleCosF((float)(gsFrame % FreezePulsePeriod) / FastIntToFloat(FreezePulsePeriod) * 6.28318f - 3.14159f) * 0.5f + 0.5f));
        FontPrintCenter(0x100, 0x7A, 0x8000C0C0, Freeze.query, -1);
        break;
    default: {
        freeze_t *dialog = &Freeze;
        int pulse;

        pulse = FastTweenColor(FreezePulseColor, FreezePulseColorBlend, FastAngleCosF((float)(gsFrame % FreezePulsePeriod) / FastIntToFloat(FreezePulsePeriod) * 6.28318f - 3.14159f) * 0.5f + 0.5f);

        DrawRoundedRect(0x50, FreezeAnsRow1 + 0x1A, 0xB0, 0x150, pulse);
        if (dialog->query != 0) {
            FontPrintCenter(0x100, 0x5A, 0x8000C0C0, dialog->query, -1);
        }

        if (dialog->ans1 != 0) {
            FontPrintCenter(0x100, FreezeAnsRow2, 0x80FFA888, dialog->ans1, -1);
        }

        if (dialog->ans2 != 0) {
            FontPrintCenter(0x100, FreezeAnsRow1, 0x80FFA888, dialog->ans2, -1);
        }

        break;
    }
    }

    FinalizeVU1FramePacketChain();
}

void UpdateModeFreeze(void)
{
    int step;
    int video_mode;
    freeze_t *frozen;

    sound_Update();

    if (Freeze.countdown != 0) {
        Freeze.countdown--;
    }

    switch (Freeze.mode) {
    case FREEZE_MODE_DELAYED_CONTINUE:
        frozen = &Freeze;
        frozen->updTimers[1]++;
        if (FastScaleRoundInt(FREEZE_DELAYED_FADE_FRAMES) < frozen->updTimers[1]) {
            if (frozen->updTimers[2] != 0) {
                frozen->updTimers[2]--;
            }
        }

        frozen = &Freeze;
        if (FastScaleRoundInt(FREEZE_DELAYED_CONTINUE_FRAMES) < frozen->updTimers[1]) {
            if (padState.bitsOn & PAD_CROSS) {
                gameMode = GAME_MODE_NORMAL;
                if (Level == LEVEL_NOVALIS) {
                    memcard_Save(0, -1);
                }
            }
        }
        break;
    case FREEZE_MODE_TRIANGLE_HIDE_HERO:
        if (padState.bitsOn & PAD_TRIANGLE) {
            MobyInstance *moby = Hero.moby;

            moby->enabled = 0;
            moby->collision = 0;
            moby->modeBits |= DISABLED;
            Hero_RevertToRatchet();
            Hero_Warp(&Hero.savedPosRot[0], &Hero.savedPosRot[4], 0, 1);
            gameMode = GAME_MODE_NORMAL;
        } else if (padState.bitsOn & PAD_CROSS) {
            gameMode = GAME_MODE_NORMAL;
        }
        break;
    case FREEZE_MODE_VIDEO_MODE_TEST:
        switch (Freeze.updTimers[0]) {
        case VIDEO_TEST_INPUT_DELAY:
            if (Freeze.countdown != 0) {
                Freeze.countdown--;
                if (Freeze.countdown == 0) {
                    Freeze.updTimers[0] = VIDEO_TEST_AWAIT_START;
                }
            } else {
                Freeze.updTimers[0] = VIDEO_TEST_AWAIT_START;
            }
            break;
        case VIDEO_TEST_AWAIT_START:
            if (padState.bitsOn & PAD_TRIANGLE) {
                gameMode = Freeze.prevGameMode;
            } else if (padState.bitsOn & PAD_CROSS) {
                FadeToBlack(4);
                PalModeRequest = 0;
                Freeze.updTimers[0] = VIDEO_TEST_PREVIEW_ACTIVE;
                Freeze.updTimers[1] = FastScaleRoundInt(VIDEO_TEST_TIMEOUT_FRAMES);
            }
            break;
        case VIDEO_TEST_PREVIEW_ACTIVE:
            if (Freeze.updTimers[1] == 0 || --Freeze.updTimers[1] == 0) {
                PalModeRequest = 1;
                Freeze.updTimers[0] = VIDEO_TEST_AWAIT_TIMEOUT_ACK;
            } else if (padState.bitsOn & PAD_TRIANGLE) {
                FadeToBlack(4);
                PalModeRequest = 1;
                gameMode = Freeze.prevGameMode;
            } else if (padState.bitsOn & PAD_CROSS) {
                PalModeRequest = 0;
                gameMode = Freeze.prevGameMode;
            }
            break;
        case VIDEO_TEST_AWAIT_TIMEOUT_ACK:
            if (padState.bitsOn & PAD_CROSS) {
                gameMode = Freeze.prevGameMode;
            }
            break;
        default:
            gameMode = Freeze.prevGameMode;
            break;
        }
        break;
    case FREEZE_MODE_TRIANGLE_SET_SHIP_FLAG:
        OcclMode = 2;
        if (padState.bitsOn & PAD_TRIANGLE) {
            gameMode = GAME_MODE_NORMAL;
            Hero.shipFlags |= HERO_SHIP_FLAG_RESET;
        } else if (padState.bitsOn & PAD_CROSS) {
            gameMode = GAME_MODE_NORMAL;
        }
        break;
    case FREEZE_MODE_AWAIT_CROSS:
        OcclMode = 2;
        if (padState.bitsOn & PAD_CROSS) {
            gameMode = GAME_MODE_NORMAL;
        }
        break;
    case FREEZE_MODE_CONFIRM_CANCEL:
        switch (Freeze.updTimers[0]) {
        case CONFIRM_PREPARE:
            if (Freeze.updTimers[1] < CONFIRM_BOX_STEPS) {
                Freeze.updTimers[1]++;
            } else if (Freeze.updTimers[2] < CONFIRM_BOX_STEPS) {
                Freeze.updTimers[2]++;
            } else {
                Freeze.updTimers[0] = CONFIRM_AWAIT_INPUT;
            }
            break;
        case CONFIRM_AWAIT_INPUT:
            if (padState.bitsOn & PAD_CROSS) {
                Freeze.updTimers[0] = CONFIRM_ACCEPT;
            } else if (padState.bitsOn & (PAD_CIRCLE | PAD_START)) {
                Freeze.updTimers[0] = CONFIRM_CANCEL;
            }

            video_mode = PalModeRequest; // fakematch
            if (video_mode >= 0) { // fakematch
                break; // fakematch
            } // fakematch
        case CONFIRM_ACCEPT:
        case CONFIRM_CANCEL:
            if (Freeze.updTimers[2] != 0) {
                Freeze.updTimers[2]--;
            } else if (Freeze.updTimers[1] != 0) {
                Freeze.updTimers[1]--;
            } else {
                step = Freeze.updTimers[0];
                video_mode = PalModeRequest; // fakematch
                if (video_mode < 0) { // fakematch
                    Freeze.updTimers[0] = step; // fakematch
                } else if (step == CONFIRM_ACCEPT) {
                    if (Hero.trickHudHandle != HERO_NO_HUD_HANDLE) {
                        Hud_SetEntryValueById(Hero.trickHudHandle, 0);
                        Hero.trickHudHandle = HERO_NO_HUD_HANDLE;
                    }
                    HudStub();
                    if (FastScaleRoundInt(FREEZE_RETRY_TIME_FRAMES) < Hero.controlModeTimer) {
                        if (Level == LEVEL_RILGAR) {
                            RilgarRetryCount++;
                        } else if (Level == LEVEL_KALEBO_3) {
                            KaleboRetryCount++;
                        }
                    }
                    gameMode = GAME_MODE_NORMAL;
                    Hero_Warp(&Hero.savedPosRot[0], &Hero.savedPosRot[4], 0, 1);
                } else {
                    gameMode = GAME_MODE_NORMAL;
                    if (Hero.raceLap >= HERO_RACE_LAP_COUNT) {
                        Hero.raceLap--;
                        Hero.raceMoby[HERO_RACE_MOBY_LAP_OFFSET] = HERO_RACE_LAP_COUNT;
                    }
                }
            }
            break;
        }
        break;
    case FREEZE_MODE_STATE_DISPATCH:
        Freeze.updTimers[1]++;
        if (FastScaleRoundInt(FREEZE_DISPATCH_FADE_FRAMES) < Freeze.updTimers[1]) {
            if (Freeze.updTimers[2] != 0) {
                Freeze.updTimers[2]--;
            }
        }

        switch (mc_state) {
        case CS_GOOD_LOAD:
            if (Freeze.countdown == 0) {
                if (padState.bitsOn & PAD_CROSS) {
                    mcstate_flags &= ~MCSTATE_FLAG_CARD_CHANGED;
                    gameMode = Freeze.prevGameMode;
                }
            }
            break;
        case CS_PROMPT_FORMAT:
            if (padState.bitsOn & PAD_CIRCLE) {
                mcstate_flags |= MCSTATE_FLAG_FORMAT_YES;
            } else if (padState.bitsOn & PAD_TRIANGLE) {
                mcstate_flags |= MCSTATE_FLAG_ANSWER_NO;
                mcstate_flags &= ~MCSTATE_FLAG_SAVE;
                mcstate_flags &= ~MCSTATE_FLAG_LOAD;
                if (InFrontEnd == 0) {
                    gameMode = Freeze.prevGameMode;
                }
            }
            break;
        case CS_PROMPT_CREATE_SAVE:
            if (padState.bitsOn & PAD_CIRCLE) {
                mcstate_flags |= MCSTATE_FLAG_CREATE_YES;
            } else if (padState.bitsOn & PAD_TRIANGLE) {
                mcstate_flags |= MCSTATE_FLAG_ANSWER_NO;
                mcstate_flags &= ~MCSTATE_FLAG_SAVE;
                mcstate_flags &= ~MCSTATE_FLAG_LOAD;
                if (InFrontEnd == 0) {
                    gameMode = Freeze.prevGameMode;
                }
            }
            break;
        case CS_PROMPT_FORMAT_FAILED:
        case CS_PROMPT_CREATE_FAILED:
        case CS_PROMPT_LOAD_FAILED:
        case CS_PROMPT_SAVE_FAILED:
            if (padState.bitsOn & PAD_CROSS) {
                mcstate_flags ^= MCSTATE_FLAG_PROMPT;
                mcstate_flags &= ~MCSTATE_FLAG_SAVE;
                mcstate_flags &= ~MCSTATE_FLAG_LOAD;
                gameMode = Freeze.prevGameMode;
            }
            break;
        case CS_NEWCARD:
            gameMode = Freeze.prevGameMode;
            pauseActionList[0] = Freeze.restorePage;
            break;
        case CS_NOSAVE:
            if (mcstate_flags & MCSTATE_FLAG_SAVE) {
                break;
            }
        case CS_NOCARD:
        case CS_UNFORMATTED:
            if (padState.bitsOn & PAD_TRIANGLE) {
                mcstate_flags &= ~MCSTATE_FLAG_SAVE;
                mcstate_flags &= ~MCSTATE_FLAG_LOAD;
                gameMode = Freeze.prevGameMode;
            }
            break;
        case CS_NO_ROOM:
            if (InFrontEnd != 0 && (mcstate_flags & MCSTATE_FLAG_SAVE)) {
                if (padState.bitsOn & PAD_CROSS) {
                    memcard_ResetGame();
                    mcstate_flags &= ~MCSTATE_FLAG_SAVE;
                    mcstate_flags &= ~MCSTATE_FLAG_LOAD;
                    mcstate_flags |= MCSTATE_FLAG_ANSWER_NO;
                    ChangeLevel(0);
                    LevelChangePending[0] = 1;
                } else if (padState.bitsOn & PAD_TRIANGLE) {
                    mcstate_flags &= ~MCSTATE_FLAG_SAVE;
                    mcstate_flags &= ~MCSTATE_FLAG_LOAD;
                    gameMode = Freeze.prevGameMode;
                }
            } else if (padState.bitsOn & PAD_TRIANGLE) {
                mcstate_flags &= ~MCSTATE_FLAG_SAVE;
                mcstate_flags &= ~MCSTATE_FLAG_LOAD;
                gameMode = Freeze.prevGameMode;
            }
            break;
        case CS_PROMPT_BEGIN_UNFORMATTED:
        case CS_PROMPT_BEGIN_NOSAVE:
            if (padState.bitsOn & PAD_CROSS) {
                memcard_ResetGame();
                mcstate_flags &= ~MCSTATE_FLAG_SAVE;
                mcstate_flags &= ~MCSTATE_FLAG_LOAD;
                mcstate_flags |= MCSTATE_FLAG_ANSWER_NO;
                ChangeLevel(0);
                LevelChangePending[0] = 1;
            } else if (padState.bitsOn & PAD_TRIANGLE) {
                mcstate_flags |= MCSTATE_FLAG_ANSWER_NO;
                gameMode = Freeze.prevGameMode;
            }
            break;
        case CS_WAIT_FOR_CARD:
            if (InFrontEnd != 0) {
                if (mcstate_flags & MCSTATE_FLAG_SAVE) {
                    if (padState.bitsOn & PAD_CROSS) {
                        memcard_ResetGame();
                        mcstate_flags &= ~MCSTATE_FLAG_SAVE;
                        mcstate_flags &= ~MCSTATE_FLAG_LOAD;
                        ChangeLevel(0);
                        LevelChangePending[0] = 1;
                    }

                    if (padState.bitsOn & PAD_TRIANGLE) {
                        mcstate_flags |= MCSTATE_FLAG_ANSWER_NO;
                        mcstate_flags &= ~MCSTATE_FLAG_SAVE;
                        mcstate_flags &= ~MCSTATE_FLAG_LOAD;
                        gameMode = Freeze.prevGameMode;
                    }
                } else if (mcstate_flags & MCSTATE_FLAG_LOAD) {
                    if (padState.bitsOn & PAD_TRIANGLE) {
                        mcstate_flags |= MCSTATE_FLAG_ANSWER_NO;
                        mcstate_flags &= ~MCSTATE_FLAG_SAVE;
                        mcstate_flags &= ~MCSTATE_FLAG_LOAD;
                        gameMode = Freeze.prevGameMode;
                    }
                } else {
                    gameMode = Freeze.prevGameMode;
                }
            } else if (padState.bitsOn & PAD_TRIANGLE) {
                mcstate_flags |= MCSTATE_FLAG_ANSWER_NO;
                mcstate_flags &= ~MCSTATE_FLAG_SAVE;
                mcstate_flags &= ~MCSTATE_FLAG_LOAD;
                gameMode = Freeze.prevGameMode;
            }
            break;
        case CS_FORMATTED:
            if (InFrontEnd != 0) {
                if (!(mcstate_flags & (MCSTATE_FLAG_SAVE | MCSTATE_FLAG_LOAD))) {
                    gameMode = Freeze.prevGameMode;
                }
            }
            break;
        }

        break;
    }

    if ((unsigned int)(gameMode - GAME_MODE_PAUSE) >= 2) {
        snd_ContinueAllSoundsInGroup(FREEZE_SOUND_GROUP);
        music_Unpause();
        snd_FlushSoundCommands();
    }
}
