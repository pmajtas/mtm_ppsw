#define MAX_TOKEN_NR 2
		
void DecodeMsg(char *pcString);

enum eTokenType {KEYWORD, NUMBER, STRING};
enum KeywordCode {CALLIB, GOTO};

union TokenValue{
	unsigned int uiNumber;
	enum KeywordCode eKeyword;
	char *pcString;
};

typedef struct Token{
	enum eTokenType eType;
	union TokenValue uValue;
	} Token;

extern struct Token asToken[MAX_TOKEN_NR];
