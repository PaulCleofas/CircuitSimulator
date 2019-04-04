#include "LU.h"

using namespace std;

ElementMatrix computeLHS(int n, vector<ElementMatrix>& mesh, ElementMatrix& R, ElementMatrix& V){
    // The number of independent loops determines the size of the matrix to be decomposed
    int m = mesh.size();
    ElementMatrix A(m);

    // Note1: loop orientation doesn't matter. It only affects sign of final answer when solving the matrix
    // Note2: resistances are put on matrix A, voltage sources on B.
    // Loop through each mesh
    for (int i = 0; i < m; i++){
        // For each row i, iterate through each mesh to find which
        // ones have a contribution to the current mesh equation, mesh[i].
        for (int j = 0; j < m; j++){
            for (int k = 0; k < n; k++){
                for (int l = 0; l < n; l++){
                    if ((mesh[i].accessMatrix(k, l) == 1 and mesh[j].accessMatrix(k, l) == 1)
                        or (mesh[i].accessMatrix(k, l) == 1 and mesh[j].accessMatrix(l, k) == 1)){
                        A.accessMatrix(i, j, R.accessMatrix(k, l) + A.accessMatrix(i,j));
                    }
                }
            }
        }
    }
    return A;
};


vector<int> computeRHS(int n, vector<ElementMatrix>& mesh, ElementMatrix& V){
    // Since B is one-dimensional, it can be represented by a vector
    vector<int> B;
    // The length of B is determined by the number of meshes
    int m = mesh.size();
    // Simply loop through each mesh, take the sum of all voltage sources
    // found in its components
    for (int i = 0; i < m; i++){
        float sum = 0;
        for (int j = 0; j < n; j++){
            for (int k = 0; k < n; k++){
                if (mesh[i].accessMatrix(j, k) == 1){
                    sum += V.accessMatrix(j, k);
                }
            }
        }
        B.push_back(sum);
    }
    return B;
};


// Source: http://ganeshtiwaridotcomdotnp.blogspot.com/2009/12/c-c-code-lu-decomposition-for-solving.html
// Modified by Daniel Florendo (04/03/2019)
void decompose(int m, ElementMatrix &A, ElementMatrix& L, ElementMatrix& U){
    int i,k,j,p;
    float sum;

    for (k = 0; k < m; k++){
        U.accessMatrix(k, k, 1);
        for (i = k; i < m; i++){
            sum = 0;
            for (p = 0; p < k; p++)
                sum += L.accessMatrix(i, p) * U.accessMatrix(p, k);
                L.accessMatrix(i, k, A.accessMatrix(i, k) - sum);
        }
        for (j = k+1; j < m; j++){
            sum = 0;
            for (p = 1; p < k; p++)
                sum += L.accessMatrix(k, p) * U.accessMatrix(p, j);
                auto value = (A.accessMatrix(k, j) - sum) / L.accessMatrix(k, k);
                U.accessMatrix(k, j, value);
        }
    }
};


// Source: http://ganeshtiwaridotcomdotnp.blogspot.com/2009/12/c-c-code-lu-decomposition-for-solving.html
// Modified by Daniel Florendo (04/03/2019)
vector<float> solveEquation(int m, ElementMatrix& L, ElementMatrix& U, vector<int>& B){
    signed int i,p;
    float sum;

    // Finding Z in LZ = B
    vector<float> Z;
    Z.reserve(m);
    for(int a = 0; a < m; a++){
        Z.push_back(0);
    }

    // Forward substitution method
    for (i = 0; i < m; i++) {
        sum = 0;
        for (p = 0; p < i; p++)
        sum += L.accessMatrix(i, p) * Z[p];
        float value = (B[i] - sum) / L.accessMatrix(i, i);
        Z.at(i) = value;
    }
    // Finding X in UX = Z
    vector<float> X;
    X.reserve(m);
    for(int a = 0; a < m; a++){
        X.push_back(0);
    }

    for (i = m-1; i > -1; i--) {
        sum = 0;
        for(p = m-1; p > i; p--)
            sum += U.accessMatrix(i, p) * X[p];
            float value = (Z[i] - sum) / U.accessMatrix(i, i);
            X.at(i) = value;
    }

    return X;
};