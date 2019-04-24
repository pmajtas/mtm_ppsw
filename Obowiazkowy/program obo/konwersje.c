

#define HEX_bm 0x000F 
unsigned int uiVal;
unsigned int *uiV = &uiVal;
char cTable[7];
char cTable2[] = "0x001D";

void UIntToHexStr(unsigned int uiValue, char pcStr[])
{
	unsigned char ucNibbleCounter;
	unsigned char ucActuallNibble;

	pcStr[0] = '0';
	pcStr[1] = 'x';

	for (ucNibbleCounter = 0; ucNibbleCounter < 4; ucNibbleCounter++)
	{
		ucActuallNibble = ((uiValue >> ucNibbleCounter * 4) & HEX_bm);

		if (ucActuallNibble > 9)
		{
			pcStr[5 - ucNibbleCounter] = ucActuallNibble - 10 + 'A';
		}
		else
		{
			pcStr[5 - ucNibbleCounter] = ucActuallNibble + '0';
		}
	
	}
	pcStr[6] = '\0';
	//printf(pcStr);
}

enum Result { OK, ERROR } eHexStringToUInt(char pcStr[], unsigned int *puiValue)
{
	unsigned char ucCharCounter; 
	if ((pcStr[0] != '0') || (pcStr[1] != 'x') || (pcStr[2] == '\0')) {
		return ERROR;
	}
	*puiValue = 0;
	for (ucCharCounter = 2; pcStr[ucCharCounter]!= '\0' ; ucCharCounter++)
	{
		if (ucCharCounter > 6) {
			return ERROR;
		}
		*puiValue = *puiValue |( pcStr[ucCharCounter] - '0');
		*puiValue = *puiValue << 4;
	}
	//printf("%u", *puiValue);
	return OK ;
}


int main()
{	unsigned int *puiValue;
	unsigned char pcStr[] = "0x001D";
	unsigned char ucCharCounter;
	puiValue = &uiVal;
	
	if ((pcStr[0] != '0') || (pcStr[1] != 'x'))
		return ERROR;
	
	*puiValue = 0;
	for (ucCharCounter = 2; ucCharCounter< 6 ; ucCharCounter++)
	{
		*puiValue = *puiValue << 4;
		if (pcStr[ucCharCounter] < 'A')
		{
			*puiValue = *puiValue | (pcStr[ucCharCounter] - '0');
		}
		else
		{
			*puiValue = *puiValue | (pcStr[ucCharCounter] - 'A' + 10);
		}
	}
	//printf("%u", *puiValue);
	return OK ;
	
	while(1)
	{ }
	return 0;
}
