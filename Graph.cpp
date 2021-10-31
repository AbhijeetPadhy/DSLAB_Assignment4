#include "Graph.h"
#include "min_heap.h"

Graph::Graph()
{
	V = 0;
	cur_time = 0;
}

Graph::Graph(int v)
{
	V = v;
	adj = new vector<pair<int,int> >[V];
	cur_time = 0;
}

// function to add a new edge to the graph without weight.
// By deafult the weight will be considered as 1.
int Graph::add_edge(int src, int dest){
	return add_edge(src, dest, 1);
}

// function to add a new edge to the graph with weight.
int Graph::add_edge(int src, int dest, int weight){
	if(src >= V || src < 0 || dest >= V || dest < 0){
		cout<<"Src and Dest node of an edge should be between 0 and "<<V-1<<endl;
		cout<<"Your edge consists of nodes outside this range."<<endl;
		return 1;
	}
	pair<int, int> edge(dest, weight);
	adj[src].push_back(edge);
	return 0;
}

// function to return number of vertices
int Graph::get_num_vertices(){
	return V;
}

// function to find shortest path distance using dijsktras algo
void Graph::dijsktras_shortest_path_algorithm(int S){
	dijsktras_shortest_path_algorithm(S,-1);
}

// function to find shortest path distance using dijsktras algo
void Graph::dijsktras_shortest_path_algorithm(int S, int D){
	min_heap *heap = new min_heap(V);
	int dist[V];
	int parent[V];
	int finalised[V];
	
	// initialise the arrays
	for(int i=0;i<V;i++){
		parent[i] = -1;
		dist[i] = INT_MAX;
		finalised[i] = false;
		if(i == S)
			dist[i] = 0;
		heap->push(make_pair(i, dist[i])); // push all the elements to the heap
	}
	
	// iterate while there is an element present in the heap
	while(heap->size() != 0){
        pair<int,int> u = heap->pop();
        finalised[u.first] = true;
        int no_of_adj_nodes = adj[u.first].size();
        
		for(int j=0;j<no_of_adj_nodes;j++){
            int v = adj[u.first].at(j).first;
            int weight = adj[u.first].at(j).second;
            // relax an edge
			if(!finalised[v] && u.second != INT_MAX && u.second + weight < dist[v]){
                dist[v] = u.second + weight;
                parent[v] = u.first;
				heap->decrease_key(v, dist[v]);
            }
        }
    }
    
	output_dijsktra(dist, parent, S, D);
}

// function to produce the output of dijsktras algo
void Graph::output_dijsktra(int dist[], int parent[], int S, int D){
	// graphviz output
	FILE *fptr;
	fptr = fopen("dijsktra_output.gv","w");
	fprintf(fptr,"digraph G {\n");
	set<int> s;
	
	if(D != -1){
		int v = D;
		while(v != -1 && v != S){
			s.insert(v);
			v = parent[v];
		}
		s.insert(S);
	}
	
	for(int u=0;u<V;u++){
		if(dist[u] != INT_MAX){
			if(u == S)
				fprintf(fptr,"%d [shape=doubleoctagon, color=magenta, label = \" %d / %d \"];\n", u, u, dist[u]);
			else if(u == D)
				fprintf(fptr,"%d [shape=doubleoctagon, color=brown, label = \" %d / %d \"];\n", u, u, dist[u]);
			else
				fprintf(fptr,"%d [label = \" %d / %d \"];\n", u, u, dist[u]);
		}
			
		else{
			if(u == D)
				fprintf(fptr,"%d [shape=doubleoctagon, color=brown, label = \" %d / unreachable \"];\n", u, u);
			else
				fprintf(fptr,"%d [label = \" %d / unreachable \"];\n", u, u);
		}
			
		
		int size = adj[u].size();
		for(int j=0;j<size;j++){
			int v = adj[u].at(j).first;
			int w = adj[u].at(j).second;
			if(D != -1 && s.find(v)!=s.end() && s.find(u)!=s.end() && parent[v] == u)
				fprintf(fptr,"\"%d\" -> \"%d\" [style=bold, color=red, label=%d];\n",u,v,w);
			else
				fprintf(fptr,"\"%d\" -> \"%d\" [label=%d];\n",u,v,w);
		}
	}
	fprintf(fptr,"}");
	fclose(fptr);
	
	
	// Terminal Output
    for(int i=0;i<V;i++){
    	if(dist[i] == INT_MAX)
    		cout<<"Node "<<i<<" is unreachable " <<endl;
    	else
			cout<<"Node "<<i<<" has dist = " << dist[i]<<endl;
	}
	
	int path[V];
	int i=0, v=D;
	if(D != -1){
		while(v != S && parent[v] != -1){
			path[i++] = v;
			v = parent[v];
		}
		if(parent[D] != -1){
			cout<<"\nThe shortest cost path from vertex "<<S<<" to "<<D<<" is "<<endl;
			cout<<S<<"->";
			for(int j=0;j<i;j++)
				cout<<path[i-j-1]<<"->";
		}else{
			cout<<"\nThe vertex "<<D<<" is not reachable from vertex "<<S;
		}
		cout<<endl;
	}
	
}

// function to read from file and create graph
void Graph::read_from_file(int variant, char *filename){
	FILE *fptr;
	if ((fptr = fopen(filename,"r")) == NULL){
		printf("Error! opening file\n");
		throw "read_from_file() : File Read Exception!";
	}
	int no_of_vertices = 0, no_of_edges = 0, src = 0, dest = 0, weight = 0;
	
	fscanf(fptr, "%d", &no_of_vertices);
	fscanf(fptr, "%d", &no_of_edges);
	V = no_of_vertices;
	adj = new vector<pair<int,int> >[V];
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

// function to print graph on terminal
void Graph::print_graph(){
	if(V == 0)
		return;
		
	for(int i=0;i<V;i++){
		cout << i << " : ";
		int size = adj[i].size();
		for(int j=0;j<size;j++){
			cout<< adj[i].at(j).first << "->";
		}
		cout << endl;
	}
}

// function to print graph on graphviz
void Graph::print_graph_graphviz(){
	if(V == 0)
		return;
	
	FILE *fptr;
	fptr = fopen("graph.gv","w");
	fprintf(fptr,"digraph G {\n");
	
	for(int i=0;i<V;i++){
		fprintf(fptr,"%d [label = \" %d \"];\n", i, i);
	}
	
	for(int u=0;u<V;u++){
		int size = adj[u].size();
		for(int j=0;j<size;j++){
			int v = adj[u].at(j).first;
			int w = adj[u].at(j).second;
			fprintf(fptr,"\"%d\" -> \"%d\" [label = \"%d\"];\n",u,v,w);
		}
	}
	fprintf(fptr,"}");
	fclose(fptr);
}

// Function to perform dfs traversal on graph
void Graph::dfs_traversal(bool visited[], int discovery_time[], int finish_time[], int u, FILE *fptr){
	visited[u] = true;
	discovery_time[u] = ++cur_time;
	int no_of_adj_vertices = adj[u].size();
	
	for(int i=0; i<no_of_adj_vertices;i++){
		int v = adj[u].at(i).first;
		int w = adj[u].at(i).second;
		if(!visited[v]){
			// classify tree edge
			dfs_traversal(visited, discovery_time, finish_time, v, fptr);
			fprintf(fptr,"\"%d\" -> \"%d\" [label = \"T/%d\"];\n",u,v,w);
		}
		
		// classify forward edges
		else if(discovery_time[u] < discovery_time[v] && finish_time[v] <= cur_time)
			fprintf(fptr,"\"%d\" -> \"%d\" [style = dotted, label = \"F/%d\"];\n",u,v,w);
	}
	
	finish_time[u] = ++cur_time;
	fprintf(fptr,"%d [label = \" %d  %d/%d \"];\n", u, u, discovery_time[u], finish_time[u]);
	
}

// Function to perform dfs traversal on graph
void Graph::dfs_traversal(int src){
	FILE *fptr;
	fptr = fopen("dfs_traversal.gv","w");
	fprintf(fptr,"digraph G {\n");
	
	cur_time = 0;
	
	bool visited[V];
	int discovery_time[V];
	int finish_time[V];
	
	for(int i=0;i<V;i++){
		visited[i] = false;
		discovery_time[i] = 0;
		finish_time[i] = 0;
	}
	
	// Call DFS from the src vertex first
	dfs_traversal(visited, discovery_time, finish_time, src, fptr);
	
	// Call DFS for other vertices if required
	for(int i=0;i<V;i++){
		if(!visited[i])
			dfs_traversal(visited, discovery_time, finish_time, i, fptr);
	}
	
	// classify cross edge or back edge
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

// function to find SCCs using Tarjan's Algo
void Graph::find_scc(int u, bool visited[], int disc[], bool stackArray[], stack<int> *stk, int low[], vector<vector<int> > *result){
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

// function to produce output of Tarjan's Algo
void Graph::output_scc(vector<vector<int> > *scc){
	FILE *fptr;
	fptr = fopen("tarjan.gv","w");
	fprintf(fptr,"digraph G {\n");
	
	for(int i=0;i<scc->size();i++){
		fprintf(fptr,"subgraph cluster%d {\n", i+1);
		fprintf(fptr,"color=blue;\n");
		fprintf(fptr,"label = \"component #%d\";\n",i+1);
		for(int j=0;j<scc->at(i).size();j++){
			int v = scc->at(i).at(j);
			fprintf(fptr,"%d [label = \" %d \"];\n", v, v);
		}
		fprintf(fptr,"}\n");
	}
	
	for(int u=0;u<V;u++){
		int size = adj[u].size();
		for(int j=0;j<size;j++){
			int v = adj[u].at(j).first;
			int w = adj[u].at(j).second;
			fprintf(fptr,"\"%d\" -> \"%d\" [label = \"%d\"];\n",u,v,w);
		}
	}
	fprintf(fptr,"}");
	fclose(fptr);
}

// function to find SCCs using Tarjan's Algo
vector<vector<int> > *Graph::find_scc(){
	cur_time = 0;
	
	bool *visited = new bool[V];
	int *disc = new int[V];
	int *low = new int[V];
	bool *stackArray = new bool[V];
	
	// initialise the arrays
	for(int i=0;i<V;i++){
		visited[i] = false;
		disc[i] = 0;
		stackArray[i] = false;
		low[i] = 0;
	}
	
	stack<int> *stk = new stack<int>();
	vector<vector<int> > *result = new vector<vector<int> >();
	
	// call the overloaded find_scc method for all the unvisited vertices
	for(int i=0;i<V;i++){
		if(!visited[i])
			find_scc(i, visited, disc, stackArray, stk, low, result);
	}
	output_scc(result);
	return result;
}

// utility function to find topological sort
void Graph::topoSortUtil(int u, Graph *graph, stack<int> *stk, bool visited[]){
        visited[u] = true;
        int no_of_adj_nodes = graph->adj[u].size();
        for(int i=0;i<no_of_adj_nodes;i++){
            int v = graph->adj[u].at(i).first;
            if(!visited[v])
                topoSortUtil(v, graph, stk, visited);
        }
        stk->push(u);
}

// function to find topological sort
int *Graph::topo_sort(Graph *graph){
	int vertices = graph->V;
	stack<int> *stk = new stack<int>();
	bool *visited = new bool[vertices];
	int *result = new int[vertices];
	int top = -1;
	
	for(int i=0;i<vertices;i++){
		visited[i] = false;
		result[i] = 0;
	}

	for(int u=0;u<vertices;u++){
		if(!visited[u])
			topoSortUtil(u, graph, stk, visited);
	}
	
	while(stk->size()!=0){
		result[++top] = stk->top();
		stk->pop();
	}
	return result;
}

// function to check if graph is semi connected
bool Graph::is_semi_connected(){
	vector<vector<int> > *vector_of_scc = find_scc(); // Find list of all SCCs using Tarjan's Algo
	int no_of_scc = vector_of_scc->size();
	Graph *component_graph = new Graph(no_of_scc);
	
	int scc_of_nodes[V];
	
	for(int i=0;i<no_of_scc;i++){
		int size_of_scc = vector_of_scc->at(i).size();
		for(int j=0;j<size_of_scc;j++){
			scc_of_nodes[vector_of_scc->at(i).at(j)] = i; // Store the SCC to which a vertex belongs in scc_of_nodes array
		}
	}
	
	// find edges between components
	for(int u=0;u<V;u++){
		int no_of_adj_nodes = adj[u].size();
		for(int i=0;i<no_of_adj_nodes;i++){
			int v = adj[u].at(i).first;
			int src = scc_of_nodes[u];
			int dest = scc_of_nodes[v];
			if(src != dest){
				component_graph->add_edge(src,dest);
			}
		}
	}
	
	//topological sort
	int *topo_sorted_array = topo_sort(component_graph);
	
	// check if vertex vi and vi+1 in component graph have an edge.
	bool flag = false;
	for(int i=0;i<no_of_scc-1;i++){
		int u = topo_sorted_array[i];
		int next_node = topo_sorted_array[i+1];
		int no_of_adj_nodes = component_graph->adj[u].size();
		flag = false;
		for(int j=0;j<no_of_adj_nodes;j++){
			int v = component_graph->adj[u].at(j).first;
			if(v == next_node){
				flag = true;
				break;
			}
		}
		if(flag == false)
			return false;
	}
	return true;
}

// function to create clone of an existing graph
Graph *Graph::clone_graph(){
	Graph *graph = new Graph(V);
	for(int i=0;i<V;i++){
		int no_of_adj_nodes = adj[i].size();
		for(int j=0;j<no_of_adj_nodes; j++){
			int v = adj[i][j].first;
			int w = adj[i][j].second;
			graph->add_edge(i,v,w);
		}
	}
	return graph;
}

// function to remove an edge of the graph
void Graph::remove_edge(int u, int v){
	cout<<"Removing edge "<<u<<"->"<<v<<endl;
	vector<pair<int,int> > edges;
	int no_of_adj_nodes = adj[u].size();
	for(int i=0;i<no_of_adj_nodes;i++){
		int d = adj[u][i].first;
		int w = adj[u][i].second;
		pair<int, int> edge(d, w);
		if(d != v)
			edges.push_back(edge);
	}
	
	// clear the current
	adj[u].clear();
	
	// add the necessary edges back 
	for(int i=0;i<edges.size();i++){
		add_edge(u, edges[i].first, edges[i].second);
	}
}

// function to check if a path is possible between two vertices
bool Graph::path_possible(Graph *graph, int u, int v, int e1, int e2){
	bool *visited = new bool[V];

	for(int i=0;i<V;i++)
		visited[i] = false;

	list<int> queue;
	
	visited[u] = true;
	queue.push_back(u);
	
	
	while(queue.size()!=0){
		int s = queue.front();
		queue.pop_front();
		int no_of_adj_nodes = graph->adj[s].size();
		for(int i=0;i<no_of_adj_nodes;i++){
			int d = graph->adj[s][i].first;
			if(s == e1 && d == e2)
				;
			else if(d ==v)
				return true;
			else if(!visited[d]){
				visited[d] = true;
				queue.push_back(d);
			}
		}
	}
	return false;
}

// function to remove edges from within a component and between two components if they are parallel edges
void Graph::remove_edges_from_components(Graph *graph, vector<vector<int> > *vector_of_scc, int component, int *scc_of_nodes){
	bool scc_connect[vector_of_scc->size()];

	for(int i=0;i<vector_of_scc->size();i++)
		scc_connect[i] = false;

	for(int i=0;i<vector_of_scc->at(component).size();i++){
		
		int u = vector_of_scc->at(component).at(i);
		int no_of_adj_nodes = adj[u].size();
		
		for(int j=0;j<no_of_adj_nodes;j++){
			int v = adj[u][j].first;
			int w = adj[u][j].second;
			if(path_possible(graph,u,v,u,v) && path_possible(graph,v,u,u,v)){
				graph->remove_edge(u,v);
			}
			if(scc_of_nodes[u] != scc_of_nodes[v]){
				if(scc_connect[scc_of_nodes[v]] == true){
					graph->remove_edge(u,v);
				}else{
					scc_connect[scc_of_nodes[v]] = true;
				}
			}
		}
	}
}

// function to create a new graph according to problem 3
Graph *Graph::compress_graph(){
	Graph *graph = clone_graph();
	vector<vector<int> > *vector_of_scc = find_scc();
	int no_of_scc = vector_of_scc->size();
	
	int scc_of_nodes[V];
	
	for(int i=0;i<no_of_scc;i++){
		int size_of_scc = vector_of_scc->at(i).size();
		for(int j=0;j<size_of_scc;j++){
			scc_of_nodes[vector_of_scc->at(i).at(j)] = i;
		}
	}
	for(int i=0;i<no_of_scc;i++){
		remove_edges_from_components(graph, vector_of_scc, i, scc_of_nodes);
	}
	return graph;
}

Graph::~Graph()
{
}
