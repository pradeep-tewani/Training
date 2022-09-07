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
	int read_cnt;
	char buff[200];

	//TODO 2: Create the message queue with msgget. Use the permissions S_RUSR | S_IWUSR 

	printf("Enter lines of text, ^D (on a separate line) to quit:\n");
	
	//TODO 3: Set the message type to 1
	while (1)
	{
		//TODO 4: Read into the msgbuf's buffer
		read_cnt = scanf("%[^\n]", buff);
		if (read_cnt == EOF)
		{
			break;
		}
		if (read_cnt == 0) // Null string
		{
			buff[0] = '\0';
		}
		scanf("%*c"); // Read the '\n'

		//TODO 5: Send the message with msgsnd
	}

	return 0;
}
