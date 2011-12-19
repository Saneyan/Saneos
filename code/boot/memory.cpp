//
// * Copyright (c) 2010 Saneyuki. All rights reserved.
//


#include "gfunction.h"

void WriteData(unsigned char *MemAddr, int Data, int Bitwise, int WriType, char Value){
	int DataLimit;

	if(Value == Byte) DataLimit = 0x000000FF;
	else if(Value == Word) DataLimit = 0x0000FFFF;
	else if(Value == DWord) DataLimit = 0xFFFFFFFF;
	else{
		;
	}
	if(WriType == NML) WriteDataNML(MemAddr, Data, DataLimit);		/* Normal write-mode */
	else if(WriType == AND) WriteDataAND(MemAddr, Data, DataLimit);	/* And write-mode */
	else if(WriType == OR) WriteDataOR(MemAddr, Data);				/* Or write-mode */
	else if(WriType == XOR) WriteDataXOR(MemAddr, Data);			/* Xor write-mode */
	else if(WriType == NOT) WriteDataNOT(MemAddr, Data, DataLimit);	/* Not write-mode */
	else{
		;
	}

	return;
}

int GetData(unsigned int MemAddr, char Value){
	int Data, DataLimit;

	if(Value == Byte) DataLimit = 0x000000FF;
	else if(Value == Word) DataLimit = 0x0000FFFF;
	else if(Value == DWord) DataLimit = 0xFFFFFFFF;
	else{
		;
	}

	Data = GetDataNML(MemAddr, DataLimit);

	return Data;
}

void MemoryCopy(unsigned char *MemAddr1, unsigned char *MemAddr2, int Count){

	for(; Count != 0 ; Count--){
		*MemAddr2 = *MemAddr1;
		MemAddr1++;
		MemAddr2++;
	}

	return;
}

void SetDefaultGDT(unsigned char *GDTAddr){
	struct GDTR *GDTR_PO = (struct GDTR *) GDTAddr - 6;
	struct GDT *GDT_PO = (struct GDT *) GDTAddr;
	int Count;

	for(Count = 0 ; Count < 1024 ; Count++){
		SetGDT(GDT_PO + Count, 0, 0, 0);
	}

	GDTR_PO->Limit = 1024 * 8 - 1;
	GDTR_PO->BaseAddr = (unsigned long) GDT_PO;

	GDT_PO = GDT_PO - 1024 * 8;

	SetGDT(GDT_PO + 1, 0x00000000, 0xFFFFFFFF, 0xD09A);
	SetGDT(GDT_PO + 2, 0x00000000, 0xFFFFFFFF, 0xD092);
	LGDT(GDTR_PO);

	return;
}

void SetDefaultIDT(unsigned char *IDTAddr){
	struct IDTR *IDTR_PO = (struct IDTR *) IDTAddr - 6;
	struct IDT *IDT_PO = (struct IDT *) IDTAddr;
	int Count;

	for(Count = 0 ; Count < 256 ; Count++){
		SetIDT(IDT_PO + Count, (unsigned long) ISR, 0x0008, 0x8E);
	}

	IDTR_PO->Limit = 256 * 8 - 1;
	IDTR_PO->BaseAddr = (unsigned long) IDT_PO;

	LIDT(IDTR_PO);

	SetIDT(IDT_PO + 0x20, (unsigned long) Int20Handler, 0x0008, 0x8E);

	return;
}

void SetGDT(struct GDT *GDT_PO, unsigned long BaseAddr, unsigned int SegLimit, short Option){

	GDT_PO->SegLimitL = SegLimit & 0xFFFF;
	GDT_PO->BaseAddrL = BaseAddr & 0xFFFF;
	GDT_PO->BaseAddrM = (BaseAddr >> 16) & 0xFF;
	GDT_PO->T_S_DPL_P = Option & 0xFF;
	GDT_PO->SLH_AVL_R_DB_G = ((Option >> 8) & 0xF0) | ((SegLimit >> 16) & 0x0F);
	GDT_PO->BaseAddrH = (BaseAddr >> 24) & 0xFF;

	return;
}

void SetIDT(struct IDT *IDT_PO, unsigned long Offset, unsigned short Selctr, unsigned char DescType){

	IDT_PO->OfsL = Offset & 0xFFFF;
	IDT_PO->Selctr = Selctr;
	IDT_PO->DescType = DescType;
	IDT_PO->OfsH = (Offset >> 16) & 0xFFFF;

	return;
}
