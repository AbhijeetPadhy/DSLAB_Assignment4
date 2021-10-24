#include "min_heap.h"

min_heap::min_heap(int V)
{
	heap_size = 0;
	capacity = V;
	heap_array = new pair<int, int>[V];
	location_of_node = new int[V];
}

int min_heap::parent(int i){
	return (i-1)/2;
}

void min_heap::swap(int i, int j){
	location_of_node[heap_array[i].first] = j;
	location_of_node[heap_array[j].first] = i;
	
	pair<int,int> temp = heap_array[i];
	heap_array[i] = heap_array[j];
	heap_array[j] = temp;
}

void min_heap::push(pair<int,int> e){
	if(heap_size == capacity){
		cout<<"Heap Overflow!"<<endl;
		return;
	}
	heap_size++;
	int i = heap_size-1;
	heap_array[i] = e;
	
	location_of_node[heap_array[i].first] = i;
	
	while(i != 0 && heap_array[parent(i)].second > heap_array[i].second){
		swap(parent(i), i);
		i = parent(i);
	}
}

void min_heap::decrease_key(int node, int new_val){
	if(node < 0)
		return;
	int i = location_of_node[node];
	heap_array[i].second = new_val;
	while(i != 0 && heap_array[parent(i)].second > heap_array[i].second){
		swap(parent(i), i);
		i = parent(i);
	}
}

void min_heap::min_heapify(int i){
	int l = 2*i + 1;
	int r = 2*i + 2;
	int smallest = i;
	
	if(l < heap_size && heap_array[l].second < heap_array[i].second)
		smallest = l;
	if(r < heap_size && heap_array[r].second < heap_array[smallest].second)
		smallest = r;
	if(smallest != i){
		swap(i, smallest);
		min_heapify(smallest);
	}
}

pair<int, int> min_heap::pop(){
	if(heap_size <= 0)
		return make_pair(-1,-1);
	
	pair<int, int> root = heap_array[0];
	
	if(heap_size == 1){
		heap_size--;
		return root;
	}
	
	location_of_node[root.first] = -1;
	heap_array[0] = heap_array[heap_size-1];
	heap_size--;
	min_heapify(0);
	
	return root;
}

int min_heap::size(){
	return heap_size;
}

min_heap::~min_heap()
{
	delete heap_array;
	delete location_of_node;
}
