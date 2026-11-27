#ifndef FASTFUNC_H
#define FASTFUNC_H

struct Vec4;
struct Mtx4;
struct BSphere;

// Stops in the debugger; used when a save is bigger than its buffer.
void FastTrap(void);
int FastScaleRoundInt(int value);
int FastAbsI(int value);
int FastTweenColor(int from, int to, float fraction);
int FastFloatToInt(float value);
// Splits value into whole and fractional parts; returns the fraction.
float FastFrac(float *whole, float value);
float FastIntToFloat(int value);
float FastAngleCosF(float angle);
float FastAngleSinF(float angle);
float FastAddRots(float angle, float delta);
float FastSubRots(float first, float second);
float FastArcTan(float x, float y);
float FastDiffRots(float first, float second);
float FastVec3DistLen(Vec4 *from, Vec4 *to);
float FastVec3Dist(Vec4 *first, Vec4 *second);
// Nonzero when the sphere (w is its radius) overlaps the bounding sphere.
int FastVec3AddSubLen(Vec4 *sphere, BSphere *bounds);
void FastScaleVec4(Vec4 *out, Vec4 *in, float scale);
// Counts a timer down to zero; returns nonzero once it has run out.
int FastDecTimer(int &timer);
int FastDecTimer(short &timer);
int FastDecTimer(unsigned char &timer);
float FastAbsF(float value);
float FastFSqrt(float value);
void FastVec3Add(Vec4 *out, Vec4 *first, Vec4 *second);
void FastVecLerp(Vec4 *out, Vec4 *first, Vec4 *second, float amount);
float FastVec3Length(float *vec);
float FastVec3Dot(Vec4 *first, Vec4 *second);
void FastMemCopy32(void *destination, void *source, int size);
// Writes the scaled xyz of in to out.
void FastVec3Scale(Vec4 *out, Vec4 *in, float scale);
void FastMtx4Identity(float *matrix);
void FastMtxTransform(Mtx4 *left, Mtx4 *right, Mtx4 *result);
void FastMemSet(void *destination, int value, int size);
float FastVec3Length2(Vec4 *vector);
float FastMaxF(float first, float second);
// Rotates vector by the 3x3 part of matrix.
void FastVecMtx3Mult(Vec4 *out, Vec4 *vector, Mtx4 *matrix);
// DMAs quadwords from the scratchpad at spr_address into main memory.
void FastFromSpr(void *destination, int spr_address, int quadwords);

void FastSubVec3(Vec4 *out, Vec4 *first, Vec4 *second);
void FastVecZero(Vec4 *vector);
void FastVecDivScalar(Vec4 *out, Vec4 *vector, float divisor);
// Scales a joint position from the scratchpad into a working vector.
void ScaleJointPosition(Vec4 *out, Vec4 *joint, float scale);
void FastVec3Normalize(Vec4 *out, Vec4 *vector, float length);
void FastVec3NormalizeFrom(Vec4 *out, Vec4 *vector, Vec4 *normal);

void FastTransformVec4(Vec4 *out, Vec4 *vector, Mtx4 *matrix);

#endif
