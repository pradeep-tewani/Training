#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

//TODO 1: Declare the structure with argument of type long and second a character array of say 200

int main(void)
{
	int msqid;
	key_t key;

	//TODO 2: Access the Message queue created by msg_send process. Use the permissions S_RUSR | S_IWUSR 

	printf("Ready to receive messages\n");

	for (;;) /* it  never quits! */
	{
		//TODO 3: Receive the message with msgrcv and display the same
	}

	return 0;
}
