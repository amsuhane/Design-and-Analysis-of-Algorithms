/*** Order Statistics ***/

#include <stdio.h>
#include <stdlib.h>

int n;
int k;

void swap_vals(int *a,int *b) {
	int t = *a;
	*a = *b;
	*b = t;
}

//partition the A[p...r]
int partition(int a[n],int p,int r) {
	if(p < r) {
		int x = a[p];
		int i = p;
		int j = 0;//loop counter

		for(j = p+1;j <=r;j++) {
			if(a[j] < x) {
				i++;
				swap_vals(&a[i],&a[j]);
			}
		}

		swap_vals(&a[p],&a[i]);
		return i;
	}
}

//Utility function for printing the array 
void print_array(int a[n]) {
	int i = 0;
	printf("\n---Displaying Array---\n");
	for(i = 0;i < n;i++) {
	printf("%d ",a[i]);
	}
	printf("\n");
}

//Find the median in A[p...r]
/***
Logic
A = [0,1,2,3,4,9,8,7,6,1]
Now suppose we want to find median of medians of this array
Suppose this indexes from A[p...r] i.e. A[p] = 0 and A[r] = 1
So we find the median for [0,1,2,3,4] and [9,8,7,6,1] and put them at the start of this array
We call median on the two groups of 5 thus formed 
base_p represents p of the original array A 
p in the function median corresponds to the sratring index of the group i.e of either of the two groups
Finally after doing the operations of median on the two groups,the array becomes : 
A = [2,7,0,3,4,9,8,1,6,1]
***/
void median(int a[n],int base_p,int p,int r) {
	//p & r are considering zero indexing
	
	/***
	First sort A[p...r]
	Find the middle elment
	This array would be of <= 5 elements
	***/

	/* Insertion Sort */
	int i = 0,j = 0;
	for(i = p;i <= r;i++) {
		int j = i - 1;
		int key = a[i];
		while(j > p-1 && a[j] > key) {
			a[j+1] = a[j];
			j--;
		}
		a[j+1] = key;
	}
	/******************/

	int mid = (p + r)/2;
	//swap the middle value with the start value
	swap_vals(&a[mid],&a[base_p + (p - base_p)/5]);
}



/*** This finds the median of medians of A[p...r] and puts that value at the start of the array ***/
/***
This first divides A[p...r] in groups of 5,finds their medians and puts them consecutively at the start of A[p...r]
***/
void select_pivot(int a[n],int p,int r) {
	/*
	A[p...r] - array on which select is to be called
	*/

	if(p == r) {
		return;
	}

	int length = (r - p + 1);

	//Divide array in groups of 5
	int groups;//number of groups
	groups = length/5;
	if(length%5 != 0)
		groups++;

	//find the medians and swap them to the front of the array
	int i = 0;
	for(i = 0;i < groups;i++) {
	//sort the group and shift all medians to the start of the array
	if(i < groups-1)
		median(a,p,p + 5*i,p + (5*i) + 4);
	else { //when last group may or may not contain 5 elements
		if(length%5 == 0)
			median(a,p,p + 5*i,p + (5*i) + 4);
		else
			median(a,p,p + 5*i,p + (5*i) + (length%5) - 1);
	}	
	}
	//end of median swapping for loop

	select_pivot(a,p,p + groups-1);
}
//This function does the partitioning and recursively searches for the kth order statistic in the different partitions made
void SELECT(int a[n],int p,int r) {
	select_pivot(a,p,r);
	//a[p] now contains the pivot value

	int place = partition(a,p,r);

	if(place == (k-1)) { //found
		printf("KTH Order Statistic : %d\n",a[place]);
		return;
	}

	else if(place > (k-1)) { //search in left partition
		SELECT(a,p,place-1);
	}
	else { //search in right partition
		SELECT(a,place+1,r);
	}	
}

int main() {
printf("Enter n : ");
scanf("%d",&n);
printf("Enter k(to find the kth smallest element) : ");
scanf("%d",&k);
int a[n];

int i = 0;

for(i = 0;i < n;i++) {
printf("Enter a[%d] : ",i);
scanf("%d",&a[i]);
}

SELECT(a,0,n-1);
return 0;
}
