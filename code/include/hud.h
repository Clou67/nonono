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
// Header of the level's HUD data, followed by the tables its offsets point to.
struct HudBankHeader {
    int unk_00;
    int icons;                // 0x04: offsets from the header
    int frameRefs;            // 0x08
    int palettePages;         // 0x0C
    int imagePages;           // 0x10
    char unk_14[0x40];
    int hasBank0;             // 0x54: banks 0, 2, 3 and 4 are sent to the IOP stash
    int bank1Size;            // 0x58: bank 1 lives in the HUD heap
    int hasBank2;             // 0x5C
    int hasBank3;             // 0x60
    int hasBank4;             // 0x64
    char unk_68[0xC];
    void *bankData[6];        // 0x74: cleared by LoadCompressedHudBank
    char unk_8C[0x8];
    int bankStash[5];         // 0x94: stash slots of the sent banks
};

enum { HUD_HEAP_SIZE = 0x64000 };
struct HudStateData {
    char unk_00[0x10];
    unsigned char *heapCursor;
    unsigned char *heapEnd;
    HudBankHeader *header;
    HudIconTableEntry *icons;   // 0x1C
    void *frameRefs;            // 0x20
    void *imagePages;           // 0x24
    void *palettePages;         // 0x28
    char unk_2C[0xC];
    int bankSizes[5];           // 0x38: of the level WAD's HUD banks, rounded up to 0x40
};
extern HudStateData HudState;

#endif
