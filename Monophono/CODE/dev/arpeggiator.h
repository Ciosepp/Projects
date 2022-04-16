#include "pin-configuration-board-v2.h"
#include "keyboard.h"

#define HOLD 0
#define LATCH 1 

int arpeggiatorMode;
int arpeggiatorOctaveExtension;


void arpeggiatorRecord(int nPressedKeys);