/*
	8 STEPS SEQUENCER ARDUINO PRO-MINI FIRMWARE V1.0

	LAST REVIEW 8/30/2022
	INPUTS:
		CV: 		A0
		CLK AMT:	A1
		CLOCK IN:	A2
		ENABLE:		A3

	OUTPUTS:

		CV:					I2C(DAC)
		GATE:				D2
		DRIVE BUS:			D3-> D10
		MULTIPLEXER ADDR:	D11->D13


*/
#include <Timer.h>
Timer t(MILLIS);

int drivePins[8]={

};
/////////////////////////////////
void pinInit(){
	
	pinMode();
}
////////////////////////////////
short ckAmtPin = A1;
#define minBPM 60
#define maxBPM 300

int getBpmAmt(){
	return map(analogRead(ckAmtPin),0,1023, minBPM, maxBPM);
}
int oldBpmVal=0;
void updateClock(){

	int val=getBpmAmt();
	if(val != oldBpmVal){

		t.setClock(60000/val ,50);
		oldBpmVal = val;
	}
}

short ckInPin = A2;
bool getInClock(){
	return digitalRead(A2);
}

void setup(){

	pinInit();
}

void loop(){

}

