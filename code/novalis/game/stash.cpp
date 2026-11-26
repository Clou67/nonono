#include <stddef.h>

#include "common.h"
#include "sce.h"
#include "stash.h"

enum { STASH_SLOT_COUNT = 64, STASH_QWORD_BYTES = 16, STASH_RPC_SERVER = 0x11,
       STASH_RPC_FETCH = 1, STASH_RPC_INFO = 2, STASH_MAX_FETCH_QWORDS = 0xFFFF };

struct StashInfo {
    int base;
    int size;
    SifRpcClient client;
    int next;
    int count;
};

struct StashBlock {
    int address;
    int qwords;
    char *comment;
    int padding;
};

extern StashInfo StashState;
extern StashBlock StashBlocks[];
extern SifRpcClient StashClient;

void Stash_Init(void)
{
    sceSifInitRpc(0);
}

void Stash_InitOnce(void)
{
    StashInfo *state;
    int reply[4];
    int index;

    for (;;) {
        if (sceSifBindRpc(&StashClient, STASH_RPC_SERVER, 1) < 0) {
            for (;;) {
            }
        }
        while (sceSifCheckStatRpc(&StashClient) != 0) {
        }
        state = &StashState;
        if (state->client.server != 0)
            break;
        // Give the IOP server time to start before retrying the bind.
        index = 0xFFFF;
        while (index != -1) {
            index--;
        }
    }

    SifRpcClient *client = &StashClient;
    sceSifCallRpc(client, STASH_RPC_INFO, 0, 0, 0, reply, sizeof(reply), 0, 0);
    // The RPC client is embedded in the stash state.
    StashInfo *info = (StashInfo *)((char *)client - offsetof(StashInfo, client));
    info->base = reply[0];
    info->size = reply[1];
    info->next = reply[0];
    info->count = 0;
    for (index = 0; index < STASH_SLOT_COUNT; index++) {
        StashBlocks[index].address = 0;
        StashBlocks[index].qwords = 0;
    }
}

int Stash_SendData(void *source, int transferQwords, int reserveQwords, char *comment)
{
    StashInfo *state = &StashState;
    int reserveBytes = reserveQwords * STASH_QWORD_BYTES;
    if (state->size - (state->next - state->base) < reserveBytes)
        return -1;
    if (state->count == STASH_SLOT_COUNT)
        return -2;

    SifDmaTransfer transfer;
    transfer.source = source;
    transfer.destination = (void *)state->next;
    transfer.size = transferQwords * STASH_QWORD_BYTES;
    transfer.attributes = 0;
    sceSifSetDma(&transfer, 1);

    int slot = state->count++;
    StashBlocks[slot].address = state->next;
    StashBlocks[slot].qwords = reserveQwords;
    StashBlocks[slot].comment = comment;
    state->next += reserveBytes;
    return slot;
}

int Stash_Upload(void *source, unsigned int slot, int offset, int qwords)
{
    if (slot >= STASH_SLOT_COUNT || StashBlocks[slot].qwords == 0)
        return -3;
    if (StashBlocks[slot].qwords < offset + qwords)
        return -1;

    SifDmaTransfer transfer;
    transfer.source = source;
    transfer.destination = (void *)(StashBlocks[slot].address + offset * STASH_QWORD_BYTES);
    transfer.size = qwords * STASH_QWORD_BYTES;
    transfer.attributes = 0;
    sceSifSetDma(&transfer, 1);
    return 0;
}

int Stash_Copy(void *destination, unsigned int slot, int offset, int qwords, int mode)
{
    if (qwords == -1)
        qwords = Stash_GetSize(slot);
    if (slot >= STASH_SLOT_COUNT || StashBlocks[slot].qwords == 0)
        return -3;
    if (StashBlocks[slot].qwords < offset + qwords)
        return -1;

    int request[4];
    request[0] = StashBlocks[slot].address + offset * STASH_QWORD_BYTES;
    while (qwords != 0) {
        int chunk = qwords > STASH_MAX_FETCH_QWORDS ? STASH_MAX_FETCH_QWORDS : qwords;
        sceSifCallRpc(&StashClient, STASH_RPC_FETCH, mode, request, sizeof(request), destination,
                      chunk * STASH_QWORD_BYTES, 0, 0);
        qwords -= chunk;
        destination = (char *)destination + chunk * STASH_QWORD_BYTES;
        request[0] += chunk * STASH_QWORD_BYTES;
    }
    return 0;
}

int Stash_GetSize(unsigned int slot)
{
    if (slot >= STASH_SLOT_COUNT)
        return -3;
    return StashBlocks[slot].qwords;
}

TEXT_PADDING(0x00000000, 0x00000000);
