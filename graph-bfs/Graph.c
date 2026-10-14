// Name: Abrham Dawit
// CruzID: asdawit
// Winter 25 - 101
// Assignment: pa2
// Graph.c
// Implementation file for the Graph ADT

#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

typedef struct GraphObj {
    int order;    // Number of vertices
    int size;     // Number of edges
    int source;   // Source vertex for BFS
    List *adj;    // Array of adjacency lists
    int *parent;  // Parent array for BFS
    int *dist;    // Distance array for BFS
} GraphObj;

Graph newGraph(int n) {
    if (n < 1) {
        fprintf(stderr, "Graph Error: newGraph() called with n < 1\n");
        exit(EXIT_FAILURE);
    }

    Graph G = malloc(sizeof(GraphObj));
    if (G == NULL) {
        fprintf(stderr, "Graph Error: malloc failed in newGraph()\n");
        exit(EXIT_FAILURE);
    }

    G->order = n;
    G->size = 0;
    G->source = NIL;

    G->adj = calloc(n + 1, sizeof(List));
    G->parent = calloc(n + 1, sizeof(int));
    G->dist = calloc(n + 1, sizeof(int));

    if (G->adj == NULL || G->parent == NULL || G->dist == NULL) {
        fprintf(stderr, "Graph Error: calloc failed in newGraph()\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 1; i <= n; i++) {
        G->adj[i] = newList();
        G->parent[i] = NIL;
        G->dist[i] = INF;
    }

    return G;
}

void freeGraph(Graph *pG) {
    if (pG == NULL || *pG == NULL) return;

    Graph G = *pG;
    for (int i = 1; i <= G->order; i++) {
        freeList(&(G->adj[i]));
    }

    free(G->adj);
    free(G->parent);
    free(G->dist);
    free(G);

    *pG = NULL;
}

int getOrder(Graph G) {
    if (G == NULL) {
        fprintf(stderr, "Graph Error: getOrder() called on NULL Graph\n");
        exit(EXIT_FAILURE);
    }
    return G->order;
}

int getSize(Graph G) {
    if (G == NULL) {
        fprintf(stderr, "Graph Error: getSize() called on NULL Graph\n");
        exit(EXIT_FAILURE);
    }
    return G->size;
}

int getSource(Graph G) {
    if (G == NULL) {
        fprintf(stderr, "Graph Error: getSource() called on NULL Graph\n");
        exit(EXIT_FAILURE);
    }
    return G->source;
}

int getParent(Graph G, int u) {
    if (G == NULL || u < 1 || u > G->order) {
        fprintf(stderr, "Graph Error: getParent() called with invalid vertex %d\n", u);
        exit(EXIT_FAILURE);
    }
    return G->parent[u];
}

int getDist(Graph G, int u) {
    if (G == NULL || u < 1 || u > G->order) {
        fprintf(stderr, "Graph Error: getDist() called with invalid vertex %d\n", u);
        exit(EXIT_FAILURE);
    }
    return G->dist[u];
}

void makeNull(Graph G) {
    if (G == NULL) {
        fprintf(stderr, "Graph Error: makeNull() called on NULL Graph\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 1; i <= G->order; i++) {
        clear(G->adj[i]);
    }

    G->size = 0;
}

void addEdge(Graph G, int u, int v) {
    if (G == NULL || u < 1 || u > G->order || v < 1 || v > G->order) {
        fprintf(stderr, "Graph Error: addEdge() called with invalid vertices (%d, %d)\n", u, v);
        exit(EXIT_FAILURE);
    }

    addArc(G, u, v);
    addArc(G, v, u);
    G->size--; // Since addArc increments size twice
}

void addArc(Graph G, int u, int v) {
    if (G == NULL || u < 1 || u > G->order || v < 1 || v > G->order) {
        fprintf(stderr, "Graph Error: addArc() called with invalid vertices (%d, %d)\n", u, v);
        exit(EXIT_FAILURE);
    }

    List L = G->adj[u];
    moveFront(L);
    while (index(L) >= 0 && get(L) < v) {
        moveNext(L);
    }
    if (index(L) == -1) {
        append(L, v);
    } else {
        insertBefore(L, v);
    }
    G->size++;
}

void BFS(Graph G, int s) {
    if (G == NULL || s < 1 || s > G->order) {
        fprintf(stderr, "Graph Error: BFS() called with invalid source vertex %d\n", s);
        exit(EXIT_FAILURE);
    }

    for (int i = 1; i <= G->order; i++) {
        G->parent[i] = NIL;
        G->dist[i] = INF;
    }

    G->source = s;
    G->dist[s] = 0;

    List queue = newList();
    append(queue, s);

    while (length(queue) > 0) {
        int x = front(queue);
        deleteFront(queue);

        List adj = G->adj[x];
        moveFront(adj);
        while (index(adj) >= 0) {
            int y = get(adj);
            if (G->dist[y] == INF) {
                G->dist[y] = G->dist[x] + 1;
                G->parent[y] = x;
                append(queue, y);
            }
            moveNext(adj);
        }
    }
    freeList(&queue);
}

void getPath(List L, Graph G, int u) {
    if (G == NULL || u < 1 || u > G->order) {
        fprintf(stderr, "Graph Error: getPath() called with invalid vertex %d\n", u);
        exit(EXIT_FAILURE);
    }
    if (getSource(G) == NIL) {
        fprintf(stderr, "Graph Error: getPath() called before BFS\n");
        exit(EXIT_FAILURE);
    }

    if (G->dist[u] == INF) {
        append(L, NIL);
    } else {
        int x = u;
        List temp = newList();
        while (x != NIL) {
            prepend(temp, x);
            x = G->parent[x];
        }
        moveFront(temp);
        while (index(temp) >= 0) {
            append(L, get(temp));
            moveNext(temp);
        }
        freeList(&temp);
    }
}

void printGraph(FILE *out, Graph G) {
    if (G == NULL) {
        fprintf(stderr, "Graph Error: printGraph() called on NULL Graph\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 1; i <= G->order; i++) {
        fprintf(out, "%d: ", i);
        printList(out, G->adj[i]);
        fprintf(out, "\n");
    }
}