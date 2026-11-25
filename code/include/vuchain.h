#ifndef VUCHAIN_H
#define VUCHAIN_H

#include "moby.h"

#include "sce.h"
#include "eekernel.h"
#include "eeregs.h"

void FastSitAndSpin(int cycles);
void FastMemCopy16(void *destination, void *source, int size);
void printf_stub(const char *format, ...);
void printf_stub2(const char *format, ...);
void printf_stub3(const char *format, ...);
void ResetFrameBufferForCutscene(void);

// VU1 chain stages still in flight (bits 0-4); cleared by the VIF1 DMA interrupt.
extern volatile int VifChainFlags;
#define VIF_CHAIN_ALL_STAGES 0x1F

// Spins of 0x400 cycles before VU1_syncChain gives up.
#define VU1_SYNC_TIMEOUT 100000

// Most chain bytes used in one frame.
extern int vu1_maxUse;

// D1_CHCR bits 16-31 hold the upper half of the DMA tag just read.
#define D_CHCR_TAG_MASK 0x03FF0000
#define D_CHCR_ASP_MASK 0x0000000C
#define D_CHCR_TAG_ID_MASK 0x70000000
#define D_CHCR_TAG_ID_END 0x70000000

// Tag bit marking a chain stage checkpoint (Vif1ChainCmd commands), and the four stages.
#define VIF_CHAIN_STAGE_BIT 0x02000000
#define VIF_CHAIN_STAGE_1 0x02010000
#define VIF_CHAIN_STAGE_2 0x02020000
#define VIF_CHAIN_STAGE_3 0x02040000
#define VIF_CHAIN_STAGE_4 0x02080000

// Handler ids from AddDmacHandler: VIF1 channel, then bus error.
extern int _dmacHandle[2];

#define DMA_CHANNEL_VIF1 1
#define DMA_CHANNEL_BUS_ERROR 15
// D_STAT channel interrupt mask bit for VIF1 (writing 1 toggles it).
#define D_STAT_CIM_VIF1 0x20000

// Current level (core global).
extern int Level;

// Level ids.
#define LEVEL_NOVALIS 1
#define LEVEL_RILGAR 5
#define LEVEL_KALEBO_3 0x10

#define LEVEL_COUNT 19

// Per-level size of a VU1 chain buffer.
extern int vu1_buf_table[LEVEL_COUNT];
extern int vu1_bufSize;

// Memory slot table set up by InitMemSlots (RC1 layout; only the fields known so far).
struct MEMSLOTS {
    void *base;
    unsigned char *vu1_chain[2];
    unsigned char *hudHeap;
    unsigned char unk_10[0x50];
    Vec4 collisionPoint;
};

extern MEMSLOTS MemSlots;

void InitMemSlots(void);

// The two VU1 DMA chain buffers, built and sent in turn.
extern unsigned char *vu1_DmaBuffers[];
// Which of vu1_DmaBuffers is being built.
extern int vu1_bufId;
struct DmaTag {
    unsigned int tag;
    unsigned int addr;
    unsigned int vif0;
    unsigned int vif1;
};

// Write position in the VU1 chain buffer being built. DL declares it qword *, but
// RC1's code reloads it around every packet store, which a union of pointer views
// reproduces (both in vuchain and in the packet builders elsewhere).
union Vu1ChainCursor {
    DmaTag *tag;
    unsigned int *words;
    unsigned char *bytes;
};

extern Vu1ChainCursor vu1_bufPtr;
// End of the chain built last frame, kept by VU1_swapChain (no DL counterpart).
extern unsigned char *vu1_lastChainEnd;

// Scratch memory carved from the top of the chain buffer being built.
extern unsigned char *EngScratchPad;
extern int EngScratchPadSize;
extern unsigned char *SkinVertexCache;

#define SKIN_VERTEX_CACHE_SIZE 0x2000

// Word at a byte offset from the VU1 chain write position.
#define VU1_CHAIN_WORD(offset) (vu1_bufPtr.words[(offset) / 4])
// Doubleword at a byte offset from the VU1 chain write position.
#define VU1_CHAIN_DWORD(offset) (*(unsigned long *)&vu1_bufPtr.words[(offset) / 4])

// DMA tag ids (bits 28-30): payload follows the tag inline (cnt) or sits at the address in word 1 (ref).
#define DMA_TAG_CNT 0x10000000
#define DMA_TAG_NEXT 0x20000000
#define DMA_TAG_REF 0x30000000
#define DMA_TAG_END 0x70000000

// VIF codes (bits 24-31 of a VIF word).
#define VIF_DIRECT 0x50000000
#define VIF_CHAIN_CMD 0x90000000

// GIFtag for one A+D register write: NLOOP 1 with EOP, NREG 1, REGS = A+D.
#define GIF_TAG_AD_LOW 0x8001
#define GIF_TAG_AD_HIGH 0x10000000
#define GIF_REG_AD 0xE

#define GS_REG_SCISSOR_1 0x40

// VIF codes for an inline upload: STCYCL 4/4, then UNPACK V4-32 of qcnt quadwords to VU memory.
#define VIF_STCYCL_4_4 0x01000404
#define VIF_UNPACK_V4_32 0x6C000000

// GS memory is moved in 64x64 PSMCT32 blocks of 0x4000 bytes.
#define GS_TRANSFER_BLOCK_SIZE 0x4000
#define GS_TRANSFER_BLOCK_QWC (GS_TRANSFER_BLOCK_SIZE / 16)
#define GS_LOAD_IMAGE_QWC (sizeof(sceGsLoadImage) / 16)

// Where a texture was placed in GS memory this frame; zero when it was not.
struct GsTextureLoc {
    short base;
    short mip;
};

// Screen size and the GS-space bounds derived from it (core global; set by InitViewContext).
struct Screen {
    int paramX;  // 0x00 draw width, sign-extended
    int paramY;  // 0x04 draw height, sign-extended
    int halfX;   // 0x08 paramX >> 1
    int halfY;   // 0x0C paramY >> 1
    int minX;    // 0x10 (0x800 - halfX) << 4
    int minY;    // 0x14 (0x800 - halfY) << 4
    int maxX;    // 0x18 (halfX + 0x800) << 4
    int maxY;    // 0x1C (halfY + 0x800) << 4
};

extern Screen Scrn;

// GS register blocks streamed to the VU1 by reference.
extern unsigned int Gif_Tex_Flush[12];
extern unsigned int vu1GsRegsNormal[12];
extern unsigned int vu1GsRegsEffects[12];
extern unsigned int vu1GsRegsFont[44];

void VU1_setBufSizeByLevel(void);
void VU1_initChain(void);
void VU1_swapChain(void);
void VU1_addDataRef(void *data, int qcnt);
void VU1_addVIFcode(unsigned int vifcode);
void VU1_addGSregister(unsigned int reg, unsigned long value);
void VU1_setScissor(int left, int right, int top, int bottom);
void VU1_texFlush(void);
void VU1_gsRegsNormal(void);
void VU1_gsRegsEffects(void);
void VU1_gsRegsFont(void);
void VU0_loadMicroProgram(long *data);
void VU1_sendChain(void);
void VU1_syncChain(int syncFlags);
void VU1_addDataDirect(int address, void *data, int qcnt);
void StashGSMem(void *ram, int gs_start, int size);
void UploadGSMemLinear(void *ram, int gs_loc, int width, int height);
void DMAC_VIF1_Enable(void);
void DMAC_VIF1_Disable(void);
int DMAC_VIF1_Handler(int channel);
int DMAC_BEIS_Handler(int channel);
void Vif1ChainCmd(int command);

struct MobyVu1Header {
    unsigned short qwc;
    unsigned char unk_02[14];
};

extern MobyVu1Header MobyVu1HeaderData __attribute__((section(".data")));
extern unsigned char MobyVU1Data[];
extern long MobyVU0Program[];

#endif
