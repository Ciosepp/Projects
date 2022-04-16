#include "pin-configuration-board-v2_5.h"
#include "arpeggiator.h"

bool noteDown(int i, bool* noteScan, bool* noteTrans){
    return noteScan[i] && noteTrans[i];
}

bool noteUp(int i, bool* noteScan, bool* noteTrans){
    return noteScan[i] && !noteTrans[i];
}

void gateRefresh(){
    digitalWrite(gatePin, 0);
    digitalWrite(gatePin, 1);
}

void gateOn(){
    digitalWrite(gatePin, 1);
}

void gateOff(){
    digitalWrite(gatePin, 0);
}

void SerialDebug(int N, int* Vector){
    for (int i = 0; i < N; i++){
		Serial.print(Vector[i]);
	}
 	Serial.println("");
}
void PrintKeyScan(){
    for (int i = 0; i < N; i++){
		Serial.print( keyboard[i]);
	}
 	Serial.println("");
}

void pinModeInit(){
	
    for(int i = 0; i < nMuxAddressPins; i++){
        pinMode(ReadMuxAddressPin[i], OUTPUT);
        pinMode(WriteMuxAddressPin[i], OUTPUT);
    }
    pinMode(WriteMuxOutPin, OUTPUT);
    pinMode(ReadMuxInPin, INPUT);
    pinMode(gatePin, OUTPUT);
}

void dacInit(){    //funzione che genera le tensioni specifiche per ogni tasto
	dac.begin(DAC_ADDRES);
	dac.setVoltage(0, false);
	
  	for (uint32_t i = 0; i < 60; i++){
    	voltages[i] = i * 4095 / 60;
  	}  	
}

void muxWrite(int val, int* Pins){
    uint8_t out = val;
    for(int i= 0; i<nMuxAddressPins; i++){

        digitalWrite(Pins[i], out & pow(2,i));    //lsb 0000 0011 & 0000 0001 = 0000 0001 >0 ==> true
    }
    //digitalWrite(Pins[1], out&2);    //    0000 0011 & 0000 0010 = 0000 0010 >0 ==> true
    //digitalWrite(Pins[2], out&4);   //msb 0000 0011 & 0000 0100 = 0000 0000 =0 ==> false
}



void WriteColumn(int index){
    if(index >= 0 && index <=7){
		if (index ==0) {
		    digitalWrite(WRITE_MUX_ENABLE_PIN, 1);
		    digitalWrite(MATRIX_WRITE_EXTERNAL_PIN, 0);
		}
    	muxWrite(WRITE_REROUTING_ARRAY[index], WRITE_MUX_ADDRESS_PINS);
    }else{
    	digitalWrite(WRITE_MUX_ENABLE_PIN, 0);
	    digitalWrite(MATRIX_WRITE_EXTERNAL_PIN, 1);
    }
}



bool readRow(int index){
	muxWrite(READ_REROUTING_ARRAY[index], READ_MUX_ADDRESS_PINS);
	return digitalRead(READ_MUX_OUT_VALUE_PIN);
}

int getOctave(int pin){
    return map(analogRead(pin), 0, 1023, 0, N_ARPEGGIATOR_OCTAVES-1);
}

int getArpeggiatorMode(int pin){
    return map(analogRead(pin), 0, 1023, 0, N_ARPEGGIATOR_MODES-1);
}

int getKeyboardMode(int pin){
    return map(analogRead(pin), 0, 1023, 0, N_KEYBOARD_MODES-1);
}

int getCkRate(){
    return map(analogRead(ARPEGGIATOR_CLOCK_RATE_PIN), 0, 1023, MIN_BPM, MAX_BPM);
}

bool getGate(){
	return digitalRead(ARPEGGIATOR_CLOCK_IN_PIN);
}

void readControls(){
	READ.Gate = getGate();
	READ.Bpm = getCkRate();
	READ.KeyboardMode = getKeyboardMode();
	READ.arpeggiatorMode = getArpeggiatorMode();
	READ.arpeggiatorOctaveExtension = getOctave();

}

int keyboardScan(){

    int columnIndex=0;
    int rowIndex=0;
    int nPressedKeys=0;

    for(int i=0; i<Nkeys; i++){

        columnIndex= i / nColumn;
        rowIndex = i % nRow;

        WriteColumn(columnIndex);
        keyboard[i] = readRow(rowIndex);
        if( keyboard[i])nPressedKeys++;

        transient[i] = oldkeyboard[i] ^ keyboard[i]; //XOR
        oldkeyboard[i] = keyboard[i]; //updating memory vector
    }
    return nPressedKeys;
}

void CvWrite(int note){
	dac.setVoltage(voltages[note], false);
}
void monophonicControl(){
	
	int nPressedKeys = 0;

  	for(int i = 0; i < N; i++){

       	if (noteDown(i, keyboard, transient)){  //detect note down
       		noteOut = i;
       		CvWrite(i);
       		gateRefresh();
            nPressedKeys++;
       		break;
       	}

       	if (noteUp(i, keyboard, transient)){ //detect note release
      		
            nPressedKeys--;
			if (nPressedKeys==0){  //only pressed key release handler
			    gateOff();
			}else{    //release handler selects the first secondly pressed key 
			    noteOut = i;
			    CvWrite(i);
			    gateRefresh();
			}
			
			break;
       	}
    }
  	
}


int noteIndex=0;
void arpeggiator(int* notes, int nNotes, int octaveExtension, int mode){

	if (getGate() && aLatch && nNotes > 0){

		CvWrite(notes[noteIndex]);
       	gateRefresh();
       	aLatch = false;
	}

	if (!getGate() && !aLatch){ 
		switch(mode){
			case 0:	//up mode 
                noteIndex = (noteIndex + 1) % maxArpVoices;
                break;
            case 1:  // up/down mode
                if (noteIndex >= maxArpVoices - 1 && up) up = false; //up
                if (noteIndex <= 0 && !up) up = true;
                if (up) noteIndex++;
                else    
                    noteIndex--;
                break;
            case 2: // down mode
                noteIndex = (noteIndex - 1) % maxArpVoices;
                break;
		}
        aLatch = true;
	}
}