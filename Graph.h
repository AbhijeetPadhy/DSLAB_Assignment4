#ifndef GRAPH_H
#define GRAPH_H
#include<bits/stdc++.h>

using namespace std;

class Graph
{
	public:
	int V;
	vector<pair<int,int>>* adj;
	
	public:
		Graph();
		Graph(int);
		int addEdge(int, int);
		int addEdge(int, int, int);
		int get_num_vertices();
		~Graph();
	protected:
};

#endif
