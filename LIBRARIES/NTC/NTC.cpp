#include "Arduino.h"
#include "NTC.h"

NTC::NTC(double _R0, double _B, double _Rh, double _VCC, int adcPin){
	R0  =  _R0;
	B   =   _B;
	Rh  =  _Rh;
	VCC = _VCC;
	pin = adcPin;
}
NTC::~NTC(){}

double NTC::getTemperatureK(){
	Vr = (5.0000 / 1023.0000)*analogRead(A0); 

	Rt = Rh / ((VCC/Vr)-1);

	ln = log(Rt/R0);

	Tx = 1/( (ln / B) + (1/T0));

	return Tx;
}

double NTC::getTemperatureC(){

	return NTC::getTemperatureK()-273.15;
}