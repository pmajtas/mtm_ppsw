#include <LPC21xx.H>

#define TIMER_ENABLE_bm (1<<0)
#define TIMER_RESET_bm 0

void InitTimer0(void){
	T0TCR |= TIMER_ENABLE_bm;
}

void WaitOnTimer0(unsigned int uiTime){ 
	T0TCR |= TIMER_RESET_bm;
	 uiTime= uiTime*15;
	while(T0TC <uiTime){}
}

void InitTimer0Match0(unsigned int iDelayTime){
	T0MCR = 1;
	T0MR0 = 15*iDelayTime;
	T0TCR = TIMER_RESET_bm;
	T0TCR = TIMER_ENABLE_bm;
}

void WaitOnTimer0Match0(){
	while(T0IR!=0){}
	
}

int main(){
	int i;
	InitTimer0Match0(1000);
	WaitOnTimer0Match0();
	i++;
	i++;
	return 0;
}
