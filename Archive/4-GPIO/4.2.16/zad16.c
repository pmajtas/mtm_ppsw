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
	IO0DIR = 0x0 ;
	IO1CLR = 0xFFFFFFFF ;
	if((IO0PIN & 0x40) == 0x40)
	{
		LedOn(0);
		return 0;
	}
	else 	//((IO0PIN & 0x40) == 0)
	{
		LedOn(1);
		return 1;
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
