#include <fcntl.h>
#include <dirent.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

/* Copy source file to destination */

int copy(char * source, char * dest)
{
	int fd_input, fd_output, rval;
	off_t n_bytes = 0;
	struct stat s_stat = {0};
	
	if ((fd_input = open(source, O_RDONLY)) == -1)
	{
		return -1;
	}
	if ((fd_output = creat(dest, 0660)) == -1)
	{
		close(fd_input);
		return -1;
	}
	
	fstat(fd_input, &s_stat);
	rval = sendfile(fd_output, fd_input, &n_bytes, s_stat.st_size);

	close(fd_input);
	close(fd_output);

	return rval;
}

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
    char msg[100];

    /* Create a file */

    printf("Enter a file name: ");
    scanf("%s", filename);

    fd = creat(filename, mode);

    /* Open a file */

    fd = open (filename, O_RDWR, mode);

    printf("fd = %d", fd);

    if (fd != -1) {

        printf("\n The file was successfully opened and given read and write access.");
        
        /* Write something on the file */

        printf("\nEnter text you want to add to the file: ");
        scanf("%s", msg);

        write(fd, msg, sizeof(msg));
        lseek(fd, 0, SEEK_SET);

        /* Read the file */
        
        read(fd, buffer, sizeof(msg));
        printf("%s was written to the file\n", buffer);

        /* Close the file */
        
        close(fd);

    } else {

        printf("\nError: File failed to open.");

    }

    /* Open a directory */

    printf("Enter the name of a directory: ");
    scanf("%s", dirname);

    dir = opendir(dirname);

    if (dir == NULL) {
        printf("Error: Unable to find directory.");
    }

    /* Read a directory */

    while( (sd = readdir(dir)) != NULL) {
        printf(">> %s\n", sd -> d_name);

    }

    /* Copy file to a destination */

    char inpath[100];
    char destpath[100];

    printf("\nEnter the path of the file you want to copy: ");
    scanf("%s", destpath);

    printf("\nEnter the path you want to copy your file to: ");
    scanf("%s", destpath);

    copy(inpath, destpath);


    /* Close directory */

    closedir(dir);

    return 0;
}