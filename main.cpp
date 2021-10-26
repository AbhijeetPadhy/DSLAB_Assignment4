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
	do{
		cout<< "Does the input file include weights?"<<endl;
		cout<< "1. Yes"<<endl;
		cout<< "2. No"<<endl;
		cout<<"\nPress 0 to quit.";
		cout<<"\nEnter Your Choice: ";
		cin>>choice;
		if(choice == 1){
			graph = new Graph();
			graph->read_from_file(1);
		}
		else if(choice == 2){
			graph = new Graph();
			graph->read_from_file(0);
		}
	}while(choice != 0 && choice != 1 && choice != 2);
	return graph;
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
		cout<<"6. Find all strongly connected components using Tarjan's algorithm."<<endl;
		cout<<"7. Determine whether graph is semi-connected."<<endl;
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
				if(graph != NULL)
					graph->dfs_traversal();
				break;
			case 5:
				cout<< "Enter the source node: ";
				cin >> element;
				if(graph != NULL)
					graph->dijsktras_shortest_path_algorithm(element);
				cout<<"Please run the below command to create the image:"<<endl;
				cout<<"step 1: dot -Tpng dijsktra_output.gv -o dijsktra_output.png"<<endl;
				cout<<"step 2: Open the file dijsktra_output.png to view the output."<<endl;
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
			default:
				cout<<"Wrong Choice!!"<<endl;
		}
	}while(choice != 0);
	return 0;
}
