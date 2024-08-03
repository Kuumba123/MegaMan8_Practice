#include <common.h>

/*Pre Loading the player file just in case a mid stage is select 1st*/

void SetupSPU();

void PreLoadPlayerFile()
{
    *((int*)0x8016d294) = 0x80137840;

    
    PacSeek(0x71);
    while (!FileCollected())
    {
    }

    SetupSPU();
}