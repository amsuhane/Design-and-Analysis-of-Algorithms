/*** Lucky-Unlucky Quicksort Algorithm ***/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

clock_t time_value;

int n;
int toggle = 0;
int kth_index = 0;
int k = 0;

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

/***************************** Kth Smallest ********************************/
int kth_partition(int a[n],int p,int r) {
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

void kth_quicksort(int a[n],int p,int r) {
	if(p >= r) return;
	int q = kth_partition(a,p,r);
	
	/*** Logic ***/
	/**
	Check if q is at the correct position i.e. the index of the current partition element is the kth smallest index
	If it is then assign the kth smallest number and return from this function
	No need to do any further computation

	If q is bigger than the kth smallest index,search for kth smallest number in the lower half of the partition
	Else search for kth smallest number in the upper half of the partition
	**/
	if(q == (k-1)) {
		kth_index = q;
		return;
	}
	if(q > k-1)
		kth_quicksort(a,p,q-1);
	else
		kth_quicksort(a,q+1,r);
}
/*************************************************************************************/

int min_index_in_a(int a[n],int p,int r) { //returns the index of the minimum in the subarray
	int i = 0;
	int min = a[p];
	int min_id = 0;
	for(i = p;i <= r;i++) {
		if(a[i] <= min) {
			min = a[i];
			min_id = i;
		}
	}
	return min_id;
}

int partition(int a[n],int p,int r) {
	if(p < r) {
		if(toggle == 0) { //choose median - Lucky
			k = (p+r)/2;
			kth_quicksort(a,p,r);
			swap(&a[k],&a[p]);
			toggle = 1;
		}
		else { //choose minimum - Unlucky
			int min_id = min_index_in_a(a,p,r);
			swap(&a[min_id],&a[p]);
			toggle = 0;
		}
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

void quicksort(int a[n],int p,int r) {
	if(p >= r) return;
	int q = partition(a,p,r);
	quicksort(a,p,q-1);
	quicksort(a,q+1,r);
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

print_array(a);

time_value = clock();
quicksort(a,0,n-1);
time_value = clock() - time_value;
double double_time = ((double)time_value)/CLOCKS_PER_SEC;

printf("Lucky Quicksort took : %lf seconds...\n",double_time);

printf("After Sorting...\n");
print_array(a);
return 0;
}
