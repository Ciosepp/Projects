// MonoV2.ino
// main file
/*
        
*/
#include "pin-configuration-board-v2_5.h"
#include "keyboard.h"
#include "arpeggiator.h"

void setup(){
    pinModeInit(); 
    Serial.begin(115200);
    Serial.print("Mono keyboard firmware 2.0 rev.C");

    // for (int i = 0; i < N; i++) {
    //     oldkeyboard[i] = 0;
    // }

    // dacInit();
}

int pressedKeys = 0;

void loop(){
    // lettura controlli tastiera
    readControls();

    // lettura tastiera

    pressedKeys = keyboardScan();

    if (KeyboardMode == MONO) {
        monophonicControl();
    }

    if (KeyboardMode != MONO) {
        arpeggiatorOldState = arpeggiatorMain(statoControlli,
                                              statoTastiera,
                                              arpeggiatorOldState);
    }

    // output controlli (led, schermi, etc)


    // roba di Giuseppe
    //int oldnote = 0;
    // n = mono(oldnote);
    // oldnote = n;
    // if (debugEnable) {
    //     SerialDebug();
    // }
}



