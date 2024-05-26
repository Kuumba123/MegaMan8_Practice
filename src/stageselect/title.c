#include <common.h>
#define timer ((char *)0x801d1848)[0]
#define transf ((char *)0x8015d226)[0]
#define cursor ((char *)0x801d284c)[0]
void Title()
{
    if (timer != 0 && transf == 0)
    {
        if ((buttonsPressed & (PAD_CROSS + PAD_START)) == 0)
        {
            if ((buttonsPressed & (PAD_UP + PAD_DOWN)) != 0)
            {
                PlaySound(0x14);
                if (cursor == 0)
                {
                    cursor = 2;
                }
                else
                {
                    cursor = 0;
                }
            }
        }else{
            PlaySound(0x15A);
            if(cursor == 0){
                StopSong();
                CreateTransition(3);
                gameMode2 =  3;
                timer = 4;
            }else{
                gameMode2 = 4;
                timer = 0;
            }
        }
    }
}
#undef cursor
#undef transF
#undef timer