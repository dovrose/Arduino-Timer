/* $Id$
||
|| @file 		       Timer.cpp
|| @author 		     Dov Rosenebrg              <dovrose@gmail.com>        
|| @url           
||
|| @description
|| | This is a Timer class
|| | It providea an easy way of handling timers
|| #
||
|| @license GPL v2
||
*/

#include <Arduino.h>
#include "Timer.h"

/*
|| @constructor
|| | Set the initial state of this timer
|| #
*/
Timer::Timer(){
	secInterval = 0;
	minInterval = 0;
	run = false;
	second = 0; 
	minute = 0; 
	tick = 0;
	cb_startTime = 0;
	cb_endTime = 0;
	cb_tickTime = 0;
}


void Timer::process(void)
{
	if (run){
		// move forward one second every 1000 milliseconds
		if (millis() - lastTick >= 1000) {
			lastTick = millis();
			second++;
			//Serial.print("second: ");Serial.print(second);
			//Serial.print("     minute: ");	Serial.println(minute);
			//Serial.print("     interval: ");Serial.println(interval);
		}	
		// move forward one minute every 60 seconds
		if (second > 59) {
			minute++;
			second = 0; // reset seconds to zero
		}
		if ((minute % tick == 0) && (second == 0)) {
			if (cb_tickTime) { cb_tickTime(*this); }	//fire the cb_tickTime event
		}
		
		if (intervalReached()) {
			if (cb_endTime) { cb_endTime(*this); }	//fire the cb_endTime event - the time ended
			run = false;
			second = 0;
			minute = 0;
			secInterval = 0;
			minInterval = 0;
		}

		// move forward one hour every 60 minutes
		if (minute > 59) {
			minute = 0; // reset minutes to zero
		}
		

	}
	
}

void Timer::setSecInterval(uint8_t s){
	secInterval = s;
}

void Timer::setMinInterval(uint8_t m){
	minInterval = m;
}

uint8_t Timer::getSecInterval(void){
	return secInterval;
}

uint8_t Timer::getMinInterval(void){
	return minInterval;
}

uint8_t Timer::getMinute(void){
	return minute;
}

bool Timer::intervalReached(void){
	if ((minInterval <= minute) && (secInterval <= second)){
		run = false;
		return true;
	}
	return false;
}

void Timer::startTimer(uint8_t min,uint8_t sec){
	secInterval = sec;
	minInterval = min;
	run = true;
	if (cb_startTime) { cb_startTime(*this); }	//fire the cb_startTime event - the time started
}

void Timer::startTimer(uint8_t min,uint8_t sec,uint8_t tickInterval){
	tick = tickInterval;
	secInterval = sec;
	minInterval = min;
	run = true;
	if (cb_startTime) { cb_startTime(*this); }	//fire the cb_startTime event - the time started
	if (cb_tickTime) { cb_tickTime(*this); }	//fire the cb_tickTime event
}

void Timer::changeTimer(uint8_t min,uint8_t sec){
	secInterval = sec;
	minInterval = min;
}

void Timer::stopTimer(void){
	run = false;
	second = 0;
	minute = 0;
	minInterval = 0;
	secInterval = 0;
	if (cb_endTime) { cb_endTime(*this); }	//fire the cb_endTime event - the time ended
}

void Timer::stopTick(void){
	if (cb_tickTime) { cb_tickTime(*this); }	//fire the cb_tickTime event - the time ended
}

/*
|| @description
|| | Register a handler for presses on this timer
|| #
||
|| @parameter handler The function to call when this button is pressed
*/
void Timer::timerStartHandler(timerEventHandler handler)
{
  cb_startTime = handler;
}

/*
|| @description
|| | Register a handler for presses on this timer
|| #
||
|| @parameter handler The function to call when this button is pressed
*/
void Timer::timerEndHandler(timerEventHandler handler)
{
  cb_endTime = handler;
}

/*
|| @description
|| | Register a handler for presses on this timer
|| #
||
|| @parameter handler The function to call when this button is pressed
*/
void Timer::timerTickHandler(timerEventHandler handler)
{
  cb_tickTime = handler;
}