#include <Servo.h>

int dirPin =12;
int stepPin =11;
int servoPin = 10;

int buttonPin =9;

double stepPermm =100.000;
double currentPosition =0;

int guageAngle = 45;
int cuttingAngle = 90;

void moveByLength(double length, double stpPmm){

	int steps = length * stpPmm;
	for(int i=0; i<steps; i++){

		digitalWrite(stepPin,1);
		delay(1);
		digitalWrite(stepPin,0);
		delay(5);
	}
}


void setup(){

	pinMode(12,OUTPUT);
	pinMode(11,OUTPUT);
	pinMode(10,OUTPUT);
	pinMode(9,INPUT_PULLUP);
	Serial.begin(9600);
	Serial.print("Wire cutter v1.0 \n");

}

void loop(){

}