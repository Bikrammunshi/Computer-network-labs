//tcp client

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1"
#define PORT 12345
#define BUFFER_SIZE 1024

int main()
{
	int socket_desc_538;
	struct sockaddr_in server_addr,client_addr;
	char server_message[BUFFER_SIZE],client_message[BUFFER_SIZE] = "HELLO THIS IS CLIENT 2";
	int server_struct_length = sizeof(server_addr);

	memset(server_message, '\0', sizeof(server_message));

	socket_desc_538 = socket(AF_INET, SOCK_STREAM,0);
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORT);
	server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);

	memset(&(server_addr.sin_zero), '\0',0);

	if(connect(socket_desc_538, (struct sockaddr*)&server_addr,sizeof(server_addr))<0)
	{
		printf("Error while connecting");
		return -1;
	}		

	printf("Connected\n");
	

	getchar();
	if(send(socket_desc_538, &client_message, sizeof(client_message), 0) < 0)
			{
				printf("Send failed");
				return -1;
			}
	if(recv(socket_desc_538, server_message, sizeof(server_message), 0)<0)
		{
			printf("Connection failed");
			return -1;
		}

	printf("%s",server_message);

	close(socket_desc_538);
	return 0;
}
