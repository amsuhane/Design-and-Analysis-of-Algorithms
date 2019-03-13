/*** Radix Sort ***/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int n,d,r,bucket_size;

/*** To print the 2D array ***/
void print_global_array(int n,int d,int a[n][d]) {
	printf("---Displaying Array---\n");
	int i = 0,j = 0;
	for(i = 0;i < n;i++) {
		printf("a[%d] : ",i);
		for(j = 0;j < d;j++) {
			printf("%d",a[i][j]);
		}
		printf("\n");
	}
}

/*** Count Sort Implementation For Sorting The Buckets ***/
void count_sort(int a[n][bucket_size],int og_arr[n][d]) {
	//conver decimal to binary
	int dec[n];
	int i = 0,j = 0;
	for(i = 0;i < n;i++) {
	int dec_no = 0;
	int exponent = 0;
	for(j = bucket_size-1;j >= 0;j--) {
		dec_no+=(a[i][j]*((int)(pow(2,exponent))));
		exponent++;
	}
	dec[i] = dec_no;
	}
	
	/* Count Sort On The Decimal Numbers*/
	//stores final count sorted output
	int b[n][d];
	//applying count sort on dec array
	int k = (int)(pow(2,bucket_size)) - 1;

	int c[k+1];
	for(i = 0;i <= k;i++) {
		c[i] = 0;
	}
		
	for(i = 0;i < n;i++) 
		c[dec[i]]++;
	
	for(i = 1;i <= k;i++) 
		c[i] = c[i] + c[i-1];
	
	for(i = n-1;i >= 0;i--) {
		for(j = 0;j < d;j++) {
			b[c[dec[i]] - 1][j] = og_arr[i][j];
		}
		c[dec[i]] = c[dec[i]] - 1;
	}

	//update values of a by taking the values form b
	for(i = 0;i < n;i++) {
		for(j = 0;j < d;j++) {
			og_arr[i][j] = b[i][j];
		}
	}
}

void radix_sort(int a[n][d]) {
int i = 0;
for(i = d-1;i >= 0;i-=bucket_size) {
//getting the bucket in an array
int bucket[n][bucket_size];
int p = 0,q = 0;

for(p = 0;p < n;p++) {
for(q = bucket_size - 1;q >= 0;q--) {
bucket[p][q] = a[p][i - (bucket_size - 1 - q)];
}
}

count_sort(bucket,a);
}
}

int main() {
printf("Enter n : ");
scanf("%d",&n);
printf("Enter d : ");
scanf("%d",&d);
printf("Enter r [Note : d % [2^r] = 0] : ");
scanf("%d",&r);

bucket_size = (int)(pow(2,r));
printf("Bucket size : %d\n",bucket_size);
int a[n][d];
int i = 0,j = 0;
for(i = 0;i < n;i++) {
	printf("Enter digits of the binary number of index[%d] with SPACES : ",i);
	for(j = 0;j < d;j++) {
		scanf("%d",&a[i][j]);
	}
}

print_global_array(n,d,a);
radix_sort(a);
printf("\nAfter Sorting...\n");
print_global_array(n,d,a);

return 0;
}
