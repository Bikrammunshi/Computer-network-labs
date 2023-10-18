/*
Write a C program to check whether the Host machine is in Little Endian or Big
Endian. Enter a number, print the content of each byte location and Convert the
Endianness of the same i.e. Little to Big Endian and vice-versa.
*/


#include <stdio.h>

struct pkt
{
	char ch1;
	char ch2[2];
	char ch3;
}; 


void get_memoryaddress(int number,struct pkt *packet)
{
	packet->ch1 = (number >> 24) & 0xFF;
	packet->ch2[0] = (number >> 16) & 0xFF;
	packet->ch2[1] = (number >> 8) & 0xFF;
	packet->ch3 = number & 0xFF;

	printf("\n\nMemory Representation of the number with the bytes extracted from the LSB \n");
	printf("-------------------------------------------------------------\n");
	printf("\nMemory address \t\t =>\t\t      Value\n");
	printf("-------------------------------------------------------------\n");
	printf("%p \t\t => \t\t      %X\n",&packet->ch1,packet->ch1);
	printf("%p \t\t => \t\t      %X\n",&packet->ch2[0],packet->ch2[0]);
	printf("%p \t\t => \t\t      %X\n",&packet->ch2[1],packet->ch2[1]);
	printf("%p \t\t => \t\t      %X\n",&packet->ch3,packet->ch3);
	
}

int check_endian(struct pkt *packet)
{
	int check  = 0;
	if(&(packet->ch1) < &(packet->ch2)[0])
	{
		printf("\n\nThe LSB is found to be stored in the highest memory address \nHence the host machine is in big endian\n");
		check = 1;
	}
	else
		printf("\n\nThe LSB is found to be stored in the lowest memory address \nHence the host machine is in little endian \n");
	
	return check;
}
	
int convert_endian(int number)
{
    
    number = ((number >> 24) & 0xFF) | ((number >> 8) & 0xFF00) | ((number << 8) & 0xFF0000) | ((number << 24) & 0xFF000000);
    return number;
}



int main()
{
	int number;
	printf("Enter a number ");
	scanf("%d",&number);
	
	struct pkt packet;
	get_memoryaddress(number,&packet);
	int flag = check_endian(&packet);
	
	if(flag == 0)
	{
		number = convert_endian(number);
		printf("\nThe converted number in big endian is %d\n",number);
		struct pkt packet2;
		get_memoryaddress(number,&packet2);
	}
	else
	{
		number = convert_endian(number);
		printf("\nThe converted number in little endian is %d\n",number);
		struct pkt packet2;
		get_memoryaddress(number,&packet2);
	}
	
    return 0;
}
