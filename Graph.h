#ifndef GRAPH_H
#define GRAPH_H
#include<bits/stdc++.h>

using namespace std;

class MyComp{
	public:
		int operator()(const pair<int,int> &a, const pair<int,int> &b){
			return a.second > b.second;
		}
};

class Graph
{
	public:
	int V;
	vector<pair<int,int>>* adj;
	
	public:
		Graph();
		Graph(int);
		int add_edge(int, int);
		int add_edge(int, int, int);
		int get_num_vertices();
		void dijsktras_shortest_path_algorithm(int);
		~Graph();
	protected:
};

#endif
