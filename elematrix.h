#ifndef _ELEMENTMATRIX_H
#define _ELEMENTMATRIX_H

#include <iostream>
#include <cstdlib>

class ElementMatrix {
    public:
        /* Constructor */
        ElementMatrix(int n);

        // Returns the value of an entry in the matrix
        float accessMatrix(int row, int column);

        // Changes the value of an entry in matrix and returns this value
        float accessMatrix(int row, int column, float value);

        // Add edge to the graph
        void addComponent(int startVertex, int endVertex, float cost);
        
        // Print the matrix
        void display();

    private:
        int numNodes;
        float **elemMat;
        bool *visited;

};

#endif