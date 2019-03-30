CC= g++
OBJS = adjmatrix.o elematrix.o circuitsimulator.o findmesh.o
EXE = circuitsimulator
CFLAGS= -c -Wall -std=c++11
LFLAGS=

circuitsimulator: adjmatrix.o elematrix.o circuitsimulator.o findmesh.o
	$(CC) circuitsimulator.o adjmatrix.o elematrix.o findmesh.o -o circuitsimulator $(LFLAGS)

circuitsimulator.o: circuitsimulator.cpp adjmatrix.o adjmatrix.h elematrix.o elematrix.h
	$(CC) circuitsimulator.cpp -o circuitsimulator.o $(CFLAGS)

adjmatrix.o: adjmatrix.h
	$(CC) adjmatrix.cpp -o adjmatrix.o $(CFLAGS)

elematrix.o: elematrix.h
	$(CC) elematrix.cpp -o elematrix.o $(CFLAGS)	

findmesh.o: findmesh.h adjmatrix.o adjmatrix.h
	$(CC) findmesh.cpp -o findmesh.o $(CFLAGS)

clean:
	@rm -f $(OBJS) $(EXE)