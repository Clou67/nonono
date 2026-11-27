#ifndef SCE_H
#define SCE_H

// Saved IPU input/output DMA state (Sony SDK / DL debug layout).
struct sceIpuDmaEnv {
    unsigned int d4madr;
    unsigned int d4tadr;
    unsigned int d4qwc;
    unsigned int d4chcr;
    unsigned int d3madr;
    unsigned int d3qwc;
    unsigned int d3chcr;
    unsigned int ipubp;
    unsigned int ipuctrl;
};

// Sony SDK (libdma, libgraph, kernel). These libraries are C, so they keep C linkage.

struct ReadBuf;
struct sceMpeg;
struct sceMpegCbData;

struct sceMpegCbDataStr {
    int type;
    int channel;
    unsigned char *data;
    int length;
    long pts;
    long dts;
};

struct sceMpegCbDataTimeStamp {
    int type;
    long pts;
    long dts;
};

struct sceMpegCbDataError {
    int type;
    char *message;
};

struct tD_CHCR {
    unsigned int DIR : 1;
    unsigned int p0 : 1;
    unsigned int MOD : 2;
    unsigned int ASP : 2;
    unsigned int TTE : 1;
    unsigned int TIE : 1;
    unsigned int STR : 1;
    unsigned int p1 : 7;
    unsigned int TAG : 16;
};

struct sceDmaTag;

// DMA channel register image; the reserved words preserve the 16-byte register stride.
struct sceDmaChan {
    union {
        unsigned int chcr;
        tD_CHCR chcrFields;
    };
    unsigned int p0[3];
    void *madr;
    unsigned int p1[3];
    unsigned int qwc;
    unsigned int p2[3];
    sceDmaTag *tadr;
    unsigned int p3[3];
    void *as0;
    unsigned int p4[3];
    void *as1;
    unsigned int p5[3];
    unsigned int p6[4];
    unsigned int p7[4];
    void *sadr;
    unsigned int p8[3];
};

// GS image readback packet built by libgraph (112 bytes).
struct sceGsStoreImage {
    unsigned long data[14];
};

// libgraph register images (Sony libgraph.h layouts).
typedef unsigned int u_long128 __attribute__((mode(TI)));

struct SifRpcClient {
    void *packet;
    unsigned int packetId;
    int threadId;
    unsigned int mode;
    unsigned int command;
    void *buffer;
    void *callbackBuffer;
    void (*callback)(void *);
    void *callbackData;
    void *server;
};

struct SifDmaTransfer {
    void *source;
    void *destination;
    int size;
    int attributes;
};

struct sceCdRMode {
    unsigned char trycount;
    unsigned char spindlctrl;
    unsigned char datapattern;
    unsigned char pad;
};

struct sceCdCLOCK {
    unsigned char stat;
    unsigned char second;
    unsigned char minute;
    unsigned char hour;
    unsigned char pad;
    unsigned char day;
    unsigned char month;
    unsigned char year;
};

struct sceGsZbuf {
    unsigned long ZBP : 9;
    unsigned long pad09 : 15;
    unsigned long PSM : 4;
    unsigned long pad28 : 4;
    unsigned long ZMSK : 1;
    unsigned long pad33 : 31;
};

struct sceGsFrame {
    unsigned long FBP : 9;
    unsigned long pad09 : 7;
    unsigned long FBW : 6;
    unsigned long pad22 : 2;
    unsigned long PSM : 6;
    unsigned long pad30 : 2;
    unsigned long FBMSK : 32;
};

struct sceGsDispfb {
    unsigned long FBP : 9;
    unsigned long FBW : 6;
    unsigned long PSM : 5;
    unsigned long pad20 : 12;
    unsigned long DBX : 11;
    unsigned long DBY : 11;
    unsigned long pad54 : 10;
};

struct sceGsDispEnv {
    unsigned long pmode;
    unsigned long smode2;
    sceGsDispfb dispfb;
    unsigned long display;
    unsigned long bgcolor;
};

struct sceGsDrawEnv1 {
    sceGsFrame frame1;
    unsigned long frame1addr;
    sceGsZbuf zbuf1;
    unsigned long zbuf1addr;
    unsigned long xyoffset1;
    unsigned long xyoffset1addr;
    unsigned long scissor1;
    unsigned long scissor1addr;
    unsigned long prmodecont;
    unsigned long prmodecontaddr;
    unsigned long colclamp;
    unsigned long colclampaddr;
    unsigned long dthe;
    unsigned long dtheaddr;
    unsigned long test1;
    unsigned long test1addr;
};

struct sceGifTag {
    unsigned long NLOOP : 15;
    unsigned long EOP : 1;
    unsigned long pad16 : 16;
    unsigned long id : 14;
    unsigned long PRE : 1;
    unsigned long PRIM : 11;
    unsigned long FLG : 2;
    unsigned long NREG : 4;
    unsigned long REGS0 : 4;
    unsigned long REGS1 : 4;
    unsigned long REGS2 : 4;
    unsigned long REGS3 : 4;
    unsigned long REGS4 : 4;
    unsigned long REGS5 : 4;
    unsigned long REGS6 : 4;
    unsigned long REGS7 : 4;
    unsigned long REGS8 : 4;
    unsigned long REGS9 : 4;
    unsigned long REGS10 : 4;
    unsigned long REGS11 : 4;
    unsigned long REGS12 : 4;
    unsigned long REGS13 : 4;
    unsigned long REGS14 : 4;
    unsigned long REGS15 : 4;
} __attribute__((aligned(16)));

struct sceGsBitbltbuf {
    unsigned long SBP : 14;
    unsigned long pad14 : 2;
    unsigned long SBW : 6;
    unsigned long pad22 : 2;
    unsigned long SPSM : 6;
    unsigned long pad30 : 2;
    unsigned long DBP : 14;
    unsigned long pad46 : 2;
    unsigned long DBW : 6;
    unsigned long pad54 : 2;
    unsigned long DPSM : 6;
    unsigned long pad62 : 2;
};

struct sceGsTrxpos {
    unsigned long SSAX : 11;
    unsigned long pad11 : 5;
    unsigned long SSAY : 11;
    unsigned long pad27 : 5;
    unsigned long DSAX : 11;
    unsigned long pad43 : 5;
    unsigned long DSAY : 11;
    unsigned long DIR : 2;
    unsigned long pad61 : 3;
};

struct sceGsTrxreg {
    unsigned long RRW : 12;
    unsigned long pad12 : 20;
    unsigned long RRH : 12;
    unsigned long pad44 : 20;
};

struct sceGsTrxdir {
    unsigned long XDR : 2;
    unsigned long pad02 : 62;
};

// GS image upload packet built by libgraph (96 bytes).
struct sceGsLoadImage {
    sceGifTag giftag0;
    sceGsBitbltbuf bitbltbuf;
    long bitbltbufaddr;
    sceGsTrxpos trxpos;
    long trxposaddr;
    sceGsTrxreg trxreg;
    long trxregaddr;
    sceGsTrxdir trxdir;
    long trxdiraddr;
    sceGifTag giftag1;
} __attribute__((aligned(16)));

// Sony libgraph.h register value builder.
#define SCE_GS_SET_TEX0(tbp, tbw, psm, tw, th, tcc, tfx, cbp, cpsm, csm, csa, cld) \
    ((unsigned long)(tbp) | ((unsigned long)(tbw) << 14) | ((unsigned long)(psm) << 20) | \
     ((unsigned long)(tw) << 26) | ((unsigned long)(th) << 30) | ((unsigned long)(tcc) << 34) | \
     ((unsigned long)(tfx) << 35) | ((unsigned long)(cbp) << 37) | ((unsigned long)(cpsm) << 51) | \
     ((unsigned long)(csm) << 55) | ((unsigned long)(csa) << 56) | ((unsigned long)(cld) << 61))
#define SCE_GS_SET_TEX1(lcm, mxl, mmag, mmin, mtba, l, k) \
    ((unsigned long)(lcm) | ((unsigned long)(mxl) << 2) | ((unsigned long)(mmag) << 5) | \
     ((unsigned long)(mmin) << 6) | ((unsigned long)(mtba) << 9) | ((unsigned long)(l) << 19) | \
     ((unsigned long)(k) << 32))
#define SCE_GS_SET_MIPTBP1(tbp1, tbw1, tbp2, tbw2, tbp3, tbw3) \
    ((unsigned long)(tbp1) | ((unsigned long)(tbw1) << 14) | ((unsigned long)(tbp2) << 20) | \
     ((unsigned long)(tbw2) << 34) | ((unsigned long)(tbp3) << 40) | ((unsigned long)(tbw3) << 54))
#define SCE_GS_SET_ZBUF(zbp, psm, zmsk) ((unsigned long)(zbp) | ((unsigned long)(psm) << 24) | ((unsigned long)(zmsk) << 32))

struct EeSemaParam {
    int count;
    int maxCount;
    int initialCount;
    int waitThreads;
    unsigned int attributes;
    unsigned int option;
};

extern "C" {
int CreateSema(EeSemaParam *parameters);
int DeleteSema(int semaphore);
int SignalSema(int semaphore);
int WaitSema(int semaphore);
int sceMpegIsEnd(sceMpeg *mpeg);
int sceMpegGetPicture(sceMpeg *mpeg, struct VoData *frame, int stride);
int sceMpegReset(sceMpeg *mpeg);
int sceMpegCreate(sceMpeg *mpeg, unsigned char *work, int workSize);
int sceMpegAddCallback(sceMpeg *mpeg, int type, int (*callback)(sceMpeg *, sceMpegCbData *, void *), void *argument);
unsigned int videoDecIsDecoderEmpty(sceMpeg *mpeg);
int videoDecRelease(sceMpeg *mpeg);
int sceMpegAddStrCallback(sceMpeg *mpeg, int type, int channel, int (*callback)(sceMpeg *, sceMpegCbData *, void *), void *argument);
void sceSifInitRpc(int mode);
int sceSifBindRpc(SifRpcClient *client, int server, int mode);
int sceSifCheckStatRpc(SifRpcClient *client);
int sceSifCallRpc(SifRpcClient *client, int command, int mode, void *send, int sendSize,
                  void *receive, int receiveSize, void (*callback)(void *), void *callbackData);
int sceCdRead(unsigned int sector, unsigned int sectors, void *destination, sceCdRMode *mode);
int sceCdSync(int mode);
int sceCdGetError(void);
int sceCdBreak(void);
int sceCdReadClock(sceCdCLOCK *clock);
int sceScfGetLocalTimefromRTC(sceCdCLOCK *clock);
void FlushCache(int operation);
int sceSifSetDma(SifDmaTransfer *transfer, int count);
void *sceSifAllocIopHeap(unsigned int size);
int sceSifFreeIopHeap(void *address);
int sceSifLoadModuleBuffer(void *address, int argLength, const char *args);
int sceSifDmaStat(int id);
int DIntr(void);
int EIntr(void);
int TerminateThread(int thread);
int DeleteThread(int thread);
int DisableIntc(int cause);
int RemoveIntcHandler(int cause, int handler);
int RotateThreadReadyQueue(int priority);
int GetThreadId(void);
int ChangeThreadPriority(int thread, int priority);

sceDmaChan *sceDmaGetChan(int channel);
void sceDmaSend(sceDmaChan *channel, void *tag);

int sceGsExecLoadImage(sceGsLoadImage *image, u_long128 *source);
int sceGsSetDefLoadImage(sceGsLoadImage *image, short bp, short bw, short psm, short x, short y, short w, short h);
int sceGsSetDefStoreImage(sceGsStoreImage *image, short bp, short bw, short psm, short x, short y, short w, short h);
int sceGsExecStoreImage(sceGsStoreImage *image, void *destination);
int sceGsSyncV(int mode);
int sceMpegDemuxPssRing(sceMpeg *mpeg, unsigned char *source, int bytes, ReadBuf *buffer, int capacity);
int sceGsSyncPath(int mode, unsigned short timeout);
void sceGsSetDefDispEnv(sceGsDispEnv *disp, short psm, short w, short h, short dx, short dy);
void sceGsSetDefDrawEnv(sceGsDrawEnv1 *draw, short psm, short w, short h, short ztest, short zpsm);
void sceGsPutDispEnv(sceGsDispEnv *disp);
int sceGsPutDrawEnv(sceGifTag *giftag);

int AddDmacHandler(int channel, int (*handler)(int), int next);
int RemoveDmacHandler(int channel, int handlerId);
int EnableDmac(int channel);
int DisableDmac(int channel);
}

// Global pointer value, set by the linker.
extern int _gp;

// EE kernel thread descriptor.
struct EeThreadParams {
    int status;
    void (*entry)(void *);
    void *stack;
    int stack_size;
    void *gp;
    int priority;
    int current_priority;
    int attributes;
    unsigned int option;
};

extern "C" {
void sceMpegInit(void);
int CreateThread(EeThreadParams *params);
int _StartThread(int thread, void *argument);
int AddIntcHandler(int cause, int (*handler)(int), int next);
int EnableIntc(int cause);
}

// EE timer 1 count register (eeregs.h).
#define T1_COUNT ((volatile unsigned int *)(0x10000800))

#endif
