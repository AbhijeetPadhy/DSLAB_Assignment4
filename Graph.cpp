#include "Graph.h"
#include "min_heap.h"

Graph::Graph()
{
	V = 0;
	adj = new vector<pair<int,int>>[V];
}

Graph::Graph(int v)
{
	V = v;
	adj = new vector<pair<int,int>>[V];
}

int Graph::add_edge(int src, int dest){
	return add_edge(src, dest, 1);
}

int Graph::add_edge(int src, int dest, int weight){
	if(src >= V || src < 0 || dest >= V || dest < 0)
		return 1;
	pair<int, int> edge(dest, weight);
	adj[src].push_back(edge);
	return 0;
}

int Graph::get_num_vertices(){
	return V;
}

void Graph::dijsktras_shortest_path_algorithm(int S){
	min_heap *heap = new min_heap(V);
	int dist[V];
	for(int i=0;i<V;i++){
		dist[i] = INT_MAX;
		if(i == S)
			dist[i] = 0;
		heap->push(make_pair(i, dist[i]));
	}
	
	while(heap->size() != 0){
        pair<int,int> u = heap->pop();
        int no_of_adj_nodes = adj[u.first].size();
        
		for(int j=0;j<no_of_adj_nodes;j++){
            int v = adj[u.first].at(j).first;
            int weight = adj[u.first].at(j).second;
			if(u.second != INT_MAX && u.second + weight < dist[v]){
                dist[v] = u.second + weight;
				heap->decrease_key(v, dist[v]);
            }
        }
    }
    
    for(int i=0;i<V;i++){
    	cout<<"Node "<<i<<" has dist = " << dist[i]<<endl;
	}
	output_dijsktra(dist);
}

void Graph::output_dijsktra(int dist[]){
	FILE *fptr;
	fptr = fopen("dijsktra_output.gv","w");
	fprintf(fptr,"digraph G {\n");

	for(int u=0;u<V;u++){
		if(dist[u] != INT_MAX)
			fprintf(fptr,"%d [label = \" %d / %d \"];\n", u, u, dist[u]);
		else
			fprintf(fptr,"%d [label = \" %d / unreachable \"];\n", u, u);
		
		int size = adj[u].size();
		for(int j=0;j<size;j++){
			int v = adj[u].at(j).first;
			fprintf(fptr,"\"%d\" -> \"%d\";\n",u,v);
		}
	}
	fprintf(fptr,"}");
	fclose(fptr);
}

Graph::~Graph()
{
}
