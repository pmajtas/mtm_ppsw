#include "command_decoder.h"
#include "string.h"

#define MAX_TOKEN_NR 2	
#define MAX_KEYWORD_LENGHT 12



/*enum eTokenType {KEYWORD, NUMBER, STRING};*/
//enum KeywordCode { GOTO,SHIFT,CALLIB};



/*typedef struct Token{
	enum eTokenType eType;
	union TokenValue uValue;
	} Token;*/

struct Keyword{
	enum KeywordCode eCode;
	char cString[MAX_KEYWORD_LENGHT+1];
};

struct Token asToken[MAX_TOKEN_NR];

struct Keyword asKeywordList[]=
{
	{CALIB, "callib"},
	{GOTO, "goto"},
	{SHIFT, "shift"}
};
	
unsigned char ucTokenNumber;



unsigned char ucFindTokensInString(char *pcStr) {
	
	unsigned char ucCharCounter;
	unsigned char ucTokenCounter=0;

	enum State{TOKEN,DELIMITER};
	enum State eState = DELIMITER;

	unsigned char cCurrentChar;
	
	for(ucCharCounter=0;;ucCharCounter++){

		cCurrentChar = pcStr[ucCharCounter];

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
					asToken[ucTokenCounter].uValue.pcString = (pcStr+ucCharCounter);
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

enum Result /*{ OK, ERROR }*/ eStringToKeyword(char pcStr[], enum KeywordCode *peKeywordCode) {
	unsigned char ucKeywordListCounter;
	for (ucKeywordListCounter = 0; ucKeywordListCounter < 3; ucKeywordListCounter++) {
		if (eCompareString(pcStr, asKeywordList[ucKeywordListCounter].cString) == EQUAL) {
			*peKeywordCode = asKeywordList[ucKeywordListCounter].eCode;
			return OK;
		}
	}
	return ERROR;
}

void DecodeTokens(void){
	
	//unsigned char ucTokenNumber;
	unsigned char ucTokenCounter;
	struct Token *psVal ;
	
	for(ucTokenCounter=0;ucTokenCounter<ucTokenNumber; ucTokenCounter++){
		psVal = &asToken[ucTokenCounter];
		if(eStringToKeyword(psVal->uValue.pcString , &psVal->uValue.eKeyword)==OK){
			psVal->eType = KEYWORD;
		}
		if(eHexStringToUInt(psVal->uValue.pcString , &psVal->uValue.uiNumber)==OK){
			psVal->eType = NUMBER;
		}
		else{
			psVal->eType = STRING;
		}
	}
	if((asToken[0].uValue.eKeyword== GOTO)||(asToken[0].uValue.eKeyword==CALIB)||(asToken[0].uValue.eKeyword==SHIFT)){
		asToken[0].eType = KEYWORD; }
	
}

void DecodeMsg(char *pcString){
	
	ucTokenNumber = ucFindTokensInString(pcString);
	ReplaceCharactersInString(pcString, ' ', '\0');
	DecodeTokens();
}
