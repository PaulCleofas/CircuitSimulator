CC= g++
OBJS = adjmatrix.o
EXE = adjmatrix
CFLAGS= -c -Wall -std=c++11
LFLAGS=

adjmatrix: adjmatrix.o
	$(CC) adjmatrix.o -o adjmatrix $(LFLAGS)

adjmatrix.o: adjmatrix.h
	$(CC) adjmatrix.cpp -o adjmatrix.o $(CFLAGS)

clean:
	@rm -f $(OBJS) $(EXE)