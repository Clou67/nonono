#include "common.h"
#include "help.h"
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
    {3, 21106}, {0, 21103}, {1, 21104}, {2, 21105},
    {1000, 21107}, {1001, 21108}, {1002, 21109}, {1003, 21110},
    {4, 21111}, {5, 21112}, {2000, 21113}, {2001, 21114},
    {2002, 21115}, {2003, 21116}, {2004, 21117}, {2005, 21118},
    {2006, 21119}, {2007, 21120}, {2008, 21121}, {2009, 21122},
    {3000, 21123}, {3001, 21124}, {3002, 21125}, {3003, 21126},
    {3004, 21127}, {3005, 21128}, {3006, 21129}, {3007, 21130},
    {4000, 21131}, {4001, 21132}, {4002, 21133}, {4003, 21134},
    {4004, 21135}, {5000, 21136}, {5001, 21137}, {5002, 21138},
    {5003, 21139}, {5004, 21140}, {5005, 21141}, {6000, 21142},
    {6001, 21143}, {6002, 21144}, {6003, 21145}, {6004, 21146},
    {6005, 21147}, {6006, 21148}, {6007, 21149}, {6008, 21150},
    {8000, 21151}, {8001, 21152}, {8002, 21153}, {8003, 21154},
    {9000, 21155}, {10000, 21156}, {10001, 21157}, {10002, 21158},
    {10003, 21159}, {10004, 21160}, {11000, 21161}, {11001, 21162},
    {11002, 21163}, {11003, 21164}, {12000, 21165}, {12001, 21166},
    {1004, 21167}, {1005, 21168}, {1006, 21169}, {1007, 21170},
    {1008, 21171}, {2010, 21172}, {2011, 21173}, {2012, 21174},
    {2013, 21175}, {4005, 21176}, {20000, 21177}, {20001, 21178},
    {20002, 21179}, {20003, 21180}, {20004, 21181}, {20005, 21182},
    {20006, 21183}, {20007, 21184}, {6009, 21185}, {6010, 21186},
    {3008, 21187}, {11004, 21188}, {11005, 21189}, {11006, 21190},
    {11007, 21191}, {11008, 21192}, {8004, 21193}, {9001, 21194},
    {10005, 21195}, {12002, 21196}, {5006, 21197}, {5007, 21198},
    {3009, 21199}, {5008, 21200}, {3010, 21201}, {3011, 21202},
    {5009, 21203}, {3012, 21204}, {5010, 21205}, {5011, 21206},
    {3013, 21207}, {10006, 21208}, {10007, 21209}, {10008, 21210},
    {11009, 21211}, {12003, 21212}, {12004, 21213}, {13000, 21214},
    {8005, 21215}, {11010, 21216}, {20008, 21217}, {20009, 21218},
    {20010, 21219}, {20011, 21220}, {20012, 21221}, {20013, 21222},
    {20014, 21223}, {20015, 21224}, {14000, 21225}, {15000, 21226},
    {15001, 21227}, {15002, 21228}, {16000, 21229}, {15003, 21230},
    {15004, 21231}, {20016, 21232}, {15005, 21233}, {16001, 21234},
    {16002, 21235}, {18000, 21236}, {11011, 21237}, {16003, 21238},
    {15006, 21239}, {15007, 21240}, {15008, 21241}, {17000, 21242},
    {18001, 21243}, {18002, 21244}, {8006, 21245}, {16004, 21246},
    {2014, 21247}, {20017, 21248}, {20018, 21249}, {20019, 21250},
    {0, 0}, {0, 0},
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
        if (musicTransition.speechHandle == 0 && musicTransition.unk1C == HELP_NO_MESSAGE) {
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
            if (vag == musicTransition.speechId - MUSIC_SPEECH_ID_BASE) {
                if ((unsigned short)(musicTransition.state - MUSIC_STATE_FINISHING) >= 2) {
                    musicTransition.state = MUSIC_STATE_STOPPING;
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
        if (vag >= 0 && musicTransition.speechHandle == 0 && musicTransition.unk1C == -1) {
            musicTransition.unk1C = vag + MUSIC_SPEECH_ID_BASE;
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
            if (musicTransition.state == MUSIC_STATE_READY || (vag = HelpMsgs[Help.message_index].vag) == -1 || vag != musicTransition.speechId - MUSIC_SPEECH_ID_BASE) {
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
            if (vag != -1 && vag == musicTransition.speechId - MUSIC_SPEECH_ID_BASE && musicTransition.state == MUSIC_STATE_READY) {
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

        if ((Help.counter >= FastScaleRoundInt(HELP_TEXT_SHOWN_FRAMES) && ((vag = HelpMsgs[Help.message_index].vag) == -1 || vag != musicTransition.speechId - MUSIC_SPEECH_ID_BASE || (musicTransition.speechHandle == 0 && musicTransition.unk1C == -1))) || (padState.bitsOn & PAD_TRIANGLE)) {
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
        if (vag != -1 && vag == musicTransition.speechId - MUSIC_SPEECH_ID_BASE && (unsigned short)(musicTransition.state - MUSIC_STATE_FINISHING) >= 2) {
            musicTransition.state = MUSIC_STATE_STOPPING;
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
