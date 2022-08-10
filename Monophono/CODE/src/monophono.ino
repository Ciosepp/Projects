/*
///	///	///	///	///	MONOPHONO KEYBOARD FIRMWARE	///	///	///	///	///

This code will be compatible with 2.5 and 3.0 boards 

Final writting begins on june 20 2022 by gAz

files:
	Framework
		monophono.ino	= 	main file
		functions.ino	=	software functions file
		hwFunctions.ino =	hardware controlling functions - may differ in different boards designs
	
	Features
		keyboard.ino 	=	all code to run simple monophonic keyboard
		arpeggiator.ino = 	code for the arpeggiator 

*/
void setup(){
    Serial.begin(115200);
    Serial.print("Mono keyboard firmware 2.0 rev.C");
	Init();
}


void loop(){

}