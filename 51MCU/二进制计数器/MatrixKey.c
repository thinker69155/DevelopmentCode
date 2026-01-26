#include <REGX52.H>
#include "delay.h"
unsigned char MatrixKey()
{
    unsigned char KeyNumber = 0;
    
    // ?1???(??P3_4,?????)
    P3 = 0xff;       // ??????
    P3_4 = 0;        // ???1?
    if (P3_0 == 0) { delay(20); while(P3_0==0); delay(20); KeyNumber=6; }
    if (P3_1 == 0) { delay(20); while(P3_1==0); delay(20); KeyNumber=10; }
    if (P3_2 == 0) { delay(20); while(P3_2==0); delay(20); KeyNumber=14; }
    if (P3_3 == 0) { delay(20); while(P3_3==0); delay(20); KeyNumber=18; }
    
    // ?2???(??P3_5,?????)
    P3 = 0xff;
    P3_5 = 0;        // ???2?
    if (P3_0 == 0) { delay(20); while(P3_0==0); delay(20); KeyNumber=7; }
    if (P3_1 == 0) { delay(20); while(P3_1==0); delay(20); KeyNumber=11; }
    if (P3_2 == 0) { delay(20); while(P3_2==0); delay(20); KeyNumber=15; }
    if (P3_3 == 0) { delay(20); while(P3_3==0); delay(20); KeyNumber=19; }
    
    // ?3???(??P3_6,?????)
    P3 = 0xff;
    P3_6 = 0;        // ???3?
    if (P3_0 == 0) { delay(20); while(P3_0==0); delay(20); KeyNumber=8; }
    if (P3_1 == 0) { delay(20); while(P3_1==0); delay(20); KeyNumber=12; }
    if (P3_2 == 0) { delay(20); while(P3_2==0); delay(20); KeyNumber=16; }
    if (P3_3 == 0) { delay(20); while(P3_3==0); delay(20); KeyNumber=20; }
    
    // ?4???(??P3_7,?????)
    P3 = 0xff;
    P3_7 = 0;        // ???4?
    if (P3_0 == 0) { delay(20); while(P3_0==0); delay(20); KeyNumber=9; }
    if (P3_1 == 0) { delay(20); while(P3_1==0); delay(20); KeyNumber=13; }
    if (P3_2 == 0) { delay(20); while(P3_2==0); delay(20); KeyNumber=17; }
    if (P3_3 == 0) { delay(20); while(P3_3==0); delay(20); KeyNumber=21; }
    
    return KeyNumber;
}