#include "led.h"
#include "uart.h" 
#include "servo.h"
#include "timer_interrupts.h"
#include "keyboard.h"



int main(){
	UART_InitWithInt(9600);
	LedInit();
	ServoInit(5);
	
	while(1){
		
		switch(cOdebranyZnak){
			case('1'):
				ServoGoTo(50);
				break;
			
			case('2'):
				ServoGoTo(100);
				break;
			
			case('3'):
				ServoGoTo(150);
				break;
			
			case('c'):
				ServoCallib();
				break;
			
			default:
				break;
		}
		
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
