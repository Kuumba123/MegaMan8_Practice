#include <sys/types.h>
#include <common.h>
#include <gpu.h>
#include "../practice.h"
#define fadeF *((u_char*)0x801b299a)
#define fadeDone *((u_char*)0x8016ca90)
#define fadeR *((u_char*)0x801b299b)
#define fadeG *((u_char*)0x801b299c)
#define fadeB *((u_char*)0x801b299d)
FadeStruct extern fades[2];

void FadeEffect(){
    if(fadeF != 0 && fadeDone != 0){

        /*Define Texpage Command*/
        fades[buffer].dr.tag = (((int)&fades[buffer].tileRect) & 0xFFFFFF) + 0x01000000;

        u_char colorR;
        u_char colorG;
        u_char colorB;
        if(fadeR < 0x80){
            fades[buffer].dr.code[0] = 0xE1000045;
            colorR = (fadeR ^ 0xFF) << 1;
            colorG = (fadeG ^ 0xFF) << 1;
            colorB = (fadeB ^ 0xFF) << 1;
        }else{
            fades[buffer].dr.code[0] = 0xE1000025;
            colorR = (fadeR << 1);
            colorG = (fadeG << 1);
            colorB = (fadeB << 1);
        }
        setRGB0(&fades[buffer].tileRect,colorR,colorG,colorB);
        fades[buffer].tileRect.x0 = 0;
        fades[buffer].tileRect.y0 = 0;
        fades[buffer].tileRect.w = 320;
        fades[buffer].tileRect.h = 240;

        //Setup RECT Command
        SetTile(&fades[buffer].tileRect);
        fades[buffer].tileRect.code = 0x62;
        /*Use OT-8*/
        AddPrims(&drawP->ot[8],&fades[buffer].dr,&fades[buffer].tileRect);
    }
}
#undef fades
#undef fadeF
#undef fadeR
#undef fadeG
#undef fadeB
#undef fadeDone