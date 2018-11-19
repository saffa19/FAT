## Implementing a FAT in C

### Changing some things I probably shouldn't:

- commented out line 29 in filesys.h because it was messing with C's built in definition of EOF (#define EOF           -1)

### bugs

- sometimes C3_C1 doesn't execute properly when it's already been compiled, run and all the produced files are there. For best results, delete runtime files before you recompile (if you want to test multiple times).