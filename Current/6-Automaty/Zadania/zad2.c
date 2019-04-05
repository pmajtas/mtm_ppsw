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

enum LedState{STATE0, STATE1, STATE2, STATE3, STATE4, STATE5};
enum LedState eLedState = STATE0;

int main()
{
	while(1)
	{
		switch(eLedState){
			case STATE0:
				eLedState = STATE1;
				LedStepRight();
				break;
			
			case STATE1:
				eLedState = STATE2;
				LedStepRight();
				break;
			
			case STATE2:
				eLedState = STATE3;
				LedStepRight();
				break;
			
			case STATE3:
				eLedState = STATE4;
				LedStepLeft();
				break;
			
			case STATE4:
				eLedState = STATE5;
				LedStepLeft();
				break;
			
			case STATE5:
				eLedState=STATE0;
				LedStepLeft();
				break;

		}
Delay(200); 
	}
	
	return 0;
}
