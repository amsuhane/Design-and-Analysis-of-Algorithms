/*** Kth Smallest Element In Array ***/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

clock_t time_value;

int n;
int k;
int kth_smallest;

void swap(int *a,int *b) {
	int t = *a;
	*a = *b;
	*b = t;
}

void print_array(int a[n]) {
	int i = 0;
	printf("\n---Displaying Array---\n");
	for(i = 0;i < n;i++){
		printf("%d ",a[i]);
	}
	printf("\n");
}

int partition(int a[n],int p,int r) {
	if(p < r) {
		int x = a[p];
		int i = p;
		int j = 0;//loop counter

		for(j = p+1;j <=r;j++) {
			if(a[j] < x) {
				i++;
				swap(&a[i],&a[j]);
			}
		}
		swap(&a[p],&a[i]);
		return i;
	}
}

void random_quicksort(int a[n],int p,int r) {
	if(p >= r) return;
	int q = partition(a,p,r);
	
	/*** Logic ***/
	/**
	Check if q is at the correct position i.e. the index of the current partition element is the kth smallest index
	If it is then assign the kth smallest number and return from this function
	No need to do any further computation

	If q is bigger than the kth smallest index,search for kth smallest number in the lower half of the partition
	Else search for kth smallest number in the upper half of the partition
	**/
	if(q == (k-1)) {
		kth_smallest = a[q];
		return;
	}
	if(q > k-1)
		random_quicksort(a,p,q-1);
	else
		random_quicksort(a,q+1,r);
}

int main() {
printf("Enter the number of elements : ");
scanf("%d",&n);

int a[n];
int i = 0;
for(i = 0;i < n;i++) {
	printf("Enter a[%d] = ",i);
	scanf("%d",&a[i]);
}
//dummy initialization
kth_smallest = a[0];

printf("Enter k : ");
scanf("%d",&k);

print_array(a);

time_value = clock();
random_quicksort(a,0,n-1);
time_value = clock() - time_value;
double double_time = ((double)time_value)/CLOCKS_PER_SEC;

printf("Finding Kth Smallest took : %lf seconds...\n",double_time);

printf("Kth smallest is : %d\n",kth_smallest);
return 0;
}
