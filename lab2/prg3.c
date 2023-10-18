/*WAP in C to input a sentence and print the average number of characters in each word where spaces are not uniform*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
	char sentence[1000];
	int totalnumberofcharacters = 0;
	int numberofwords = 0;

	printf("Enter a sentence : \n");
	scanf("%[^\n]s",&sentence);

	int stringlength = strlen(sentence);

	for(int i=0;i<stringlength;i++)
	{
		if( sentence[i] != ' ' && sentence[i] != '\n')
		{
			totalnumberofcharacters++;
			if( i>0 & (sentence[i-1] == ' ' || sentence[i-1] == '\n' ))
				numberofwords++;
		}
	}

	if(sentence[stringlength-1] != ' ' && sentence[stringlength-1] != '\n')
		numberofwords++;

	double average = (double)totalnumberofcharacters/numberofwords;

	printf("The average number of characters per word is %0.2f.",average);
	return 0;
}