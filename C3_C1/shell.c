/*
Criteria for C3_C1:

Implement the following interface functions:
- myfopen()
- myfputc()
- myfgetc()
- myfclose()

It is assumed that there is only a root directory and that all files are created there. 
Extend your test program shell.c with the following steps:
- create a file “testfile.txt” in your virtual disk: call myfopen ( “testfile.txt”, “w” ) to open this file
- write a text of size 4kb (4096 bytes) to this file, using the function myfputc():
	- in shell.c, create a char array of 4 * BLOCKSIZE, fill it with text and then write it to the virtual file with myfputc()
- close the file with myfclose()
- write the complete virtual disk to a file “virtualdiskC3_C1”
- test myfgetc():
	- openthefileagainonyourvirtualharddisk
	- read out its content with myfgetc() (you may read until the function returns EOF) and, at the same time, print it to the screen
	- write the content to a real file on your real hard disk and call it “testfileC3_C1_copy.txt”
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "filesys.h"

void cgsC3_C1(){
	format("CS3026 Operating Systems Assessment 2018") ;
	writedisk("virtualdiskC3_C1\0") ;
}

int main(){
	cgsC3_C1() ;
}
