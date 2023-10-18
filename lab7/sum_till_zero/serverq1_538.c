//tcp server

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 12345
#define BUFFER_SIZE 1024
#define BACKLOG 10

void tostring(char str[], int num)
{
    int i, rem, len = 0, n;
 
    n = num;
    while (n != 0)
    {
        len++;
        n /= 10;
    }
    for (i = 0; i < len; i++)
    {
        rem = num % 10;
        num = num / 10;
        str[len - (i + 1)] = rem + '0';
    }
    str[len] = '\0';
}

int main()
{
	int socket_desc_538, new_fd;
	struct sockaddr_in server_addr,client_addr;
	char server_message[BUFFER_SIZE], client_message[BUFFER_SIZE];
	int client_struct_length = sizeof(client_addr);

	
	memset(server_message, '\0', sizeof(server_message));
	memset(client_message, '\0', sizeof(client_message));
	
	socket_desc_538 = socket(AF_INET, SOCK_STREAM, 0);
	
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(PORT);
	memset(&(server_addr.sin_zero),'\0',8); 
	
	if(bind(socket_desc_538,  (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) < 0)
	{
		printf("Bind failed\n");
		return -1;
	}
	
	if(listen(socket_desc_538, BACKLOG) < 0)
	{
		printf("Waiting time exceeded");
		return -1;
	}
	printf("Listening to client\n");
	
	int sin_size = sizeof(struct sockaddr_in);
	
	new_fd = accept(socket_desc_538, (struct sockaddr *)&client_addr, &sin_size);
	
	if(new_fd < 0)
	{
		printf("Accepting failed");
		return -1;
	}
	printf("Accepting from client\n");

	char message[100]="Start sending the number but remember 0 means exit";

	if(send(new_fd, &message, sizeof(message),0) <0 )
	{
		printf("sending failed");
		return -1;
	}

	int sum=0;

	while(1)
	{
		if(recv(new_fd, client_message, sizeof(client_message),0) <0 )
		{
			printf("Receive failed");
			return -1;
		}

		if(atoi(client_message)!= 0)
			sum = sum+ atoi(client_message);
		else
			break;
	}

	 tostring(server_message,sum);

	if(send(new_fd, &server_message, sizeof(server_message),0) <0 )
		{
			printf("sending failed");
			return -1;
		}

	close(socket_desc_538);
	close(new_fd);
	return 0;
}
