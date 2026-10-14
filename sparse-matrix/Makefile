#------------------------------------------------------------------------------
# Name: Abrham Dawit
# CruzID: asdawit
# Winter 25 - 101
# Assignment: pa4
# Makefile
# Compilation file for Programming Assignment 4
#------------------------------------------------------------------------------
#  Makefile for CSE 101 Programming Assignment 4
#
#  make                     makes Sparse
#  make MatrixTest          makes MatrixTest
#  make ListTest            makes ListTest
#  make clean               removes all binaries
#  make SparseCheck         runs Sparse in Valgrind
#  make MatrixCheck         runs MatrixTest in Valgrind
#  make ListCheck           runs ListTest in Valgrind
#------------------------------------------------------------------------------

# Program Names
MAIN           = Sparse
ADT1           = Matrix
ADT2           = List

# Source Files
SOURCE         = $(MAIN).c
OBJECT         = $(MAIN).o
ADT1_TEST      = $(ADT1)Test
ADT1_SOURCE    = $(ADT1).c
ADT1_OBJECT    = $(ADT1).o
ADT1_HEADER    = $(ADT1).h
ADT2_TEST      = $(ADT2)Test
ADT2_SOURCE    = $(ADT2).c
ADT2_OBJECT    = $(ADT2).o
ADT2_HEADER    = $(ADT2).h

# Compilation and Linking
COMPILE        = gcc -std=c17 -Wall -c
LINK           = gcc -std=c17 -Wall -o
REMOVE         = rm -f
MEMCHECK       = valgrind --leak-check=full

# Default target (Compile Sparse)
$(MAIN): $(OBJECT) $(ADT1_OBJECT) $(ADT2_OBJECT)
	$(LINK) $(MAIN) $(OBJECT) $(ADT1_OBJECT) $(ADT2_OBJECT)

# Compile MatrixTest
$(ADT1_TEST): $(ADT1_TEST).o $(ADT1_OBJECT) $(ADT2_OBJECT)
	$(LINK) $(ADT1_TEST) $(ADT1_TEST).o $(ADT1_OBJECT) $(ADT2_OBJECT)

# Compile ListTest
$(ADT2_TEST): $(ADT2_TEST).o $(ADT2_OBJECT)
	$(LINK) $(ADT2_TEST) $(ADT2_TEST).o $(ADT2_OBJECT)

# Compile object files
$(OBJECT): $(SOURCE) $(ADT1_HEADER) $(ADT2_HEADER)
	$(COMPILE) $(SOURCE)

$(ADT1_TEST).o: $(ADT1_TEST).c $(ADT1_HEADER) $(ADT2_HEADER)
	$(COMPILE) $(ADT1_TEST).c

$(ADT2_TEST).o: $(ADT2_TEST).c $(ADT2_HEADER)
	$(COMPILE) $(ADT2_TEST).c

$(ADT1_OBJECT): $(ADT1_SOURCE) $(ADT1_HEADER)
	$(COMPILE) $(ADT1_SOURCE)

$(ADT2_OBJECT): $(ADT2_SOURCE) $(ADT2_HEADER)
	$(COMPILE) $(ADT2_SOURCE)

# Clean all compiled files
clean:
	$(REMOVE) $(MAIN) $(ADT1_TEST) $(ADT2_TEST)
	$(REMOVE) $(OBJECT) $(ADT1_TEST).o $(ADT2_TEST).o $(ADT1_OBJECT) $(ADT2_OBJECT)

# Memory checks using Valgrind
$(MAIN)Check: $(MAIN)
	$(MEMCHECK) ./$(MAIN) input.txt output.txt

$(ADT1)Check: $(ADT1_TEST)
	$(MEMCHECK) ./$(ADT1_TEST)

$(ADT2)Check: $(ADT2_TEST)
	$(MEMCHECK) ./$(ADT2_TEST)