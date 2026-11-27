#ifndef VOLUME_H
#define VOLUME_H

#include "moby.h"

// Shared PS2 volume records from the DL debug types (0x80 bytes each).

struct Cuboid {
    Mtx3 matrix; // 0x00
    Vec4 pos; // 0x30
    Mtx3 imatrix; // 0x40
    Vec4 rot; // 0x70
};

struct Cylinder {
    Mtx3 matrix; // 0x00
    Vec4 pos; // 0x30
    Mtx3 imatrix; // 0x40
    Vec4 rot; // 0x70
};

struct Sphere {
    Mtx3 matrix; // 0x00
    Vec4 pos; // 0x30
    Mtx3 imatrix; // 0x40
    Vec4 rot; // 0x70
};

#endif
