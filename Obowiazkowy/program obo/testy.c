#include "lanc-op-proste_mod.h"
#include "konwersje_keil_mod.h"
#include "tokeny_keil.h"

enum Result Result1,Result2,Result3,Result4,Result5,Result6,Result7,Result8,Result9,Result10,Result11 ;
//Testy funkcji lancuchy znakowe - operacje proste

enum Result TestOf_CopyString(){
	char cDestination[] = "cDest";
	char cDestination2[] = "";
	
	CopyString("cSorc", cDestination);
	CopyString("cSorc", cDestination2);
	
	//Test1 - rowne wymiary tablic	
	if(eCompareString(cDestination,"cSorc") == DIFFERENT){
		return ERROR;
	}
	//Test2 - kopiowanie do pustego lancucha
	if(eCompareString(cDestination2,"cSource" )==EQUAL){
		return ERROR;
	}
		else 
			return OK;
}

enum Result TestOf_eCompareString(){
	//Test 1 - takie same lancuchy
	if(eCompareString("Test1", "Test1") == DIFFERENT){
		return ERROR;
	}
	//Test 2 - pusty lancuch
	else if(eCompareString("Test1","") == EQUAL){
		return ERROR;
	}
	else
		return OK;
}

enum Result TestOf_AppendString(){
	char cDest1[11] = "Test2";
	char cDest2[] = "";
	
	AppendString("Test1",cDest1);
	//Test 1 - dwa niepuste lancuchy
	if(eCompareString(cDest1,"Test2Test1")==DIFFERENT){
		return ERROR;
	}
	AppendString("Test1",cDest2);
	//Test 2 - append do pustego lancucha
	if(eCompareString("Test1",cDest2)==EQUAL){
		return ERROR;
	}
	else 
		return OK;
}

enum Result TestOf_ReplaceCharactersInString(){
	char cString1[] = "Test1 Test2 Test3";
	char cString2[] = "";

	ReplaceCharactersInString(cString1, ' ','\0');
	ReplaceCharactersInString(cString2, '\0',' ');


	//Test 1 - spacja na null
	if((cString1[5] != '\0')||(cString1[11] != '\0')){
		return ERROR;
	}
	//Test 2 - zamiana w pustym
	else if(cString2[0] == ' '){
		return ERROR;
	}
	return OK;
}

// Testy funkcji lancuchy znakowe - konwersje
enum Result TestOf_UIntToHexStr(){

	unsigned int uiNumber1 =0x1A;
	char cNumber1[] = "0x001A";
	char cHexString[6];
	
	UIntToHexStr(uiNumber1, cHexString);
	//Test 1 - sprawdzenie poprawnosci zamiany uint na lancuch znakowy hex
	if(eCompareString(cNumber1,cHexString)==DIFFERENT){
		return ERROR;
	}
	return OK;
}

enum Result TestOf_eHexStringToUInt(){

	unsigned int uiResult;
	
	eHexStringToUInt("0x002A",&uiResult);
	//Test 1 - poprawny lancuch
	if(uiResult != 0x2A){
		return ERROR;
	}
	//Test 2 - zamiast x jest inna litera
	else if(eHexStringToUInt("0a002A", &uiResult)== OK){
		return ERROR;
	}
	//Test 3 - zamiast 0 na poczatku inna cyfra
	else if(eHexStringToUInt("1x002A", &uiResult)== OK){
		return ERROR;
	}
	//Test 4 - za dlugi hexstring
	else if(eHexStringToUInt("0x0002A", &uiResult)== OK){
		return ERROR;
	}
	//Test 5 - pusty hexstring
	else if(eHexStringToUInt("", &uiResult)== OK){
		return ERROR;
	}
	return OK;
}

enum Result TestOf_AppendUIntToString(){
	char cHexStr1[12] = "0x001A";
	char cHexStr2[] = "0x001A0x002A";
	
	AppendUIntToString(0x2A,cHexStr1);
	
	// Test 1 - sprawdzenie przypisania 
	if(eCompareString(cHexStr1, cHexStr2)==DIFFERENT){
		return ERROR;
	}
	else
		return OK;
}

//Testy funkcji sluzacych do dekodowania komunikatow

enum Result TestOf_ucFindTokensInString(){
	char cString1[] = "test string test test";
	char cString2[] = "";
	char cString3[] = "     ";
	char cString4[] = "   test    test   ";

	//Test1 - sprawdzenie ilosci tokenow w komunikacie
	if(ucFindTokensInString(cString1) != 3){
		return ERROR;
	}
	//Test 2 - sprawdzenie ilosci tokenow w pustym komunikacie
	else if(ucFindTokensInString(cString2) !=0){
		return ERROR;
	}
	//Test 3 - sprawdzenie ilosci tokenow w komunikacie z samymi delimiterami
	else if(ucFindTokensInString(cString3) !=0){
		return ERROR;
	}
	//Test 4 - sprawdzenie ilosci tokenow w komunikacie z wiecej niz jednym delimiterem
	else if(ucFindTokensInString(cString4) !=2){
		return ERROR;
	}
	return OK;
}

enum Result TestOf_eStringToKeyword(){

	enum KeywordCode peCode;
	
	//Test 1 - Sprawdzenie poprawnosci wykrycia
	eStringToKeyword("store", &peCode);
	if(peCode != ST){
		return ERROR;
	}
	else if(eStringToKeyword("store", &peCode)==ERROR){
		return ERROR;
	}
	//Test 2 - podanie wartosci z bledem
	if(eStringToKeyword("stoore", &peCode) != ERROR){
		return ERROR;
	}
	//Test 3 - Sprawdzenie przy podaniu slowa, ktore nie jest wartoscia slowa kluczowego
	if(eStringToKeyword("start", &peCode) != ERROR){
		return ERROR;
	}
 
	return OK;
}

enum Result TestOf_DecodeTokens(){
	
	struct Token *psToken;
	char cTest[] = "0x0010";
	char cTest2[] = "reset";
	char cTest3[] = "test";

	asToken[0].uValue.pcString = cTest;
	asToken[1].uValue.pcString = cTest2;
	asToken[2].uValue.pcString = cTest3;
	
	//ucFindTokensInString(cTest);
	//ReplaceCharactersInString(cTest,' ', '\0');
	DecodeTokens();
	psToken = &asToken[0];
	//Test 1 - sprawdzenie tokenu typu number
	if(psToken->eType != NUMBER){
		return ERROR;
	}
	else if(psToken->uValue.uiNumber != 0x10){
		return ERROR;
	}
	//Test 2 - sprawdzenie tokenu typu keyword
	else if((psToken+1)->eType != KEYWORD){
		return ERROR;
	}
	else if((psToken+1)->uValue.eKeyword != RST){
		return ERROR;
	}
	//Test 3 - sprawdzenie tokenu typu string
	else if((psToken+2)->eType != STRING){
		return ERROR;
	}
	else if((psToken+2)->uValue.pcString !=cTest3){
		return ERROR;
	}
	return OK;
}

enum Result TestOf_DecodeMsg(){

	struct Token *psToken ;
	char pcString1[] = "reset 0x0010 test1 test2";
	DecodeMsg(pcString1);
	psToken = asToken;
	//Test 1 - dekodowanie wiadomosci z wiecej niz max_token_nr
	if(psToken->eType != KEYWORD){
		return ERROR;
	}
	else if(psToken->uValue.eKeyword != RST){
		return ERROR;
	}
	else if((psToken+1)->eType != NUMBER){
		return ERROR;
	}
	else if((psToken+1)->uValue.uiNumber != 16){
		return ERROR;
	}
	else if((psToken+2)->eType != STRING){
		return ERROR;
	}
	else if((psToken+2)->uValue.pcString != (pcString1+13)){
		return ERROR;
	}
	return OK;
}

int main(void){
	
	//Testy funkcji - lancuchy operacje proste
	Result1 = TestOf_CopyString();
	Result2 = TestOf_eCompareString();
	Result3 = TestOf_AppendString();
	Result4 = TestOf_ReplaceCharactersInString();
	//Testy funkcji - lancuchy konwersje
	Result5 = TestOf_UIntToHexStr();
	Result6 = TestOf_eHexStringToUInt();
	Result7 = TestOf_AppendUIntToString();
	//Testy funkcji - dekodowanie komunikatow
	Result8 = TestOf_ucFindTokensInString();
	Result9 = TestOf_eStringToKeyword();
	Result10 = TestOf_DecodeTokens();
	Result11 = TestOf_DecodeMsg();
	
return 0;
}
