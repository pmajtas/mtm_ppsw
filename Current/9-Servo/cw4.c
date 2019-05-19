#include "led.h"
#include "keyboard.h"
#include "timer_interrupts.h"
#include "timer.h"
#include "servo.h"



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
