#include "led.h"
#include "keyboard.h"
#include "timer_interrupts.h"
#include "timer.h"
#include <LPC21xx.H>

#define P10_bm (1<<10)

void Delay(int iDelayMiliSeconds)
{
	int i;
	int iLimit = 12000*iDelayMiliSeconds; 
	
	for(i=0; i < iLimit ; i++)
	{
		
	}
}

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
	unsigned char ucLedStepCounter=1;

	enum LedState{STAND_STILL, LED_RIGHT,LED_LEFT,LED_RIGHT_STEPS, CALLIB};
	enum LedState eLedState = CALLIB; 

	LedInit();
	KeyboardInit();

	while(1) 
	{
		switch(eLedState){
			
			case STAND_STILL:
				if(eKeyboardRead()==BUTTON_0){
					eLedState= LED_LEFT;}
				else if(eKeyboardRead()==BUTTON_2){
					eLedState = LED_RIGHT;}
				else{
					eLedState = STAND_STILL;}
				break;
					
			case LED_LEFT :
				if(eKeyboardRead()==BUTTON_1){
					eLedState = STAND_STILL;}
				else{
					LedStepLeft();
					eLedState = LED_LEFT;}
				break;
			
			case LED_RIGHT :
				if(eKeyboardRead()==BUTTON_1){
					eLedState=STAND_STILL;}
				else if(eKeyboardRead()==BUTTON_0){
					eLedState= LED_RIGHT_STEPS ;}
				else{
					LedStepRight();
					eLedState=LED_RIGHT;}
				break;
					
			case LED_RIGHT_STEPS:
				if(ucLedStepCounter ==10){
					ucLedStepCounter=0;
					LedStepLeft();
					eLedState = LED_LEFT;}
				else{
					LedStepRight();
					ucLedStepCounter=ucLedStepCounter+1;
					eLedState = LED_RIGHT_STEPS;}
			break;
					
				case CALLIB:
					if(eReadDetector()==INACTIVE){
						LedStepRight();}
					else{
						eLedState= STAND_STILL;}
						break;			
								
			default:
				break;
		}
		Delay(100);
	}
}

enum DetectorState Result;
int main (){ 
	
	unsigned int iMainLoopCtr;
	DetectorInit();
	LedInit();
	Timer1Interrupts_Init(20000, &Automat);
	
	while(1){
	 	iMainLoopCtr++;
	}
}
