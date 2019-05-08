#define MAX_TOKEN_NR 3
#define MAX_KEYWORD_STRING_LTH 10 
#define MAX_KEYWORD_NR 3

typedef enum TokenType { KEYWORD, NUMBER, STRING } TokenType;

typedef enum KeywordCode { LD, ST, RST } KeywordCode;

typedef union TokenValue
{
	enum KeywordCode eKeyword; // jezeli KEYWORD
	unsigned int uiNumber; // jezeli NUMBER
	char *pcString; // jezeli STRING
} TokenValue;

typedef struct Token
{
	enum TokenType eType; // KEYWORD, NUMBER, STRING
	union TokenValue uValue; // enum, unsigned int, char*
}Token;

struct Token asToken[MAX_TOKEN_NR];

typedef struct Keyword
{
	enum KeywordCode eCode;
	char cString[MAX_KEYWORD_STRING_LTH + 1];
}Keyword;

struct Keyword asKeywordList[MAX_KEYWORD_NR]  =
{
{RST,"reset"},
{LD, "load" },
{ST, "store"}
};


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
				
				if ((cCurrentChar == '\0')||(ucTokenCounter == MAX_TOKEN_NR)) {
					return ucTokenCounter;
				}
				else if (cCurrentChar !=' ') {
					eState = TOKEN;
					asToken[ucTokenCounter].uValue.pcString = (pcString+ucCharCounter);
					ucTokenCounter++;
					break;
				}
				else {
					break;
				}
			case(TOKEN):
				
				if (cCurrentChar == ' ') {
					eState = DELIMITER;
				}
				else if ((cCurrentChar == '\0')||(ucTokenCounter == MAX_TOKEN_NR)) {
					return ucTokenCounter;
				}
				else  {
					break;
				}
		}
	}
}

char *test = "qaz wsx test";
int main(){
	
	ucFindTokensInString( test);
	return 0;
}
