CC= g++
OBJS = elematrix.o circuitsimulator.o findmesh.o LU.o results.o
EXE = circuitsimulator
CFLAGS= -c -Wall -std=c++11
LFLAGS=

circuitsimulator: $(OBJS)
	$(CC) $(OBJS) -o $(EXE) $(LFLAGS)

circuitsimulator.o: circuitsimulator.cpp elematrix.o elematrix.h LU.o findmesh.o results.h results.o
	$(CC) circuitsimulator.cpp -o circuitsimulator.o $(CFLAGS)

elematrix.o: elematrix.h
	$(CC) elematrix.cpp -o elematrix.o $(CFLAGS)	

findmesh.o: findmesh.h elematrix.o elematrix.h
	$(CC) findmesh.cpp -o findmesh.o $(CFLAGS)

LU.o: LU.h elematrix.h elematrix.o findmesh.h findmesh.o
	$(CC) LU.cpp -o LU.o $(CFLAGS)

results.o: results.h elematrix.h elematrix.o
	$(CC) results.cpp -o results.o $(CFLAGS)

clean:
	@rm -f $(OBJS) $(EXE)