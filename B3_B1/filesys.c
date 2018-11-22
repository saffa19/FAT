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
	//printf ( "\nwritedisk> virtualdisk[0] = %s\n", virtualDisk[0].data ) ;
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

// move some passed block.data into a block->data for easier referencing
void readblock( diskblock_t * block, int block_address ){
	// basically opposite of writeblock()
	// moves data from the virtualDisk into data property of a block variable
	memmove ( block->data, virtualDisk[block_address].data, BLOCKSIZE ) ;
}

// finds the index of the next entry in entrylist[] that has unused == TRUE
int nextUnusedDirEntry(dirblock_t block){
	for (int i = 0; i < DIRENTRYCOUNT; i++){
		if (block.entrylist[i].unused){
			return i ;
			printf(" \nfree dir entry found at pos %i \n", i);
		}
	}
	// no more space in entrylist
	return -1 ;
}

// finds the index of the next UNUSED block
// terminates execution if mem is full
int nextUnusedBlock(){
	for (int pos = 4; pos < MAXBLOCKS; pos++){
		if (FAT[pos] == UNUSED){
			return pos ;
			printf("found an unused block!\n") ;
		}
	}
	printf("\nThe disk is full\n") ;
	// kill the program
	exit(0) ;
	// no blocks left
	return -1 ;
}


// checks to see if a file with same filename exists in diskblock
int fileExists(dirblock_t block, const char *filename){
	int pos ;
	for (int pos = 0; pos < DIRENTRYCOUNT; pos++){
		if (!(block.entrylist[pos].unused) && strcmp(block.entrylist[pos].name, filename) == 0 && block.entrylist[pos].isdir == 0){
			return pos;
		}
	}
	// file with that name doesn't exist in dirblock
	return -1 ;
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

void copyFAT(){
	int fatblocksneeded = (MAXBLOCKS / FATENTRYCOUNT) ;
	diskblock_t block ;
	int index = 0 ;
	// 2: fat blocks needed
	for (int i = 0; i < fatblocksneeded; i++){
		// 512: number of fat entries in one block
		for (int j = 0; j < FATENTRYCOUNT; j++){
			block.fat[j] = FAT[index++] ;
		}
	writeblock(&block, i + 1) ;
	}
}

// in: disk_name
void format(char * disk_name){
	diskblock_t block ;
	direntry_t  rootDir ;
	int         pos             = 0 ;
	int         fatentry        = 0 ;
	int         fatblocksneeded =  (MAXBLOCKS / FATENTRYCOUNT) ;

	// prepare block 0
	for (int i = 0; i < BLOCKSIZE; i++) block.data[i] = '\0' ;

	memcpy( block.data,	disk_name, strlen(disk_name)) ;
	writeblock(&block, 0) ;

	// all other blocks are UNUSED
	for (int i = 0 ; i < MAXBLOCKS; i++) FAT[i] = UNUSED ;

	// block 0, fatblock, rootblock and end of chain
	FAT[0] = ENDOFCHAIN ;
	FAT[1] = 2 ;
	FAT[2] = ENDOFCHAIN ;
	FAT[3] = ENDOFCHAIN ;

	// implement a function copyFAT (also saves the FAT)
	copyFAT() ;

	// prepare root block
	// clearing block data for use 
	for (int i = 0; i < BLOCKSIZE; i++) block.data[i] = '\0' ;
	  
	// set directory entries to empty 
	for (int i = 0; i < DIRENTRYCOUNT; i++) block.dir.entrylist[i].unused = TRUE ;
	
	// directory block
	block.dir.isdir = 1 ;

	// first element in the entrylist
	block.dir.nextEntry = 0 ;
	
	// write root block to disk
	writeblock(&block, fatblocksneeded + 1) ;
	rootDirIndex = fatblocksneeded + 1 ;
	currentDirIndex = rootDirIndex ;
}

// in: filename, mode(r/w)
MyFILE * myfopen(const char *filename, const char * mode){	// from official C library function

	// should probably check if there's a fakefile with the same name before writing anything

	dirblock_t blockToBeWritten ;
	diskblock_t dirblock ;
	int pos ;

	// allocate memory
	MyFILE * fakefile = malloc(sizeof(MyFILE)) ;
	memcpy(fakefile -> mode, mode, strlen(mode)) ;
	
	// the direntry block
	dirblock = virtualDisk[rootDirIndex] ;
	
	// check if fakefile is already in dirblock
	pos = fileExists(dirblock.dir, filename) ;

	if (pos != -1){
		// starts blockchain for fakeFile, populates first block with current info
		fakefile -> blockno = dirblock.dir.entrylist[pos].firstblock;
	
		// file always starts at the beginning of the block
		fakefile -> pos = 0 ;

	} else {
		
		// looks for a free fat entry
		pos = nextUnusedBlock() ;
		// looks for an empty dir in dirblock entrylist[]
		int i = nextUnusedDirEntry(dirblock.dir) ;
				
		FAT[pos] = ENDOFCHAIN ;
		
		// set position of fakefile blockno and entrylist
		fakefile -> blockno = pos ;
		dirblock.dir.entrylist[i].firstblock = pos ;
		
		// write to FAT
		copyFAT() ;
	
		// direntry.name is the fakeFile name and fakeFile now occupies this direntry
		strcpy(dirblock.dir.entrylist[i].name, filename) ;
		dirblock.dir.entrylist[i].unused = FALSE ;
		
		// write to dirblock
		writeblock(&dirblock, 3) ;
	}
	return fakefile ;
}

// in: chars, an open file
void myfputc(int b, MyFILE *stream){		// from official C library function
	// writes byte to file
	// buffer has size BLOCKSIZE
	// if the pos is greater than (or equal to) the buffer size: we'll have to save the buffer
	// to block, empty the buffer and set pos = 0 before continuing
	
	if (strcmp(stream -> mode, "w") != 0){
		// can't put chars if the file isn't opened in write mode
		return ;
	
	} else {

		int fatIndex ;		// which fat block are you in?
		int i ;				// i gets recycled for multiple purposes

		// pos can't be larger than buffer
		if (stream -> pos >= BLOCKSIZE){
			// looks for a free fat entry
			i = nextUnusedBlock() ;			
			FAT[fatIndex] = i ;
			FAT[i] = ENDOFCHAIN ;
			copyFAT() ;

			// empty the buffer
			for (i = 0; i < MAXBLOCKS; i++) stream -> buffer.data[i] = '\0' ;
			// reset pos
			stream -> pos = 0 ;
		}

		// setting start position of file
		fatIndex = stream->blockno ; 
		
		// loops until the position is ENDOFCHAIN (for the current file)
		while (1){
			if (FAT[fatIndex] == ENDOFCHAIN){
				break ;
			} else {
				fatIndex = FAT[fatIndex] ;
			}
		}
		
		// buffer is final block
		stream -> buffer = virtualDisk[fatIndex] ;
		
		// sets pos to the last character in the current file
		for (i = 0; i < BLOCKSIZE; i++){
			if (stream -> buffer.data[i] == '\0'){
				stream -> pos = i ;
				break ;
			}
		}
		
		// write byte from stream to buffer at pos specified above
		stream -> buffer.data[stream -> pos] = b ;
		// increment pos (next char will get put after this one)
		stream -> pos++ ;
		// write the buffer block to disk
		writeblock(&stream -> buffer, fatIndex) ;
	}
}

// in: an open file
int myfgetc(MyFILE *stream){		// from official C library function
	// checking for stream->mode wasn't working :(
	/*
	if (!(strcmp(stream -> mode, "r") == 0)){
		// can't read chars if the file isn't opened in read mode
		return '\0' ;
	}*/
	char gotChar ;

	// If the pos pointer is at the end of a block (pos == BLOCKSIZE).
	// Then reset the pos pointer and set current blockno to last block in FAT blockchain for
	// this file. Return the final char.
	if (stream -> pos == BLOCKSIZE){
		stream -> pos = 0 ;
		stream -> blockno = FAT[stream -> blockno] ;

	} else {	// buffer is current blockno in virtualDisk

		stream -> buffer = virtualDisk[stream->blockno] ;
		gotChar = stream -> buffer.data[stream->pos] ;
		// next char
		stream -> pos ++ ;
	}
	return gotChar ;
}

// in: an open file
void myfclose(MyFILE *stream){		// from official C library function
	free(stream) ;		// unshackle the memory
}

// set all entries in the entrylist for the current block to unused
void clearBlockEntries(int index, diskblock_t * block){
	if (index > rootDirIndex){
		for (int i = 0; i < DIRENTRYCOUNT; i++){
			block->dir.entrylist[i].unused = TRUE ;
		}
	}
}

int mymkdir(char* path){
	// a very naïve implementation
	char str[strlen(path)+1] ;
	strcpy(str,path) ;

	char *token ;
	char *rest = str ;
	int index = rootDirIndex ;


	while ((token = strtok_r(rest, "/" , &rest))){
		int nextBlock ;
		int entry ;

		diskblock_t block = virtualDisk[index] ;
		
		clearBlockEntries(index, &block) ;
		entry = nextUnusedDirEntry(block.dir) ;
		nextBlock = nextUnusedBlock() ;

		//set filename to block
		strcpy(block.dir.entrylist[entry].name, token) ;	

		block.dir.nextEntry = 0 ;
		block.dir.isdir = 1 ;	
		block.dir.entrylist[entry].unused = FALSE ;
		block.dir.entrylist[entry].firstblock = nextBlock ;
		
		FAT[nextBlock] = ENDOFCHAIN ;

		copyFAT() ;
		writeblock(&block,index) ;

		index = nextBlock ;
	}
	return 0 ;
}

// finds a directory according to name: returns the index of the dir
int findDir(dirblock_t block, char* name){
   for (int i = 0; i < block.nextEntry; i++) {
      if (strcmp(name, block.entrylist[i].name) == 0 && block.entrylist[i].isdir == 1) 
         return i;
   }
   return -1;
}

//use this for testing
void printBlock ( int blockIndex )
{
	printf ( "virtualdisk[%d] = %s\n", blockIndex, virtualDisk[blockIndex].data ) ;
}


