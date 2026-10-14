#------------------------------------------------------------------------------
# Name: Abrham Dawit
# CruzID: asdawit
# Winter 25 - 101
# Assignment: pa6
# Makefile
# Compilation file for Programming Assignment 6
#------------------------------------------------------------------------------
#  Makefile for CSE 101 Programming Assignment 6
#
#  make                     makes the Arithmetic executable
#  make BigIntegerTest      makes the BigIntegerTest executable
#  make ListTest            makes the ListTest executable
#  make clean               removes all binaries
#  make ArithmeticCheck     runs Arithmetic under valgrind on input.txt output.txt
#  make BigIntegerCheck     runs BigIntegerTest under valgrind
#  make ListCheck           runs ListTest under valgrind
#------------------------------------------------------------------------------

MAIN           = Arithmetic
BIGINT_TEST    = BigIntegerTest
LIST_TEST      = ListTest
ADT1           = BigInteger
ADT2           = List
SOURCE         = $(MAIN).cpp
OBJECT         = $(MAIN).o
ADT1_SOURCE    = $(ADT1).cpp
ADT1_OBJECT    = $(ADT1).o
ADT1_HEADER    = $(ADT1).h
ADT2_SOURCE    = $(ADT2).cpp
ADT2_OBJECT    = $(ADT2).o
ADT2_HEADER    = $(ADT2).h
COMPILE        = g++ -std=c++17 -Wall -c
LINK           = g++ -std=c++17 -Wall -o
REMOVE         = rm -f
MEMCHECK       = valgrind --leak-check=full

$(MAIN): $(OBJECT) $(ADT1_OBJECT) $(ADT2_OBJECT)
	$(LINK) $(MAIN) $(OBJECT) $(ADT1_OBJECT) $(ADT2_OBJECT)

$(BIGINT_TEST): $(BIGINT_TEST).o $(ADT1_OBJECT) $(ADT2_OBJECT)
	$(LINK) $(BIGINT_TEST) $(BIGINT_TEST).o $(ADT1_OBJECT) $(ADT2_OBJECT)

$(LIST_TEST): $(LIST_TEST).o $(ADT2_OBJECT)
	$(LINK) $(LIST_TEST) $(LIST_TEST).o $(ADT2_OBJECT)

$(OBJECT): $(SOURCE) $(ADT1_HEADER) $(ADT2_HEADER)
	$(COMPILE) $(SOURCE)

$(BIGINT_TEST).o: $(BIGINT_TEST).cpp $(ADT1_HEADER) $(ADT2_HEADER)
	$(COMPILE) $(BIGINT_TEST).cpp

$(LIST_TEST).o: $(LIST_TEST).cpp $(ADT2_HEADER)
	$(COMPILE) $(LIST_TEST).cpp

$(ADT1_OBJECT): $(ADT1_SOURCE) $(ADT1_HEADER)
	$(COMPILE) $(ADT1_SOURCE)

$(ADT2_OBJECT): $(ADT2_SOURCE) $(ADT2_HEADER)
	$(COMPILE) $(ADT2_SOURCE)

clean:
	$(REMOVE) $(MAIN) $(BIGINT_TEST) $(LIST_TEST)
	$(REMOVE) $(OBJECT) $(BIGINT_TEST).o $(LIST_TEST).o $(ADT1_OBJECT) $(ADT2_OBJECT)

$(MAIN)Check: $(MAIN)
	$(MEMCHECK) $(MAIN) input.txt output.txt

$(BIGINT_TEST)Check: $(BIGINT_TEST)
	$(MEMCHECK) $(BIGINT_TEST)

$(LIST_TEST)Check: $(LIST_TEST)
	$(MEMCHECK) $(LIST_TEST)