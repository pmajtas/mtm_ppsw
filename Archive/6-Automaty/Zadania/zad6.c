#include <LPC21xx.H>  

#define LED0_bm (1<<16) 
#define LED1_bm (1<<17)
#define LED2_bm (1<<18)
#define LED3_bm (1<<19)

#define S0_bm (1<<4)
#define S1_bm (1<<6)
#define S2_bm (1<<5)
#define S3_bm (1<<7)

enum eDirections{Left,Right};
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
	IO1DIR = LED0_bm | LED1_bm | LED2_bm | LED3_bm ;
	IO1SET = LED0_bm  ;
}

void KeyboardInit()
{
	IO0DIR = IO0DIR & ~( S0_bm | S1_bm | S2_bm | S3_bm) ;
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
	static unsigned char ucLedPoint=9;
	
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

enum LedState{STAND_STILL, LED_RIGHT,LED_LEFT,LED_RIGHT_STEPS};
enum LedState eLedState = STAND_STILL; 

int main()
{
unsigned char ucLedStepCounter=1;

LedInit();
KeyboardInit();
	
	while(1) 
	{
		switch(eLedState){
			
			case STAND_STILL:
				if(eKeyboardRead()==BUTTON_0){
					eLedState= LED_LEFT;}
				else if(eKeyboardRead()==BUTTON_2){
					eLedState = LED_RIGHT;}
				else{
					eLedState = STAND_STILL;}
				break;
					
			case LED_LEFT :
				if(eKeyboardRead()==BUTTON_1){
					eLedState = STAND_STILL;}
				else{
					LedStepLeft();
					eLedState = LED_LEFT;}
				break;
			
			case LED_RIGHT :
				if(eKeyboardRead()==BUTTON_1){
					eLedState=STAND_STILL;}
				else if(eKeyboardRead()==BUTTON_0){
					eLedState= LED_RIGHT_STEPS ;}
				else{
					LedStepRight();
					eLedState=LED_RIGHT;}
				break;
					
			case LED_RIGHT_STEPS:
				if(ucLedStepCounter ==10){
					ucLedStepCounter=0;
					LedStepLeft();
					eLedState = LED_LEFT;}
				else{
					LedStepRight();
					ucLedStepCounter=ucLedStepCounter+1;
					eLedState = LED_RIGHT_STEPS;}
			break;
								
			default:
				break;
		}
		Delay(100);
	}
}
