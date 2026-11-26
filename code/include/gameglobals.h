#ifndef GAMEGLOBALS_H
#define GAMEGLOBALS_H

// Values of gameMode.
enum gameMode_t {
    GAME_MODE_NONE = -2,
    GAME_MODE_DEBUG = -1,
    GAME_MODE_NORMAL = 0,
    GAME_MODE_MOVIE = 1,
    GAME_MODE_SCENE = 2,
    GAME_MODE_PAUSE = 3,
    GAME_MODE_FREEZE = 4,
    GAME_MODE_VENDOR = 5,
    GAME_MODE_SPACE = 6,
    GAME_MODE_CREDITS = 7
};

extern int gameMode;
extern int CutscenePlaying;
// Game time in frames.
extern int worldUpdateTime;
extern int gameLanguage;
// Play time in game frames.
extern int TotalPlayTime;

extern float transStepScale;

#endif
