#include <REGX52.H>
#include "delay.h"
unsigned char Key(void) {
    unsigned char Keynumber = 0;  // ???0(???)
    
    // ??P3_0??(????1)
    if(P3_0 == 0) {               // ????(???)
        delay(20);                // ??
        if(P3_0 == 0) {           // ????
            Keynumber = 1;
            // ??:??????,??????????
            while(P3_0 == 0);     // ????
            delay(20);            // ???????
        }
    }
    // ??P3_1??(????2)
    else if(P3_1 == 0) {          // ?else if????????????
        delay(20);
        if(P3_1 == 0) {
            Keynumber = 2;
            while(P3_1 == 0);
            delay(20);
        }
    }
    // ??P3_2??(????3)
    else if(P3_2 == 0) {
        delay(20);
        if(P3_2 == 0) {
            Keynumber = 3;
            while(P3_2 == 0);
            delay(20);
        }
    }
    // ??P3_3??(????4)
    else if(P3_3 == 0) {
        delay(20);
        if(P3_3 == 0) {
            Keynumber = 4;
            while(P3_3 == 0);
            delay(20);
        }
    }
    
    return Keynumber;
}