#ifndef GRAPH_H
#define GRAPH_H
#include<bits/stdc++.h>
#define TEST "input_file.txt"

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
	void output_dijsktra(int[]);
	int cur_time = 0;
	void dfs_traversal(bool[], int[], int[], int, FILE *);
	void find_scc(int, bool[], int[], bool[], stack<int>*, int[], vector<vector<int>>*);
	
	public:
		Graph();
		Graph(int);
		int add_edge(int, int);
		int add_edge(int, int, int);
		int get_num_vertices();
		void dijsktras_shortest_path_algorithm(int);
		void read_from_file(int);
		void print_graph();
		void dfs_traversal();
		void find_scc();
		~Graph();
	protected:
};

#endif
