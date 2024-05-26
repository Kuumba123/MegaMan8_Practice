#include <common.h>
static struct selectStruct
{
    u_char mode;
    u_char act;
    u_char act2;
    u_char pastStage;
    u_char newStage;
};
#define midPoint ((u_char *)0x801c3374)[0]
#define checkPoint ((u_char *)0x801c3371)[0]
#define midCheckPoints ((u_char *)0x80137af4)
void AssignWeapons(int id,bool mid);
void SelectOptions(struct selectStruct *selectP)
{
    midPoint = 0; // Default
    checkPoint = 0;
    uint cursor = 0;
    char destMode = ((char *)selectP)[0xE];
    while (1)
    {
        if (destMode == 2 || destMode == 4 || destMode == 5) //Stage Load
        {
            if (selectP->newStage > 0 && selectP->newStage != 9)
            {
                ThreadSleep(1);
                if (selectP->newStage < 9)
                {
                    FntPrint("1ST");
                    if (cursor == 0)
                    {
                        FntPrint("<\n");
                    }
                    else
                    {
                        FntPrint("\n");
                    }
                    FntPrint("MID");
                    if (cursor == 1)
                    {
                        FntPrint("<\n");
                    }
                    else
                    {
                        FntPrint("\n");
                    }
                }
                else
                { // The 4 Castle Levels
                    for (size_t i = 0; i < 4; i++)
                    {
                        FntPrint("W%d", i + 1);
                        if (cursor == i)
                        {
                            FntPrint("<\n");
                        }
                        else
                        {
                            FntPrint("\n");
                        }
                    }
                }

                if ((buttonsPressed & PAD_UP) == PAD_UP)
                {
                    cursor--;
                }
                else if ((buttonsPressed & PAD_DOWN) == PAD_DOWN)
                {
                    cursor++;
                }
                else if ((buttonsPressed & (PAD_CROSS + PAD_START)) != 0) // Load Level
                {
                    if (selectP->newStage > 9)
                    {
                        selectP->newStage = cursor + 0xA;
                    }
                    else
                    {
                        if (cursor != 0)
                        {
                            checkPoint = midCheckPoints[selectP->newStage];
                            midPoint = 1;
                        }
                    }
                    AssignWeapons(selectP->newStage,midPoint);
                    selectP->act2 = 0;
                    selectP->mode = 2;
                    return;
                }

                if (selectP->newStage < 9)
                {
                    cursor &= 1;
                }
                else
                {
                    if (cursor > 3)
                    {
                        cursor = 0;
                    }
                }
            }
            else
            {
                ((u_char *)selectP)[0xD] = 0;
                ((u_char *)selectP)[0xE] = 0;
                AssignWeapons(selectP->newStage,0);
                if(selectP->newStage == 9){
                    ((char*)0x801c336c)[0] = 3;
                    return;
                }
                selectP->mode = 2;
                return;
            }
        }else if(destMode == -1){ //Dr.Lights Labs (change this to 6 for future updates)

        }else{  //Do Things the game does semi normally
            if(!songLoading){
                ((char*)selectP)[0xD] = 0;
                ((char*)selectP)[0xE] = 0;
                selectP->mode = destMode;
                selectP->act = 0;
            }

            return;
        }
    }
}
#undef midPoint
#undef checkPoint
#undef midCheckPoints