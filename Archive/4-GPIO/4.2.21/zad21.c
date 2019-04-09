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

static unsigned int LedPoint ;
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
	IO1DIR = IO1DIR | LED0_bm | LED1_bm | LED2_bm | LED3_bm ;
	IO1SET = IO1SET | LED0_bm ;
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

int ReadButton1()
{ 
	enum ButtonState{RELEASED,PRESSED};
	unsigned char ucButtonState;
	
	ucButtonState = (~(IO0PIN) & S0_bm);

	switch(ucButtonState){
		case(0x10):
			return PRESSED;
		
		default:
			return RELEASED;
	
	}
}

void KeyboardInit(void){
	IO0DIR = IO0DIR & ~(S0_bm | S1_bm | S2_bm | S3_bm) ;
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

void StepRight()
{
	LedPoint--;
	LedOn(LedPoint%4);
}


int main()
{
	int cLedCounter;
	KeyboardInit() ;
	LedInit() ;
	
	while(1)
	{
		for(cLedCounter=0; cLedCounter <4; cLedCounter++){
		IO1SET = LED3_bm >> cLedCounter;
		}
		IO1CLR = LED0_bm | LED1_bm | LED2_bm | LED3_bm;
	}
}
