//TCP server

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 12345
#define BUFFER_SIZE 1024
#define BACKLOG 10 //pending conenctions will hold up to
int main()
{
int socket_desc,new_fd;
struct sockaddr_in server_addr, client_addr;
char server_message[2000], client_message[2000];
int client_struct_length = sizeof(client_addr);

memset(server_message, '\0', sizeof(server_message));
memset(client_message, '\0', sizeof(client_message));

socket_desc = socket(AF_INET, SOCK_STREAM, 0);

memset(&server_addr, 0, sizeof(server_addr));
server_addr.sin_family = AF_INET;
server_addr.sin_addr.s_addr = INADDR_ANY;
server_addr.sin_port = htons(PORT);
memset(&(server_addr.sin_zero),'\0',8); //zero the rest of the structure

if(bind(socket_desc,  (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) < 0)
{
	printf("Bind failed\n");
	return -1;
}

if(listen(socket_desc, BACKLOG) < 0)
{
	printf("Waiting time exceeded");
	return -1;
}
printf("Listening to client\n");

int sin_size = sizeof(struct sockaddr_in);

new_fd = accept(socket_desc, (struct sockaddr *)&client_addr, &sin_size);

if(new_fd < 0)
{
	printf("Accepting failed");
	return -1;
}
printf("Accepting from client\n");
return 0;
}

