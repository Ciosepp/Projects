#include "pin-configuration-board-v2.h"

int nKeys = 49;
int nCol=9; //Read
int nRow=6; //Write

int arpeggitorSetting = 0; //0- OFF, 1-HOLD, 2- LATCH
int arpeggitorMode = 0; //0- UP, 1- U/D, 2-DOWN , 3-RAND
int octaveExtension;

int clockRate = 100; //[BPM]
int clockDivision = 0;//

long tProp = 5; //us


void readControls(){

	arpeggitorSetting	= 	getArpeggiatorSetting();
	arpeggitorMode		= 	getArpeggiatorMode();
	clockRate 			= 	getClockRate();
	octaveExtension 	= 	getOctaveExtension();

}
bool *pressedKeys;
bool *changedKeys;
int *voltages;
bool initializer(){

	pressedKeys = (*bool)malloc(nKeys * sizeof(bool));
	changedKeys = (*bool)malloc(nKeys * sizeof(bool));
	voltages = cvVoltages(nKeys, 1);
	return true;
}

int keyboardScan(bool *oldArray,bool *changeArray){

	int nPressedKeys = 0;
	bool scanRead =false;
	for (int i = 0; i < nRow; i++){

		writeMatrix(i);

		for(int j=0; j < nCol; j++){

			scanRead = muxRead();
			changeArray[i * nRow + j] = oldArray[i * nRow + j] ^ scanRead;
			oldArray[i * nRow + j] = scanRead;
			array[i * nRow + j] ? nPressedKeys ++;
		}
	}
}
