#include <NTC.h>

double R0 = 20000;
double Rh = 100000;
double B = 3950;
double VCC = 5.0000;
int ADC_PIN = A0;//14

int setTempPin = A1;
float tDelta = 3.00;
float setTemp;

NTC ntc(R0 ,B ,Rh ,VCC ,ADC_PIN);

void setup(){

	pinMode(12, OUTPUT);
	pinMode(13, OUTPUT);
}
int bounceCount =0;

void loop(){
	setTemp = map(analogRead(setTempPin),0 ,1023 ,80.00, 130.00);

	if(ntc.getTemperatureC() >= setTemp + tDelta){
		digitalWrite(12, 1);
		bounceCount ++;
	}

	if(ntc.getTemperatureC() <= setTemp - tDelta){
		digitalWrite(12, 0);
	}

	if(bounceCount > 10) digitalWrite(13, 1);
}