/* 
The following code has the purpose to test and clibrate the interaction between the hardware 
ande software side.
The HMI is via serial monitor with buadrate if 115200 
*/

#include <pin-configuration-board-v2.h>
#include <keyboard.h>

void setup(){
	Serial.begin(115200);
	SP("Monophono keyboard testing program");
	SP("Please select one the testing program:");

	SP("1 - Set DAC Vout = 1V");
	SP("2 - Read keyboard scan for 10s");
	SP("3 - Read internal clock BPM setting");
	SP("4 - Read Arpeggiator status");
	SP("5 - Read Arpeggiator mode");
	SP("6 - Read Arpeggiator octave extension");
	SP("7 - Read Arpeggiator mode");
}

String Read = "";
int selection =0;

bool scanEnable = false;
long timer1 = 0;
void loop(){
	while (Serial.available() > 0) {
		int inChar = Serial.read();
		if (isDigit(inChar)) {
		  // convert the incoming byte to a char and add it to the string:
		    Read += (char)inChar;
		}
		if (inChar == '\n') {
			selection= Read.toInt();
		    Read = "";  
		}
	}
	switch(selection){
		case(1):
			dac.setVoltage(819, false);
			SP("DAC voltage set: 1V");
			selection =0;
			break;
		case(2):
			scanEnable = true;
			timer1 = millis()+10000;
			SP("Scanning");
			selection =0;
			break;
		case(3):
			int BPM = getMode();
			SP("BPM setting: ");
			SP(String(BMP));
			selection =0;
			break;
		case(4):
			int BPM = getMode();
			SP("BPM setting: ");
			SP(String(BMP));
			selection =0;
			break;
		case(5):
			int BPM = getMode();
			SP("BPM setting: ");
			SP(String(BMP));
			selection =0;
			break; ////////////////////da finire!!!!!!!!!!!!!!!
	}
	if(millis() <= timer1){
		PrintKeyScan();
	}

}

void SP(String line){//serial printer
	Serial.print(line);
	Serial.println("");
}
