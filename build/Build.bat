@echo off

rem /*********/
rem /* Ready */
rem /*********/

cd ../code/boot


rem /*********************/
rem /* Make object files */
rem /*********************/

rem #boot

rem /* Bootloader */
	g++ -c bootloader.cpp
	move bootloader.o ../../lib

rem /* Global functions */
	nasm -f elf gfunction.asm
	move gfunction.o ../../lib

rem /* Graphic */
	g++ -c graphic.cpp
	move graphic.o ../../lib
	
rem /* Memory */
	g++ -c memory.cpp
	move memory.o ../../lib
	
rem /* In/Output */
	g++ -c in_output.cpp
	move in_output.o ../../lib


rem /********/
rem /* Link */
rem /********/

rem /* Link */
	cd ../../lib
	ld -nostdlib -s -o bootloader.sos link.ld
	move bootloader.sos ../bin


rem /**********/
rem /* Others */
rem /**********/

	cd ../code

rem /* Database */
	nasm -o database.sos database.asm
	move database.sos ../bin
	
rem /* Test data */
	nasm -o test_data.sos test_data.asm
	move test_data.sos ../bin

	cd boot
	
rem /* Starter */
	nasm -o starter.sos starter.asm
	move starter.sos ../../bin
	
	cd ../font
	
rem /* System font */
	nasm -o system.sfn system.asm
	move system.sfn ../../bin
	
	cd ../../bin


rem /*********/
rem /* Build */
rem /*********/

rem /* Build Saneos image */
	nasm -o Saneos.img Build.asm
	move Saneos.img ../installer
	
	
rem /**********/
rem /* Return */
rem /**********/

	cd ../build