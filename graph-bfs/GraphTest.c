// Name: Abrham Dawit
// CruzID: asdawit
// Winter 25 - 101
// Assignment: pa2
// GraphTest.c
// Test client for the Graph ADT

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

    // 2. Test addEdge()
    printf("\nAdding edges to graph...\n");
    addEdge(G, 1, 2);
    addEdge(G, 1, 3);
    addEdge(G, 2, 4);
    addEdge(G, 3, 5);
    addEdge(G, 4, 6);
    addEdge(G, 5, 6);
    printf("Edges added. Graph should now be connected.\n");

    // 3. Print Graph Structure
    printf("\nGraph adjacency list:\n");
    printGraph(stdout, G);

    // 4. Test BFS
    printf("\nRunning BFS from vertex 1...\n");
    BFS(G, 1);
    for (int i = 1; i <= n; i++) {
        printf("Vertex %d: Distance = %d, Parent = %d\n",
               i, getDist(G, i), getParent(G, i));
    }

    // 5. Test Path Retrieval
    List path = newList();
    printf("\nTesting shortest path retrieval from vertex 1:\n");
    for (int v = 1; v <= n; v++) {
        getPath(path, G, v);
        printf("Shortest path from 1 to %d: ", v);
        if (front(path) == NIL) {
            printf("No path exists.\n");
        } else {
            printList(stdout, path);
            printf("\n");
        }
        clear(path);
    }

    // 6. Test Directed Graph Operations
    printf("\nCreating a directed graph...\n");
    Graph D = newGraph(n);
    addArc(D, 1, 2);
    addArc(D, 2, 3);
    addArc(D, 3, 4);
    addArc(D, 4, 5);
    addArc(D, 5, 6);
    addArc(D, 6, 1);
    printf("Directed graph created.\n");

    printf("\nPrinting directed graph adjacency list:\n");
    printGraph(stdout, D);

    // 7. Run BFS on Directed Graph
    printf("\nRunning BFS on directed graph from vertex 1...\n");
    BFS(D, 1);
    for (int i = 1; i <= n; i++) {
        printf("Vertex %d: Distance = %d, Parent = %d\n",
               i, getDist(D, i), getParent(D, i));
    }

    // 8. Edge Cases Testing
    printf("\nTesting graph edge cases...\n");

    printf("\nRunning BFS on an empty graph (should have INF distances):\n");
    Graph Empty = newGraph(4);
    BFS(Empty, 1);
    for (int i = 1; i <= 4; i++) {
        printf("Vertex %d: Distance = %d, Parent = %d\n",
               i, getDist(Empty, i), getParent(Empty, i));
    }

    // 9. Free Memory
    printf("\nCleaning up memory...\n");
    freeList(&path);
    freeGraph(&G);
    freeGraph(&D);
    freeGraph(&Empty);
    printf("GraphTest completed successfully!\n");

    return 0;
}
