// Name: Abrham Dawit
// CruzID: asdawit
// Winter 25 - 101
// Assignment: pa3
// FindComponents.c
// Main program to compute strongly connected components (SCCs) in a directed graph using DFS.

#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
#include "List.h"

int main(int argc, char *argv[])
{
    // 1. Check for correct usage
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // 2. Open input and output files
    FILE *in = fopen(argv[1], "r");
    FILE *out = fopen(argv[2], "w");

    if (in == NULL || out == NULL)
    {
        fprintf(stderr, "Error: Cannot open file.\n");
        return EXIT_FAILURE;
    }

    // 3. Read the number of vertices
    int n;
    fscanf(in, "%d", &n);
    Graph G = newGraph(n);

    // 4. Read edges and build the graph
    int u, v;
    while (fscanf(in, "%d %d", &u, &v) == 2 && u != 0 && v != 0)
    {
        addArc(G, u, v);
    }
    fclose(in);

    // 5. Print the adjacency list representation
    fprintf(out, "Adjacency list representation of G:\n");
    printGraph(out, G);
    fprintf(out, "\n");

    // 6. Prepare for DFS
    List S = newList();
    for (int i = 1; i <= n; i++)
        append(S, i);

    DFS(G, S);

    // 7. Compute the transpose graph
    Graph GT = transpose(G);
    DFS(GT, S);

    // 8. Identify strongly connected components (SCCs)
    int numSCCs = 0;
    List component = newList();
    moveFront(S);

    while (index(S) >= 0)
    {
        int v = get(S);
        if (getParent(GT, v) == NIL)
        {
            if (length(component) > 0)
            {
                clear(component);
            }
            numSCCs++;
        }
        append(component, v);
        moveNext(S);
    }
    freeList(&component);

    fprintf(out, "G contains %d strongly connected components:\n", numSCCs);
    List* allComponents = malloc(numSCCs * sizeof(List));
    for(int i = 0; i < numSCCs; i++) {
        allComponents[i] = newList();
    }
    int k = 0;
    component = allComponents[k];
    moveFront(S);
    while (index(S) >= 0)
    {
        int v = get(S);
        if (getParent(GT, v) == NIL)
        {
            if (length(component) > 0)
            {
                component = allComponents[++k];
            }
        }
        append(component, v);
        moveNext(S);
    }
    for(int i = 0; i < numSCCs; i++) {
        fprintf(out, "Component %d: ", i+1);
        printList(out, allComponents[numSCCs - i - 1]);
        fprintf(out, "\n");
    }

    // 9. Free all memory
    freeList(&S);
    freeList(&component);
    freeGraph(&G);
    freeGraph(&GT);
    fclose(out);

    return EXIT_SUCCESS;
}
