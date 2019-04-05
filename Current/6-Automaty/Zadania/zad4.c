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
typedef enum eKeyboardButtons{BUTTON_0, BUTTON_1, BUTTON_2, BUTTON_3,RELEASED } eKeyboardButtons;


void Delay(int iDelayMiliSeconds)
{
	int i;
	int iLimit = 12000*iDelayMiliSeconds; 
	
	for(i=0; i < iLimit ; i++)
	{
		
	}
}

enum eKeyboardButtons eKeyboardRead()
{

	if((IO0PIN & S0_bm) == 0x0)
	{
		return BUTTON_0 ;
	}
	
	else if((IO0PIN & S1_bm) == 0x0)
	{
		return BUTTON_1 ;
	}
	
	else if((IO0PIN & S2_bm) == 0x0)
	{
		return BUTTON_2 ;
	}
	
	else if((IO0PIN & S3_bm) == 0x0)
	{
		return BUTTON_3 ;
	}
	else
	{
		return RELEASED ; 
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

enum LedState{STAND_STILL, LED_RIGHT};
enum LedState eLedState = STAND_STILL; 

int main()
{
	
	while(1)
	{
		switch(eLedState){
			case STAND_STILL:
				if(eKeyboardRead()==0){eLedState=LED_RIGHT;}
				break;
			
			case LED_RIGHT:
				LedStepRight();
				Delay(100);
				LedStepRight();
				Delay(100);
				LedStepRight();
				Delay(100);
				eLedState = STAND_STILL;
				break;
		} 
	}
}
