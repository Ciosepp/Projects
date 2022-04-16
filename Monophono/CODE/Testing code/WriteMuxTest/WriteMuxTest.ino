#include "pin-configuration-board-v2.h"
#include <Timer.h>

Timer T;
void muxWrite(int val, int* Pins){
    /*
    for(int i= 0; i<3; i++){
        digitalWrite(Pins[i], double(val) & pow(2,i));//pow non funziona come integer
    }
    */
    digitalWrite(Pins[0], val&1);     //lsb 0000 0011 & 0000 0001 = 0000 0001 >0 ==> true
    digitalWrite(Pins[1], val&2);    //    0000 0011 & 0000 0010 = 0000 0010 >0 ==> true
    digitalWrite(Pins[2], val&4);   //msb 0000 0011 & 0000 0100 = 0000 0000 =0 ==> false
}
void setup(){
	for(int i=0; i<3; i++){
		pinMode(WRITE_MUX_ADDRESS_PINS[i], OUTPUT);
	}
	pinMode(WRITE_MUX_ENABLE_PIN, OUTPUT);
  pinMode(4, OUTPUT);//trigger O for oscilloscope
	Serial.begin(9600);
  Serial.println("hello");
	T.init(1);
	T.ckInit(1000,10);
}
bool latch =false;
int index = 0;
void loop(){
	if(!latch && T.Clock()){

		index = (index+1)%8; 
		muxWrite(index, WRITE_MUX_ADDRESS_PINS);
		latch = true; 
	}
	if(latch && !T.Clock()){
		latch = false;
	}

}