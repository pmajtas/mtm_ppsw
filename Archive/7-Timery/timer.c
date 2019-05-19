#include <LPC21xx.H>
#include "timer.h"

#define TIMER_ENABLE_bm (1<<0)
#define TIMER_RESET_bm 0

void InitTimer0(void){
	T0TCR |= TIMER_ENABLE_bm; //pozwolenie timera na zlizcanie
}

void WaitOnTimer0(unsigned int uiTime){ 
	T0TCR |= TIMER_RESET_bm; // reset timera
	 uiTime= uiTime*15; //ustawienie ilosci zliczanych impulsow
	while(T0TC < uiTime){}	//porownanie, czekanie do osiagniecia wartosci
	T0TC=0;
}

void InitTimer0Match0(unsigned int iDelayTime){
	T0MCR = 1; //ustawienie przerwania 
	T0MR0 = 15*iDelayTime;	//ustawienie ilosci zliczanych impulsow
	T0TCR = TIMER_RESET_bm; //reset timera
	T0TCR = TIMER_ENABLE_bm; //start timera
}

void WaitOnTimer0Match0(void){
	while(T0TC <  T0MR0){ //porownanie z wartoscia w MR0
	}
	T0IR = 1;	//wyzerowanie flagi przerwania	
	T0TC=0;
}


