CC= g++
OBJS = adjmatrix.o elematrix.o circuitsimulator.o findmesh.o LU.o
EXE = circuitsimulator
CFLAGS= -c -Wall -std=c++11
LFLAGS=

circuitsimulator: $(OBJS)
	$(CC) $(OBJS) -o $(EXE) $(LFLAGS)

circuitsimulator.o: circuitsimulator.cpp adjmatrix.o adjmatrix.h elematrix.o elematrix.h LU.o findmesh.o
	$(CC) circuitsimulator.cpp -o circuitsimulator.o $(CFLAGS)

adjmatrix.o: adjmatrix.h
	$(CC) adjmatrix.cpp -o adjmatrix.o $(CFLAGS)

elematrix.o: elematrix.h
	$(CC) elematrix.cpp -o elematrix.o $(CFLAGS)	

findmesh.o: findmesh.h adjmatrix.o adjmatrix.h
	$(CC) findmesh.cpp -o findmesh.o $(CFLAGS)

LU.o: LU.h adjmatrix.h adjmatrix.o elematrix.h elematrix.o findmesh.h findmesh.o
	$(CC) LU.cpp -o LU.o $(CFLAGS)

clean:
	@rm -f $(OBJS) $(EXE)