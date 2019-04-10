#include "led.h"
#include "keyboard.h"


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
	KeyboardInit() ;
	LedInit() ;
	
	while(1)
	{
		switch(eKeyboardRead())
		{
			case BUTTON_1:
				LedStepRight();
				break;
			
			case BUTTON_2:
				LedStepLeft();
				break;
			
			default:
				break;
		}
		Delay(200);
	}
}
