#include "elematrix.h"

using namespace std;


ElementMatrix::ElementMatrix(int n) {
    this->numNodes = n;
    visited = new bool [n];
    elemMat = new float* [n];
    for (int i = 0; i < n; i++) {
        elemMat[i] = new float [n];
        for(int j = 0; j < n; j++)
        {
            elemMat[i][j] = 0;
        }
    }

}

float ElementMatrix::accessMatrix(int row, int column, float value) {
    elemMat[row][column] = value;

    return value;
}

float ElementMatrix::accessMatrix(int row, int column) {
    return elemMat[row][column];
}

void ElementMatrix::addComponent(int startVertex, int endVertex, float cost) {
    if( startVertex > numNodes || endVertex > numNodes|| startVertex < 0 || endVertex < 0) {   
        cout<<"Invalid edge!\n";
    }
    else
    {
        elemMat[startVertex - 1][endVertex - 1] = cost;
            
    }
}

void ElementMatrix::display() {
    int i,j;
    for(i = 0;i < numNodes;i++)
    {
        for(j = 0; j < numNodes; j++)
            cout<<elemMat[i][j]<<"  ";
        cout<<endl;
    }
}