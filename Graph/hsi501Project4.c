#include "Graph.h"
int main()
{
    //create file variable and open the file
    FILE *f;
    f = fopen("p4Input.txt", "r");
    if(f == NULL){
        printf("ERROR: file did not open properly\n");
        return -1;
    }
    //declare variables for main
    char arr[20];
    char stemp[20];
    int temp;
    int i = 0;
    Edge e;
    //read in first couple lines to determine how large the graph will be and create graph
    temp = fscanf(f, "%s", arr);
    sscanf(arr, "%d", &temp);
    Graph g = newGraph(temp);
    temp = fscanf(f, "%s", arr);
    sscanf(arr, "%d", &temp);
   //first while loop to start reading through the first part of the file to fill up the matrix
    while(fgets(arr, 20, f) && i <= temp){
        if(i > 0){
        sscanf(arr, "%d %d", &e.fromVertex, &e.toVertex);
        addEdge(g,e);
        }
        i++;
    }
    //second while loop that takes file input to determine shortest path between 2 vertexes 
    while(fgets(arr, 20, f)){
        sscanf(arr, "%s %d %d", stemp, &e.fromVertex, &e.toVertex);
        shortestPath(g, e.fromVertex, e.toVertex);
    }
    //free graph and close the file then end program
    freeGraph(g);
    fclose(f);
    return 0;
}


