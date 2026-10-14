// Name: Abrham Dawit
// CruzID: asdawit
// Winter 25 - 101
// Assignment: pa3
// GraphTest.c
// Test client for the Graph ADT (now includes DFS tests)

#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
#include "List.h"

int main() {
    printf("Running GraphTest...\n\n");

    // 1. Test Graph Construction
    int n = 6;
    Graph G = newGraph(n);
    printf("Graph created with %d vertices.\n", getOrder(G));

    // 2. Test addArc()
    addArc(G, 1, 2);
    addArc(G, 2, 3);
    addArc(G, 3, 1);
    addArc(G, 3, 4);
    addArc(G, 4, 5);
    addArc(G, 5, 6);
    addArc(G, 6, 4);
    printf("Arcs added. Graph should now have a cycle.\n");

    // 3. Print Graph Structure
    printf("Graph adjacency list:\n");
    printGraph(stdout, G);

    // 4. Test DFS
    List order = newList();
    for (int i = 1; i <= n; i++) {
        append(order, i);
    }

    printf("\nRunning DFS on original graph...\n");
    DFS(G, order);
    for (int i = 1; i <= n; i++) {
        printf("Vertex %d: Discover = %d, Finish = %d, Parent = %d\n",
               i, getDiscover(G, i), getFinish(G, i), getParent(G, i));
    }

    // 5. Test Transpose Graph
    Graph T = transpose(G);
    printf("\nTransposed Graph adjacency list:\n");
    printGraph(stdout, T);

    // 6. Run DFS on Transposed Graph
    printf("\nRunning DFS on transposed graph...\n");
    DFS(T, order);
    for (int i = 1; i <= n; i++) {
        printf("Vertex %d: Discover = %d, Finish = %d, Parent = %d\n",
               i, getDiscover(T, i), getFinish(T, i), getParent(T, i));
    }

    // 7. Free Memory
    freeList(&order);
    freeGraph(&G);
    freeGraph(&T);
    printf("\nGraphTest completed successfully!\n");

    return 0;
}
