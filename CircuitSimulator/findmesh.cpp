#include "findmesh.h"

using namespace std;

void spanTree(int n, ElementMatrix& A, ElementMatrix& B, vector<int>& C){
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

void prune(int n, ElementMatrix& D){
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

void getMesh(int n, ElementMatrix& A, ElementMatrix& B, vector<ElementMatrix>& mesh){
    // A, B, C, D are matrices of size n×n ;
    ElementMatrix C(n);
    ElementMatrix D(n);

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

    int countEdge = 0;
    // here we find all the cycles of the fundamental set
    // Traversing only the upper triangle of the C matrix
    for (int i = 0; i < n-1; i++){
        for(int j = i+1; j < n; j++){
            if (C.accessMatrix(i, j) == 1){  // here we find a discarded link between nodes i and j
                // reset the D matrix as the spanning tree
                ElementMatrix D(n);
                for (int i = 0; i < n; i++){
                    for (int j = 0; j < n; j++){
                        D.accessMatrix(i, j, B.accessMatrix(i, j));
                    }
                }
                // Add the discarded link
                D.accessMatrix(i, j, 1);
                D.accessMatrix(j, i, 1);
                prune(n, D);
                ElementMatrix E(n);
                if (!mesh.empty()) {
                    // cout << "mesh previous" << endl;
                    // (mesh.back()).display();
                    // cout << "mesh current" << endl;
                    // D.display();
                    for (int i = 0; i < n; i++){
                        for (int j = 0; j < n; j++){

                            if (((mesh.back()).accessMatrix(i,j) || D.accessMatrix(i, j)) 
                                && ((mesh.back()).accessMatrix(i,j) != D.accessMatrix(i, j))) { 

                                E.accessMatrix(i, j, 1);
                                countEdge++;

                            }
                        }
                    }  
                // cout << "emergency mesh" << endl;
                // E.display();  
                }


                if (countEdge == 4) {
                mesh.push_back(E);
                }

                else{
                    mesh.push_back(D);
                }

                countEdge = 0;
            }
        }
    }
    return;
}

void setOrientation(int n, vector<ElementMatrix>& mesh){
    // n is the size of the matrices
    // loop through all independent cycles
    // set an arbitrary orientation for each, based on the first encountered link
    for(auto iter = mesh.begin(); iter != mesh.end(); iter++){
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                if ((*iter).accessMatrix(i,j) == 1){
                    (*iter).accessMatrix(j, i, 0);
                    break;
                }
            }
        }        
    }
    return;
}