#include <common.h>
#include <gpu.h>

void PrintFlush()
{
    FntFlush(-1);
    DrawSync(0);
}