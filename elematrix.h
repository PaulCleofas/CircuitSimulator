#ifndef _ELEMENTMATRIX_H
#define _ELEMENTMATRIX_H

#include <iostream>
#include <cstdlib>

class ElementMatrix {
    public:
        /* Constructor */
        ElementMatrix(int n);

        void addComponent(int startVertex, int endVertex, float cost);

        void display();

        int accessMatrix(int row, int column);

        int accessMatrix(int row, int column, int value);

    private:
        int numNodes;
        float **elemMat;
        bool *visited;

};

#endif