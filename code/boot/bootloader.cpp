//
// * Copyright (c) 2010 Saneyuki. All rights reserved.
//


#include "gfunction.h"

int LoaderMain(void){
	int Count, Data;
	unsigned char *GDTAddr = (unsigned char *) 0x0000DBE6;
	unsigned char *IDTAddr = (unsigned char *) 0x0000FBEC;

	SetDefaultGDT(GDTAddr);
	SetDefaultIDT(IDTAddr);

	Output(0x21, 0xFB, Byte);	/* Enable timer & keyboard */
	SetIntFlug();

	WriteCharacter(0x00, 0x00, 'S', 0x0F);
	WriteCharacter(0x08, 0x00, 'a', 0x0F);
	WriteCharacter(0x10, 0x00, 'n', 0x0F);
	WriteCharacter(0x18, 0x00, 'e', 0x0F);
	WriteCharacter(0x20, 0x00, 'o', 0x0F);
	WriteCharacter(0x28, 0x00, 's', 0x0F);

	HaltProcessor();
}

void Error(void){
	struct Graphic *SetGraphic = (struct Graphic *) 0x000107A0;
	int Count;
	SetGraphic->VRAMAddr = (unsigned char *) 0x000A0000;

	Output(0x03CE, 0x0305, Word);
	Output(0x03CE, 0x0300, Word);
	Output(0x03CE, 0xFF08, Word);

	for(Count = 0 ; Count < (640 * 480) / (8 * 4) ; Count++){
		WriteData(SetGraphic->VRAMAddr, 0xFFFFFFFF, 0x00, NML, DWord);
		SetGraphic->VRAMAddr = SetGraphic->VRAMAddr + 0x00000004;
	}

	HaltProcessor();
}
