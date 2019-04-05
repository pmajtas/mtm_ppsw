#include <LPC21xx.H> 

#define LED0_bm 0x00010000
#define LED1_bm 0x00020000
#define LED2_bm 0x00040000
#define LED3_bm 0x00080000
#define LED7_bm 0x00800000


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
	IO1DIR = IO1DIR | LED0_bm | LED1_bm | LED2_bm | LED3_bm | LED7_bm ;
	IO1SET = IO1SET | LED0_bm | LED7_bm ;
}


void LedOn(unsigned char ucLedIndeks)
{
	if(ucLedIndeks == 0)
	{
		IO1SET = IO1SET | LED0_bm ;
	}
	else if(ucLedIndeks == 1)
	{
		IO1SET = IO1SET | LED1_bm ;
	}
	else if(ucLedIndeks == 2)
	{
		IO1SET = IO1SET | LED2_bm ;
	}
	else if(ucLedIndeks == 3)
	{
		IO1SET = IO1SET | LED3_bm ;
	}
}

int ReadButton1()
{ 
	
	char cLedNumber ;
	
	enum ButtonState{RELEASED=0, PRESSED=1} ;

	IO0DIR = 0x0 ;
	IO1CLR = 0xFFFFFFFF ;

	cLedNumber = IO0PIN & 0x40 ;
	switch(cLedNumber)
	{
		case 0x40:
			LedOn(RELEASED);
			return RELEASED;
		
		case 0:
			LedOn(PRESSED);
			return PRESSED ;
		
		default: 
			return 0;
	}
	
}

int main()
{
	LedInit() ;
	Delay(1000);
	
	while(1)
	{
		ReadButton1();
	}
}
