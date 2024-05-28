#ifndef PRACTICE_H
#define PRACTICE_H
#include <sys/types.h>
#include <stdbool.h>
typedef struct {
    int bossTimer;
    int roomTimer;
    int stageTimer;
    int roomTimerBackup;
    int stageTimerBackup;
    int weaponAmmoBackup[12];
    int bossP;
    int ballP;
    u_char weaponCountBackup[12];
    ushort fade;
    ushort fade2;
    ushort backupRefights;
    ushort rushFlags;
    ushort rushFlags2;
    ushort backupWater;
    u_char weaponBackup;
    u_char backupDoorFlag;
    u_char backupMode2;
    u_char backPoint;
    u_char backupRushAmmo;
    u_char fadeD;
    u_char disableF;
    bool showRush;
    bool backupSwapDisable;
    bool backupMenuFlag; //Pause Menu Disabled
    bool showedTxt;
    u_char frontDoor;
    u_char shotCount;
    bool showStageTimer;
    bool stateMade;
    u_char stateTextTimer;
} Practice;
typedef struct
{
    DR_TPAGE dr;
    TILE tileRect;
} FadeStruct;
extern Practice practice;
#define backupSpawnData ((u_char*)0x1f800300) //end of cache

#endif