/*

Write a program to copy a file from a source to destination using POSIX API. 
Your program should account for the option to copy directories.
Hints:

    Include fcntl.h 
    system calls to consider: creat, open, read, write, exit
    For directories dirent.h is useful to include, system calls to consider: opendir, readdir
    Do not use standard library (i.e. do not include stdlib.h nor use fopen,....etc. This defies the objective of the assignment. 

What to turn in:
1. Your source code
2. A shell script to compile your source file and execute it
   using at least 4 test cases. (attached is an example)
   
Note: please put all files in a directory, 
zip the directory and submit as one file on blackboard 
or submit on github 

Allowed imports:
filectrl.h
direct.h
stdio.h

*/
