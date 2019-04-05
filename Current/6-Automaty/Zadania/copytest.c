char Dst[] = "678";
char Src[] = "012345";



unsigned char ucCharCounter;

int main(){
	
	for(ucCharCounter = 0 ; Src[ucCharCounter] != '\0' ; ucCharCounter++)
	{
		Dst[ucCharCounter]= Src[ucCharCounter];
	}
	Dst[ucCharCounter] = '\0';

	return 0;
}
