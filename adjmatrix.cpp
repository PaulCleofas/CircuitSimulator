#include "adjmatrix.h"

using namespace std;


AdjacencyMatrix::AdjacencyMatrix(int n) {
    this->numNodes = n;
    visited = new bool [n];
    adjMat = new int* [n];
    for (int i = 0; i < n; i++) {
        adjMat[i] = new int [n];
        for(int j = 0; j < n; j++)
        {
            adjMat[i][j] = 0;
        }
    }

}

int AdjacencyMatrix::accessMatrix(int row, int column) {
    return adjMat[row][column];
}

int AdjacencyMatrix::accessMatrix(int row, int column, int value) {
    adjMat[row][column] = value;

    return value;
}

void AdjacencyMatrix::addEdge(int startVertex, int endVertex) {
    if( startVertex > numNodes || endVertex > numNodes|| startVertex < 0 || endVertex < 0) {   
        cout<<"Invalid edge!\n";
    }
    else
    {
        adjMat[startVertex - 1][endVertex - 1] = 1;
        adjMat[endVertex - 1][startVertex - 1] = 1;
            
    }
}

 /*
 * Print the graph
 */ 
void AdjacencyMatrix::display() {
    int i,j;
    for(i = 0;i < numNodes;i++)
    {
        for(j = 0; j < numNodes; j++)
            cout<<adjMat[i][j]<<"  ";
        cout<<endl;
    }
}


// /*
//  * Main
//  */ 
// int main()
// {
//     int nodes, max_edges, origin, destin;
//     cout<<"Enter number of nodes: ";
//     cin>>nodes;
//     AdjacencyMatrix am(nodes);
//     max_edges = nodes * (nodes - 1);
//     for (int i = 0; i < max_edges; i++)
//     {
//         cout<<"Enter edge (-1 -1 to exit): ";
//         cin>>origin>>destin;
//         if((origin == -1) && (destin == -1))
//             break;
//         am.addEdge(origin, destin);
//     }
//     am.display();
//     return 0;
// }



