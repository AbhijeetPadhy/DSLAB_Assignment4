#include "Graph.h"

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

Graph::~Graph()
{
}
