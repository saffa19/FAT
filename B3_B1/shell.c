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
	- open the file again on your virtual hard disk
	- read out its content with myfgetc() (you may read until the function returns EOF) and, at the same time, print it to the screen
	- write the content to a real file on your real hard disk and call it “testfileC3_C1_copy.txt”
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "filesys.h"

void cgsB3_B1(){
	format("CS3026 Operating Systems Assessment 2018") ;
	writedisk("virtualdiskD3_D1\0") ;
	
	// create a fake file "testfile.txt" in your virtual disk
	MyFILE * fakeFile = myfopen("testfile.txt", "w") ;
	writedisk("virtualdiskC3_C1\0") ;
	
	// write body of text (4096 bytes) to the fake file
	char * string = "ABCDEFGHIJKLMNOPQRSTUVWXYZ" ;
	int i, j;
	for (i = 0; i < 4*BLOCKSIZE; i++){
		myfputc(string[j], fakeFile) ;
		j++ ;
		if (j == 26) j = 0;
	}
	myfputc(EOF, fakeFile) ;
	
	// close the fake file
	myfclose(fakeFile) ;

	// write the complete virtual disk to a file virtualdiskC3_C1
	writedisk("virtualdiskC3_C1\0") ;

	// open the file on the virtual disk
	myfopen("fakeFile", "r") ;

	// open a file to be written to local hard disk
	FILE * realFile;
	char lastcharacter ;
	realFile = fopen("testfileC3_C1_copy.txt", "w");

	// print out fakeFile's content to the screen and save it to testfileC3_C1_copy.txt
	printf("This is the content of testfileC3_C1_copy.txt:\n") ;
	while (lastcharacter != EOF){
		lastcharacter = myfgetc(fakeFile) ;
		if (lastcharacter != EOF){
			printf("%c", lastcharacter);
			fprintf(realFile, "%c",lastcharacter);
		}
	}
	printf("\n\n") ;

	format("CS3026 Operating Systems Assessment 2018") ;
	writedisk("virtualdiskB3_B1\0") ;





}

int main(){
	cgsB3_B1() ;
}
