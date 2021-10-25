#include "Graph.h"
#include "min_heap.h"

Graph::Graph()
{
	V = 0;
	//adj = new vector<pair<int,int>>[V];
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

void Graph::read_from_file(int variant){
	FILE *fptr;
	if ((fptr = fopen(TEST,"r")) == NULL){
		printf("Error! opening file\n");
		throw "read_from_file() : File Read Exception!";
	}
	int no_of_vertices = 0, no_of_edges = 0, src = 0, dest = 0, weight = 0;
	
	fscanf(fptr, "%d", &no_of_vertices);
	fscanf(fptr, "%d", &no_of_edges);
	V = no_of_vertices;
	adj = new vector<pair<int,int>>[V];
	for(int i=0;i<no_of_edges;i++){
		fscanf(fptr, "%d", &src);
		fscanf(fptr, "%d", &dest);
		if(variant == 1){
			fscanf(fptr, "%d", &weight);
			add_edge(src, dest, weight);
		}else
			add_edge(src, dest);	
		
	}
	fclose(fptr);
}

void Graph::print_graph(){
	if(V == 0)
		return;
		
	for(int i=0;i<V;i++){
		cout << i;
		int size = adj[i].size();
		for(int j=0;j<size;j++){
			cout<< "->" <<adj[i].at(j).first;
		}
		cout << endl;
	}
}

void Graph::dfs_traversal(bool visited[], int discovery_time[], int finish_time[], int u, FILE *fptr){
	visited[u] = true;
	discovery_time[u] = ++cur_time;
	int no_of_adj_vertices = adj[u].size();
	
	for(int i=0; i<no_of_adj_vertices;i++){
		int v = adj[u].at(i).first;
		int w = adj[u].at(i).second;
		if(!visited[v]){
			// tree edge
			dfs_traversal(visited, discovery_time, finish_time, v, fptr);
			fprintf(fptr,"\"%d\" -> \"%d\" [label = \"T/%d\"];\n",u,v,w);
		}
		
		// forward edges
		else if(discovery_time[u] < discovery_time[v] && finish_time[v] <= cur_time)
			fprintf(fptr,"\"%d\" -> \"%d\" [style = dotted, label = \"F/%d\"];\n",u,v,w);
	}
	
	finish_time[u] = ++cur_time;
	fprintf(fptr,"%d [label = \" %d  %d/%d \"];\n", u, u, discovery_time[u], finish_time[u]);
	
}

void Graph::dfs_traversal(){
	FILE *fptr;
	fptr = fopen("graph.gv","w");
	fprintf(fptr,"digraph G {\n");
	//fprintf(fptr,"node [shape = record,height=.1];\n");
	
	cur_time = 0;
	
	bool visited[V];
	memset(visited, false, sizeof(visited));
	
	int discovery_time[V];
	memset(discovery_time, 0, sizeof(discovery_time));
	
	int finish_time[V];
	memset(finish_time, 0, sizeof(finish_time));
	
	
	for(int i=0;i<V;i++){
		if(!visited[i])
			dfs_traversal(visited, discovery_time, finish_time, i, fptr);
	}
	
	for(int u = 0; u < V; u++){
		int no_of_adj_vertices = adj[u].size();
		for(int i=0; i<no_of_adj_vertices;i++){
			int v = adj[u].at(i).first;
			int w = adj[u].at(i).second;
			//cross edge
			if(discovery_time[v] < finish_time[v] && 
				finish_time[v] < discovery_time[u] &&
				discovery_time[u] < finish_time[u])
				fprintf(fptr,"\"%d\" -> \"%d\" [style = dotted, label = \"C/%d\"];\n",u,v,w);
			
			//back edge
			else if(discovery_time[v] <= discovery_time[u] && 
				discovery_time[u] < finish_time[u] &&
				finish_time[u] <= finish_time[v])
				fprintf(fptr,"\"%d\" -> \"%d\" [style = dotted, label = \"B/%d\"];\n",u,v,w);
		}
	}
	
	fprintf(fptr,"}");
	fclose(fptr);
}

void Graph::find_scc(int u, bool visited[], int disc[], bool stackArray[], stack<int> *stk, int low[], vector<vector<int>> *result){
	visited[u] = true;
	low[u] = disc[u] = ++cur_time;
	stk->push(u);
	stackArray[u] = true;
	
	int no_of_adj_nodes = adj[u].size();
	for(int i=0;i<no_of_adj_nodes;i++){
		int v = adj[u].at(i).first;
		// Tree Edge
		if(!visited[v]){
			find_scc(v, visited, disc, stackArray, stk, low, result);
			low[u] = (low[u] < low[v])? low[u] : low[v];
		}
		// Back Edge
		else if(stackArray[v]){
			low[u] = (low[u] < disc[v])? low[u] : disc[v];
		}
	}
	
	// Head Node
	if(low[u] == disc[u]){
		vector<int> *sccs = new vector<int>();
		int w = -1;
		while(w != u){
			
			w = stk->top();
			stk->pop();
			sccs->push_back(w);
			stackArray[w] = false;
		}
		result->push_back(*sccs);
	}
}

void Graph::find_scc(){
	cur_time = 0;
	
	bool *visited = new bool[V];
	memset(visited, false, sizeof(visited));
	
	int *disc = new int[V];
	memset(disc, 0, sizeof(disc));
	
	bool *stackArray = new bool[V];
	memset(stackArray, false, sizeof(stackArray));
	
	int *low = new int[V];
	memset(low, 0, sizeof(low));
	
	stack<int> *stk = new stack<int>();
	vector<vector<int>> *result = new vector<vector<int>>();
	
	for(int i=0;i<V;i++){
		if(!visited[i])
			find_scc(i, visited, disc, stackArray, stk, low, result);
	}
	
	cout<<"The connected components are: "<<endl;
	int no_of_scc = result->size();
	for(int i=0;i<no_of_scc;i++){
		int size_of_scc = result->at(i).size();
		for(int j=0;j<size_of_scc;j++){
			cout << result->at(i).at(j) << " ";
		}
		cout<<endl;
	}
}

Graph::~Graph()
{
}
