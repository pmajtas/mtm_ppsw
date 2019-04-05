#include <LPC21xx.H> 

#define LED0_bm 0x00010000
#define LED1_bm 0x00020000
#define LED2_bm 0x00040000
#define LED3_bm 0x00080000
#define LED7_bm 0x00800000

#define S0_bm 0x0000000010
#define S1_bm 0x0000000040
#define S2_bm 0x0000000020
#define S3_bm 0x0000000080


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


void LedInit()
{
	IO1DIR = IO1DIR | LED0_bm | LED1_bm | LED2_bm | LED3_bm | LED7_bm ;
	IO1SET = IO1SET | LED0_bm;
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


void KeyboardInit()
{
	IO0DIR = IO0DIR & ~( S0_bm | S1_bm | S2_bm | S3_bm) ;
}

int ReadButton1()
{ 
	
	char cLedNumber ;
	
	enum ButtonState{RELEASED, PRESSED} ;


	cLedNumber = IO0PIN & 0x40 ;

	switch(cLedNumber)
	{
		case 0x40:
			return RELEASED;
		
		case 0:
			return PRESSED ;
		
		default: 
			return 0;
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

unsigned char ucDirectionTwo;
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
		}	
		Delay(250);
	}
}
