/*
Criteria for B3_B1:

Add a directory hierarchy to your virtualdisk that allows the creation of subdirectories. 
Implement the following interface functions:
- mymkdir( char * path) that creates a new directory
- char ** mylistdir (char * path) that lists the content of a directory

Extend your test program shell.c with the following test steps:
- create a directory “/myfirstdir/myseconddir/mythirddir” in the virtual disk
- call mylistdir(“/myfirstdir/myseconddir”): print out the list of strings returned by this function
- write out virtual disk to “virtualdiskB3_B1_a”
- create a file “/myfirstdir/myseconddir/testfile.txt” in the virtual disk
- call mylistdir(“/myfirstdir/myseconddir”): print out the list of strings returned by this function
- write out virtual disk to “virtualdiskB3_B1_b”
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "filesys.h"

void cgsB3_B1(){
/*	format("CS3026 Operating Systems Assessment 2018") ;
	writedisk("virtualdiskD3_D1\0") ;
	
	// create a fake file "testfile.txt" in your virtual disk
	MyFILE * fakeFile = myfopen("testfile.txt", "w") ;
	//writedisk("virtualdiskC3_C1\0") ;
	
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
*/
	format("Block 0") ;
	
	// it should be easier to add the directories like this.
	// can pull only last element of the path, check if it's a directory,
	mymkdir("/myfirstdir") ;
	mymkdir("/myfirstdir/myseconddir") ;
	mymkdir("/myfirstdir/myseconddir/mythirddir") ;
	
	char** list ;
	list = mylistdir("/myfirstdir/myseconddir") ;

	writedisk("virtualdiskB3_B1_a\0") ;



	writedisk("virtualdiskB3_B1_b\0") ;





}

int main(){
	cgsB3_B1() ;
}
