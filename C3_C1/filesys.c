/* filesys.c
 * 
 * provides interface to virtual disk
 * 
 */
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "filesys.h"


diskblock_t  virtualDisk [MAXBLOCKS] ;           // define our in-memory virtual, with MAXBLOCKS blocks
fatentry_t   FAT         [MAXBLOCKS] ;           // define a file allocation table with MAXBLOCKS 16-bit entries
fatentry_t   rootDirIndex            = 0 ;       // rootDir will be set by format
direntry_t * currentDir              = NULL ;
fatentry_t   currentDirIndex         = 0 ;

/* writedisk : writes virtual disk out to physical disk
 * 
 * in: file name of stored virtual disk
 */

void writedisk ( const char * filename )
{
	printf ( "writedisk> virtualdisk[0] = %s\n", virtualDisk[0].data ) ;
	FILE * dest = fopen( filename, "w" ) ;
	if ( fwrite ( virtualDisk, sizeof(virtualDisk), 1, dest ) < 0 )
		fprintf ( stderr, "write virtual disk to disk failed\n" ) ;
	//write( dest, virtualDisk, sizeof(virtualDisk) ) ;
	fclose(dest) ;
	
}

void readdisk ( const char * filename )
{
	FILE * dest = fopen( filename, "r" ) ;
	if ( fread ( virtualDisk, sizeof(virtualDisk), 1, dest ) < 0 )
		fprintf ( stderr, "write virtual disk to disk failed\n" ) ;
	//write( dest, virtualDisk, sizeof(virtualDisk) ) ;
		fclose(dest) ;
}

/* the basic interface to the virtual disk
 * this moves memory around
 */

void writeblock ( diskblock_t * block, int block_address )
{
	//printf ( "writeblock> block %d = %s\n", block_address, block->data ) ;
	memmove ( virtualDisk[block_address].data, block->data, BLOCKSIZE ) ;
	//printf ( "writeblock> virtualdisk[%d] = %s / %d\n", block_address, virtualDisk[block_address].data, (int)virtualDisk[block_address].data ) ;
}


/* read and write FAT
 * 
 * please note: a FAT entry is a short, this is a 16-bit word, or 2 bytes
 *              our blocksize for the virtual disk is 1024, therefore
 *              we can store 512 FAT entries in one block
 * 
 *              how many disk blocks do we need to store the complete FAT:
 *              - our virtual disk has MAXBLOCKS blocks, which is currently 1024
 *                each block is 1024 bytes long
 *              - our FAT has MAXBLOCKS entries, which is currently 1024
 *                each FAT entry is a fatentry_t, which is currently 2 bytes
 *              - we need (MAXBLOCKS /(BLOCKSIZE / sizeof(fatentry_t))) blocks to store the
 *                FAT
 *              - each block can hold (BLOCKSIZE / sizeof(fatentry_t)) fat entries
 */

void copyFAT(fatentry_t * FAT, int fatblocksneeded){
	diskblock_t fatblock ;
	unsigned int i, j, k = 0;
	for (i = 1; i <= fatblocksneeded; i++){
		for (j = 0; j < FATENTRYCOUNT; j++){
			fatblock.fat[j] = FAT[k] ;
			k++ ;
		}
	writeblock(&fatblock, i) ;
	}
}


void format(char * disk_name){
	diskblock_t block ;
	direntry_t  rootDir ;
	int         pos             = 0 ;
	int         fatentry        = 0 ;
	int         fatblocksneeded =  (MAXBLOCKS + (FATENTRYCOUNT - 1)) / FATENTRYCOUNT ;

	unsigned int i = 1 ;
	for (int i = 0; i < BLOCKSIZE; i++){
		block.data[i] = '\0' ;
	}	
	memcpy(block.data, disk_name, strlen(disk_name)) ;
	writeblock(&block, 0) ;
	FAT[0] = ENDOFCHAIN ;
	for (i = 1; i < fatblocksneeded; i++){
		FAT[i] = i+1;	//setting FAT[1] = 2
	}
	FAT[fatblocksneeded] = ENDOFCHAIN ; // end of blockchain for FAT table
	FAT[fatblocksneeded + 1] = ENDOFCHAIN ; // root directory
	for(i = fatblocksneeded + 2; i < MAXBLOCKS; i++){ // all other blocks are UNUSED
		FAT[i] = UNUSED ;
	}

	copyFAT(FAT, fatblocksneeded) ;

	diskblock_t rootBlock ;
	rootBlock.dir.isdir = 1 ;
	rootBlock.dir.nextEntry = 0 ;
	rootDirIndex = fatblocksneeded + 1;
	
	// write root directory block to virtual disk
	writeblock(&rootBlock, rootDirIndex) ;
}

// in: filename, mode(r/w), MyFILE?
myfopen(char name, char mode){
	if (mode == 'w'){

	}
}

// in: filename, chars, MyFILE?
myfputc(){

}

// in: filename, MyFILE?
myfgetc(){

}


// in: filename, MyFILE?
myfclose(){

}




//use this for testing

void printBlock ( int blockIndex )
{
	printf ( "virtualdisk[%d] = %s\n", blockIndex, virtualDisk[blockIndex].data ) ;
}


