/*** Counting Sort ***/

#include <stdio.h>
#include <stdlib.h>

int n,k;

void print_array(int t,int a[t]) {
	int i = 0;
	printf("---Displaying Array---\n");
	for(i = 0;i < t;i++) {
		printf("%d ",a[i]);
	}
	printf("\n");
}

int main() {
printf("Enter n : ");
scanf("%d",&n);
printf("Enter k : ");
scanf("%d",&k);

int a[n],b[n],c[k+1];
int i = 0;
for(i = 0;i < n;i++) {
	printf("Enter a[%d] (value in range [0,k]): ",i);
	scanf("%d",&a[i]);
}

print_array(n,a);
for(i = 0;i <= k;i++) {
c[i] = 0;
}

for(i = 0;i < n;i++) 
	c[a[i]] = c[a[i]] + 1;

for(i = 1;i <= k;i++) 
	c[i] = c[i] + c[i-1];

for(i = n-1;i >= 0;i--) {
	b[c[a[i]] - 1] = a[i];
	c[a[i]] = c[a[i]] - 1;
}
printf("\nAfter Sorting...\n");
print_array(n,b);

return 0;
}
