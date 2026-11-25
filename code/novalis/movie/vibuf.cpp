#include "common.h"
#include "videodec.h"

void setD4_CHCR(unsigned int value);

enum {
    IPU_INPUT_DMA_MADR = 0x1000B010,
    IPU_INPUT_DMA_QWC = 0x1000B020,
    IPU_INPUT_DMA_CHCR = 0x1000B000,
    IPU_OUTPUT_DMA_CHCR = 0x1000B400,
    IPU_CONTROL = 0x10002010,
    IPU_TOP = 0x10002020,
    IPU_CONTROL_FIFO_MASK = 0xF0
};

enum {
    VIBUF_BLOCK_SHIFT = 11,
    VIBUF_BLOCK_SIZE = 1 << VIBUF_BLOCK_SHIFT,
    VIBUF_PHYSICAL_ADDRESS_MASK = 0x0FFFFFFF,
    IPU_OUTPUT_DMA_IDLE_CHCR = 5,
    IPU_OUTPUT_DMA_MADR = 0x1000B410,
    IPU_OUTPUT_DMA_QWC = 0x1000B420,
    IPU_OUTPUT_DMA_TADR = 0x1000B430
};

unsigned int getFIFOindex(ViBuf *buffer, void *position)
{
    unsigned int endTag = ((buffer->n << 4) + (unsigned int)buffer->tag + 0x10) & VIBUF_PHYSICAL_ADDRESS_MASK;
    if (position == (void *)endTag)
        return 0;
    return ((unsigned int)position - (unsigned int)buffer->data) >> VIBUF_BLOCK_SHIFT;
}

enum {
    DMAC_ENABLE_READ = 0x1000F520,
    DMAC_ENABLE_WRITE = 0x1000F590,
    DMAC_ENABLE_CHANNEL_WRITE = 0x10000
};

void setD3_CHCR(unsigned int value)
{
    DIntr();
    *(volatile unsigned int *)DMAC_ENABLE_WRITE =
        *(volatile unsigned int *)DMAC_ENABLE_READ | DMAC_ENABLE_CHANNEL_WRITE;
    *(volatile unsigned int *)IPU_INPUT_DMA_CHCR = value;
    *(volatile unsigned int *)DMAC_ENABLE_WRITE =
        *(volatile unsigned int *)DMAC_ENABLE_READ & ~DMAC_ENABLE_CHANNEL_WRITE;
    EIntr();
}

void setD4_CHCR(unsigned int value)
{
    DIntr();
    *(volatile unsigned int *)DMAC_ENABLE_WRITE =
        *(volatile unsigned int *)DMAC_ENABLE_READ | DMAC_ENABLE_CHANNEL_WRITE;
    *(volatile unsigned int *)IPU_OUTPUT_DMA_CHCR = value;
    *(volatile unsigned int *)DMAC_ENABLE_WRITE =
        *(volatile unsigned int *)DMAC_ENABLE_READ & ~DMAC_ENABLE_CHANNEL_WRITE;
    EIntr();
}

void scTag2(unsigned long *tag, unsigned int address, unsigned int id, unsigned int count)
{
    *tag = ((unsigned long)address << 32) | (((unsigned long)id << 32) >> 4) | (unsigned long)count;
}

int viBufCreate(ViBuf *buffer, unsigned long long *input, unsigned long long *tags, int sectors,
                TimeStamp *timestamps, int timestampCount)
{
    EeSemaParam parameters;
    buffer->data = (u_long128 *)input;
    buffer->tag = (u_long128 *)(((unsigned int)tags & VIBUF_PHYSICAL_ADDRESS_MASK) | 0x20000000);
    buffer->n = sectors;
    buffer->buffSize = sectors << VIBUF_BLOCK_SHIFT;
    buffer->ts = timestamps;
    buffer->n_ts = timestampCount;

    parameters.initialCount = 1;
    parameters.maxCount = 1;
    buffer->sema = CreateSema(&parameters);
    viBufReset(buffer);
    buffer->totalBytes = 0;
    return 1;
}

int viBufReset(ViBuf *buffer)
{
    int index;

    buffer->isActive = 1;
    buffer->dmaStart = 0;
    buffer->dmaN = 0;
    buffer->readBytes = 0;
    buffer->count_ts = 0;
    buffer->wt_ts = 0;

    for (index = 0; index < buffer->n_ts; index++) {
        buffer->ts[index].pts = -1;
        buffer->ts[index].dts = -1;
        buffer->ts[index].pos = 0;
        buffer->ts[index].len = 0;
    }

    for (index = 0; index < buffer->n; index++) {
        unsigned int address = ((index << VIBUF_BLOCK_SHIFT) + (unsigned int)buffer->data) & VIBUF_PHYSICAL_ADDRESS_MASK;
        scTag2((unsigned long *)&buffer->tag[index], address, 3, VIBUF_BLOCK_SIZE / 16);
    }
    scTag2((unsigned long *)&buffer->tag[index], (unsigned int)buffer->tag & VIBUF_PHYSICAL_ADDRESS_MASK, 2, 0);

    *(volatile unsigned int *)IPU_OUTPUT_DMA_QWC = 0;
    *(volatile unsigned int *)IPU_OUTPUT_DMA_MADR = (unsigned int)buffer->data & VIBUF_PHYSICAL_ADDRESS_MASK;
    *(volatile unsigned int *)IPU_OUTPUT_DMA_TADR = (unsigned int)buffer->tag & VIBUF_PHYSICAL_ADDRESS_MASK;
    setD4_CHCR(IPU_OUTPUT_DMA_IDLE_CHCR);
    return 1;
}

int viBufBeginPut(ViBuf *buffer, unsigned char **first, int *firstSize, unsigned char **second, int *secondSize)
{
    WaitSema(buffer->sema);

    int tagIndex = buffer->dmaN + 2;
    int position = ((buffer->dmaStart + buffer->dmaN) << VIBUF_BLOCK_SHIFT) + buffer->readBytes;
    int available = ((buffer->n - tagIndex) << VIBUF_BLOCK_SHIFT) - buffer->readBytes;
    position %= buffer->buffSize;

    if (buffer->buffSize - position >= available) {
        *first = (unsigned char *)buffer->data + position;
        *firstSize = available;
        *second = 0;
        *secondSize = 0;
    } else {
        *first = (unsigned char *)buffer->data + position;
        *firstSize = buffer->buffSize - position;
        *second = (unsigned char *)buffer->data;
        *secondSize = available - (buffer->buffSize - position);
    }

    return SignalSema(buffer->sema);
}

void viBufEndPut(ViBuf *buffer, int size)
{
    WaitSema(buffer->sema);
    buffer->readBytes += size;
    buffer->totalBytes += size;
    SignalSema(buffer->sema);
}

void ErrMessage(char *message);

int viBufAddDMA(ViBuf *buffer)
{
    int added = 0;
    WaitSema(buffer->sema);
    if (!buffer->isActive) {
        ErrMessage("DMA ADD not active\n");
        return 0;
    }

    setD4_CHCR(IPU_OUTPUT_DMA_IDLE_CHCR);
    unsigned int channelControl = *(volatile unsigned int *)IPU_OUTPUT_DMA_CHCR;
    int current = getFIFOindex(buffer, (void *)*(volatile unsigned int *)IPU_OUTPUT_DMA_MADR);
    int consumed = (current + buffer->n - buffer->dmaStart) % buffer->n;
    buffer->dmaStart = (buffer->dmaStart + consumed) % buffer->n;
    buffer->dmaN -= consumed;
    int next = (buffer->dmaStart + buffer->dmaN) % buffer->n;
    int blocks = buffer->readBytes / VIBUF_BLOCK_SIZE;
    buffer->readBytes -= blocks << VIBUF_BLOCK_SHIFT;

    if (blocks > 0) {
        int last = buffer->n - 1;
        int previous = (buffer->dmaStart + buffer->dmaN + last) % buffer->n;
        scTag2((unsigned long *)&buffer->tag[previous],
               (unsigned int)buffer->data + (previous << VIBUF_BLOCK_SHIFT), 3, VIBUF_BLOCK_SIZE / 16);
        added = 1;
    }

    int index = next;
    for (int block = 0; block < blocks; block++) {
        int id = 0;
        if (block != blocks - 1)
            id = 3;
        scTag2((unsigned long *)&buffer->tag[index],
               (unsigned int)buffer->data + (index << VIBUF_BLOCK_SHIFT), id, VIBUF_BLOCK_SIZE / 16);
        index = (index + 1) % buffer->n;
    }

    buffer->dmaN += blocks;
    if (buffer->dmaN != 0) {
        if (added)
            channelControl = (channelControl & VIBUF_PHYSICAL_ADDRESS_MASK) | 0x30000000;
        setD4_CHCR(channelControl | 0x100);
    }

    SignalSema(buffer->sema);
    return 1;
}

void setD3_CHCR(unsigned int value);

int viBufStopDMA(ViBuf *buffer)
{
    WaitSema(buffer->sema);
    buffer->isActive = 0;

    setD4_CHCR(IPU_OUTPUT_DMA_IDLE_CHCR);
    buffer->d4madr = *(volatile unsigned int *)IPU_OUTPUT_DMA_MADR;
    buffer->d4tadr = *(volatile unsigned int *)IPU_OUTPUT_DMA_TADR;
    buffer->d4qwc = *(volatile unsigned int *)IPU_OUTPUT_DMA_QWC;
    buffer->d4chcr = *(volatile unsigned int *)IPU_OUTPUT_DMA_CHCR;
    while (*(volatile unsigned int *)IPU_CONTROL & IPU_CONTROL_FIFO_MASK) {
    }

    setD3_CHCR(0);
    buffer->d3madr = *(volatile unsigned int *)IPU_INPUT_DMA_MADR;
    buffer->d3qwc = *(volatile unsigned int *)IPU_INPUT_DMA_QWC;
    buffer->d3chcr = *(volatile unsigned int *)IPU_INPUT_DMA_CHCR;
    buffer->ipubp = *(volatile unsigned int *)IPU_TOP;
    buffer->ipuctrl = *(volatile unsigned int *)IPU_CONTROL;
    SignalSema(buffer->sema);
    return 1;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/movie/vibuf", viBufRestartDMA__FP5ViBuf);

int viBufDelete(ViBuf *buffer)
{
    setD4_CHCR(IPU_OUTPUT_DMA_IDLE_CHCR);
    *(volatile unsigned int *)IPU_OUTPUT_DMA_QWC = 0;
    *(volatile unsigned int *)IPU_OUTPUT_DMA_MADR = 0;
    *(volatile unsigned int *)IPU_OUTPUT_DMA_TADR = 0;
    DeleteSema(buffer->sema);
    return 1;
}

int viBufCount(ViBuf *buffer)
{
    WaitSema(buffer->sema);
    int count = (buffer->dmaN << VIBUF_BLOCK_SHIFT) + buffer->readBytes;
    SignalSema(buffer->sema);
    return count;
}

int viBufFlush(ViBuf *buffer)
{
    WaitSema(buffer->sema);
    int rounded = buffer->readBytes + (VIBUF_BLOCK_SIZE - 1);
    int adjusted = buffer->readBytes + (2 * VIBUF_BLOCK_SIZE - 2);
    int limit = -1;
    if (limit < rounded)
        adjusted = rounded;
    buffer->readBytes = (adjusted >> VIBUF_BLOCK_SHIFT) << VIBUF_BLOCK_SHIFT;
    return SignalSema(buffer->sema);
}

static inline int ringPosition(int position, int capacity)
{
    return position % capacity;
}

int viBufModifyPts(ViBuf *buffer, TimeStamp *timestamp)
{
    int index = (buffer->wt_ts - buffer->count_ts + buffer->n_ts) % buffer->n_ts;
    int capacity = buffer->n << VIBUF_BLOCK_SHIFT;
    int keepScanning = 1;
    TimeStamp *entry;

    if (buffer->count_ts > 0) {
        while (keepScanning && (entry = &buffer->ts[index])->len != 0 && timestamp->len != 0) {
            if (ringPosition(entry->pos + capacity - timestamp->pos, capacity) < timestamp->len) {
                int overlap = timestamp->pos + timestamp->len - entry->pos;
                if (entry->len < overlap)
                    overlap = entry->len;

                entry->pos = (entry->pos + overlap) % capacity;
                entry->len -= overlap;
                if (entry->len == 0) {
                    if (entry->pts >= 0) {
                        entry->pts = -1;
                        entry->dts = -1;
                        entry->pos = 0;
                        entry->len = 0;
                    }

                    buffer->count_ts = (buffer->count_ts - 1 < 0) ? 0 : buffer->count_ts - 1;
                }
            } else {
                keepScanning = 0;
            }

            index = (index + 1) % buffer->n_ts;
        }
    }

    return 0;
}

int viBufModifyPts(ViBuf *buffer, TimeStamp *timestamp);

int viBufPutTs(ViBuf *buffer, TimeStamp *timestamp)
{
    int result = 0;
    WaitSema(buffer->sema);

    if (buffer->count_ts < buffer->n_ts) {
        viBufModifyPts(buffer, timestamp);
        if (timestamp->pts >= 0 || timestamp->dts >= 0) {
            buffer->ts[buffer->wt_ts].pts = timestamp->pts;
            buffer->ts[buffer->wt_ts].dts = timestamp->dts;
            buffer->ts[buffer->wt_ts].pos = timestamp->pos;
            buffer->ts[buffer->wt_ts].len = timestamp->len;
            buffer->count_ts++;
            buffer->wt_ts = (buffer->wt_ts + 1) % buffer->n_ts;
        }

        result = 1;
    }

    SignalSema(buffer->sema);
    return result;
}

int viBufGetTs(ViBuf *buffer, TimeStamp *timestamp)
{
    unsigned int address = *(volatile unsigned int *)IPU_OUTPUT_DMA_MADR;
    unsigned int top = *(volatile unsigned int *)IPU_TOP;
    int bits = buffer->ipubp & 0x7F;
    int capacity = buffer->n << VIBUF_BLOCK_SHIFT;
    int found = 0;

    address -= (((top >> 16) & 3) + ((top >> 8) & 0xF)) << 4;
    WaitSema(buffer->sema);
    timestamp->pts = -1;
    timestamp->dts = -1;
    address += bits >> 3;
    address += capacity;

    int position = (address - (unsigned int)buffer->data) % capacity;
    int count = buffer->count_ts;
    int next = buffer->wt_ts;
    for (int index = 0; index < count && !found; index++) {
        int slot = (next - count + buffer->n_ts + index) % buffer->n_ts;
        if (ringPosition(position + capacity - buffer->ts[slot].pos, capacity) < buffer->ts[slot].len) {
            found = 1;
            timestamp->pts = buffer->ts[slot].pts;
            timestamp->dts = buffer->ts[slot].dts;
            buffer->ts[slot].pts = -1;
            buffer->ts[slot].dts = -1;
            buffer->count_ts -= (buffer->count_ts < 2) ? buffer->count_ts : 1;
        }
    }

    SignalSema(buffer->sema);
    return 1;
}
