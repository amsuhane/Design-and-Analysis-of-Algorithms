#include <stdio.h>
#include <stdlib.h>

/***
Implementation of Prims Algorithm implemented using an aray
***/

int V;

#define INF 99999999

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
	int Q[V];//this stores the key values of all the vertices...If some vertex has been visited,it's key is stored as a negative value
	for(i = 0;i < V;i++) {
		Q[i] = INF;
	}
	Q[0] = 0;//start vertex
	
	while(check_empty_queue(Q) == 0) { //while the queue is not empty
		int min_id = find_min(Q);//find the smallest key vertex in the queue...vertex 'u'
		
		Q[min_id] = -1;//extract the element out of the queue...now this element is no longer accessed
		visited[min_id] = 1;

		int j;
		i = min_id;
		for(j = 0;j < V;j++) { //loop over all adjacent vertices of u...vertices 'v'
			if(Graph[i][j] < INF && visited[j] == 0) {
			if(key[j] > Graph[i][j]) {
				key[j] = Graph[i][j];
				Q[j] = Graph[i][j];
				parent[j] = i;
				MST[i][j] = Graph[i][j];
				MST[j][i] = Graph[i][j];
			}
			}
		}
	}
	
	printf("\n\n\n---Printing MST---\n");
	printf("Source : %d\n",0);
	printf("Vertices : Edge\n");
	//printing the MST
	for(i = 0;i < V;i++) {
		if(parent[i] < 0) continue;//case the vertex is the source
		printf("%d - %d : %d\n",i,parent[i],MST[i][parent[i]]);
	}
}

int main() {
	printf("Enter number of vertices : ");
	scanf("%d",&V);
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
	/*
	add_edge(Graph,0,1,4);
	add_edge(Graph,0,6,8);
	
	add_edge(Graph,1,2,8);
	add_edge(Graph,1,6,11);

	add_edge(Graph,2,3,2);
	add_edge(Graph,2,4,4);
	add_edge(Graph,2,7,7);
	
	add_edge(Graph,3,5,6);
	add_edge(Graph,3,6,7);

	add_edge(Graph,4,5,2);
	add_edge(Graph,4,7,14);
	add_edge(Graph,4,8,10);
	
	add_edge(Graph,5,6,1);
	
	add_edge(Graph,7,8,9);
	*/
	
	printf("---Printing Graph---\n");
	print_graph(Graph);
	Prim(Graph,MST);
	
	return 0;
}
