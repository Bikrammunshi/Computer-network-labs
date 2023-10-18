
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


int no_of_characters(char str[])
{
	int count=0;
	int i=0;
	while(str[i] != '\0')
	{
		count ++;
		i++;
	}
	return count;
}

int count_words(char *sentence) {
  int word_count = 0;
  int in_word = 0;
  for (int i = 0; sentence[i] != '\0'; i++) {
    if (sentence[i] == ' ' || sentence[i] == '\n' || sentence[i] == '\t') {
      in_word = 0;
    } else if (!in_word) {
      word_count++;
      in_word = 1;
    }
  }
  return word_count;
}

int count_vowels(char *sentence) {
  int vowel_count = 0;
  char vowels[] = {'a', 'e', 'i', 'o', 'u'};
  for (int i = 0; sentence[i] != '\0'; i++) {
    for (int j = 0; j < 5; j++) {
      if (sentence[i] == vowels[j]) {
        vowel_count++;
      }
    }
  }
  return vowel_count;
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

	char message[100]="Send message to get the number of characters";

	if(send(new_fd, &message, sizeof(message),0) <0 )
	{
		printf("sending failed");
		return -1;
	}

	int sum=0;

	if(recv(new_fd, client_message, sizeof(client_message),0) <0 )
		{
			printf("Receive failed");
			return -1;
		}

	sum = no_of_characters(client_message);
	
	tostring(server_message,sum);
	
	if(send(new_fd, &server_message, sizeof(server_message),0) <0 )
		{
			printf("sending failed");
			return -1;
		}
	printf("Number of characters sent successfully\n");

	sum = count_words(client_message);
	tostring(server_message,sum);
		
	if(send(new_fd, &server_message, sizeof(server_message),0) <0 )
		{
			printf("sending failed");
			return -1;
		}
	printf("Number of words sent successfully\n");

	sum = count_vowels(client_message);
	tostring(server_message,sum);
		
	if(send(new_fd, &server_message, sizeof(server_message),0) <0 )
		{
			printf("sending failed");
			return -1;
		}
	printf("Number of vowels sent successfully\n");
	
	close(socket_desc_538);
	close(new_fd);
	return 0;
}
