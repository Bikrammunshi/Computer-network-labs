// WAp in C to store todays date using structure (d,mm,yyyy) and add some days with the inputted date and siplay the new date

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct date
{
	int day;
	int month;
	int year;
};

int main()
{
	time_t T = time(NULL);
	struct tm cur = *localtime(&T);

	struct date current_date;

	current_date.day = cur.tm_mday;
	current_date.month = cur.tm_mon + 1;
	current_date.year = cur.tm_year + 1900;

	printf("Current date is %d/%d/%d \n",current_date.day,current_date.month,current_date.year);

	int days;

	printf("Enter the number of days\n");
	scanf("%d",&days);

	struct date new_date;

	new_date.day = current_date.day;
	new_date.month = current_date.month;
	new_date.year = current_date.year;
	
	if(new_date.month != 2)
	{
		if(new_date.month == 1 || new_date.month == 3 || new_date.month == 5 || new_date.month == 7 || new_date.month == 8 || new_date.month == 10 || new_date.month == 12)
		{
			new_date.day = current_date.day + days ;
			if(new_date.day > 31)
			{
				new_date.month = new_date.month + new_date.day / 31;
				new_date.day = new_date.day % 31;
			}
			if(new_date.day == 0)
				new_date.day++;
		}

		else
		{new_date.day = current_date.day + days ;
			if(new_date.day > 30)
			{
				new_date.month = new_date.month + new_date.day / 30;
				new_date.day = new_date.day % 30;
			}
			if(new_date.day == 0)
				new_date.day++;
		}
	}

	else 
	{
		if ((new_date.year % 4 == 0 && new_date.year % 100 != 0) || (new_date.year % 400 == 0))
		{
			new_date.day = current_date.day + days ;
			if(new_date.day > 29)
			{
				new_date.month = new_date.month + new_date.day / 29;
				new_date.day = new_date.day % 29;
			}
			if(new_date.day == 0)
				new_date.day++;
		}
		else
		{
			new_date.day = current_date.day + days;
			if(new_date.day > 28)
			{
				new_date.month = new_date.month + new_date.day / 28;
				new_date.day = new_date.day % 28;
			}
			if(new_date.day == 0)
				new_date.day++;		
		}
	}
	if(new_date.month > 12)
	{
		new_date.year = new_date.year + new_date.month / 12;
		new_date.month = new_date.month % 12;
	}
	if(new_date.month == 0)
		new_date.month++;

	printf("New date is %d/%d/%d \n",new_date.day,new_date.month,new_date.year);

	return 0;
}