#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int data;
	int color;//0 for B and 1 for R
	struct node *left;
	struct node *right;
	struct node *parent;
} node,*tree;

void fixup(node *current);

/***
NOTE : BLACK NIL NODES ARE NOT MAINTAINED
Wherever there is a NULL pointer, we assume that it is a NIL node and is colored black
***/

tree root = NULL;

void initialise(int data) {
	root = (node *)malloc(sizeof(node));
	root->data = data;
	root->color = 0;//Color root black
	root->left = NULL;
	root->right = NULL;
	root->parent = NULL;
}

int is_left_child(node *current) {
	//Utility function to state if a node is a left child of it's parent
	if(current == root) return 0;
	if(current->parent->right == current) return 0;
	return 1;
}

int is_right_child(node *current) {
	//Utility function to state if a node is a left child of it's parent
	if(current == root) return 0;
	if(current->parent->left == current) return 0;
	return 1;
}

void left_rotate(node *current) {
	//Left rotate about current node
	node *parent = current->parent;
	node *right = current->right;
	
	//Fix parent and chlid
	if(is_right_child(current)) {
		parent->right = right;
		right->parent = parent;
	}
	else if(is_left_child(current)){ //current is a left child
		parent->left = right;
		right->parent = parent;
	}
	else { //current node is the root
		right->parent = parent;
		root = right;
	}
	
	//Fix right's left child and current
	current->right = right->left;
	if(right->left != NULL)
		right->left->parent = current;
	
	//Fix current and right
	current->parent = right;
	right->left = current;
}

void right_rotate(node *current) {
	//Right rotate about current node
	node *parent = current->parent;
	node *left = current->left;

	//Fix parent and chlid
	if(is_right_child(current)) {
		parent->right = left;
		left->parent = parent;
	}
	else if(is_left_child(current)){ //current is a left child
		parent->left = left;
		left->parent = parent;
	}
	else { //current node is the root
		left->parent = parent;
		root = left;
	}
	
	//Fix left's right child and current
	current->left = left->right;
	if(left->right != NULL)
		left->right->parent = current;
	
	//Fix current and left
	current->parent = left;
	left->right = current;
}

int get_color(node *current) {
	if(current == NULL) return 0;
	else return current->color;
}

void insert(int data){
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
				current->color = 1;
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
				current->color = 1;
				break;
			}
			else {
				current = current->right;
				continue;
			}
		}
	}

	fixup(current);	
}

void fixup(node *current){
	//Fixes the insertion
	//printf("FIXUP : %d\n",current->data);
	//printf("PARENT OF FIXUP ELEMENT : %d\n",current->parent->data);
	while(current->parent->color == 1) {
		if(is_left_child(current->parent)) {
			node *uncle = current->parent->parent->right;
			if(get_color(uncle) == 1) {
				current->parent->color = 0;
				uncle->color = 0;
				current->parent->parent->color = 1;
				current = current->parent->parent;
			}
			else if(is_right_child(current)) {
				current = current->parent;
				left_rotate(current);
			}
			if(current != root && current != NULL && current->parent != root) {
				current->parent->color = 0;
				current->parent->parent->color = 1;
				right_rotate(current->parent->parent);
			}
			else break;
		}
		else {
			node *uncle = current->parent->parent->left;
			if(get_color(uncle) == 1) {
				current->parent->color = 0;
				uncle->color = 0;
				current->parent->parent->color = 1;
				current = current->parent->parent;
			}
			else if(is_left_child(current)) {
				current = current->parent;
				right_rotate(current);
			}
			if(current != root && current != NULL && current->parent != root) {
				current->parent->color = 0;
				current->parent->parent->color = 1;
				left_rotate(current->parent->parent);
			}
			else break;
		}
	}
	root->color = 0;
}

void inorder(node *current) {
	if(current == NULL) return;
	inorder(current->left);
	printf("%d , COLOR : %d\n",current->data,current->color);
	inorder(current->right);
}

int main() {
	int n;
	printf("Enter number of elements in the tree : ");
	scanf("%d",&n);
	int arr[n];

	int i = 0;
	for(i = 0;i < n;i++) {
		printf("Enter a[%d] : ",i);
		scanf("%d",&arr[i]);
		if(i == 0) initialise(arr[i]);
		else insert(arr[i]);
	}

	/*
	TEST CASE : 
	initialise(4);
	insert(7);
	insert(12);
	insert(15);
	insert(3);
	insert(5);
	insert(14);
	insert(18);
	insert(16);
	insert(17);
	*/

	printf("---Printing Inorder Traversal Of The Tree With Node Colors---(0 : BLACK,1 : RED)\n");
	inorder(root);
	printf("\n");
	printf("ROOT : %d\n",root->data);
	return 0;
}
