#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 12345
#define BUFFER_SIZE 1024
#define BACKLOG 10000 //pending conenctions will hold up to

int main()
{
	struct sockaddr_in server_addr, client_addr;
	char server_message[2000] = "HELLO CLIENT", client_message[2000];
	int client_struct_length = sizeof(client_addr);
	
	memset(client_message, '\0', sizeof(client_message));

	
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);

	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(PORT);
	memset(&(server_addr.sin_zero),'\0',8); //zero the rest of the structure

	
	if(bind(sockfd,(struct sockaddr *)&server_addr, sizeof(struct sockaddr)) < 0)
	{
		printf("Bind failed\n");
		return -1;
	}
	
	if(listen(sockfd, BACKLOG) < 0)
	{
		printf("Waiting time exceeded");
		return -1;
	}
	printf("Listening to client\n");
	
	fd_set readfd,allfd;
	FD_ZERO(&allfd);
	FD_SET(sockfd,&allfd);
	int i=0,j,clientfd[10],maxfd;
	maxfd=sockfd+1;

	struct timeval t;
	t.tv_sec = 25;
	t.tv_usec = 30;

	int sin_size = sizeof(struct sockaddr_in);
	
	while(1)
	{
		readfd = allfd;
		int k = select(maxfd,&readfd,NULL,NULL,&t);
		if(FD_ISSET(sockfd,&readfd))
		{
			int new_clientfd = accept(sockfd, (struct sockaddr *)&client_addr, &sin_size);
			if (new_clientfd < 0) {
				printf("accept failed\n");
				continue;
			}

			if (i >= BACKLOG) {
				printf("Too many clients\n");
				close(new_clientfd);
				continue;
			}

			clientfd[i] = new_clientfd;
			FD_SET(clientfd[i],&allfd);
			if(clientfd[i]>maxfd)
			{
				maxfd = clientfd[i]+1;
			}
			i++;
		}

		for(j=0;j<i;j++)
		{
			if(FD_ISSET(clientfd[j],&readfd))
			{
				int n=recv(clientfd[j], client_message, sizeof(client_message),0);
				if(n==0)
				{
					close(clientfd[j]);
					FD_CLR(clientfd[j],&allfd);
				}
				else
				{
					printf("%s",client_message);
					send(clientfd[j], &server_message, sizeof(server_message),0);
					close(clientfd[j]);
					FD_CLR(clientfd[j], &allfd);
 
				}
			}
		}
	}
	return 0;
}
