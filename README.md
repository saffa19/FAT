## Implementing a FAT in C

### Prerequisites

- env: MAC OS 10.13.x
- language: C99
- compiler: gcc

### How to run D3_D1

- change directory into one of the grade range folders `cd D3_D1`
- run the Makefile
- assuming everything works, you should see a few things appear in your terminal
```
$ make
gcc -o shell shell.c filesys.c
./shell
writedisk> virtualdisk[0] = CS3026 Operating Systems Assessment 2018
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

### How to run C3_C1

- change directory into one of the grade range folders `cd C3_C1`
- run the Makefile
- assuming everything works, you should see a few things appear in your terminal
```
$ make
gcc -o shell shell.c filesys.c
./shell
writedisk> virtualdisk[0] = CS3026 Operating Systems Assessment 2018
writedisk> virtualdisk[0] = CS3026 Operating Systems Assessment 2018
writedisk> virtualdisk[0] = CS3026 Operating Systems Assessment 2018
This is the content of testfileC3_C1_copy.txt:
BCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKL
```
<p align="center">...you get it, alphabet on loop for 4kb...</p>

```
#hexdump -C virtualdiskD3_D1
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
<p align="center">...some time later...</p>

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

### Changing some things I probably shouldn't:

- commented out line 29 in filesys.h because it was messing with C's built in definition of EOF 
- `//#define EOF           -1`

### BUGS

- sometimes C3_C1 doesn't execute properly when it's already been compiled, run and all the produced files are there. For best results, delete runtime files before you recompile (if you want to test multiple times).