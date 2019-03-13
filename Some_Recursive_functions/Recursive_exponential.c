#include <stdio.h>

//global variables
int a,n;

int power(int n) {
//base cases
if(n == 0) return 1;
if(n == 1) return a;

//different cases for even and odd powers
if(n%2 == 0) return power(n/2)*power(n/2);
else return power((n-1)/2)*power((n-1)/2)*a;
}

int main() {
printf("Enter a = ");
scanf("%d",&a);
printf("Enter n = ");
scanf("%d",&n);
int out = power(n);

printf("%d^%d = %d\n",a,n,out);
}
