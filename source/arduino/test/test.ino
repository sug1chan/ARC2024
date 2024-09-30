#include "operate.h"

void setup() {
    init_pinMode();
}

void loop() {
    opr op[] = {
        CTPL_FWRD,
        CTPL_RTRN,
        CTPL_LTRN,
        CTPL_BKWD,
    };
    
    for(int i = 0; i < 4; i++) {
        contrl_catepillar(op[i]);
        delay(500);
        contrl_catepillar(CTPL_REST);
        delay(500);
    }
}

