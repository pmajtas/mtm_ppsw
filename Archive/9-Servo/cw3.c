#include "led.h"
#include "keyboard.h"
#include "timer_interrupts.h"
#include "timer.h"
#include <LPC21xx.H>

#define P10_bm (1<<10)

enum ServoState{CALLIB, IDLE, IN_PROGRESS};
	
	struct Servo {
		enum ServoState eState; 
		unsigned int uiCurrentPosition;
		unsigned int uiDesiredPosition;
	};
	
	struct Servo sServo;
	
/*void Delay(int iDelayMiliSeconds)
{
	int i;
	int iLimit = 12000*iDelayMiliSeconds; 
	
	for(i=0; i < iLimit ; i++)
	{
		
	}
}*/

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

	LedInit();
	KeyboardInit();

	//while(1) 
	//{
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
				if(sServo.uiCurrentPosition < sServo.uiDesiredPosition){
					LedStepLeft();
					sServo.uiCurrentPosition++; }
				else if(sServo.uiCurrentPosition > sServo.uiDesiredPosition){
					LedStepRight();
					sServo.uiCurrentPosition--;}
				else{
					sServo.eState = IDLE;}
				break;		
								
			default:
				break;
			}
		//Delay(100);
		//}
	}

void ServoInit(unsigned int uiServoFrequency){
	Timer1Interrupts_Init((1000000/uiServoFrequency), &Automat); //spytac jak szybko na plytce
	LedInit();
	DetectorInit();
}
	
void ServoCallib(void){
	sServo.eState = CALLIB;
}

void ServoGoTo(unsigned int uiPosition){
	sServo.uiDesiredPosition = uiPosition;
}

int main (){ 
	
	ServoInit(5);
	KeyboardInit();
	
	while(1){
		
		if(eKeyboardRead() == BUTTON_0){
			ServoCallib();}
		else if(eKeyboardRead() == BUTTON_1){
			ServoGoTo(12);}
		else if(eKeyboardRead() == BUTTON_2){
			ServoGoTo(24);}
		else if(eKeyboardRead() == BUTTON_3){
			ServoGoTo(36);}
	}
}
