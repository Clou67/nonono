#ifndef MOBY_H
#define MOBY_H

struct Vec3 {
    float x;
    float y;
    float z;
};

// Quadword vector; the VU loads it with lq/sq, so it is 16-byte aligned.
struct Vec4 {
    float x;
    float y;
    float z;
    float w;
} __attribute__((aligned(16)));

struct Mtx4 {
    Vec4 v0;
    Vec4 v1;
    Vec4 v2;
    Vec4 v3;
};

struct Mtx3 {
    Vec4 v0;
    Vec4 v1;
    Vec4 v2;
};

struct BSphere {
    float x;
    float y;
    float z;
    float rad;
};

enum { COLLPRIM_JOINT = 2, COLLPRIM_PILL = 3, COLLPRIM_CAPSULE = 4 };

struct JointPair { short a; short b; };

enum { COLLPRIM_RANDOM_POINTS = 0x20000, COLLPRIM_LAST = 0x80000000 };

union CollPrimShape {
    float length;
    int joint;
    JointPair ends;
};

struct CollPrim {
    union {
        unsigned int flags;
        struct {
            unsigned char collType;
            unsigned char _pad01;
            short sets;
        };
    };
    union {
        CollPrimShape shape;
        float length;
        int joint;
        struct {
            short jointA;
            short jointB;
        } ends;
    };
    unsigned char _pad08[4];
    float radius;
    Vec4 offset;
};


struct MobyCollPrims {
    short primSetA;
    short primSetB;
    int unk04;
    int count;
    int unk0C;
    CollPrim primitives[0]; // 0x10
};

struct MobySeqFrame {
    float length;
    short time;
    short qwords;
    short jointBytes;
    short scaleKeys;
    short transOffset;
    short transKeys;
    unsigned long long joints[0];
};

// The frame pointer table follows the 0x1C-byte RaC1 sequence header.
struct MobySeq {
    BSphere bSphere;              // 0x00
    unsigned char frameCount;    // 0x10
    signed char sound;           // 0x11
    unsigned char triggerCount;  // 0x12
    unsigned char unk_13;
    short *triggers;              // 0x14
    unsigned int unk_18;
    MobySeqFrame *frames[1];      // 0x1C, frameCount entries
};

// One GS texture setup of a moby packet (0x40 bytes); the loader fills it in from the
// class's texture definitions.
struct MobyGifDef {
    int mipDist;        // 0x00
    int filter;         // 0x04
    int unk_08[2];
    int clampU;         // 0x10
    int clampV;         // 0x14
    int unk_18[2];
    int texIndex;       // 0x20, -1 for none
    int unk_24[7];
};

// A packet group: high half of counts is the number of gif quadwords, low half the packet end.
struct MobyPacket {
    MobyGifDef *gifs;   // 0x00
    int counts;         // 0x04
    void *data;         // 0x08
    int unk_0C;
};

struct MobyDraw {
    unsigned int mip_tex;
    unsigned char pad_04[0x2C];
    unsigned int base_tex;
    unsigned char pad_34[0xC];
};

// Texture slots used by a run of draws; the last entry has the top bit of draws set.
struct MobyGifUsage {
    unsigned char stash[12];
    MobyDraw *draws;
};
struct SoundDef;

// The animation pointer table follows the 0x48-byte RaC1 class header.
struct MobyInstance;
typedef int (*MobyClassCallback)(MobyInstance *moby);
typedef void (*MobyUpdateFunc)(MobyInstance *moby);

struct MobyClassCallbacks {
    int unk_00;
    MobyClassCallback callback04;
    MobyClassCallback callback08;
    MobyClassCallback callback0C;
};

struct MobyAnimationJoints {
    int count;
    unsigned char *joints[1];
};

struct MobyClass {
    MobyPacket *packets;                // 0x00
    unsigned char packetCount0;        // 0x04
    unsigned char packetCount1;        // 0x05
    unsigned char metalCount;          // 0x06
    unsigned char unk_07;
    unsigned char jointCount;          // 0x08
    unsigned char unk_09;
    unsigned char unk_0A;
    unsigned char unk_0B;
    unsigned char sequenceCount;       // 0x0C
    unsigned char soundCount;          // 0x0D
    unsigned char lodTransition;       // 0x0E
    unsigned char shadowCount;         // 0x0F
    MobyCollPrims *collision;           // 0x10
    void *skeleton;                     // 0x14
    Vec4 *commonTranslations;           // 0x18
    MobyAnimationJoints *animationJoints;              // 0x1C
    MobyGifUsage *gifUsage;              // 0x20
    float scale;                        // 0x24
    SoundDef *soundDefs;                // 0x28
    // The loader saves mipDistance before the runtime slot can hold callbacks.
    union {                             // 0x2C
        unsigned int mipDistance;
        MobyClassCallbacks *callbacks;
    };
    BSphere bSphere;                    // 0x30
    unsigned int glowRgba;              // 0x40
    unsigned short modeBits;            // 0x44
    short type;                         // 0x46
    MobySeq *animations[1];              // 0x48, sequenceCount entries
};
struct Manipulator {
    unsigned char animJoint;
    unsigned char state;
    char scaleOn;
    char absolute;
    int jointId;
    Manipulator *pChain;
    float interp;
    Vec4 q; // Quaternion in x/y/z/w representation (DL: q).
    Vec4 scale;
    Vec4 trans;
};

// Bits of MobyInstance::modeBits.
enum MobyModeBit {
    NONE = 0,
    DISABLED = 1,
    NO_UPDATE = 2,
    NO_POST_UPDATE = 4,
    TRANSPARENT = 8,
    HAS_GLOW = 16,
    HAS_SPECIAL_VARS = 32,
    UNK_40 = 64,
    NO_DRAW = 128,
    LOCK_ROTATION = 256,
    DRAW_TRANSPARENT_WEIRD = 512,
    DRAW_SHADOW = 1024,
    DISABLE_Z_WRITE = 2048,
    CAN_BE_AUTO_TARGETED = 4096,
    HIDE_BACKFACES = 8192,
    CAN_BE_DAMAGED = 16384,
    MIRROR = 32768
};

// A moby (game object) instance, 0x100 bytes.
struct AnimLayer;

enum { MOBY_ANIMATION_ENDED = 2 };

struct MobyInstance {
    BSphere bSphere;
    Vec4 pos;
    unsigned char state;
    unsigned char group;
    unsigned char mClass;
    unsigned char alpha;
    MobyClass *pClass;
    MobyInstance *pChain;
    float scale;
    unsigned char updateDistance;
    unsigned char drawn; // 0x31: visibility from the draw pass, not an enable switch
    short drawDistance;
    unsigned short modeBits;
    unsigned short occlIndex;
    union {
        unsigned long long lights;
        struct {
            unsigned int color;
            unsigned int light;
        };
    };
    Vec4 rotation;
    unsigned char previousAnimationFrame;
    unsigned char animationFrame;
    unsigned char updateId;
    unsigned char animationId;
    float animationBlend;
    float animIScale;
    float animSpeed;
    AnimLayer *pAnimationLayers;
    Manipulator *pManipulators;
    void *pPreviousAnimationData;
    void *pCurrentAnimationData;
    unsigned char animationFlags;
    unsigned char unk71;
    unsigned char lodTransition;
    unsigned char metal;
    MobyUpdateFunc pUpdate;
    void *pVar;
    unsigned char soundDesired;
    unsigned char soundChannel;
    unsigned char trigsCnt;
    unsigned char shadow;
    int colorManipulator;
    float shadowPlane;
    float shadowRange;
    char unk8C[4];
    unsigned int glowRgba;
    union {
        unsigned short *collision;
        MobyCollPrims *pCollPrims;
    };
    unsigned int collisionDisable; // 0x98: one disable bit per collision primitive
    int collQueryStamp;
    union {
        unsigned int collCount;
        struct {
            unsigned char gridMinX;
            unsigned char gridMinY;
            unsigned char gridMaxX;
            unsigned char gridMaxY;
        };
    };
    unsigned char hitSlot; // 0xA4: collision hit-message slot, 0xFF for none
    unsigned char previousAnimationId;
    unsigned short oClass;
    int handle;
    unsigned int index;
    unsigned char levelFlagIdx;
    unsigned char unkB1;
    unsigned short uid;
    short bolts; // 0xB4: adjusted bolt drop
    short baseBolts; // 0xB6: unadjusted bolt drop
    MobyInstance *pParent; // 0xB8: spawner
    unsigned char command; // 0xBC: command supplied by group and scripted events
    unsigned char shadowIndex;
    char unkBE[2];
    Mtx4 transform;
};

enum { ANIM_CACHE_COUNT = 16 };
extern MobyInstance *AnimationCacheRegistry[ANIM_CACHE_COUNT];

void SetLevelFlag(int flag);

extern int StashedMobyClassDists[];

// Loaded moby classes by mClass, the next free mClass and each mClass's oClass.
enum { MOBY_CLASS_CAPACITY = 0xE0 };
extern MobyClass *MobyClasses[MOBY_CLASS_CAPACITY];
extern MobyUpdateFunc MobyClassUpdate[MOBY_CLASS_CAPACITY];
extern int MobyClassIndex;
extern short MobyOClasses[MOBY_CLASS_CAPACITY];

void SetupMobyFunctions(int oClass);

void InitMobyClassDists(void);

void StashMobyClassDists(void);

void RestoreMobyClassDists(void);

void MB_GetBonePos(MobyInstance *moby, int index, Vec4 *out);

void MB_GetBoneTransformation(MobyInstance *moby, int index, Mtx4 *out);

int MB_FindNearestAnimTrigger(MobySeq *sequence, float time);

void MB_GetJointsWorldMtx(MobyInstance *moby, int count, int *indices, Mtx4 *joints);

int M849_CallClassCallback04(MobyInstance *moby);

int M849_CallClassCallback0C(MobyInstance *moby);

int AnimCache_Register(MobyInstance *moby);

void GetMobyJointsWorldPos(MobyInstance *moby, int count, int *joints, Vec4 *out);

struct AnimLayer {
    short joint;               /* 0x00 */
    unsigned short jointCount;          /* 0x02 */
    unsigned char inUse;                /* 0x04 */
    unsigned char stepped;              /* 0x05  */
    unsigned char prevFromBuffer;       /* 0x06 */
    unsigned char curFromBuffer;        /* 0x07   */
    float weight;            /* 0x08   */
    unsigned char *jointMap;            /* 0x0c */
    void *jointBuf;          /* 0x10  */
    struct MobyClass *pClass;     /* 0x14  */
    struct MobyClass *animClass;  /* 0x18 */
    struct AnimLayer *next;  /* 0x1c */
    unsigned char prevFrame;            /* 0x20 */
    unsigned char curFrame;             /* 0x21 */
    unsigned char prevSeq;              /* 0x22 */
    unsigned char curSeq;               /* 0x23 */
    float blend;             /* 0x24   */
    float speed;             /* 0x28 */
    float frameScale;        /* 0x2c */
    unsigned char _pad30[8];
    void *prevFrameData;     /* 0x38 */
    void *curFrameData;      /* 0x3c */
};


void MB_UpdateAnimLayer(MobyInstance *moby, AnimLayer *layer);
extern Vec4 LightDirection __attribute__((section(".data")));
void MB_GetLightDirection(MobyInstance *moby, Vec4 *out);
void MB_UpdateLightAngle(void);

void MobyComputeJointMtxs(MobyInstance *moby, int count, Mtx4 *out);

#endif
