# Data Structures & Algorithms in C and C++

A collection of data structures and algorithms I implemented from scratch in C and C++ while studying Computer Engineering at UC Santa Cruz. No libraries doing the work for me — every list, graph, matrix, and tree here is built node by node, with test drivers I wrote to check my own code.

## What's inside

| Folder | What it is |
|---|---|
| `list-adt-and-lex` | A doubly linked List ADT in C with a cursor, plus a lexicographic sort that reads a file and orders its lines using the list |
| `graph-bfs` | A Graph ADT in C with adjacency lists, and a breadth-first search program that finds shortest paths between vertices |
| `graph-strongly-connected-components` | The same Graph ADT extended with DFS to find strongly connected components (Kosaraju's algorithm) |
| `sparse-matrix` | A sparse Matrix ADT in C — stores only non-zero entries as lists of triples, supports add, multiply, transpose, and scalar ops |
| `list-adt-cpp-and-shuffle` | The List ADT rebuilt as a C++ class, used to simulate perfect shuffles of a deck of cards and count how many shuffles restore the deck |
| `big-integer-arithmetic` | An arbitrary-precision integer library in C++ — add, subtract, multiply, and power for numbers far bigger than 64 bits, backed by the List class |
| `dictionary-bst` | A Dictionary (key-value store) in C++ backed by a binary search tree, with in-order traversal and a client that sorts file lines by key |
| `dictionary-red-black-tree` | The Dictionary rebuilt on a red-black tree so lookups stay balanced, plus a word-frequency counter that counts every word in a text file |

## Build & run

Each folder is self-contained with its own `Makefile`:

```bash
cd big-integer-arithmetic
make          # builds the Arithmetic program and the test drivers
./Arithmetic <input-file> <output-file>
```

Every module ships with the test driver I used while developing it (e.g. `ListTest`, `GraphTest`, `BigIntegerTest`, `DictionaryTest`), so you can verify each ADT on its own before trusting the client programs.

## Why I built this

Data structures clicked for me when I stopped using them and started building them. Writing a red-black tree rotation by hand, or making a sparse matrix multiply without wasting memory on zeros, taught me more about how software actually works than any single class lecture. This is the foundation under everything else I build — my backend and systems projects all trace back to what's in here.

— Abrham Dawit, Computer Engineering, UC Santa Cruz '28
