#ifndef DEBUG_H
#define DEBUG_H

void STUB_002187f8(void);

void STUB_00218800(void);

void STUB_00218808(void);

void STUB_00218810(void);

void STUB_00218818(void);

void STUB_00218820(void);

void STUB_00218828(void);

void STUB_00218830(void);


// Debug switches set up for each level (DL's debug globals).
struct DebugSettings {
    char unk_00[0x8];
    int update;
    int selectedCol;
    char unk_10[0x8];
    int profile;
    // How occlusion data is used: 0 none, 2 from the gameplay file.
    int occlusionMode;
    char unk_20[0x10];
    int tvMode;
    char unk_34[0x4];
    int scene;
    char unk_3C[0xB8];
    int actuator;
};

extern DebugSettings Debug;

#endif
