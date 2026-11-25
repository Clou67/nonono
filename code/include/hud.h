#ifndef HUD_H
#define HUD_H

struct HudIconTableEntry {
    unsigned short id;
    unsigned short unk_02;
    unsigned short variantCount;
    unsigned char baseIndex;
    unsigned char unk_07;
};

extern HudIconTableEntry *HudIconTable;

struct HudEntry;
typedef void (*HudFunction)(HudEntry *entry);

struct HudEntry {
    int iconId;
    unsigned int flags;
    int maximum;
    void *value;
    HudFunction init;
    HudFunction update;
    HudFunction draw;
    int unk1C;
    unsigned int registeredIcon;
    unsigned int registeredFlags;
    int registeredMaximum;
    void *registeredValue;
    HudFunction registeredInit;
    HudFunction registeredUpdate;
    HudFunction registeredDraw;
    int unk3C;
    short iconTableIndex;
    unsigned char iconBaseIndex;
    unsigned char unk43;
    int iconVariantCount;
    short offsetX;
    short offsetY;
    char unk4C[0xC];
    int width;
    int height;
    unsigned int alignFlags;
    int id;
    int locked;
    char unk6C[0x10];
    int timer;
    short *counter;
    char unk84[0xC];
};

enum { HUD_ENTRY_COUNT = 13 };
extern HudEntry HudEntries[HUD_ENTRY_COUNT];

int HudTex_GetFrame(int texture, int frame);
void Hud_DrawFlatRect(int left, int top, int right, int bottom, unsigned long rgba, int mode);
void Hud_DrawFlatRectFixed(int left, int top, int right, int bottom, unsigned long rgba, int mode);
void Hud_DrawTexQuad(int frame, int x, int y, int width, int height, int alpha);
void Hud_DrawTexQuadF(int frame, int x, int y, int width, int height, int u, int v, int alpha);
int HudTex_Bind(int frame);
void Hud_DrawRotatedSprite16(float cx, float cy, float width, float height, float theta, int texW, int texH, unsigned long tex0);
void Hud_SetEntryValueById(int id, int value);
void HudStub(void);

// Adds a HUD entry with its init, update and draw functions; returns its handle.
int RegisterHUDCallback(int type, int texture, HudFunction init, HudFunction update, HudFunction draw, void *value, int maximum);
// Keeps the entry on screen for the given frames; nonzero when it is no longer registered.
int Hud_SetEntryMinValueById(int handle, int frames);
int Hud_SetEntryIconById(int handle);
void HudEntry_InitCounterSlide(HudEntry *entry);

void Draw_PromptMsg(HudEntry *entry);

void BoltHud_Update(HudEntry *entry);
void Draw_BoltCountUI(HudEntry *entry);
// Shows a help prompt with the given text.
void GetHelpLen(char *text);

void Hud_GetTexIndex(HudEntry *entry);

void HudEntry_UpdateCounterWrap(HudEntry *entry);

void HudEntry_InitCounter(HudEntry *entry);

void HudEntry_RoundFixed(HudEntry *entry);

void Hud_DrawTexQuadUV_Fixed(HudEntry *entry);

void HudEntry_InitCounter32(HudEntry *entry);

void HudHeap_Reset(void);

void *HudHeap_Alloc(int size);

void HudEntry_SetIcon(HudEntry *entry, unsigned int id);

void HudEntry_Restore(HudEntry *entry);

// Header of the loaded HUD image; only the fields known so far.
struct HudBankHeader {
    char unk_00[0x74];
    void *bankData[6];        // 0x74: cleared by LoadCompressedHudBank
};

enum { HUD_HEAP_SIZE = 0x64000 };
struct HudStateData {
    char unk_00[0x10];
    unsigned char *heapCursor;
    unsigned char *heapEnd;
    HudBankHeader *header;
    HudIconTableEntry *icons;
};
extern HudStateData HudState;

#endif
