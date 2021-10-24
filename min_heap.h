#ifndef MIN_HEAP_H
#define MIN_HEAP_H
#include<bits/stdc++.h>

using namespace std;

class min_heap
{
	int heap_size;
	int capacity;
	pair<int, int> *heap_array;
	int *location_of_node;
	
	public:
		min_heap(int V);
		int parent(int);
		pair<int, int> pop();
		void push(pair<int,int>);
		void decrease_key(int, int);
		void swap(int, int);
		void min_heapify(int);
		int size();
		~min_heap();
	protected:
};

#endif
