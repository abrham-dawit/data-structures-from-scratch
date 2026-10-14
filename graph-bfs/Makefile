#------------------------------------------------------------------------------
# Name: Abrham Dawit
# CruzID: asdawit
# Winter 25 - 101
# Assignment: pa2
# Makefile
# Compilation file (Improved and finalized version)
#------------------------------------------------------------------------------
#  Makefile for CMPS 101 Programming Assignment 2
#
#  make                     compiles FindPath
#  make GraphTest           compiles GraphTest
#  make clean               removes binaries
#  make checkFind           runs FindPath with valgrind for memory leaks
#  make checkTest           runs GraphTest with valgrind for memory leaks
#------------------------------------------------------------------------------

BASE_SOURCES   = Graph.c List.c
BASE_OBJECTS   = Graph.o List.o
HEADERS        = Graph.h List.h

COMPILE        = gcc -std=c17 -Wall -c
LINK           = gcc -std=c17 -Wall -o
REMOVE         = rm -f
MEMCHECK       = valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose

FindPath : FindPath.o $(BASE_OBJECTS)
	$(LINK) FindPath FindPath.o $(BASE_OBJECTS)

GraphTest : GraphTest.o $(BASE_OBJECTS)
	$(LINK) GraphTest GraphTest.o $(BASE_OBJECTS)

FindPath.o : FindPath.c $(HEADERS)
	$(COMPILE) FindPath.c

GraphTest.o : GraphTest.c $(HEADERS)
	$(COMPILE) GraphTest.c

$(BASE_OBJECTS) : $(BASE_SOURCES) $(HEADERS)
	$(COMPILE) $(BASE_SOURCES)

clean :
	$(REMOVE) FindPath GraphTest FindPath.o GraphTest.o $(BASE_OBJECTS)

checkFind : FindPath
	$(MEMCHECK) ./FindPath input.txt output.txt

checkTest : GraphTest
	$(MEMCHECK) ./GraphTest
