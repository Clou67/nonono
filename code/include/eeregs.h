#ifndef EEREGS_H
#define EEREGS_H

// EE hardware registers (names from Sony eeregs.h).
#define T0_COUNT ((volatile unsigned int *)0x10000000)
#define D0_CHCR ((volatile unsigned int *)0x10008000)
#define D0_QWC ((volatile unsigned int *)0x10008020)
#define D0_TADR ((volatile unsigned int *)0x10008030)
#define D1_CHCR ((volatile unsigned int *)0x10009000)
#define D1_TADR ((volatile unsigned int *)0x10009030)
#define D_STAT ((volatile unsigned int *)0x1000E010)

// D_STAT access in the style of Sony's DGET_/DPUT_ macros. Reads are volatile;
// the write is a plain store (both DMAC functions in vuchain only match that way).
#define DGET_D_STAT() (*D_STAT)
#define DPUT_D_STAT(value) (*(unsigned int *)D_STAT = (value))

// D_CHCR: channel busy (start) bit.
#define D_CHCR_STR 0x100

#endif
