// Write a C program to extract each byte from a given number and store them in
//separate character variables and print the content of those variables.

#include <stdio.h>

int main()
{
    // Given number
    int number;
    printf("Enter a number: ");
    scanf("%d", &number);

    // Extracting bytes using bitwise operations
    char byte4 = (number >> 24) & 0xFF;
    char byte3 = (number >> 16) & 0xFF;
    char byte2 = (number >> 8) & 0xFF;
    char byte1 = number & 0xFF;

    // Printing the content of the variables
    printf("Byte 1: %X\n", byte1);
    printf("Byte 2: %X\n", byte2);
    printf("Byte 3: %X\n", byte3);
    printf("Byte 4: %X\n", byte4);

    return 0;
}
