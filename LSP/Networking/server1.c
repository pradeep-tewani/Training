#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>


int main()
{
	int server_sockfd, client_sockfd;
	int server_len, client_len;
	struct sockaddr_in server_address;
	struct sockaddr_in client_address;
	//TODO 1: Get the named fd for the socket

	//TODO 2: Initialize the sockaddr data structure
	server_len = sizeof(server_address);
	//TODO 3: Bind the socket
	//TODO 4: Create the queue for listening 

	while (1)
	{
		char ch;
		printf("server waiting\n");
		client_len = sizeof(client_address);
		//TODO 5: Accept the connection
		//TODO 6: Read the variable from the client, increment and send it back to the client
	}
	return 0;
}
