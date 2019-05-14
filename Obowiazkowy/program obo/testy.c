#include "lanc-op-proste_mod.h"
#include "konwersje_keil_mod.h"
#include "tokeny_keil.h"

//Testy funkcji lancuchy znakowe - operacje proste

enum Result TestOf_CopyString(){
	char cString1[] = "Test1";
	char cString2[] = "Test2";
	char cString3[] = "Test3";
	char cString4[] = "";
	
	//Test1 - sprawdzenie poprawnosci dzialania CopyString
	CopyString(cString1, cString2);
	CopyString(cString3, cString4);
	if(eCompareString(cString1,cString2) == DIFFERENT){
		return ERROR;
	}
	//Test2 - test dla róznych wymiarow tablic
	if(eCompareString(cString3, cString4)==EQUAL){
		return ERROR;
	}
		else 
			return OK;
}

enum Result TestOf_eCompareString(){
	char cString1[] = "Test1";
	char cString2[] = "Test1";
	char cString3[] = "Test2";
	//Test 1 - sprawdzenie dla takich samych lanuchow
	if(eCompareString(cString1, cString2) == DIFFERENT){
		return ERROR;
	}
	//Test 2 - sprawdzenie dla roznych lancuchow
	else if(eCompareString(cString2,cString3) == EQUAL){
		return ERROR;
	}
	else
		return OK;
}

enum Result TestOf_AppendString(){
	char cString1[10] = "Test1";
	char cString2[10] = "Test2";
	char cString3[10] = "Test1Test2";
	char cString4[10] = "";
	char cString5[10] = "Test1Test2";

	
	AppendString(cString2,cString1);
	AppendString(cString4,cString5);

	//Test 1 - sprawdzenie przy dwoch niepustych lancuchach
	if(eCompareString(cString1,cString3)==DIFFERENT){
		return ERROR;
	}
	//Test 2 - sprawdzenie przy dolaczaniu pustego lancucha
	else if(eCompareString(cString5,cString3)==DIFFERENT){
		return ERROR;
	}
	else 
		return OK;
}

enum Result TestOf_ReplaceCharactersInString(){
	char cString1[] = "Test1";
	char cString2[] = "Tost1";
	char cChar1 = 'e';
	char cChar2 = 'o';
	
	ReplaceCharactersInString(cString1, cChar1,cChar2);

	//Test 1 - Sprawdzenie poprawnosci zmienonego znaku
	if(eCompareString(cString1,cString2)==DIFFERENT){
		return ERROR;
	}
	return OK;
}

// Testy funkcji lancuchy znakowe - konwersje
enum Result TestOf_UIntToHexStr(){

	unsigned int uiNumber1 = 25;
	char cNumber1[] = "0x0019";
	char cHexString[6];
	
	UIntToHexStr(uiNumber1, cHexString);
	//Test 1 - sprawdzenie poprawnosci zamiany uint na lancuch znakowy hex
	if(eCompareString(cNumber1,cHexString)==DIFFERENT){
		return ERROR;
	}
	return OK;
}

enum Result TestOf_eHexStringToUInt(){
	char cHexStr1[] = "0x0028";
	char cHexStr2[] = "0a0011";
	char cHexStr3[] = "1x0012";
	char cHexStr4[] = "0x00001";
	char cHexStr5[] = "0x";
	unsigned int uiResult;
	unsigned int uiValue = 40;
	
	eHexStringToUInt(cHexStr1,&uiResult);
	//Test 1 - sprawdzenie poprawnosci zamiany lancucha na uint
	if(uiResult != uiValue){
		return ERROR;
	}
	//Test 2 - sprawdzenie wykrycia nieprawidlowego hexstring
	else if(eHexStringToUInt(cHexStr2, &uiResult)== OK){
		return ERROR;
	}
	//Test 3 - sprawdzenie wykrycia nieprawidlowego hexstring
	else if(eHexStringToUInt(cHexStr3, &uiResult)== OK){
		return ERROR;
	}
	//Test 4 - sprawdzenie wykrycia nieprawidlowego hexstring
	else if(eHexStringToUInt(cHexStr4, &uiResult)== OK){
		return ERROR;
	}
	//Test 5 - sprawdzenie wykrycia nieprawidlowego hexstring
	else if(eHexStringToUInt(cHexStr5, &uiResult)== OK){
		return ERROR;
	}
	return OK;
}

enum Result TestOf_AppendUIntToString(){
	char cHexStr1[12] = "0x0012";
	char cHexStr2[] = "0x00120x0014";
	unsigned int uiValue = 20;
	
	AppendUIntToString(uiValue,cHexStr1);
	
	// Test 1 - sprawdzenie przypisania 
	if(eCompareString(cHexStr1, cHexStr2)==DIFFERENT){
		return ERROR;
	}
	else
		return OK;
}

//Testy funkcji sluzacych do dekodowania komunikatow

enum Result TestOf_ucFindTokensInString(){
	char cString1[] = "test string";
	char cString2[] = "";
	char cString3[] = "     ";
	char cString4[] = "   test    test   ";
	unsigned char ucResult1, ucResult2, ucResult3, ucResult4;
	
	ucResult1 = ucFindTokensInString(cString1);
	ucResult2 = ucFindTokensInString(cString2);
	ucResult3 = ucFindTokensInString(cString3);
	ucResult4 = ucFindTokensInString(cString4);
	//Test1 - sprawdzenie ilosci tokenow w komunikacie
	if(ucResult1 != 2){
		return ERROR;
	}
	//Test 2 - sprawdzenie ilosci tokenow w pustym komunikacie
	else if(ucResult2 !=0){
		return ERROR;
	}
	//Test 3 - sprawdzenie ilosci tokenow w komunikacie z samymi delimiterami
	else if(ucResult3 !=0){
		return ERROR;
	}
	//Test 4 - sprawdzenie ilosci tokenow w komunikacie z wiecej niz jednym delimiterem
	else if(ucResult4 !=2){
		return ERROR;
	}
	return OK;
}

enum Result TestOf_eStringToKeyword(){
	
	
	return OK;
}

enum Result eResult=ERROR;
char Tab[15] = "0x1234";

int main(){
	
	AppendUIntToString(20,Tab);
	eResult=TestOf_ucFindTokensInString();
	
	return 1;
}
