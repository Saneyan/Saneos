//
// Copyright (c) 2010 Saneyuki. All rights reserved.
//


extern "C" {
#define Byte 0x01
#define Word 0x02
#define DWord 0x03
#define NML 0x00
#define AND 0x01
#define OR 0x02
#define XOR 0x03
#define NOT 0x04

	int LoaderMain(void);
	void Error(void);
	void ISR(void);
	void Int20Handler(void);
	int LGDT(struct GDTR *GDTRAddr);
	int LIDT(struct IDTR *IDTRAddr);
	void SetGDT(struct GDT *GDT_PO, unsigned long BaseAddr, unsigned int SegLimit, short Option);
	void SetIDT(struct IDT *IDT_PO, unsigned long Offset, unsigned short Selctr, unsigned char DescType);
	void SetDefaultGDT(unsigned char *GDTAddr);
	void SetDefaultIDT(unsigned char *IDTAddr);

	struct GDT{
		unsigned short SegLimitL;
		unsigned short BaseAddrL;
		unsigned char BaseAddrM;
		unsigned char T_S_DPL_P;
		unsigned char SLH_AVL_R_DB_G;
		unsigned char BaseAddrH;
	};
	struct GDTR{
		unsigned short Limit;
		unsigned long BaseAddr;
	};
	struct IDT{
		unsigned short OfsL;
		unsigned short Selctr;
		unsigned char Res;
		unsigned char DescType;
		unsigned short OfsH;
	};
	struct IDTR{
		unsigned short Limit;
		unsigned long BaseAddr;
	};
	struct Graphic{
		unsigned char *VRAMAddr;
	};

	void WriteData(unsigned char *MemAddr, int Data, int Bitwise, int WriType, char Value);
	void WriteDataNML(unsigned char *MemAddr, int Data, int DataLimit);
	void WriteDataAND(unsigned char *MemAddr, int Data, int DataLimit);
	void WriteDataOR(unsigned char *MemAddr, int Data);
	void WriteDataXOR(unsigned char *MemAddr, int Data);
	void WriteDataNOT(unsigned char *MemAddr, int Data, int DataLimit);

	int GetData(unsigned int MemAddr, char Value);
	int GetDataNML(unsigned int MemAddr, int DataLimit);

	void MemoryCopy(unsigned char *MemAddr1, unsigned char *MemAddr2, int Count);

	int WritePixel(int x, int y, short Color);
	int WriteCharacter(int x, int y, int Carctr, short Color);
	int WriteString(int x, int y, char String[], short Color);
	int DrawLine(int x1, int y1, int x2, int y2, short Color);

	int Input(short Inport, char Value);
	char InputB(short Inport);
	short InputW(short Inport);
	int InputD(short Inport);

	void Output(short Outport, int Data, char Value);
	void OutputB(short Outport, char Data);
	void OutputW(short Outport, short Data);
	void OutputD(short Outport, int Data);

	void HaltProcessor(void);
	void SetIntFlug(void);
	void ClearIntFlug(void);
	void NoOperation(void);
	void IRET(void);
}
