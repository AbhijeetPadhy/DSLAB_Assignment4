/*
 * TODO
 * -----------------------
 * 1. what if an edge is already present!
 * 2. Modify Dijsktra to include dest vertex!
 */

#include <iostream>
#include "Graph.h"

using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

Graph *read_from_file(){
	int choice = 0;
	Graph *graph = NULL;
	char filename[255] = "input_file_7.txt";
	cout<<"Enter the filename: ";
	fflush(stdin);
	cin>>filename;
	fflush(stdin);
	do{
		cout<< "Does the input file include weights?"<<endl;
		cout<< "1. Yes"<<endl;
		cout<< "2. No"<<endl;
		cout<<"\nPress 0 to quit.";
		cout<<"\nEnter Your Choice: ";
		cin>>choice;
		if(choice == 1){
			graph = new Graph();
			graph->read_from_file(1, filename);
		}
		else if(choice == 2){
			graph = new Graph();
			graph->read_from_file(0, filename);
		}
	}while(choice != 0 && choice != 1 && choice != 2);
	return graph;
}

void shortes_path(Graph *graph){
	int choice = 0;
	int src=0, dest=0;
	
	if(graph == NULL){
		cout<<"Graph is empty, first create a graph and then use this option to find out shortest distance."<<endl;
		return;
	}
	
	cout<<"Note that graph contains "<<graph->get_num_vertices()<< " vertices which are named 0 to "<<graph->get_num_vertices()-1<<endl;
	cout<<"Hence donot enter any node value other than 0 to "<<graph->get_num_vertices()-1<<endl;
	cout<<"Enter the source vertex: ";
	cin>>src;
	do{
		cout<<"Do you want to enter a destination node as well?"<<endl;
		cout<<"1. Yes"<<endl;
		cout<< "2. No"<<endl;
		cout<<"\nPress 0 to quit.";
		cout<<"\nEnter Your Choice: ";
		cin>>choice;
		if(choice == 1){
			cout<<"Enter the destination vertex: ";
			cin>>dest;
			cout<<"The distances of all the vertices from src vertex "<< src <<" are:"<<endl;
			graph->dijsktras_shortest_path_algorithm(src, dest);
		}
		else if(choice == 2){
			cout<<"The distances of all the vertices from src vertex "<< src <<" are:"<<endl;
			graph->dijsktras_shortest_path_algorithm(src);
		}
	}while(choice != 0 && choice != 1 && choice != 2);
	
	if(choice != 0){
		cout<<"\nPlease run the below command to create the image:"<<endl;
		cout<<"step 1: dot -Tpng dijsktra_output.gv -o dijsktra_output.png"<<endl;
		cout<<"step 2: Open the file dijsktra_output.png to view the output."<<endl;
	}else
		cout<<"You have opted to quit, hence there is nothing to output."<<endl;
	
}

Graph *create_new_graph_manually(){
	int V = 0;
	int no_of_edges = 0;
	int u, v, w;
	cout<<"Enter the number of vertices: ";
	cin>>V;
	Graph *graph = new Graph(V);
	cout<<"Enter the number of edges: ";
	cin>>no_of_edges;
	cout<<"Enter the details of all the edges in the following format:"<<endl;
	cout<<"In each row, details of an edge should be present as such \n<src node> <dest node> <weight>"<<endl;
	cout<<"Note: src node and dest node should be between "<<0<<" and "<<V-1<<endl;
	for(int i=0;i<no_of_edges;i++){
		cin>>u;
		cin>>v;
		cin>>w;
		graph->add_edge(u, v, w);
	}
	return graph;
}

int main(int argc, char** argv) {
	Graph *graph = NULL;
	Graph *graph2 = NULL;
	int choice = 0;
	int element = 0;
	int element2 = -1;
	
	do{
		cout<<"\nThis is an implementation of Graph"<<endl;
		cout<<"--------------------------------------------------------"<<endl;
		cout<<"1. Create a new graph manually."<<endl;
		cout<<"2. Create a new graph from file input."<<endl;
		cout<<"3. Print graph on terminal."<<endl;
		cout<<"4. Print graph on image using Graphviz."<<endl;
		cout<<"5. Perform DFS Traversal."<<endl;
		cout<<"6. Find all strongly connected components using Tarjan's algorithm."<<endl;
		cout<<"7. Create another graph G'(V, E') from the existing graph G(V, E) such that "<<endl;
		cout<<"       -> E' is a subset of E and"<<endl;
		cout<<"       -> G' has the same SCCs as G and"<<endl;
		cout<<"       -> G' has the same component graph as G and"<<endl;
		cout<<"       -> E' is as small as possible."<<endl;
		cout<<"8. Determine whether graph is semi-connected."<<endl;
		cout<<"9. Compute shortest distance from a node using Dijsktra's Algorithm."<<endl;
		cout<<"\nPress 0 to quit.";
		cout<<"\nEnter Your Choice: ";
		cin>>choice;
		cout<<"\n------------------OPERATION-------------------"<<endl;
		switch(choice){
			case 0:
				// Quit Case
				break;
			case 1:
				// Create a new graph manually.
				delete(graph);
				graph = create_new_graph_manually();
				break;
			case 2:
				// Create a new graph from file input.
				delete(graph);
				try{
					graph = read_from_file();
					cout<<"Graph has been successfully initialised from file input."<<endl;
				}catch(const char *msg){
					cout<< msg << endl;
				}
				break;
			case 3:
				// Print graph on terminal.
				if(graph != NULL){
					cout<<"The adjacency list of the graph is: "<<endl;
					graph->print_graph();
				}else{
					cout<<"The graph is not initialised with data."<<endl;
					cout<<"Please use options 1 or 2 to first feed data into the graph."<<endl;
				}
				break;
			case 4:
				// Print graph on image using Graphviz.
				if(graph!=NULL){
					graph->print_graph_graphviz();
					cout<<"Please run the below command to create the image:"<<endl;
					cout<<"step 1: dot -Tpng graph.gv -o graph.png"<<endl;
					cout<<"step 2: Open the file graph.png to view the output."<<endl;
				}
				else{
					cout<<"The graph is not initialised with data."<<endl;
					cout<<"Please use options 1 or 2 to first feed data into the graph."<<endl;
				}
				break;
			case 5:
				// Perform DFS Traversal.
				if(graph != NULL){
					cout<<"Enter the vertex from where DFS needs to start: ";
					cin >> element;
					graph->dfs_traversal(element);
					cout<<"Please run the below command to create the image:"<<endl;
					cout<<"step 1: dot -Tpng dfs_traversal.gv -o dfs_traversal.png"<<endl;
					cout<<"step 2: Open the file dfs_traversal.png to view the output."<<endl;
				}else{
					cout<<"The graph is not initialised with data."<<endl;
					cout<<"Please use options 1 or 2 to first feed data into the graph."<<endl;
				}
				break;
			case 6:
				// Find all strongly connected components using Tarjan's algorithm.
				if(graph != NULL){
					vector<vector<int>> *result = graph->find_scc();
					cout<<"The strongly connected components are: "<<endl;
					int no_of_scc = result->size();
					for(int i=0;i<no_of_scc;i++){
						int size_of_scc = result->at(i).size();
						cout<<"Component #"<<i+1<<": ";
						for(int j=0;j<size_of_scc;j++){
							cout << result->at(i).at(j) << " ";
						}
						cout<<endl;
					}
					cout<<"Please run the below command to create the image:"<<endl;
					cout<<"step 1: dot -Tpng tarjan.gv -o tarjan.png"<<endl;
					cout<<"step 2: Open the file tarjan.png to view the output."<<endl;
				}else{
					cout<<"The graph is not initialised with data."<<endl;
					cout<<"Please use options 1 or 2 to first feed data into the graph."<<endl;
				}
				break;
			case 7:
				// Compress the graph.
				if(graph != NULL){
					cout<<"The edges which are removed are:"<<endl;
					graph2 = graph->compress_graph();
					cout<<"\nThe adjacency list representation of the new graph is: "<<endl;
					graph2->print_graph();
					graph2->print_graph_graphviz();
					cout<<"\nPlease run the below command to create the image:"<<endl;
					cout<<"step 1: dot -Tpng graph.gv -o compressed_graph.png"<<endl;
					cout<<"step 2: Open the file compressed_graph.png to view the output."<<endl;
				}else{
					cout<<"The graph is not initialised with data."<<endl;
					cout<<"Please use options 1 or 2 to first feed data into the graph."<<endl;
				}
				
				break;
			case 8:
				// Determine whether graph is semi-connected.
				if(graph != NULL){
					if(graph->is_semi_connected())
						cout<<"The graph is semi connected!"<<endl;
					else
						cout<<"The graph is not semi connected!"<<endl;
				}else{
					cout<<"The graph is not initialised with data."<<endl;
					cout<<"Please use options 1 or 2 to first feed data into the graph."<<endl;
				}
				break;
			case 9:
				// Compute shortest distance from a node using Dijsktra's Algorithm.
				if(graph != NULL){
					shortes_path(graph);
				}
				else{
					cout<<"The graph is not initialised with data."<<endl;
					cout<<"Please use options 1 or 2 to first feed data into the graph."<<endl;
				}
				break;
			default:
				cout<<"Wrong Choice!!"<<endl;
		}
	}while(choice != 0);
	return 0;
}
