/*
	NTC library meant to return C deg value .
	Written by G. Balducci, April 15, 2022.
	Released into the public domain.
	Version 1.0
*/

#ifndef NTC_h
#define NTC_h

#include "Arduino.h"

class NTC{

public:
	NTC(double _R0, double _B, double _Rh, double _VCC, int adcPin);
	~NTC();

	double getTemperatureC();
	double getTemperatureK();

private:
	const double  T0 = 298.1500;

	double	R0, B ,Rh ,VCC;

	double Rt, Vr, ln, Tx, Vrt;

	int pin;

};
#endif