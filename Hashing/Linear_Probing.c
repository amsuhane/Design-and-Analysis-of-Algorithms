#include <stdio.h>
#include <stdlib.h>

/*** Linear Probing ***/
long long int m;//size of the hash table
long long int n;//number of keys to enter

void print_table(long long int a[m],long long int empty[m]) {
int i;
for(i = 0;i < m;i++) {
	if(empty[i] == 0)
		printf("SLOT %d : %lld \n",i,a[i]);
	else
		printf("SLOT %d : EMPTY \n",i);
}
}

int main() {
printf("Enter number of keys : ");
scanf("%lld",&n);
printf("Enter size of hash table (Please ensure size of hash table os greater than the number of keys) :");
scanf("%lld",&m);

//the hash table
long long int a[m];
long long int empty[m];
long long int i;
for(i = 0;i < m;i++) {
	a[i] = 0;
	empty[i] = 1;
}

for(i = 0;i < n;i++) {
	long long int no;
	no = rand();
	long long int probe_index = 0;
	long long int slot;
	
	while(1) {
		slot = (no%m + probe_index)%m;
		if(empty[slot] == 1) {
			empty[slot] = 0;//that slot is not empty now
			a[slot] = no;
			break;
		}	
		probe_index++;
		if(probe_index > m)
			break;
	}	
}

printf("------Printing Table---------\n"); 
print_table(a,empty);
return 0;
}
