#define HEX_bm 0x000F 


unsigned int uiVal;
unsigned int *puiV= &uiVal ;

char cTable[] = "0x0012";
char cTable2[] = "0x00FD";

void UIntToHexStr(unsigned int uiValue, char pcStr[])
{
	unsigned char ucNibbleCounter;
	unsigned char ucCurrentNibble;

	pcStr[0] = '0';
	pcStr[1] = 'x';

	for (ucNibbleCounter = 0; ucNibbleCounter < 4; ucNibbleCounter++)
	{
		ucCurrentNibble = ((uiValue >> ucNibbleCounter * 4) & HEX_bm);

		if (ucCurrentNibble > 9)
		{
			pcStr[5 - ucNibbleCounter] = ucCurrentNibble - 10 + 'A';
		}
		else
		{
			pcStr[5 - ucNibbleCounter] = ucCurrentNibble + '0';
		}
	
	}
	pcStr[6] = '\0';
}


enum Result{OK, ERROR} eHexStringToUInt(char pcStr[], unsigned int *puiValue)
{
	unsigned char ucCharCounter;
	unsigned char ucCurrentChar;
	
	if((pcStr[0]!= '0')||(pcStr[1]!='x')||(pcStr[2] == '\0')){
		return ERROR;}
		
	*puiValue = 0;
		for(ucCharCounter=2;pcStr[ucCharCounter]!='\0';ucCharCounter++){
			if(ucCharCounter>5){
				return ERROR;}
			
			ucCurrentChar = pcStr[ucCharCounter];
			*puiValue = *puiValue<<4;
				
			if(ucCurrentChar < 'A'){
					*puiValue= *puiValue | (ucCurrentChar - '0');
			}
			else{
				*puiValue = *puiValue | (ucCurrentChar - 'A' + 10);
			}
		}
		return OK;
}


/*void AppendUIntToString(unsigned int uiValue, char pcDestinationStr[])
{
	unsigned char ucEndPointer;
	for (ucEndPointer = 0; pcDestinationStr[ucEndPointer] != '\0'; ucEndPointer++) {}
	UIntToHexStr(uiValue, pcDestinationStr + ucEndPointer);

}*/

	enum Result eReturnValue;
int main()
{
	//int poglad = 0;
	unsigned int uiValue = 65000;
	char cHexStr[12] = "0xF5A97";
 	
	//eReturnValue = eHexStringToUInt(cHexStr , &uiValue);
	
	
	
	//eReturnValue = ERROR; //to bd dzialac i nawet poprawnie z konwencjami, bo zawsze i tak zwroci ci dobra wartosc jezeli jest dobra
	//a jak zla to zostanie zla rozumiesz? tak, ale nie lapie czemu samo z siebie nie moze zwrocic wartosci tylko trzeba recznie jakas wpisac
	//kompilator jest dziwny i dlatego moim zdaniem 
	eReturnValue = eHexStringToUInt(cHexStr , &uiValue);
	//albo i nie 
	//cczekaj porobie foty i zapytam sie na stackoverflow XDD <3
  
	
}
