#include "findmesh.h"

using namespace std;

void spanTree(int n, AdjacencyMatrix& A, AdjacencyMatrix& B, vector<int>& C){
    // A is the original adjacency matrix
    // B is the adjacency matrix of the spanning tree
    // C is a vector of size n and is the list of vertices already included in the spanning tree

    // Initialize B and C
    C.push_back(1);
    for (int i = 1; i < n; i++){
        C.push_back(0);
    }
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            B.accessMatrix(i, j, 0);
        }
    }
    // Construct the spanning tree
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if (A.accessMatrix(i, j) == 1 and C[i] == 1 and C[j] == 0){
                B.accessMatrix(i, j, 1);
                B.accessMatrix(j, i, 1);
                C[j] = 1;
            }
            if (A.accessMatrix(i, j) == 1 and C[i] == 0 and C[j] == 1){
                B.accessMatrix(i, j, 1);
                B.accessMatrix(j, i, 1);
                C[i] = 1;
            }
        }
    }
    return;
}

void prune(int n, AdjacencyMatrix& D){
    bool pruned = true;
    int current_vertex;
    // The number of connected vertices to a particular vertex is one if
    // it is a vertex to be pruned
    int connection_count = 0;
    // D is the nxn matrix to be pruned
    // A vertex is to be pruned if it connects to only one other vertex
    while (pruned){
        pruned = false;
        for (int i = 0; i < n; i++){
            current_vertex = i;
            for (int j = 0; j < n; j++){
                if (D.accessMatrix(i, j) == 1){
                    connection_count++;
                }
            }
            if (connection_count == 1){
                pruned = true;
                // remove edge both ways on all other vertices
                for (int j = 0; j < n; j++){
                    D.accessMatrix(current_vertex, j, 0);
                    D.accessMatrix(j, current_vertex, 0);
                }
            }
            connection_count = 0;
        }
    }
    return;
}

void getMesh(int n, AdjacencyMatrix& A, AdjacencyMatrix& B, vector<AdjacencyMatrix>& mesh){
    // A, B, C, D are matrices of size n×n ;
    AdjacencyMatrix C(n);
    AdjacencyMatrix D(n);

    // A is the original adjacency matrix
    // B is the adjacency matrix of the spanning tree
    // D is the adjacency matrix of the spanning tree , augmented with the addition of the k−th discarded link
    // mesh contains a collection of fundamental cycles, a.k.a. loop currents, represented as matrices

    // first we find the set of discarded links
    // the C matrix will have 1’s in the positions of the discarded links
    // we also copy the B matrix into the D matrix
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            C.accessMatrix(i, j, A.accessMatrix(i, j) - B.accessMatrix(i, j));
            D.accessMatrix(i, j, B.accessMatrix(i, j));
        }
    }
    cout << "Discarded Links Matrix: (A-B)" << endl;
    C.display();
    // here we find all the cycles of the fundamental set
    // Traversing only the upper triangle of the C matrix
    for (int i = 0; i < n-1; i++){
        for(int j = i+1; j < n; j++){
            if (C.accessMatrix(i, j) == 1){  // here we find a discarded link between nodes i and j
                // reset the D matrix as the spanning tree
                AdjacencyMatrix D(n);
                for (int i = 0; i < n; i++){
                    for (int j = 0; j < n; j++){
                        D.accessMatrix(i, j, B.accessMatrix(i, j));
                    }
                }
                // Add the discarded link
                D.accessMatrix(i, j, 1);
                D.accessMatrix(j, i, 1);
                prune(n, D);
                mesh.push_back(D);
            }
        }
    }
    return;
}