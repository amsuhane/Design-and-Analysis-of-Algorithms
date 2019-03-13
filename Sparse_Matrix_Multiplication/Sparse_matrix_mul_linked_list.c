#include <stdio.h>
#include <stdlib.h>

/* Linked List Implementation */

int n;

typedef struct {
	int i,j,data;
	struct node *next;
} node,*list;

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
//reference pointers for the head of the two lists
//these are a list if (i,j,data) pairs storing all non-zero elements in the arrays A and B
list head = NULL;//list for elements of A
list head_B = NULL;//list for elements of B

//taking n as input
printf("Enter n : ");
scanf("%d",&n);

//storing the matrices
int A[n][n];
int B[n][n];
int C[n][n];//result

//stores number of non zero elements in A and B
int num_non_zero_in_A = 0,num_non_zero_in_B = 0;

int i,j;//loop counters

//taking matrix A as input
for(i = 0;i < n;i++){
	for(j = 0;j < n;j++){
		printf("Enter A[%d][%d] : ",i,j);
		scanf("%d",&A[i][j]);
		if(A[i][j] != 0) {
		if(head == NULL) { //if the list for A has not yet been initialized,initialize it
			head = (node *)malloc(sizeof(node));
			head->i = i;
			head->j = j;
			head->data = A[i][j];
			head->next = NULL;
		}
		else { //else go to the end of the list and append this node 
			node *n = (node *)malloc(sizeof(node));
			n->i = i;
			n->j = j;
			n->data = A[i][j];
			node *current = head;
			//iterate over list to insert element at the end
			while(current->next) {
				current = current->next;
			}
			current->next = n;
			current = current->next;
			current->next = NULL;
		}
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

//taking matrix B as input
for(i = 0;i < n;i++){
	for(j = 0;j < n;j++){
		printf("Enter B[%d][%d] : ",i,j);
		scanf("%d",&B[i][j]);
		if(B[i][j] != 0) {
		if(head_B == NULL) { //if the list for the non-zero elements in B has not yet been initialized,initialize it
			head_B = (node *)malloc(sizeof(node));
			head_B->i = i;
			head_B->j = j;
			head_B->data = B[i][j];
			head_B->next = NULL;
		}
		else { //iterate over the list to append the new element to the end
			node *n = (node *)malloc(sizeof(node));
			n->i = i;
			n->j = j;
			n->data = B[i][j];
			node *current = head_B;
			//iterate over list to insert element at the end
			while(current->next) {
				current = current->next;
			}
			current->next = n;
			current = current->next;
			current->next = NULL;
		}
		num_non_zero_in_B++;
	}
	}
}

/*** Iterate over the non-zero elements in A and B ***/
node *current_A = head;
node *current_B = head_B;

/*** Main Logic ***/
/*
For every non-zero entry in A,loop over all the columns in B and find if the col of A matches with the row of B
If it does,append the corresponding entry in C
*/
while(current_A) {
	current_B = head_B;
	//these store the data for the current non-zero entry in A
	int row = current_A->i;
	int col = current_A->j;
	int data = current_A->data;
	
	//iterate over all the non-zero entries in B
	while(current_B) {
	//stores the data for the current non-zero entry in B
	int row_B = current_B->i;
	int col_B = current_B->j;
	int data_B = current_B->data;
	
	if(col == row_B) {
		C[row][col_B]+=(data*data_B);
	}
	current_B = current_B->next;
	}
	current_A = current_A->next;
}

//display the matrices in the output
printf("A -- \n");
display_mat(A);
printf("B -- \n");
display_mat(B);
printf("C -- \n");
display_mat(C);

return 0;
}
