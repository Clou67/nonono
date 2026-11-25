#include "common.h"
#include "movie.h"

// MPEG sequence end code (as stream bytes) that videoDecFlush feeds the decoder.
unsigned char VideoSequenceEndCode[4] = { 0x00, 0x00, 0x01, 0xB7 };

enum {
    MPEG_CALLBACK_ERROR = 0,
    MPEG_CALLBACK_NO_DATA = 1,
    MPEG_CALLBACK_STOP_DMA = 2,
    MPEG_CALLBACK_RESTART_DMA = 3,
    MPEG_CALLBACK_TIMESTAMP = 5
};

int videoDecCreate(VideoDec *decoder, unsigned char *work, int workSize, unsigned long long *input,
                   unsigned long long *tags, int sectors, TimeStamp *timestamps, int timestampCount)
{
    sceMpegCreate(&decoder->mpeg, work, workSize);
    sceMpegAddCallback(&decoder->mpeg, MPEG_CALLBACK_ERROR, (MpegStreamCallback)mpegError, 0);
    sceMpegAddCallback(&decoder->mpeg, MPEG_CALLBACK_NO_DATA, mpegNodata, 0);
    sceMpegAddCallback(&decoder->mpeg, MPEG_CALLBACK_STOP_DMA, (MpegStreamCallback)mpegStopVideoDMA, 0);
    sceMpegAddCallback(&decoder->mpeg, MPEG_CALLBACK_RESTART_DMA, (MpegStreamCallback)mpegRestartVideoDMA, 0);
    sceMpegAddCallback(&decoder->mpeg, MPEG_CALLBACK_TIMESTAMP, (MpegStreamCallback)mpegTimeStamp, 0);
    videoDecReset(decoder);
    viBufCreate(&decoder->vibuf, input, tags, sectors, timestamps, timestampCount);
    return 1;
}

TEXT_PADDING(0x27BD0010, 0x00000000);

int videoDecSetStream(VideoDec *decoder, int type, int channel, MpegStreamCallback callback, void *argument)
{
    sceMpegAddStrCallback(&decoder->mpeg, type, channel, callback, argument);
    return 1;
}

int videoDecBeginPut(VideoDec *decoder, unsigned char **first, int *firstSize, unsigned char **second, int *secondSize)
{
    return viBufBeginPut(&decoder->vibuf, first, firstSize, second, secondSize);
}

void videoDecEndPut(VideoDec *decoder, int size)
{
    viBufEndPut(&decoder->vibuf, size);
}

void videoDecReset(VideoDec *decoder)
{
    decoder->state = 0;
}

int videoDecDelete(VideoDec *decoder)
{
    viBufDelete(&decoder->vibuf);
    videoDecRelease(&decoder->mpeg);
    return 1;
}

void videoDecAbort(VideoDec *decoder)
{
    decoder->state = 1;
}

unsigned int videoDecGetState(VideoDec *decoder)
{
    return decoder->state;
}

unsigned int videoDecSetState(VideoDec *decoder, unsigned int state)
{
    unsigned int oldState = decoder->state;
    decoder->state = state;
    return oldState;
}

int videoDecPutTs(VideoDec *decoder, long pts, long dts, unsigned char *position, int size)
{
    TimeStamp timestamp;
    timestamp.pts = pts;
    timestamp.dts = dts;
    timestamp.pos = position - (unsigned char *)decoder->vibuf.data;
    timestamp.len = size;
    return viBufPutTs(&moviePlayer->video_dec.vibuf, &timestamp);
}

int videoDecInputCount(VideoDec *decoder)
{
    return viBufCount(&decoder->vibuf);
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/movie/videodec", func_0031CBA8);

#ifdef ALLOW_NON_MATCHING
enum {
    MPEG_PHYSICAL_ADDRESS_MASK = 0x0FFFFFFF,
    MPEG_UNCACHED_ACCELERATED_BASE = 0x20000000,
    VIDEO_DECODER_FLUSHING = 2
};

int videoDecFlush(VideoDec *decoder)
{
    unsigned char sequenceEnd[4] = { 0x00, 0x00, 0x01, 0xB7 };
    unsigned char *first;
    int firstSize;
    unsigned char *second;
    int secondSize;

    videoDecBeginPut(decoder, &first, &firstSize, &second, &secondSize);

    if (firstSize + secondSize < (int)sizeof(sequenceEnd))
        return 0;

    int copied = cpy2area((unsigned char *)(((unsigned int)first & MPEG_PHYSICAL_ADDRESS_MASK) | MPEG_UNCACHED_ACCELERATED_BASE),
                          firstSize,
                          (unsigned char *)(((unsigned int)second & MPEG_PHYSICAL_ADDRESS_MASK) | MPEG_UNCACHED_ACCELERATED_BASE),
                          secondSize, sequenceEnd, sizeof(sequenceEnd), 0, 0);
    videoDecEndPut(&moviePlayer->video_dec, copied);
    viBufFlush(&decoder->vibuf);

    if (decoder->state == 0)
        decoder->state = VIDEO_DECODER_FLUSHING;
    return 1;
}
#else
INCLUDE_ASM("code/_generated/novalis/nonmatchings/movie/videodec", videoDecFlush__FP8VideoDec);
#endif

int videoDecIsFlushed(VideoDec *decoder)
{
    int flushed = 0;
    if (videoDecInputCount(decoder) == 0)
        flushed = videoDecIsDecoderEmpty(&decoder->mpeg) > 0;
    return flushed;
}

enum {
    VIDEO_DECODER_ABORTED = 1,
    VIDEO_DECODER_FINISHED = 3
};

void videoDecMain(void *argument)
{
    VideoDec *decoder = (VideoDec *)argument;
    viBufReset(&decoder->vibuf);
    voBufReset(&moviePlayer->vo_buf);
    decBs0(decoder);

    while (moviePlayer->vo_buf.count != 0 && videoDecGetState(decoder) != VIDEO_DECODER_ABORTED) {
    }

    videoDecSetState(decoder, VIDEO_DECODER_FINISHED);
}

void setImageTag(unsigned int (*packets)[2], VoData *frame, int width, int height);
void printf_stub(const char *format, ...);

int decBs0(VideoDec *decoder)
{
    int result = 1;
    while (!sceMpegIsEnd(&decoder->mpeg)) {
        if (videoDecGetState(decoder) == VIDEO_DECODER_ABORTED) {
            result = -1;
            printf_stub("decode thread: aborted\n");
            break;
        }

        VoData *frame;
        while ((frame = voBufGetData(&moviePlayer->vo_buf)) == 0) {
            switchThread();
        }
        if (sceMpegGetPicture(&decoder->mpeg, frame, 0x340) < 0)
            ErrMessage("sceMpegGetPicture() decode error");

        if (decoder->mpeg.frameCount == 0) {
            int width = decoder->mpeg.width;
            int height = decoder->mpeg.height;
            for (int index = 0; index < moviePlayer->vo_buf.size; index++) {
                setImageTag(moviePlayer->vo_buf.tag[index].v,
                            &moviePlayer->vo_buf.data[index], width, height);
            }
        }
        voBufIncCount(&moviePlayer->vo_buf);
        switchThread();
    }

    sceMpegReset(&decoder->mpeg);
    return result;
}

void printf_stub(const char *format, ...);

int mpegError(sceMpeg *mpeg, sceMpegCbDataError *data, void *argument)
{
    printf_stub("%s\n", data->message);
    return 1;
}

int mpegNodata(sceMpeg *mpeg, sceMpegCbData *data, void *argument)
{
    switchThread();
    viBufAddDMA(&moviePlayer->video_dec.vibuf);
    return 1;
}

int mpegStopVideoDMA(void)
{
    viBufStopDMA(&moviePlayer->video_dec.vibuf);
    return 1;
}

int mpegRestartVideoDMA(void)
{
    viBufRestartDMA(&moviePlayer->video_dec.vibuf);
    return 1;
}

int mpegTimeStamp(sceMpeg *mpeg, sceMpegCbDataTimeStamp *data, void *argument)
{
    TimeStamp timestamp;
    viBufGetTs(&moviePlayer->video_dec.vibuf, &timestamp);
    data->pts = timestamp.pts;
    data->dts = timestamp.dts;
    return 1;
}
