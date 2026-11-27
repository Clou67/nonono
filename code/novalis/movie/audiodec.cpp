#include "audiodec.h"
#include "common.h"
#include "framebuf.h"
#include "sce.h"

extern unsigned char *movieAdpcmStagingBuffer;

int snd_InitMovieSound(int block_size, int page_size, int transfer_size, int spu_address, int left_voice, int right_voice);

void snd_CloseMovieSound(void);

void snd_StartMovieSound(int iop_buffer, int buffer_size, int iop_offset, int rate, int channels);

void snd_ResetMovieSound(void);

void sendADPCM(_AudioDec *decoder);

void snd_UpdateMovieADPCM(int size, int offset);

int snd_GetMovieNAX(void);

enum {
    ADPCM_BLOCK_SIZE = 0x400,
    ADPCM_PAGE_SIZE = 0x1000,
    ADPCM_FRAME_SIZE = 0x10,
    ADPCM_FLAGS_OFFSET = 1,
    ADPCM_LOOP_END = 1,
    ADPCM_LOOP_REPEAT = 2,
    ADPCM_LOOP_START = 4,
    STREAM_HEADER_SIZE = sizeof(SpuStreamHeader) + sizeof(SpuStreamBody)
};

int audioDecCreate(_AudioDec *decoder, unsigned char *buffer, int buffer_size, unsigned char *staging_buffer)
{
    FastMemSetZero(&decoder->sshd, sizeof(decoder->sshd));
    decoder->data = buffer;
    decoder->size = buffer_size;
    decoder->type = sceMpegStrADPCM;
    decoder->state = AUDIO_DEC_HEADER_PENDING;
    decoder->hdrCount = 0;
    decoder->put = 0;
    decoder->count = 0;
    decoder->totalBytes = 0;
    decoder->iopLastPos = 0;
    decoder->totalBytesSent = 0;
    decoder->iopZero = 0;
    decoder->spuPos = 0;
    movieAdpcmStagingBuffer = staging_buffer;
    decoder->iopBuffSize = ADPCM_BLOCK_SIZE;
    int movie_handle = snd_InitMovieSound(ADPCM_BLOCK_SIZE, ADPCM_PAGE_SIZE, ADPCM_BLOCK_SIZE, 0, 5, 3);
    decoder->iopBuff = movie_handle;

    if (movie_handle < 0)
        return 0;

    return 1;
}

int audioDecDelete(_AudioDec *ad)
{
    snd_CloseMovieSound();
    return 1;
}

TEXT_PADDING(0x27BD0010, 0);

void audioDecStart(_AudioDec *ad)
{
    snd_StartMovieSound(ad->iopBuff,
                        (ad->iopBuffSize / ADPCM_BLOCK_SIZE) * ADPCM_BLOCK_SIZE,
                        ad->iopZero, ad->sshd.rate, ad->sshd.ch);
    ad->state = AUDIO_DEC_PLAYING;
}

void audioDecReset(_AudioDec *ad)
{
    snd_ResetMovieSound();
    ad->state = AUDIO_DEC_HEADER_PENDING;
    ad->hdrCount = 0;
    ad->put = 0;
    ad->count = 0;
    ad->totalBytes = 0;
    ad->iopLastPos = 0;
    ad->totalBytesSent = 0;
    ad->iopZero = 0;
}

void audioDecBeginPut(_AudioDec *decoder, unsigned char **first, int *first_size, unsigned char **second, int *second_size)
{
    if (decoder->state == AUDIO_DEC_HEADER_PENDING) {
        if (decoder->type != sceMpegStrDATA) {
            *first = (unsigned char *)&decoder->sshd + decoder->hdrCount;
            *first_size = STREAM_HEADER_SIZE - decoder->hdrCount;
            *second = decoder->data;
            *second_size = decoder->size;
        }

        else {
            *first = decoder->data;
            *first_size = decoder->size;
            *second = 0;
            *second_size = 0;
        }
    }

    else {
        int free_space = decoder->size - decoder->count;
        if (decoder->size - decoder->put >= free_space) {
            *first = decoder->data + decoder->put;
            *first_size = free_space;
            *second = 0;
            *second_size = 0;
        }

        else {
            *first = decoder->data + decoder->put;
            *first_size = decoder->size - decoder->put;
            *second = decoder->data;
            *second_size = free_space - (decoder->size - decoder->put);
        }
    }
}

void audioDecEndPut(_AudioDec *ad, int size)
{
    if (ad->state == AUDIO_DEC_HEADER_PENDING) {
        if (ad->type != sceMpegStrDATA) {
            int header_space = STREAM_HEADER_SIZE - ad->hdrCount;
            int header_bytes = header_space < size ? header_space : size;
            ad->hdrCount += header_bytes;
            if (ad->hdrCount >= STREAM_HEADER_SIZE)
                ad->state = AUDIO_DEC_PRESET;

            size -= header_bytes;
        }

        else {
            ad->state = AUDIO_DEC_PRESET;
        }
    }

    ad->size = ad->size / ADPCM_BLOCK_SIZE * ADPCM_BLOCK_SIZE;
    ad->put = (ad->put + size) % ad->size;
    ad->count += size;
    ad->totalBytes += size;
}

int audioDecIsPageFull(_AudioDec *decoder)
{
    return decoder->iopLastPos >= ADPCM_PAGE_SIZE;
}

void audioDecSend(_AudioDec *ad)
{
    if (ad->state != AUDIO_DEC_HEADER_PENDING)
        sendADPCM(ad);
}

void sendToSPU(_AudioDec *decoder, unsigned char *source, int size, int offset)
{
    SifDmaTransfer transfer;
    int dma_id;

    FlushCache(0);
    transfer.source = source;
    transfer.destination = (void *)decoder->iopBuff;
    transfer.size = size;
    transfer.attributes = 0;

    do {
        dma_id = sceSifSetDma(&transfer, 1);
    } while (dma_id == 0);

    while (sceSifDmaStat(dma_id) >= 0) {
    }

    snd_UpdateMovieADPCM(size, offset);
}

void sendADPCM(_AudioDec *ad)
{
    int available = 0;

    switch (ad->state) {
    case AUDIO_DEC_PRESET:
        if (ad->count < ADPCM_PAGE_SIZE)
            return;

        available = ADPCM_PAGE_SIZE - ad->iopLastPos;
        break;

    case AUDIO_DEC_PLAYING:
        available = (snd_GetMovieNAX() - ad->spuPos) & (ADPCM_PAGE_SIZE - 1);
        break;

    case AUDIO_DEC_PAUSED:
        return;
    }

    while (available >= ADPCM_BLOCK_SIZE && ad->count >= ad->sshd.ch * ADPCM_BLOCK_SIZE) {
        for (int channel = 0; channel < ad->sshd.ch; channel++) {
            unsigned char *read_cursor = ad->data + (ad->put - ad->count + ad->size) % ad->size;
            read_cursor += channel * ad->sshd.interSize;
            unsigned char *write_cursor = movieAdpcmStagingBuffer;
            int copied = 0;

            while (copied < ADPCM_BLOCK_SIZE) {
                for (int byte_index = 0; byte_index < ad->sshd.interSize; byte_index++) {
                    *write_cursor++ = *read_cursor++;
                    copied++;
                }
                read_cursor += ad->sshd.interSize * (ad->sshd.ch - 1);
            }

            if (ad->spuPos + ADPCM_BLOCK_SIZE == ADPCM_PAGE_SIZE)
                movieAdpcmStagingBuffer[ADPCM_BLOCK_SIZE - ADPCM_FRAME_SIZE + ADPCM_FLAGS_OFFSET] =
                    ADPCM_LOOP_END | ADPCM_LOOP_REPEAT;

            if (ad->spuPos == 0) {
                unsigned char *staging_buffer = movieAdpcmStagingBuffer;
                staging_buffer[ADPCM_FLAGS_OFFSET] = ADPCM_LOOP_START | ADPCM_LOOP_REPEAT;
                staging_buffer[ADPCM_FRAME_SIZE + ADPCM_FLAGS_OFFSET] = ADPCM_LOOP_REPEAT;
            }
            sendToSPU(ad, movieAdpcmStagingBuffer, ADPCM_BLOCK_SIZE,
                      channel * ADPCM_PAGE_SIZE + ad->spuPos);
        }

        ad->spuPos = (ad->spuPos + ADPCM_BLOCK_SIZE) % ADPCM_PAGE_SIZE;
        ad->count -= ad->sshd.ch * ADPCM_BLOCK_SIZE;
        ad->iopLastPos += ADPCM_BLOCK_SIZE;
        available -= ADPCM_BLOCK_SIZE;
    }
}
