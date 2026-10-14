// Name: Abrham Dawit
// CruzID: asdawit
// Winter 25 - 101
// Assignment: pa2
// Graph.h
// Header file for the Graph ADT

#ifndef GRAPH_H_INCLUDE
#define GRAPH_H_INCLUDE

#include <stdio.h>
#include "List.h"

// Constants
#define UNDEF -1  // Undefined discovery/finish time
#define NIL 0     // Nil parent for BFS and DFS
#define INF -1    // Infinite distance for unvisited vertices in BFS

// Exported Type
typedef struct GraphObj* Graph;

// Constructors-Destructors
Graph newGraph(int n);
// Creates and returns a new graph with n vertices and no edges.

void freeGraph(Graph* pG);
// Frees all heap memory associated with *pG and sets *pG to NULL.

// Access Functions
int getOrder(Graph G);
// Returns the number of vertices in the graph.

int getSize(Graph G);
// Returns the number of edges in the graph.

int getSource(Graph G);
// Returns the source vertex used for the most recent BFS, or NIL if BFS has not been called.

int getParent(Graph G, int u);
// Returns the parent of vertex u in the BFS tree, or NIL if BFS has not been called. Pre: 1 <= u <= getOrder(G).

int getDist(Graph G, int u);
// Returns the distance from the source to vertex u, or INF if BFS has not been called. Pre: 1 <= u <= getOrder(G).

void getPath(List L, Graph G, int u);
// Appends to List L the vertices of the shortest path from the source to u, or NIL if no path exists. Pre: BFS has been called.

void makeNull(Graph G);
// Deletes all edges in the graph, restoring it to its original state.

// Manipulation Procedures
void addEdge(Graph G, int u, int v);
// Adds an undirected edge between vertices u and v. Pre: 1 <= u, v <= getOrder(G).

void addArc(Graph G, int u, int v);
// Adds a directed edge from vertex u to vertex v. Pre: 1 <= u, v <= getOrder(G).

void BFS(Graph G, int s);
// Runs BFS on the graph using the specified source vertex.

// Other Operations
void printGraph(FILE* out, Graph G);
// Prints the adjacency list representation of the graph to the output file.

#endif // GRAPH_H_INCLUDE
