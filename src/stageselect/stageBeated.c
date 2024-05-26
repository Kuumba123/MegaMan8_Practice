#include <common.h>
#include "../practice.h"
void DrawTime(int time);
void ClearWeapons();
void StageBeated(){
    ((char*)0x801c336c)[0] = 1; //Intro Clear Flag
    ((char*)0x801cf840)[0] = 2; //Game Mode (Stage Select)
    ((char*)0x801b299a)[0] = 0; //FadeF
    ((char*)0x801b299a)[1] = 0; //FadeR
    ((char*)0x801b299a)[2] = 0; //FadeG
    ((char*)0x801b299a)[3] = 0; //FadeB

    while (1)
    {
        ThreadSleep(1);
        FntPrint("\tYour Level Clear Time was\n\n\t\t\t");
        DrawTime(practice.stageTimer);
        FntPrint("\n\n\n\tPress any button to\n\treturn to stage select");

        if(buttonsPressed != 0){
            ClearWeapons();
            break;
        }
    }
    
}