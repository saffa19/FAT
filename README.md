## Implementing a FAT in C

### Prerequisites

- env: MAC OS 10.13.x
- language: C99
- compiler: gcc

### How to run

- change directory into one of the grade range folders
- `cd D3_D1`
- run the Makefile. Assuming everything works, you should see a few things appear in your terminal:
1. gcc -o shell shell.c filesys.c
2. ./shell
3. hexdump -C virtualdiskD3_D1
- these are all commands I've put in the Makefile
- you should also see the hexdump -C of the virtualdisk produced by my code

### Changing some things I probably shouldn't:

- commented out line 29 in filesys.h because it was messing with C's built in definition of EOF 
- `//#define EOF           -1`

### bugs

- sometimes C3_C1 doesn't execute properly when it's already been compiled, run and all the produced files are there. For best results, delete runtime files before you recompile (if you want to test multiple times).