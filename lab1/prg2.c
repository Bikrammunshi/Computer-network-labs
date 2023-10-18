#include<stdio.h>
#include<stdlib.h>

struct dob
{
	int d;
	int m;
	int y;
};

struct student_info
{
	int roll_no;
	char name[10];
	float CGPA;
	struct dob age;
};

void call_by_value(struct student_info student)
{
	printf("\nName: %s",student.name);
	printf("\nRoll no: %d",student.roll_no);
	printf("\nCGPA: %f",student.CGPA);
	printf("\nDate of birth: %d/%d/%d",student.age.d,student.age.m,student.age.y);
}
void call_by_reference(struct student_info *student)
{
	printf("\nName: %s",student->name);
	printf("\nRoll no: %d",student->roll_no);
	printf("\nCGPA: %f",student->CGPA);
	printf("\nDate of birth: %d/%d/%d",student->age.d,student->age.m,student->age.y);
}

int main()
{
	struct student_info record;
	printf("\nEnter the name of the student ");
	scanf("%[^\n]s",record.name);
	printf("\nEnter the roll of the student ");
	scanf("%d",&record.roll_no);
	printf("\nEnter the cgpa of the student ");
	scanf("%f",&record.CGPA);
	printf("\nEnter the date of birth  of the student in the format of dd/mm//yyyy ");
	scanf("%d",&record.age.d);
	scanf("%d",&record.age.m);
	scanf("%d",&record.age.y);
	
	printf("\nUsing call by value");
	call_by_value(record);
	
	printf("\nUsing call by reference");
	call_by_reference(&record);	
	return 0;
}
