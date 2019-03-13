#include <stdio.h>

/* Array Implementation */

int n;
typedef struct {
	int i,j,data;
} Element;

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
//taking n as input
printf("Enter n : ");
scanf("%d",&n);

//declaring the matrices
int A[n][n];
int B[n][n];
int C[n][n];//result

Element non_zero_A[n*n];//stores the non-zero elements of A
Element non_zero_B[n*n];//stores the non-zero elements of B

//stores number of non zero elements in A and B
int num_non_zero_in_A = 0,num_non_zero_in_B = 0;

int i,j;//loop counters

//taking elements of A as input
for(i = 0;i < n;i++){
	for(j = 0;j < n;j++){
		printf("Enter A[%d][%d] : ",i,j);
		scanf("%d",&A[i][j]);
		if(A[i][j] != 0) {
		non_zero_A[num_non_zero_in_A].data = A[i][j];
		non_zero_A[num_non_zero_in_A].i = i;
		non_zero_A[num_non_zero_in_A].j = j;
		num_non_zero_in_A++;
	}
	}
}

//initialize all elements of C to zero
for(i = 0;i < n;i++) {
	for(j = 0;j < n;j++) {
		C[i][j] = 0;
	}
}

//taking elements of B as input
for(i = 0;i < n;i++){
	for(j = 0;j < n;j++){
		printf("Enter B[%d][%d] : ",i,j);
		scanf("%d",&B[i][j]);
		if(B[i][j] != 0) {
		non_zero_B[num_non_zero_in_B].data = B[i][j];
		non_zero_B[num_non_zero_in_B].i = i;
		non_zero_B[num_non_zero_in_B].j = j;
		num_non_zero_in_B++;
	}
	}
}

/*** Main Logic ***/
/*
For every non-zero entry in A,loop over all the columns in B and find if the col of A matches with the row of B
If it does,append the corresponding entry in C
*/
for(i = 0;i < num_non_zero_in_A;i++) {
	int row = non_zero_A[i].i; //row of element of A
	int col = non_zero_A[i].j; //col of element of A
	int data = non_zero_A[i].data; //data of element of A
	
	for(j = 0;j < num_non_zero_in_B;j++) {
		int row_B = non_zero_B[j].i;//correspoding row of an element in B
		int col_B = non_zero_B[j].j;//correspoding col of an element in B
		int data_B = non_zero_B[j].data;//corresponding data of element in B
		if(col == row_B) { //if it's possible to take this product
			C[row][col_B]+=(data*data_B); //add the product to it's position in C
		}
	}
}

//Displaying the output
printf("A -- \n");
display_mat(A);
printf("B -- \n");
display_mat(B);
printf("C -- \n");
display_mat(C);

return 0;
}
