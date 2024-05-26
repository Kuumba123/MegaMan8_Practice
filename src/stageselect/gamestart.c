#include <common.h>
#define introF ((char*)0x801c336c)[0]
#define lives ((char*)0x801c3370)[0]
void ClearWeapons();
void StartGame(){
    ClearWeapons();
    lives = 2;
    introF = 1;
    gameMode = 1;
}
#undef introF
#undef lives