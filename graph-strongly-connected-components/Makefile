#------------------------------------------------------------------------------
# Name: Abrham Dawit
# CruzID: asdawit
# Winter 25 - 101
# Assignment: pa3
# Makefile
# Compilation file for Programming Assignment 3
#------------------------------------------------------------------------------
#  Makefile for CSE 101 Programming Assignment 3
#
#  make                     makes FindComponents
#  make GraphTest           makes GraphTest
#  make clean               removes binaries
#  make checkFind           tests FindComponents for memory leaks
#  make checkTest           tests GraphTest for memory leaks
#------------------------------------------------------------------------------

# Source files and objects
BASE_SOURCES   = Graph.c List.c
BASE_OBJECTS   = Graph.o List.o
HEADERS        = Graph.h List.h

# Compilation and linking settings
COMPILE        = gcc -std=c17 -Wall -c
LINK           = gcc -std=c17 -Wall -o
REMOVE         = rm -f
MEMCHECK       = valgrind --leak-check=full

# Build FindComponents executable
FindComponents : FindComponents.o $(BASE_OBJECTS)
	$(LINK) FindComponents FindComponents.o $(BASE_OBJECTS)

# Build GraphTest executable
GraphTest : GraphTest.o $(BASE_OBJECTS)
	$(LINK) GraphTest GraphTest.o $(BASE_OBJECTS)

# Compile individual files
FindComponents.o : FindComponents.c $(HEADERS)
	$(COMPILE) FindComponents.c

GraphTest.o : GraphTest.c $(HEADERS)
	$(COMPILE) GraphTest.c

$(BASE_OBJECTS) : $(BASE_SOURCES) $(HEADERS)
	$(COMPILE) $(BASE_SOURCES)

# Clean up object files and executables
clean :
	$(REMOVE) FindComponents GraphTest FindComponents.o GraphTest.o $(BASE_OBJECTS)

# Memory check for FindComponents
checkFind : FindComponents
	$(MEMCHECK) ./FindComponents infile1.txt outfile1.txt

# Memory check for GraphTest
checkTest : GraphTest
	$(MEMCHECK) ./GraphTest
