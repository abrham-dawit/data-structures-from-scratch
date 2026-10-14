// Name: Abrham Dawit
// CruzID: asdawit
// Winter 25 - 101
// Assignment: pa2
// FindPath.c
// Client program to compute shortest paths using BFS

#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
#include "List.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *in = fopen(argv[1], "r");
    FILE *out = fopen(argv[2], "w");

    if (in == NULL) {
        fprintf(stderr, "Error: Cannot open input file %s\n", argv[1]);
        return EXIT_FAILURE;
    }
    if (out == NULL) {
        fprintf(stderr, "Error: Cannot open output file %s\n", argv[2]);
        fclose(in);
        return EXIT_FAILURE;
    }

    int n;
    if (fscanf(in, "%d", &n) != 1 || n < 1) {
        fprintf(stderr, "Error: Invalid number of vertices in input file.\n");
        fclose(in);
        fclose(out);
        return EXIT_FAILURE;
    }

    Graph G = newGraph(n);

    int u, v;
    while (fscanf(in, "%d %d", &u, &v) == 2) {
        if (u == 0 && v == 0) break;  // Termination condition
        if (u < 1 || u > n || v < 1 || v > n) {
            fprintf(stderr, "Error: Invalid edge (%d, %d) in input file.\n", u, v);
            freeGraph(&G);
            fclose(in);
            fclose(out);
            return EXIT_FAILURE;
        }
        addEdge(G, u, v);
    }

    printGraph(out, G);

    List path = newList();

    while (fscanf(in, "%d %d", &u, &v) == 2) {
        if (u == 0 && v == 0) break; // Termination condition

        BFS(G, u);
        getPath(path, G, v);

        fprintf(out, "\nThe distance from %d to %d is ", u, v);
        if (getDist(G, v) == INF) {
            fprintf(out, "infinity\n");
            fprintf(out, "No %d-%d path exists\n", u, v);
        } else {
            fprintf(out, "%d\n", getDist(G, v));
            fprintf(out, "A shortest %d-%d path is: ", u, v);
            printList(out, path);
            fprintf(out, "\n");
        }

        clear(path);
    }

    freeList(&path);
    freeGraph(&G);
    fclose(in);
    fclose(out);

    return EXIT_SUCCESS;
}