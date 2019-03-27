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

    private:
        int numNodes;
        float **elemMat;
        bool *visited;

};

#endif