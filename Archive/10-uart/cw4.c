#include "led.h"
#include "uart.h" 
#include "servo.h"
#include "timer_interrupts.h"


int main(){
	unsigned char ucSteps=12;
	UART_InitWithInt(9600);
	LedInit();
	ServoInit(20);
	
	while(1){
		
		switch(cOdebranyZnak){
			case('1'):
				ServoGoTo(ucSteps);
				ucSteps +=12;
				ucSteps %= 48;
				cOdebranyZnak='\0';
				break;
			
			case('c'):
				ServoCallib();
				break;
			
			default:
				break;
		}
	}
}
