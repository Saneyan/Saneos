//
// * Copyright (c) 2010 Saneyuki. All rights reserved.
//


#include "gfunction.h"

void Output(short Outport, int Data, char Value){

	if(Value == 0x01) OutputB(Outport, Data);
	else if(Value == 0x02) OutputW(Outport, Data);
	else if(Value == 0x03) OutputD(Outport, Data);
	else{
		;
	}

	return;
}

int Input(short Inport, char Value){
	int Data;

	if(Value == 0x01) InputB(Inport);
	else if(Value == 0x02) InputW(Inport);
	else if(Value == 0x03) InputD(Inport);
	else{
		;
	}

	return Data;
}
