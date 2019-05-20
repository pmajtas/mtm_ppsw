#include "led.h"
#include "uart.h" 
#include "servo.h"
#include "timer_interrupts.h"


int main(){
	UART_InitWithInt(9600);
	LedInit();
	ServoInit(5);
	
	while(1){
		
		switch(cOdebranyZnak){
			case('1'):
				ServoGoTo(50);
				break;
			
			case('c'):
				ServoCallib();
				break;
			
			default:
				break;
		}
	}
}
