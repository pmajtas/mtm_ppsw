#include "tokeny_keil.h"
#include "lanc-op-proste_mod.h"
#include "konwersje_keil_mod.h"

#define MAX_TOKEN_NR 3 //maksymalna dopuszczalna ilosc tokenów
#define MAX_KEYWORD_STRING_LTH 10 // mksymalna dlugosc komendy
#define MAX_KEYWORD_NR 3

/*void ReplaceCharactersInString(char pcString[], char cOldChar,char cNewChar)
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
}*/

struct Token asToken[MAX_TOKEN_NR];

typedef struct Keyword
{
	enum KeywordCode eCode;
	char cString[MAX_KEYWORD_STRING_LTH +1];
}Keyword;


struct Keyword asKeywordList[MAX_KEYWORD_NR]  =
{
{RST,"reset"},
{LD, "load" },
{ST, "store"}
};


enum KeywordCode Test;
enum KeywordCode *Test1 = &Test;

enum Result /*{ OK, ERROR }*/ eStringToKeyword(char pcStr[], enum KeywordCode *peKeywordCode) {
	unsigned char ucKeywordListCounter;
	for (ucKeywordListCounter = 0; ucKeywordListCounter < MAX_KEYWORD_NR; ucKeywordListCounter++) {
		if (eCompareString(pcStr, asKeywordList[ucKeywordListCounter].cString) == EQUAL) {
			*peKeywordCode = asKeywordList[ucKeywordListCounter].eCode;
			return OK;
		}
	}
	return ERROR;
}


unsigned char ucFindTokensInString(char *pcString) {
	unsigned char ucCharCounter;
	unsigned char ucTokenCounter=0;

	enum State{TOKEN,DELIMITER};
	enum State eState = DELIMITER;

	unsigned char cCurrentChar;
	
	for(ucCharCounter=0;;ucCharCounter++){

		cCurrentChar = *(pcString+ucCharCounter);

		switch (eState) {
			case(DELIMITER):
				if (cCurrentChar ==' ') {
					break;
				}
				else if ((cCurrentChar == '\0')||(ucTokenCounter == MAX_TOKEN_NR)) {
					return ucTokenCounter;
				}
				else {
					eState = TOKEN;
					asToken[ucTokenCounter].uValue.pcString = (pcString+ucCharCounter);
					ucTokenCounter++;
					break;
				}
			case(TOKEN):
				if ((cCurrentChar != ' ')&&(cCurrentChar != '\0')) {
					break;
				}
				else if (cCurrentChar == ' ') {
					eState = DELIMITER;
				}
				else if ((cCurrentChar == '\0')||(ucTokenCounter == MAX_TOKEN_NR)) {
					return ucTokenCounter;
				}
		}
	}
}

unsigned char ucTokenNumber=3;
void DecodeTokens(void){
	
	//unsigned char ucTokenNumber;
	unsigned char ucTokenCounter;
	Token *psVal ;
	
	for(ucTokenCounter=0;ucTokenCounter<ucTokenNumber; ucTokenCounter++){
		psVal = &asToken[ucTokenCounter];
		if(eStringToKeyword(psVal->uValue.pcString , &psVal->uValue.eKeyword)==OK){
			psVal->eType = KEYWORD;
		}
		else if(eHexStringToUInt(psVal->uValue.pcString , &psVal->uValue.uiNumber)==OK){
			psVal->eType = NUMBER;
		}
		else{
			psVal->eType = STRING;
		}
	}
}

char test[] = "store 0x5 test";
char *test1 = test;


void DecodeMsg(char *pcString){

	ucTokenNumber = ucFindTokensInString(pcString);
	ReplaceCharactersInString(pcString, ' ', '\0');
	DecodeTokens();
}



//int main() {
	//ucFindTokensInString(test1);
	//eStringToKeyword(test, &Test);
	//DecodeMsg(test1);
	
	
	
	
	//return 0;
	
	
	
	
	
	
	
	/*unsigned char ucCharCounter;
	unsigned char ucTokenCounter=0;

	enum State{TOKEN,DELIMITER};
	enum State eState = DELIMITER;

	char cCurrentChar;
	
	for(ucCharCounter=0;;ucCharCounter++){

		cCurrentChar = *(test1+ucCharCounter);

		switch (eState) {
			case(DELIMITER):
				if (cCurrentChar ==' ') {
					break;
				}
				else if (cCurrentChar == '\0') {
					//printf("%c",ucTokenCounter);
					return ucTokenCounter;
				}
				else {
					eState = TOKEN;
					asToken[ucTokenCounter].uValue.pcString = (test1+ucCharCounter);
					ucTokenCounter++;
					break;
				}
			case(TOKEN):
				if ((cCurrentChar != ' ')&&(cCurrentChar != '\0')) {
					break;
				}
				else if (cCurrentChar == ' ') {
					eState = DELIMITER;
				}
				else if (cCurrentChar == '\0') {
					//printf("%c",ucTokenCounter);
					return ucTokenCounter;
				}
		}
	}
}*/
