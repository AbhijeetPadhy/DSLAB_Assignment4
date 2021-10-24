#include <iostream>
#include "Graph.h"

using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

const char TEST[] = "input_file.txt";

Graph *read_from_file(int variant){
	FILE *fptr;
	char operation[7];
	int element = 0;
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
			graph->addEdge(src, dest, weight);
		}else
			graph->addEdge(src, dest);	
		
	}
	return graph;
}

void print_graph(Graph *graph){
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
	Graph *graph;
	
	try{
		graph = read_from_file(0);
	}catch(const char *msg){
		cout<< msg << endl;
	}
	print_graph(graph);
	return 0;
}
