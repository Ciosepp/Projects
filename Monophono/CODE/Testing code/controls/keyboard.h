#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

const int N =49; //n. tasti
int keyboard[N]; //array contenente gli stati di tutti i pulsanti
uint32_t voltages[N];
int R=6,r=0;
int W=9,w=0;
int n=0;
#define pressed 1
#define unpressed 0
#define debugEnable true

#include <Wire.h>
#include <Adafruit_MCP4725.h>
Adafruit_MCP4725 dac;
const int maxArpVoices= 7;


bool noteDown(int i, bool* noteScan, bool* noteTrans)

bool noteUp(int i, bool* noteScan, bool* noteTrans)

void gateRefresh();

void gateOn();

void gateOff();

void SerialDebug();

void pinModeInit();
    
void dacInit();

void muxWrite(int val, int* Pins);

void writeColumn(int index, int value);

#endif