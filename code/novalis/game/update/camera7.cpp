#include "common.h"
#include "hero.h"
#include "camera.h"
#include "vtbl.h"

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/camera7", ActivateCamera_7);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/camera7", FUN_003182c8);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/camera7", func_003188F8);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/camera7", FUN_00318900);

void FUN_003182c8(UpdateCam *camera);
void FUN_00318900(UpdateCam *camera);

void FUN_00318ad0(UpdateCam *camera)
{
    FUN_003182c8(camera);
    FUN_00318900(camera);
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/camera7", func_00318B00);

int InitCamera_7(UpdateCam *camera)
{
    return 0;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/update/camera7", UpdateCamera_7);

enum { CAMERA_DEACTIVATE_ON_EXIT = 3 };

void ExitCamera_7(UpdateCam *camera)
{
    if (Hero.requestedCamType != camera->type && Hero.state != HERO_STATE_FALL) {
        camera->activation.activate = 0;
        camera->activation.deactivate = CAMERA_DEACTIVATE_ON_EXIT;
    }
}
