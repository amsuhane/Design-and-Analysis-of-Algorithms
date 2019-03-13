#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*** Double Hashing ***/
long long int m;//size of the hash table
long long int n;//number of keys to enter
long long int w;//w-bit number
long long int r;//m = 2^r
long long int A;

void print_table(long long int a[m],long long int empty[m]) {
int i;
for(i = 0;i < m;i++) {
	if(empty[i] == 0)
		printf("SLOT %d : %lld \n",i,a[i]);
	else
		printf("SLOT %d : EMPTY \n",i);
}
}

long long int h1(long long int k) {
	return k%m;
}

long long int h2(long long int k,long long int A) {
	long long int divisor = (long long int)pow(2,w);//stores 2^w

	long long int slot = (A*k)%divisor;
	//right shift the slot value by w-r bits
	long long int div = (long long int)pow(2,w-r);
	slot = slot/div;
	
	return slot;//slot to which the key hashes
}

int main() {
/*** Input ***/
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
/*************/

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

	//convert the decimal to a decimal number which is of w bits in the binary format
	no = no%divisor;

	long long int probe_index = 0;
	long long int slot;
	long long int h_1 = h1(no);
	long long int h_2 = h2(no,A);

	while(1) {
		//Double Hashing
		slot = (h_1 + probe_index*h_2)%m;
		if(empty[slot] == 1) {
			empty[slot] = 0;//that slot is not empty now
			a[slot] = no;
			break;
		}	
		probe_index++;
		if(probe_index > m) //clearly no slot found
			break;
	}	
}

printf("------Printing Table---------\n"); 
print_table(a,empty);
}
