#include<stdio.h>

int main(){

	char *name = "Atharva"; //how does this work ?// the string is assigned to the base address of the 'name' var then it scans the given 
				//string till EOL (end of line is found) i.e '\0'.
				
	char *name1; //char pointer doesn't store the address of the string ?
	char name2[10] = "Omesh";
	//i want to pass the base of address of name2 var to name1
	//i tried getting the base address of name2, which was 690388030, just found out that the address of name2 changes after every compilation
	//so that doesn't work therefore doing the following is just dumb
	//int *a;
	//a = 690388030;
	//name1 = a;
	//i tried passing that to name1 but the types are not matching
	//

	name1 = name2;

	int *num;
	int a = 5;
	num = &a;

	printf("My name is %s\n", name);
	printf("My name is %s\n", name1);
	printf("%d\n", *num); //



	return 0;
}
