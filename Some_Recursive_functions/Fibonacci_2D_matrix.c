#include <stdio.h>
//NOTE : 0th fibonacci number is 0 and 1st fibonacci number is 1

//structure definition for matrix type
typedef struct {
int a00,a01,a10,a11;
/*
Format is below:
[a00 a01]
[a10 a11]
*/
} Mat;

//global structure for the base case of Fibonacci numbers
Mat a;

//function to print the structure
void print_struct(Mat b) {
printf("%d %d\n",b.a00,b.a01);
printf("%d %d\n",b.a10,b.a11);
}

//matrix multiplication function
Mat matmul(Mat b,Mat c) {
Mat out;
out.a00 = b.a00*c.a00 + b.a01*c.a10;
out.a01 = b.a00*c.a01 + b.a01*c.a11;
out.a10 = b.a10*c.a00 + b.a11*c.a10;
out.a11 = b.a10*c.a01 + b.a11*c.a11;
return out;
}

//recursive function definition
Mat power(int n) {
if(n == 0) {
//return the identity matrix
Mat I;
I.a00 = 1;
I.a01 = 0;
I.a10 = 0;
I.a11 = 1;
return I;
}

if(n == 1) {
return a;
}

if(n%2 == 0) {
return matmul(power(n/2),power(n/2));
}
else {
return matmul(matmul(power((n-1)/2),power((n-1)/2)),a);
}
}

int main() {
int n;
printf("Enter n : ");
scanf("%d",&n);
//base case matrix initilisation
a.a00 = 1;
a.a01 = 1;
a.a10 = 1;
a.a11 = 0;
printf("NOTE : 0th fibonacci number is 0 and 1st fibonacci number is 1\n");
//NOTE : 0th fibonacci number is 0 and 1st fibonacci number is 1
Mat out = power(n);
printf("Printing matrix : \n");
print_struct(out);
printf("Printing index [%d] of fibonacci number : %d\n",n,out.a01);
return 0;
}
