#include <stdio.h>

char cTextTwo[] = "Ciasto" ;
char cTextOne[] =  "Placekkkkkk" ;

char cTextThree[]=  "Tort" ;
char cDoZmiany = 'a';
char cNowa = 'o';

/*typedef enum CompResult 
{ DIFFERENT , EQUAL } CompResult;*/

void CopyString(char pcSource[], char pcDestination[])
{
	unsigned char ucCharCounter;

	for (ucCharCounter=0 ; pcSource[ucCharCounter] !='\0'; ucCharCounter++)
	{
		pcDestination[ucCharCounter] = pcSource[ucCharCounter];
		
	}
	pcDestination[ucCharCounter] = '\0';
}

enum CompResult{DIFFERENT, EQUAL} eCompareString(char pcStr1[], char pcStr2[])
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


void AppendString(char pcSourceStr[], char pcDestinationStr[])
{
	unsigned char ucCharCounter;

	for (ucCharCounter = 0; pcDestinationStr[ucCharCounter] != '\0'; ucCharCounter++)
	{

	}
		CopyString(pcSourceStr, pcDestinationStr+ucCharCounter);

}


void ReplaceCharactersInString(char pcString[], char cOldChar,char cNewChar)
{
	unsigned char ucCharCounter;

	for (ucCharCounter=0; ucCharCounter < 254; ucCharCounter++)
	{
		if (pcString[ucCharCounter] == cOldChar)
		{
			pcString[ucCharCounter] = cNewChar;
		}
	}
}
char result;
int main()
{

	unsigned char ucCharCounter;

	for (ucCharCounter=0 ; cTextOne[ucCharCounter] !='\0'; ucCharCounter++)
	{
		cTextTwo[ucCharCounter] = cTextOne[ucCharCounter];
		
	}
	cTextTwo[ucCharCounter] = '\0';

	return 0;
}
