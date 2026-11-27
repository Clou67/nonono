#include "readbuf.h"

void readBufCreate(ReadBuf *b)
{
    b->size = READ_BUF_CAPACITY;
    b->put = 0;
    b->count = 0;
}

void readBufDelete(ReadBuf *b)
{
}

int readBufBeginPut(ReadBuf *buffer, unsigned char **destination)
{
    int free_space = buffer->size - buffer->count;

    if (free_space != 0)
        *destination = buffer->data + buffer->put;

    return free_space;
}

void readBufEndPut(ReadBuf *b, int size)
{
    int free_space = b->size - b->count;
    int written = size < free_space ? size : free_space;

    b->put = (b->put + written) % b->size;
    b->count += written;
}

int readBufBeginGet(ReadBuf *buffer, unsigned char **source)
{
    if (buffer->count != 0) {
        int get_pos = (buffer->put - buffer->count + buffer->size) % buffer->size;
        *source = buffer->data + get_pos;
    }

    return buffer->count;
}

int readBufEndGet(ReadBuf *b, int size)
{
    int consumed = size < b->count ? size : b->count;
    b->count -= consumed;

    return consumed;
}
