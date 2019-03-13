#include <stdio.h>

/*** Strassen's algorithm ***/

int n;

int** test(int **A) {
printf("%d\n",A[0][0]);
return A;
}

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

int** sub(int l,int **a,int **b) { //l = 1

int i = 0,j = 0;

/***Allocating memory***/
int **c = (int **)malloc((l+1)*sizeof(int *)); //2x2
for(i = 0; i < (l+1);i++) {
c[i] = (int *)malloc((l+1)*sizeof(int *));
}
/***********************/

for(i = 0;i < (l+1);i++) {//i < 1
for(j = 0;j < (l+1);j++) {//j < 1
c[i][j] = a[i][j] - b[i][j];
}
}

return c;
}

int** matmul(int l,int **a,int **b) { //l = 1
//printf("START : %d\n",l);
//output is a lxl matrix
int i = 0,j = 0;
//printf("IN");
/***Allocating memory***/
int **c = (int **)malloc((l+1)*sizeof(int *));//2x2
for(i = 0; i < l+1;i++) {
c[i] = (int *)malloc((l+1)*sizeof(int *));
}
/***********************/
//display_mat(l+1,c);

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

int **p1 = matmul(t,a00,sub(t,b01,b11));
int **p2 = matmul(t,add(t,a00,a01),b11);
int **p3 = matmul(t,add(t,a10,a11),b00);
int **p4 = matmul(t,a11,sub(t,b10,b00));
int **p5 = matmul(t,add(t,a00,a11),add(t,b00,b11));
int **p6 = matmul(t,sub(t,a01,a11),add(t,b10,b11));
int **p7 = matmul(t,sub(t,a00,a10),add(t,b00,b01));

//display_mat((l+1)/2,a00);
//printf("IN2\n");
int **c00 = add(t,add(t,p5,p6),sub(t,p4,p2));
//printf("IN3\n");
int **c01 = add(t,p1,p2);
int **c10 = add(t,p3,p4);
int **c11 = add(t,sub(t,p5,p7),sub(t,p1,p3));

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
//matmul(A,B,C);
display_mat(n,C);


//printf("A");


/* int **C = test(A); (int **)malloc(n*sizeof(int *));
for(i = 0; i < n;i++) {
D[i] = (int *)malloc(n*sizeof(int *));
}

D = test(A);

printf("%d\n",*(*(D+1)+1));
*/

return 0;
}
