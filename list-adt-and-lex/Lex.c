// Name: Abrham Dawit
// Cruzid: asdawit
// Winter 25 - 101
// Assignment: pa1
// Lex.c
// Main program for this project

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"

char* my_strdup(const char* s) {
    size_t len = strlen(s) + 1;
    char* copy = malloc(len);
    if (copy) {
        memcpy(copy, s, len);
    }
    return copy;
}

int main(int argc, char *argv[]) {
    // 1. Command Line Arguments and Error Handling
    if (argc != 3) {
        fprintf(stderr, "Usage: Lex <input file> <output file>\n");
        return 1;
    }
    
    char * inputFile = argv[1];
    char * outputFile = argv[2];
    
    // 2. Reading the Input File
    FILE *in = fopen(inputFile, "r");
    if (in == NULL){
        fprintf(stderr, "Unable to open file: %s\n", inputFile);
        return 1;
    }

    // Count the lines in the input file
    int n = 0;
    char c;
    while((c = fgetc(in)) != EOF){
         if (c == '\n') n++;
    }
    rewind(in);
    
    // Allocate memory for string array    
    char **stringArray = malloc(n * sizeof(char *));
    if (stringArray == NULL) {
      fprintf(stderr, "Memory allocation failed\n");
      fclose(in);
      return 1;
    }

    // Read lines into stringArray
    char buffer[256];
    for(int i = 0; i < n; i++){
      if (fgets(buffer, sizeof(buffer), in)) {
         buffer[strcspn(buffer, "\n")] = '\0'; // strip newline
         stringArray[i] = my_strdup(buffer); //use custom strdup
         if (stringArray[i] == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            fclose(in);
            return 1;
	 }
      }
    }
    fclose(in);
    
    // 3. Creating and Sorting the List of Indices
    List L = newList();
    for (int i = 0; i < n; i++) {
        moveFront(L);
        while (index(L) != -1 && strcmp(stringArray[get(L)], stringArray[i]) < 0) {
            moveNext(L);
	}
        if(index(L) == -1){
            append(L, i);
        } else insertBefore(L, i);
    }

    // 4. Printing the Sorted Output
    FILE *out = fopen(outputFile, "w");
    if (out == NULL){
         fprintf(stderr, "Unable to open output file: %s\n", outputFile);
         freeList(&L);
	 return 1;
    }

    moveFront(L);
    while(index(L) != -1){
        fprintf(out, "%s\n", stringArray[get(L)]);
        moveNext(L);
    }
    fclose(out);

    // 5. Memory Management and Cleanup
    for(int i = 0; i < n; i++){
       free(stringArray[i]);
    }
    free(stringArray);
    freeList(&L);

    return 0;
}
