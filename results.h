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

ElementMatrix getVoltage(int n, ElementMatrix& I, ElementMatrix& V, ElementMatrix& R, ElementMatrix& nodeVoltages);
/* 
Input(s):
    mesh is a collection of ORIENTED, independent loops
    nodeVoltages is the nxn matrix where the branch voltages will be stored
    I is the current matrix
    V is the voltage matrix
    R is the resistance matrix

Return(s): V, the branch currents matrix
*/


#endif