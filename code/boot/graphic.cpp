//
// * Copyright (c) 2010 Saneyuki. All rights reserved.
//


#include "gfunction.h"

int WritePixel(int x, int y, short Color){
	int OutputData, Data;
	unsigned char *VRAMAddr = (unsigned char *) 0x000A0000;

	VRAMAddr = VRAMAddr + y * 80;

	while(x >= 8){
		VRAMAddr++;
		x = x - 8;
	}

	Data = 128;
	Data = Data >> x;
	OutputData = Data;
	OutputData = OutputData << 8;
	OutputData = OutputData | 8;
	Output(0x03CE, OutputData, Word);
	Color = Color << 8;
	Output(0x03CE, Color, Word);

	*VRAMAddr = *VRAMAddr | Data;

	return 0;
}

int WriteCharacter(int x, int y, int Charctr, short Color){
	int Count1, Count2, NullCount, Data, Width, Height;
	unsigned char *MemAddr = (unsigned char *) 0x0000BC00;

	NullCount = 0;
	Width = 8;
	Height = 16;
	x = x + Width;

	MemAddr = MemAddr + Charctr * 0x20;
	for(Count1 = 0 ; Count1 < Height ; Count1++){
		Data = *MemAddr;
		for(Count2 = 0 ; Count2 < Width ; Count2++){
			if(Data & 1 == 1){
				WritePixel(x, y, Color);
			}
			Data = Data >> 1;
			x--;
		}
		MemAddr++;
		x = x + Width;
		y++;
	}
	for(Count1 = 0 ; Count1 < Height ; Count1++){
		Data = *MemAddr;
		if(Data == 0){
			NullCount++;
		}
		MemAddr++;
	}
	if(NullCount != 16){
		MemAddr = MemAddr - Height;
		for(Count1 = 0 ; Count1 < Height ; Count1++){
			Data = *MemAddr;
			for(Count2 = 0 ; Count2 < Width ; Count2++){
				if(Data & 1 == 1){
					WritePixel(x, y, Color);
				}
				Data = Data >> 1;
				x--;
			}
			MemAddr++;
			x = x + Width;
			y++;
		}
	}

	return 0;
}

int WriteString(int x, int y, char String[], short Color){
	int Count = 0;
	char Data;

	while(1){
		Data = String[Count];
		if(Data == 0){
			break;
		}
		WriteCharacter(x, y, Data, Color);
		x = x + 8;
		Count++;
	}

	return 0;
}


void SetGDT(unsigned char *GDTAddr){
	return;
}
