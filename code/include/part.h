#ifndef PART_H
#define PART_H

#include "moby.h"

struct PartInstance;

// DL particle records, including later-game effects. Shared RaC1 layouts retain verified differences.
// RaC1 uses unsigned state bytes in Part011, Part030, Part040, Part042 and Part058.
// Part048::rotSpeed is 8-bit in RaC1, 16-bit in DL.

struct Path;

struct Part000 {
    Vec4 vel;
};

struct Part002 {
    int vel1;
    int vel2;
    int rgba1;
    int rgba2;
    short int shootTimer;
    short int slowTimer;
    short int fadeTimer;
    short int initScale;
    short int finalScale;
    unsigned char unk_1A;
    unsigned char unk_1B;
};

struct Part003 {
    Vec4 vel;
    char *existFlag;
    int state;
    int numFlipColls;
    int numFramesSinceColl;
};

struct Part004 {
    Vec4 vel;
    int beginColor;
    int endColor;
    short int maxScale;
    short int startScale;
    int lifeSpan;
};

struct Part005 {
    int fadeTimer;
    float scaleDelta;
};

struct Part006Deltas {
    Vec4 acc;
    Vec4 min;
    Vec4 max;
    float dscale;
    float drot;
    float dalpha;
    float bounce;
    float velmax;
    float minalpha;
    float maxalpha;
    float dr;
    float dg;
    float db;
    float minr;
    float ming;
    float minb;
    float maxr;
    float maxg;
    float maxb;
    int flags;
    float minscale;
    float maxscale;
    MobyInstance *parent;
};

struct Part006 {
    Vec3 vel;
    struct Part006Deltas *d;
    float alpha;
    float rot;
    unsigned char rf;
    unsigned char gf;
    unsigned char bf;
    unsigned char flags;
};

struct Part007 {
    int fadeTimer;
    float scaleDelta;
};

struct Part008 {
    Vec4 vel;
    int beginRGBA;
    int endRGBA;
    int lifeSpan;
    float scaleDelta;
};

struct Part009 {
    int timer;
    MobyInstance *pParent;
    float rotRange;
    float curRot;
    int alpha;
};

struct Part010 {
    Vec4 vel;
    float r;
    float g;
    float b;
    float alpha;
};

struct Part011 {
    Vec4 vel;
    int beginRGBA;
    int endRGBA;
    unsigned char totalTime;
    unsigned char stateFlags;
    unsigned char generationCount;
    unsigned char lifeSpan;
    float maxScale;
};

struct Part012 {
    Vec4 vel;
    float dist;
    int initRGBA;
    int finalRGBA;
    char timer;
    char lifetime;
    char rotSpeed;
    char flags;
};

struct Part013 {
    int timer;
    int state;
    int rotDir;
    float scale;
    float zSpeed;
    int rgb;
};

struct Part014 {
    int rot;
    int state;
    MobyInstance *pMoby;
};

struct Part015 {
    Vec4 vel;
    int beginRGBA;
    int endRGBA;
    short int lifeSpan;
    short int master;
    float maxScale;
};

struct Part016 {
    Vec4 vel;
    int beginRGBA;
    int endRGBA;
    short lifeSpan;
    short partClass;
    float maxScale;
};

struct Part018 {
    Mtx3 *rotmatrix;
    float alpha;
    float rot;
    float asign;
};

struct Part020 {
    Mtx3 *rotmatrix;
    float alpha;
    float rot;
    float asign;
    float offset;
    float angle;
    MobyInstance *target;
    float vel;
};

struct Part021 {
    Vec4 vel;
    int beginRGBA;
    int endRGBA;
    short int lifeSpan;
    short int master;
    float maxScale;
};

struct Part022 {
    Vec4 vel;
    int beginRGBA;
    int endRGBA;
    short int lifeSpan;
    short int pad;
    float dScale;
};

struct Part023 {
    int rgb;
    int state;
    short int rotDir;
    unsigned char initAlpha;
    unsigned char initTimer;
    float scale;
    Vec4 vel;
};

struct Part024 {
    PartInstance *parent;
    float scalemul;
    float scaleadd;
    float alpha;
    float alphamul;
    float dalpha;
};

struct Part025 {
    Vec4 vel;
    float r;
    float g;
    float b;
    float alpha;
};

struct Part026 {
    MobyInstance *parent;
    short int timer;
    short int joint;
    int lifeSpan;
    int alpha;
};

struct Part027 {
    Vec4 vel;
    int timer;
    int lifeSpan;
    int alpha;
};

struct Part028 {
    Mtx3 *rotmatrix;
    float alpha;
    float rot;
    float asign;
    Vec4 vel;
};

// RaC1 attachment data; DL uses a different Part029 layout.
struct Part029Attachment {
    MobyInstance *parent;
    float alpha;
    float rot;
    short textureFrame;
    short bone;
    float alphaStep;
    float cameraOffset;
};

struct Part029_Style {
    float fWidth;
    float fLengthScale;
    float fSlowDownFactor;
    float fpad[1];
};

struct Part030 {
    Vec4 vel;
    PartInstance *prev;
    PartInstance *next;
    float ground;
    short grounded;
    unsigned short type;
};

struct Part031 {
    MobyInstance *target;
};

// RaC1 stores the second point before the DL attachment record.
struct Part031TwoPoint {
    Vec4 end;
    Part031 attachment;
};

struct Part032 {
    MobyInstance *parent;
    float alpha;
    float dalpha;
    float rot;
    float r;
    float g;
    float b;
};

struct Part034 {
    float velx;
    float vely;
    float velz;
    float idealScale;
    float waterHeight;
    float t;
    float dt;
    float waveSpeed;
};

struct Part035 {
    Vec4 vel;
    int type;
    int timer;
    float spawn_height;
    float gravity;
};

struct Part036 {
    int *pLightOn;
    float ang;
    float thresh;
    int rgba;
    Vec4 pos;
};

struct Part037 {
    Vec4 pos;
    int rgba;
    int thresh;
    unsigned char unk_18;
    unsigned char unk_19;
    unsigned char unk_1A;
    unsigned char unk_1B;
    unsigned char unk_1C;
    unsigned char unk_1D;
    unsigned char unk_1E;
    unsigned char unk_1F;
};

struct Part038 {
    Vec4 vel;
    float scale_delta;
    float alpha;
    unsigned char unk_18;
    unsigned char unk_19;
    unsigned char unk_1A;
    unsigned char unk_1B;
    unsigned char unk_1C;
    unsigned char unk_1D;
    unsigned char unk_1E;
    unsigned char unk_1F;
};

struct Part039 {
    float alpha;
    MobyInstance *pMoby;
    int texIdx;
};

struct Part040 {
    Vec4 vel;
    float rot;
    short timer;
    short posttimer;
    unsigned char flags;
    unsigned char scaleFactor;
    short sPad;
    MobyInstance *parent;
};

struct Part041 {
    struct MobyInstance *parent;
};

struct Part042 {
    Vec4 vel;
    float rot;
    short timer;
    short posttimer;
    unsigned char flags;
    unsigned char pad_19[3];
    MobyInstance *parent;
};

struct Part043 {
    Vec4 vel;
    struct MobyInstance *parent;
    char r;
    char g;
    char b;
    char a;
    short int lifetime;
    unsigned char unk_1A;
    unsigned char unk_1B;
    unsigned char unk_1C;
    unsigned char unk_1D;
    unsigned char unk_1E;
    unsigned char unk_1F;
};

struct Part044 {
    Vec3 vel;
    float gravity;
    char rotSpeed;
    unsigned char r;
    unsigned char g;
    unsigned char b;
    float scaleSpeed;
    float damp;
    short int frames;
    short int alpha;
};

struct Part045 {
    Vec4 vel;
    float expandSpeed;
    float *zHeight;
    unsigned char unk_18;
    unsigned char unk_19;
    unsigned char unk_1A;
    unsigned char unk_1B;
    unsigned char unk_1C;
    unsigned char unk_1D;
    unsigned char unk_1E;
    unsigned char unk_1F;
};

struct Part046 {
    Vec4 vel;
    float rot;
    float spin;
    float *zHeight;
    unsigned char unk_1C;
    unsigned char unk_1D;
    unsigned char unk_1E;
    unsigned char unk_1F;
};

struct Part048 {
    Vec4 vel;
    float invTimer;
    int RGBA1;
    int RGBA2;
    char rotSpeed;
    unsigned char pad_1D[3];
};

struct Part049 {
    Vec3 vel;
    MobyInstance *pParent;
};

struct Part050 {
    Vec4 vel;
    float height;
    int rotSpeed;
    float gravity;
    unsigned char unk_1C;
    unsigned char unk_1D;
    unsigned char unk_1E;
    unsigned char unk_1F;
};

struct Part052 {
    float initScale;
    float finalScale;
    int initRGBA;
    int finalRGBA;
    float invTime;
};

struct Part053 {
    float initScale;
    float finalScale;
    short int initTime;
    char rotSpeed;
    char initAlpha;
    Vec3 vel;
    float gravity;
    short int alphaSub;
    short int pad;
};

struct Part054 {
    struct Path *pPath;
    float curDist;
    float flowSpeed;
    float segmentLength;
    float rot;
    MobyInstance *pParent;
};

struct Part055 {
    MobyInstance *pParent;
    int joint;
    int parent_oClass;
    float start_width;
};

struct Part057 {
    Vec4 vel;
    float rot;
    float spin;
    unsigned char unk_18;
    unsigned char unk_19;
    unsigned char unk_1A;
    unsigned char unk_1B;
    unsigned char unk_1C;
    unsigned char unk_1D;
    unsigned char unk_1E;
    unsigned char unk_1F;
};

struct Part058 {
    Vec4 vel;
    unsigned char type;
    unsigned char fade_time;
    unsigned char burst_time;
    unsigned char spawn_rate;
    unsigned char state;
    unsigned char flame_time;
    unsigned char alpha_top;
    unsigned char pad;
    MobyInstance *pParent;
    float damageHp;
};

struct Part059 {
    Vec4 ofs;
    int type;
    MobyInstance *hero;
    int pad[2];
};

struct Part060 {
    Vec3 vel;
    MobyInstance *hero;
    Vec3 ofs;
    int type;
};

struct Part061 {
    MobyInstance *parent;
    float alpha;
    float rot;
    short int frame;
    short int joint;
    float dalpha;
    float dist;
};

struct Part062 {
    short int alphaSub;
    char type;
    char addHero;
    Vec3 vel;
    Vec3 pos;
    short int maxTimer;
    short int timer;
};

struct Part064 {
    Vec4 vel;
    float height;
    float gravity;
    int endRGBA;
};

struct Part065 {
    Vec4 vel;
    float r;
    float g;
    float b;
    float alpha;
};

struct Part066 {
    Vec4 vel;
    float expandSpeed;
};

enum PartOrbitMode { PART_ORBIT_TRAIL_FADE = 0, PART_ORBIT_EMITTER = 1 };
enum { PART_ORBIT_FADE_FRAMES = 10, PART_ORBIT_ALPHA_STEP = 0x10 };

struct Part067 {
    Vec3 vel;
    MobyInstance *pParent;
    float tOuter;
    float tInner;
    short int aliveTime;
    short int alphaSub;
    short int type;
    short int timer;
};

struct Part068 {
    MobyInstance *pParent;
    char joint;
    unsigned char vary_percent;
    short int parent_oClass;
    float start_width;
    float length;
};

struct Part069 {
    Vec4 vel;
    float initTimerInv;
    short int initAlpha;
    short int state;
    int color;
    MobyInstance *pParent;
};

struct update78 {
    Vec4 closePt;
    int generator;
    int fadeTime;
    int pad[2];
};

struct Part071 {
    unsigned int vel1;
    unsigned int vel2;
    int rgba1;
    int rgba2;
    short shootTimer;
    short slowTimer;
    short fadeTimer;
    short pad_16;
    update78 *p78Var;
};

struct Part072 {
    Vec4 vel;
    int type;
    int spawnedSmoke;
    int rot;
    float scaleFactor;
};

struct Part074_fixed {
    int beginColor;
    int endColor;
    short int maxScale;
    short int startScale;
    int lifeSpan;
};

struct Part074 {
    Vec3 vel;
    MobyInstance *pParent;
    Vec3 ofs;
    struct Part074_fixed *fixed;
};

struct Part075 {
    Vec4 vel;
    short int type;
    short int rot;
    float scaleFactor;
    float timerInv;
    int alphaDec;
};

struct Part078 {
    float initScale;
    float finalScale;
    short int initTime;
    char rotSpeed;
    char initAlpha;
    Vec3 vel;
    MobyInstance *pTarget;
    float zOfs;
};

struct Part079 {
    Vec4 ofs;
    Vec3 vel;
    MobyInstance *pParent;
};

struct Part080 {
    int type;
};

struct Part081 {
    Vec4 vel;
    short int burst_time;
    char type;
    char spawn_rate;
    char state;
    char flame_time;
    char alpha_top;
    char trail_ndx;
    MobyInstance *pParent;
    float damageHp;
};

struct Part082 {
    Vec4 vel;
    float rot;
    short int timer;
    short int posttimer;
    char flags;
    unsigned char unk_19;
    unsigned char unk_1A;
    unsigned char unk_1B;
    struct MobyInstance *parent;
};

struct Part083 {
    Vec4 vel;
    float speed;
    float scale;
    short int lifetimeCounter;
    short int rot;
    float minZ;
};

struct Part084 {
    MobyInstance *parent;
    short int timer;
    short int period;
    float scale;
    int alpha;
};

struct Part085 {
    Vec3 vel;
    float gravity;
    float scaleDelt;
    char padC;
    char rotSp;
    short int alphaDelt;
    float currAlpha;
    void *pFunc;
};

struct Part086_fixed {
    int *frameColors;
    short int *frameScales;
    short int *frameTimes;
    short int numFrames;
    unsigned char unk_0E;
    unsigned char unk_0F;
    int lifeSpan;
    float damping;
};

struct Part086 {
    Vec4 vel;
    struct Part086_fixed *fixed;
    short int currentFrame;
    unsigned char unk_16;
    unsigned char unk_17;
    int rotSpeed;
    unsigned char unk_1C;
    unsigned char unk_1D;
    unsigned char unk_1E;
    unsigned char unk_1F;
};

struct Part087 {
    MobyInstance *parent;
    short int timer;
    short int joint;
    int color;
    int pad;
};

struct Part089 {
    MobyInstance *pMoby;
    int jointIdx;
    float pushOfs;
    char iUseNormal;
    char rotSp;
    char rotWithCam;
    char useSetAlpha;
    Vec4 posOfs;
};

struct Part090 {
    Vec4 vel;
};

struct Part091 {
    Vec4 vel;
    int beginRGBA;
    int endRGBA;
    short int lifeSpan;
    short int master;
    float maxScale;
};

struct Part092 {
    float initScale;
    float finalScale;
    short int initTime;
    char rotSpeed;
    char initAlpha;
    Vec3 vel;
    int frameOfs;
    short int alphaSub;
    short int fastExpandFrames;
};

struct Part094 {
    Vec4 vel;
    float speed;
    float target;
    short int rot;
    short int pad;
    int intPad;
};

struct Part096 {
    Vec4 vel;
    int fadeTime;
    int rotSpeed;
    float endSize;
    float grav;
};

struct Part097 {
    Vec3 vel;
    float gravity;
    float scaleDelt;
    char alphaDelt;
    char rotSp;
    short int padS;
    int pad;
    void *pFunc;
};

struct Part098 {
    Vec3 vel;
    float gravity;
    float scaleDelta;
    char alphaDelta;
    char rotationDelta;
    short int padding1;
    int alphaTexture;
    void *pUpdateFunction;
};

struct Part099 {
    Vec4 vel;
    MobyInstance *pMoby;
    short int fadeTime;
    short int rotSpeed;
    float endSize;
    float driftOsc;
};

struct Part100 {
    Vec4 vel;
    float height;
    int rotSpeed;
    float gravity;
    Vec4 *refVel;
};

struct Part101 {
    struct Part101_Fixed *fixed;
    float radius;
    float theta;
    float angSpeed;
    float scaleInc;
    short int rotSpeed;
    unsigned char unk_16;
    unsigned char unk_17;
};

struct Part101_Fixed {
    Vec4 center;
    float thetaMax;
    unsigned char unk_14;
    unsigned char unk_15;
    unsigned char unk_16;
    unsigned char unk_17;
    unsigned char unk_18;
    unsigned char unk_19;
    unsigned char unk_1A;
    unsigned char unk_1B;
    unsigned char unk_1C;
    unsigned char unk_1D;
    unsigned char unk_1E;
    unsigned char unk_1F;
};

struct Part102 {
    Vec4 vel;
    float estimatedGroundZ;
    short int fadeTime;
    short int rotSpeed;
    float endSize;
    float driftOsc;
};

struct Part104 {
    Vec4 vel;
    int alpha;
    int onTrain;
    int pad[2];
};

struct Part105 {
    Vec3 vel;
    float gravity;
    float scaleDelt;
    char alphaDelt;
    char rotSp;
    short int padS;
    int pad;
    void *pFunc;
};

struct Part106 {
    Vec3 devDir;
    int endColor;
    char rotSpeed;
    char lifetime;
    char startAlpha;
    char state;
    float startScale;
    float endScale;
    float maxDev;
};

struct Part107 {
    Vec3 devDir;
    int endColor;
    char rotSpeed;
    char lifetime;
    char startAlpha;
    char state;
    char maxHeight;
    char startSpeed;
    char endSpeed;
    char distTraveled;
    float startScale;
    float endScale;
};

struct Part108 {
    Vec3 devDir;
    char endShade_startAlpha;
    char rotSpeed_state;
    char lifetime;
    char maxDev;
    Vec3 perpDir;
    char startSpeed;
    char endSpeed;
    char startScale;
    char endScale;
};

struct Part109 {
    Vec4 vel;
    int alpha;
    int pad[3];
};

struct Part110 {
    Vec4 vel;
    int startAlpha;
    int startColor;
    int lifeTime;
    int pad;
};

struct Part112 {
    Vec3 vel;
    float gravity;
    float scaleDelt;
    char alphaDelt;
    char rotSp;
    short int padS;
    int pad;
    void *pFunc;
};

struct Part114 {
    Vec4 vel;
    int rgba1;
    int rgba2;
    short int maxLife;
    char postEffect;
    char pad[5];
};

struct Part115 {
    short int startColor;
    short int endColor;
    signed char spinNum;
    char startOffsetAng;
    char startRadius;
    char endRadius;
    short int travelDirx;
    short int travelDiry;
    short int travelDirz;
    short unsigned int startScale;
    short int startingPosx;
    short int startingPosy;
    short int startingPosz;
    short unsigned int endScale;
    short int perpDirx;
    short int perpDiry;
    short int perpDirz;
    short unsigned int lifetimeMax;
};

struct Part115Init {
    Vec4 pos;
    Vec4 travelDir;
    char startR;
    char startG;
    char startB;
    char startA;
    char endR;
    char endG;
    char endB;
    char endA;
    int lifeTime;
    float startSwirlRadius;
    float endSwirlRadius;
    float startScale;
    float endScale;
    float spinNum;
    int blendMode;
    short int texMajor;
    short int texMinor;
    short int SpriteRotationSpeed;
    char startRot;
    char startOffsetAng;
    unsigned char unk_4C;
    unsigned char unk_4D;
    unsigned char unk_4E;
    unsigned char unk_4F;
};

struct Part116 {
    float speed;
    float baseWidth;
    float endScale;
    short int lifespan;
    short int pad;
};

struct Part118 {
    float speed;
    float baseWidth;
    float endScale;
    short int lifespan;
    short int pad;
};

struct Part119 {
    float speed;
    float baseWidth;
    float endScale;
    short int lifespan;
    short int pad;
};

struct Part121 {
    Vec4 vel;
    MobyInstance *pMoby;
    short int fadeTime;
    short int rotSpeed;
    float endSize;
    float driftOsc;
};

struct Part122 {
    MobyInstance *pMoby;
    float initScale;
    float finalScale;
    short int fadeTime;
    short int lifeTime;
    float pushOfs;
    char jointIndex;
    char rotSpeed;
    char startAlpha;
    char pushAxis;
    int pad[2];
};

struct Part123 {
    Vec4 vel;
    short int timer;
    short int initTimer;
    unsigned char stage;
    unsigned char shootTime;
    unsigned char expandTime;
    unsigned char fadeTime;
    float maxSize;
    unsigned char unk_1C;
    unsigned char unk_1D;
    unsigned char unk_1E;
    unsigned char unk_1F;
};

struct Part124 {
    Vec4 vel;
    MobyInstance *pMoby;
    float scaleStart;
    float scaleEnd;
    char alphaStart;
    char damageHp;
    char respawnProb;
    char pad;
};

struct Part125 {
    float scaleDelta;
    int initRGBA;
    int finalRGBA;
    float invTime;
};

struct Part126 {
    Vec4 vel;
    float invTime;
    float zHeight;
    float fpad;
    char stage;
    char emitDust;
    char cpad[2];
};

struct Part127 {
    Vec4 vel;
    float scaleDelt;
    char rotSp;
    char padc;
    short int grav;
    int startRGBA;
    int endRGBA;
};

struct Part128 {
    Vec4 vel;
    float invTime;
    float zHeight;
    float fpad;
    char stage;
    char emitDust;
    char cpad[2];
};

// RaC1-specific layouts without a verified named DL equivalent.

struct PartLineMotion {
    Vec4 origin;
    Vec4 velocity;
};

struct PartSpinMotion {
    Vec4 velocity;
    char rotationStep;
};

struct PartRotationMotion {
    char unk_00[0x18];
    char rotationStep;
};

struct PartFollowFade {
    short fadeStep; // alpha removed each frame
    short mode;     // 1 = frozen, 2 = follows pMoby
    MobyInstance *pMoby;
    char unk_08[8];
    Vec4 offset; // offset from pMoby
};

enum PartSplittingFlags {
    PART_SPLIT_REVERSE_ROTATION = 1,
    PART_SPLIT_FADING = 8,
    PART_SPLIT_NO_MOMENTUM = 0x40,
    PART_SPLIT_CHILD = 0x80
};

enum {
    PART_TEXTURE_SPLITTING = 12,
    PART_SPLIT_COLLISION_NO_DAMAGE = 4,
    PART_SPLIT_DAMAGE_FLAGS = 0x10001
};

enum PartBranchingFlags {
    PART_BRANCH_FADING = 1,
    PART_BRANCH_BOOST = 2,
    PART_BRANCH_GRAVITY = 4,
    PART_BRANCH_LONG_FADE = 8
};

enum { PART_DRIFT_COLLISION_FLAGS = 0x12 };

enum { PART_COLOR_DECAY_COLLISION_FLAGS = 2 };

enum PartDebrisKind {
    PART_DEBRIS_SPAWN_ON_LANDING = 1,
    PART_DEBRIS_UPWARD_ACCELERATING = 3
};

enum PartLinkedFlags {
    PART_LINK_FIXED = 1,
    PART_LINK_FADING = 2
};

enum PartTweenEmitterPhase {
    PART_TWEEN_INITIAL = 0,
    PART_TWEEN_EMITTING = 1,
    PART_TWEEN_EMITTED = 2
};

enum { PART_TEXTURE_TWEEN_EMITTER = 58 };

// Retail tests grounded/type with a packed 64-bit load beginning at ground.
#define PART_LINK_BLOCKED_MASK 0x1FFFF00000000LL

struct PartInstance {
    char i_class;
    char type;
    char tex;
    char gs_alpha;
    int rgba;
    char rot;
    char draw_dist;
    short timer;
    float scale;
    Vec4 pos;
    // Original fixed-size storage; the particle class selects its effect struct.
    int update[8];
};
// Texture slot of each particle class, indexed by the iClass passed to CreatePart.
extern unsigned char *PartClassTexs[];

// Per-class texture-selection records and the packed palette/texture descriptors (DL names).
struct PartTex {
    int pal;
    int tex;
};

extern unsigned char PartClassData[];
extern int PartTexCnt;
extern PartTex PartTexs[];

PartInstance *CreatePart(int iClass);
void DeletePart(PartInstance *part);

void UpdatePart_017(PartInstance *part);

void UpdatePart_033(PartInstance *part);

void UpdatePart_041(PartInstance *part);

void UpdatePart_063(PartInstance *part);
void UpdatePart_064(PartInstance *particle);

extern unsigned int PartFloorBurstRandomLimit;
// Original unreferenced small-data constants retained for the overlay layout.
extern const unsigned int PartLiteralSignedMask;
extern const unsigned int PartLiteralByteMask;
extern const float PartLiteralHalf;
extern const float PartLiteralZero;
extern const unsigned int PartLiteralNine;

PartInstance *SpawnPart_015(Vec4 *pos, Vec4 *vel, int beginRGBA, int endRGBA, float maxScale, int numFrames, int master, int useTex, int useGsAlpha);
PartInstance *SpawnPart_045(Vec4 *position, int flags, int color, float scale, float scaleStep);

void SpawnPart_008(Vec4 *position, Vec4 *velocity, int startColor, int endColor, int lifetime, float scale);

void UpdatePart_019(PartInstance *part);

void UpdatePart_056(PartInstance *part);

void UpdatePart_059(PartInstance *part);

void UpdatePart_070(PartInstance *part);
void UpdatePart_071(PartInstance *particle);

void UpdatePart_072(PartInstance *part);

PartInstance *SpawnPart_040(Vec4 *position, Vec4 *velocity, int flags, MobyInstance *owner);
void UpdatePart_040(PartInstance *particle);
PartInstance *SpawnPart_042(Vec4 *position, Vec4 *velocity, int flags, MobyInstance *owner);
void UpdatePart_042(PartInstance *particle);

// RaC1 places randomVelSpeed last; DL places it before generationCount.
void SpawnPart_011(Vec4 *pos, Vec4 *vel, int beginRGBA, int endRGBA, float maxScale, int numFrames, int totalTime, int generationCount, int state, float randomVelSpeed);
void UpdatePart_011(PartInstance *particle);

void UpdatePart_003(PartInstance *particle);

void UpdatePart_025(PartInstance *particle);

PartInstance *SpawnPart_016(Vec4 *position, Vec4 *velocity, int startColor, int endColor, float scale, int lifetime, int kind);
void UpdatePart_016(PartInstance *particle);

void UpdatePart_030(PartInstance *particle);

void UpdatePart_020(PartInstance *particle);

extern PartInstance *PartInstances;
PartInstance *SpawnPart_058(Vec4 *position, int phase, int tweenFrames, int emitFrames, int emitCount, int lifetime, MobyInstance *pParent, float damageScale, float speedScale);
void UpdatePart_058(PartInstance *particle);

PartInstance *SpawnPart_067(MobyInstance *parent, Vec4 *position, int lifetime, float orbit, float wobble, int type, int color, Vec4 *offset);
void UpdatePart_067(PartInstance *particle);

extern Vec4 ParticleProximityAxis __attribute__((section(".data")));
extern float PartProximityCorrectionLength;
extern const unsigned int PartLiteralReservedZero;
extern const unsigned int PartLiteralSeventySix;
void UpdatePart_078(PartInstance *particle);

enum { PART_WATER_FADE_FRAMES = 14 };
void UpdatePart_034(PartInstance *particle);

enum { PART_TEXTURE_ATTACHMENT_PULSE = 29, PART_ATTACHMENT_FRAME_MASK = 0xF };
void UpdatePart_029(PartInstance *particle);

void UpdatePart_065(PartInstance *particle);

enum { PART_TEXTURE_JOINT_PULSE = 61 };
void UpdatePart_061(PartInstance *particle);

enum PartPulsePhase { PART_PULSE_FADE_IN = 0, PART_PULSE_FADE_OUT = 1, PART_PULSE_CUSTOM_FADE_OUT = 2, PART_PULSE_CUSTOM_FADE_IN = 3 };
void UpdatePart_023(PartInstance *particle);

extern int PartSpinInitialColorSource;
extern int PartSpinInitialColorTarget;
extern int PartSpinFinalColorSource;
extern int PartSpinFinalColorTarget;
extern float PartSpinInitialScale;
extern float PartSpinFinalScale;
extern int PartSpinMinLifetime;
extern int PartSpinMaxLifetime;
extern int PartSpinAlternateInitialColorSource;
extern int PartSpinAlternateInitialColorTarget;
extern int PartSpinAlternateFinalColorSource;
extern int PartSpinAlternateFinalColorTarget;
extern float PartSpinAlternateInitialScale;
extern float PartSpinAlternateFinalScale;
extern int PartSpinAlternateMinLifetime;
extern int PartSpinAlternateMaxLifetime;
extern float PartSpinDeceleration;
extern float PartSpinVerticalSpeed;
extern const unsigned int PartSpinLiteral00;
extern float PartBeamFirstOffsetScale;
extern float PartBeamSecondOffsetScale;
extern const unsigned int PartSpinLiteral03;
extern const unsigned int PartSpinLiteral04;
extern const unsigned int PartSpinLiteral05;
extern const unsigned int PartSpinLiteral06;
extern const unsigned int PartSpinLiteral07;
extern const unsigned int PartSpinLiteral08;
extern const unsigned int PartSpinLiteral09;
extern const unsigned int PartSpinLiteral10;
extern const unsigned int PartSpinLiteral11;
extern const unsigned int PartSpinLiteral12;
extern const unsigned int PartSpinLiteral13;
extern unsigned char PartSpinSizeBoost[];
enum PartSpinFlags { PART_SPIN_ALTERNATE_SCALE = 1, PART_SPIN_SIZE_BOOST = 4 };
void UpdatePart_012(PartInstance *particle);

void UpdatePart_002(PartInstance *particle);

void UpdatePart_028(PartInstance *particle);

void UpdatePart_053(PartInstance *particle);

enum PartBallisticMode { PART_BALLISTIC_NO_CONTACT = 0, PART_BALLISTIC_LINE_CONTACT = 1, PART_BALLISTIC_WATER_CONTACT = 3 };
PartInstance *SpawnPart_066(Vec4 *position, int color, float scale, float height);
void UpdatePart_035(PartInstance *particle);

void UpdatePart_015(PartInstance *particle);

PartInstance *SpawnPart_021(Vec4 *position, Vec4 *velocity, int beginRGBA, int endRGBA, float maxScale, int lifetime, int master);
void UpdatePart_021(PartInstance *particle);

void UpdatePart_043(PartInstance *particle);

void UpdatePart_032(PartInstance *particle);

extern Vec4 PartGridDrift __attribute__((section(".data")));
extern float PartGridMinimumGround;
extern float PartGridClearance;
void UpdatePart_073(PartInstance *particle);

void UpdatePart_074(PartInstance *particle);

void UpdatePart_060(PartInstance *particle);

void UpdatePart_031(PartInstance *particle);

void UpdatePart_044(PartInstance *particle);

void UpdatePart_018(PartInstance *particle);

extern int PartGrayscaleFadeFrames;
void UpdatePart_009(PartInstance *particle);

#endif
