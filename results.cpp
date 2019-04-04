#include "results.h"

using namespace std;

ElementMatrix getCurrent(int n, vector<float> X, vector<ElementMatrix>& mesh, ElementMatrix& I){
    // X.size() and mesh.size() are equal
    int a = mesh.size();

    // Loop through all branches of the circuit
    // Traverse upper half only since lower half is just negated mirror image
    for (int i = 0; i < n-1; i++){
        for (int j = i+1; j < n; j++){
            // For each i, j iterate through all oriented meshes
            for (int k = 0; k < a; k++){
                // k is the mesh number
                // Iterate through each branch of the mesh
                if (mesh[k].accessMatrix(i,j) == 1){
                    // cout << "In node " << i+1 << " to " << j+1 << endl;
                    // cout << "Current number " << k+1 << " has a contribution." << endl;
                    // // Add the current both ways
                    // cout << "Adding current: " << X[k] << endl;
                    I.accessMatrix(i, j, X[k] + I.accessMatrix(i, j));
                    I.accessMatrix(j, i, I.accessMatrix(j, i) - X[k]);
                }
                else if(mesh[k].accessMatrix(j,i) == 1){
                    // cout << "(Else if branch) In node " << i+1 << " to " << j+1 << endl;
                    // cout << "Current number " << k+1 << " has a contribution." << endl;
                    // // Add the current both ways
                    // cout << "Adding current: " << X[k] << endl;
                    I.accessMatrix(i, j, I.accessMatrix(i, j) - X[k]);
                    I.accessMatrix(j, i, X[k] + I.accessMatrix(j, i));
                }
            }
        }
    }
    return I;
};


ElementMatrix getVoltage(int n, ElementMatrix& I, ElementMatrix& V, ElementMatrix& R, ElementMatrix& nodeVoltages){
    // Just multiply I and R for each element since V = IR plus any sources in that node
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            float voltage = I.accessMatrix(i,j) * R.accessMatrix(i,j);
            voltage += V.accessMatrix(i,j);
            nodeVoltages.accessMatrix(i,j,voltage);
        }
    }
    return nodeVoltages;
};