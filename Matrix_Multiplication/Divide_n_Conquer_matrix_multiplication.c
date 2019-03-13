#include <stdio.h>

/***Divide and Conquer ***/

int n;

int** add(int l,int **a,int **b) { //l = 1

	int i = 0,j = 0;

	/***Allocating memory***/
	int **c = (int **)malloc((l+1)*sizeof(int *)); //2x2
	for(i = 0; i < (l+1);i++) {
	c[i] = (int *)malloc((l+1)*sizeof(int *));
	}
	/***********************/

	for(i = 0;i < (l+1);i++) {//i < 1
	for(j = 0;j < (l+1);j++) {//j < 1
	c[i][j] = a[i][j] + b[i][j];
	}
	}

	return c;
}

int** matmul(int l,int **a,int **b) { //l = 1
//output is a lxl matrix
	int i = 0,j = 0;

	/***Allocating memory***/
	int **c = (int **)malloc((l+1)*sizeof(int *));//2x2
	for(i = 0; i < l+1;i++) {
	c[i] = (int *)malloc((l+1)*sizeof(int *));
	}
	/***********************/


	if(l == 0) {
	c[0][0] = a[0][0]*b[0][0];
	return c;
	}

	//declaring the different sub-matrices of size l/2xl/2
	int t = l/2;//t = 0
	int **a00 = (int **)malloc((t+1)*sizeof(int *));//1x1
	int **a01 = (int **)malloc((t+1)*sizeof(int *));
	int **a10 = (int **)malloc((t+1)*sizeof(int *));
	int **a11 = (int **)malloc((t+1)*sizeof(int *));
	int **b00 = (int **)malloc((t+1)*sizeof(int *));
	int **b01 = (int **)malloc((t+1)*sizeof(int *));
	int **b10 = (int **)malloc((t+1)*sizeof(int *));
	int **b11 = (int **)malloc((t+1)*sizeof(int *));

	for(i = 0;i < (l+1)/2;i++) {//i < 1
	a00[i] = (int *)malloc(n*sizeof(int *));
	a01[i] = (int *)malloc(n*sizeof(int *));
	a10[i] = (int *)malloc(n*sizeof(int *));
	a11[i] = (int *)malloc(n*sizeof(int *));
	b00[i] = (int *)malloc(n*sizeof(int *));
	b01[i] = (int *)malloc(n*sizeof(int *));
	b10[i] = (int *)malloc(n*sizeof(int *));
	b11[i] = (int *)malloc(n*sizeof(int *));
	}

	//adding values in a
	for(i = 0;i < l+1;i++) { //i < 2
	for(j = 0;j < l+1;j++) {
	if(i <= t && j <= t) {
	a00[i][j] = a[i][j];
	}
	else if(i <= t && j > t) {
	a01[i][j-t-1] = a[i][j];
	}
	else if(i > t && j <= t) {
	a10[i-t-1][j] = a[i][j];
	}
	else {
	a11[i-t-1][j-t-1] = a[i][j];
	}
	}
	}

//adding values in b
	for(i = 0;i < l+1;i++) { //i < 2
	for(j = 0;j < l+1;j++) {
	if(i <= t && j <= t) {
	b00[i][j] = b[i][j];
	}
	else if(i <= t && j > t) {
	b01[i][j-t-1] = b[i][j];
	}
	else if(i > t && j <= t) {
	b10[i-t-1][j] = b[i][j];
	}
	else {
	b11[i-t-1][j-t-1] = b[i][j];
	}
	}
	}

	int **c00 = add(t,matmul(t,a00,b00),matmul(t,a01,b10));
	int **c01 = add(t,matmul(t,a00,b01),matmul(t,a01,b11));
	int **c10 = add(t,matmul(t,a10,b00),matmul(t,a11,b10));
	int **c11 = add(t,matmul(t,a10,b01),matmul(t,a11,b11));

	//update c
	for(i = 0;i < l+1;i++) { //i < 2
	for(j = 0;j < l+1;j++) {
	if(i <= t && j <= t) {
	c[i][j] = c00[i][j];
	}
	else if(i <= t && j > t) {
	c[i][j] = c01[i][j-t-1];
	}
	else if(i > t && j <= t) {
	c[i][j] = c10[i-t-1][j];
	}
	else {
	c[i][j] = c11[i-t-1][j-t-1];
	}
	}
	}

	return c;
}

void display_mat(int l,int **mat) {
	int i = 0,j = 0;
	for(i = 0;i < l;i++) {
	for(j = 0;j < l;j++) {
	printf("%d ",mat[i][j]);
	}
	printf("\n");
	}
	printf("\n");
}

int main() {
printf("Enter n : ");
scanf("%d",&n);
int **A = (int **)malloc(n*sizeof(int *));
int **B = (int **)malloc(n*sizeof(int *));

int i = 0,j = 0,k = 0;


//accept the data
//A
for(i = 0;i < n;i++) {
A[i] = (int *)malloc(n*sizeof(int *));
for(j = 0 ;j < n;j++) {
printf("Enter A[%d][%d] : ",i,j);
scanf("%d",&A[i][j]);
}
}


//B
for(i = 0;i < n;i++) {
B[i] = (int *)malloc(n*sizeof(int *));
for(j = 0 ;j < n;j++) {
printf("Enter B[%d][%d] : ",i,j);
scanf("%d",&B[i][j]);
}
}


printf("---A---\n");
display_mat(n,A);

printf("---B---\n");
display_mat(n,B);

printf("---C=AxB---\n");

int **C = matmul(n-1,A,B);
display_mat(n,C);

return 0;
}
