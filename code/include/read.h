#ifndef READ_H
#define READ_H

#include "videodec.h"

int videoCallback(sceMpeg *mpeg, sceMpegCbData *event, void *argument);
int pcmCallback(sceMpeg *mp, sceMpegCbDataStr *event, void *argument);

int cpy2area(unsigned char *first, int firstSize, unsigned char *second, int secondSize,
             unsigned char *source, int sourceSize, unsigned char *wrapped, int wrappedSize);

#endif
