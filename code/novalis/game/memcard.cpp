#include "common.h"
#include "memcard.h"
#include "fastfunc.h"
#include "libc.h"
#include "wad.h"
#include "freeze.h"
#include "galaxymap.h"
#include "music.h"
#include "vuchain.h"
#include "mcstate.h"
#include "map.h"
#include "pause.h"

#define CURRENT_CARD g_memcard.memcards[g_memcard.slot]

// Save chunks whose data differed from what was already in memory on the last restore.
int g_loaderr = 0;

void memcard_GetName(char *buff)
{
    int position;
    unsigned char region = buff[0x12];

    if (region == 'E') {
        SAVEGAME_NAME[2] = region;
    }

    for (position = 3; position < 7; position++) {
        SAVEGAME_NAME[position] = buff[position + 0xD];
    }

    for (position = 8; position < 11; position++) {
        SAVEGAME_NAME[position] = buff[position + 0xD];
    }

    for (position = 11; position < 13; position++) {
        SAVEGAME_NAME[position] = buff[position + 0xE];
    }

    strncpy(SAVEGAME_WILD, SAVEGAME_NAME, 13);
    strncpy(SAVEGAME_SYS, SAVEGAME_NAME, 13);
    strncpy(SAVEGAME_VIEW, SAVEGAME_NAME, 13);
    strncpy(SAVEGAME_MAIN, SAVEGAME_NAME, 13);
    strncpy(SAVEGAME_MAIN + 0x14, SAVEGAME_NAME, 13);
    strncpy(SAVEGAME_SLOT, SAVEGAME_NAME, 13);
}

TEXT_PADDING(0x27BD0060, 0x00000000);

void memcard_RestoreGame(char *addr)
{
    int gameSize = memcard_GetDataSize(mc_gamedata);
    int levelSize = memcard_GetDataSize(mc_leveldata);

    if (*(int *)addr != gameSize || *(int *)(addr + 4) != levelSize) {
        printf_stub("Out of date save!\n");
        return;
    }

    addr += 8;
    memcard_RestoreData(addr, 0, mc_gamedata);
    addr += gameSize;

    for (int level = 0; level < MEMCARD_LEVEL_COUNT; level++) {
        memcard_RestoreData(addr, level, mc_leveldata);
        addr += levelSize;
    }
}

void memcard_ResetGame(void)
{
    void *saveBuffer;
    void *secondBuffer;

    GetSaveBuffers(bootAssets.savegame.length << 11, &saveBuffer, &secondBuffer);
    music_Sync(1);
    music_LoadFileSync(saveBuffer, bootAssets.savegame.offset, bootAssets.savegame.length);
    memcard_RestoreGame((char *)saveBuffer + *(int *)((char *)saveBuffer + 0x10));
    Level = 0;
}

void memcard_Update(void)
{
    char name[0x40];

    if (g_memcard.sync) {
        g_memcard.sync = sceMcSync(1, &g_memcard.cmd, &g_memcard.res) == 0;
        return;
    }
    g_memcard.sync = 1;

    switch (g_memcard.stage) {
    case MC_STAGE_GET_INFO:
        if (g_memcard.slot < 0) {
            g_memcard.slot = 0;
        }
        if (sceMcGetInfo(CURRENT_CARD.port, CURRENT_CARD.slot, &CURRENT_CARD.type, &CURRENT_CARD.free, &CURRENT_CARD.format) == 0) {
            g_memcard.stage = MC_STAGE_GET_INFO_DONE;
        }
        break;

    case MC_STAGE_GET_INFO_DONE:
        if (g_memcard.res != 0) {
            CURRENT_CARD.saveslot = -3;
            CURRENT_CARD.result = g_memcard.res;
            CURRENT_CARD.oldsave = -1;
        }
        if (++g_memcard.slot < 1) {
            g_memcard.stage = MC_STAGE_GET_INFO;
        } else {
            g_memcard.stage = MC_STAGE_IDLE;
        }
        g_memcard.sync = 0;
        break;

    case MC_STAGE_IDLE:
        if (g_memcard.nextstage >= MC_STAGE_GET_INFO) {
            if (g_memcard.memcards[0].result == 0) {
                if (g_memcard.nextslot >= 0) {
                    g_memcard.slot = g_memcard.nextslot;
                    g_memcard.stage = g_memcard.nextstage;
                    g_memcard.err = 0;
                } else {
                    g_memcard.err = 0x271A;
                }
            }
            g_memcard.nextstage = -1;
            g_memcard.nextslot = -1;
        } else {
            if (++g_memcard.slot >= 31) {
                g_memcard.slot = 0;
                g_memcard.stage = MC_STAGE_GET_INFO;
            }
        }
        g_memcard.sync = 0;
        break;

    case MC_STAGE_FORMAT:
        if (CURRENT_CARD.format == 0) {
            if (sceMcFormat(CURRENT_CARD.port, CURRENT_CARD.slot) == 0) {
                g_memcard.stage = MC_STAGE_FORMAT_DONE;
            }
            break;
        }
        g_memcard.sync = 0;
        g_memcard.stage = MC_STAGE_IDLE;
        break;

    case MC_STAGE_FORMAT_DONE:
        if (g_memcard.res != 0) {
            g_memcard.err = 1;
            g_memcard.errslot = g_memcard.slot;
        }
        g_memcard.stage = MC_STAGE_GET_INFO;
        g_memcard.slot = 0;
        g_memcard.sync = 0;
        break;

    case MC_STAGE_UNFORMAT:
        if (CURRENT_CARD.format == 0) {
            if (sceMcUnformat(CURRENT_CARD.port, CURRENT_CARD.slot) == 0) {
                g_memcard.stage = MC_STAGE_UNFORMAT_DONE;
            }
            break;
        }
        g_memcard.sync = 0;
        g_memcard.stage = MC_STAGE_IDLE;
        break;

    case MC_STAGE_UNFORMAT_DONE:
        if (g_memcard.res != 0) {
            g_memcard.err = 2;
            g_memcard.errslot = g_memcard.slot;
        }
        g_memcard.stage = MC_STAGE_GET_INFO;
        g_memcard.slot = 0;
        g_memcard.sync = 0;
        break;

    case MC_STAGE_CHECK_SAVE:
        if (sceMcChdir(CURRENT_CARD.port, CURRENT_CARD.slot, SAVEGAME_NAME, 0) == 0) {
            g_memcard.substage = 0;
            g_memcard.stage = MC_STAGE_CHECKING_SAVE;
        }
        break;

    case MC_STAGE_CHECKING_SAVE:
        switch (g_memcard.substage) {
        case MC_CHECK_CHDIR_DONE:
            if (g_memcard.res == 0) {
                int *save_index_ptr = &CURRENT_CARD.saveslot;
                if (*save_index_ptr < 0) {
                    *save_index_ptr = -1;
                }
                g_memcard.sync = 0;
                g_memcard.substage = 1;
            } else {
                CURRENT_CARD.saveslot = -2;
                if (g_memcard.res == -2) {
                    g_memcard.err = 3;
                    g_memcard.errslot = g_memcard.slot;
                } else if (g_memcard.res != -4) {
                    g_memcard.err = 4;
                    g_memcard.errslot = g_memcard.slot;
                }
                g_memcard.stage = MC_STAGE_GET_INFO;
                g_memcard.slot = 0;
                g_memcard.sync = 0;
            }
            break;
        case MC_CHECK_OPEN:
            sprintf(name, SAVEGAME_SLOT, 0);
            if (sceMcOpen(CURRENT_CARD.port, CURRENT_CARD.slot, name, 1) == 0) {
                g_memcard.substage++;
            }
            break;
        case MC_CHECK_OPEN_DONE:
            if (g_memcard.res >= 0) {
                g_memcard.file = g_memcard.res;
                g_memcard.substage = 3;
            } else {
                CURRENT_CARD.saveslot = -2;
                g_memcard.errslot = g_memcard.slot;
                if (g_memcard.res == -7) {
                    g_memcard.err = 0x2710;
                } else if (g_memcard.res == -5) {
                    g_memcard.err = 0x2711;
                } else if (g_memcard.res == -4) {
                    g_memcard.err = 0x2712;
                } else if (g_memcard.res == -3) {
                    g_memcard.err = 0x2713;
                } else if (g_memcard.res == -2) {
                    g_memcard.err = 3;
                } else {
                    g_memcard.err = 4;
                }
                g_memcard.stage = MC_STAGE_GET_INFO;
                g_memcard.slot = 0;
            }
            g_memcard.sync = 0;
            break;
        case MC_CHECK_READ_HEADER:
            g_memcard.size = 8;
            if (sceMcRead(g_memcard.file, &CURRENT_CARD.gamesize, 8) == 0) {
                g_memcard.substage = 4;
            }
            break;
        case MC_CHECK_READ_HEADER_DONE:
            if (g_memcard.res == g_memcard.size) {
                CURRENT_CARD.oldsave = 0;
                if (CURRENT_CARD.gamesize != memcard_GetDataSize(mc_gamedata)) {
                    CURRENT_CARD.oldsave++;
                }
                if (CURRENT_CARD.levelsize != memcard_GetDataSize(mc_leveldata)) {
                    CURRENT_CARD.oldsave++;
                }
                g_memcard.sync = 0;
                g_memcard.substage = 5;
            } else {
                CURRENT_CARD.saveslot = -2;
                g_memcard.errslot = g_memcard.slot;
                if (g_memcard.res >= 0) {
                    g_memcard.err = 0x2716;
                    if (sceMcClose(g_memcard.file) == 0) {
                        g_memcard.stage = MC_STAGE_GET_INFO;
                        g_memcard.slot = 0;
                        g_memcard.sync = 0;
                    }
                    break;
                }
                if (g_memcard.res == -5) {
                    g_memcard.err = 0x2711;
                } else if (g_memcard.res == -4) {
                    g_memcard.err = 0x2714;
                } else if (g_memcard.res == -3) {
                    g_memcard.err = 0x2715;
                } else if (g_memcard.res == -2) {
                    g_memcard.err = 3;
                } else {
                    g_memcard.err = 4;
                }
                g_memcard.stage = MC_STAGE_GET_INFO;
                g_memcard.slot = 0;
                g_memcard.sync = 0;
            }
            break;
        case MC_CHECK_CLOSE:
            if (sceMcClose(g_memcard.file) == 0) {
                g_memcard.sync = 0;
                g_memcard.stage = MC_STAGE_SCAN_SLOTS;
            }
            break;
        }
        break;

    case MC_STAGE_CREATE_SAVE:
        g_memcard.stage = MC_STAGE_CREATING_SAVE;
        g_memcard.substage = 0;
        CURRENT_CARD.saveslot = 0;
    case MC_STAGE_CREATING_SAVE:
        switch (g_memcard.substage) {
        case MC_CREATE_CHECK_SPACE:
            if (CURRENT_CARD.free >= 350) {
                g_memcard.substage = 1;
            } else {
                g_memcard.err = 7;
                g_memcard.errslot = g_memcard.slot;
                g_memcard.stage = MC_STAGE_GET_INFO;
                g_memcard.slot = 0;
            }
            g_memcard.sync = 0;
            break;
        case MC_CREATE_MKDIR:
            if (sceMcMkdir(CURRENT_CARD.port, CURRENT_CARD.slot, SAVEGAME_NAME) == 0) {
                g_memcard.substage = 2;
            }
            break;
        case MC_CREATE_MKDIR_DONE:
            if (g_memcard.res == 0 || g_memcard.res == -4) {
                g_memcard.substage = 3;
                break;
            }
            g_memcard.errslot = g_memcard.slot;
            if (g_memcard.res == -3) {
                g_memcard.err = 7;
            } else if (g_memcard.res == -2) {
                g_memcard.err = 6;
            } else {
                g_memcard.err = 0xD;
            }
            g_memcard.stage = MC_STAGE_GET_INFO;
            g_memcard.slot = 0;
            g_memcard.sync = 0;
            break;
        case MC_CREATE_LOAD_FILES: {
            mc_resource *chunk;
            int      size;

            GetSaveBuffers(bootAssets.savegame.length << 11, (void **)&chunk, (void **)&size);
            music_LoadFile(
                chunk, bootAssets.savegame.offset, bootAssets.savegame.length);
            g_memcard.substage = 4;
            g_memcard.sync = 0;
            break;
        }
        case MC_CREATE_LOADING_FILES:
            if (CdReadActive[0] == 0) {
                g_memcard.substage = 5;
            }
            g_memcard.sync = 0;
            break;
        case MC_CREATE_OPEN_ICON_SYS:
        case MC_CREATE_OPEN_ICON:
        case MC_CREATE_OPEN_SLOT:
        case MC_CREATE_OPEN_MAIN:
            switch (g_memcard.substage) {
            case MC_CREATE_OPEN_ICON_SYS:
                strcpy(name, SAVEGAME_SYS);
                break;
            case MC_CREATE_OPEN_ICON:
                strcpy(name, SAVEGAME_VIEW);
                break;
            case MC_CREATE_OPEN_MAIN:
                strcpy(name, SAVEGAME_MAIN);
                break;
            case MC_CREATE_OPEN_SLOT:
                sprintf(name, SAVEGAME_SLOT, CURRENT_CARD.saveslot);
                break;
            }
            if (sceMcOpen(CURRENT_CARD.port, CURRENT_CARD.slot, name, 0x203) == 0) {
                g_memcard.file = -1;
                g_memcard.substage++;
            }
            break;
        case MC_CREATE_WRITE_ICON_SYS:
        case MC_CREATE_WRITE_ICON:
        case MC_CREATE_WRITE_SLOT:
        case MC_CREATE_WRITE_MAIN: {
            mc_resource *chunk;
            int      size;

            if (g_memcard.res >= 0) {
                if (g_memcard.file < 0) {
                    g_memcard.file = g_memcard.res;
                }
                GetSaveBuffers(bootAssets.savegame.length << 11, (void **)&chunk, (void **)&size);
                switch (g_memcard.substage) {
                case MC_CREATE_WRITE_ICON_SYS:
                    g_memcard.size = 0x3C4;
                    g_memcard.addr = (char *)chunk + chunk->iconSysOffset;
                    break;
                case MC_CREATE_WRITE_ICON:
                    g_memcard.size = chunk->staticIconSize;
                    g_memcard.addr = (char *)chunk + chunk->staticIconOffset;
                    break;
                case MC_CREATE_WRITE_MAIN:
                    if (pauseActionListMode != 0) {
                        g_memcard.size = 0x3C00;
                    } else {
                        g_memcard.size = 0x3C04;
                    }
                    g_memcard.addr = (char *)&Level;
                    break;
                case MC_CREATE_WRITE_SLOT: {
                    int n = memcard_GetDataSize(mc_gamedata);
                    g_memcard.size = n + memcard_GetDataSize(mc_leveldata) * 20 + 8;
                    g_memcard.addr = (char *)chunk + chunk->saveDataOffset;
                    break;
                }
                }
                if (sceMcWrite(g_memcard.file, g_memcard.addr, g_memcard.size) == 0) {
                    g_memcard.substage++;
                }
            } else {
                g_memcard.err = 0xA;
                g_memcard.errslot = g_memcard.slot;
                g_memcard.stage = MC_STAGE_GET_INFO;
                g_memcard.slot = 0;
                g_memcard.sync = 0;
            }
            break;
        }
        case MC_CREATE_CLOSE_ICON_SYS:
        case MC_CREATE_CLOSE_ICON:
        case MC_CREATE_CLOSE_SLOT:
        case MC_CREATE_CLOSE_MAIN:
            if (g_memcard.res == g_memcard.size) {
                if (sceMcClose(g_memcard.file) == 0) {
                    g_memcard.substage++;
                }
                break;
            }
            g_memcard.errslot = g_memcard.slot;
            if (g_memcard.res >= 0) {
                g_memcard.err = 0xB;
                if (sceMcClose(g_memcard.file) == 0) {
                    g_memcard.stage = MC_STAGE_GET_INFO;
                    g_memcard.slot = 0;
                    g_memcard.sync = 0;
                }
                break;
            }
            if (g_memcard.res == -4) {
                g_memcard.err = 8;
            } else if (g_memcard.res == -3) {
                g_memcard.err = 7;
            } else if (g_memcard.res == -2) {
                g_memcard.err = 6;
            } else {
                g_memcard.err = 0xD;
            }
            g_memcard.stage = MC_STAGE_GET_INFO;
            g_memcard.slot = 0;
            g_memcard.sync = 0;
            break;
        case MC_CREATE_ICON_SYS_DONE:
        case MC_CREATE_ICON_DONE:
        case MC_CREATE_SLOT_DONE:
            if (g_memcard.res == 0) {
                g_memcard.substage++;
            } else {
                g_memcard.err = 0xC;
                g_memcard.errslot = g_memcard.slot;
                g_memcard.stage = MC_STAGE_GET_INFO;
                g_memcard.slot = 0;
            }
            g_memcard.sync = 0;
            break;
        case MC_CREATE_NEXT_SLOT:
            if (++CURRENT_CARD.saveslot < 5) {
                g_memcard.substage = 13;
            } else {
                g_memcard.substage++;
            }
            g_memcard.sync = 0;
            break;
        case MC_CREATE_DONE:
            g_memcard.memcards[0].saveslot = -1;
            g_memcard.stage = MC_STAGE_GET_INFO;
            g_memcard.slot = 0;
            g_memcard.memcards[0].oldsave = 0;
            break;
        }
        break;

    case MC_STAGE_DELETE_SAVE:
        g_memcard.stage = MC_STAGE_DELETING_SAVE;
        g_memcard.substage = 0;
        CURRENT_CARD.saveslot = -2;
    case MC_STAGE_DELETING_SAVE:
        switch (g_memcard.substage) {
        case MC_DELETE_FIRST_FILE:
            if (sceMcGetDir(CURRENT_CARD.port, CURRENT_CARD.slot, SAVEGAME_WILD, 0, 1, mc_dirEntry) == 0) {
                g_memcard.substage = 1;
            }
            break;
        case MC_DELETE_FILE:
            if (g_memcard.res == 1) {
                sprintf(name, "%s/%s", SAVEGAME_NAME, (char *)mc_dirEntry[0].EntryName);
                printf_stub("deleting %s\n", name);
                if (sceMcDelete(CURRENT_CARD.port, CURRENT_CARD.slot, name) == 0) {
                    g_memcard.substage = 2;
                }
            } else {
                if (g_memcard.res == 0) {
                    g_memcard.substage = 3;
                } else {
                    g_memcard.errslot = g_memcard.slot;
                    if (g_memcard.res == -5) {
                        g_memcard.err = 0x10;
                    } else if (g_memcard.res == -4) {
                        g_memcard.err = 0xF;
                    } else if (g_memcard.res == -2) {
                        g_memcard.err = 0xE;
                    } else {
                        g_memcard.err = 0x12;
                    }
                    g_memcard.stage = MC_STAGE_GET_INFO;
                    g_memcard.slot = 0;
                }
                g_memcard.sync = 0;
            }
            break;
        case MC_DELETE_NEXT_FILE:
            if (sceMcGetDir(CURRENT_CARD.port, CURRENT_CARD.slot, SAVEGAME_WILD, 1, 1, mc_dirEntry) == 0) {
                g_memcard.substage = 1;
            }
            break;
        case MC_DELETE_FOLDER:
            if (sceMcDelete(CURRENT_CARD.port, CURRENT_CARD.slot, SAVEGAME_NAME) == 0) {
                printf_stub("deleting folder %s\n", SAVEGAME_NAME);
                g_memcard.substage = 4;
            }
            break;
        case MC_DELETE_FOLDER_DONE:
            if (g_memcard.res != 0) {
                g_memcard.errslot = g_memcard.slot;
                if (g_memcard.res == -6) {
                    g_memcard.err = 0x11;
                } else if (g_memcard.res == -5) {
                    g_memcard.err = 0x10;
                } else if (g_memcard.res == -4) {
                    g_memcard.err = 0xF;
                } else if (g_memcard.res == -2) {
                    g_memcard.err = 0xE;
                } else {
                    g_memcard.err = 0x12;
                }
            }
            g_memcard.stage = MC_STAGE_GET_INFO;
            g_memcard.slot = 0;
            g_memcard.sync = 0;
            break;
        }
        break;

    case MC_STAGE_SCAN_SLOTS:
        g_memcard.stage = MC_STAGE_NEXT_SLOT;
        CURRENT_CARD.curslot = -1;
        g_memcard.level = 0;
        break;

    case MC_STAGE_NEXT_SLOT:
        CURRENT_CARD.curslot++;
        if (CURRENT_CARD.curslot < 5) {
            g_memcard.substage = 0;
            g_memcard.stage = MC_STAGE_READ_SLOT_INFO;
        } else {
            g_memcard.stage = MC_STAGE_GET_INFO;
            g_memcard.slot = 0;
            g_memcard.sync = 0;
        }
        break;
    case MC_STAGE_LOAD:
        if (CURRENT_CARD.saveslot < 0) {
            g_memcard.sync = 0;
            g_memcard.stage = MC_STAGE_GET_INFO;
            g_memcard.slot = 0;
            g_memcard.err = 0x13;
            break;
        }
        g_memcard.level = 0;
        g_memcard.substage = 0;
        g_memcard.stage = MC_STAGE_LOADING;
    case MC_STAGE_LOADING:
    case MC_STAGE_READ_SLOT_INFO:
        switch (g_memcard.substage) {
        case MC_LOAD_OPEN:
            if (g_memcard.stage == MC_STAGE_READ_SLOT_INFO) {
                sprintf(name, SAVEGAME_SLOT, CURRENT_CARD.curslot);
            } else {
                sprintf(name, SAVEGAME_SLOT, CURRENT_CARD.saveslot);
            }
            if (sceMcOpen(CURRENT_CARD.port, CURRENT_CARD.slot, name, 1) == 0) {
                g_memcard.substage++;
            }
            break;
        case MC_LOAD_OPEN_DONE:
            if (g_memcard.res >= 0) {
                g_memcard.file = g_memcard.res;
                g_memcard.substage = 2;
            } else {
                g_memcard.errslot = g_memcard.slot;
                if (g_memcard.res == -7) {
                    g_memcard.err = 0x14;
                } else if (g_memcard.res == -5) {
                    g_memcard.err = 0x15;
                } else if (g_memcard.res == -4) {
                    g_memcard.err = 0x16;
                } else if (g_memcard.res == -3) {
                    g_memcard.err = 0x17;
                } else if (g_memcard.res == -2) {
                    g_memcard.err = 0x18;
                } else {
                    g_memcard.err = 0x1C;
                }
                g_memcard.stage = MC_STAGE_GET_INFO;
                g_memcard.slot = 0;
            }
            g_memcard.sync = 0;
            break;
        case MC_LOAD_READ_HEADER:
            g_memcard.size = 8;
            if (sceMcRead(g_memcard.file, &CURRENT_CARD.gamesize, 8) == 0) {
                g_memcard.substage = 3;
            }
            break;
        case MC_LOAD_READ_HEADER_DONE:
            if (g_memcard.res == g_memcard.size) {
                g_memcard.sync = 0;
                g_memcard.substage = 4;
                break;
            }
            g_memcard.errslot = g_memcard.slot;
            if (g_memcard.res >= 0) {
                g_memcard.err = 0x1B;
                if (sceMcClose(g_memcard.file) == 0) {
                    g_memcard.stage = MC_STAGE_GET_INFO;
                    g_memcard.slot = 0;
                    g_memcard.sync = 0;
                }
                break;
            }
            if (g_memcard.res == -5) {
                g_memcard.err = 0x15;
            } else if (g_memcard.res == -4) {
                g_memcard.err = 0x19;
            } else if (g_memcard.res == -3) {
                g_memcard.err = 0x1A;
            } else if (g_memcard.res == -2) {
                g_memcard.err = 0x18;
            } else {
                g_memcard.err = 0x1C;
            }
            g_memcard.stage = MC_STAGE_GET_INFO;
            g_memcard.slot = 0;
            g_memcard.sync = 0;
            break;
        case MC_LOAD_READ_GAME:
            g_memcard.size = CURRENT_CARD.gamesize;
            if (g_memcard.size > MC_GAME_DATA_SIZE) {
                FastTrap();
            }
            if (sceMcRead(g_memcard.file, mc_gameprepbuff, g_memcard.size) == 0) {
                g_memcard.substage = 5;
            }
            break;
        case MC_LOAD_READ_GAME_DONE:
            if (g_memcard.res == g_memcard.size) {
                if (g_memcard.stage == MC_STAGE_READ_SLOT_INFO) {
                    memcard_RestoreInfo(mc_gameprepbuff, g_memcard.slot, CURRENT_CARD.curslot);
                    g_memcard.substage = 8;
                } else {
                    CURRENT_CARD.oldsave = memcard_RestoreData(mc_gameprepbuff, 0, mc_gamedata);
                    g_memcard.substage = 6;
                }
                g_memcard.sync = 0;
                break;
            }
            g_memcard.errslot = g_memcard.slot;
            if (g_memcard.res >= 0) {
                g_memcard.err = 0x1B;
                if (sceMcClose(g_memcard.file) == 0) {
                    g_memcard.stage = MC_STAGE_GET_INFO;
                    g_memcard.slot = 0;
                    g_memcard.sync = 0;
                }
                break;
            }
            if (g_memcard.res == -5) {
                g_memcard.err = 0x15;
            } else if (g_memcard.res == -4) {
                g_memcard.err = 0x19;
            } else if (g_memcard.res == -3) {
                g_memcard.err = 0x1A;
            } else if (g_memcard.res == -2) {
                g_memcard.err = 0x18;
            } else {
                g_memcard.err = 0x1C;
            }
            g_memcard.stage = MC_STAGE_GET_INFO;
            g_memcard.slot = 0;
            g_memcard.sync = 0;
            break;
        case MC_LOAD_READ_LEVEL:
            g_memcard.size = CURRENT_CARD.levelsize;
            if (g_memcard.size > MC_LEVEL_DATA_SIZE) {
                FastTrap();
            }
            if (sceMcRead(g_memcard.file, mc_levelprepbuff, g_memcard.size) == 0) {
                g_memcard.substage = 7;
            }
            break;
        case MC_LOAD_READ_LEVEL_DONE:
            if (g_memcard.res == g_memcard.size) {
                CURRENT_CARD.oldsave +=
                    memcard_RestoreData(mc_levelprepbuff, g_memcard.level, mc_leveldata);
                if (++g_memcard.level < 20) {
                    g_memcard.substage = 6;
                } else {
                    g_memcard.substage = 8;
                }
                g_memcard.sync = 0;
                break;
            }
            g_memcard.errslot = g_memcard.slot;
            if (g_memcard.res >= 0) {
                g_memcard.err = 0x1B;
                if (sceMcClose(g_memcard.file) == 0) {
                    g_memcard.stage = MC_STAGE_GET_INFO;
                    g_memcard.slot = 0;
                    g_memcard.sync = 0;
                }
                break;
            }
            if (g_memcard.res == -5) {
                g_memcard.err = 0x15;
            } else if (g_memcard.res == -4) {
                g_memcard.err = 0x19;
            } else if (g_memcard.res == -3) {
                g_memcard.err = 0x1A;
            } else if (g_memcard.res == -2) {
                g_memcard.err = 0x18;
            } else {
                g_memcard.err = 0x1C;
            }
            g_memcard.stage = MC_STAGE_GET_INFO;
            g_memcard.slot = 0;
            g_memcard.sync = 0;
            break;
        case MC_LOAD_CLOSE:
            if (sceMcClose(g_memcard.file) == 0) {
                if (g_memcard.stage == MC_STAGE_READ_SLOT_INFO) {
                    g_memcard.sync = 0;
                    g_memcard.stage = MC_STAGE_NEXT_SLOT;
                } else {
                    g_memcard.stage = MC_STAGE_GET_INFO;
                    g_memcard.slot = 0;
                }
            }
            break;
        }
        break;

    case MC_STAGE_SAVE:
        if (CURRENT_CARD.oldsave != 0) {
            g_memcard.sync = 0;
            g_memcard.stage = MC_STAGE_GET_INFO;
            g_memcard.slot = 0;
            g_memcard.err = 0x2717;
            break;
        }
        if (CURRENT_CARD.saveslot < 0) {
            g_memcard.sync = 0;
            g_memcard.stage = MC_STAGE_GET_INFO;
            g_memcard.slot = 0;
            g_memcard.err = 0x1D;
            break;
        }
        g_memcard.substage = 0;
        g_memcard.stage = MC_STAGE_SAVING;
    case MC_STAGE_SAVING:
        switch (g_memcard.substage) {
        case MC_SAVE_OPEN:
            sprintf(name, SAVEGAME_SLOT, CURRENT_CARD.saveslot);
            if (sceMcOpen(CURRENT_CARD.port, CURRENT_CARD.slot, name, 2) == 0) {
                g_memcard.substage = 1;
            }
            break;
        case MC_SAVE_OPEN_DONE:
            if (g_memcard.res >= 0) {
                g_memcard.file = g_memcard.res;
                g_memcard.substage = 2;
            } else {
                g_memcard.errslot = g_memcard.slot;
                if (g_memcard.res == -7) {
                    g_memcard.err = 0x1E;
                } else if (g_memcard.res == -5) {
                    g_memcard.err = 0x1F;
                } else if (g_memcard.res == -4) {
                    g_memcard.err = 0x20;
                } else if (g_memcard.res == -3) {
                    g_memcard.err = 0x21;
                } else if (g_memcard.res == -2) {
                    g_memcard.err = 0x22;
                } else {
                    g_memcard.err = 0x26;
                }
                g_memcard.stage = MC_STAGE_GET_INFO;
                g_memcard.slot = 0;
            }
            g_memcard.sync = 0;
            break;
        case MC_SAVE_SKIP_HEADER:
            if (sceMcSeek(g_memcard.file, 8, 0) == 0) {
                g_memcard.substage = 3;
            }
            break;
        case MC_SAVE_SKIP_HEADER_DONE:
            if (g_memcard.res >= 0) {
                g_memcard.substage = 4;
            } else {
                g_memcard.stage = MC_STAGE_GET_INFO;
                g_memcard.slot = 0;
                g_memcard.sync = 0;
            }
            break;
        case MC_SAVE_WRITE_GAME:
            if (sceMcWrite(g_memcard.file, mc_gameprepbuff, memcard_GetDataSize(mc_gamedata)) ==
                0) {
                g_memcard.substage = 5;
            }
            break;
        case MC_SAVE_WRITE_GAME_DONE:
            if (g_memcard.res == memcard_GetDataSize(mc_gamedata)) {
                g_memcard.substage = 6;
                break;
            }
            g_memcard.errslot = g_memcard.slot;
            if (g_memcard.res >= 0) {
                g_memcard.err = 0x25;
                if (sceMcClose(g_memcard.file) == 0) {
                    g_memcard.stage = MC_STAGE_GET_INFO;
                    g_memcard.slot = 0;
                    g_memcard.sync = 0;
                }
                break;
            }
            if (g_memcard.res == -5) {
                g_memcard.err = 0x1F;
            } else if (g_memcard.res == -4) {
                g_memcard.err = 0x23;
            } else if (g_memcard.res == -3) {
                g_memcard.err = 0x24;
            } else if (g_memcard.res == -2) {
                g_memcard.err = 0x22;
            } else {
                g_memcard.err = 0x26;
            }
            g_memcard.stage = MC_STAGE_GET_INFO;
            g_memcard.slot = 0;
            g_memcard.sync = 0;
            break;
        case MC_SAVE_SEEK_LEVEL:
            if (g_memcard.level == 0) {
                g_memcard.substage = 8;
                break;
            }
            if (sceMcSeek(g_memcard.file, g_memcard.level * memcard_GetDataSize(mc_leveldata), 1) == 0) {
                g_memcard.substage = 7;
            }
            break;
        case MC_SAVE_SEEK_LEVEL_DONE:
            if (g_memcard.res >= 0) {
                g_memcard.substage = 8;
            } else {
                g_memcard.stage = MC_STAGE_GET_INFO;
                g_memcard.slot = 0;
                g_memcard.sync = 0;
            }
            break;
        case MC_SAVE_WRITE_LEVEL:
            if (sceMcWrite(g_memcard.file, mc_levelprepbuff, memcard_GetDataSize(mc_leveldata)) ==
                0) {
                g_memcard.substage = 9;
            }
            break;
        case MC_SAVE_WRITE_LEVEL_DONE:
            if (g_memcard.res == memcard_GetDataSize(mc_leveldata)) {
                g_memcard.substage = 10;
                break;
            }
            g_memcard.errslot = g_memcard.slot;
            if (g_memcard.res >= 0) {
                g_memcard.err = 0x25;
                if (sceMcClose(g_memcard.file) == 0) {
                    g_memcard.stage = MC_STAGE_GET_INFO;
                    g_memcard.slot = 0;
                    g_memcard.sync = 0;
                }
                break;
            }
            if (g_memcard.res == -5) {
                g_memcard.err = 0x1F;
            } else if (g_memcard.res == -4) {
                g_memcard.err = 0x23;
            } else if (g_memcard.res == -3) {
                g_memcard.err = 0x24;
            } else if (g_memcard.res == -2) {
                g_memcard.err = 0x18;
            } else {
                g_memcard.err = 0x1C;
            }
            g_memcard.stage = MC_STAGE_GET_INFO;
            g_memcard.slot = 0;
            g_memcard.sync = 0;
            break;
        case MC_SAVE_CLOSE:
            if (sceMcClose(g_memcard.file) == 0) {
                g_memcard.stage = MC_STAGE_GET_INFO;
                g_memcard.slot = 0;
            }
            break;
        }
        break;

    case MC_STAGE_READ_BLANK_SAVE: {
        mc_resource *chunk;
        int      size;

        GetSaveBuffers(bootAssets.savegame.length << 11, (void **)&chunk, (void **)&size);
        music_LoadFile(
            chunk, bootAssets.savegame.offset, bootAssets.savegame.length);
        g_memcard.substage = 18;
        g_memcard.sync = 0;
        break;
    }

    case MC_STAGE_READING_BLANK_SAVE:
        if (CdReadActive[0] == 0) {
            mc_resource *chunk;
            int      size;

            GetSaveBuffers(bootAssets.savegame.length << 11, (void **)&chunk, (void **)&size);
            g_memcard.substage = 19;
            g_memcard.addr = (char *)chunk + chunk->saveDataOffset;
        }
        g_memcard.sync = 0;
        break;

    case MC_STAGE_WRITE_WHOLE_SAVE:
        if (CURRENT_CARD.oldsave != 0) {
            g_memcard.sync = 0;
            g_memcard.stage = MC_STAGE_GET_INFO;
            g_memcard.slot = 0;
            g_memcard.err = 0x2718;
            break;
        }
        if (CURRENT_CARD.saveslot < 0) {
            g_memcard.sync = 0;
            g_memcard.stage = MC_STAGE_GET_INFO;
            g_memcard.slot = 0;
            g_memcard.err = 0x27;
            break;
        }
        g_memcard.level = 0;
        g_memcard.substage = 0;
        g_memcard.stage = MC_STAGE_WRITING_WHOLE_SAVE;
    case MC_STAGE_WRITING_WHOLE_SAVE:
        switch (g_memcard.substage) {
        case MC_WRITE_OPEN:
            sprintf(name, SAVEGAME_SLOT, CURRENT_CARD.saveslot);
            if (sceMcOpen(CURRENT_CARD.port, CURRENT_CARD.slot, name, 2) == 0) {
                g_memcard.substage = 1;
            }
            break;
        case MC_WRITE_WRITE:
            if (g_memcard.res >= 0) {
                int n;

                g_memcard.file = g_memcard.res;
                n = memcard_GetDataSize(mc_gamedata);
                g_memcard.size = n + memcard_GetDataSize(mc_leveldata) * 20 + 8;
                if (sceMcWrite(g_memcard.file, g_memcard.addr, g_memcard.size) == 0) {
                    g_memcard.substage = 2;
                }
                break;
            }
            g_memcard.err = 0x2B;
            g_memcard.errslot = g_memcard.slot;
            g_memcard.stage = MC_STAGE_GET_INFO;
            g_memcard.slot = 0;
            g_memcard.sync = 0;
            break;
        case MC_WRITE_CLOSE:
            if (g_memcard.res == g_memcard.size) {
                if (sceMcClose(g_memcard.file) == 0) {
                    g_memcard.substage = 3;
                }
                break;
            }
            g_memcard.errslot = g_memcard.slot;
            if (g_memcard.res >= 0) {
                g_memcard.err = 0xB;
                if (sceMcClose(g_memcard.file) == 0) {
                    g_memcard.stage = MC_STAGE_GET_INFO;
                    g_memcard.slot = 0;
                    g_memcard.sync = 0;
                }
                break;
            }
            if (g_memcard.res == -4) {
                g_memcard.err = 0x28;
            } else if (g_memcard.res == -3) {
                g_memcard.err = 0x29;
            } else if (g_memcard.res == -2) {
                g_memcard.err = 0x2A;
            } else {
                g_memcard.err = 0x2D;
            }
            g_memcard.stage = MC_STAGE_GET_INFO;
            g_memcard.slot = 0;
            g_memcard.sync = 0;
            break;
        case MC_WRITE_DONE:
            if (g_memcard.res != 0) {
                g_memcard.err = 0x2C;
                g_memcard.errslot = g_memcard.slot;
            }
            g_memcard.stage = MC_STAGE_GET_INFO;
            g_memcard.slot = 0;
            g_memcard.sync = 0;
            break;
        }
        break;
    }
}


void memcard_MakeWholeSave(char *addr)
{
    *(int *)addr = memcard_GetDataSize(mc_gamedata);
    *(int *)(addr + 4) = memcard_GetDataSize(mc_leveldata);

    addr += 8;
    addr += memcard_PrepData(addr, 0, mc_gamedata);

    for (int level = 0; level < MEMCARD_LEVEL_COUNT; level++) {
        addr += memcard_PrepData(addr, level, mc_leveldata);
    }
}

void memcard_Init(void)
{
    if (sceMcInit() != 0) {
        printf_stub("ERROR: could not init memcard lib\n");
    }
}

int memcard_GetDataSize(mc_data *mcd)
{
    int size = 8;

    for (; mcd->addr != 0; mcd++) {
        size += 8;
        size += mcd->size;
        size = (size + 3) & ~3;
    }

    return size + 8;
}

int memcard_Checksum(char *data, int size)
{
    unsigned char *byte = (unsigned char *)data;
    unsigned char *end;
    unsigned int crc;

    if (size > MEMCARD_CHECKSUM_LIMIT) {
        return 0;
    }

    end = byte + size;
    crc = 0xEDB88320;

    while (byte < end) {
        crc ^= *byte++ << 8;

        for (int bit = 7; bit >= 0; bit--) {
            if (crc & 0x8000) {
                crc = (crc << 1) ^ 0x1F45;
            } else {
                crc <<= 1;
            }
        }
    }

    return crc & 0xFFFF;
}

int memcard_TestChecksum(char *addr)
{
    int checksum = *(int *)(addr + 4);
    int good = 0;
    int size = *(int *)addr;

    if (checksum != 0) {
        good = memcard_Checksum(addr + 8, size) == checksum;
    }

    return good;
}

int memcard_PrepData(char *addr, int index, mc_data *mcd)
{
    int *cursor = (int *)(addr + 8);
    int size = 0;

    if (mcd->addr != 0) {
        mc_data *entry = mcd;

        do {
            char *source = (char *)entry->addr + index * entry->size;

            size += 8;
            cursor[0] = entry->iff;
            cursor[1] = entry->size;
            cursor += 2;
            FastMemCopy32(cursor, source, entry->size);

            cursor = (int *)((char *)cursor + entry->size);
            size += entry->size;
            cursor = (int *)(((int)cursor + 3) & ~3);
            size = (size + 3) & ~3;
            entry++;
        } while (entry->addr != 0);
    }

    cursor[1] = 0;
    cursor[0] = -1;

    size += 8;
    *(int *)(addr + 4) = memcard_Checksum(addr + 8, size);
    *(int *)addr = size;

    return size + 8;
}

void memcard_RestoreInfo(char *addr, int slot, int index)
{
    g_memcard.memcards[slot].info[index].bad = !memcard_TestChecksum(addr);

    // Each value sits in its own save chunk: 8 bytes of chunk header, then the int.
    addr += 0x10;
    g_memcard.memcards[slot].info[index].level = *(int *)addr;
    addr += 0xC;
    g_memcard.memcards[slot].info[index].bolts = *(int *)addr;
    addr += 0xC;
    g_memcard.memcards[slot].info[index].completes = *(int *)addr;
    addr += 0xC;
    g_memcard.memcards[slot].info[index].elapsedTime = *(int *)addr;
    addr += 0xC;
    g_memcard.memcards[slot].info[index].saveTime = *(sceCdCLOCK *)addr;
}

int memcard_RestoreData(char *addr, int index, mc_data *mcd)
{
    int errors;
    int restored;
    int entryIndex;

    if (!memcard_TestChecksum(addr)) {
        return 1;
    }

    addr += 8;
    errors = 0;
    restored = 8;

    for (entryIndex = 0; mcd[entryIndex].addr != 0; entryIndex++) {
        mcd[entryIndex].mark = 0;
    }

    while (((mc_chunk *)addr)->iff != -1) {
        mc_chunk *chunk = (mc_chunk *)addr;
        mc_data *entry;

        entryIndex = 0;

        if (mcd[0].addr == 0) {
            goto missing;
        }

        while (mcd[entryIndex].iff != chunk->iff) {
            entryIndex++;

            if (mcd[entryIndex].addr == 0) {
                goto missing;
            }
        }

        entry = (mc_data *)(entryIndex * (int)sizeof(mc_data) + (int)mcd);

        if (entry->addr != 0) {
            int chunkSize = chunk->size;
            char *destination = (char *)entry->addr + index * entry->size;
            int size;

            if (chunkSize == entry->size) {
                size = entry->size;
                entry->mark = 1;
            } else if (chunkSize < entry->size) {
                size = chunkSize;
                entry->mark = -1;
            } else {
                size = entry->size;
                entry->mark = -2;
            }

            if (memcmp(destination, chunk + 1, size) != 0) {
                g_loaderr++;
            }

            FastMemCopy32(destination, chunk + 1, size);
            restored += ((size + 3) & ~3) + 8;
        } else {
        missing:
            errors++;
        }

        addr += ((chunk->size + 3) & ~3) + 8;
    }

    restored += 8;

    if (restored != memcard_GetDataSize(mcd)) {
        errors++;
    }

    // The terminating chunk is followed by the id of the last block that was saved.
    addr += 8;

    for (entryIndex = 0; mcd[entryIndex].addr != 0 && mcd[entryIndex].iff != *(int *)addr; entryIndex++) {
        if (mcd[entryIndex].mark <= 0) {
            errors++;
        }
    }

    g_memcard.memcards[g_memcard.slot].oldsave = errors;

    return errors;
}

int memcard_Save(int force, int level)
{
    sceCdReadClock(&LastSaveTime);
    sceScfGetLocalTimefromRTC(&LastSaveTime);
    map_SaveLevelObjectState();
    map_SaveRevealMask(&MapRevealMasks[Level * MAP_REVEAL_MASK_SIZE]);

    if (g_memcard.useslot == -1 || g_memcard.memcards[g_memcard.useslot].saveslot < 0) {
        return force == 0;
    }

    g_memcard.autosave |= force;

    if (g_memcard.autosave != 0) {
        if (force == 0) {
            mcstate_flags |= MCSTATE_FLAG_DO_SAVE;
        }

        if (g_memcard.stage < MC_STAGE_FORMAT && g_memcard.nextstage < 0) {
            unsigned char visited = 0;

            g_memcard.level = Level;

            if (level >= 0) {
                Level = level;
                visited = LevelVisited[level];

                if (!visited) {
                    LevelVisited[level] = 1;
                }
            }

            g_memcard.memcards[0].info[g_memcard.memcards[0].saveslot].bolts = HeroBolts;
            g_memcard.memcards[0].info[g_memcard.memcards[0].saveslot].level = Level;
            g_memcard.memcards[0].info[g_memcard.memcards[0].saveslot].elapsedTime = ElapsedTime;
            g_memcard.memcards[0].info[g_memcard.memcards[0].saveslot].saveTime = LastSaveTime;
            g_memcard.memcards[0].info[g_memcard.memcards[0].saveslot].completes = ChallengeMode;

            memcard_PrepData(mc_gameprepbuff, 0, mc_gamedata);
            memcard_PrepData(mc_levelprepbuff, g_memcard.level, mc_leveldata);

            if (level >= 0) {
                LevelVisited[Level] = visited;
                Level = g_memcard.level;
            }

            if (g_memcard.nextstage < 0) {
                g_memcard.nextstage = MC_STAGE_SAVE;
                g_memcard.nextslot = g_memcard.useslot;
            }
        }
    }

    return g_memcard.nextstage == MC_STAGE_SAVE;
}

// The rest of memcard.cpp's small data; nothing decompiled reads it yet.
int MemcardSdata15FF48 = 0x1C0;
int MemcardSdata15FF4C = 0x1C;
