## Implementing a FAT in C

### Dev environment

- env: MAC OS 10.13.x
- language: C99
- compiler: gcc

### D3_D1

- change directory into one of the grade range folders `cd D3_D1`
- run the Makefile
- assuming everything works, you should see a few things appear in your terminal
```
$ make
gcc -o shell shell.c filesys.c
./shell

hexdump -C virtualdiskD3_D1
00000000  43 53 33 30 32 36 20 4f  70 65 72 61 74 69 6e 67  |CS3026 Operating|
00000010  20 53 79 73 74 65 6d 73  20 41 73 73 65 73 73 6d  | Systems Assessm|
00000020  65 6e 74 20 32 30 31 38  00 00 00 00 00 00 00 00  |ent 2018........|
00000030  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
*
00000400  00 00 02 00 00 00 00 00  ff ff ff ff ff ff ff ff  |................|
00000410  ff ff ff ff ff ff ff ff  ff ff ff ff ff ff ff ff  |................|
*
00000c00  01 00 00 00 00 00 00 00  00 00 00 00 00 01 00 00  |................|
00000c10  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
*
00000d20  00 00 00 00 00 01 00 00  00 00 00 00 00 00 00 00  |................|
00000d30  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
*
00000e30  00 00 00 00 00 00 00 00  00 00 00 00 00 01 00 00  |................|
00000e40  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
*
00100000
```
- Block 0: addresses 0x000 to 0x3ff (0000-1023). Block 0 is the sacred block.
- Block 1: addresses 0x400 to 0x7ff (1024-2047). Occupied by the FAT blockchain. 
- Block 2: addresses 0x800 to 0xbff (2048-3071). Occupied by the FAT blockchain.
- Block 3: addresses 0xc00 to 0xfff (3072-4095). The root directory.

#### You can see the FAT at 0x400:
- the first `00 00` is the value in FAT entry for block 0 (FAT[0]), set to ENDOFCHAIN
- the next `02 00` is the value in FAT entry for block 1 (FAT[1]), set to 2 (this is the index of `FAT[2]`)
- the next `00 00` is the value in FAT entry for block 2 (FAT[2]), set to ENDOFCHAIN (end of FAT table's blockchain)
- the next `00 00` is the value in FAT entry for block 3 (FAT[3]), set to ENDOFCHAIN (the root
directory)
- the rest remains UNUSED, which is -1 or 0xff

#### You can see the block for the root directory at 0xc00:
- the first `01 00` is the value stored in "isDir" of dirblock_t `block.dir.isdir = 1`
- the rest of the block is initialized to '\0'
- the `00 01`'s scattered in the rest of the root directory are where I've set the `dir.entrylist[i].unused = TRUE`

### C3_C1

- change directory into one of the grade range folders `cd C3_C1`
- run the Makefile
- assuming everything works, you should see a few things appear in your terminal
```
$ make
gcc -o shell shell.c filesys.c
./shell

This is the content of testfileC3_C1_copy.txt:
BCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOP
QRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDE
FGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRST
UVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHI

```
<p align="center">...you get it, alphabet on loop for 4kb...</p>

```
JKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWX
YZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLM
NOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZAB
CDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMN

hexdump -C virtualdiskC3_C1
00000000  43 53 33 30 32 36 20 4f  70 65 72 61 74 69 6e 67  |CS3026 Operating|
00000010  20 53 79 73 74 65 6d 73  20 41 73 73 65 73 73 6d  | Systems Assessm|
00000020  65 6e 74 20 32 30 31 38  00 00 00 00 00 00 00 00  |ent 2018........|
00000030  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
*
00000400  00 00 02 00 00 00 00 00  05 00 06 00 07 00 08 00  |................|
00000410  00 00 ff ff ff ff ff ff  ff ff ff ff ff ff ff ff  |................|
00000420  ff ff ff ff ff ff ff ff  ff ff ff ff ff ff ff ff  |................|
*
00000c00  01 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
00000c10  00 00 00 00 00 00 00 00  00 00 00 00 04 00 74 65  |..............te|
00000c20  73 74 66 69 6c 65 2e 74  78 74 00 00 00 00 00 00  |stfile.txt......|
00000c30  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
*
00000d20  00 00 00 00 00 01 00 00  00 00 00 00 00 00 00 00  |................|
00000d30  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
*
00000e30  00 00 00 00 00 00 00 00  00 00 00 00 00 01 00 00  |................|
00000e40  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
*
00001000  41 42 43 44 45 46 47 48  49 4a 4b 4c 4d 4e 4f 50  |ABCDEFGHIJKLMNOP|
00001010  51 52 53 54 55 56 57 58  59 5a 41 42 43 44 45 46  |QRSTUVWXYZABCDEF|
00001020  47 48 49 4a 4b 4c 4d 4e  4f 50 51 52 53 54 55 56  |GHIJKLMNOPQRSTUV|
00001030  57 58 59 5a 41 42 43 44  45 46 47 48 49 4a 4b 4c  |WXYZABCDEFGHIJKL|
00001040  4d 4e 4f 50 51 52 53 54  55 56 57 58 59 5a 41 42  |MNOPQRSTUVWXYZAB|
00001050  43 44 45 46 47 48 49 4a  4b 4c 4d 4e 4f 50 51 52  |CDEFGHIJKLMNOPQR|
00001060  53 54 55 56 57 58 59 5a  41 42 43 44 45 46 47 48  |STUVWXYZABCDEFGH|
00001070  49 4a 4b 4c 4d 4e 4f 50  51 52 53 54 55 56 57 58  |IJKLMNOPQRSTUVWX|
00001080  59 5a 41 42 43 44 45 46  47 48 49 4a 4b 4c 4d 4e  |YZABCDEFGHIJKLMN|
00001090  4f 50 51 52 53 54 55 56  57 58 59 5a 41 42 43 44  |OPQRSTUVWXYZABCD|
000010a0  45 46 47 48 49 4a 4b 4c  4d 4e 4f 50 51 52 53 54  |EFGHIJKLMNOPQRST|
000010b0  55 56 57 58 59 5a 41 42  43 44 45 46 47 48 49 4a  |UVWXYZABCDEFGHIJ|
000010c0  4b 4c 4d 4e 4f 50 51 52  53 54 55 56 57 58 59 5a  |KLMNOPQRSTUVWXYZ|
```
<p align="center">...a few lines later...</p>

```
00001f50  55 56 57 58 59 5a 41 42  43 44 45 46 47 48 49 4a  |UVWXYZABCDEFGHIJ|
00001f60  4b 4c 4d 4e 4f 50 51 52  53 54 55 56 57 58 59 5a  |KLMNOPQRSTUVWXYZ|
00001f70  41 42 43 44 45 46 47 48  49 4a 4b 4c 4d 4e 4f 50  |ABCDEFGHIJKLMNOP|
00001f80  51 52 53 54 55 56 57 58  59 5a 41 42 43 44 45 46  |QRSTUVWXYZABCDEF|
00001f90  47 48 49 4a 4b 4c 4d 4e  4f 50 51 52 53 54 55 56  |GHIJKLMNOPQRSTUV|
00001fa0  57 58 59 5a 41 42 43 44  45 46 47 48 49 4a 4b 4c  |WXYZABCDEFGHIJKL|
00001fb0  4d 4e 4f 50 51 52 53 54  55 56 57 58 59 5a 41 42  |MNOPQRSTUVWXYZAB|
00001fc0  43 44 45 46 47 48 49 4a  4b 4c 4d 4e 4f 50 51 52  |CDEFGHIJKLMNOPQR|
00001fd0  53 54 55 56 57 58 59 5a  41 42 43 44 45 46 47 48  |STUVWXYZABCDEFGH|
00001fe0  49 4a 4b 4c 4d 4e 4f 50  51 52 53 54 55 56 57 58  |IJKLMNOPQRSTUVWX|
00001ff0  59 5a 41 42 43 44 45 46  47 48 49 4a 4b 4c 4d 4e  |YZABCDEFGHIJKLMN|
00002000  ff 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
00002010  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
*
00100000
```
#### So what's going on here?
- the first `00 00` is the value in FAT entry for block 0 (FAT[0]), set to ENDOFCHAIN
- the next `02 00` is the value in FAT entry for block 1 (FAT[1]), set to 2 (this is the index of `FAT[2]`)
- the next `00 00` is the value in FAT entry for block 2 (FAT[2]), set to ENDOFCHAIN (end of FAT table's blockchain)
- the next `00 00` is the value in FAT entry for block 3 (FAT[3]), set to ENDOFCHAIN (the root
directory)
- the rest remains UNUSED, which is -1 or 0xff

### B3_B1

- change directory into one of the grade range folders `cd B3_B1`
- run the Makefile
- assuming everything works, you should see a few things appear in your terminal
```
$ make
gcc -o shell shell.c filesys.c
./shell

hexdump -C virtualdiskB3_B1_a
hexdump -C virtualdiskB3_B1_a
00000000  43 53 33 30 32 36 20 4f  70 65 72 61 74 69 6e 67  |CS3026 Operating|
00000010  20 53 79 73 74 65 6d 73  20 41 73 73 65 73 73 6d  | Systems Assessm|
00000020  65 6e 74 20 32 30 31 38  00 00 00 00 00 00 00 00  |ent 2018........|
00000030  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
*
00000400  00 00 02 00 00 00 00 00  05 00 06 00 07 00 00 00  |................|
00000410  ff ff ff ff ff ff ff ff  ff ff ff ff ff ff ff ff  |................|
*
00000c00  01 00 00 00 00 00 00 00  00 00 00 00 00 01 00 00  |................|
00000c10  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
*
00000d20  00 00 00 00 00 01 00 00  00 00 00 00 00 00 00 00  |................|
00000d30  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
*
00000e30  00 00 00 00 00 00 00 00  00 00 00 00 00 01 00 00  |................|
00000e40  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
*
00001000  01 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
00001010  00 00 00 00 00 00 00 00  00 00 00 00 05 00 6d 79  |..............my|
00001020  66 69 72 73 74 64 69 72  00 00 00 00 00 00 00 00  |firstdir........|
00001030  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
*
00001120  00 00 00 00 00 01 00 00  00 00 00 00 00 00 00 00  |................|
00001130  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
*
00001230  00 00 00 00 00 00 00 00  00 00 00 00 00 01 00 00  |................|
00001240  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
*
00001400  01 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
00001410  00 00 00 00 00 00 00 00  00 00 00 00 06 00 6d 79  |..............my|
00001420  73 65 63 6f 6e 64 64 69  72 00 00 00 00 00 00 00  |seconddir.......|
00001430  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
*
00001520  00 00 00 00 00 01 00 00  00 00 00 00 00 00 00 00  |................|
00001530  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
*
00001630  00 00 00 00 00 00 00 00  00 00 00 00 00 01 00 00  |................|
00001640  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
*
00001800  01 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
00001810  00 00 00 00 00 00 00 00  00 00 00 00 07 00 6d 79  |..............my|
00001820  74 68 69 72 64 64 69 72  00 00 00 00 00 00 00 00  |thirddir........|
00001830  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
*
00001920  00 00 00 00 00 01 00 00  00 00 00 00 00 00 00 00  |................|
00001930  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
*
00001a30  00 00 00 00 00 00 00 00  00 00 00 00 00 01 00 00  |................|
00001a40  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
*
00100000

hexdump -C virtualdiskB3_B1_b
00000000  43 53 33 30 32 36 20 4f  70 65 72 61 74 69 6e 67  |CS3026 Operating|
00000010  20 53 79 73 74 65 6d 73  20 41 73 73 65 73 73 6d  | Systems Assessm|
00000020  65 6e 74 20 32 30 31 38  00 00 00 00 00 00 00 00  |ent 2018........|
00000030  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
*
00000400  00 00 02 00 00 00 00 00  05 00 06 00 07 00 00 00  |................|
00000410  09 00 0a 00 0b 00 0c 00  00 00 ff ff ff ff ff ff  |................|
00000420  ff ff ff ff ff ff ff ff  ff ff ff ff ff ff ff ff  |................|
*
00000c00  01 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
00000c10  00 00 00 00 00 00 00 00  00 00 00 00 08 00 74 65  |..............te|
00000c20  73 74 66 69 6c 65 2e 74  78 74 00 00 00 00 00 00  |stfile.txt......|
00000c30  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
*
00000d20  00 00 00 00 00 01 00 00  00 00 00 00 00 00 00 00  |................|
00000d30  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
*
00000e30  00 00 00 00 00 00 00 00  00 00 00 00 00 01 00 00  |................|
00000e40  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
*
00001000  01 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
00001010  00 00 00 00 00 00 00 00  00 00 00 00 05 00 6d 79  |..............my|
00001020  66 69 72 73 74 64 69 72  00 00 00 00 00 00 00 00  |firstdir........|
00001030  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
*
00001120  00 00 00 00 00 01 00 00  00 00 00 00 00 00 00 00  |................|
00001130  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
*
00001230  00 00 00 00 00 00 00 00  00 00 00 00 00 01 00 00  |................|
00001240  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
*
00001400  01 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
00001410  00 00 00 00 00 00 00 00  00 00 00 00 06 00 6d 79  |..............my|
00001420  73 65 63 6f 6e 64 64 69  72 00 00 00 00 00 00 00  |seconddir.......|
00001430  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
*
00001520  00 00 00 00 00 01 00 00  00 00 00 00 00 00 00 00  |................|
00001530  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
*
00001630  00 00 00 00 00 00 00 00  00 00 00 00 00 01 00 00  |................|
00001640  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
*
00001800  01 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
00001810  00 00 00 00 00 00 00 00  00 00 00 00 07 00 6d 79  |..............my|
00001820  74 68 69 72 64 64 69 72  00 00 00 00 00 00 00 00  |thirddir........|
00001830  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
*
00001920  00 00 00 00 00 01 00 00  00 00 00 00 00 00 00 00  |................|
00001930  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
*
00001a30  00 00 00 00 00 00 00 00  00 00 00 00 00 01 00 00  |................|
00001a40  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
*
00002000  41 42 43 44 45 46 47 48  49 4a 4b 4c 4d 4e 4f 50  |ABCDEFGHIJKLMNOP|
00002010  51 52 53 54 55 56 57 58  59 5a 41 42 43 44 45 46  |QRSTUVWXYZABCDEF|
00002020  47 48 49 4a 4b 4c 4d 4e  4f 50 51 52 53 54 55 56  |GHIJKLMNOPQRSTUV|
```
<p align="center">...a few lines later...</p>

```
00002fd0  53 54 55 56 57 58 59 5a  41 42 43 44 45 46 47 48  |STUVWXYZABCDEFGH|
00002fe0  49 4a 4b 4c 4d 4e 4f 50  51 52 53 54 55 56 57 58  |IJKLMNOPQRSTUVWX|
00002ff0  59 5a 41 42 43 44 45 46  47 48 49 4a 4b 4c 4d 4e  |YZABCDEFGHIJKLMN|
00003000  ff 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
00003010  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
*
00100000
```

### Changing some things I probably shouldn't:

- commented out line 29 in filesys.h because it was messing with C's built in definition of EOF 
- `//#define EOF           -1`

### BUGS

- sometimes C3_C1 doesn't execute properly when it's already been compiled, run and all the produced files are there. For best results, delete runtime files before you recompile (if you want to test multiple times).