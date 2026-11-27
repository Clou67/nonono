#include "common.h"
#include "movie.h"

// The vblank handler reads and updates these display flags.
extern volatile int movieDisplayActive;
extern volatile int movieVblankCount;

INCLUDE_ASM("code/_generated/novalis/nonmatchings/movie/disp", setImageTag);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/movie/disp", vblankHandler);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/movie/disp", handler_endimage);

void startDisplay(int waitEven)
{
    while (sceGsSyncV(0) == waitEven) {
    }

    movieDisplayActive = 1;
    movieVblankCount = 0;
}

void endDisplay(void)
{
    movieDisplayActive = 0;
}
