#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main (int argc, char* argv[])
{
	char* file = argv[1];
	int fd;
	struct flock lock;

	printf ("opening %s\n", file);
	/* Open a file descriptor to the file.*/
	//TODO 1: Open the file
	if (fd < 0)
	{
		printf("Unable to open the file %s\n", argv[1]);
		return -1;
	}

	printf ("locking\n");
	//TODO 2: Initialize the flock structure

	//TODO 3: Place a write lock on the file
	printf ("locked; hit Enter to unlock... ");

	/* Wait for the user to hit Enter. */
	getchar ();
	printf ("unlocking\n");
	//TODO 4: Release the lock

	close (fd);

	return 0;
}
