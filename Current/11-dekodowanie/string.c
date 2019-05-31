#include "string.h"
	
	
	enum Result eHexStringToUInt(char pcStr[], unsigned int *puiValue)
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

void ReplaceCharactersInString(char pcString[], char cOldChar,char cNewChar)
{
	unsigned char ucCharCounter;

	for (ucCharCounter=0; pcString[ucCharCounter]!='\0'; ucCharCounter++)
	{
		if (pcString[ucCharCounter] == cOldChar)
		{
			pcString[ucCharCounter] = cNewChar;
		}
	}
}

enum CompResult eCompareString(char pcStr1[], char pcStr2[])
{
	unsigned char ucCharCounter;

	for (ucCharCounter = 0; pcStr1[ucCharCounter] != '\0'; ucCharCounter++)
	{
		if (pcStr1[ucCharCounter] != pcStr2[ucCharCounter])
		{
			return DIFFERENT;
		}
	}
	return EQUAL;
}


