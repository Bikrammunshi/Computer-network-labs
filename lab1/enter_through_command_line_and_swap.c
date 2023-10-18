#include <stdio.h>
#include <stdlib.h>
void swap(int *x,int *y)
{
	int temp ;
	temp = *x;
	*x = *y;
	*y = temp;
}


int main(int argc,char*argv[]) //argc counts the number of arguments argv contains the total number of the argument with the file name as the first argument
{
	printf("%d",argc);
	
	int a = atoi(argv[1]) ;
	int b = atoi(argv[2]) ;
	printf("\nOriginal two numbers");
	printf("\nNumber 1: %d",a);
	printf("\nNumber 2: %d",b);
	
	swap(&a,&b);
	printf("\nNew two numbers");
	printf("\nNumber 1: %d",a);
	printf("\nNumber 2: %d",b);
	
	return 0;
}
	
