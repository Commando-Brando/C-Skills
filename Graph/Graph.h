/************************************************************************
Graph.h

Purpose:
    Struct definitions for the Adjacency Matrix representation of a Graph.
    Define function prototypes used by graphs.
************************************************************************/

//Including Queue.h and Stack.h so that they can be used in the shortest path algorithm.
#include "Queue.h"
#include "Stack.h"
#define TRUE 1
#define FALSE 0

//Typedef so that graph Vertices are represented as integers.
typedef int Vertex;

//typedef for a directed edge that begins at fromVertex and ends at toVertex.
typedef struct
{
	Vertex fromVertex;
	Vertex toVertex;
	
} Edge;


//Typedef for a Graph implementation.  
//Contains an adjacency matrix and the number of vertices in the graph (n).
typedef struct
{
    int n;
    int **adjacencyM;
} GraphImp;

typedef GraphImp *Graph;


/*****Prototypes*******/

//Given the number of vertices of the graph, malloc the nxn adjacency matrix and initialize every edge to 0 (i.e. the edges aren't there initially).
//Return the address of the graph.
Graph newGraph(int n);

//Free the adjacency matrix and then the graph itself.
void freeGraph(Graph g);

//Add the edge e to the graph g.
void addEdge(Graph g, Edge e);

//Given graph g and vertex v, scan the adjacency matrix and return the first edge in g such that v is the "fromVertex" of the edge.
//Return NULL if there is no such edge.
Edge firstAdjacent(Graph g, Vertex v);

//Given graph g and vertex e, scan the adjacency matrix and return the next edge after e in g such that e.fromVertex is the "fromVertex" of the edge.
//Return NULL if there is no such edge.
Edge nextAdjacent(Graph g, Edge e);

//Print the sequence of vertices on a shortest path in g starting from start and ending at destination.  
//A shortest path should be computed using the Breadth First Search (BFS) algorithm that maintains the parents of each vertex in the shortest path tree as defined in class.  
//BFS can be implemented directly in this function, or you may create a new function for BFS.
void shortestPath(Graph g, Vertex start, Vertex destination);
//prints our the edges of a graph
void printGraph(Graph g);

void printGraphMatrix(Graph g);