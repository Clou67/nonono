#ifndef PAD_H
#define PAD_H

#define PAD_L2 0x0001
#define PAD_R2 0x0002
#define PAD_L1 0x0004
#define PAD_R1 0x0008
#define PAD_TRIANGLE 0x0010
#define PAD_CIRCLE 0x0020
#define PAD_CROSS 0x0040
#define PAD_SELECT 0x0100
#define PAD_START 0x0800
#define PAD_UP 0x1000
#define PAD_RIGHT 0x2000
#define PAD_DOWN 0x4000
#define PAD_LEFT 0x8000
#define PAD_DPAD (PAD_UP | PAD_RIGHT | PAD_DOWN | PAD_LEFT)

// Set in bitsOn when the stick was flicked to full deflection.
#define PAD_STICK_FLICK 0x10000

// Reverses the left and right of the sticks and the d-pad.
#define CHEAT_MIRROR_MODE 4
// Big head mode (the manipulator scale is applied while set).
#define CHEAT_BIG_HEAD 7
#define CHEAT_COUNT 12

// Frames of button and stick history kept in the rings.
#define PAD_RING_LENGTH 30

#define PAD_ANALOG_COUNT 16
#define PAD_PROFILE_SIZE 4

// What the HUD does with the input it has taken over for itself.
#define PAD_HUD_DIVERT_NONE 0
#define PAD_HUD_DIVERT_ACTIONS 1
#define PAD_HUD_DIVERT_MENU_ONLY 2

// Progress of the controller's setup.
#define PAD_PHASE_PROFILE 0
#define PAD_PHASE_READY 1
#define PAD_PHASE_UNSUPPORTED 2

// DL struct PAD; the later build has more members after repeatCounter.
struct PAD {
    unsigned char unk_000[0x100];
    float analog[PAD_ANALOG_COUNT];
    float hudAnalog[PAD_ANALOG_COUNT];
    unsigned char profile[PAD_PROFILE_SIZE];
    unsigned char vib_profile[PAD_PROFILE_SIZE];
    unsigned char act_direct[PAD_PROFILE_SIZE];
    short invalidTimer;
    short ringIndex;
    int ringValidSize;
    int socket;
    int phase;
    int state;
    int bits;
    int bitsOn;
    int bitsOff;
    int bitsPrev;
    int digitalBits;
    int digitalBitsOn;
    int digitalBitsOff;
    int digitalBitsPrev;
    int hudBits;
    int hudBitsOn;
    int hudBitsOff;
    int hudDivert;
    int handsOff;
    int handsOffStick;
    int useAnalog;
    int term_id;
    int bitsOnRing[PAD_RING_LENGTH];
    float analogAngRing[PAD_RING_LENGTH];
    float analogMagRing[PAD_RING_LENGTH];
    int unmaskedBits;
    unsigned char port;
    unsigned char repeatDelay;
    unsigned char repeatSpeed;
    unsigned char repeatCounter;
};

typedef char PadSizeCheck[sizeof(PAD) == 0x350 ? 1 : -1];
typedef char PadRepeatCheck[((int)&((PAD *)0)->repeatCounter) == 0x34F ? 1 : -1];
typedef char PadAngCheck[((int)&((PAD *)0)->analogMagRing) == 0x2D0 ? 1 : -1];

// Options for the socket the pad library opens on the PAD buffer.
struct Pad2SocketParam {
    int mode;
    int enabled;
    int unk_08[6];
};

extern PAD padState;
extern Pad2SocketParam PadSocketParam;
// One flag per cheat; these are set by Hero_CheckCheatSequences.
extern unsigned char CheatsActivated[CHEAT_COUNT] __attribute__((section(".sdata")));

void InitPadRing(void);
int PadRingBitsOn(int bits, int frames, int *frame);
int PadRingCoincidentBitsOn(int firstBits, int secondBits, int frames, int window);
float PadRingAng(int frames);
void pad_Init(void);
void UpdatePadEx(PAD *pad);
void ClearPadInput(PAD *pad);
void ProcessPadInput(PAD *pad, unsigned char *data, int length);
void UpdatePad(void);

#endif
