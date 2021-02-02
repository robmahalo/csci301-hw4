#include <fcntl.h>
#include <dirent.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {

    // File descriptor
    int fd;
    char filename[100];

    // Directory
    DIR *dir;
    char dirname[100];

    // Structure
    struct dirent *sd;

    mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
    char buffer[80];
    char msg[50];

    /* Create a file */

    printf("Enter a file name: ");
    scanf("%s", filename);

    fd = creat(filename, mode);

    /* Open a file */

    fd = open (filename, O_RDWR, mode);

    printf("fd = %d", fd);

    if (fd != -1) {

        printf("\n The file was successfully opened and given read and write access");
        
        /* Write something on the file */

        printf("\nEnter text you want to add to the file: ");
        scanf("%s", msg);

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

    printf("Enter the name of a directory: ");
    scanf("%s", dirname);

    dir = opendir(dirname);

    if (dir == NULL) {
        printf("Error: Unable to find directory");
    }

    /* Read a directory */

    while( (sd = readdir(dir)) != NULL) {
        printf(">> %s\n", sd -> d_name);

    }

    /* Close directory */

    closedir(dir);

    return 0;
}