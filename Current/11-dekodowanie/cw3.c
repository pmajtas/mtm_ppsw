#include "uart.h"
#include "lanc-op-proste_mod.h"
#include "servo.h"


enum eReceiverStatus {EMPTY, READY, OVERFLOW}; 
enum eReceiverStatus eStatus;
 
int main(){
	char ucArray[10];
	UART_InitWithInt(9600);

	ServoInit(20);


	
	while(1){
		
		if(eReceiver_GetStatus()==READY){
			Receiver_GetStringCopy(ucArray);
		}
		
		if(eCompareString("callib",ucArray)==EQUAL){
			ServoCallib();}
			
		else if(eCompareString("left",ucArray)==EQUAL){
			ServoGoTo(12);}
			
		else if(eCompareString("right",ucArray)==EQUAL){
			ServoGoTo(36);}
			
			
			
		}
}
