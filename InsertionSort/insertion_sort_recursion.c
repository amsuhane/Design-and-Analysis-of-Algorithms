#include <stdio.h>
#include <math.h>

int global_n;

void print_array(int n,int a[n]) {
int i = 0;
for(i = 0;i < n;i++) {
printf("%d ",a[i]);
}
printf("\n");
}

void insert(int n,int num,int a[]) {
//insert num in the array a of size n
int i = n-1; 

//binary search
int l = 0;
int h = n;
int m = (l+h)/2;

while(h >= l) {
	m = (l+h)/2;
	if(num < a[m]) {
		h = m-1;
		continue;
	}
else if(num > a[m]) {
	l = m+1;
	continue;
}
else {
	break;
}
}

for(i = n-1;i>=m;i--) {
	a[i+1] = a[i];
}
a[m] = num;
print_array(global_n,a);
}

void insertion_sort(int n,int a[]) { //n is the number of elements to access in the array
	if(n == 1) return;
	insertion_sort(n-1,a);
	insert(n-1,a[n-1],a);
}

int main() {
int n;
printf("Enter number of elements in the array\n");
scanf("%d",&n);
global_n = n;
int a[n];

//taking in the input numbers
int i = 0;
for(i = 0;i < n;i++) {
printf("Enter arr[%d] : ",i);
scanf("%d",&a[i]);
}

//call to insertion sort
insertion_sort(n,a);

//output
int j = 0;
printf("---------Output of the array in the ascending order-----------\n");
for(j = 0;j < n;j++) {
printf("%d ",a[j]);
}
printf("\n");
return 0;
}
