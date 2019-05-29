void UART_InitWithInt(unsigned int uiBaudRate);
void Receiver_PutCharacterToBuffer(char Character);
enum eReceiverStatus eReceiver_GetStatus(void);
void Receiver_GetStringCopy(char * ucDestination);
extern char cOdebranyZnak;


