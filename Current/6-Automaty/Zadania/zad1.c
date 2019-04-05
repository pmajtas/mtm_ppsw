#include <LPC21xx.H> 

#define LED0_bm (1<<16) 
#define LED1_bm (1<<17)
#define LED2_bm (1<<18)
#define LED3_bm (1<<19)
#define LED7_bm (1<<23)

#define S0_bm (1<<5)
#define S1_bm (1<<7)
#define S2_bm (1<<6)
#define S3_bm (1<<8)

typedef enum eDirections{Left,Right,Nothing} eDirections;

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
	IO1CLR = IO1CLR | (LED0_bm | LED1_bm | LED2_bm | LED3_bm );
	
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

enum eDirections LedStep(enum  eDirections DirectStep)
{
	typedef enum eDirections eDirection ;
	static unsigned int LedPoint  ;
	
	if(DirectStep==Left)
	{
		LedPoint++ ;
		LedOn(LedPoint%4);
	}
	else if(DirectStep==Right)
	{
		LedPoint--;
		LedOn(LedPoint%4);
	}
	return Nothing;
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
Delay(500);
	}
	
	return 0;
}
