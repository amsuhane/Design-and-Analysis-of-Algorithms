#include <stdio.h>
#include <stdlib.h>

/*** Hashing ***/
long long int m;//size of the hash table
long long int n;//number of keys to enter

//linked list
typedef struct node {
int data;
struct node *next;
} node,*list;

void print_table(node *a[m]){
	int i;//loop counter
	for(i = 0;i < m;i++) {
		if(a[i] != NULL) {
			node *current = a[i];
			printf("Slot %d : ",i);
			while(current != NULL) {
				printf("%d -> ",current->data);
				current = current->next;
			}
		printf("NULL\n");
		}	
		else {
			printf("Slot %d : NULL\n",i);
		}
	}
}

int main() {
printf("Enter number of keys : ");
scanf("%lld",&n);
printf("Enter size of hash table : ");
scanf("%lld",&m);

//the hash table
node* a[m];

int i;//loop counter
for(i = 0;i < m;i++) {
a[i] = NULL;
}

for(i = 0;i < n;i++) {
	long long int no;
	no = rand();
	long long int slot = no%m;

	if(a[slot] == NULL) {
		a[slot] = (node *)malloc(sizeof(node));
		a[slot]->next = NULL;
		a[slot]->data = no;
	}	
	else {	
		//insert at the start of the list
		node *n = (node *)malloc(sizeof(node));
		n->data = no;
		n->next = a[slot];
		a[slot] = n;
	}
}

printf("------Printing Table---------\n"); 
print_table(a);
return 0;
}
