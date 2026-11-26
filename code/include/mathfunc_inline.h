#ifndef MATHFUNC_INLINE_H
#define MATHFUNC_INLINE_H

#include "moby.h"

// Copies a quadword vector through $2, as the original's inline vector helpers do.
static inline void CopyVec4Inline(Vec4 *destination, Vec4 *source)
{
    __asm__ volatile("lq $2, 0(%1)\n\tsq $2, 0(%0)" : : "r"(destination), "r"(source) : "$2", "memory");
}

// 128-bit integer type; assigning one compiles to lq/sq, as the original's whole-vector copies do.
typedef int Vec4Quad __attribute__((mode(TI)));

// Copies a quadword vector through any free register.
static inline void CopyVec4(Vec4 *destination, Vec4 *source)
{
    *(Vec4Quad *)destination = *(Vec4Quad *)source;
}

// Clears a vector with a quadword store, as retail's whole-vector assignments of zero do.
static inline void ClearVec4(Vec4 *vector)
{
    *(Vec4Quad *)vector = 0;
}

// Retail clears an aligned vector directly from the zero register.
static inline void ClearVec4Inline(Vec4 *vector)
{
    __asm__ volatile("sq $0, %0" : "=m"(*vector) : : "memory");
}

// Clears an aligned vector through an address register. The asm has no outputs or clobbers, so GCC
// forgets every value it was tracking (retail reloads addresses after it, as in UpdateViewContext).
static inline void ZeroVec4Inline(Vec4 *vector)
{
    __asm__ volatile("sq $0, 0(%0)" : : "r"(vector));
}

#endif
