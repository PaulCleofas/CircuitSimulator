#include "LU.h"

using namespace std;

vector<AdjacencyMatrix> prepareLU(int n, vector<AdjacencyMatrix>& mesh, ElementMatrix& R, ElementMatrix& V){
    /* 
    Input(s):
        mesh is a collection of oriented, independent loops
        R is the nxn resistance matrix
        V is the nxn voltage matrix

    Return(s): vector containing matrix A and B in the equation AI = B. I is the matrix containing mesh currents.
    */


    vector<AdjacencyMatrix> LUVector;
    // The number of independent loops determines the size of the matrix to be decomposed
    int m = mesh.size();
    AdjacencyMatrix A(m);
    AdjacencyMatrix B(m);

    // Note: loop orientation doesn't matter. It only affects sign of final answer when solving the matrix
    // resistances are put on matrix A, voltage sources on B.
    // Matrix A first
    // Loop through each mesh
    for (int i = 0; i < m; i++){
        // For each row of A[i], iterate through each mesh to find which
        // ones have a contribution to the current mesh, mesh[i].
        for (int j = 0; j < m; j++){
            for (int k = 0; k < n; k++){
                for (int l = 0; l < n; l++){
                    if ((mesh[i].accessMatrix(k, l) == 1 and mesh[j].accessMatrix(k, l) == 1)
                        or (mesh[i].accessMatrix(k, l) == 1 and mesh[j].accessMatrix(l, k) == 1)){
                        // cout << "Mesh: " << i+1 << " and Mesh: " << j+1 << " ";
                        // cout << "k: " << k+1 << ", l: " << l+1 << endl;
                        A.accessMatrix(i, j, R.accessMatrix(k, l) + A.accessMatrix(i,j));
                    }
                }
            }
        }
    }

    LUVector.push_back(A);

    // Now do Matrix B
    // But matrix B is not a square matrix...
    return LUVector;
};