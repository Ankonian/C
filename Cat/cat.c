#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
int main(int argc, char *argv[])
{

	int fileDescriptor; //declare file descriptor to return a value for standard input, output, and error
	ssize_t br; //declare a signed variable for bytes of char that are read
	uint8_t buffer[4096]; //buffer size of how many chars are read one at a time
	ssize_t bw; // declare a signed variable for bytes of char that are written
	if(argc < 2)
	{

	}
	else
	{
		for(int i = 1; i < argc; i++) // as long as there's still files to read, keep reading
		{
			fileDescriptor = open(argv[i], O_RDONLY); //assign value to the file descriptor
			while((br = read (fileDescriptor, buffer, 4096)) > 0){ //while the bytes read did not reach the end of file, keep reading the file
            			bw = write (1, buffer, br); //assign write value to bytes written
            			if(bw != br)
				{
                			perror("cat");
					exit(errno);
                			return 2;
            			}
    			}
		}
	}

	int closed = close(fileDescriptor); //close the opened file
	if(closed == -1) //if the closing procedure did not succeed output error message
	{
		perror("cat");
		exit(errno);
	}

	return 0;
}
