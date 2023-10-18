/* WAP in C to perform all the arithmetic operation arith() and print all the result like result of +,-,/,* and % in main(), by calling the function arith() once in main()*/

#include <stdio.h>
#include <stdlib.h>

int* arith(int *num1, int* num2)
{
	int *arr = (int *)malloc(5*sizeof(int));

	arr[0] = *num1 + *num2;
	
	if(*num1 > *num2)
		arr[1] = *num1 - *num2;
	else
		arr[1] = *num2 - *num1;

	arr[2] = *num1 * *num2;

	if(*num2 == 0)
		arr[3] = 999;
	else
		arr[3] = *num1 / *num2;

	arr[4] = (int)*num1 % (int)*num2;

	return arr;
}

int main()
{
	int n1,n2;
	printf("Enter the two numbers \n");
	scanf("%d",&n1);
	scanf("%d",&n2);

	int *arr = arith(&n1 , &n2);

	printf("The summation of two numbers is %d \n",arr[0]);
	printf("The difference between the two numbers is %d \n",arr[1]);
	printf("The product of the two numbers %d \n",arr[2]);
	if(arr[3] == 999)
		printf("Since number 2 is 0 division is not possible \n");
	else
		printf("The quotient after dividing the number 1 with number 2 is %d \n",arr[3]);
	printf("The remainder after dividing number 1 with number 2 is %d \n",arr[4]);

	return 0;
}
