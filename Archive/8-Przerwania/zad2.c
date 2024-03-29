#include <LPC21xx.H>
#include "led.h"

// TIMER
#define mCOUNTER_ENABLE 0x00000001
#define mCOUNTER_RESET  0x00000002

// CompareMatch
#define mINTERRUPT_ON_MR0 0x00000001
#define mRESET_ON_MR0     0x00000002
#define mMR0_INTERRUPT    0x00000001

// VIC (Vector Interrupt Controller) VICIntEnable
#define VIC_TIMER0_CHANNEL_NR 4

// VICVectCntlx Vector Control Registers
#define mIRQ_SLOT_ENABLE 0x00000020

/**********************************************/
//(Interrupt Service Routine) of Timer 1 interrupt
__irq void Timer0IRQHandler(){

	T0IR=mMR0_INTERRUPT; 	// skasowanie flagi przerwania 
	LedStepRight();		// cos do roboty
	VICVectAddr=0x00; 	// potwierdzenie wykonania procedury obslugi przerwania
}
/**********************************************/
void Timer0Interrupts_Init(unsigned int uiPeriod){ // microseconds

        // interrupts //VICIntEnable odblokowywuje przerwania z danych kanalow
											//VICVectCntlx nadanie adresu kanalu, z ktorego bedzie przerwanie, nadaje priorytet przerwaniom z kanalow
											//VICVectAddrx adres obslugi przerwania (adres pierwszego rozkazu programu do obslugi przerwania).

	VICIntEnable |= (0x1 << VIC_TIMER0_CHANNEL_NR);            // Enable Timer 0 interrupt channel 
	VICVectCntl0  = mIRQ_SLOT_ENABLE | VIC_TIMER0_CHANNEL_NR;  // Enable Slot 0 and assign it to Timer 0 interrupt channel //0 to najwyzszy priorytet
	VICVectAddr0 = (unsigned long) Timer0IRQHandler; 	   // Set to Slot 0 Address of Interrupt Service Routine 

        // match module

	T0MR0 = 15 * uiPeriod;                 	      // value 
	T0MCR |= (mINTERRUPT_ON_MR0 | mRESET_ON_MR0); // action 

        // timer

	T0TCR |=  mCOUNTER_ENABLE; // start 

}
/**********************************************/
int main (){
	unsigned int iMainLoopCtr;
	Timer0Interrupts_Init(250000);

	while(1){
	 	iMainLoopCtr++;
	}
}
