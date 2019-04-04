#ifndef _RESULTS_H_
#define _RESULTS_H_

#include "findmesh.h"
#include "elematrix.h"

using namespace std;

ElementMatrix getCurrent(int n, vector<float> X, vector<ElementMatrix>& mesh, ElementMatrix& I);
/* 
Input(s):
    mesh is a collection of ORIENTED, independent loops
    I is the nxn matrix where the branch currents will be stored
    X contains the mesh currents

Return(s): I, the branch currents matrix
*/

#endif