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
			graph->dijsktras_shortest_path_algorithm(src, dest);
		}
		else if(choice == 2){
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
		cout<<"5. Compute shortest distance from a node."<<endl;
		cout<<"6. Find all strongly connected components using Tarjan's algorithm."<<endl;
		cout<<"7. Determine whether graph is semi-connected."<<endl;
		cout<<"8. Compress the graph."<<endl;
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
				if(graph != NULL)
					graph->print_graph();
				break;
			case 4:
				if(graph != NULL){
					cout<<"Enter the vertex from where DFS needs to start: ";
					cin >> element;
					graph->dfs_traversal(element);
				}
					
				break;
			case 5:
				shortes_path(graph);
				break;
			case 6:
				if(graph != NULL){
					vector<vector<int>> *result = graph->find_scc();
					cout<<"The strongly connected components are: "<<endl;
					int no_of_scc = result->size();
					for(int i=0;i<no_of_scc;i++){
						int size_of_scc = result->at(i).size();
						for(int j=0;j<size_of_scc;j++){
							cout << result->at(i).at(j) << " ";
						}
						cout<<endl;
					}
					cout<<"Please run the below command to create the image:"<<endl;
					cout<<"step 1: dot -Tpng tarjan.gv -o tarjan.png"<<endl;
					cout<<"step 2: Open the file tarjan.png to view the output."<<endl;
				}	
				break;
			case 7:
				if(graph != NULL){
					if(graph->is_semi_connected())
						cout<<"The graph is semi connected!"<<endl;
					else
						cout<<"The graph is not semi connected!"<<endl;
				}
				break;
			case 8:
				graph2 = graph->compress_graph();
				cout<<"The adjacency list representation of the compressed graph is: "<<endl;
				graph2->print_graph();
				graph2->dfs_traversal(0);
				cout<<"Please run the below command to create the image:"<<endl;
				cout<<"step 1: dot -Tpng graph.gv -o compressed_graph.png"<<endl;
				cout<<"step 2: Open the file compressed_graph.png to view the output."<<endl;
				break;
			default:
				cout<<"Wrong Choice!!"<<endl;
		}
	}while(choice != 0);
	return 0;
}
