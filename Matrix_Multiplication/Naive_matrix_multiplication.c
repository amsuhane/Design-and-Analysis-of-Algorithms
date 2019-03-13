#include <stdio.h>

/*** Naive Algorithm ***/

int n;

void matmul(int A[n][n],int B[n][n],int C[n][n]) {
int i = 0,j = 0,k = 0;
for(i = 0;i < n;i++) {
for(j = 0;j < n;j++) {
int sum = 0;
for(k = 0;k < n;k++) {
sum+=A[i][k]*B[k][j];
}
C[i][j] = sum;
}
}
}

void display_mat(int mat[n][n]) {
int i = 0,j = 0;
for(i = 0;i < n;i++) {
for(j = 0;j < n;j++) {
printf("%d ",mat[i][j]);
}
printf("\n");
}
printf("\n");
}

int main() {
printf("Enter n : ");
scanf("%d",&n);
int A[n][n],B[n][n],C[n][n];

int i = 0,j = 0,k = 0;

//accept the data
//A
for(i = 0;i < n;i++) {
for(j = 0 ;j < n;j++) {
printf("Enter A[%d][%d] : ",i,j);
scanf("%d",&A[i][j]);
}
}

//B
for(i = 0;i < n;i++) {
for(j = 0 ;j < n;j++) {
printf("Enter B[%d][%d] : ",i,j);
scanf("%d",&B[i][j]);
}
}

printf("---A---\n");
display_mat(A);

printf("---B---\n");
display_mat(B);

printf("---C=AxB---\n");
matmul(A,B,C);
display_mat(C);

return 0;
}
