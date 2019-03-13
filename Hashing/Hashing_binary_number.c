#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*** Hashing ***/
long long int m;//size of the hash table
long long int n;//number of keys to enter
long long int w;//w-bit number
long long int r;//m = 2^r
long long int A;

//linked list
typedef struct node {
long long int data;
struct node *next;
} node,*list;

void print_table(node *a[m]){
	int i;//loop counter
	for(i = 0;i < m;i++) {
		if(a[i] != NULL) {
			node *current = a[i];
			printf("Slot %d : ",i);
			while(current != NULL) {
				printf("%lld -> ",current->data);
				current = current->next;
			}
		printf("NULL\n");
		}	
		else {
			printf("Slot %d : NULL\n",i);
		}
	}
}


long long int h(long long int k,long long int A) {
	long long int divisor = (long long int)pow(2,w);//stores 2^w

	long long int slot = (A*k)%divisor;
	//right shift the slot value by w-r bits
	long long int div = (long long int)pow(2,w-r);
	slot = slot/div;
	
	return slot;//slot to which the key hashes
}	

int main() {
printf("Enter number of keys : ");
scanf("%lld",&n);
printf("Enter w : ");
scanf("%lld",&w);
printf("Enter r [m = 2^r] (Value of r must be less w): ");
scanf("%lld",&r);

long long int divisor = (long long int)pow(2,w);//stores 2^w

printf("Enter A in range [0,%lld] (The number is then w bits when converted into the binary form) : ",divisor - 1);
scanf("%lld",&A);

m = (long long int)pow(2,r);

//the hash table
node* a[m];

int i;//loop counter
for(i = 0;i < m;i++) {
a[i] = NULL;
}

for(i = 0;i < n;i++) {
	long long int no;
	no = rand();
	
	//convert the decimal to a decimal number which is of w bits in the binary format
	no = no%divisor;
	long long int slot = h(no,A);

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
