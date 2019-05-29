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

enum DetectorState Result, Button1,Button2,Button3,Button4;
int main (){ 
	
	unsigned int iMainLoopCtr;
	DetectorInit();
	LedInit();
	KeyboardInit();
	Timer1Interrupts_Init(200000, &Automat);
	
	while(1){
	 	iMainLoopCtr++;
		if(eKeyboardRead() == BUTTON_0){
			sServo.eState = CALLIB;}
		else if(eKeyboardRead() == BUTTON_1){
			sServo.uiDesiredPosition=12;}
		else if(eKeyboardRead() == BUTTON_2){
			sServo.uiDesiredPosition=24;}
		else if(eKeyboardRead() == BUTTON_3){
			sServo.uiDesiredPosition=36;}
	}
}
