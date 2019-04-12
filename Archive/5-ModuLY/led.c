#include <LPC21xx.H>
#include "led.h"

#define LED0_bm (1<<16) //w nawiasie poniewaz jest to wyrazenie, a nie stala
#define LED1_bm (1<<17)
#define LED2_bm (1<<18)
#define LED3_bm (1<<19)

#define S0_bm (1<<4)
#define S1_bm (1<<6)
#define S2_bm (1<<5)
#define S3_bm (1<<7)


typedef enum eDirections{Left,Right} eDirections;


void LedOn(unsigned char ucLedIndeks)
{
	IO1CLR =  (LED0_bm | LED1_bm | LED2_bm | LED3_bm );
	
	switch(ucLedIndeks)
		{
		case(0):
			IO1SET = LED0_bm ;
			break;
		
		case(1):
			IO1SET = LED1_bm ;
			break;
		
		case(2):
			IO1SET = LED2_bm ;
			break;
		
		case(3):
			IO1SET =  LED3_bm ;
			break;

		}
}

void LedInit(void)
{
	IO1DIR = LED0_bm | LED1_bm | LED2_bm | LED3_bm ;
	IO1SET = LED0_bm ;
}


void LedStep(enum  eDirections DirectStep)
{
	static unsigned int LedPoint;
	
	switch(DirectStep)
	{
		case(Left):
			LedPoint++;
			break;
		
		case(Right):
			LedPoint--;
			break;
		
		default:
			break;
	}
	LedOn(LedPoint%4);
}

void LedStepLeft(void)
{
	LedStep(Left);
}

void LedStepRight(void)
{
	LedStep(Right);
}
