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
struct  sockaddr_in server_addr, client_addr;
char server_message[2000], client_message[2000];
int server_struct_length = sizeof(server_addr);

memset(server_message, '\0', sizeof(server_message));
memset(client_message, '\0', sizeof(client_message));

socket_desc = socket(AF_INET, SOCK_STREAM, 0);

server_addr.sin_family = AF_INET;	//host byte order
server_addr.sin_port = htons(PORT);		//network byte order
server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);

memset(&(server_addr.sin_zero), '\0',8);

if(connect(socket_desc, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
{

printf("Error while connecting");
return -1;

}
printf("Connected \n");
return 0;
}



