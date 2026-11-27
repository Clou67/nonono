#ifndef READBUF_H
#define READBUF_H

enum { READ_BUF_CAPACITY = 0x50000 };

struct ReadBuf {
    unsigned char data[READ_BUF_CAPACITY];
    int put;
    int count;
    int size;
};

void readBufCreate(ReadBuf *b);
void readBufDelete(ReadBuf *b);
int readBufBeginPut(ReadBuf *buffer, unsigned char **destination);
void readBufEndPut(ReadBuf *b, int size);
int readBufBeginGet(ReadBuf *buffer, unsigned char **source);
int readBufEndGet(ReadBuf *b, int size);

#endif
