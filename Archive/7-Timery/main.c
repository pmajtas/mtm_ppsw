#include "timer.h"
#include "led.h"

int main(){
	LedInit();
	InitTimer0Match0(1000000);
	
	while(1){
		WaitOnTimer0Match0();
		LedStepRight();
	}
}
