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

void LedInit()
{
	IO1DIR = IO1DIR | LED0_bm | LED1_bm | LED2_bm | LED3_bm ;
	IO1SET =  LED0_bm ;
}

void LedOn(unsigned char ucLedIndeks)
{
	IO1CLR =  (LED0_bm | LED1_bm | LED2_bm | LED3_bm );
	
	switch(ucLedIndeks)
		{
		case(0):
			IO1SET = IO1SET | LED0_bm ;
			break;
		
		case(1):
			IO1SET = IO1SET | LED1_bm ;
			break;
		
		case(2):
			IO1SET = IO1SET | LED2_bm ;
			break;
		
		case(3):
			IO1SET = IO1SET | LED3_bm ;
			break;
		}
}

int main()
{
	unsigned char ucLedCounter;
	LedInit() ;
	
	while(1)
	{
		for(ucLedCounter=0; ucLedCounter <4; ucLedCounter++){
			LedOn(ucLedCounter);
			Delay(250);
		}
		
	}
}
