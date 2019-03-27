#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <iostream>
#include <cstdlib>

class AdjacencyMatrix{
    public:
        /* constructor */
        AdjacencyMatrix(int n);

        /* Add edge to the graph */
        void addEdge(int startVertex, int endVertex);

        void display();

    private:
        int numNodes;
        int **adjMat;
        bool *visited;

};

#endif

