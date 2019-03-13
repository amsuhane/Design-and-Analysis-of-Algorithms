#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//time variables
int size;//stores the array size
clock_t time_value;

/*************Utils*************/
void print_array(int a[]) {
int i = 0;
for(i = 0;i < size;i++) {
printf("%d ",a[i]);
}
printf("\n");
}

/*******************************/

/***************Insertion Sort*****************/
void insertion_sort(int a[]) {
int i = 0;//loop counter

for(i = 1;i < size;i++) {
int key = a[i];
int j = i-1;
while(j >= 0 && a[j] > key) {
a[j+1] = a[j];
j--;
}
a[j+1] = key;
}

}

/**********************************************/

/************Merge Sort***************/
void merge(int a[],int l,int m,int h) {
int n1 = m-l+1;
int n2 = h-m;
int left[n1+1];
int right[n2+1];

int i = 0,j = 0;

for(i = 0;i < n1;i++) {
left[i] = a[l + i];
}

for(i = 0;i < n2;i++) {
right[i] = a[i + m + 1];
}

//sequetially put in the elements one by one
i = 0;
int k = 0;

for(k = l;k <= h;k++) {
	if(i >= n1) {
		a[k] = right[j];
		j++;
	}
	else if(j >= n2) {
		a[k] = left[i];
		i = i+1;
	}
	else {
		if(left[i] < right[j]) {
			a[k] = left[i];
			i++;
		}
		else {
			a[k] = right[j];
			j++;
		}
	}

}
}

void mergesort(int a[],int l,int h){
if(l >= h) return;
int m = (l+h)/2;
mergesort(a,l,m);
mergesort(a,m+1,h);
merge(a,l,m,h);
}

/********************************/

/**************Comparing the running times for varied sizes of inputs***********/
void compare(){
//array storing the different input sizes to compare the running times
int sizes[4] = {10,100,1000,10000};
//worst case analysis of both the algorithms

int s;//loop counter for iterating over all the sizes

for(s = 0;s < 4;s++) {
printf("\n");
int n = sizes[s];
size = n;
int a[n];
int a_copy[n];

int i = 0;

for(i = 0;i < n;i++) {
a[i] = rand()%n;
a_copy[i] = rand()%n;
}

//call insertion_sort
time_value = clock();
insertion_sort(a);
//print_array(a);
time_value = clock() - time_value;
double double_time = ((double)time_value)/CLOCKS_PER_SEC;
printf("%d - Insertion Sort : %lf   ",n,double_time);

//call merge sort
time_value = clock();
mergesort(a_copy,0,n-1);
//print_array(a_copy);
time_value = clock() - time_value;
double_time = ((double)time_value)/CLOCKS_PER_SEC;
printf("Merge Sort : %lf   ",double_time);

}//end of the sizes loop

}

int main() {
//compare the different sorting algorithms
compare();
printf("\n");
return 0;
}
