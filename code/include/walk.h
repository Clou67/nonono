#ifndef WALK_H
#define WALK_H

#include "moby.h"

// One leg of a two-legged walker (DL's w_legData, 0xB0 bytes). The hip and ankle manipulators
// twist the leg so the foot keeps pointing the way it was planted.
struct w_legData {
    char jiFoot;           // 0x00 joint indices
    char jiHeel;           // 0x01
    char jiAnkle;          // 0x02
    char jiHip;            // 0x03
    short idle;            // 0x04
    short _2mainIdle;      // 0x06
    float frDest;          // 0x08 yaw the foot was planted with
    float arAct;           // 0x0C ankle twist
    float arSpeed;         // 0x10
    float hrAct;           // 0x14 hip twist
    float hrSpeed;         // 0x18
    float twistLow;        // 0x1C limits of both twists
    float twistHigh;       // 0x20
    int pad24[3];          // 0x24
    Manipulator MAnkle;    // 0x30
    Manipulator MHip;      // 0x70
};

// One animation of a two-legged walker (w_2legData::anims[], DL's w_2legAnim). walk_init2LegAnim
// fills in speed, frame0, frames and the ranges. Index [0] and [1] are leg 0 and leg 1.
struct w_2legAnim {
    int anim;              // 0x00 sequence, negative when unused
    float stride;          // 0x04 distance covered by one cycle
    float speed;           // 0x08 stride per frame of the cycle
    float frame0;          // 0x0C first frame
    float frames;          // 0x10 length of the cycle
    int fromIdle;          // 0x14 frame to start from when leaving idle
    float move1Reset;      // 0x18
    float move2Reset;      // 0x1C
    float heelRange[2];    // 0x20 frames the heel is down for
    float heelDown[2];     // 0x28
    float heelUp[2];       // 0x30
    float footRange[2];    // 0x38 frames the foot is down for
    float footDown[2];     // 0x40 frame the foot comes down on
    float footUp[2];       // 0x48 frame the foot lifts on
};

// w_2legData::onground, the tracked joints (fpos[]) that are planted.
enum WalkContact {
    WALK_CONTACT_FOOT0 = 0x01,
    WALK_CONTACT_HEEL0 = 0x02,
    WALK_CONTACT_FOOT1 = 0x04,
    WALK_CONTACT_HEEL1 = 0x08,
    WALK_CONTACT_MOVE1 = 0x10,
    WALK_CONTACT_MOVE2 = 0x20
};

// w_2legData::flags.
enum WalkFlag {
    WALK_FLAG_JUMP = 0x1,      // the moby wants a jump to jumpPos at the next step
    WALK_FLAG_JUMPING = 0x2,   // taking off
    WALK_FLAG_AIRBORNE = 0x4,  // flying to jumpPos
    WALK_FLAG_STEP_DOWN = 0x8  // stepping down, so the body does not snap up to the ground
};

// w_2legData::state. The comment is the anims[] index each state plays (WalkStateAnim).
enum WalkState {
    WALK_STATE_IDLE = 0,
    WALK_STATE_WALK = 1,
    WALK_STATE_UP_A = 2,
    WALK_STATE_UP_B = 3,
    WALK_STATE_UP_HIGH = 4,
    WALK_STATE_UP_A_TOP = 5,
    WALK_STATE_UP_B_TOP = 6,
    WALK_STATE_DOWN_A = 7,
    WALK_STATE_DOWN_B = 8,
    WALK_STATE_DOWN_LOW = 9,
    WALK_STATE_DOWN_A_END = 10,
    WALK_STATE_DOWN_B_END = 11,
    WALK_STATE_STOP = 12,  // goes straight back to idle
    WALK_STATE_RUN = 13,
    WALK_STATE_JUMP_A = 14,
    WALK_STATE_JUMP_B = 15,
    WALK_STATE_AIR = 16,
    WALK_STATE_LAND_A = 17,
    WALK_STATE_LAND_B = 18,
    WALK_STATE_LANDED_A = 19,
    WALK_STATE_LANDED_B = 20
};

// Indices into w_2legData::anims[].
enum WalkAnimSlot {
    WALK_ANIM_WALK = 0,
    WALK_ANIM_UP_A = 1,
    WALK_ANIM_UP_B = 2,
    WALK_ANIM_UP_HIGH = 3,
    WALK_ANIM_DOWN_A = 4,
    WALK_ANIM_DOWN_B = 5,
    WALK_ANIM_DOWN_LOW = 6,
    WALK_ANIM_RUN = 7,
    WALK_ANIM_STOP = 8,
    WALK_ANIM_JUMP_A = 9,
    WALK_ANIM_LAND_A = 10,
    WALK_ANIM_JUMP_B = 11,
    WALK_ANIM_LAND_B = 12,
    WALK_ANIM_COUNT = 13
};

// A two-legged walker (DL's w_2legData, 0x250 bytes). The moby keeps one in its pVars and fills
// in the joints, anims and tuning, then calls walk_init2LegAnim; walk_Update moves it each frame.
struct w_2legData {
    Vec4 fpos[6];          // 0x000 foot0, heel0, foot1, heel1, move1 and move2 in world space
    Vec4 jumpPos;          // 0x060 where a jump lands, w is the heading of the jump
    w_2legAnim *anims[WALK_ANIM_COUNT]; // 0x070
    int pad_A4[3];         // 0x0A4
    unsigned char idle;             // 0x0B0 sequences
    unsigned char stand;            // 0x0B1
    unsigned char jumpc;            // 0x0B2
    unsigned char rjumpc;           // 0x0B3 the sequence played in the air
    unsigned char moveJoint1;       // 0x0B4 joints
    unsigned char moveJoint2;       // 0x0B5
    unsigned char onground; // 0x0B6 WalkContact bits
    unsigned char state;   // 0x0B7 WalkState
    float yrot;            // 0x0B8 pitch of the ground, which rotation.y follows
    float yrSpeed;         // 0x0BC
    float speed;           // 0x0C0
    float acc;             // 0x0C4 most the speed changes per frame
    float angVel;          // 0x0C8 turning of rotation.z
    float angGain;         // 0x0CC
    float angDamp;         // 0x0D0
    float angLimit;        // 0x0D4
    float zVel;            // 0x0D8
    float grav;            // 0x0DC
    float stepHeight;      // 0x0E0
    float stepZ;           // 0x0E4 ground height ahead of the leading foot
    float collZAdj;        // 0x0E8 raises the collision pill while stepping
    short counter;         // 0x0EC
    unsigned short flags;  // 0x0EE WalkFlag bits
    w_legData legs[2];     // 0x0F0
};

// The anims[] index each WalkState plays, -1 for none.
extern int WalkStateAnim[21];

unsigned int walk_GetLegRangeMask(w_2legAnim *anim, float frame);
void walk_ResetLegTwist(w_2legData *walker);
float walk_SolveStepTiming(MobyInstance *moby, w_2legData *walker);
void walk_UpdateStateMachine(float speed, float angle, float accel, MobyInstance *moby,
                             w_2legData *walker, unsigned int contacts);

// Older, simpler layouts of the same walker structs, kept for reference. They do not match retail
// (no anims[] table, no jumpPos, 16-bit onground/state, one twist per leg), so nothing uses them.
//
// struct legData {
//     char jiFoot;
//     char jiHeel;
//     char jiAnkle;
//     char jiHip;
//     float frAct;
//     float frDest;
//     float frSpeed;
//     Manipulator MAnkle;
//     Manipulator MHip;
//     void *_pBHip;
//     float twistLow;
//     float twistHigh;
//     short idle;
//     short _2mainIdle;
// };
//
// struct _2legAnim {
//     int anim;
//     float stride;
//     float frame0;
//     float frames;
//     int fromIdle;
//     int pad[3];
//     float heelRange[2];
//     float heelDown[2];
//     float heelUp[2];
//     float footRange[2];
//     float footDown[2];
//     float footUp[2];
// };
//
// struct _2legData {
//     Vec4 fpos[5];
//     short onground;
//     short state;
//     float yrot;
//     float yrSpeed;
//     short idle;
//     short stand;
//     _2legAnim walk;
//     _2legAnim run;
//     float speed;
//     int counter;
//     int moveJoint;
//     int pad[1];
//     legData legs[2];
// };

#endif
