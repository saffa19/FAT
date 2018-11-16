/*
Criteria for D3_D1:

Implement the function format() to create a structure for the virtual disk. Format has to create the FAT and the root directory. Write a test program containing the main() function, and call it “shell.c”.

Your test program shell.c should perform the following three actions:
- call format() to format the virtual disk
- transfer the following text into block 0: “CS3026 Operating Systems Assessment”
- write the virtual disk to a file (call it “virtualdiskD3_D1”).

Include any header files required, in your shell.c (do NOT include any .c files!).
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "filesys.h"

void cgsD3_D1(){
	format("CS3026 Operating Systems Assessment 2018");
	writeDisk("virtualdiskD3_D1\0");
}

void main(){
	cgsD3_D1();
}
