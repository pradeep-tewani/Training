#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
	int sockfd;
	int len;
	struct sockaddr_un address;
	int result;
	char ch = 'A';

	//TODO 1: Get the fd for the socket

	//TODO 2: Initialize the sockaddr
	len = sizeof(address);

	//TODO 3: Connect to the server 
	if(result == -1) {
		perror("oops: client1");
		exit(1);
	}
	//TODO 3: Write a character to socket & read it back
	//TODO 4: Close the socket
	exit(0);
}
