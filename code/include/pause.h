#ifndef PAUSE_H
#define PAUSE_H

struct MobyInstance;
struct FontWindow;

// The pause menu's state; only the state and the memory card icon switch are named so far.
struct PauseMenuState {
    int state;                      // 0x000
    char unk_004[0x138];
    int hideActivityIcon;           // 0x13C
};

extern PauseMenuState PauseMenu;

enum { GAME_COMPLETE_MOBY_COUNT = 24 };

struct GameCompleteWidget {
    char unk_00[0x44];
    MobyInstance *mobys[GAME_COMPLETE_MOBY_COUNT];
};

struct GoldBoltWidget {
    char unk_00[0x44];
    MobyInstance *moby;
};

struct ImageWidget {
    char unk_00[0x44];
    int image;
    void *streamBuffers[2];
    int unk_50;
    int unk_54;
};

enum { MENU_STREAM_BUFFER_COUNT = 5, MENU_STREAM_LARGE = 1, MENU_STREAM_LOCKED = 4 };

struct MenuStreamBuffer {
    void *data;
    int flags;
};

extern MenuStreamBuffer MenuStreamBuffers[MENU_STREAM_BUFFER_COUNT];

struct MenuClipWidget {
    char unk_00[0x18];
    int x;
    int y;
    int width;
    int height;
};

struct MessageBoxWidget {
    char unk_00[0x54];
    void *streamBuffer;
};

struct SaveLoadWidget {
    char unk_00[0x48];
    void *streamBuffer;
    int unk_4C;
};

struct ItemViewWidget {
    char unk_00[0x44];
    MobyInstance *moby;
    MobyInstance *otherMoby;
};

extern int pauseActionListMode;

enum { MAP_CACHE_SLOT_COUNT = 5 };
struct MapPageState {
    char unk0[0x28];
    int available;
    char unk2C[0x1F8];
    int level;
    char unk228[0x50];
    void *cacheBuffers[MAP_CACHE_SLOT_COUNT];
    int cacheIds[MAP_CACHE_SLOT_COUNT];
    char unk2A0[4];
    int cacheSizes[MAP_CACHE_SLOT_COUNT];
};

extern MapPageState MapPage;
extern int pauseActionList[];

int MenuText_OnEnterResetBuffers(void);

void ItemView_SpinMobyUpdate(MobyInstance *moby);

void GoldBolt_SpinMobyUpdate(MobyInstance *moby);

int MapPage_Draw(void);

int GameComplete_Draw(GameCompleteWidget *widget);

int GoldBoltWidget_DeleteMoby(GoldBoltWidget *widget);

int ImageWidget_OnExit(ImageWidget *widget);

int Menu_GetStreamBufferSize(void *data);

int Menu_SetClipRect(MenuClipWidget *widget);

int MessageBox_OnExit(MessageBoxWidget *widget);

int SaveLoad_OnEnter(SaveLoadWidget *widget);

int SaveLoad_OnExit(SaveLoadWidget *widget);

int ItemView_OnExit(ItemViewWidget *widget);

void Menu_InitSpriteRect(FontWindow *window, MenuClipWidget *widget);

#endif
