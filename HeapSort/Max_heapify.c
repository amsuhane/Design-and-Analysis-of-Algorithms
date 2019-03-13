#include <stdio.h>
#include <stdlib.h>

int n;

void print_array(int a[]) {
	int i = 0;
	printf("Displaying Array ---\n");
	for(i = 0;i < n;i++) {
		printf("%d ",a[i]);
	}
	printf("\n");
}

void swap(int *p,int *q) {
int tmp = *p;
*p = *q;
*q = tmp;
}

void max_heapify(int a[],int i) { //assume i is given in 1 indexed format
	int l = 2*(i);
	int r = 2*(i) + 1;
	int largest = i;
	int value_largest = a[i-1];
	//left element is indexed at l-1 and right element is indexed at r-1
	if((l-1) < n) {
		if(a[l-1] > value_largest) {
			largest = l;
			value_largest = a[l-1];
		}
	}
	if((r-1) < n) {
		if(a[r-1] > value_largest) {
			largest = r;
			value_largest = a[r-1];
		}
	}	
	if(largest != i) {
		swap(&a[i-1],&a[largest-1]);
		max_heapify(a,largest);
	}
}

void build_max_heap(int a[n]) {
	int i = 1;
	for(i = (n/2);i >= 1;i--) {
		max_heapify(a,i);
	}
}

int main() {
	printf("Enter n : ");
	scanf("%d",&n);
	int a[n];

	int i = 0;
	for(i = 0;i < n;i++) {
		printf("Enter a[%d] : ",i);
		scanf("%d",&a[i]);
	}

	print_array(a);
	build_max_heap(a);
	print_array(a);
	return 0;
}
