/* Write a C Program to enter a number and store the number across the following
structure and print the content of each member of the structure. Then aggregate each
member of the structure to form the original number and print the same.
struct pkt{
char ch1;
char ch2[2];
char ch3;
};
*/

#include <stdio.h>

struct pkt
{
	char ch1;
	char ch2[2];
	char ch3;
};

int main()
{
	struct pkt packet;
	int number;
    	printf("Enter a number: ");
    	scanf("%d", &number);

	
	// Extracting bytes using bitwise operations
	packet.ch3 = (number >> 24) & 0xFF;
	packet.ch2[1] = (number >> 16) & 0xFF;
	packet.ch2[0] = (number >> 8) & 0xFF;
	packet.ch1 = number & 0xFF;
	printf("%d\n",number);
	// Printing the content of the variables
	printf("Byte 1: %d\n", packet.ch1);
	printf("Byte 2: %d\n", packet.ch2[0]);
	printf("Byte 3: %d\n", packet.ch2[1]);
	printf("Byte 4: %d\n", packet.ch3);
	
	int original_number = (packet.ch3 << 24) | (packet.ch2[1] << 16) | (packet.ch2[0] << 8) | packet.ch1;
	
	printf("The number from the byte characters is %d\n",original_number);
	return 0;
}
