#ifndef _ADJMATRIX_H_
#define _ADJMATRIX_H_

#include <iostream>
#include <cstdlib>

class AdjacencyMatrix{
    public:
        /* constructor */
        AdjacencyMatrix(int n);

        // Returns the value of an entry in adjacency matrix
        int accessMatrix(int row, int column);

        // Changes the value of an entry in adjacency matrix and returns this value
        int accessMatrix(int row, int column, int value);

        // Add edge to the graph
        void addEdge(int startVertex, int endVertex);

        void display();

    private:
        int numNodes;
        int **adjMat;
        bool *visited;

};

#endif

