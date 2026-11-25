#include "common.h"
#include "vuchain.h"

volatile int VifChainFlags = 0;

void VU0_loadMicroProgram(long *data)
{
    while (*D0_CHCR & D_CHCR_STR) {
        FastSitAndSpin(16);
    }

    *D0_QWC = 0;
    *D0_TADR = (unsigned int)data & 0x0FFFFFFF;
    *D0_CHCR = 0x145;

    while (*D0_CHCR & D_CHCR_STR) {
        FastSitAndSpin(16);
    }
}

void VU1_setBufSizeByLevel(void)
{
    int level = Level;

    if (level >= LEVEL_COUNT) {
        level = 0;
    }

    vu1_bufSize = vu1_buf_table[level];
}

void VU1_initChain(void)
{
    vu1_DmaBuffers[0] = MemSlots.vu1_chain[0];
    vu1_DmaBuffers[1] = MemSlots.vu1_chain[1];
    vu1_bufId = 0;
    vu1_bufPtr.bytes = vu1_DmaBuffers[0];

    EngScratchPad = vu1_bufPtr.bytes + vu1_bufSize - EngScratchPadSize;
    SkinVertexCache = EngScratchPad - SKIN_VERTEX_CACHE_SIZE;
}

void VU1_swapChain(void)
{
    vu1_bufId = 1 - vu1_bufId;
    vu1_lastChainEnd = vu1_bufPtr.bytes;
    vu1_bufPtr.bytes = vu1_DmaBuffers[vu1_bufId];

    EngScratchPad = vu1_bufPtr.bytes + vu1_bufSize - EngScratchPadSize;
    SkinVertexCache = EngScratchPad - SKIN_VERTEX_CACHE_SIZE;
}

void VU1_sendChain(void)
{
    int overflow = 0;
    int used;

    VifChainFlags |= VIF_CHAIN_ALL_STAGES;
    used = vu1_bufPtr.bytes - vu1_DmaBuffers[vu1_bufId];

    if (used > vu1_maxUse) {
        vu1_maxUse = used;

        if (used > vu1_bufSize) {
            printf_stub("vu1 chain overflow\n");
            overflow = 1;
        }
    }

    if (!overflow) {
        sceDmaChan *channel;

        VU1_CHAIN_WORD(0) = DMA_TAG_END;
        VU1_CHAIN_WORD(4) = 0;
        VU1_CHAIN_WORD(8) = 0;
        VU1_CHAIN_WORD(12) = 0;

        channel = sceDmaGetChan(DMA_CHANNEL_VIF1);
        channel->chcr |= 0xC0;
        FlushCache(0);
        sceDmaSend(channel, vu1_DmaBuffers[vu1_bufId]);
        return;
    }

    VifChainFlags = 0;
}

void VU1_syncChain(int syncFlags)
{
    int spins = 0;

    for (;;) {
        if (!(VifChainFlags & syncFlags)) {
            return;
        }

        FastSitAndSpin(0x400);

        if (spins <= VU1_SYNC_TIMEOUT) {
            spins++;
            continue;
        }

        printf_stub("vu1 syncChain sit-and-spin timeout.\n");
        ResetFrameBufferForCutscene();
        return;
    }
}

void VU1_addDataRef(void *data, int qcnt)
{
    VU1_CHAIN_WORD(0) = qcnt | DMA_TAG_REF;
    VU1_CHAIN_WORD(4) = (unsigned int)data;
    VU1_CHAIN_WORD(8) = 0;
    VU1_CHAIN_WORD(12) = 0;

    vu1_bufPtr.bytes += 16;
}

TEXT_PADDING(0xAF82C020, 0x00000000);

void VU1_addDataDirect(int address, void *data, int qcnt)
{
    VU1_CHAIN_WORD(0) = qcnt | DMA_TAG_CNT;
    VU1_CHAIN_WORD(4) = 0;
    VU1_CHAIN_WORD(8) = VIF_STCYCL_4_4;
    VU1_CHAIN_WORD(12) = address | (qcnt << 16) | VIF_UNPACK_V4_32;

    vu1_bufPtr.bytes += 16;

    FastMemCopy16(vu1_bufPtr.bytes, data, qcnt << 4);
    vu1_bufPtr.bytes += qcnt << 4;
}

TEXT_PADDING(0xAF82C020, 0x00000000);

void VU1_addVIFcode(unsigned int vifcode)
{
    VU1_CHAIN_WORD(0) = DMA_TAG_CNT;
    VU1_CHAIN_WORD(4) = 0;
    VU1_CHAIN_WORD(8) = 0;
    VU1_CHAIN_WORD(12) = vifcode;

    vu1_bufPtr.bytes += 16;
}

void VU1_addGSregister(unsigned int reg, unsigned long value)
{
    VU1_CHAIN_WORD(0) = DMA_TAG_CNT | 2;
    VU1_CHAIN_WORD(4) = 0;
    VU1_CHAIN_WORD(8) = 0;
    VU1_CHAIN_WORD(12) = VIF_DIRECT | 2;

    VU1_CHAIN_WORD(16) = GIF_TAG_AD_LOW;
    VU1_CHAIN_WORD(20) = GIF_TAG_AD_HIGH;
    VU1_CHAIN_WORD(24) = GIF_REG_AD;
    VU1_CHAIN_WORD(28) = 0;

    VU1_CHAIN_DWORD(32) = value;
    VU1_CHAIN_WORD(40) = reg;
    VU1_CHAIN_WORD(44) = 0;

    vu1_bufPtr.bytes += 48;
}

TEXT_PADDING(0xAF82C020, 0x00000000);

void VU1_setScissor(int left, int right, int top, int bottom)
{
    int maxX = Scrn.paramX - 1;
    int maxY = Scrn.paramY - 1;

    VU1_CHAIN_WORD(0) = DMA_TAG_CNT | 2;
    VU1_CHAIN_WORD(4) = 0;
    VU1_CHAIN_WORD(8) = 0;
    VU1_CHAIN_WORD(12) = VIF_DIRECT | 2;

    if (right > maxX) {
        right = maxX;
    }

    if (left < 0) {
        left = 0;
    }

    if (top < 0) {
        top = 0;
    }

    if (bottom > maxY) {
        bottom = maxY;
    }

    VU1_CHAIN_WORD(16) = GIF_TAG_AD_LOW;
    VU1_CHAIN_WORD(20) = GIF_TAG_AD_HIGH;
    VU1_CHAIN_WORD(24) = GIF_REG_AD;
    VU1_CHAIN_WORD(28) = 0;

    VU1_CHAIN_DWORD(32) = (unsigned long)left | ((unsigned long)right << 16)
                                         | ((unsigned long)top << 32) | ((unsigned long)bottom << 48);
    VU1_CHAIN_WORD(40) = GS_REG_SCISSOR_1;
    VU1_CHAIN_WORD(44) = 0;

    vu1_bufPtr.bytes += 48;
}

TEXT_PADDING(0x27BD0030, 0x00000000);

void VU1_texFlush(void)
{
    VU1_CHAIN_WORD(0) = DMA_TAG_REF | 3;
    VU1_CHAIN_WORD(4) = (unsigned int)Gif_Tex_Flush;
    VU1_CHAIN_WORD(8) = 0;
    VU1_CHAIN_WORD(12) = VIF_DIRECT | 3;

    vu1_bufPtr.bytes += 16;
}

void VU1_gsRegsNormal(void)
{
    VU1_CHAIN_WORD(0) = DMA_TAG_REF | 3;
    VU1_CHAIN_WORD(4) = (unsigned int)vu1GsRegsNormal;
    VU1_CHAIN_WORD(8) = 0;
    VU1_CHAIN_WORD(12) = VIF_DIRECT | 3;

    vu1_bufPtr.bytes += 16;
}

void VU1_gsRegsEffects(void)
{
    VU1_CHAIN_WORD(0) = DMA_TAG_REF | 3;
    VU1_CHAIN_WORD(4) = (unsigned int)vu1GsRegsEffects;
    VU1_CHAIN_WORD(8) = 0;
    VU1_CHAIN_WORD(12) = VIF_DIRECT | 3;

    vu1_bufPtr.bytes += 16;
}

TEXT_PADDING(0xAF82C020, 0x00000000);

void VU1_gsRegsFont(void)
{
    VU1_CHAIN_WORD(0) = DMA_TAG_REF | 11;
    VU1_CHAIN_WORD(4) = (unsigned int)vu1GsRegsFont;
    VU1_CHAIN_WORD(8) = 0;
    VU1_CHAIN_WORD(12) = VIF_DIRECT | 11;

    vu1_bufPtr.bytes += 16;
}

void StashGSMem(void *ram, int gs_start, int size)
{
    sceGsStoreImage image;
    int offset = 0;
    int remaining = (size + GS_TRANSFER_BLOCK_SIZE - 1) & ~(GS_TRANSFER_BLOCK_SIZE - 1);

    while (remaining > 0) {
        sceGsSetDefStoreImage(&image, (gs_start + offset) >> 8, 1, 0, 0, 0, 64, 64);
        remaining -= GS_TRANSFER_BLOCK_SIZE;
        FlushCache(0);
        sceGsExecStoreImage(&image, (unsigned char *)ram + offset);
        offset += GS_TRANSFER_BLOCK_SIZE;
        sceGsSyncPath(0, 0);
    }
}

void UploadGSMemLinear(void *ram, int gs_loc, int width, int height)
{
    int offset = 0;
    int remaining = (width + GS_TRANSFER_BLOCK_SIZE - 1) & ~(GS_TRANSFER_BLOCK_SIZE - 1);

    while (remaining > 0) {
        VU1_CHAIN_WORD(0) = DMA_TAG_CNT | GS_LOAD_IMAGE_QWC;
        VU1_CHAIN_WORD(4) = 0;
        VU1_CHAIN_WORD(8) = 0;
        VU1_CHAIN_WORD(12) = VIF_DIRECT | GS_LOAD_IMAGE_QWC;
        vu1_bufPtr.bytes += 16;

        remaining -= GS_TRANSFER_BLOCK_SIZE;
        sceGsSetDefLoadImage((sceGsLoadImage *)vu1_bufPtr.bytes, (gs_loc + offset) >> 8, 1, 0, 0, 0, 64, 64);
        vu1_bufPtr.bytes += sizeof(sceGsLoadImage);

        VU1_CHAIN_WORD(0) = DMA_TAG_REF | GS_TRANSFER_BLOCK_QWC;
        VU1_CHAIN_WORD(4) = (unsigned int)((unsigned char *)ram + offset);
        VU1_CHAIN_WORD(8) = 0;
        VU1_CHAIN_WORD(12) = VIF_DIRECT | GS_TRANSFER_BLOCK_QWC;
        vu1_bufPtr.bytes += 16;

        offset += GS_TRANSFER_BLOCK_SIZE;
    }
}

void DMAC_VIF1_Enable(void)
{
    if (_dmacHandle[0] != 0 || _dmacHandle[1] != 0) {
        return;
    }

    if (!(DGET_D_STAT() & D_STAT_CIM_VIF1)) {
        DPUT_D_STAT(D_STAT_CIM_VIF1);
    }

    _dmacHandle[0] = AddDmacHandler(DMA_CHANNEL_VIF1, DMAC_VIF1_Handler, 0);
    _dmacHandle[1] = AddDmacHandler(DMA_CHANNEL_BUS_ERROR, DMAC_BEIS_Handler, 0);
    EnableDmac(DMA_CHANNEL_VIF1);
}

void DMAC_VIF1_Disable(void)
{
    if (DGET_D_STAT() & D_STAT_CIM_VIF1) {
        DPUT_D_STAT(D_STAT_CIM_VIF1);
    }

    RemoveDmacHandler(DMA_CHANNEL_VIF1, _dmacHandle[0]);
    RemoveDmacHandler(DMA_CHANNEL_BUS_ERROR, _dmacHandle[1]);
    DisableDmac(DMA_CHANNEL_VIF1);

    _dmacHandle[0] = 0;
    _dmacHandle[1] = 0;
}

int DMAC_VIF1_Handler(int channel)
{
    unsigned int chcr = *D1_CHCR;
    unsigned int tag = chcr & D_CHCR_TAG_MASK;

    if (*D1_TADR != 0 && (chcr & D_CHCR_ASP_MASK)) {
        if ((chcr & D_CHCR_TAG_ID_MASK) == D_CHCR_TAG_ID_END) {
            VifChainFlags &= ~0x1F;
        } else {
            if (tag & VIF_CHAIN_STAGE_BIT) {
                switch (tag) {
                case VIF_CHAIN_STAGE_1:
                    VifChainFlags &= ~0x2;
                    break;
                case VIF_CHAIN_STAGE_2:
                    VifChainFlags &= ~0x4;
                    break;
                case VIF_CHAIN_STAGE_3:
                    VifChainFlags &= ~0x8;
                    break;
                case VIF_CHAIN_STAGE_4:
                    VifChainFlags &= ~0x10;
                    break;
                }
            }

            *D1_CHCR = chcr | D_CHCR_STR;
        }
    }

    ExitHandler();
    return 0;
}

int DMAC_BEIS_Handler(int channel)
{
    unsigned int chcr = *D1_CHCR;
    unsigned int tadr = *D1_TADR;

    printf_stub("DMAC(15) - Bus Error\n");
    printf_stub("D1_CHCR=%X\nD1_TADR=%X", chcr, tadr);
    printf_stub("Why doesn't this work?");

    for (;;) {
    }
}

// Appends a VIF1 command packet (command word plus three zero words) to the VU1 chain.
void Vif1ChainCmd(int command)
{
    unsigned char *chainHead = vu1_bufPtr.bytes;
    unsigned int *packet = (unsigned int *)chainHead;

    chainHead += 16;
    vu1_bufPtr.bytes = chainHead;

    packet[0] = command + VIF_CHAIN_CMD;
    packet[1] = 0;
    packet[2] = 0;
    packet[3] = 0;
}

TEXT_PADDING(0x27BD0030, 0x00000000, 0xE4A301BC, 0x00000000, 0x27BD00F0, 0x00000000);
