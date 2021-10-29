#ifndef GRAPH_H
#define GRAPH_H
#include<bits/stdc++.h>
#define TEST "input_file_5.txt"

using namespace std;

class MyComp{
	public:
		int operator()(const pair<int,int> &a, const pair<int,int> &b){
			return a.second > b.second;
		}
};

class Graph
{
	int V;
	vector<pair<int,int>>* adj;
	void output_dijsktra(int[], int[], int, int);
	int cur_time = 0;
	void dfs_traversal(bool[], int[], int[], int, FILE *);
	void find_scc(int, bool[], int[], bool[], stack<int>*, int[], vector<vector<int>>*);
	void topoSortUtil(int, Graph *, stack<int> *, bool[]);
	void output_scc(vector<vector<int>> *);
	void remove_edges_from_components(Graph *, vector<vector<int>> *, int , int *);
	bool path_possible(Graph *, int, int, int, int);
	Graph *clone_graph();
	void remove_edge(int, int);
	
	public:
		Graph();
		Graph(int);
		int add_edge(int, int);
		int add_edge(int, int, int);
		int get_num_vertices();
		void dijsktras_shortest_path_algorithm(int);
		void dijsktras_shortest_path_algorithm(int, int);
		void read_from_file(int, char *);
		void print_graph();
		void dfs_traversal();
		vector<vector<int>> *find_scc();
		int *topo_sort(Graph *graph);
		bool is_semi_connected();
		Graph *compress_graph();
		~Graph();
	protected:
};

#endif
