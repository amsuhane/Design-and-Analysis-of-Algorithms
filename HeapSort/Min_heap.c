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

void min_heapify(int a[],int i,int size) { //assume i is given in 1 indexed format
	int l = 2*(i);
	int r = 2*(i) + 1;
	int smallest = i;
	int value_smallest = a[i-1];
	//left element is indexed at l-1 and right element is indexed at r-1
	if((l-1) < size) {
		if(a[l-1] < value_smallest) {
			smallest = l;
			value_smallest = a[l-1];
		}
	}
	if((r-1) < size) {
		if(a[r-1] < value_smallest) {
			smallest = r;
			value_smallest = a[r-1];
		}
	}	
	if(smallest != i) {
		swap(&a[i-1],&a[smallest-1]);
		min_heapify(a,smallest,size);
	}
}

void build_min_heap(int a[],int size) {
	int i = 1;
	for(i = (size/2);i >= 1;i--) {
		min_heapify(a,i,size);
	}
}

int find_cost(int a[]) {
int cost = 0;
int i = 0;
/***
Logic : 
Build a minimum heap of all the sizes of the N arrays.
Find the two smallest in the heap and add their merging cost in our variable.
Remove the smallest from the heap and again repeat this process until only two elements are left to merge.
***/
for(i = 0;i < (n-1);i++) {
	build_min_heap(a+i,n-i);
	//Now the first element is the minimum and the next smallest is it's child
	if((i+2) < n) { //if right child exists
		if(a[i+2] < a[i+1]) { //if right child is the next smallets in the heap
			cost+=(a[i+2] + a[i]);
			a[i+2] = a[i+2] + a[i];
		}
		else { //if left5 child is the next smallest in the heap
			cost+=(a[i+1] + a[i]); 
			a[i+1] = a[i+1] + a[i];
		}
	}
	else { //if only the left child exists,then merge the two
		cost+=(a[i+1] + a[i]);
		a[i+1] = a[i+1] + a[i];
	}
}

return cost;
}

int main() {
	printf("Enter N (the number of sorted arrays whose sizes are to be taken) : ");
	scanf("%d",&n);
	int a[n]; //stores sizes 
	
	int i = 0;
	for(i = 0;i < n;i++) {
		printf("Enter size of array of index %d : ",i);
		scanf("%d",&a[i]);
	}
	
	int c = find_cost(a);
	printf("\nMerging Cost : %d\n",c);
	return 0;
}
