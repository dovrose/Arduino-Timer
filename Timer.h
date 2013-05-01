/* $Id$
||
|| @file 		       Timer.h
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

#ifndef Timer_h
#define Timer_h

class Timer;
typedef void (*timerEventHandler)(Timer&);

class Timer {
	public:
  
		Timer();
		void process(void);
		void setSecInterval(uint8_t s);
		void setMinInterval(uint8_t m);
		uint8_t getSecInterval(void);
		uint8_t getMinInterval(void);
		uint8_t getMinute(void);
		bool intervalReached(void);
		void startTimer(uint8_t min,uint8_t sec);
		void startTimer(uint8_t min,uint8_t sec, uint8_t tickInterval);
		void stopTimer(void);
		void stopTick(void);
		void changeTimer(uint8_t min,uint8_t sec);
		
		void timerStartHandler(timerEventHandler handler);
		void timerEndHandler(timerEventHandler handler);
		void timerTickHandler(timerEventHandler handler);
		
	private: 
		unsigned long lastTick; // set up a local variable to hold the last time we moved forward one second
		bool run;
		uint8_t second; // declare time variables
		uint8_t minute; // declare time variables
		uint8_t secInterval;// declare time interval variables
		uint8_t minInterval;// declare time interval variables
		uint8_t tick;
		timerEventHandler  cb_startTime;
		timerEventHandler  cb_endTime;
		timerEventHandler  cb_tickTime;
};

#endif