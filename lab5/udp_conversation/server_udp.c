//server side for the udp

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 12345
#define BUFFER_SIZE 1024

int main()
{
	int socket_desc;
	struct sockaddr_in server_addr, client_addr;
	char server_message[2000], client_message[2000];
	int client_struc_length = sizeof(client_addr);


	memset(server_message, '\0', sizeof(server_message));
	memset(client_message, '\0', sizeof(client_message));

	socket_desc = socket(AF_INET,SOCK_DGRAM, IPPROTO_UDP);

	if(socket_desc < 0)
	{
		printf("Socket creation failed \n");
		return -1;
	}
	printf("Socket created succesfully\n");

	memset(&server_addr, 0,sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(PORT);

	if(bind(socket_desc,(struct sockaddr*)&server_addr, sizeof(server_addr)) < 0 )
	{
		printf("Bind failed\n");
		return -1;
	}
	printf("Binding succesfull\n");

	char flag[5] = "exit\0";
	while(1)
	{
		if(recvfrom(socket_desc,client_message,sizeof(client_message),0,(struct sockaddr*)&client_addr,&client_struc_length) > 0)
			printf("Message received: %s\n",client_message);
		if(strcmp(client_message,flag) == 0 )
			break;
		printf("Enter the answer which has to be sent to client: ");
		scanf("%[^\n]",&server_message);
		getchar();
		if(sendto(socket_desc, server_message,sizeof(server_message),0,(struct sockaddr*)&client_addr,client_struc_length) <0 )
			printf("Error in sending\n");

	}
	
	printf("Connection terminated");
	close(socket_desc);
	return 0;
}
	
