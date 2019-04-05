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

static unsigned int LedPoint = 3;
typedef enum eKeyboardButtons{BUTTON_0=0, BUTTON_1=1, BUTTON_2=2, BUTTON_3,RELEASED } eKeyboardButtons;


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
	IO1SET = IO1SET | LED0_bm ;
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

	IO0DIR = 0x0 ;
	IO1CLR = 0xFFFFFFFF ;

	cLedNumber = IO0PIN & 0x40 ;

	switch(cLedNumber)
	{
		case 0x40:
			LedOn(RELEASED);
			return RELEASED;
		
		case 0:
			LedOn(PRESSED);
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

void StepLeft()
{
	LedPoint++;
	LedOn(LedPoint%4);
}


int main()
{
	KeyboardInit() ;
	LedInit() ;
	Delay(1000);
	
	while(1)
	{
		StepLeft();	IO1SET = IO1SET | LED0_bm ;
		StepLeft();	IO1SET = IO1SET | LED0_bm | LED1_bm ;
		StepLeft();	IO1SET = IO1SET | LED0_bm | LED1_bm | LED2_bm ;
		StepLeft(); IO1SET = IO1SET | LED0_bm | LED1_bm | LED2_bm | LED3_bm ;
	}
}
