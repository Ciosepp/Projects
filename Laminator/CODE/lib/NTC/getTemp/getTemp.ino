#include <NTC.h>
#include <Timer.h>

double R0 = 20000;
double Rh = 100000;
double B = 3950;
double VCC = 5.0000;
int ADC_PIN = A0;//14

NTC ntc(R0 ,B ,Rh ,VCC ,ADC_PIN);
Timer t;

void setup(){

	Serial.begin(9600);
	t.setClock(1000, 1);
}

bool flag =true;

void loop(){
	
	if(t.getClock() && flag){
		Serial.println( ntc.getTemperatureC() );
    flag = false;
		//Serial.println( ntc.getTemperatureK() );
	}
 if(!t.getClock() && !flag) flag= true;
 
}