/*** Modified Randomized Quicksort Algorithm ***/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

clock_t time_value;

int n;

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
		int len = r - p + 1;
		int random;

		if(len <= 4) {
		//generate a random index
		random = rand()%(r-p+1) + p;
		}
		
		else {
		int min1,max1,min2,max2;
		min1=max1=min2=max2=a[p];
		//find min1,max1,min2,max2
		int i = 0;
		for(i = p+1;i <= r;i++) {
			if(a[i] > max1) {
				max2 = max1;
				max1 = a[i];
			}
			if(a[i] < max1 && a[i] > max2) {
				max2 = a[i];
			}
			if(a[i] < min1) {
				min2 = min1;
				min1 = a[i];
			}
			if(a[i] > min1 && a[i] < min2) {
				min2 = a[i];
			}
		}
		
		random = rand()%(r-p+1) + p;
		while(a[random] != min1 && a[random] != min2 && a[random] != max1 && a[random] != max2)
			random = rand()%(r-p+1) + p;

		}
		//swap array element at random index with start element
		swap(&a[random],&a[p]);

		//apply normal quicksort as before
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
	random_quicksort(a,p,q-1);
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

print_array(a);

time_value = clock();
random_quicksort(a,0,n-1);
time_value = clock() - time_value;
double double_time = ((double)time_value)/CLOCKS_PER_SEC;

printf("Modified Randomized Quicksort took : %lf seconds...\n",double_time);

printf("After Sorting...\n");
print_array(a);
return 0;
}
