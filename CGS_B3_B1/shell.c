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
	// creates the virtual disk
	format("CS3026 Operating Systems Assessment 2018") ;
	
	// makes directories
	char * path = "/myfirstdir/myseconddir/mythirddir" ;
	mymkdir(path) ;

	writedisk("virtualdiskB3_B1_a\0") ;

	// makes file
	MyFILE * fakeFile = myfopen("testfile.txt", "w") ;
	char * string = "ABCDEFGHIJKLMNOPQRSTUVWXYZ" ;
	int i, j ;
	for (i = 0; i < 4*BLOCKSIZE; i++){
		myfputc(string[j], fakeFile) ;
		j++ ;
		if (j == 26) j = 0 ;
	}
	myfputc(EOF, fakeFile) ;
	myfclose(fakeFile) ;

	writedisk("virtualdiskB3_B1_b\0") ;
}

int main(){
	cgsB3_B1() ;
}
