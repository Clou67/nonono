#include "common.h"
#include "camera.h"
#include "mathfunc_inline.h"
#include "vtbl.h"

void FUN_0030f338(UpdateCam *camera)
{
}

extern Vec4 HeroPosition __attribute__((section(".data")));

void Camera_CopyHeroPosition(MobyInstance *target, Vec4 *position)
{
    CopyVec4Inline(position, &HeroPosition);
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/camera0", FUN_0030f358);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/camera0", FUN_0030f468);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/camera0", FUN_0030f498);

void FUN_0030f600(UpdateCam *camera, void *work)
{
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/camera0", FUN_0030f608);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/camera0", func_0030F750);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/camera0", FUN_0030f758);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/camera0", FUN_0030f890);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/camera0", FUN_0030fa78);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/camera0", FUN_0030fb08);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/camera0", FUN_003101c0);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/camera0", FUN_00310790);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/camera0", FUN_00310850);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/camera0", FUN_00310908);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/camera0", FUN_00310a08);

void FUN_00311008(UpdateCam *camera)
{
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/camera0", FUN_00311010);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/camera0", FUN_003111d8);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/camera0", FUN_00311890);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/camera0", FUN_00311dd0);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/camera0", ActivateCamera_0);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/camera0", FUN_00312310);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/camera0", FUN_003124f0);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/camera0", FUN_003126f8);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/camera0", FUN_00312708);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/camera0", FUN_003127f0);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/camera0", FUN_00312ba0);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/camera0", FUN_00312c08);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/camera0", FUN_00312ef8);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/camera0", func_00313548);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/camera0", FUN_00313550);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/camera0", FUN_00313560);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/camera0", FUN_00313598);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/camera0", FUN_00313628);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/camera0", FUN_00313668);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/camera0", FUN_00313690);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/camera0", FUN_003136c8);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/camera0", FUN_00313718);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/camera0", FUN_00313740);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/camera0", FUN_00313768);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/camera0", FUN_003137b0);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/camera0", FUN_003137f8);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/camera0", FUN_00313820);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/camera0", FUN_00313858);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/camera0", FUN_00313888);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/camera0", FUN_00313aa0);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/camera0", FUN_00313af0);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/camera0", FUN_00313b48);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/camera0", FUN_00313b88);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/camera0", FUN_00313d90);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/camera0", FUN_00314118);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/camera0", FUN_003141e8);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/camera0", FUN_003146f0);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/camera0", FUN_003148f8);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/camera0", FUN_00314c78);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/camera0", FUN_00314d88);

int InitCamera_0(UpdateCam *camera)
{
    return 0;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/camera0", UpdateCamera_0);

void ExitCamera_0(UpdateCam *camera)
{
}
