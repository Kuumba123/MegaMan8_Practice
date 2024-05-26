#include <common.h>
#define var ((char*)0x801d1848)[0]
void PrintTitle(){
    FntPrint("\n\n\n\n\n\n\n\n\n\n\t Practice Hack 1.1");
    FntPrint("\n\n\n\n\n\n\n\n\n\n\n\nMade by Pogchampguy AKA Kuumba");
}
void PrintTitleCheck(){
    void (*resetObjDisp)() = 0x80104c04;
    (*resetObjDisp)();

    if(gameMode == 1 && gameMode2 == 2){
        PrintTitle();
    }else if(gameMode == 1 && gameMode2 == 1 && var == 3){
        PrintTitle();
    }

}
#undef var