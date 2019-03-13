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

node *search(node *current,int data) {
	if(current == NULL) return NULL;
	if(current->data == data) return current;
	else {
		if(data < current->data)
			return search(current->left,data);
		else
			return search(current->right,data);
	}
}

void inorder(node *current) {
	if(current == NULL) return;
	inorder(current->left);
	printf("%d ",current->data);
	inorder(current->right);
}

//--- Longest Common Ancestor Code ---
node *lca(node *r,int n1,int n2) {
	if(r == NULL) return NULL;

	if(r->data > n1 && r->data > n2)
		return lca(r->left,n1,n2);
	if(r->data<n1 && r->data<n2)
		return lca(r->right,n1,n2);
	return r;
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

printf("Enter first element : ");
int n1;
scanf("%d",&n1);
printf("Enter second element : ");
int n2;
scanf("%d",&n2);

node *curr = search(root,n1);
node *curr1 = search(root,n2);

if(curr == NULL || curr1 == NULL) printf("Either of the elements do not exist\n");
else {
	node *ancestor = lca(root,curr->data,curr1->data);
	printf("%d\n",ancestor->data);
}

return 0;
}
