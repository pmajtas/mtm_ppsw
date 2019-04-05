#include <LPC21xx.H>
#define LED0_bm 0x00010000
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
	IO1DIR = IO1DIR | LED3_bm ;
	IO1SET = IO1SET | LED3_bm ;
	IO1CLR = IO1CLR | LED3_bm ;
	
	while(1)
	{
		IO1SET = IO1SET | LED3_bm ;
		Delay(100) ;
		IO1CLR = IO1CLR | LED3_bm ;
		Delay(100) ;
	}
}
