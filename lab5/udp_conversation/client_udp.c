//client side for udp

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
	int server_struc_length = sizeof(server_addr);

	memset(server_message, '\0', sizeof(server_message));
	memset(client_message, '\0', sizeof(client_message));

	socket_desc = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);

	if(socket_desc < 0)
	{
		printf("Socket creation failed \n");
		return -1;
	}
	printf("Socket created succesfully\n");

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

	char flag[5] = "exit\0";
	while(1)
	{
		printf("Enter message: ");
		scanf("%[^\n]",&client_message);
		getchar();
		if(sendto(socket_desc, client_message,sizeof(client_message),0,(struct sockaddr*)&server_addr,server_struc_length) <0 )
			printf("Error in sending\n");
		if(strcmp(client_message,flag) == 0 )
			break;
		if(recvfrom(socket_desc,server_message,sizeof(server_message),0,(struct sockaddr*)&server_addr,&server_struc_length) > 0)
			printf("Message received: %s\n",server_message);
		
	}
	
	printf("Connection terminated");
	close(socket_desc);
	return 0;
}