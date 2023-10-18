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
	char flag2[100] = "please calculate\0" ;
	char operator[1000];
	int num1,num2;


	while(1)
	{
		if(recvfrom(socket_desc,client_message,sizeof(client_message),0,(struct sockaddr*)&client_addr,&client_struc_length) > 0)
			printf("Message received: %s\n",client_message);
		if(strcmp(client_message,flag) == 0 )
			break;
		/*num1 = atoi(client_message);

		if(recvfrom(socket_desc,client_message,sizeof(client_message),0,(struct sockaddr*)&client_addr,&client_struc_length) > 0)
			printf("Message received: %s\n",client_message);
		num2 = atoi(client_message);


		if(recvfrom(socket_desc,client_message,sizeof(client_message),0,(struct sockaddr*)&client_addr,&client_struc_length) > 0)
			printf("Message received: %s\n",client_message);
		strcpy(operator,client_message);
		*/

		if(strcmp(client_message,flag2) == 0)
		{
			printf("Enter number 1: ");
			scanf("%d",&num1);
			printf("Enter number 2: ");
			scanf("%d",&num2);
			getchar();
			printf("Enter the operator: ");
			scanf("%[^\n]",&operator);
			getchar();
		}

		if(operator[0] == '+')
			num1 = num1 + num2;
	
		if(operator[0] == '-')
		{
			if(num1 > num2)
				num1 = num1 - num2;
			else
				num1 = num2 - num1;
		}


		if(operator[0] == '*')
			num1 = num1 * num2;



		sprintf(server_message,"%d",num1);


		if(operator[0] == '/')
		{	
			if(num2 == 0)
				strcpy(server_message,"Invalid dinominator is 0\0");

			else
				{
					num1 = num1 / num2;
					sprintf(server_message,"%d",num1);
				}
		}
		if(operator[0] == '%')
		{
			if(num2 == 0)
				strcpy(server_message,"Invalid dinominator is 0\0");
			else
			{
				num1 = num1 % num2;
				sprintf(server_message,"%d",num1);
			}
		}

		printf("Message sent: %d\n",num1);
		if(sendto(socket_desc, server_message,sizeof(server_message),0,(struct sockaddr*)&client_addr,client_struc_length) <0 )
			printf("Error in sending\n");

	}
	
	printf("Connection terminated");
	close(socket_desc);
	return 0;
}
	
