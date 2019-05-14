#define MAX_TOKEN_NR 3

typedef enum KeywordCode { LD, ST, RST } KeywordCode;
typedef enum TokenType { KEYWORD, NUMBER, STRING } TokenType;

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

extern struct Token asToken[MAX_TOKEN_NR];

unsigned char ucFindTokensInString(char *pcString);
enum Result eStringToKeyword(char pcStr[], enum KeywordCode *peKeywordCode);
void DecodeTokens(void);
void DecodeMsg(char *pcString);
