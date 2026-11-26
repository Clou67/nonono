#include "common.h"
#include "hero.h"
#include "vuchain.h"
#include "fastfunc.h"
#include "hud.h"

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hud", hud_InitBanks);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hud", Hud_LoadBankData);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hud", Hud_SetupBank);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hud", Hud_ClearBank);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hud", Hud_UploadBankIcons);


void HudHeap_Reset(void)
{
    unsigned char *base = MemSlots.hudHeap;
    HudState.heapCursor = base;
    HudState.heapEnd = base + HUD_HEAP_SIZE;
}

void *HudHeap_Alloc(int size)
{
    if (!HudState.heapCursor)
        HudHeap_Reset();

    unsigned char *end = HudState.heapEnd;
    unsigned char *allocation = HudState.heapCursor;
    if (end - allocation < size)
        return 0;

    size = (size + 15) & ~15u;
    HudState.heapCursor = allocation + size;
    return allocation;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hud", Hud_SwapMobyBank);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hud", RegisterHUDCallback);

void HudEntry_Restore(HudEntry *entry)
{
    HudEntry_SetIcon(entry, entry->registeredIcon);

    entry->flags = entry->registeredFlags;
    entry->update = entry->registeredUpdate;
    entry->draw = entry->registeredDraw;
    entry->value = entry->registeredValue;
    entry->maximum = entry->registeredMaximum;
    entry->init = entry->registeredInit;
    if (entry->init)
        entry->init(entry);

    entry->locked = 0;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hud", Hud_UnregisterById);

enum { HUD_NO_ICON = 0xFFFF };

int Hud_SetEntryIconById(int handle)
{
    int slot = 0;
    while (slot < HUD_ENTRY_COUNT && HudEntries[slot].id != handle)
        ++slot;

    if (slot < HUD_ENTRY_COUNT) {
        RegisterHUDCallback(slot, HUD_NO_ICON, 0, 0, 0, 0, 0);
        return 1;
    }

    return 0;
}

int Hero_FindHudEntry(int id);

void HudEntry_SetIcon(HudEntry *entry, unsigned int id)
{
    int index = Hero_FindHudEntry(id);
    unsigned short iconId = HudState.icons[index].id;

    entry->iconTableIndex = index;
    entry->iconId = iconId;
    entry->iconBaseIndex = HudState.icons[index].baseIndex;
    entry->iconVariantCount = HudState.icons[index].variantCount;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hud", func_0024B088);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hud", Hud_SetEntryValueById);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hud", HudEntry_ApplyAlignment);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hud", HudEntry_GetSlideOffset);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hud", HudEntry_CalcNumberSize);

void HudEntry_CalcNumberSize(HudEntry *entry);

void HudEntry_InitCounter(HudEntry *entry)
{
    int timer = FastScaleRoundInt(180) + 30;
    entry->offsetX = 0;
    entry->offsetY = 0;
    entry->timer = timer;
    HudEntry_CalcNumberSize(entry);
}

void HudEntry_InitCounter32(HudEntry *entry)
{
    int timer = FastScaleRoundInt(180) + 30;
    entry->offsetX = 0;
    entry->offsetY = 0;
    entry->timer = timer;
    entry->width = 32;
    entry->height = 32;
    HudEntry_CalcNumberSize(entry);
}

TEXT_PADDING(0, 0);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hud", Hud_SetEntryMinValueById);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hud", HudEntry_UpdateCounter);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hud", HudEntry_UpdateCounterSlide);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hud", func_0024B8F8);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hud", OxygenHud_Update);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hud", DrawOxygenMeter);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hud", HudBubbles_Init);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hud", Moby185Hud_Update);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hud", Draw_Moby185Meter);

void HudEntry_InitCounterSlide(HudEntry *entry)
{
    int timer = FastScaleRoundInt(10) + 30;
    entry->offsetX = 0;
    entry->offsetY = 0;
    entry->timer = timer;
    entry->width = 32;
    entry->height = 32;
    HudEntry_CalcNumberSize(entry);
}

void HudEntry_UpdateCounter(HudEntry *entry);

void HudEntry_UpdateCounterWrap(HudEntry *entry)
{
    HudEntry_UpdateCounter(entry);
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hud", Draw_PromptMsg);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hud", GetHelpLen);

void HudEntry_InitCounter(HudEntry *entry);

void Hud_GetTexIndex(HudEntry *entry)
{
    HudEntry_InitCounter(entry);
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hud", Moby849Hud_Update);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hud", Draw_Moby849Meter);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hud", QuickSelectHud_Init);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hud", UpdateQuickSelect);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hud", Draw_QuickSelectHud);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hud", func_0024E1A8);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hud", HudEntry_DrawIcon);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hud", Draw_NanotechUI);

extern short BoltHudCounter;

void Hud_DrawTexQuadUV_Fixed(HudEntry *entry)
{
    HudEntry_RoundFixed(entry);
    entry->counter = &BoltHudCounter;
    BoltHudCounter = 0;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hud", BoltHud_Update);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hud", Draw_BoltCountUI);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hud", func_0024EE00);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hud", Draw_MetalDetectorHud);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hud", Hud_DrawTextBox);

void HudEntry_RoundFixed(HudEntry *entry)
{
    entry->timer = FastScaleRoundInt(120) + 30;
    entry->width = 32;
    entry->height = 32;
    HudEntry_CalcNumberSize(entry);
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hud", Draw_AmmoCounter);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hud", func_0024F6A0);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hud", HudIcon_GetAnimFrame);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hud", Hud_ResetAllEntries);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hud", Hud_RegisterGameplayEntries);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hud", Hud_ClearAmmoEntry);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hud", HudStub);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hud", DrawGameplayHud);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hud", Hud_DrawTexQuadOffset);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hud", HudTex_GetFrame);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hud", HudTex_Bind);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hud", Hud_DrawTexQuad);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hud", Hud_DrawFlatOverlay);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hud", Hud_DrawTexHeaderQuad);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hud", Hud_DrawEffectTexQuad);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hud", Hud_DrawTexQuadUV);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hud", Hud_DrawTexQuadF);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hud", Hud_DrawTexQuad4Pt);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hud", Hud_DrawRotatedSprite16);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hud", Hud_DrawEffectTexQuadUV);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hud", HudTex_BuildUploadPacket);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hud", Hud_DrawFlatRect);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hud", Hud_DrawFlatRectFixed);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hud", Hud_DrawFlatRect4Col);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hud", func_002519B8);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hud", func_00251AA8);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hud", Hud_DrawTextBoxFrame);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/hud", Hud_DrawTextBoxCentered);
