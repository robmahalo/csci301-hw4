#include <fcntl.h>
#include <dirent.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {

    // File descriptor
    int fd;

    // Directory
    DIR *dir;

    // Structure
    struct dirent *sd;

    mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
    char *filename = "file1.txt";
    char buffer[80];
    char msg[50] = "Hello CSCI 301!";

    /* Create a file */

    fd = creat(filename, mode);

    /* Open a file */

    fd = open ("file1.txt", O_RDWR);

    printf("fd = %d", fd);

    if (fd != -1) {

        printf("\n file1.txt was opened with read and write access");
        
        /* Write something on the file */

        write(fd, msg, sizeof(msg));
        lseek(fd, 0, SEEK_SET);

        /* Read the file */
        
        read(fd, buffer, sizeof(msg));
        printf("\n %s was written to the file\n", buffer);

        /* Close the file */
        
        close(fd);

    } else {

        printf("Error: File failed to open");

    }

    /* Open a directory */

    dir = opendir(".");

    if (dir == NULL) {
        print("Error: Unable to find directory");
        exit(1);
    }

    /* Read a directory */

    while( (sd = readdir(dir)) != NULL) {
        printf(">> %s\n", sd -> d_name);

    }

    /* Close directory */

    closedir(dir);

    return 0;
}