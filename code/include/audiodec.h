#ifndef AUDIODEC_H
#define AUDIODEC_H

struct SpuStreamHeader {
    char id[4];
    int size;
    int type;
    int rate;
    int ch;
    int interSize;
    int loopStart;
    int loopEnd;
};

struct SpuStreamBody {
    char id[4];
    int size;
};

enum AudioDecState {
    AUDIO_DEC_HEADER_PENDING,
    AUDIO_DEC_PRESET,
    AUDIO_DEC_PLAYING,
    AUDIO_DEC_PAUSED
};

enum sceMpegStrType {
    sceMpegStrM2V,
    sceMpegStrIPU,
    sceMpegStrPCM,
    sceMpegStrADPCM,
    sceMpegStrDATA
};

struct _AudioDec {
    int state;
    sceMpegStrType type;
    SpuStreamHeader sshd;
    SpuStreamBody ssbd;
    int hdrCount;
    unsigned char *data;
    int put;
    int count;
    int size;
    int totalBytes;
    int iopBuff;
    int iopBuffSize;
    // The IOP/SPU fields follow the Novalis layout.
    int iopLastPos;
    int iopPausePos;
    int totalBytesSent;
    int iopZero;
    int spuPos;
};

int audioDecCreate(_AudioDec *decoder, unsigned char *buffer, int buffer_size, unsigned char *staging_buffer);
int audioDecDelete(_AudioDec *ad);
void audioDecStart(_AudioDec *ad);
void audioDecReset(_AudioDec *ad);
void audioDecBeginPut(_AudioDec *decoder, unsigned char **first, int *first_size,
                      unsigned char **second, int *second_size);
void audioDecEndPut(_AudioDec *ad, int size);
int audioDecIsPageFull(_AudioDec *decoder);
void audioDecSend(_AudioDec *ad);

#endif
