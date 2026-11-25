#ifndef MOVIE_H
#define MOVIE_H

#include "audiodec.h"
#include "readbuf.h"
#include "sce.h"
#include "strfile.h"
#include "videodec.h"
#include "vobuf.h"

enum {
    MOVIE_INPUT_SECTOR_SIZE = 0x800,
    MOVIE_INPUT_SECTORS = 0x100,
    MOVIE_TIMESTAMP_COUNT = 0x200,
    MOVIE_AUDIO_BUFFER_SIZE = 0x2000,
    MOVIE_DECODER_STACK_SIZE = 0x4000
};

struct MoviePlayer {
    ReadBuf read_buf;
    unsigned char unk_5000c[0x34];
    unsigned char audio_buf[MOVIE_AUDIO_BUFFER_SIZE];
    unsigned char vi_buf_data[MOVIE_INPUT_SECTORS][MOVIE_INPUT_SECTOR_SIZE];
    unsigned char decoder_stack[MOVIE_DECODER_STACK_SIZE];
    TimeStamp vi_buf_ts[MOVIE_TIMESTAMP_COUNT];
    StrFile str_file;
    VideoDec video_dec;
    _AudioDec audio_dec;
    unsigned char unk_d9164[4];
    VoBuf vo_buf;
};

// Layout of the decoder buffer passed to playMpegMovie.
struct MovieDecoderMemory {
    VoData output_frames[2];
    VoTag output_tags[2];
    u_long128 input_tags[MOVIE_INPUT_SECTORS + 1];
    unsigned char adpcm_staging[0x400];
    unsigned char unk_1c8590[0x30];
    unsigned char mpeg_work[0xEB768];
};

extern MoviePlayer *moviePlayer;
extern unsigned char *movieDecoderBuffer;
extern int movieDecoderThread;

// How the movie can be skipped: MOVIE_SKIP_DISABLED, 0 for Start only, or MOVIE_SKIP_ANY_BUTTON.
// Sampled again when checking whether Start is allowed.
extern volatile int decodeMode;
extern int GoodiesMenuUnlocked;

int playMpegMovie(int sector, int size, unsigned char *decoder_buffer, MoviePlayer *player, int language);
int readMpeg(VideoDec *decoder, ReadBuf *buffer, StrFile *file);
void switchThread(void);
int isAudioOK(void);
int initAll(int sector, int size, int language);
void termAll(void);
void ErrMessage(char *message);
void proceedAudio(void);

#endif
