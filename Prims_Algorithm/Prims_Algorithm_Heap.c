#include <stdio.h>
#include <stdlib.h>

int V;
int n;

#define INF 99999999

typedef struct Q_elem {
	int d;
	int id;
} Q_elem;

/*** Implementing the heap ***/
void print_array(Q_elem a[]) {
	int i = 0;
	printf("Displaying Array ---\n");
	for(i = 0;i < n;i++) {
		printf("%d ",a[i].d);
	}
	printf("\n");
}

void swap(Q_elem *p,Q_elem *q) {
Q_elem tmp = *p;
*p = *q;
*q = tmp;
}

void min_heapify(Q_elem a[],int i,int heap_size) { //assume i is given in 1 indexed format
	int l = 2*(i);
	int r = 2*(i) + 1;
	int smallest = i;
	int value_smallest = a[i-1].d;
	//left element is indexed at l-1 and right element is indexed at r-1
	if((l-1) < heap_size) {
		if(a[l-1].d < value_smallest) {
			smallest = l;
			value_smallest = a[l-1].d;
		}
	}
	if((r-1) < heap_size) {
		if(a[r-1].d < value_smallest) {
			smallest = r;
			value_smallest = a[r-1].d;
		}
	}	
	if(smallest != i) {
		swap(&a[i-1],&a[smallest-1]);
		min_heapify(a,smallest,heap_size);
	}
}

void build_min_heap(Q_elem a[],int heap_size) {
	int i = 1;
	for(i = (heap_size/2);i >= 1;i--) {
		min_heapify(a,i,heap_size);
	}
}


Q_elem extract_min(Q_elem a[],int heap_size) {
	swap(&a[0],&a[heap_size-1]);
	Q_elem min = a[heap_size-1];
	return min;
}

/*****************************/
void add_edge(int Graph[V][V],int u,int v,int wt) {
	//add edge of weight w between u and v
	Graph[u][v] = wt;
	Graph[v][u] = wt;
}

void print_graph(int Graph[V][V]) {
	int i,j;
	printf("Vertices : Edge\n");
	for(i = 0;i < V;i++) {
		for(j = 0;j < V;j++) {
			if(Graph[i][j] < INF) {
				printf("%d - %d : %d\n",i,j,Graph[i][j]);
			}
		}
	}
}

int find_min(int Q[V]) {
	int i,min_id = -1,min = INF;
	for(i = 0;i < V;i++) {
		if(Q[i] < min && Q[i] >= 0) {
			min = Q[i];
			min_id = i;
		}
	}
	return min_id;
}

int check_empty_queue(int Q[V]) {
	//if queue is empth, the array used for it's implementation has al negative values...
	int empty = 1;
	int i;
	for(i = 0;i < V;i++) {
		if(Q[i] >= 0) {
			empty = 0;
			break;
		}
	}
	return empty;
}

void Prim(int Graph[V][V],int MST[V][V]) {
	int key[V],parent[V],i;
	int visited[V];
	
	for(i = 0;i < V;i++) {
		key[i] = INF;
		parent[i] = -1;//equivalent to NIL
		visited[i] = 0;
	}

	//start from the 0 indexed vertex
	key[0] = 0;
	visited[0] = 1;
	
	//intialise Queue as an array
	Q_elem Q[V];//this stores the key values of all the vertices...If some vertex has been visited,it's key is stored as a negative value
	for(i = 0;i < V;i++) {
		Q[i].d = INF;
		Q[i].id = i;
	}
	Q[0].d = 0;//start vertex

	build_min_heap(Q,V);
	int heap_size = V;

	while(heap_size > 1) { //while the queue is not empty
		build_min_heap(Q,heap_size);

		Q_elem min = extract_min(Q,heap_size);//find the smallest key vertex in the queue...vertex 'u'
		printf("Heap Size : %d\n",heap_size);

		heap_size = heap_size - 1;

		int x;
		for(x = 0;x < V;x++) printf("Q[%d].d : %d\n",x,Q[x].d);

		int min_id = min.id;
		printf("id : %d, d : %d\n",min.id,min.d);

		visited[min_id] = 1;

		int j;
		i = min_id;
		for(j = 0;j < V;j++) { //loop over all adjacent vertices of u...vertices 'v'
			if(Graph[i][j] < INF && visited[j] == 0) {
			if(key[j] > Graph[i][j]) {
				key[j] = Graph[i][j];
				
				//update the values in the queue
				int k;
				for(k = 0;k < heap_size;k++) {
					if(Q[k].id == j) Q[k].d = Graph[i][j];
				}

				parent[j] = i;
				MST[i][j] = Graph[i][j];
				MST[j][i] = Graph[i][j];
			}
			}
		}
	}
	
	printf("\n\n\n---Printing MST---\n");
	//printing the MST
	for(i = 0;i < V;i++) {
		if(parent[i] < 0) continue;//case the vertex is the source
		printf("%d - %d : %d\n",i,parent[i],MST[i][parent[i]]);
	}
}

int main() {
	printf("Enter number of vertices : ");
	scanf("%d",&V);
	n = V;
	
	//V = 9;
	int Graph[V][V];
	int MST[V][V];//visualising MST as a graph
	
	//initialising all the edges with weight = inf.
	int i,j;
	for(i = 0;i < V;i++) {
		for(j = 0;j < V;j++) {
			Graph[i][j] = INF;
			MST[i][j] = INF;
		}
	}
	
	//add edges
	
	int inp = 1;
	
	printf("Enter edges for a connected graph and maximum weight is less than 99999999 and weights are >= 0--- \n");
	
	while(inp == 1) {
		printf("Enter 1 for adding an edge between 2 vertices and -1 to exit : ");
		scanf("%d",&inp);
		if(inp == -1) break;
		else {
			int u,v,w;
			printf("Enter index of vertex u : ");
			scanf("%d",&u);
			printf("Enter index of vertex v : ");
			scanf("%d",&v);
			printf("Enter weight of edge : ");
			scanf("%d",&w);
			add_edge(Graph,u,v,w);
		}
	}

	
	printf("---Printing Graph---\n");
	print_graph(Graph);
	Prim(Graph,MST);
	return 0;
}
