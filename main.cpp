#include <iostream>
#include "Graph.h"

using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

const char TEST[] = "input_file.txt";

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

int main(int argc, char** argv) {
	Graph *graph = NULL;
	int choice = 0;
	
	do{
		cout<<"\nThis is an implementation of Graph"<<endl;
		cout<<"--------------------------------------------------------"<<endl;
		cout<<"1. Create a new graph manually."<<endl;
		cout<<"2. Create a new graph from file input."<<endl;
		cout<<"3. Print graph on terminal."<<endl;
		cout<<"4. Print graph on image using Graphviz."<<endl;
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
				break;
		}
	}while(choice != 0);
	print_graph(graph);
	return 0;
}
