#include <LPC21xx.H> 

#define LED0_bm (1<<16) 
#define LED1_bm (1<<17)
#define LED2_bm (1<<18)
#define LED3_bm (1<<19)


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

int eKeyboardRead()
{
	enum eKeyboardButtons{BUTTON_0, BUTTON_1, BUTTON_2, BUTTON_3,RELEASED } ;

	IO1CLR = 0xFFFFFFFF ;

	if((IO0PIN & S0_bm) == 0x0)
	{
		return 0 ;
	}
	
	else if((IO0PIN & S1_bm) == 0x0)
	{
		return 1 ;
	}
	
	else if((IO0PIN & S2_bm) == 0x0)
	{
		return 2 ;
	}
	
	else if((IO0PIN & S3_bm) == 0x0)
	{
		return 3 ;
	}
	else
	{
		return 4 ; 
	}
}

void LedInit()
{
	IO1DIR = IO1DIR | LED0_bm | LED1_bm | LED2_bm | LED3_bm  ;
	IO1SET = IO1SET | LED0_bm  ;
}


void LedOn(unsigned char ucLedIndeks)
{
	IO1CLR =  (LED0_bm | LED1_bm | LED2_bm | LED3_bm );
	
	switch(ucLedIndeks)
		{
		case(0):
			IO1SET =  LED0_bm ;
			break;
		
		case(1):
			IO1SET =  LED1_bm ;
			break;
		
		case(2):
			IO1SET =  LED2_bm ;
			break;
		
		case(3):
			IO1SET =  LED3_bm ;
			break;
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

enum LedState{LED_LEFT, LED_RIGHT};
enum LedState eLedState = LED_LEFT; 

int main()
{

	static unsigned char ucLED_STEP_COUNTER =0;
	LedInit();
	
	while(1)
	{
		switch(eLedState){
			case LED_LEFT:
				LedStepRight();
				ucLED_STEP_COUNTER= (ucLED_STEP_COUNTER+1)%3;
				if(ucLED_STEP_COUNTER==2){
					eLedState=LED_RIGHT;}
				break;
			
			case LED_RIGHT:
				LedStepLeft();
				ucLED_STEP_COUNTER = (ucLED_STEP_COUNTER+1)%3;
				if(ucLED_STEP_COUNTER==2){
					eLedState = LED_LEFT;}
				break;
		}
	Delay(200); 
	}
}
