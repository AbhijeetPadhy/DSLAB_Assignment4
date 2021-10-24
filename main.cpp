// TODO: what if an edge is already present!

#include <iostream>
#include "Graph.h"

using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

const char TEST[] = "input_file.txt";
int cur_time = 0;

Graph *read_from_file(int variant){
	FILE *fptr;
	if ((fptr = fopen(TEST,"r")) == NULL){
		printf("Error! opening file\n");
		throw "read_from_file() : File Read Exception!";
	}
	int no_of_vertices = 0, no_of_edges = 0, src = 0, dest = 0, weight = 0;
	
	fscanf(fptr, "%d", &no_of_vertices);
	fscanf(fptr, "%d", &no_of_edges);
	Graph * graph = new Graph(no_of_vertices);
	for(int i=0;i<no_of_edges;i++){
		fscanf(fptr, "%d", &src);
		fscanf(fptr, "%d", &dest);
		if(variant == 1){
			fscanf(fptr, "%d", &weight);
			graph->add_edge(src, dest, weight);
		}else
			graph->add_edge(src, dest);	
		
	}
	fclose(fptr);
	return graph;
}

Graph *read_from_file(){
	int choice = 0;
	Graph *graph = NULL;
	do{
		cout<< "Does the input file include weights?"<<endl;
		cout<< "1. Yes"<<endl;
		cout<< "2. No"<<endl;
		cout<<"\nPress 0 to quit.";
		cout<<"\nEnter Your Choice: ";
		cin>>choice;
		if(choice == 1)
			graph = read_from_file(1);
		else if(choice == 2)
			graph = read_from_file(0);
	}while(choice != 0 && choice != 1 && choice != 2);
	
	
	return graph;
}



void print_graph(Graph *graph){
	if(graph == NULL)
		return;
	int V = graph->get_num_vertices();
	for(int i=0;i<V;i++){
		cout << i;
		int size = graph->adj[i].size();
		for(int j=0;j<size;j++){
			cout<< "->" <<graph->adj[i].at(j).first;
		}
		cout << endl;
	}
}

void dfs_traversal(Graph *graph, bool visited[], int discovery_time[], int finish_time[], int u, FILE *fptr){
	visited[u] = true;
	discovery_time[u] = ++cur_time;
	int no_of_adj_vertices = graph->adj[u].size();
	
	for(int i=0; i<no_of_adj_vertices;i++){
		int v = graph->adj[u].at(i).first;
		int w = graph->adj[u].at(i).second;
		if(!visited[v]){
			// tree edge
			dfs_traversal(graph, visited, discovery_time, finish_time, v, fptr);
			fprintf(fptr,"\"%d\" -> \"%d\" [label = \"T/%d\"];\n",u,v,w);
		}
		
		// forward edges
		else if(discovery_time[u] < discovery_time[v] && finish_time[v] <= cur_time)
			fprintf(fptr,"\"%d\" -> \"%d\" [style = dotted, label = \"F/%d\"];\n",u,v,w);
	}
	
	finish_time[u] = ++cur_time;
	fprintf(fptr,"%d [label = \" %d  %d/%d \"];\n", u, u, discovery_time[u], finish_time[u]);
	
}

void dfs_traversal(Graph *graph){
	FILE *fptr;
	fptr = fopen("graph.gv","w");
	fprintf(fptr,"digraph G {\n");
	//fprintf(fptr,"node [shape = record,height=.1];\n");
	
	cur_time = 0;
	int V = graph->get_num_vertices();
	
	bool visited[V];
	memset(visited, false, sizeof(visited));
	
	int discovery_time[V];
	memset(discovery_time, 0, sizeof(discovery_time));
	
	int finish_time[V];
	memset(finish_time, 0, sizeof(finish_time));
	
	
	for(int i=0;i<V;i++){
		if(!visited[i])
			dfs_traversal(graph, visited, discovery_time, finish_time, i, fptr);
	}
	
	for(int u = 0; u < V; u++){
		int no_of_adj_vertices = graph->adj[u].size();
		for(int i=0; i<no_of_adj_vertices;i++){
			int v = graph->adj[u].at(i).first;
			int w = graph->adj[u].at(i).second;
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

int main(int argc, char** argv) {
	Graph *graph = NULL;
	int choice = 0;
	int element = 0;
	
	do{
		cout<<"\nThis is an implementation of Graph"<<endl;
		cout<<"--------------------------------------------------------"<<endl;
		cout<<"1. Create a new graph manually."<<endl;
		cout<<"2. Create a new graph from file input."<<endl;
		cout<<"3. Print graph on terminal."<<endl;
		cout<<"4. Print graph on image using Graphviz."<<endl;
		cout<<"5. Compute shortest distance from a node."<<endl;
		cout<<"\nPress 0 to quit.";
		cout<<"\nEnter Your Choice: ";
		cin>>choice;
		cout<<"\n------------------OPERATION-------------------"<<endl;
		switch(choice){
			case 0:
				break;
			case 1:
				break;
			case 2:
				delete(graph);
				try{
					graph = read_from_file();
				}catch(const char *msg){
					cout<< msg << endl;
				}
				break;
			case 3:
				print_graph(graph);
				break;
			case 4:
				dfs_traversal(graph);
				break;
			case 5:
				cout<< "Enter the source node: ";
				cin >> element;
				graph->dijsktras_shortest_path_algorithm(element);
				cout<<"Please run the below command to create the image:"<<endl;
				cout<<"step 1: dot -Tpng dijsktra_output.gv -o dijsktra_output.png"<<endl;
				cout<<"step 2: Open the file dijsktra_output.png to view the output."<<endl;
				break;
			default:
				cout<<"Wrong Choice!!"<<endl;
		}
	}while(choice != 0);
	return 0;
}
