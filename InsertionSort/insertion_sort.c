#include <stdio.h>
#include <math.h>

void print_array(int n,int a[n]) {
int i = 0;
for(i = 0;i < n;i++) {
printf("%d ",a[i]);
}
printf("\n");
}

int main() {
int n;
printf("Enter number of elements in the array\n");
scanf("%d",&n);

int a[n];

//taking in the input numbers
int i = 0;
for(i = 0;i < n;i++) {
printf("Enter arr[%d] : ",i);
scanf("%d",&a[i]);
}

//writing insertion sort
int j = 1;//loop counter

for(j = 1;j < n;j++) {
	int key = a[j];
	int i = j-1;
	while(i > -1 && a[i] > key) {
		a[i+1] = a[i];
		i = i - 1;
	}
	a[i+1] = key;
	printf("Step %d : ",j);
	print_array(n,a);
}

//output
printf("---------Output of the array in the ascending order-----------\n");
for(j = 0;j < n;j++) {
printf("%d ",a[j]);
}
printf("\n");
return 0;
}
