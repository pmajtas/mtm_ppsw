#include <LPC21xx.H>

void Delay(int iDelayMiliSeconds)
{
	int i=0;
	int iLimit = 12000*iDelayMiliSeconds; 
	
	for(i=0; i < iLimit ; i++)
	{
		
	}
}

int main()
{
	IO1DIR = 1 ;
	IO1SET = 0x00010000 ;
	IO1CLR = 0x00010000 ;
	
	while(1)
	{
		IO1SET = 0x00010000 ;
		Delay(1000) ;
		IO1CLR = 0x00010000 ;
		Delay(1000) ;
	}
}


