//udp client

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
	int socket_desc;
	struct sockaddr_in server_addr, client_addr;
	char server_message[2000], client_message[2000];
	int server_struct_length = sizeof(server_addr);


	memset(server_message, '\0', sizeof(server_message));
	memset(client_message, '\0', sizeof(client_message));

	socket_desc = socket(AF_INET, SOCK_STREAM, 0);




	if(socket_desc < 0)
	{
		printf("Error while creating socket\n");
		return -1;
	}
	printf("Socket created sucessfully\n");


    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);

	if(bind(socket_desc,(struct sockaddr*)&client_addr , sizeof(client_addr)) < 0)
	{
		printf("Couldnot bind to port\n");
		return -1;
	}
	printf("Port binding succesfull\n");

	return 0;
}