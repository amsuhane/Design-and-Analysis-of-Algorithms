#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int data;
	struct node *left;
	struct node *right;
	struct node *parent;
} node,*tree;

tree root = NULL;

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

void bstsort(node *current) {
	if(current == NULL) return;
	bstsort(current->left);
	printf("%d ",current->data);
	bstsort(current->right);
}

int main() {
int n;
printf("Enter n : ");
scanf("%d",&n);
int a[n];

//Taking elements as input
int i = 0;
for(i = 0;i < n;i++) {
	printf("Enter a[%d] : ",i);
	scanf("%d",&a[i]);
	if(i == 0) initialise(a[i]);
	else insert(a[i]);
}

printf("---Printing Sorted Sequence---\n");
bstsort(root);
printf("\n");

return 0;
}
