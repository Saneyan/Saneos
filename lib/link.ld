INPUT(bootloader.o graphic.o gfunction.o memory.o in_output.o)
OUTPUT_FORMAT(binary)

SECTIONS
{
	. = 0x00008400;
	.text : 
	{
		*(.text)
		_LoaderMain = .;
	}
	
	. = 0x00009400;
	.data : 
	{
		*(.data)
	}
	
	.bss : 
	{
		*(.bss)
	}
}