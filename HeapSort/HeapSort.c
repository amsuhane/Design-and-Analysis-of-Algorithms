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

void max_heapify(int a[],int i,int heap_size) { //assume i is given in 1 indexed format
	int l = 2*(i);
	int r = 2*(i) + 1;
	int largest = i;
	int value_largest = a[i-1];
	//left element is indexed at l-1 and right element is indexed at r-1
	if((l-1) < heap_size) {
		if(a[l-1] > value_largest) {
			largest = l;
			value_largest = a[l-1];
		}
	}
	if((r-1) < heap_size) {
		if(a[r-1] > value_largest) {
			largest = r;
			value_largest = a[r-1];
		}
	}	
	if(largest != i) {
		swap(&a[i-1],&a[largest-1]);
		max_heapify(a,largest,heap_size);
	}
}

void build_max_heap(int a[],int heap_size) {
	int i = 1;
	for(i = (heap_size/2);i >= 1;i--) {
		max_heapify(a,i,heap_size);
	}
}

void heap_sort(int a[],int heap_size) {
build_max_heap(a,n);
int i;
for(i = n;i >= 2;i--) {
	swap(&a[0],&a[i-1]);
	heap_size = heap_size - 1;
	max_heapify(a,1,heap_size);
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
	printf("\nBefore Sort\n");
	print_array(a);
	heap_sort(a,n);
	printf("\nAfter Sort\n");
	print_array(a);
	return 0;
}
