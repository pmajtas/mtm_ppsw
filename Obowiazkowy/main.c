#include <LPC21xx.H>
#include <stdio.h>

void CopyString(char pcSource[], char pcDestination[])
{
	unsigned char ucCopyLoopCounter;

	for (ucCopyLoopCounter=0 ; pcSource[ucCopyLoopCounter] !='\0'; ucCopyLoopCounter++)
	{
		pcDestination[ucCopyLoopCounter] = pcSource[ucCopyLoopCounter];
		
	}
	pcDestination[ucCopyLoopCounter] = '\0';
}

int eCompareString(char pcStr1[], char pcStr2[])
{
	enum CompResult{DIFFERENT, EQUAL};
	unsigned char ucCompareLoopCounter;


	for (ucCompareLoopCounter = 0; pcStr1[ucCompareLoopCounter]!='\0'; ucCompareLoopCounter++)
	{
		if (pcStr1[ucCompareLoopCounter] != pcStr2[ucCompareLoopCounter])
		{
			return DIFFERENT;
		}
	}
		return EQUAL;	
}


void AppendString(char pcSourceStr[], char pcDestinationStr[])
{
	unsigned char ucAppendLoopCounter;

	for (ucAppendLoopCounter = 0; pcDestinationStr[ucAppendLoopCounter] != '\0'; ucAppendLoopCounter++)
	{

	}
		CopyString(pcSourceStr, pcDestinationStr+ucAppendLoopCounter);
}


void ReplaceCharactersInString(char pcString[], char cOldChar,char cNewChar)
{
	unsigned char ucReplaceLoopCounter;

	for (ucReplaceLoopCounter=0; ucReplaceLoopCounter < 254; ucReplaceLoopCounter++)
	{
		if (pcString[ucReplaceLoopCounter] == cOldChar)
		{
			pcString[ucReplaceLoopCounter] = cNewChar;
		}
	}
}

int main()
{
	return 0;
}
