#include <LPC21xx.H>
#include "servo.h"
#include "led.h"
#include "timer_interrupts.h"

#define P10_bm (1<<10)

enum ServoState{CALLIB,IDLE, IN_PROGRESS};
	
	struct Servo {
		enum ServoState eState; 
		unsigned int uiCurrentPosition;
		unsigned int uiDesiredPosition;
	};
	
	struct Servo sServo;
	

void DetectorInit(void){
	IO0DIR = IO0DIR & ~(P10_bm);
}

enum DetectorState{INACTIVE, ACTIVE} eReadDetector(void){
	if((IO0PIN & P10_bm) == 0){
		return ACTIVE;
	}
	return INACTIVE;
}

void Automat(void){


		switch(sServo.eState){
			
			case CALLIB:
				if(eReadDetector() != ACTIVE){
					sServo.eState = CALLIB;
					LedStepRight();}
				else{
					sServo.eState = IDLE;}
				break;
					
			case IDLE :
				if(sServo.uiCurrentPosition != sServo.uiDesiredPosition){
					sServo.eState = IN_PROGRESS;}
				else{
					sServo.eState = IDLE;}
				break;
			
			case IN_PROGRESS :
				if(sServo.uiCurrentPosition != sServo.uiDesiredPosition){
					LedStepLeft();
					sServo.uiCurrentPosition++;
					sServo.uiCurrentPosition%=48;}
					
				else{
					sServo.eState = IDLE;
					sServo.uiCurrentPosition=0;}
				break;		
								
			default:
				break;
			}
	}

void ServoInit(unsigned int uiServoFrequency){
	Timer1Interrupts_Init((1000000/uiServoFrequency), &Automat); //spytac jak szybko na plytce
	LedInit();
	DetectorInit();
	ServoCallib();
}
	
void ServoCallib(void){
	sServo.eState = CALLIB;
}

void ServoGoTo(unsigned int uiPosition){
	
	sServo.uiDesiredPosition = uiPosition;
	sServo.eState = IN_PROGRESS;
	while(sServo.eState!=IDLE){}
}
	
	
	
