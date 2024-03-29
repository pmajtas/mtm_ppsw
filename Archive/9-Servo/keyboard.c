#include <LPC21xx.H>
#include "keyboard.h"

#define LED0_bm (1<<16) //w nawiasie poniewaz jest to wyrazenie, a nie stala
#define LED1_bm (1<<17)
#define LED2_bm (1<<18)
#define LED3_bm (1<<19)
#define LED7_bm (1<<23)

#define S0_bm (1<<4)
#define S1_bm (1<<6)
#define S2_bm (1<<5)
#define S3_bm (1<<7)


void KeyboardInit(void)
{
	IO0DIR = IO0DIR & ~( S0_bm | S1_bm | S2_bm | S3_bm) ;
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

enum eKeyboardButtons eKeyboardRead(void)
{

	if((IO0PIN & S0_bm) == 0x0)
	{
		return BUTTON_0 ;
	}
	
	else if((IO0PIN & S1_bm) == 0x0) // przy wcisnieciu daje 0, przy puszczeniu daje 0x40
	{
		return BUTTON_1 ;
	}
	
	else if((IO0PIN & S2_bm) == 0x0) // // przy wcisnieciu daje 0, przy puszczeniu daje 0x20
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
