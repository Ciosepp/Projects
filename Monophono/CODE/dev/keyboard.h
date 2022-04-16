#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

const int Nkeys =49; //n. tasti
int keyboard[Nkeys]; //array contenente gli stati di tutti i pulsanti
bool oldkeyboard[Nkeys];
bool transient[Nkeys];
uint32_t voltages[Nkeys];

const short int Nkeys=49;
const short int nColumn = 9;
const short int nRow = 6;

int noteOut=0;

#define PRESSED 1
#define UNPRESSED 0
#define DEBUG_ENABLE true

#define MONO 0

#include <Wire.h>
#include <Adafruit_MCP4725.h>
Adafruit_MCP4725 dac;
const int maxArpVoices= 7;
const int nMuxAddressPins = 3;

int KeyboardMode = MONO;


#define N_ARPEGGIATOR_OCTAVES 4
int octave = 0;
#define N_ARPEGGIATOR_MODES 3

#define MIN_BPM 60
#define MAX_BPM 300
int KeyboardMode;
#define N_KEYBOARD_MODES 3
struct READ{
	int Gate;
	int Bpm;
	int KeyboardMode;
	int arpeggiatorOctaveExtension;
};

///////////////////////////initialization functions /////////

void pinModeInit();

void dacInit();

///////////////////////////input function //////////////////

bool noteDown(int i, bool* noteScan, bool* noteTrans)

bool noteUp(int i, bool* noteScan, bool* noteTrans)

int getOctave(int pin);

int getMode(int pin);

int getCkRate();

bool readRow(int index);

int keyboardScan();

bool getGate();

void readControls();

///////////////////////////output functions//////////////////

void gateOn();

void gateRefresh();

void gateOff();

void CvWrite(int note);

void muxWrite(int val, int* Pins);

void writeColumn(int index);

void monophonicControl();

void PrintKeyScan();

void SerialDebug();

#endif