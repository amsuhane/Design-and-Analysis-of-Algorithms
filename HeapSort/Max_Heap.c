#include <stdio.h>
#include <stdlib.h>

int n;

typedef struct Student {
	char name[256];
	int roll_no;
	double CGPA;
} Student;

void swap(Student *p,Student *q) {
Student tmp = *p;
*p = *q;
*q = tmp;
}

void max_heapify(Student a[],int i) { //assume i is given in 1 indexed format
	int l = 2*(i);
	int r = 2*(i) + 1;
	int largest = i;
	double value_largest = a[i-1].CGPA;
	//left element is indexed at l-1 and right element is indexed at r-1
	if((l-1) < n) {
		if(a[l-1].CGPA > value_largest) {
			largest = l;
			value_largest = a[l-1].CGPA;
		}
	}
	if((r-1) < n) {
		if(a[r-1].CGPA > value_largest) {
			largest = r;
			value_largest = a[r-1].CGPA;
		}
	}	
	if(largest != i) {
		swap(&a[i-1],&a[largest-1]);
		max_heapify(a,largest);
	}
}

void build_max_heap(Student a[n]) {
	int i = 1;
	for(i = (n/2);i >= 1;i--) {
		max_heapify(a,i);
	}
}

int main() {
	printf("Enter n : ");
	scanf("%d",&n);
	Student a[n];
	
	int i = 0;
	for(i = 0;i < n;i++) {
		printf("Taking details for index %d---\n",i);
		printf("Enter name of student : ");
		fflush(stdin); //to remove the already put in the spaces
		scanf("%s",(a[i].name));
		printf("Enter Roll Number (an integer) : ");
		scanf("%d",&(a[i].roll_no));
		printf("Enter CGPA : ");
		scanf("%lf",&(a[i].CGPA));
	}
	
	build_max_heap(a);
	
	printf("\n---Printing details of student with highest CGPA---\n");
	//displaying output of the student with the maximum CGPA
	printf("Name : %s\nRoll Number : %d\nCGPA : %lf\n",a[0].name,a[0].roll_no,a[0].CGPA);
	return 0;
}
