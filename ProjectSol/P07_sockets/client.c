#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "sig.h"
#include "em_registers.h"

#define PORT_NUM 2000

int main(int argc, char *argv[])
{
    struct em_registers reg;
    int sock_fd;
    char *ip_addr;
    struct sockaddr_in my_addr;
    socklen_t my_addr_len = sizeof(my_addr);

    if (argc != 2)
    {
        printf("Usage: %s <server ip addr>\n", argv[0]);
        return 1;
    }

    ip_addr = argv[1];

    // TODO 1: Create the socket using socket API
    if ((sock_fd = socket(AF_INET, SOCK_STREAM, 0 /* IPPROTO_TCP */)) == -1)
    {
        perror("socket");
        return 2;
    }
    printf("done\n");

    // TODO 2: Initialize the required fields for my_addr & connecto the socket
    my_addr.sin_family = AF_INET; // address family 
    my_addr.sin_port = htons(PORT_NUM); // short, network byte order
    my_addr.sin_addr.s_addr = inet_addr(ip_addr);
    bzero(&(my_addr.sin_zero), 8);

    printf("Connecting socket to %s ... ", ip_addr);
    if (connect(sock_fd, (struct sockaddr *)&my_addr, my_addr_len) == -1)
    {
        perror("connect");
        close(sock_fd);
        return 4;
    }
    printf("done\n");

    while ((recv(sock_fd, &reg, sizeof(struct em_registers), 0)) > 0)
    {
        printf("Va = %u, Vb = %u Vc = %u\n", reg.va, reg.vb, reg.vc);
        printf("Va_max = %u, Vb_max = %u Vc_max = %u\n", reg.va_max, reg.vb_max, reg.vc_max);
    }
   
    close(sock_fd);

    return 0;
}
