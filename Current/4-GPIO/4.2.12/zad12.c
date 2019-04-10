#include <LPC21xx.H>
#define LED0_bm 0x00010000
#define LED1_bm 0x00020000
#define LED2_bm 0x00040000
#define LED3_bm 0x00080000

void Delay(int iDelayMiliSeconds)
{
	int i;
	int iLimit = 12000*iDelayMiliSeconds; 
	
	for(i=0; i < iLimit ; i++)
	{
		
	}
}

int main()
{
	unsigned char ucLedCounter;
	IO1DIR = IO1DIR | LED0_bm | LED1_bm | LED2_bm | LED3_bm ;
	
	while(1)
	{
		for(ucLedCounter=0; ucLedCounter <4; ucLedCounter++){
			IO1SET = LED0_bm << (ucLedCounter);
			IO1CLR = LED0_bm << (ucLedCounter+3)%4;
			Delay(250);
		}
	}
}
