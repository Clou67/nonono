#include "common.h"
#include "sce.h"

int LoadIopModuleFromEE(void *source, int size)
{
    SifDmaTransfer transfer;
    int status;
    int loaded = 1;
    void *iopBuffer = sceSifAllocIopHeap(size);
    int dmaId;

    transfer.source = source;
    transfer.destination = iopBuffer;
    transfer.size = size;
    transfer.attributes = 0;

    dmaId = sceSifSetDma(&transfer, 1);

    if (dmaId != 0) {
        for (;;) {
            if (sceSifDmaStat(dmaId) < 0)
                break;
        }

        status = sceSifLoadModuleBuffer(iopBuffer, 0, 0);

        if (status < 0)
            loaded = 0;

        sceSifFreeIopHeap(iopBuffer);
    }

    return loaded;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/initonce", InitMemSlots);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/initonce", InitOnce);
