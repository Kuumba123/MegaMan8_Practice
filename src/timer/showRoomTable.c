#include <common.h>
void SaveRoomTime(u_char * objP);
void ShowRoomTime(u_char * objP);

static void (*transitionH_ObjectTable[])() = {
    &SaveRoomTime,
    &ShowRoomTime
};