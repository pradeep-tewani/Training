#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
	int sockfd;
	int len;
	struct sockaddr_in address;
	int result;
	char ch = 'A';
	//TODO 1: Get the fd for the socket
	len = sizeof(address);
	//TODO 2: Initialize the sockaddr_in
	//TODO 3: Connect to the server 
	if(result == -1) {
		perror("oops: client1");
		exit(1);
	}
	//TODO 4: Write a character to socket & read it back
	//TODO 5: Close the socket
	exit(0);
}
