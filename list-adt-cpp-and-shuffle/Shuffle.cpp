// Name: Abrham Dawit
// CruzID: asdawit
// Winter 25 - 101
// Assignment: pa5
// Shuffle.cpp 
// Simulates perfect shuffling of a deck of cards

#include <iostream>
#include <iomanip>
#include "List.h"

using namespace std;

// Performs a perfect shuffle on List D
void shuffle(List& D) {
    if (D.length() <= 1) return;

    int mid = D.length() / 2;
    List firstHalf, secondHalf;
    D.moveFront();

    // Split into two halves
    for (int i = 0; i < mid; i++) {
        firstHalf.insertBefore(D.moveNext());
    }
    while (D.position() < D.length()) {
        secondHalf.insertBefore(D.moveNext());
    }

    // Perform interleaving
    D.clear();
    firstHalf.moveFront();
    secondHalf.moveFront();
    
    while (firstHalf.position() < firstHalf.length() || secondHalf.position() < secondHalf.length()) {
        if (secondHalf.position() < secondHalf.length()) {
            D.insertBefore(secondHalf.moveNext());
        }
        if (firstHalf.position() < firstHalf.length()) {
            D.insertBefore(firstHalf.moveNext());
        }
    }
}

// Main function
int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <max deck size>" << endl;
        return EXIT_FAILURE;
    }

    int maxN = stoi(argv[1]);
    cout << "deck size       shuffle count" << endl;
    cout << "------------------------------" << endl;

    for (int n = 1; n <= maxN; n++) {
        List deck, original;

        for (int i = 1; i <= n; i++) {
            deck.insertBefore(i);
            original.insertBefore(i);
        }
        int shuffleCount = 0;
        do {
            shuffle(deck);
            shuffleCount++;
        } while (!(deck == original));
        printf("%3d              %3d\n", n, shuffleCount);
    }
    return EXIT_SUCCESS;
}