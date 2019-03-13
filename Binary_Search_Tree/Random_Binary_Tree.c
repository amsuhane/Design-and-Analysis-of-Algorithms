#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int data;
	struct node *left;
	struct node *right;
	struct node *parent;
	int height; //To store height
} node,*tree;

tree root = NULL;
int n;

//Utils
int max(int a,int b) {
	if(a >= b) return a;
	else return b;
}

void swap(int *a,int *b) {
	int t = *a;
	*a = *b;
	*b = t;
}

void print_array(int n,int a[n]) {
	int i = 0;
	for(i = 0;i < n;i++) {
		printf("%d ",a[i]);
	}
	printf("\n");
}

int height(node *current) {
	if(current->parent == NULL) current->height = 0;
	else current->height = current->parent->height + 1;
	
	if(current->left == NULL && current->right == NULL) return current->height;

	if(current->left == NULL) return height(current->right);
	else if(current->right == NULL) return height(current->left);
	else return max(height(current->left),height(current->right));
}

void initialise(int data) {
	root = (node *)malloc(sizeof(node));
	root->data = data;
	root-> left = NULL;
	root->right = NULL;
	root->parent = NULL;
}

void insert(int data) {
	node *current = root;
	while(1) {
		if(data <= current->data) {
			if(current->left == NULL) {
				//add the element
				current->left = (node *)malloc(sizeof(node));
				current->left->parent = current;
				current = current->left;
				current->left = NULL;
				current->right = NULL;
				current->data = data;
				break;
			}
			else {
				current = current->left;
				continue;
			}
		}

		else {
			if(current->right == NULL) {
				//add the element
				current->right = (node *)malloc(sizeof(node));
				current->right->parent = current;
				current = current->right;
				current->left = NULL;
				current->right = NULL;
				current->data = data;
				break;
			}
			else {
				current = current->right;
				continue;
			}
		}
	}
}

void inorder(node *current) {
	if(current == NULL) return;
	inorder(current->left);
	printf("%d ",current->data);
	inorder(current->right);
}

int main() {
printf("***NOTE : Height of root is taken as 0 here***\n");

printf("Enter n : ");
scanf("%d",&n);
int a[n];

float sum_heights = 0;//used for storing the average height

int perm;
printf("Enter number of times to permute the array : ");
scanf("%d",&perm);

//Taking elements as input
int i = 0;
for(i = 0;i < n;i++) {
	printf("Enter a[%d] : ",i);
	scanf("%d",&a[i]);
	if(i == 0) initialise(a[i]);
	else insert(a[i]);
}

//Printing Outputs
int h = height(root);
printf("---Before permuting---\n");
printf("Height of the tree : %d\n",h);
printf("Inorder traversal of the BST : ");
inorder(root);
printf("\n");
int h_BST = h;

/*** Permuting the array ***/
printf("\nPrinting Array Before Permutation : ");
print_array(n,a);

printf("\n---Carrying the permutation step %d times...---\n",perm);

int t = perm;
int pass = 1;

while(t--) {
	printf("---Pass : %d---\n",pass);
	pass++;
	
	//Permuting the array
	int j = 0;
	for(i = n-1;i > 0;i--) {
		j = rand()%(i+1);
		swap(&a[i],&a[j]);
	}

	printf("Printing Array After Permutation : ");
	print_array(n,a);

	root = NULL;
	for(i = 0;i < n;i++) {
		if(i == 0) initialise(a[i]);
		else insert(a[i]);
	}

	h = height(root);
	sum_heights+=h;

	printf("---After permuting---\n");
	printf("Height of the tree : %d\n",h);
	//printf("Inorder traversal of the BST : ");
	//inorder(root);
	printf("\n");
}

float avg_height = sum_heights/(1.0*perm);
printf("Average Height Of Randomly Built BSTs : %f\n",avg_height);
printf("Height of Original BST : %d\n",h_BST);

return 0;
}
