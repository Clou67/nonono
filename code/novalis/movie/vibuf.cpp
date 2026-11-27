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

unsigned int getFIFOindex(ViBuf *f, void *addr)
{
    unsigned int endTag = ((f->n << 4) + (unsigned int)f->tag + 0x10) & VIBUF_PHYSICAL_ADDRESS_MASK;
    if (addr == (void *)endTag)
        return 0;
    return ((unsigned int)addr - (unsigned int)f->data) >> VIBUF_BLOCK_SHIFT;
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

int viBufReset(ViBuf *f)
{
    int index;

    f->isActive = 1;
    f->dmaStart = 0;
    f->dmaN = 0;
    f->readBytes = 0;
    f->count_ts = 0;
    f->wt_ts = 0;

    for (index = 0; index < f->n_ts; index++) {
        f->ts[index].pts = -1;
        f->ts[index].dts = -1;
        f->ts[index].pos = 0;
        f->ts[index].len = 0;
    }

    for (index = 0; index < f->n; index++) {
        unsigned int address = ((index << VIBUF_BLOCK_SHIFT) + (unsigned int)f->data) & VIBUF_PHYSICAL_ADDRESS_MASK;
        scTag2((unsigned long *)&f->tag[index], address, 3, VIBUF_BLOCK_SIZE / 16);
    }
    scTag2((unsigned long *)&f->tag[index], (unsigned int)f->tag & VIBUF_PHYSICAL_ADDRESS_MASK, 2, 0);

    *(volatile unsigned int *)IPU_OUTPUT_DMA_QWC = 0;
    *(volatile unsigned int *)IPU_OUTPUT_DMA_MADR = (unsigned int)f->data & VIBUF_PHYSICAL_ADDRESS_MASK;
    *(volatile unsigned int *)IPU_OUTPUT_DMA_TADR = (unsigned int)f->tag & VIBUF_PHYSICAL_ADDRESS_MASK;
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

void viBufEndPut(ViBuf *f, int size)
{
    WaitSema(f->sema);
    f->readBytes += size;
    f->totalBytes += size;
    SignalSema(f->sema);
}

void ErrMessage(char *message);

int viBufAddDMA(ViBuf *f)
{
    int added = 0;
    WaitSema(f->sema);
    if (!f->isActive) {
        ErrMessage("DMA ADD not active\n");
        return 0;
    }

    setD4_CHCR(IPU_OUTPUT_DMA_IDLE_CHCR);
    unsigned int channelControl = *(volatile unsigned int *)IPU_OUTPUT_DMA_CHCR;
    int current = getFIFOindex(f, (void *)*(volatile unsigned int *)IPU_OUTPUT_DMA_MADR);
    int consumed = (current + f->n - f->dmaStart) % f->n;
    f->dmaStart = (f->dmaStart + consumed) % f->n;
    f->dmaN -= consumed;
    int next = (f->dmaStart + f->dmaN) % f->n;
    int blocks = f->readBytes / VIBUF_BLOCK_SIZE;
    f->readBytes -= blocks << VIBUF_BLOCK_SHIFT;

    if (blocks > 0) {
        int last = f->n - 1;
        int previous = (f->dmaStart + f->dmaN + last) % f->n;
        scTag2((unsigned long *)&f->tag[previous],
               (unsigned int)f->data + (previous << VIBUF_BLOCK_SHIFT), 3, VIBUF_BLOCK_SIZE / 16);
        added = 1;
    }

    int index = next;
    for (int block = 0; block < blocks; block++) {
        int id = 0;
        if (block != blocks - 1)
            id = 3;
        scTag2((unsigned long *)&f->tag[index],
               (unsigned int)f->data + (index << VIBUF_BLOCK_SHIFT), id, VIBUF_BLOCK_SIZE / 16);
        index = (index + 1) % f->n;
    }

    f->dmaN += blocks;
    if (f->dmaN != 0) {
        if (added)
            channelControl = (channelControl & VIBUF_PHYSICAL_ADDRESS_MASK) | 0x30000000;
        setD4_CHCR(channelControl | 0x100);
    }

    SignalSema(f->sema);
    return 1;
}

void setD3_CHCR(unsigned int value);

int viBufStopDMA(ViBuf *f)
{
    WaitSema(f->sema);
    f->isActive = 0;

    setD4_CHCR(IPU_OUTPUT_DMA_IDLE_CHCR);
    f->env.d4madr = *(volatile unsigned int *)IPU_OUTPUT_DMA_MADR;
    f->env.d4tadr = *(volatile unsigned int *)IPU_OUTPUT_DMA_TADR;
    f->env.d4qwc = *(volatile unsigned int *)IPU_OUTPUT_DMA_QWC;
    f->env.d4chcr = *(volatile unsigned int *)IPU_OUTPUT_DMA_CHCR;
    while (*(volatile unsigned int *)IPU_CONTROL & IPU_CONTROL_FIFO_MASK) {
    }

    setD3_CHCR(0);
    f->env.d3madr = *(volatile unsigned int *)IPU_INPUT_DMA_MADR;
    f->env.d3qwc = *(volatile unsigned int *)IPU_INPUT_DMA_QWC;
    f->env.d3chcr = *(volatile unsigned int *)IPU_INPUT_DMA_CHCR;
    f->env.ipubp = *(volatile unsigned int *)IPU_TOP;
    f->env.ipuctrl = *(volatile unsigned int *)IPU_CONTROL;
    SignalSema(f->sema);
    return 1;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/movie/vibuf", viBufRestartDMA__FP5ViBuf);

int viBufDelete(ViBuf *f)
{
    setD4_CHCR(IPU_OUTPUT_DMA_IDLE_CHCR);
    *(volatile unsigned int *)IPU_OUTPUT_DMA_QWC = 0;
    *(volatile unsigned int *)IPU_OUTPUT_DMA_MADR = 0;
    *(volatile unsigned int *)IPU_OUTPUT_DMA_TADR = 0;
    DeleteSema(f->sema);
    return 1;
}

int viBufCount(ViBuf *f)
{
    WaitSema(f->sema);
    int count = (f->dmaN << VIBUF_BLOCK_SHIFT) + f->readBytes;
    SignalSema(f->sema);
    return count;
}

int viBufFlush(ViBuf *f)
{
    WaitSema(f->sema);
    int rounded = f->readBytes + (VIBUF_BLOCK_SIZE - 1);
    int adjusted = f->readBytes + (2 * VIBUF_BLOCK_SIZE - 2);
    int limit = -1;
    if (limit < rounded)
        adjusted = rounded;
    f->readBytes = (adjusted >> VIBUF_BLOCK_SHIFT) << VIBUF_BLOCK_SHIFT;
    return SignalSema(f->sema);
}

static inline int ringPosition(int position, int capacity)
{
    return position % capacity;
}

int viBufModifyPts(ViBuf *f, TimeStamp *new_ts)
{
    int index = (f->wt_ts - f->count_ts + f->n_ts) % f->n_ts;
    int capacity = f->n << VIBUF_BLOCK_SHIFT;
    int keepScanning = 1;
    TimeStamp *entry;

    if (f->count_ts > 0) {
        while (keepScanning && (entry = &f->ts[index])->len != 0 && new_ts->len != 0) {
            if (ringPosition(entry->pos + capacity - new_ts->pos, capacity) < new_ts->len) {
                int overlap = new_ts->pos + new_ts->len - entry->pos;
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

                    f->count_ts = (f->count_ts - 1 < 0) ? 0 : f->count_ts - 1;
                }
            } else {
                keepScanning = 0;
            }

            index = (index + 1) % f->n_ts;
        }
    }

    return 0;
}

int viBufModifyPts(ViBuf *buffer, TimeStamp *timestamp);

int viBufPutTs(ViBuf *f, TimeStamp *timestamp)
{
    int result = 0;
    WaitSema(f->sema);

    if (f->count_ts < f->n_ts) {
        viBufModifyPts(f, timestamp);
        if (timestamp->pts >= 0 || timestamp->dts >= 0) {
            f->ts[f->wt_ts].pts = timestamp->pts;
            f->ts[f->wt_ts].dts = timestamp->dts;
            f->ts[f->wt_ts].pos = timestamp->pos;
            f->ts[f->wt_ts].len = timestamp->len;
            f->count_ts++;
            f->wt_ts = (f->wt_ts + 1) % f->n_ts;
        }

        result = 1;
    }

    SignalSema(f->sema);
    return result;
}

int viBufGetTs(ViBuf *f, TimeStamp *timestamp)
{
    unsigned int address = *(volatile unsigned int *)IPU_OUTPUT_DMA_MADR;
    unsigned int top = *(volatile unsigned int *)IPU_TOP;
    int bits = f->env.ipubp & 0x7F;
    int capacity = f->n << VIBUF_BLOCK_SHIFT;
    int found = 0;

    address -= (((top >> 16) & 3) + ((top >> 8) & 0xF)) << 4;
    WaitSema(f->sema);
    timestamp->pts = -1;
    timestamp->dts = -1;
    address += bits >> 3;
    address += capacity;

    int position = (address - (unsigned int)f->data) % capacity;
    int count = f->count_ts;
    int next = f->wt_ts;
    for (int index = 0; index < count && !found; index++) {
        int slot = (next - count + f->n_ts + index) % f->n_ts;
        if (ringPosition(position + capacity - f->ts[slot].pos, capacity) < f->ts[slot].len) {
            found = 1;
            timestamp->pts = f->ts[slot].pts;
            timestamp->dts = f->ts[slot].dts;
            f->ts[slot].pts = -1;
            f->ts[slot].dts = -1;
            f->count_ts -= (f->count_ts < 2) ? f->count_ts : 1;
        }
    }

    SignalSema(f->sema);
    return 1;
}
