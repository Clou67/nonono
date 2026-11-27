#include "sce.h"
#include "vobuf.h"

enum {
    VO_TAG_EMPTY = 0,
    VO_TAG_FILLED = 2
};

void voBufCreate(VoBuf *f, VoData *data, VoTag *tag, int size)
{
    f->count = 0;
    f->data = data;
    f->tag = tag;
    f->size = size;
    f->write = 0;

    for (int slot = 0; slot < size; slot++)
        f->tag[slot].status = VO_TAG_EMPTY;
}

void voBufDelete(VoBuf *f)
{
}

void voBufReset(VoBuf *f)
{
    f->count = 0;
    f->write = 0;
}

int voBufIsFull(VoBuf *f)
{
    return f->count == f->size;
}

void voBufIncCount(VoBuf *f)
{
    DIntr();
    f->tag[f->write].status = VO_TAG_FILLED;
    f->count++;
    f->write = (f->write + 1) % f->size;
    EIntr();
}

VoData *voBufGetData(VoBuf *f)
{
    if (voBufIsFull(f))
        return 0;

    return &f->data[f->write];
}

int voBufIsEmpty(VoBuf *f)
{
    return f->count == 0;
}

VoTag *voBufGetTag(VoBuf *f)
{
    if (voBufIsEmpty(f))
        return 0;

    int slot = (f->write - f->count + f->size) % f->size;
    return &f->tag[slot];
}

void voBufDecCount(VoBuf *f)
{
    if (f->count > 0)
        f->count--;
}
