#ifndef GSREGS_H
#define GSREGS_H

// TEX0 texture descriptor, exposed as a register word or individual GS fields.
union GsTex0 {
    unsigned long bits;
    struct {
        unsigned long tbp0 : 14;
        unsigned long tbw : 6;
        unsigned long psm : 6;
        unsigned long tw : 4;
        unsigned long th : 4;
        unsigned long tcc : 1;
        unsigned long tfx : 2;
        unsigned long cbp : 14;
        unsigned long cpsm : 4;
        unsigned long csm : 1;
        unsigned long csa : 5;
        unsigned long cld : 3;
    } fields;
};

// GS register addresses written through packets (A+D).
#define GS_REG_RGBAQ 0x01
#define GS_REG_CLAMP_1 0x08
#define GS_REG_ALPHA_1 0x42
#define GS_REG_TEST_1 0x47
#define GS_REG_ZBUF_1 0x4E

// TEST_1 fields.
#define GS_TEST_ATE 1
#define GS_TEST_ATST_GEQUAL (5 << 1)
#define GS_TEST_AREF(ref) ((ref) << 4)
#define GS_TEST_AFAIL_FB_ONLY (1 << 12)
#define GS_TEST_AFAIL_RGB_ONLY (3 << 12)
#define GS_TEST_ZTE (1 << 16)
#define GS_TEST_ZTST_ALWAYS (1 << 17)
#define GS_TEST_ZTST_GEQUAL (2 << 17)

// ZBUF_1 fields: the Z buffer base pointer is in units of 8192 bytes.
#define GS_ZBUF_ZBP(address) ((address) >> 13)
#define GS_ZBUF_PSMZ24 (1 << 24)

// CLAMP_1 wrap modes: repeat both axes, or clamp both.
#define GS_CLAMP_REPEAT 0
#define GS_CLAMP_CLAMP 5

#endif
