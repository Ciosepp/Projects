#include "pin-configuration-board-v2.h"

int getArpeggiatorSetting(){

	return map(analogRead(ARPEGGIATOR_MODE_PIN),
	 0,1023,
	 0,2 );
}
int getArpeggiatorMode(){

	return map(analogRead(ARPEGGIATOR_MODE_PIN),
	 0,1023,
	 0,3 );
}

int getOctaveExtension(){

	return map(analogRead(ARPEGGIATOR_MODE_PIN),
	 0,1023,
	 0,3 );
}


#define minBPM 60
#define maxBPM 300

int getClockRate(){

	return map(analogRead(ARPEGGIATOR_MODE_PIN),0,1023,minBPM,maxBPM);
}

void muxWrite(int n, int *addrPins){

	for(int i=0 ; i<3 ; i++){
		digitalWrite(pins[i], (n>>i) && 1);
	}
}
bool muxRead(){
	
	return digitalRead(READ_MUX_OUT_VALUE_PIN);
}

void writeMatrix(int n, int extWritepin, int EN){
	
	if(n < nRow -1){		
		digitalWrite(MATRIX_WRITE_EXTERNAL_PIN,0);
		digitalWrite(WRITE_MUX_ENABLE_PIN,0);
	} 
	else{
		digitalWrite(MATRIX_WRITE_EXTERNAL_PIN,1);
		digitalWrite(WRITE_MUX_ENABLE_PIN,1);
	}
	muxWrite(n, WRITE_MUX_ADDRESS_PINS);
}

bool readMatrix(int n, int *addrPins, int ReadPin){
	
	muxWrite(j, READ_MUX_ADDRESS_PINS);
	return digitalRead(READ_MUX_OUT_VALUE_PIN);
}

bool noteDown(int key){
	cvWrite(voltages[key]);
	gateRefresh();
}
bool noteUp(int key){
	gateOff();
}

void gateOn(){
	digitalWrite(GATE_PIN,1);
}
void gateOff(){
	digitalWrite(GATE_PIN,0);
}
void gateRefresh(){
	gateOff();
	delay(1);
	gateOn();
}

//////////////////////genera i valori di cv/////////////////////////////////////////
int* cvVoltages(int N, int vOct){       //da chiamre solo una volta se no esplode fortissimo

	int* cvArray= (int*)malloc(N* sizeof(int));
	int k = 1000*vOct/12;

	for(int i=0; i<N; i++){
		cvArray[i]= i*k;
	}
	return cvArray;
}

void cvWrite(int cv_mV){

	uint32_t dacVal = 4096/5000*cv_mV;
	dac.setVoltage(dacVal,false);
}