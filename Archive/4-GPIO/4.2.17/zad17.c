#include <LPC21xx.H> 
//git test
#define LED0_bm 0x00010000
#define LED1_bm 0x00020000
#define LED2_bm 0x00040000
#define LED3_bm 0x00080000
#define LED7_bm 0x00800000

#define S0_bm (1<<4)
#define S1_bm (1<<6)
#define S2_bm (1<<5)
#define S3_bm (1<<7)

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
	IO1CLR =  (LED0_bm | LED1_bm | LED2_bm | LED3_bm );
	
	switch(ucLedIndeks)
		{
		case(0):
			IO1SET = IO1SET | LED0_bm ;
			break;
		
		case(1):
			IO1SET = IO1SET | LED1_bm ;
			break;
		
		case(2):
			IO1SET = IO1SET | LED2_bm ;
			break;
		
		case(3):
			IO1SET = IO1SET | LED3_bm ;
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

int main()
{
	LedInit() ;
	
	while(1)
	{
		if(ReadButton1()){
			LedOn(0);
		}
		else
			IO1CLR=LED0_bm ;
	}
}
