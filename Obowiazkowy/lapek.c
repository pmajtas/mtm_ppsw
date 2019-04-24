#include <LPC21xx.H>

#define BIT16_bm (1<<16)
#define BIT17_bm (1<<16)
#define BIT18_bm (1<<16)
#define BIT16_bm (1<<16)


int main()
{
	IO1DIR = 0x0001000;
		
	IO1SET = 0x0001000;
	IO1CLR = 0x0001000;

}
