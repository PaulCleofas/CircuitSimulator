#ifndef _RESULTS_H_
#define _RESULTS_H_

#include "elematrix.h"
#include <vector>

using namespace std;

void getBranchCurrents(int n, ElementMatrix& I, vector<ElementMatrix>& mesh, vector<float>& meshCurrents);

void getNodeVoltages(int n, ElementMatrix& I, ElementMatrix& V, ElementMatrix& R, ElementMatrix& nodeVoltages);

#endif

