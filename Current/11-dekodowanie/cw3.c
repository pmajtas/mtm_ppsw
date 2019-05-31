#include "uart.h"
#include "string.h"
#include "servo.h"
#include "command_decoder.h"


enum eReceiverStatus {EMPTY, READY, OVERFLOW}; 
enum eReceiverStatus eStatus;
 
int main(){
	char ucArray[10];
	UART_InitWithInt(9600);

	ServoInit(2);


	
	while(1){
		
		if(eReceiver_GetStatus()==READY){ 
			Receiver_GetStringCopy(ucArray);
			
			DecodeMsg(ucArray);
			
			switch(asToken[0].uValue.eKeyword){
			
				case(CALLIB):
					ServoCallib();
					break;
				
				case(GOTO):
					ServoGoTo(asToken[1].uValue.uiNumber);
					break;
				
				default:
					break;
			}
		}
	}
}
