// Name: Abrham Dawit
// CruzID: asdawit
// Winter 25 - 101
// Assignment: pa3
// Graph.c
// Implementation file for the Graph ADT

#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

// Graph struct
typedef struct GraphObj {
    List* adj;
    int* parent;
    int* discover;
    int* finish;
    int order;
    int size;
    int time;
} GraphObj;

// Function prototypes
void visit(Graph G, int u, List S);

// Constructors-Destructors
Graph newGraph(int n) {
    Graph G = malloc(sizeof(GraphObj));
    if (G == NULL) {
        fprintf(stderr, "Graph Error: newGraph() failed to allocate memory\n");
        exit(EXIT_FAILURE);
    }

    G->order = n;
    G->size = 0;
    G->time = 0;

    G->adj = calloc(n + 1, sizeof(List));
    G->parent = calloc(n + 1, sizeof(int));
    G->discover = calloc(n + 1, sizeof(int));
    G->finish = calloc(n + 1, sizeof(int));

    for (int i = 1; i <= n; i++) {
        G->adj[i] = newList();
        G->parent[i] = NIL;
        G->discover[i] = UNDEF;
        G->finish[i] = UNDEF;
    }
    return G;
}

void freeGraph(Graph* pG) {
    if (pG != NULL && *pG != NULL) {
        Graph G = *pG;
        for (int i = 1; i <= G->order; i++) {
            freeList(&(G->adj[i]));
        }
        free(G->adj);
        free(G->parent);
        free(G->discover);
        free(G->finish);
        free(G);
        *pG = NULL;
    }
}

// Access functions
int getOrder(Graph G) { return G->order; }
int getSize(Graph G) { return G->size; }
int getParent(Graph G, int u) { return G->parent[u]; }
int getDiscover(Graph G, int u) { return G->discover[u]; }
int getFinish(Graph G, int u) { return G->finish[u]; }

// Manipulation procedures
void addArc(Graph G, int u, int v) {
    if (G == NULL || u < 1 || u > G->order || v < 1 || v > G->order) return;

    for(moveFront(G->adj[u]); index(G->adj[u]) >= 0; moveNext(G->adj[u])) {
        if (get(G->adj[u]) == v) {
            return;
        }
    }

    moveFront(G->adj[u]);
    while (index(G->adj[u]) >= 0) {
        if(get(G->adj[u]) > v) {
            insertBefore(G->adj[u], v);
            break;
        }
        moveNext(G->adj[u]);
    }


    if (index(G->adj[u]) == -1) {
        append (G->adj[u], v);
    }
    G->size++;
}

void addEdge(Graph G, int u, int v) {
    addArc(G, u, v);
    addArc(G, v, u);
    G->size--;
}

void visit(Graph G, int u, List S) {
    G->discover[u] = ++G->time;
    moveFront(G->adj[u]);

    while (index(G->adj[u]) >= 0) {
        int v = get(G->adj[u]);
        if (G->discover[v] == UNDEF) {
            G->parent[v] = u;
            visit(G, v, S);
        }
        moveNext(G->adj[u]);
    }

    G->finish[u] = ++G->time;
    prepend(S, u);
}

void DFS(Graph G, List S) {
    for (int i = 1; i <= G->order; i++) {
        G->parent[i] = NIL;
        G->discover[i] = UNDEF;
        G->finish[i] = UNDEF;
    }

    G->time = 0;
    List finishedOrder = newList();

    moveFront(S);
    while (index(S) >= 0) {
        int u = get(S);
        if (G->discover[u] == UNDEF) {
            visit(G, u, finishedOrder);
        }
        moveNext(S);
    }

    clear(S);
    moveFront(finishedOrder);
    while (index(finishedOrder) >= 0) {
        append(S, get(finishedOrder));
        moveNext(finishedOrder);
    }

    freeList(&finishedOrder);
}

// Other operations
Graph transpose(Graph G) {
    Graph T = newGraph(G->order);
    for (int i = 1; i <= G->order; i++) {
        moveFront(G->adj[i]);
        while (index(G->adj[i]) >= 0) {
            addArc(T, get(G->adj[i]), i);
            moveNext(G->adj[i]);
        }
    }
    return T;
}

void printGraph(FILE* out, Graph G) {
    for (int i = 1; i <= G->order; i++) {
        fprintf(out, "%d: ", i);
        moveFront(G->adj[i]);
        while (index(G->adj[i]) >= 0) {
            fprintf(out, "%d ", get(G->adj[i]));
            moveNext(G->adj[i]);
        }
        fprintf(out, "\n");
    }
}
