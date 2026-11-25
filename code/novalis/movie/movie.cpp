#include "common.h"
#include "movie.h"
#include "disp.h"
#include "memcard.h"
#include "pad.h"
#include "read.h"
#include "sound.h"
#include "vuchain.h"

#define MOVIE_THREAD_PRIORITY 1
#define MOVIE_VBLANK_INTERRUPT 2
#define MOVIE_GIF_DMA_CHANNEL 2

// DMA controller registers: D_CTRL (bit 0 enables DMA, DMA_CONTROL_RELEASE releases the
// cycle-stealing hold) and D_STAT (writing a channel's bit acknowledges it).
#define DMA_CONTROL_ADDRESS 0x1000E000
#define DMA_STATUS_ADDRESS 0x1000E010
#define DMA_CONTROL_RELEASE 2

#define MOVIE_SKIP_DISABLED -1
#define MOVIE_SKIP_ANY_BUTTON 2
#define MOVIE_DECODER_END 3
#define MOVIE_READ_SIZE 0x10000
#define MOVIE_MIN_DEMUX_SIZE 5
#define MOVIE_SOUND_GROUP 5

// The decoder buffer, re-read from the global each time it is used.
#define DECODER_MEMORY ((MovieDecoderMemory *)movieDecoderBuffer)

// Address of the same memory through the uncached segment.
#define UNCACHED_ADDRESS(address) (((unsigned int)(address) & 0x0FFFFFFF) | 0x20000000)

static inline int movieButtonPressed(PAD *pad, int mask)
{
    return pad->bitsOn & mask;
}

// Reads bits and bitsOn as one 64-bit word: the held buttons in the low half and the
// newly pressed ones in the high half, so the chord is "hold L1+L2+R1+R2, press Start".
static inline int movieSkipChord(PAD *pad, unsigned long mask)
{
    if ((*(unsigned long *)&pad->bits & mask) != mask)
        return 0;

    return 1;
}

int playMpegMovie(int sector, int size, unsigned char *decoder_buffer, MoviePlayer *player, int language)
{
    movieDecoderBuffer = decoder_buffer;
    moviePlayer = player;
    ChangeThreadPriority(GetThreadId(), MOVIE_THREAD_PRIORITY);

    if (initAll(sector, size, language))
        readMpeg(&moviePlayer->video_dec, &moviePlayer->read_buf, &moviePlayer->str_file);

    termAll();
    movieDecoderBuffer = 0;
    moviePlayer = 0;

    return 0;
}

int readMpeg(VideoDec *decoder, ReadBuf *buffer, StrFile *file)
{
    const unsigned long skip_chord = ((unsigned long)PAD_START << 32)
                                   | PAD_L1 | PAD_L2 | PAD_R1 | PAD_R2;
    unsigned char *write_ptr;
    unsigned char *read_ptr;
    int skipped = 0;
    int started = 0;
    int decode_remaining = file->size;
    int read_remaining = decode_remaining;

    FlushCache(0);
    FlushCache(2);
    sceGsSyncV(0);

    while (decode_remaining >= MOVIE_MIN_DEMUX_SIZE && videoDecGetState(decoder) != MOVIE_DECODER_END) {
        UpdatePad();
        int skip_mode = decodeMode;

        if (skip_mode != MOVIE_SKIP_DISABLED) {
            int skip;

            if ((skip_mode == MOVIE_SKIP_ANY_BUTTON && movieButtonPressed(&padState, -1)) ||
                ((GoodiesMenuUnlocked != 0 || ChallengeMode != 0 || decodeMode != 0 || Level <= 0) &&
                 movieButtonPressed(&padState, PAD_START)))
                skip = 1;

            else
                skip = movieSkipChord(&padState, skip_chord);

            if (skip) {
                skipped = 1;
                videoDecAbort(&moviePlayer->video_dec);
            }
        }

        int space = readBufBeginPut(buffer, &write_ptr);

        if (read_remaining > 0 && space >= MOVIE_READ_SIZE) {
            int transferred = strFileRead(file, write_ptr, MOVIE_READ_SIZE, 0);
            read_remaining -= transferred;
            readBufEndPut(buffer, transferred);
        }

        proceedAudio();
        switchThread();

        int available = readBufBeginGet(buffer, &read_ptr);

        if (available > 0) {
            int transferred = sceMpegDemuxPssRing(&decoder->mpeg, read_ptr, available, buffer, buffer->capacity);
            decode_remaining -= transferred;
            readBufEndGet(buffer, transferred);
        }

        proceedAudio();

        if (!started && voBufIsFull(&moviePlayer->vo_buf) && isAudioOK()) {
            started = 1;
            startDisplay(1);
            audioDecStart(&moviePlayer->audio_dec);
        }
    }

    while (!videoDecFlush(decoder)) {
        proceedAudio();
        switchThread();
    }

    while (!videoDecIsFlushed(decoder) && videoDecGetState(decoder) != MOVIE_DECODER_END) {
        proceedAudio();
        switchThread();
    }

    endDisplay();
    audioDecReset(&moviePlayer->audio_dec);
    snd_SetMasterVolume(MOVIE_SOUND_GROUP, audioState.group_volume[MOVIE_SOUND_GROUP]);
    snd_FlushSoundCommands();

    return skipped;
}

void switchThread(void)
{
    RotateThreadReadyQueue(MOVIE_THREAD_PRIORITY);
}

int isAudioOK(void)
{
    return audioDecIsPageFull(&moviePlayer->audio_dec);
}

int initAll(int sector, int size, int language)
{
    const unsigned int dma_enable = 1;
    const unsigned int gif_acknowledge = 1 << MOVIE_GIF_DMA_CHANNEL;
    volatile unsigned int *const dma_control = (volatile unsigned int *)DMA_CONTROL_ADDRESS;
    volatile unsigned int *const dma_status = (volatile unsigned int *)DMA_STATUS_ADDRESS;
    EeThreadParams thread;
    int opened;

    *dma_control |= dma_enable | DMA_CONTROL_RELEASE;
    *dma_status = gif_acknowledge;

    readBufCreate(&moviePlayer->read_buf);
    sceMpegInit();

    videoDecCreate(&moviePlayer->video_dec, DECODER_MEMORY->mpeg_work,
                   sizeof(DECODER_MEMORY->mpeg_work),
                   (unsigned long long *)moviePlayer->vi_buf_data,
                   (unsigned long long *)DECODER_MEMORY->input_tags, MOVIE_INPUT_SECTORS,
                   moviePlayer->vi_buf_ts, MOVIE_TIMESTAMP_COUNT);
    audioDecCreate(&moviePlayer->audio_dec, moviePlayer->audio_buf, MOVIE_AUDIO_BUFFER_SIZE,
                   DECODER_MEMORY->adpcm_staging);
    videoDecSetStream(&moviePlayer->video_dec, sceMpegStrM2V, 0, videoCallback, &moviePlayer->read_buf);
    videoDecSetStream(&moviePlayer->video_dec, sceMpegStrADPCM, language,
                      (MpegStreamCallback)pcmCallback, &moviePlayer->read_buf);

    voBufCreate(&moviePlayer->vo_buf, (VoData *)UNCACHED_ADDRESS(DECODER_MEMORY->output_frames),
                DECODER_MEMORY->output_tags, sizeof(DECODER_MEMORY->output_frames) / sizeof(VoData));

    thread.stack = moviePlayer->decoder_stack;
    thread.entry = videoDecMain;
    thread.stack_size = MOVIE_DECODER_STACK_SIZE;
    thread.priority = MOVIE_THREAD_PRIORITY;
    thread.gp = &_gp;
    thread.option = 0;

    int thread_id = CreateThread(&thread);
    movieDecoderThread = thread_id;
    _StartThread(thread_id, &moviePlayer->video_dec);

    if (!strFileBegin(&moviePlayer->str_file, sector, size)) {
        opened = 0;
        printf_stub("Can't Open movie
");
    } else {
        opened = 1;
    }

    moviePlayer->video_dec.hid_vblank = AddIntcHandler(MOVIE_VBLANK_INTERRUPT, vblankHandler, 0);
    EnableIntc(MOVIE_VBLANK_INTERRUPT);
    moviePlayer->video_dec.hid_endimage = AddDmacHandler(MOVIE_GIF_DMA_CHANNEL, handler_endimage, 0);
    EnableDmac(MOVIE_GIF_DMA_CHANNEL);

    return opened;
}

void termAll(void)
{
    sceCdSync(0);
    readBufDelete(&moviePlayer->read_buf);
    voBufDelete(&moviePlayer->vo_buf);
    TerminateThread(movieDecoderThread);
    DeleteThread(movieDecoderThread);
    DisableDmac(MOVIE_GIF_DMA_CHANNEL);
    RemoveDmacHandler(MOVIE_GIF_DMA_CHANNEL, moviePlayer->video_dec.hid_endimage);
    DisableIntc(MOVIE_VBLANK_INTERRUPT);
    RemoveIntcHandler(MOVIE_VBLANK_INTERRUPT, moviePlayer->video_dec.hid_vblank);
    videoDecDelete(&moviePlayer->video_dec);
    audioDecDelete(&moviePlayer->audio_dec);
    strFileDelete(&moviePlayer->str_file);
    sceCdSync(0);
    *(unsigned int *)DMA_CONTROL_ADDRESS &= ~DMA_CONTROL_RELEASE;
}

void ErrMessage(char *message)
{
    printf_stub("[ Error ] %s\n", message);
}

void proceedAudio(void)
{
    audioDecSend(&moviePlayer->audio_dec);
}

// The rest of movie.cpp's small data, after its error format. Defined last so the functions above reach it
// with lui, as retail does.
unsigned char *movieDecoderBuffer = 0;
MoviePlayer *moviePlayer = 0;
int movieDecoderThread = 0;
int MovieSdata161354 = 0;
