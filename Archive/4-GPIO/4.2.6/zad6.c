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

	
	while(1)
	{
		Delay(1000) ;
	}
}


