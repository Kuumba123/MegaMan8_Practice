#include <common.h>

void ExitCheck(u_char * puaseP){
    if((buttonsPressed & 0x840) == 0){
        return;
    }
    ((char*)0x801b2995)[0] = 1; //Stage Clear flag

    puaseP[2] = 0;
    puaseP[3] = 0;
    puaseP[1] = puaseP[1] + 1;
}