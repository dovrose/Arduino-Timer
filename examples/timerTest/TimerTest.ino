//test for the network lib
#include <Timer.h>


//LED pin
const uint8_t ledPin = 4;    		  // the number of the switch pin

Timer ledTimer = Timer();

/* time started for the ledPin */
void startLed(){
	if (digitalRead(ledPin)) {
		digitalWrite(ledPin, LOW); 
	}
}

/* time ended for the ledPin */
void stopLed(Timer& t){
	if (!digitalRead(ledPin)) {
		digitalWrite(ledPin, HIGH); 
	}
}

void setup(){
	Serial.begin(57600);
	Serial.println("Started");
	
	ledTimer.timerStartHandler(startLed); //set event for start time for switch
	ledTimer.timerEndHandler(stopLed); //set event for end time for switch
	
	//start the led for 2 min
	ledTimer.startTimer(2,0);
	
	Serial.println("Idel");

}

void loop(){
	ledTimer.process();

}

