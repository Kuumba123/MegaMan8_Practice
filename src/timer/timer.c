#include <common.h>
#include <object.h>
#include "../practice.h"

void SaveState();
void LoadState();

void DrawTime(int time)
{
    int totalSeconds = time / 60;
    int minutes = totalSeconds / 60;
    int seconds = totalSeconds % 60;
    int frames = time % 60;

    FntPrint("  %d:", minutes);
    if (seconds > 9)
    {
        FntPrint("%d:", seconds);
    }
    else
    {
        FntPrint("0%d:", seconds);
    }
    if (frames > 9)
    {
        FntPrint("%d\n", frames);
    }
    else
    {
        FntPrint("0%d\n", frames);
    }
}

void DrawRoomTime(int time)
{
    FntPrint("  ROOM TIME:");
    DrawTime(time);
}

void RunTimer()
{
    GetRng(); // TODO: add option for locking/displaying RNG (maybe)

    DrawTime(practice.stageTimer);

    if (practice.stateTextTimer != 0)
    {
        FntPrint(" State Saved\n");
        practice.stateTextTimer -= 1;
    }

    if (pacStatus == 1 || songLoading)
    {
        FntPrint(" (Loading)\n");
    }
    else
    {
        practice.stageTimer += 1;
        practice.roomTimer += 1;
        if (((char *)0x8015e23d)[0] > 1 || ((char *)0x8015e23E)[0] > 1 || ((char *)0x8015e23d)[0] == 3)
        {
            if ((buttonsPressed & (PAD_L2 + PAD_R2 + PAD_SELECT)) != 0 && ((char *)0x8015d226)[0] == 0 && *((char *)0x801c73e8) == 0)
            {
                if ((buttonsHeld & (PAD_R2 + PAD_SELECT) /*L2*/) == (PAD_R2 + PAD_SELECT))
                {
                    SaveState();
                }
                else if ((buttonsHeld & (PAD_L2 + PAD_SELECT) /*R2*/) == (PAD_L2 + PAD_SELECT) && practice.stateMade)
                {
                    LoadState();
                }
            }
        }
    }
}
void RunTimer2() // For Pause Menu
{
    practice.stageTimer += 1;
    practice.roomTimer += 1;
    ThreadSleep(1);
    DrawTime(practice.stageTimer);
}

void SaveRoomTime(uint8_t *objP)
{
    if (objP[6] == 0x10) // id
    {
        void (*effectFunc)() = 0x80132210;
        effectFunc(objP);
    }
    else
    {
        void (*effectFunc)() = 0x801324c0;
        effectFunc(objP);
    }

    if (objP[1] == 2) // Check if Transition started
    {
        // store in object xspeed
        *((int *)(objP + 0x14)) = practice.roomTimer;
        practice.roomTimer = 0;
    }
}
void ShowRoomTime(uint8_t *objP)
{
    DrawRoomTime(*((int *)(objP + 0x14)));

    if (objP[6] == 0x10) // id
    {
        void (*effectFunc)() = 0x80132324;
        effectFunc(objP);
    }
    else
    {
        void (*effectFunc)() = 0x80132628;
        effectFunc(objP);
    }
}

void SaveRoomTime2(uint8_t *objP) //For Boss Doors
{
    // store in object xspeed
    *((int *)(objP + 0x14)) = practice.roomTimer;
    practice.roomTimer = 0;

    SetAnime(objP,1);
}
void ShowRoomTime2(uint8_t * objP)
{
    DrawRoomTime(*((int *)(objP + 0x14)));
    AnimeAdvance(objP);
}