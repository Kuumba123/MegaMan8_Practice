#include <common.h>
#include "../practice.h"
bool weaponTable[8][8] = {
    /*F,TH,I, T, W,SW, H, A*/
    {1, 0, 0, 0, 0, 0, 0, 0}, //Frost
    {1, 0, 1, 1, 0, 0, 0, 0}, //Clown
    {1, 0, 1, 0, 0, 0, 0, 0}, //Tengu
    {0, 0, 0, 0, 0, 0, 0, 0}, //Grenade
    {1, 1, 1, 1, 1, 0, 0, 1}, //Sword
    {1, 1, 1, 1, 0, 0, 0, 1}, //Aqua
    {1, 1, 1, 1, 0, 0, 0, 0}, //Astro
    {1, 1, 1, 1, 1, 1, 0, 1}};//Search

void ClearWeapons(){
    for (size_t i = 0; i < 16; i++) //Clear Aquaired Weapons
    {
        ((char*)0x801b1eac)[i * 4] = 0;
    }
    ((char*)0x801b1eac)[0] = 1; //Bustin
    ((char*)0x8016d2f2)[0] = 0; //Hyper Slide
}
void AssignWeapons(int id, bool mid)
{
    practice.stageTimer = 0;
    practice.stateTextTimer = 0;

    ((int*)0x8016d300)[0] = 0; //Rush Power Ups (Bike > Mystery > Missle > Med)

    if(id == 0){
        ClearWeapons();
        return;
    }
    ((char*)0x801b1eb0)[0] = 1; //Mega-Ball
    ((char*)0x8016d2f2)[0] = 0; //Hyper Slide

    if(id > 4 && id != 9){
        ((char*)0x8016d2f2)[0] = 0xF; //Hyper Slide
        ((char*)0x8016d300)[0] = 1; //Rush Bike
    }
    
    if(id > 9){ //Castle Stages
        for (size_t i = 0; i < 8; i++)
        {
            ((char*)0x801b1eb4)[i * 4] = 1;
        }
        ((int*)0x8016d300)[0] = 1; //Rush Power Ups (Bike > Mystery > Missle > Med)
    }else if(id != 9){
        for (size_t i = 0; i < 8; i++)
        {
            ((char*)0x801b1eb4)[i * 4] = weaponTable[id - 1][i];
        }
        
    }else{
        for (size_t i = 0; i < 4; i++) //just 1st 4
        {
            ((char*)0x801b1eb4)[i * 4] = 1;
        }
    }

    //Determine Rush-Power Ups
    if(id == 4 && mid){
        ((char*)0x8016d300)[0] = 1; //Rush Bike
    }
    if(id == 2 && mid){
        ((char*)0x8016d300)[1] = 1; //Rush Mystery
    }
    if(id == 5 && mid){
        ((char*)0x8016d300)[2] = 1; //Rush Missle        
    }
    if(id == 6 && mid){
        ((char*)0x8016d300)[3] = 1; //Rush Med
    }

    //Weapon Check
    if(((char*)0x801b1eb4)[0 * 4] == 1){
        ((char*)0x8016d300)[0] = 1; //Rush Bike
    }
    if(((char*)0x801b1eb4)[1 * 4] == 1){
        ((char*)0x8016d300)[1] = 1; //Rush Mystery
    }
    if(((char*)0x801b1eb4)[5 * 4] == 1){
        ((char*)0x8016d300)[2] = 1; //Rush Missle        
    }
    if(((char*)0x801b1eb4)[4 * 4] == 1){
        ((char*)0x8016d300)[3] = 1; //Rush Med
    }

}