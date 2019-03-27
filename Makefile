CC= g++
OBJS = adjmatrix.o elematrix.o getmatrices.o
EXE = getmatrices
CFLAGS= -c -Wall -std=c++11
LFLAGS=

getmatrices: adjmatrix.o elematrix.o getmatrices.o
	$(CC) getmatrices.o adjmatrix.o elematrix.o -o getmatrices $(LFLAGS)

adjmatrix.o: adjmatrix.h
	$(CC) adjmatrix.cpp -o adjmatrix.o $(CFLAGS)

elematrix.o: elematrix.h
	$(CC) elematrix.cpp -o elematrix.o $(CFLAGS)	

getmatrices.o: getmatrices.cpp adjmatrix.o adjmatrix.h elematrix.o elematrix.h
	$(CC) getmatrices.cpp -o getmatrices.o $(CFLAGS)

clean:
	@rm -f $(OBJS) $(EXE)