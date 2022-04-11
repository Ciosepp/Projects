#include <Timer.h>
//Timer t(MICROS);
Timer t0; //Timer t(MILLIS), both equivalent
Timer t1;
void setup(){

	pinMode(13,OUTPUT);
 
	t0.setClock(2000, 50);//initialize clock0 @2000ms period 50% dc
    t1.setClock(100, 20);//initialize clock1 @100ms period 20% dc
  
	digitalWrite(13, 1);//led on

	t0.setDelayTime(2000); // start 2s timer

	while(!t0.getDelayQ()){}
		
	digitalWrite(13, 0);

}

void loop(){

	digitalWrite(13, t0.getClock() && t1.getClock());
}