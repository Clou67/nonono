#include "common.h"
#include "help.h"
#include "helpstrings.h"
#include "draw.h"
#include "fastfunc.h"
#include "font.h"
#include "gameglobals.h"
#include "gsregs.h"
#include "hud.h"
#include "mobyutil.h"
#include "music.h"
#include "pad.h"
#include "pause.h"
#include "sound.h"
#include "vuchain.h"

// Frames a message box takes to open, close and fade its text.
#define HELP_BOX_OPEN_FRAMES 6
#define HELP_TRANSITION_FRAMES 8
#define HELP_TEXT_FADE_FRAMES 4

// Frames to wait before the box can be used, before the prompt gives way to the
// text, how long the text stays up and how long a suspended box stays hidden.
#define HELP_READY_FRAMES 0x78
#define HELP_PROMPT_FRAMES 0x18
#define HELP_TEXT_SHOWN_FRAMES 0x1A4
#define HELP_SUSPEND_FRAMES 60

// Selector under which the box asks the moby code to show a message.
#define HELP_MESSAGE_SELECTOR 5

// Layout of the message box (screen space, 512 wide).
#define HELP_BOX_CENTER_X 0x100
#define HELP_BOX_BOTTOM_OFFSET 60
#define HELP_BOX_BOTTOM_MARGIN 12
#define HELP_BOX_PADDING_X 10
#define HELP_BOX_PADDING_Y 5
#define HELP_BOX_START_HALF_SIZE 8
#define HELP_ICON_HALF_SIZE 0x20
#define HELP_ICON_SIZE 0x40
#define HELP_ICON_FONT 4
#define HELP_ICON_FADE_STEP 21
#define HELP_ICON_ALPHA 0x7E
#define HELP_ALPHA_OPAQUE 0x80
#define HELP_FRAME_ALPHA 0x60
#define HELP_SPRITE_RGB 0x808080
#define HELP_TEXT_RGB 0xFFA888
#define HELP_TEXT_COLOR 0x80FFA888

// Bookkeeping of what has been shown: a message can be counted up to this many
// times, play time is kept in buckets of this many frames, and the top bit of
// level_die marks a message as used since the last death.
#define HELP_TIMES_USED_MAX 0xFFFF
#define HELP_FRAMES_PER_MINUTE 600
#define HELP_LEVEL_DIE_USED 0x80000000

HelpDef Help = {
    HELP_STATE_IDLE, 0,
    0, 0, 0, 0, 0, 0,
    HELP_NO_MESSAGE, HELP_NO_MESSAGE, 0, 0,
    0, 0, 0, 0, 0
};

// Rows of (id, value); the id is looked up in either column.
HelpPair HelpPairs[HELP_PAIR_COUNT] = {
    {3, HELP_STR_WELCOME_3}, {0, HELP_STR_BOMB_GLOVE_USE}, {1, HELP_STR_WHATS_NANOTECH}, {2, HELP_STR_THIS_IS_NANOTECH},
    {1000, HELP_STR_WHAT_ARE_INFOBOTS}, {1001, HELP_STR_INFOBOT_HINT}, {1002, HELP_STR_SHIP_REMINDER}, {1003, HELP_STR_LONGER_JUMPS},
    {4, HELP_STR_HYPER_STRIKE_HELP}, {5, HELP_STR_COMET_STRIKE_EXPLAINED}, {2000, HELP_STR_WHERE_TO_USE_HOVERBOARD}, {2001, HELP_STR_NEED_AMMO},
    {2002, HELP_STR_SANDSHARK_HINT}, {2003, HELP_STR_TRY_THE_PYROCITOR}, {2004, HELP_STR_IMPRESS_THE_AGENT}, {2005, HELP_STR_SONIC_SUMMONER_HELP},
    {2006, HELP_STR_SWINGIN_WITH_THE_SWINGSHOT}, {2007, HELP_STR_NEED_THE_SWINGSHOT}, {2008, HELP_STR_SWINGSHOT_REMINDER}, {2009, HELP_STR_TRESPASSER_DESCRIPTION},
    {3000, HELP_STR_HOW_TO_GLIDE}, {3001, HELP_STR_HOW_TO_BOOST_JUMP}, {3002, HELP_STR_WALL_JUMP_HINT}, {3003, HELP_STR_HOW_TO_STRETCH_JUMP},
    {3004, HELP_STR_USE_THE_MAP}, {3005, HELP_STR_SWINGSHOT_INSTRUCTIONS}, {3006, HELP_STR_SWINGSHOT_CAUTION}, {3007, HELP_STR_ZIPLINE_HINT},
    {4000, HELP_STR_GLOVE_OF_DOOM_REMINDER}, {4001, HELP_STR_GLOVE_OF_DOOM_EXPLANATION}, {4002, HELP_STR_SUCK_CANNON_DESCRIPTION}, {4003, HELP_STR_SECURITY_DOOR},
    {4004, HELP_STR_SECURITY_DOOR_2}, {5000, HELP_STR_BASIC_RACING}, {5001, HELP_STR_USING_TURBO}, {5002, HELP_STR_HYDRODISPLACER_HINT},
    {5003, HELP_STR_HYDRODISPLACER_SUGGESTION}, {5004, HELP_STR_AMMO_REMINDER}, {5005, HELP_STR_BUY_SOME_WEAPONS}, {6000, HELP_STR_GADGE_BOT_USAGE},
    {6001, HELP_STR_WHAT_IS_A_BOT_DEVICE}, {6002, HELP_STR_GADGE_BOT_ACTIONS}, {6003, HELP_STR_GLIDE_REMINDER}, {6004, HELP_STR_FORCEFIELD_HINT},
    {6005, HELP_STR_GRINDBOOTS_DESCRIPTION}, {6006, HELP_STR_HYDRODISPLACER_DESCRIPTION}, {6007, HELP_STR_STRATEGY_AGAINST_BLARG}, {6008, HELP_STR_BATTLE_SUGGESTION},
    {8000, HELP_STR_YOU_NEED_GRINDBOOTS}, {8001, HELP_STR_HOW_TO_USE_GRINDBOOTS}, {8002, HELP_STR_YOU_NEED_MAGNEBOOTS}, {8003, HELP_STR_METAL_DETECTOR_DESCRIPTION},
    {9000, HELP_STR_PILOTS_HELMET_DESCRIPTION}, {10000, HELP_STR_TIPTOE_HELP}, {10001, HELP_STR_CLANK_AND_MAGNEBOOTS}, {10002, HELP_STR_PREMIUM_NANOTECH_INFO},
    {10003, HELP_STR_ULTRA_NANOTECH_INFO}, {10004, HELP_STR_ORXON_EXPLORATION}, {11000, HELP_STR_O2_MASK_DESCRIPTION}, {11001, HELP_STR_PERSUADER_DESCRIPTION},
    {11002, HELP_STR_NEED_PILOTS_HELMET}, {11003, HELP_STR_POWER_SLAM_EXPLAINED}, {12000, HELP_STR_HYDRO_PACK_DESCRIPTION}, {12001, HELP_STR_RARITANIUM_DESCRIPTION},
    {1004, HELP_STR_LOOK_AROUND_MODE}, {1005, HELP_STR_FIRST_PERSON_AND_WEAPONS}, {1006, HELP_STR_BOLT_CRANK_EXPLANATION}, {1007, HELP_STR_ACTIVATING_MAP},
    {1008, HELP_STR_SWIMMING_HELP}, {2010, HELP_STR_MOUSE_HELP}, {2011, HELP_STR_INVINCO_LOCK_DIRECTIONS}, {2012, HELP_STR_INVINCO_LOCK_HELP},
    {2013, HELP_STR_HOW_TO_ACTIVATE_MAP}, {4005, HELP_STR_WALL_JUMP_REMINDER}, {20000, HELP_STR_AIMING_THE_BLASTER}, {20001, HELP_STR_SPEND_YOUR_BOLTS},
    {20002, HELP_STR_CAMERA_CONTROL}, {20003, HELP_STR_BOOST_JUMP_HELP}, {20004, HELP_STR_CONSTANT_FLAME}, {20005, HELP_STR_QUICKSELECT_HELP},
    {20006, HELP_STR_QUICKSELECT_INTRODUCTION}, {20007, HELP_STR_RISE_WHILE_SWIMMING}, {6009, HELP_STR_NEED_O2_MASK}, {6010, HELP_STR_SHUTTLE_EXPLANATION},
    {3008, HELP_STR_JUMP_SLOTS}, {11004, HELP_STR_JET_FIGHTER_INSTRUCTIONS}, {11005, HELP_STR_LOCK_ON_MISSILES}, {11006, HELP_STR_GET_MISSILES},
    {11007, HELP_STR_GET_HEALTH}, {11008, HELP_STR_JET_TURBO}, {8004, HELP_STR_BUY_THE_DEVASTATOR}, {9001, HELP_STR_PARATROOPER_STRATEGY},
    {10005, HELP_STR_BLARG_SAUCER_STRATEGY}, {12002, HELP_STR_HELICOPTER_STRATEGY}, {5006, HELP_STR_ACROSS_THE_GAP}, {5007, HELP_STR_HOVERBOARD_TRICKS},
    {3009, HELP_STR_TURN_OFF_HELPDESK}, {5008, HELP_STR_HELI_PACK_HINTS}, {3010, HELP_STR_EQUIP_THE_BLASTER}, {3011, HELP_STR_USE_THE_SWINGSHOT},
    {5009, HELP_STR_SWINGSHOT_CAUTION_2}, {3012, HELP_STR_QUICKSELECT_INSTRUCTIONS}, {5010, HELP_STR_LOOK_AROUND_2}, {5011, HELP_STR_MAP_GUIDANCE},
    {3013, HELP_STR_CONGRATULATIONS}, {10006, HELP_STR_NEED_DEVASTATOR}, {10007, HELP_STR_BOT_PORTS_2}, {10008, HELP_STR_BOT_DEVICE_2},
    {11009, HELP_STR_POWER_SLAM_EXPLAINED_2}, {12003, HELP_STR_HOW_TO_STRAFE}, {12004, HELP_STR_STRAFE_LEFT_AND_RIGHT}, {13000, HELP_STR_DESTROY_THE_TOWERS},
    {8005, HELP_STR_USE_THE_MAGNEBOOTS}, {11010, HELP_STR_SLAM_SWITCH}, {20008, HELP_STR_SWIMMING_SURVIVAL}, {20009, HELP_STR_MISSIONS_FINISHED},
    {20010, HELP_STR_INTERRUPT_HELPDESK}, {20011, HELP_STR_SAVE_ICON}, {20012, HELP_STR_REVERSE_CAMERA}, {20013, HELP_STR_DOUBLE_TAP_TRIANGLE},
    {20014, HELP_STR_HYRDO_PACK_TURBOJETS}, {20015, HELP_STR_CENTER_CAMERA}, {14000, HELP_STR_MORPH_O_RAY_INTRODUCTION}, {15000, HELP_STR_NEED_HOLOGUISE},
    {15001, HELP_STR_USE_THE_HOLOGUISE}, {15002, HELP_STR_WAVING}, {16000, HELP_STR_HOLOGUISE_DESCRIPTION}, {15003, HELP_STR_GIANT_CLANK_INSTRUCTIONS},
    {15004, HELP_STR_ATOMIC_BLAST}, {20016, HELP_STR_TESLA_CLAW_USE}, {15005, HELP_STR_NEED_HYDRO_PACK}, {16001, HELP_STR_RACE_ROCKETS},
    {16002, HELP_STR_MAP_O_MATIC_INSTRUCTIONS}, {18000, HELP_STR_STOP_THE_COUNTDOWN}, {11011, HELP_STR_LOCATING_RARITANIUM}, {16003, HELP_STR_NEED_HOVERBOARD},
    {15006, HELP_STR_SENTRY_BOT_WARNING}, {15007, HELP_STR_INSTANT_DEATH}, {15008, HELP_STR_HOLOGUISE_COLORS}, {17000, HELP_STR_FIND_ANOTHER_WAY},
    {18001, HELP_STR_RESET_TIMER}, {18002, HELP_STR_TIME_IS_SHORT}, {8006, HELP_STR_METAL_DETECTOR_HELP}, {16004, HELP_STR_HOLOGUISE_HELP},
    {2014, HELP_STR_SONIC_SUMMONER_HELP_2}, {20017, HELP_STR_SKILL_POINTS_4}, {20018, HELP_STR_GOLD_WEAPON_PURCHASE}, {20019, HELP_STR_GOLD_WEAPON_PURCHASE_2},
    {0, HELP_STR_TO_USE_YOUR_BOMB_0x0000}, {0, HELP_STR_TO_USE_YOUR_BOMB_0x0000},
};

void Help_Skip(void)
{
    switch (Help.state) {
    case HELP_STATE_IDLE:
        Help.message_id = HELP_NO_MESSAGE;
        break;
    case HELP_STATE_BOX_OPENING:
    case HELP_STATE_PROMPT:
        Help.state = HELP_STATE_BOX_CLOSING;
        Help.counter = 0;
        break;
    case HELP_STATE_PROMPT_TO_BOX:
        Help.state = HELP_STATE_BOX_CLOSING;
        Help.counter = 0;
        break;
    case HELP_STATE_TEXT_FADE_IN:
        Help.state = HELP_STATE_TEXT_FADE_OUT;
        Help.counter = HELP_TEXT_FADE_FRAMES - Help.counter;
        break;
    case HELP_STATE_TEXT_SHOWN:
        Help.state = HELP_STATE_TEXT_FADE_OUT;
        Help.counter = 0;
        break;
    case HELP_STATE_TEXT_FADE_OUT:
    case HELP_STATE_BOX_CLOSING:
        break;
    }
}

int Help_QueueMessage(int id, int flag)
{
    if (Help.state == HELP_STATE_IDLE && Help.message_id == HELP_NO_MESSAGE) {
        if (musicGlobals.speech.handle == 0 && musicGlobals.queuedSpeech == HELP_NO_MESSAGE) {
            if (HelpDataMessages[flag].timesUsed != HELP_TIMES_USED_MAX) {
                Help.message_id = id;
                Help.message_flg = flag;
                Help_AddToLog(id);
                return 1;
            }
        }
    }

    return 0;
}

void Help_Kill(void)
{
    if (Help.state != HELP_STATE_IDLE) {
        int vag = HelpMsgs[Help.message_index].vag;

        if (vag != HELP_NO_VAG) {
            if (vag == musicGlobals.speech.track - MUSIC_SPEECH_ID_BASE) {
                if ((unsigned short)(musicGlobals.speech.status - MUSIC_STATE_FINISHING) >= 2) {
                    musicGlobals.speech.status = MUSIC_STATE_STOPPING;
                }
            }
        }

        Help.state = HELP_STATE_IDLE;
        Help.message_id = HELP_NO_MESSAGE;
        Help.message_index = HELP_NO_MESSAGE;
        Help.counter = 0;
    }
}

void Help_ClearUsedSinceDeath(void)
{
    int i;

    for (i = 0; i < HELP_DATUM_COUNT; i++) {
        HelpDataMessages[i].level_die &= ~HELP_LEVEL_DIE_USED;
    }
}

int Help_FindIndex(int id)
{
    int found = -1;
    int index = 0;

    if (Help.num_message > 0) {
        if (HelpMsgs[0].id == id) {
            found = 0;
        } else {
        next:
            index++;
            if (index < Help.num_message) {
                if (HelpMsgs[index].id == id) {
                    found = index;
                } else {
                    goto next;
                }
            }
        }
    }

    return found;
}

char *msg_string(int id)
{
    static char not_found[] = "Paradox: This message does not exist";

    int index = Help_FindIndex(id);

    if (index >= 0) {
        return HelpMsgs[index].text;
    }

    return not_found;
}

void Help_Suspend(void)
{
    if (Help.suspend == 0) {
        Help.suspend = 1;
        Help.suspend_timer = FastScaleRoundInt(HELP_SUSPEND_FRAMES);

        Help_Skip();

        if (Help.state == HELP_STATE_IDLE) {
            Help.state = HELP_STATE_SUSPENDED;
        }
    }
}

void Help_Resume(void)
{
    Help.suspend = 0;
}

void Help_StartMessageBox(void)
{
    FontWindow window;
    char *text;
    int screenHeight;
    int top;
    int halfHeight;
    short textWidth;
    short textHeight;

    Help.state = HELP_STATE_BOX_OPENING;
    Help.counter = 0;

    if (sceneHelpMsgFlag1 != 0 || sceneHelpMsgFlag0 != 0) {
        sound_LevelPlay(0, 1, 0);
    }

    text = HelpMsgs[Help.message_index].text;
    SetFontWindow(&window, 0xF0, 0x1E0, 0x2C, 0x1D4, HELP_BOX_CENTER_X, 0x168, 0x10, 7);
    FontPrintWindowSmall(&window, HELP_TEXT_COLOR, text, -1);

    screenHeight = Scrn.paramY;
    textWidth = window.max_width;
    textHeight = window.max_height;
    halfHeight = (textHeight >> 1) + HELP_BOX_PADDING_Y;
    top = screenHeight - HELP_BOX_BOTTOM_OFFSET;

    Help.half_width = (textWidth >> 1) + HELP_BOX_PADDING_X;
    Help.half_height = halfHeight;
    Help.center_x = HELP_BOX_CENTER_X;
    Help.frame_half_width = HELP_BOX_START_HALF_SIZE;
    Help.frame_half_height = HELP_BOX_START_HALF_SIZE;
    Help.center_y = top;

    if (screenHeight - HELP_BOX_BOTTOM_MARGIN < top + halfHeight) {
        Help.center_y = screenHeight - HELP_BOX_BOTTOM_MARGIN - halfHeight;
    }
}

// Every message that is shown counts as used, is stamped with the play time (in
// minutes) it was last shown at and is marked as seen in the current level.
static inline void Help_RecordUse(void)
{
    HelpDatum *datum = &HelpDataMessages[Help.message_flg];

    if (datum->timesUsed < HELP_TIMES_USED_MAX) {
        datum->timesUsed++;
    }
}

static inline void Help_RecordTime(void)
{
    if (FastScaleRoundInt(TotalPlayTime) / HELP_FRAMES_PER_MINUTE > HelpDataMessages[Help.message_flg].lastTime) {
        HelpDataMessages[Help.message_flg].lastTime = FastScaleRoundInt(TotalPlayTime) / HELP_FRAMES_PER_MINUTE;
    }
}

static inline void Help_RecordLevel(void)
{
    HelpDataMessages[Help.message_flg].level_die = HelpDataMessages[Help.message_flg].level_die | (1 << Level) | HELP_LEVEL_DIE_USED;
}

void Help_Update(void)
{
    if (Help.ready == 0) {
        if (Help.ready_timer == 0 && (padState.bits & PAD_DPAD)) {
            Help.ready_timer = 1;
        }

        if (Help.ready_timer != 0) {
            if (++Help.ready_timer >= FastScaleRoundInt(HELP_READY_FRAMES)) {
                Help.ready = 1;
            }
        }
    }

    if (gameMode != 0 || Help.ready == 0) {
        Help.message_id = HELP_NO_MESSAGE;
        Help.state = HELP_STATE_IDLE;
        Help.counter = 0;
        return;
    }

    Help.counter++;

    switch (Help.state) {
    case HELP_STATE_SUSPENDED:
        if (Help.suspend != 0) {
            break;
        }

        if (Help.message_index >= 0) {
            if (Help.text_shown == 0) {
                if (FastDecTimer(Help.suspend_timer) != 0) {
                    Help_StartMessageBox();
                    Help.text_shown++;
                }
                break;
            }

            Help_RecordUse();
        }

        Help_RecordTime();
        Help_RecordLevel();
        Help.message_index = HELP_NO_MESSAGE;
        Help.state = HELP_STATE_IDLE;
        Help.text_shown = 0;
        break;

    case HELP_STATE_IDLE:
        if (Help.message_id >= 0) {
            Help.message_index = Help_FindIndex(Help.message_id);
            Help.message_id = HELP_NO_MESSAGE;

            if (Help.message_index >= 0) {
                Help_StartMessageBox();
            }
        }
        break;

    case HELP_STATE_BOX_OPENING: {
        int vag;

        MB_RequestHelpMessage(HELP_MESSAGE_SELECTOR, 0);

        vag = HelpMsgs[Help.message_index].vag;
        if (vag >= 0 && musicGlobals.speech.handle == 0 && musicGlobals.queuedSpeech == -1) {
            musicGlobals.queuedSpeech = vag + MUSIC_SPEECH_ID_BASE;
        }

        if (padState.bitsOn & PAD_TRIANGLE) {
            Help_RecordUse();
            Help_RecordTime();
            Help_RecordLevel();
            Help.counter = HELP_TRANSITION_FRAMES - Help.counter;
            Help.state = HELP_STATE_BOX_CLOSING;
        } else if (Help.counter >= HELP_BOX_OPEN_FRAMES) {
            Help.counter = 0;
            Help.state = HELP_STATE_PROMPT;
        }
        break;
    }

    case HELP_STATE_PROMPT: {
        int vag;

        MB_RequestHelpMessage(HELP_MESSAGE_SELECTOR, 0);

        if (padState.bitsOn & PAD_TRIANGLE) {
            Help_RecordUse();
            Help_RecordTime();
            Help.state = HELP_STATE_BOX_CLOSING;
            Help.counter = 0;
            Help_RecordLevel();
        } else if (Help.counter >= FastScaleRoundInt(HELP_PROMPT_FRAMES)) {
            if (musicGlobals.speech.status == MUSIC_STATE_READY || (vag = HelpMsgs[Help.message_index].vag) == -1 || vag != musicGlobals.speech.track - MUSIC_SPEECH_ID_BASE) {
                Help.state = HELP_STATE_PROMPT_TO_BOX;
                Help.counter = 0;
            }
        }
        break;
    }

    case HELP_STATE_PROMPT_TO_BOX:
        MB_RequestHelpMessage(HELP_MESSAGE_SELECTOR, 0);

        if (padState.bitsOn & PAD_TRIANGLE) {
            Help_RecordUse();
            Help_RecordTime();
            Help.state = HELP_STATE_BOX_CLOSING;
            Help.counter = 0;
            Help_RecordLevel();
        } else if (Help.counter >= HELP_TRANSITION_FRAMES) {
            Help.counter = 0;
            Help.state = HELP_STATE_TEXT_FADE_IN;
        }
        break;

    case HELP_STATE_TEXT_FADE_IN: {
        int vag;

        MB_RequestHelpMessage(HELP_MESSAGE_SELECTOR, 0);

        if (padState.bitsOn & PAD_TRIANGLE) {
            Help_RecordUse();
            Help_RecordTime();
            Help.state = HELP_STATE_TEXT_FADE_OUT;
            Help_RecordLevel();
            Help.counter = HELP_TEXT_FADE_FRAMES - Help.counter;
        } else if (Help.counter >= HELP_TEXT_FADE_FRAMES) {
            vag = HelpMsgs[Help.message_index].vag;
            if (vag != -1 && vag == musicGlobals.speech.track - MUSIC_SPEECH_ID_BASE && musicGlobals.speech.status == MUSIC_STATE_READY) {
                music_PlayPreseekedSpeech();
            }
            Help.state = HELP_STATE_TEXT_SHOWN;
            Help.counter = 0;
        }
        break;
    }

    case HELP_STATE_TEXT_SHOWN: {
        int vag;

        MB_RequestHelpMessage(HELP_MESSAGE_SELECTOR, 0);

        if ((Help.counter >= FastScaleRoundInt(HELP_TEXT_SHOWN_FRAMES) && ((vag = HelpMsgs[Help.message_index].vag) == -1 || vag != musicGlobals.speech.track - MUSIC_SPEECH_ID_BASE || (musicGlobals.speech.handle == 0 && musicGlobals.queuedSpeech == -1))) || (padState.bitsOn & PAD_TRIANGLE)) {
            Help_RecordUse();
            Help_RecordTime();
            Help.state = HELP_STATE_TEXT_FADE_OUT;
            Help.counter = 0;
            Help_RecordLevel();
        }
        break;
    }

    case HELP_STATE_TEXT_FADE_OUT:
        if (sceneHelpMsgFlag1 == 0 || Help.counter >= HELP_TEXT_FADE_FRAMES || (padState.bitsOn & PAD_TRIANGLE)) {
            Help.state = HELP_STATE_BOX_CLOSING;
            Help.counter = 0;
        }
        break;

    case HELP_STATE_BOX_CLOSING: {
        int vag;

        MB_RequestHelpMessage(HELP_MESSAGE_SELECTOR, 0);

        vag = HelpMsgs[Help.message_index].vag;
        if (vag != -1 && vag == musicGlobals.speech.track - MUSIC_SPEECH_ID_BASE && (unsigned short)(musicGlobals.speech.status - MUSIC_STATE_FINISHING) >= 2) {
            musicGlobals.speech.status = MUSIC_STATE_STOPPING;
        }

        if (Help.counter >= HELP_TRANSITION_FRAMES) {
            if (Help.suspend != 0) {
                Help.state = HELP_STATE_SUSPENDED;
            } else {
                Help.state = HELP_STATE_IDLE;
                Help.message_index = HELP_NO_MESSAGE;
            }
            Help.counter = 0;
        }
        break;
    }
    }
}

void Help_DrawIconBox(void)
{
    int alpha;

    Help.frame_half_width = HELP_ICON_HALF_SIZE;
    Help.frame_half_height = HELP_ICON_HALF_SIZE;

    DrawTextShadow(Help.center_y - HELP_ICON_HALF_SIZE, Help.center_y + HELP_ICON_HALF_SIZE, Help.center_x - HELP_ICON_HALF_SIZE, Help.center_x + HELP_ICON_HALF_SIZE, HELP_FRAME_ALPHA);

    if (Help.state == HELP_STATE_BOX_OPENING || Help.state == HELP_STATE_BOX_CLOSING) {
        alpha = Help.counter * HELP_ICON_FADE_STEP;
    } else {
        alpha = HELP_ICON_ALPHA;
    }

    if (alpha > HELP_ALPHA_OPAQUE) {
        alpha = HELP_ALPHA_OPAQUE;
    }

    DrawSprite(Help.center_x - HELP_ICON_HALF_SIZE, Help.center_y - HELP_ICON_HALF_SIZE, HELP_ICON_SIZE, HELP_ICON_SIZE, 0, 0, HELP_ICON_SIZE, HELP_ICON_SIZE, (alpha << 24) | HELP_SPRITE_RGB, FontSet(HELP_ICON_FONT));
}

void Help_Draw(void)
{
    if (Help.state == HELP_STATE_IDLE) {
        return;
    }

    if (Help.ready == 0) {
        return;
    }

    if (sceneHelpMsgFlag1 == 0 && sceneHelpMsgFlag0 == 0) {
        return;
    }

    switch (Help.state) {
    case HELP_STATE_BOX_OPENING:
        if (sceneHelpMsgFlag1) {
            int extent = Help.counter * 4 + HELP_BOX_START_HALF_SIZE;

            Help.frame_half_width = extent;
            Help.frame_half_height = extent;
            DrawTextShadow(Help.center_y - extent, Help.center_y + extent, Help.center_x - extent, Help.center_x + extent, HELP_FRAME_ALPHA);
        }
        break;
    case HELP_STATE_PROMPT:
        if (sceneHelpMsgFlag1) {
            Help_DrawIconBox();
        }
        break;
    case HELP_STATE_PROMPT_TO_BOX:
        if (sceneHelpMsgFlag1) {
            int halfWidth = (Help.half_width - HELP_ICON_HALF_SIZE) * Help.counter / HELP_TRANSITION_FRAMES + HELP_ICON_HALF_SIZE;
            int halfHeight = (Help.half_height - HELP_ICON_HALF_SIZE) * Help.counter / HELP_TRANSITION_FRAMES + HELP_ICON_HALF_SIZE;
            int alpha;

            Help.frame_half_width = halfWidth;
            Help.frame_half_height = halfHeight;
            DrawTextShadow(Help.center_y - halfHeight, Help.center_y + halfHeight, Help.center_x - halfWidth, Help.center_x + halfWidth, HELP_FRAME_ALPHA);

            alpha = (HELP_TRANSITION_FRAMES - Help.counter) * 16;
            if (alpha < 0) {
                alpha = 0;
            }

            DrawSprite(Help.center_x - HELP_ICON_HALF_SIZE, Help.center_y - HELP_ICON_HALF_SIZE, HELP_ICON_SIZE, HELP_ICON_SIZE, 0, 0, HELP_ICON_SIZE, HELP_ICON_SIZE, (alpha << 24) | HELP_SPRITE_RGB, FontSet(HELP_ICON_FONT));
        }
        break;
    case HELP_STATE_TEXT_FADE_IN:
    case HELP_STATE_TEXT_SHOWN:
    case HELP_STATE_TEXT_FADE_OUT:
        if (sceneHelpMsgFlag1) {
            FontWindow window;
            int color = HELP_TEXT_COLOR;
            char *text;

            Help.frame_half_width = Help.half_width;
            Help.frame_half_height = Help.half_height;
            DrawTextShadow(Help.center_y - Help.half_height, Help.center_y + Help.half_height, Help.center_x - Help.half_width, Help.center_x + Help.half_width, HELP_FRAME_ALPHA);

            if (Help.state == HELP_STATE_TEXT_FADE_IN) {
                color = HELP_TEXT_RGB | (Help.counter << 29);
            } else if (Help.state == HELP_STATE_TEXT_FADE_OUT) {
                color = ((HELP_TEXT_FADE_FRAMES - Help.counter) << 29) | HELP_TEXT_RGB;
            }

            text = HelpMsgs[Help.message_index].text;
            SetFontWindow(&window, 0xF0, 0x1E0, 0x2C, 0x1D4, HELP_BOX_CENTER_X, Help.center_y, 0x10, 3);
            FontPrintWindowSmall(&window, color, text, -1);
        }
        break;
    case HELP_STATE_BOX_CLOSING:
        if (sceneHelpMsgFlag1) {
            int halfWidth = Help.frame_half_width - (Help.frame_half_width - HELP_BOX_START_HALF_SIZE) * Help.counter / HELP_TRANSITION_FRAMES;
            int halfHeight = Help.frame_half_height - (Help.frame_half_height - HELP_BOX_START_HALF_SIZE) * Help.counter / HELP_TRANSITION_FRAMES;

            DrawTextShadow(Help.center_y - halfHeight, Help.center_y + halfHeight, Help.center_x - halfWidth, Help.center_x + halfWidth, (HELP_TRANSITION_FRAMES - Help.counter) * 12);
        }
        break;
    }
}

int Help_FindPairIndex(short id, int reverse, unsigned short *other)
{
    int i;

    for (i = 0; i < HELP_PAIR_COUNT; i++) {
        if (HelpPairs[i].column[reverse] == id) {
            if (other != 0) {
                *other = HelpPairs[i].column[reverse ? 0 : 1];
            }

            return i;
        }
    }

    return -1;
}

void Help_AddToLog(int id)
{
    int slot = Help_FindPairIndex(id, 0, 0);
    int i;

    if (slot == -1) {
        return;
    }

    for (i = 0; activeMessageRecords[i] != slot && i < activeMessageRecordCount; i++) {
    }

    if (i < activeMessageRecordCount) {
        for (; i < activeMessageRecordCount - 1; i++) {
            activeMessageRecords[i] = activeMessageRecords[i + 1];
        }

        activeMessageRecords[i] = 0;
        activeMessageRecordCount--;
    }

    activeMessageRecords[activeMessageRecordCount] = slot;
    activeMessageRecordCount++;
}
