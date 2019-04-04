#include "results.h"

void getBranchCurrents(int n, ElementMatrix& I, vector<ElementMatrix>& mesh, vector<float>& meshCurrents) {
    unsigned int i;
    int j, k;

    // i represents the mesh index
    // j, k represent the row and column of the target mesh
    // l, m represent the row and column of the matrix for branch current
    for (i = 0; i < mesh.size(); i++) {
        for (j = 0; j < n; j++) {
            for (k = 0; k < n; k++) {
                if (mesh[i].accessMatrix(j, k) == 1) {
                    // Only put branch current on the upper triangular part
                    if (k < j) {
                        I.accessMatrix(k, j, I.accessMatrix(j, k) - meshCurrents[i]);
                        cout << "Mesh current of edge(" << k << "," << j << "):" << "in mesh " << i << " which is " << meshCurrents[i];
                        cout << " is subtracted from " << "current of edge(" << j << "," << k << ")" << endl;
                        // Negate the sign
                        I.accessMatrix(j, k, 0 -I.accessMatrix(k, j));
                    }

                    else if (j < k) {
                        I.accessMatrix(j, k, meshCurrents[i] + I.accessMatrix(j, k));
                        cout << "Mesh current of edge(" << k << "," << j << "):" << "in mesh " << i << " which is " << meshCurrents[i];
                        cout << " is added to " << "current of edge(" << j << "," << k << ")" << endl;
                        // Negate the sign
                        I.accessMatrix(k, j, 0 - I.accessMatrix(j, k));
                    }
                }
            }
        }
    }

}

void getNodeVoltages(int n, ElementMatrix& I, ElementMatrix& V, ElementMatrix& R, ElementMatrix& nodeVoltages){
    // Just multiply I and R for each element since V = IR plus any sources in that node
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            float voltage = I.accessMatrix(i,j) * R.accessMatrix(i,j);
            voltage += V.accessMatrix(i,j);
            nodeVoltages.accessMatrix(i,j,voltage);
        }
    }
};