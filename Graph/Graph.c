#include "Graph.h"

/******
 * In this file, provide all of the definitions of the graph functions as described in Graph.h.
 *
 * ****/
//Given the number of vertices of the graph, malloc the nxn adjacency matrix and initialize every edge to 0 (i.e. the edges aren't there initially).
//Return the address of the graph.
Graph newGraph(int n){
    int i, j;
    Graph g = (Graph) malloc(sizeof(GraphImp));
    g->adjacencyM = (int**) malloc(n * sizeof(int*));
    for(i = 0; i < n; i++){
        g->adjacencyM[i] = (int*) malloc(n * sizeof(int));
    }
    g->n = n;
    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            g->adjacencyM[i][j] = 0;
        }
    }
    return g;
}

//Free the adjacency matrix and then the graph itself.
void freeGraph(Graph g){
    int i;
    for(i = 0; i < g->n; i++){
        free(g->adjacencyM[i]); //free each drawer of 2D array
    }
    free(g->adjacencyM); //free 1st dimension of 2D array
    free(g); //free graph 
}

//Add the edge e to the graph g.
void addEdge(Graph g, Edge e){
    int i;
    for(i = 0; i < g->n; i++){
        if(i == e.toVertex){
            g->adjacencyM[e.fromVertex][e.toVertex] = 1; //set value of graph position to 1 to indicate a edge path connection
            return;
        }
    }
    printf("ERROR: could not add edge either there already of non existent\n");
}

//Given graph g and vertex v, scan the adjacency matrix and return the first edge in g such that v is the "fromVertex" of the edge.
//Return NULL if there is no such edge.
Edge firstAdjacent(Graph g, Vertex v){
    int i;
    Edge e;
    for(i = 0; i < g->n; i++){
        if(g->adjacencyM[v][i] == 1){ //for loop scans matrix to find the first edge for a vertex
            e.fromVertex = v;
            e.toVertex = i;
            return e;
        }
    }
    e.fromVertex = e.toVertex = -1;
    return e;
}

//Given graph g and vertex e, scan the adjacency matrix and return the next edge after e in g such that e.fromVertex is the "fromVertex" of the edge.
//Return -1 stored in an edge if there is no such edge.
Edge nextAdjacent(Graph g, Edge e){
    int i;
    for(i = e.toVertex + 1; i < g->n; i++){
        if(g->adjacencyM[e.fromVertex][i] == 1){ //for loop scans matrix to find the next edge for a vertex based on previous starting point
            e.toVertex = i;
            return e;
        }
    }
    e.fromVertex = e.toVertex = -1;
    return e;
}

//Print the sequence of vertices on a shortest path in g starting from start and ending at destination.  
//A shortest path should be computed using the Breadth First Search (BFS) algorithm that maintains the parents of each vertex in the shortest path tree as defined in class.  
//BFS can be implemented directly in this function, or you may create a new function for BFS.
void shortestPath(Graph g, Vertex start, Vertex destination){
    //declare variables for function including arrays that we malloc
    int i;
    int j = 0;
    Edge e;
    Vertex *parent = (Vertex*) malloc(g->n * sizeof(Vertex));
    Vertex *visited = (Vertex*) malloc(g->n * sizeof(Vertex));
    for(i = 0; i < g->n; i++){ //for loop sets values for parent and visited arrays
        visited[i] = FALSE;
        parent[i] = -1;
    }
    Queue q = newQueue(); //create Queue data structure
    Stack s = newStack(g->n); //create Stack data structure 
    enqueue(q, start); //enqueue and visit array below to start at start vertex
    visited[start] = TRUE;
    Vertex curV;
    while(dequeue(q, &curV) == TRUE){ //while loop ends when the queue has no more nodes and curV pointer returns maintains previous to vertex
        for(e = firstAdjacent(g, curV); e.toVertex != -1; e = nextAdjacent(g, e)){
            Vertex tempV = e.toVertex;
            if(visited[tempV] == FALSE){ //if we have not visited the vertex we enter this if statement and we enqueue the to vertex
                enqueue(q, tempV);
                visited[tempV] = TRUE; //set the vertex to being visited
                parent[tempV] = curV; //put who the parent vertex is of current vertex in array
            }
        }
        j++;
    }
    curV = FALSE;
    for(i = 0; i < g->n; i++){ //check to see if the start vertex has ANY connecting vertexes via edges
        if(parent[i] != -1){
            curV = TRUE;
        }
    }
    //if the start vertex has edges than we use a stack to print out the edge-vertex path
    if(curV == TRUE){
        curV = destination;
        while(parent[curV] != -1){ //while loop adds edge path to stack
            push(s, curV);
            curV = parent[curV];
        }
        push(s, curV);
        printf("Shortest path from %d to %d: ", start, destination);
        while(isEmptyStack(s) == FALSE){ //while loop pops and prints the paths
            Element es = pop(s);
            printf("%d", es);
            if(isEmptyStack(s) == FALSE)
                printf(" -> ");
        }
        printf("\n");
    }
    else{
        printf("There is no path from %d to %d.\n", start, destination);
    }
    //free all function variables that were dynamically allocated
    freeStack(s);
    free(parent);
    free(visited);
    freeQueue(q);
}
//prints the graph edge connections
void printGraph(Graph g){
    int i, j;
    for(i = 0; i < g->n; i++){
        for(j = 0; j < g->n; j++){
            if(g->adjacencyM[i][j] == 1){
                printf("Vertex %d connects to vertex %d\n", i, j);
            }
        }
    }
}
//prints out the graph in a matrix style format
void printGraphMatrix(Graph g){
    int i, j;
    for(i = 0; i < g->n; i++){
        printf("Row: %d\n", i);
        for(j = 0; j < g->n; j++){
            printf("%d\t", g->adjacencyM[i][j]);
        }
        printf("\n");
    }
}