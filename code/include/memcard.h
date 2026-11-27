#ifndef MEMCARD_H
#define MEMCARD_H

#include "sce.h"
#include "libmc.h"

#define MEMCARD_SAVE_SLOTS 5

// What the save menu shows for one save slot (DL memcard_saveinfo, without
// savedDifficultyLevel).
struct memcard_saveinfo {
    int level;
    int bolts;
    int completes;
    int elapsedTime;
    sceCdCLOCK saveTime;
    int bad;
};

// One memory card port (DL memcard_data, cut down for RC1).
struct memcard_data {
    int port;
    int slot;
    int type;
    int free;
    int format;
    int saveslot;
    int curslot;     // save slot being scanned for the load menu
    int result;     // last sceMcGetInfo result: 0 same card, -1 new formatted card, -2 unformatted
    memcard_saveinfo info[MEMCARD_SAVE_SLOTS];
    int oldsave;    // number of save chunks that didn't match the current layout
    int gamesize;   // from the save file header
    int levelsize;
};

// One block of game state that goes into a save, listed in mc_gamedata and
// mc_leveldata. A table ends with a null addr.
struct mc_data {
    void *addr;
    int size;
    int iff;        // chunk id written in front of the data
    int mark;       // set by memcard_RestoreData: 1 same size, -1 shorter, -2 longer
};

// Whole-save payload: block sizes followed by game data and per-level blocks.
struct mc_save_header {
    int gameSize;
    int levelSize;
};

// Header enclosing a checksummed sequence of mc_chunk records.
struct mc_block_header {
    int size;
    int checksum;
};

// One chunk in a save block: its id, size, then the data.
struct mc_chunk {
    int iff;
    int size;
};

// Field names follow DL's memcard_globals.
struct memcard_globals {
    memcard_data memcards[1];
    int cmd;
    int res;
    int useslot;
    int slot;
    int level;
    int sync;
    int file;
    int stage;
    int substage;
    int nextstage;
    int nextslot;
    int err;
    int errslot;
    char *addr;
    int size;
    int autosave;
};

// Values of sceMcGetInfo's result, kept in memcard_data::result.
#define MC_RESULT_SAME_CARD 0
#define MC_RESULT_NEW_CARD -1
#define MC_RESULT_UNFORMATTED -2

// memcard_globals::stage / nextstage values: the card operation memcard_Update
// is running. substage is the step within it.
enum mc_stage {
    MC_STAGE_GET_INFO = 0x0,
    MC_STAGE_GET_INFO_DONE = 0x1,
    MC_STAGE_IDLE = 0x2,
    MC_STAGE_FORMAT = 0x3,
    MC_STAGE_FORMAT_DONE = 0x4,
    MC_STAGE_UNFORMAT = 0x5,
    MC_STAGE_UNFORMAT_DONE = 0x6,
    MC_STAGE_CHECK_SAVE = 0x7,
    MC_STAGE_CHECKING_SAVE = 0x8,
    MC_STAGE_CREATE_SAVE = 0x9,
    MC_STAGE_CREATING_SAVE = 0xA,
    MC_STAGE_DELETE_SAVE = 0xB,
    MC_STAGE_DELETING_SAVE = 0xC,
    MC_STAGE_LOAD = 0xD,
    MC_STAGE_LOADING = 0xE,
    MC_STAGE_SAVE = 0xF,
    MC_STAGE_SAVING = 0x10,
    MC_STAGE_READ_BLANK_SAVE = 0x11,
    MC_STAGE_READING_BLANK_SAVE = 0x12,
    MC_STAGE_WRITE_WHOLE_SAVE = 0x13,
    MC_STAGE_WRITING_WHOLE_SAVE = 0x14,
    MC_STAGE_SCAN_SLOTS = 0x15,
    MC_STAGE_NEXT_SLOT = 0x16,
    MC_STAGE_READ_SLOT_INFO = 0x17
};

enum mc_check_step {
    MC_CHECK_CHDIR_DONE = 0x0,
    MC_CHECK_OPEN = 0x1,
    MC_CHECK_OPEN_DONE = 0x2,
    MC_CHECK_READ_HEADER = 0x3,
    MC_CHECK_READ_HEADER_DONE = 0x4,
    MC_CHECK_CLOSE = 0x5
};

enum mc_create_step {
    MC_CREATE_CHECK_SPACE = 0x0,
    MC_CREATE_MKDIR = 0x1,
    MC_CREATE_MKDIR_DONE = 0x2,
    MC_CREATE_LOAD_FILES = 0x3,
    MC_CREATE_LOADING_FILES = 0x4,
    MC_CREATE_OPEN_ICON_SYS = 0x5,
    MC_CREATE_WRITE_ICON_SYS = 0x6,
    MC_CREATE_CLOSE_ICON_SYS = 0x7,
    MC_CREATE_ICON_SYS_DONE = 0x8,
    MC_CREATE_OPEN_ICON = 0x9,
    MC_CREATE_WRITE_ICON = 0xA,
    MC_CREATE_CLOSE_ICON = 0xB,
    MC_CREATE_ICON_DONE = 0xC,
    MC_CREATE_OPEN_SLOT = 0xD,
    MC_CREATE_WRITE_SLOT = 0xE,
    MC_CREATE_CLOSE_SLOT = 0xF,
    MC_CREATE_SLOT_DONE = 0x10,
    MC_CREATE_NEXT_SLOT = 0x11,
    MC_CREATE_OPEN_MAIN = 0x12,
    MC_CREATE_WRITE_MAIN = 0x13,
    MC_CREATE_CLOSE_MAIN = 0x14,
    MC_CREATE_DONE = 0x15
};

enum mc_delete_step {
    MC_DELETE_FIRST_FILE = 0x0,
    MC_DELETE_FILE = 0x1,
    MC_DELETE_NEXT_FILE = 0x2,
    MC_DELETE_FOLDER = 0x3,
    MC_DELETE_FOLDER_DONE = 0x4
};

enum mc_load_step {
    MC_LOAD_OPEN = 0x0,
    MC_LOAD_OPEN_DONE = 0x1,
    MC_LOAD_READ_HEADER = 0x2,
    MC_LOAD_READ_HEADER_DONE = 0x3,
    MC_LOAD_READ_GAME = 0x4,
    MC_LOAD_READ_GAME_DONE = 0x5,
    MC_LOAD_READ_LEVEL = 0x6,
    MC_LOAD_READ_LEVEL_DONE = 0x7,
    MC_LOAD_CLOSE = 0x8
};

enum mc_save_step {
    MC_SAVE_OPEN = 0x0,
    MC_SAVE_OPEN_DONE = 0x1,
    MC_SAVE_SKIP_HEADER = 0x2,
    MC_SAVE_SKIP_HEADER_DONE = 0x3,
    MC_SAVE_WRITE_GAME = 0x4,
    MC_SAVE_WRITE_GAME_DONE = 0x5,
    MC_SAVE_SEEK_LEVEL = 0x6,
    MC_SAVE_SEEK_LEVEL_DONE = 0x7,
    MC_SAVE_WRITE_LEVEL = 0x8,
    MC_SAVE_WRITE_LEVEL_DONE = 0x9,
    MC_SAVE_CLOSE = 0xA
};

enum mc_write_step {
    MC_WRITE_OPEN = 0x0,
    MC_WRITE_WRITE = 0x1,
    MC_WRITE_CLOSE = 0x2,
    MC_WRITE_DONE = 0x3
};



// Free space (in KB) a save needs.
#define MC_SAVE_SIZE 0x15E

extern memcard_globals g_memcard;
extern mc_data mc_gamedata[];
extern mc_data mc_leveldata[];
extern int g_loaderr;

// What GetSaveBuffers hands back for the boot WAD's memory card file: the
// icon.sys, the static icon and a blank whole save, each found by offset.
struct mc_resource {
    int iconSysOffset;
    int unk_4;
    int staticIconOffset;
    int staticIconSize;
    int saveDataOffset;
};

// Sizes of mc_gameprepbuff and mc_levelprepbuff.
#define MC_GAME_DATA_SIZE 0x1800
#define MC_LEVEL_DATA_SIZE 0x1000

// The directory listing memcard_Update deletes a save folder through.
extern sceMcTblGetDir mc_dirEntry[];


// Staging buffers memcard_Save packs the game and level blocks into.
extern char mc_gameprepbuff[];
extern char mc_levelprepbuff[];

// Game state that goes into a save slot's summary.
extern sceCdCLOCK LastSaveTime;
extern unsigned char LevelVisited[];
extern int HeroBolts;
extern int ElapsedTime;
extern int ChallengeMode;

// Memory card paths, patched with the disc's product code by memcard_GetName.
extern char SAVEGAME_NAME[];
extern char SAVEGAME_WILD[];
extern char SAVEGAME_SYS[];
extern char SAVEGAME_VIEW[];
extern char SAVEGAME_MAIN[];
extern char SAVEGAME_SLOT[];

// Largest save block memcard_Checksum accepts.
#define MEMCARD_CHECKSUM_LIMIT 0x1800

// Number of levels with their own block in a whole save.
#define MEMCARD_LEVEL_COUNT 20

void memcard_GetName(char *buff);
void memcard_RestoreGame(char *addr);
void memcard_ResetGame(void);
void memcard_Update(void);
void memcard_MakeWholeSave(char *addr);
void memcard_Init(void);
int memcard_GetDataSize(mc_data *mcd);
int memcard_Checksum(char *data, int size);
int memcard_TestChecksum(char *addr);
int memcard_PrepData(char *addr, int index, mc_data *mcd);
void memcard_RestoreInfo(char *addr, int slot, int index);
int memcard_RestoreData(char *addr, int index, mc_data *mcd);
int memcard_Save(int flags, int slot);

#endif
