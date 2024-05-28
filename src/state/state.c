#include <common.h>
#include <gpu.h>
#include <object.h>
#include "../practice.h"
#define VariableSetsCount 11
#define BuffersCount 5
#define StateCoolDown 25
#define StateTextTimer 25
#define enemyData ((Enemy*)0x801c2b3c)
FadeStruct fades[2];
void * freeAddress[] = {
    0x8018D83C, //Screen Data (end)
    0x801ABC40, //Backup Screen Data (end)
    0x801F9240, //End of Overlay
    0x8015d230, //Fade Clut
    0x8015a064, //Default Clut
};
int freeAddressSizes[] = {
    0x2400,
    0x2400,
    0x2DC0,
    0x1000,
    0x1000
};

void * readAddress[] ={
    0x8015b174, //Main
    0x801b1eec, //Item
    0x801b12ac, //Weapon
    0x801d184c, //Weapon Effect
    0x801cf540, //Effect
    0x801cf848, //Misc
    0x8015e23c, //Mega
    0x801d2890, //Rush
    0x80158f64, //Clut
    0x801d2914, //BG Layers
    0x801b28fc  //Clut Anime
};
int addressesSize[] = {
    0x40 * 0x60, //Main
    0x20 * 0x50, //Item
    0x20 * 0x60, //Weapon
    0x20 * 0x10, //Weapon Effect
    0x18 * 0x20, //Effect
    0x40 * 0x80, //Misc
    168, //Mega
    132, //Rush
    0x1000, //Clut
    48 * 3,  //BG Layers
    0x20    //Clut Anime
};

#define fadeF *((ushort*)0x801b299a)
#define fadeDone *((u_char*)0x8016ca90)
#define fadeR *((u_char*)0x801b299b)
#define fadeG *((ushort*)0x801b299c)
#define fadeB *((u_char*)0x801b299d)

void SaveState(){   //TODO: Fix Rush Textures Saving & Locked flag not being saved (Rush items check it)
    /*
    Save MegaMan Textures @ X:320, Y:192 & Boss Textures @ X:320, Y:208 
    */
   RECT rect = {
        320,192,64,16
   };
    MoveImage(&rect,0,488);
    DrawSync(0);
    rect.y = 192 + 16;
    
    MoveImage(&rect,0 + 64,488);
    DrawSync(0);
    rect.y = 192 + 16 + 16;

    MoveImage(&rect,0 + 64 + 64, 488);
    DrawSync(0);

    //backup enemy data other vars
    for (size_t i = 0; i < 255; i++)
    {
        backupSpawnData[i] = enemyData[i].spawned;
    }
    

    int freeId = 0;
    int freeSize  = freeAddressSizes[freeId];
    uint freeP = freeAddress[freeId];

    for (size_t i = 0; i < VariableSetsCount; i++)
    {
        int dumpSize = addressesSize[i];
        uint srcAddr = readAddress[i];

    SizeCheck:
        if(dumpSize > freeSize){
            MemoryCopy(freeP,srcAddr,freeSize);
            srcAddr += freeSize;
            dumpSize -= freeSize;

            //Fix Free Data Vars
            freeId++;

            if (freeId > BuffersCount - 1)
            {
                printf("ERROR: went past MAX buffer counts: %X\n", BuffersCount);
                return;
            }

            freeSize = freeAddressSizes[freeId];
            freeP = freeAddress[freeId];
            goto SizeCheck;
        }else{
            MemoryCopy(freeP,srcAddr,dumpSize);
            freeP += dumpSize;
            freeSize -= dumpSize;
        }
    }
    practice.roomTimerBackup = practice.roomTimer;
    practice.stageTimerBackup = practice.stageTimer;
    practice.backupMenuFlag = ((char*)0x801b2993)[0];
    practice.backPoint = ((char*)0x801c3371)[0];
    MemoryCopy(0x80190040,0x80171c3c,0xDE * 0x200);
    MemoryCopy(&practice.weaponCountBackup[0],0x801b2948,12);
    MemoryCopy(&practice.weaponAmmoBackup[0],0x801b1eac,12 * 4);
    practice.weaponBackup = ((char*)0x8016dc08)[0];
    practice.backupDoorFlag = ((char*)0x801b299e)[0];
    practice.backupRefights = ((ushort*)0x801c3378)[0];
    practice.backupSwapDisable = ((char*)0x801b2992)[0];
    practice.backupWater = *((ushort*)0x801b2988);
    practice.backupRushAmmo = *((char*)0x801b2990);
    practice.rushFlags = *((ushort*)0x801c3352);
    practice.rushFlags2 = *((ushort*)0x801c3354);
    practice.bossP = *((int*)0x801b297c);
    practice.showRush = *((char*)0x801b298f);
    practice.showedTxt = *((char*)0x801c337f);
    practice.frontDoor = *((char*)0x801b29a0);
    practice.shotCount = *((char*)0x801b2949);
    practice.ballP = *((int*)0x801b2980);
    practice.disableF = *((char*)0x801b2994);
    practice.fade = fadeF;
    practice.fade2 = fadeG;
    practice.fadeD = fadeDone;
    practice.backupMode2 = gameMode2;
    practice.stateMade = true;
    practice.stateTextTimer = StateTextTimer;
}

void LoadState(){
    /*
    Restore MegaMan Textures @ X:320, Y:192 & Boss Textures @ X:320, Y:208 
    */
   RECT rect = {
        0,488,64,16
   };
    MoveImage(&rect,320,192);
    DrawSync(0);
    rect.x = 64;
    
    MoveImage(&rect,320,192 + 16);
    DrawSync(0);
    rect.x = 64 + 64;

    MoveImage(&rect,320, 192 + 16 + 16);
    DrawSync(0);

    ThreadSleep(StateCoolDown);

    //restore enemy data
    for (size_t i = 0; i < 255; i++)
    {
        enemyData[i].spawned = backupSpawnData[i];
    }

    int freeId = 0;
    int freeSize  = freeAddressSizes[freeId];
    uint freeP = freeAddress[freeId];

    for (size_t i = 0; i < VariableSetsCount; i++)
    {
        int dumpSize = addressesSize[i];
        uint srcAddr = readAddress[i];

    SizeCheck:
        if(dumpSize > freeSize){
            MemoryCopy(srcAddr,freeP,freeSize);
            srcAddr += freeSize;
            dumpSize -= freeSize;

            //Fix Free Data Vars
            freeId++;
            freeSize = freeAddressSizes[freeId];
            freeP = freeAddress[freeId];
            goto SizeCheck;
        }else{
            MemoryCopy(srcAddr,freeP,dumpSize);
            freeP += dumpSize;
            freeSize -= dumpSize;
        }
    }
    practice.roomTimer = practice.roomTimerBackup;
    practice.stageTimer = practice.stageTimerBackup;
    ((char*)0x801c3371)[0] = practice.backPoint;
    gameMode2 = practice.backupMode2;
    practice.stateTextTimer = 0;
    ((char*)0x801b2993)[0] = practice.backupMenuFlag;
    ((char*)0x8016dc08)[0] = practice.weaponBackup;
    ((char*)0x801b299e)[0] = practice.backupDoorFlag;
    ((ushort*)0x801c3378)[0] = practice.backupRefights;
    ((char*)0x801b2992)[0] = practice.backupSwapDisable;
    *((ushort*)0x801b2988) = practice.backupWater;
    *((char*)0x801b2990) = practice.backupRushAmmo;
    *((ushort*)0x801c3352) = practice.rushFlags;
    *((ushort*)0x801c3354) = practice.rushFlags2;
    *((int*)0x801b297c) = practice.bossP;
    *((char*)0x801b298f) = practice.showRush;
    *((char*)0x801c337f) = practice.showedTxt;
    *((char*)0x801b29a0) = practice.frontDoor;
    *((char*)0x801b2949) = practice.shotCount;
    *((char*)0x801b2994) = practice.disableF;
    fadeF = practice.fade;
    fadeG = practice.fade2;
    fadeDone = practice.fadeD;
    *((int*)0x801b2980) = practice.ballP;
    MemoryCopy(0x80171c3c,0x80190040,0xDE * 0x200);
    MemoryCopy(0x801b2948,&practice.weaponCountBackup[0],12);
    MemoryCopy(0x801b1eac,&practice.weaponAmmoBackup[0],12 * 4);
}
#undef fades
#undef fadeF
#undef fadeR
#undef fadeG
#undef fadeB
#undef fadeDone
void ResetSettings(){
    practice.stateMade = false;
    practice.roomTimer = 0;
    ClearAll();
}