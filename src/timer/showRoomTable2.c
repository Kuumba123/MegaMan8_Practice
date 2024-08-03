#include <common.h>
void SaveRoomTime(uint8_t * objP);
void ShowRoomTime(uint8_t * objP);

static void (*transitionV_ObjectTable[])() = {
    &SaveRoomTime,
    &ShowRoomTime
};