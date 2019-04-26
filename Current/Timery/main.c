#include "timer.h"

int main(){
	
	InitTimer0Match0(1000);
	WaitOnTimer0Match0();

	return 0;
}
