# DSLAB_Assignment4
Implement directed graph ADT using adjacency list data structure.

System Requirements
======================
1. Windows(Using DEVCPP)
	i.	Install Dev CPP if not present.
	ii. Open DSLAB_Assignment4.dev file present in the project folder using DevCPP or simply double click the file to open the project.
	iii.The project opens in Dev CPP.
	iv. Compile and execute to run the project.

2. Windows(Without using DEVCPP)  
	i.	Install GNU make  
		https://sourceforge.net/projects/gnuwin32/files/make/3.81/make-3.81.exe/download  
	ii. Install GNU GCC compiler  
	iii.Install Graphwiz  
		https://graphviz.org/download/
	Please remember to add path to environemt variable during installation for each of the above mentioned tools.
	
3. Linux  
	i. Install Graphwiz  
	https://graphviz.org/download/

Build Instructions  (Not Required if using Dev Cpp)
==================
In case you want to build the source code via terminal, use the following procedure:

run the following command in terminal in the same directory as source code:  
	make  

This is expected to produce the executable binary which goes by the name "DSLAB_Assignment4.exe" in windows and "DSLAB_Assignment4" in linux.

Execution instructions (Not Required if using Dev Cpp)
====================
1. Windows : In Command Prompt type
	DSLAB_Assignment4.exe  
2. Linux  : In terminal type
	./DSLAB_Assignment4  

/* If there is any problem in using above steps for compiling, use the following command to compile:
 *	g++ min_heap.cpp Graph.cpp main.cpp
 *	This is supposed to create an executable(a.exe or a.out) which you must run to start the program.
 */

Program Instructions
====================

NOTE: IF YOU HAVE ENTERED N AS THE NUMBER OF VERTICES, THEN NAMES OF VERTICES WILL BE 0, 1, 2, ..., N-1.
NOTE: WHEN YOU NEED TO SELECT OPTIONS IN ANY MENU, USE ONLY NUMBERS. DO NOT ENTER Y, N, YES, NO AS THE INPUT
      IS NOT DESIGNED TO TAKE CHARACTER INPUT. HOWEVER IN CASE OF FILE NAMES YOU HAVE TO USE CHARACTERS AND
	  IT WILL NOT CAUSE AN Y PROBLEM.

The program starts with the following menu:

	This is an implementation of Graph
	--------------------------------------------------------
	1. Create a new graph manually.
	2. Create a new graph from file input.
	3. Print graph on terminal.
	4. Print graph on image using Graphviz.
	5. Perform DFS Traversal.
	6. Find all strongly connected components using Tarjan's algorithm.
	7. Create another graph G'(V, E') from the existing graph G(V, E) such that
		   -> E' is a subset of E and
		   -> G' has the same SCCs as G and
		   -> G' has the same component graph as G and
		   -> E' is as small as possible.
	8. Determine whether graph is semi-connected.
	9. Compute shortest distance from a node using Dijsktra's Algorithm.

	Press 0 to quit.
	Enter Your Choice:

OPTION 1: is used to create graph by adding number of vertices and edges manually.
OPTION 2: is used to take file input for creating graph. You have to select if the input file contains weights 
			or not in the next menu shown.
OPTION 3: will print the adjacency list representation 
OPTION 4: will create an image of the graph. Use the below command to convert .gv file to .png file for viewing:
			dot -Tpng graph.gv -o graph.png
OPTION 5: will perform DFS traversal and produce a .gv file. Input the source vertex first. Use the command:
			dot -Tpng dfs_traversal.gv -o dfs_traversal.png
OPTION 6: will find all SCCs using Tarjan's Algo. Use the command to produce the output:
			dot -Tpng tarjan.gv -o tarjan.png
OPTION 7: creates a new graph from an existing graph having as less edges as possible. Use the command for output:
			dot -Tpng graph.gv -o compressed_graph.png
OPTION 8: use this to check if the graph is semi connected. The output is shown in terminal.
OPTION 9: use this to find shortest distance of vertices from a source vertex. First enter the source vertex. 
			Then specify if you want to enter a destination vertex(press 1 or 2). If you sepcify a destination 
			vertex, then path to that vertex from sorce will be shown. Otherwise shortest distance of all 
			vertices from source vertex is printed. Use the following command to produce output:
			dot -Tpng dijsktra_output.gv -o dijsktra_output.png

Format of input file
====================

Case 1: Without Edge Weights
----------------------------

5 10
0 1
0 2
1 4
1 2
2 1
2 4
2 3
3 0
3 4
4 3

Here 5 10 in the first line specify that 
	1. number of vertices is 5 and 
	2. number of edges is 10

Each line after first line specify 
	source vertex name followed by destination vertex name of an edge.

Case 1: With Edge Weights
----------------------------

5 10
0 1 3
0 2 5
1 4 6
1 2 2
2 1 1
2 4 4
2 3 6
3 0 3
3 4 7
4 3 2

Here 5 10 in the first line specify that 
	1. number of vertices is 5 and 
	2. number of edges is 10

Each line after first line specify 
	source vertex name followed by destination vertex name followed by weight of an edge.