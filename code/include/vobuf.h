#ifndef VOBUF_H
#define VOBUF_H

struct VoData {
    unsigned char v[0xD0000];
};

struct VoTag {
    int status;
    int buffer;
    int dummy[14];
    unsigned int v[10000][2];  // Novalis GS image packet storage.
};

struct VoBuf {
    VoData *data;
    VoTag *tag;
    volatile int write;
    volatile int count;
    int size;
};

void voBufCreate(VoBuf *f, VoData *data, VoTag *tag, int size);
void voBufDelete(VoBuf *f);
void voBufReset(VoBuf *f);
int voBufIsFull(VoBuf *f);
void voBufIncCount(VoBuf *f);
VoData *voBufGetData(VoBuf *f);
int voBufIsEmpty(VoBuf *f);
VoTag *voBufGetTag(VoBuf *f);
void voBufDecCount(VoBuf *f);

#endif
