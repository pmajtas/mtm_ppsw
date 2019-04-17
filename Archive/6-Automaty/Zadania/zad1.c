#include <LPC21xx.H> 

#define LED0_bm (1<<16) 
#define LED1_bm (1<<17)
#define LED2_bm (1<<18)
#define LED3_bm (1<<19)

#define S0_bm (1<<5)
#define S1_bm (1<<7)
#define S2_bm (1<<6)
#define S3_bm (1<<8)

typedef enum eDirections{Left,Right} eDirections;

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
	IO1DIR = LED0_bm | LED1_bm | LED2_bm | LED3_bm  ;
	IO1SET = LED0_bm  ;
}


void LedOn(unsigned char ucLedIndeks)
{
	IO1CLR = (LED0_bm | LED1_bm | LED2_bm | LED3_bm );
	
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

void LedStep(enum eDirections eDirection)
{
	static unsigned char ucLedPoint=0;
	
	if(eDirection==0)
	{
		ucLedPoint++;
		LedOn(ucLedPoint%4);
	}
	else if(eDirection==1)
	{
		ucLedPoint--;
		LedOn(ucLedPoint%4);
	}
}

void LedStepLeft(void)
{	
	LedStep(Left);
}

void LedStepRight(void)
{
	LedStep(Right);
}

enum LedState{LED_LEFT,LED_RIGHT};
enum LedState eLedState = LED_LEFT;

int main()
{
	LedInit();
	while(1)
	{
		switch(eLedState){
			case LED_LEFT:
				eLedState = LED_RIGHT;
				LedStepRight();
				break;
			
			case LED_RIGHT:
				eLedState = LED_LEFT;
				LedStepLeft();
				break;

		}
Delay(200);
	}
}
