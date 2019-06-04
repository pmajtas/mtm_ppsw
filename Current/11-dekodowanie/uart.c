#include <LPC210X.H>
#include "uart.h"


/************ UART ************/
// U0LCR Line Control Register
#define mDIVISOR_LATCH_ACCES_BIT                   0x00000080
#define m8BIT_UART_WORD_LENGTH                     0x00000003

// UxIER Interrupt Enable Register
#define mRX_DATA_AVALIABLE_INTERRUPT_ENABLE        0x00000001
#define mTHRE_INTERRUPT_ENABLE                     0x00000002

// UxIIR Pending Interrupt Identification Register
#define mINTERRUPT_PENDING_IDETIFICATION_BITFIELD  0x0000000F
#define mTHRE_INTERRUPT_PENDING                    0x00000002
#define mRX_DATA_AVALIABLE_INTERRUPT_PENDING       0x00000004

/************ Interrupts **********/
// VIC (Vector Interrupt Controller) channels
#define VIC_UART0_CHANNEL_NR  6
#define VIC_UART1_CHANNEL_NR  7

// VICVectCntlx Vector Control Registers
#define mIRQ_SLOT_ENABLE                           0x00000020

////////////// Zmienne globalne ////////////
#define RECEIVER_SIZE 12

char cOdebranyZnak;

//enum eReceiverStatus {EMPTY, READY, OVERFLOW};

struct ReceiverBuffer{
	
	char cData[RECEIVER_SIZE];
	unsigned char ucCharCtr;
	enum eReceiverStatus eStatus;
};

struct ReceiverBuffer sBuffer;

///////////////////////////////////////////
__irq void UART0_Interrupt (void) {
   // jesli przerwanie z odbiornika (Rx)
   
   unsigned int uiCopyOfU0IIR=U0IIR; // odczyt U0IIR powoduje jego kasowanie wiec lepiej pracowac na kopii

   if      ((uiCopyOfU0IIR & mINTERRUPT_PENDING_IDETIFICATION_BITFIELD) == mRX_DATA_AVALIABLE_INTERRUPT_PENDING) // odebrano znak
   {
      cOdebranyZnak = U0RBR; //sluzy do odczytania bufora, zeby odczytac musi byc u0lcr=0 MSB to najnowszy bit, LSB to najstarszy
   } 
   
   if ((uiCopyOfU0IIR & mINTERRUPT_PENDING_IDETIFICATION_BITFIELD) == mTHRE_INTERRUPT_PENDING)              // wyslano znak - nadajnik pusty 
   {
      // narazie nic nie wysylamy
   }

   VICVectAddr = 0; // Acknowledge Interrupt
}

__irq void UART0_Interrupt_Servo(void){

	unsigned int uiCopyOfU0IIR=U0IIR; // odczyt U0IIR powoduje jego kasowanie wiec lepiej pracowac na kopii

   if      ((uiCopyOfU0IIR & mINTERRUPT_PENDING_IDETIFICATION_BITFIELD) == mRX_DATA_AVALIABLE_INTERRUPT_PENDING) // odebrano znak
   {
      cOdebranyZnak = U0RBR; //sluzy do odczytania bufora, zeby odczytac musi byc u0lcr=0 MSB to najnowszy bit, LSB to najstarszy
   } 
	 Receiver_PutCharacterToBuffer(cOdebranyZnak);
   
   if ((uiCopyOfU0IIR & mINTERRUPT_PENDING_IDETIFICATION_BITFIELD) == mTHRE_INTERRUPT_PENDING)              // wyslano znak - nadajnik pusty 
   {
      // narazie nic nie wysylamy
   }

   VICVectAddr = 0; // Acknowledge Interrupt

}

////////////////////////////////////////////
void UART_InitWithInt(unsigned int uiBaudRate){

   // UART0
   PINSEL0 = (PINSEL0 | 0x4) ;                                     // ustawic pina na odbiornik uart0, 
   U0LCR  |= m8BIT_UART_WORD_LENGTH | mDIVISOR_LATCH_ACCES_BIT; // dlugosc slowa, DLAB = 1, wlaczony DLAB to umozliwienie transmisji
   U0DLL   = (((15000000)/16)/uiBaudRate);                      // predkosc transmisji
   U0LCR  &= (~mDIVISOR_LATCH_ACCES_BIT);                       // DLAB = 0
   U0IER  |= mRX_DATA_AVALIABLE_INTERRUPT_ENABLE;               // UxIER sluzy do odblokowania czterech zrodel przerwan, w tym wypadku odblokowywujemy przerwania pochodzace z  Rx 

   // INT
   VICVectAddr1  = (unsigned long) UART0_Interrupt_Servo;             // set interrupt service routine address
   VICVectCntl1  = mIRQ_SLOT_ENABLE | VIC_UART0_CHANNEL_NR;     // use it for UART 0 Interrupt
   VICIntEnable |= (0x1 << VIC_UART0_CHANNEL_NR);               // Enable UART 0 Interrupt Channel
}

void Receiver_PutCharacterToBuffer(char cCharacter){
	//terminator to enter 0xD
	if(cCharacter != 0xD){
		sBuffer.cData[sBuffer.ucCharCtr] = cCharacter;
		sBuffer.ucCharCtr ++ ;
	}	
	else{
		sBuffer.cData[sBuffer.ucCharCtr] = '\0';
		sBuffer.eStatus = READY;
		sBuffer.ucCharCtr=0;
	}
	if(sBuffer.cData[(RECEIVER_SIZE-1)]!= '\0' ){
			sBuffer.eStatus = OVERFLOW;
			sBuffer.ucCharCtr=0;}
}

enum eReceiverStatus eReceiver_GetStatus(void){
	return sBuffer.eStatus ;
}

void Receiver_GetStringCopy(char cDestination[]){
	unsigned char ucCharCounter;

	for(ucCharCounter=0;sBuffer.cData[ucCharCounter] != '\0';ucCharCounter++){
		cDestination[ucCharCounter] = sBuffer.cData[ucCharCounter];
	}
	cDestination[ucCharCounter]= '\0';
	sBuffer.eStatus=EMPTY;
}
