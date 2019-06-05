#include "uart.h"
#include "string.h"
#include "servo.h"
#include "command_decoder.h"


//enum eReceiverStatus {EMPTY, READY, OVERFLOW};   
//enum eReceiverStatus eStatus;
 
int main(){
	
	char ucArray[12];
	unsigned int uiPosition=0;
	UART_InitWithInt(9600);

	ServoInit(50);
	

	
	while(1){
		
		if(eReceiver_GetStatus()==READY){ 
			Receiver_GetStringCopy(ucArray);
			
			DecodeMsg(ucArray);
			
			if((ucTokenNumber !=0)&&(asToken[0].eType == KEYWORD)){
				
				switch(asToken[0].uValue.eKeyword){
				
					case(CALIB):
						ServoCallib();
						break;
					
					case(GOTO):
						uiPosition = asToken[1].uValue.uiNumber;
						uiPosition %=48;
						ServoGoTo(uiPosition);
						
						break;
					
					case(SHIFT):
						uiPosition +=asToken[1].uValue.uiNumber;
						uiPosition %=48;
						ServoGoTo(uiPosition);
						
					default:
						break;
				}
			}
		}
	}
}
